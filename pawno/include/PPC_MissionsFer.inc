// Setup a custom type that holds all data about a Fer route
enum TFerRoute
{
	HomeDepot, // The ID of the home-depot
	LineNumber, // The number of the Ferroute
	Score, // Determines the score the player gets when he reaches the end of the Ferroute
	RouteDescription[100], // The description of the Ferroute
	Locations[30] // The Location-IDs where the player must load/unload passengers (up to 30 Ferstops per route)
}

// Setup an array that holds all Ferroute data
new AFerRoutes[][TFerRoute] =
{
	// HomeDepot, LineNumber, array of FerLocations (location "-1" states the end of the route -> start over from the first location)
	{64, 101, 2, "SomeStart1 - SomeStop1", {65, 67, 94, 99, 69, 75, 76, 65, -1}},
	{64, 102, 1, "SomeStart2 - SomeStop2", {94, 96, 99, 100, 71, 94, -1}},
	{64, 201, 3, "SomeStart3 - SomeStop3", {92, 93, 91, 89, 88, 86, 84, 85, 79, 73, 72, 92, -1}},
	{64, 301, 2, "Las Barrancas - Bayside", {108, 107, 105, 103, 104, 108, -1}},
	{64, 302, 2, "Bayside - Las Payasdas", {103, 104, 106, 109, 105, 103, -1}},
	{64, 303, 2, "Fort Carson - El Quebrados", {112, 108, 105, 106, 108, 111, 112, -1}},
	{64, 401, 2, "Palomino Creek - Dillimore", {116, 117, 120, 118, 115, 116, -1}}
};



// Forward the function to Load or Unload passengers during missions (used by a timer)
forward Fer_LoadUnload(playerid, PassengersOnFerStop);



// This function is called when a Fer enters a checkpoint
Fer_EnterRaceCheckpoint(playerid)
{
	// Check if the player is inside his vehicle while entering a checkpoint
	if (GetPlayerVehicleID(playerid) == APlayerData[playerid][VehicleID])
	{
		// Setup local variables
		new LineNr, Description[100], PassengersOnFer, PassengersOnFerStop, Job, RouteText[255];

		// Show that the player is loading and unloading passengers
	//	GameTextForPlayer(playerid, "Loading/unloading passengers... Please wait", 5000, 4);

		// Disable the player's actions (he cannot move anymore)
		//TogglePlayerControllable(playerid, 0);

		// Get the JobID
		Job = APlayerData[playerid][JobID];
		// Get the data to construct the textdraw
		LineNr = AFerRoutes[Job][LineNumber];
		format(Description, 100, "%s", AFerRoutes[Job][RouteDescription]);
		PassengersOnFer = APlayerData[playerid][Passengers];
		// Determine a random number of passengers on the Ferstop (between 10 and 30 passengers can be waiting at the Ferstop)
		PassengersOnFerStop = random(20) + 10;
		// Limit the number of passengers to 100
	//	if ((APlayerData[playerid][Passengers] + PassengersOnFerStop) > 100)
	//	    PassengersOnFerStop = 100 - APlayerData[playerid][Passengers];

		// Combine it all into a string for the TextDraw (the player can see this all the time) to describe the mission
		format(RouteText, 255, TXT_FerFerStopInfo, LineNr, Description, PassengersOnFer, PassengersOnFerStop);
		// Set the TextDraw so the player can see it
		TextDrawSetString(APlayerData[playerid][MissionText], RouteText);

		// Start a timer (Public function "Fer_LoadUnload(playerid)" gets called when the timer runs out)
		APlayerData[playerid][LoadingTimer] = SetTimerEx("Fer_LoadUnload", 5000, false, "di" , playerid, PassengersOnFerStop);
	}

	return 1;
}

// After a truckdriver entered a checkpoint, a timer is created. This function is called when the timer runs out
public Fer_LoadUnload(playerid, PassengersOnFerStop)
{
    // Setup local variables
	new RouteText[255], Float:x, Float:y, Float:z, Job, NextLoc, NextStep, Depot, Msg[128];
	new PassengersOnFer, PassengersGettingOff, LineNr, Description[100], Payment;
	new Float:xn, Float: yn, Float:zn;

	// Also delete any race-checkpoint (at the location of the homedepot)
	DisablePlayerCheckpoint(playerid);
	// Delete the checkpoint where the player just loaded/unloaded passengers
	DisablePlayerRaceCheckpoint(playerid);

	// Get the JobID
	Job = APlayerData[playerid][JobID];
	// Select the next location (jobstep)
	APlayerData[playerid][JobStep]++;
	NextStep = APlayerData[playerid][JobStep];
	// Determine a random number of passengers leaving the Fer and let them leave (if there are any)
	if (APlayerData[playerid][Passengers] > 0)
		PassengersGettingOff = random(APlayerData[playerid][Passengers]);
	APlayerData[playerid][Passengers] = APlayerData[playerid][Passengers] - PassengersGettingOff;
	// Also let the passengers, that are waiting at the Ferstop, get on the Fer
	APlayerData[playerid][Passengers] = APlayerData[playerid][Passengers] + PassengersOnFerStop;

	// Grab the next locationID
	NextLoc = AFerRoutes[Job][Locations][NextStep];
	// If the end of the route is reached, restart it from location 0 (also add a racecheckpoint at the Ferdepot to end the mission)
	if (NextLoc == -1)
	{
	    // Setup local variables
		new MissionMsg[128], Name[24];

		// Get the player name
		GetPlayerName(playerid, Name, sizeof(Name));
		// Construct the message sent to all players that this player completed a mafia mission
		format(MissionMsg, 128, TXT_PlayerCompletedFerLine, Name, AFerRoutes[Job][LineNumber]);
		SendClientMessageToAll(0xFFFFFFFF, MissionMsg);



	    // Start the route again from the first location
	    NextStep = 1;
	    APlayerData[playerid][JobStep] = NextStep;
		// Grab the locationID of this Ferstop
		NextLoc = AFerRoutes[Job][Locations][NextStep];

		// Get the homedepot locationID
		Depot = AFerRoutes[Job][HomeDepot];
		// Grab the coordinates of the homedepot
		x = ALocations[Depot][LocX];
		y = ALocations[Depot][LocY];
		z = ALocations[Depot][LocZ];
		// Create a checkpoint at the coordinates of the homedepot
		SetPlayerCheckpoint(playerid, x, y, z, 7);
		// Reward the player with a score for completing a Ferroute
		RewardPlayer(playerid, 0, AFerRoutes[Job][Score]);

		// Increase the stats for completing a Fer-route
		APlayerData[playerid][StatsFerJobs]++;
		// Also save the data (in case the server crashes, progress would be lost)
		PlayerFile_Save(playerid);
	}

	// Get the data to construct the textdraw
	LineNr = AFerRoutes[Job][LineNumber];
	format(Description, 100, "%s", AFerRoutes[Job][RouteDescription]);
	PassengersOnFer = APlayerData[playerid][Passengers];
	// Combine it all into a string for the TextDraw (the player can see this all the time) to describe the mission
	format(RouteText, 255, TXT_FerJobInfo, LineNr, Description, PassengersOnFer);
	// Set the TextDraw so the player can see it
	TextDrawSetString(APlayerData[playerid][MissionText], RouteText);

	// Grab the coordinates of the next location
	x = ALocations[NextLoc][LocX];
	y = ALocations[NextLoc][LocY];
	z = ALocations[NextLoc][LocZ];
	// Create a new checkpoint where the player should load/unload the passengers
	SetPlayerRaceCheckpoint(playerid, 2, x, y, z, xn, yn, zn, 7);

    // Enable the player again (he can move again)
	TogglePlayerControllable(playerid, 1);

	// Reward the player (every passengers that left the Fer pays $9) and let him know about it
	if (PassengersGettingOff != 0)
	{
		// Reward the player (give cash and points)
		Payment = PassengersGettingOff * 9;
		RewardPlayer(playerid, Payment, 0);
		format(Msg, 128, TXT_FerReward, Payment);
		GameTextForPlayer(playerid, Msg, 3000, 4);
	}

	return 1;
}



// This function starts the Fer job
Fer_StartJob(playerid, Job)
{
	new Vehicle = GetPlayerVehicleID(playerid), StartLoc;
	new Float:xn, Float: yn, Float:zn;

    // Setup local variables
	new RouteText[255], Float:x, Float:y, Float:z, LineNr, Description[100], PassengersOnFer;

	// Job has started
	APlayerData[playerid][JobStarted] = true;
	// Store VehicleID
	APlayerData[playerid][VehicleID] = Vehicle;
	// Store the Ferroute Ferroute
	APlayerData[playerid][JobID] = Job;
	// Set jobstep to 0 (going to the first Ferstop)
	APlayerData[playerid][JobStep] = 0;

	// Get the data to construct the textdraw
	LineNr = AFerRoutes[Job][LineNumber];
	format(Description, 100, "%s", AFerRoutes[Job][RouteDescription]);
	PassengersOnFer = 0;
	APlayerData[playerid][Passengers] = PassengersOnFer;
	// Combine it all into a string for the TextDraw (the player can see this all the time) to describe the mission
	format(RouteText, 255, TXT_FerJobInfo, LineNr, Description, PassengersOnFer);
	// Set the TextDraw so the player can see it
	TextDrawSetString(APlayerData[playerid][MissionText], RouteText);
	// Grab the x, y, z positions for the first location
	StartLoc = AFerRoutes[Job][Locations][0];
	x = ALocations[StartLoc][LocX];
	y = ALocations[StartLoc][LocY];
	z = ALocations[StartLoc][LocZ];
	// Create a race-checkpoint where the player should load/unload passengers
	SetPlayerRaceCheckpoint(playerid, 2, x, y, z, xn, yn, zn, 7);
	// Set the job-fail-time for the global vehicle-timer
	APlayerData[playerid][VehicleTimerTime] = Job_TimeToFailMission;

	return 1;
}

// This function is used to cleanup the current job
Fer_EndJob(playerid)
{
	if (APlayerData[playerid][JobStarted] == true)
	{
		// Clear all data about the job from the player, so he can start a new one
		APlayerData[playerid][JobStarted] = false;
		APlayerData[playerid][JobStep] = 0;
		APlayerData[playerid][JobID] = 0;
		APlayerData[playerid][Passengers] = 0;
		APlayerData[playerid][VehicleTimerTime] = 0;
		APlayerData[playerid][VehicleID] = 0;

		// Delete the checkpoint
		DisablePlayerCheckpoint(playerid);
		// Also delete any race-checkpoint (at the location of the homedepot)
		DisablePlayerRaceCheckpoint(playerid);
		// Reset the missiontext
		TextDrawSetString(APlayerData[playerid][MissionText], Fer_NoJobText);
	}

	return 1;
}

