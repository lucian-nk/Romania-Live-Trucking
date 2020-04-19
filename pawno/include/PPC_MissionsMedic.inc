// Forward the function to timer to check players every second to see if they're carrying a Medic-load
forward Medic_CheckMedicLoads(playerid);
// Forward the public function used as a timer to load/unload your vehicle
forward Medic_LoadUnload(playerid);



// This function is called when a Medic wants to start a job by entering "/work"
Medic_StartRandomJob(playerid)
{
	if (APlayerData[playerid][JobStarted] == false)
	{
	    // Setup local variables
		new StartLoc[50], EndLoc[50], Load[50], RouteText[255], Float:x, Float:y, Float:z, LoadMsg[128];

		// Job has started
		APlayerData[playerid][JobStarted] = true;

		// Get a random LoadID from the Medic-products
		APlayerData[playerid][LoadID] = Product_GetRandom(PCV_MedicAmbulance);
		// Also get a random start-location and end-location
		APlayerData[playerid][JobLoc1] = Product_GetRandomStartLoc(APlayerData[playerid][LoadID]);
		APlayerData[playerid][JobLoc2] = Product_GetRandomEndLoc(APlayerData[playerid][LoadID]);

		// Set jobstep to 1 (going to load the goods)
		APlayerData[playerid][JobStep] = 1;
		// Get the startlocation, endlocation and the load texts
		format(StartLoc, 50, ALocations[APlayerData[playerid][JobLoc1]][LocationName]);
		format(EndLoc, 50, ALocations[APlayerData[playerid][JobLoc2]][LocationName]);
		format(Load, 50, ALoads[APlayerData[playerid][LoadID]][LoadName]);
		// Combine it all into a string for the TextDraw (the player can see this all the time) to describe the mission
		format(RouteText, 255, TXT_MedicHaulingCargoFromToPickup, Load, StartLoc, EndLoc);
		// Set the TextDraw so the player can see it
		TextDrawSetString(APlayerData[playerid][MissionText], RouteText);
		// Grab the x, y, z positions for the first location
		x = ALocations[APlayerData[playerid][JobLoc1]][LocX];
		y = ALocations[APlayerData[playerid][JobLoc1]][LocY];
		z = ALocations[APlayerData[playerid][JobLoc1]][LocZ];
		// Create a checkpoint where the player should load the goods
		SetPlayerCheckpoint(playerid, x, y, z, 7);
		// Store the vehicleID (required to be able to check if the player left his vehicle)
		APlayerData[playerid][VehicleID] = GetPlayerVehicleID(playerid);
		// Set the job-fail-time for the global vehicle-timer
		APlayerData[playerid][VehicleTimerTime] = Job_TimeToFailMission;
		// Inform the player that he must load his goods
		format(LoadMsg, 128, TXT_PickupCargoAt, Load, StartLoc);
		SendClientMessage(playerid, 0xFFFFFFFF, LoadMsg);
	}

	return 1;
}






// This function is called whenever a Medic player enters a checkpoint
Medic_OnPlayerEnterCheckpoint(playerid)
{
	// First check if the Medic player started a job or not
	if (APlayerData[playerid][JobStarted] == false) // Medic player delivered a Medic-load
	{
	    // This code handles stolen Medic-loads
		new vehicle = GetPlayerVehicleID(playerid);
		new trailer = GetVehicleTrailer(vehicle);

		// If the Medic player has a trailer, so detach and respawn the trailer
		if (trailer > 0)
		{
			DetachTrailerFromVehicle(vehicle);
			SetVehicleToRespawn(trailer);
		}
		else // The Medic player has no trailer, so the load is inside the truck -> remove player from vehicle and respawn the vehicle
		{
		    RemovePlayerFromVehicle(playerid);
			SetVehicleToRespawn(vehicle);
		}

		// Reward the Medic player (give cash and points)
		RewardPlayer(playerid, 50000, 5);
		

		// Increase the stats for completing a delivery of a stolen Medic load
		// Also save the data (in case the server crashes, progress would be lost)
		PlayerFile_Save(playerid);

		// Cleanup
		APlayerData[playerid][VehicleID] = 0;
		APlayerData[playerid][TrailerID] = 0;
	    // Disable the checkpoint where he must bring his load
		DisablePlayerCheckpoint(playerid);
		// Reset the missiontext
		TextDrawSetString(APlayerData[playerid][MissionText], Medic_NoJobText);
	}
	else // The Medic-player is doing a job
	{
		// Check if the player is inside his vehicle while entering a checkpoint
		if (GetPlayerVehicleID(playerid) == APlayerData[playerid][VehicleID])
		{
			new LoadMsg[128];

		    // Check the jobstep
		    switch (APlayerData[playerid][JobStep])
		    {
				// JobStep is 1 (Medic is loading his goods at the checkpoint)
		 		case 1: format(LoadMsg, 128, TXT_MedicLoadingGoods, ALoads[APlayerData[playerid][LoadID]][LoadName]);
				// JobStep is 2 (Medic is unloading his goods at the checkpoint)
				case 2: format(LoadMsg, 128, TXT_MedicUnloadingGoods, ALoads[APlayerData[playerid][LoadID]][LoadName]);
		    }

			// Disable the player's actions (he cannot move anymore)
			TogglePlayerControllable(playerid, 0);

			// Show the message to inform him what he's doing (loading/unloading)
			GameTextForPlayer(playerid, LoadMsg, 5000, 5);
			// Start a timer (Public function "LoadUnload(playerid)" gets called when the timer runs out)
			APlayerData[playerid][LoadingTimer] = SetTimerEx("Medic_LoadUnload", 5000, false, "d" , playerid);
		}
	}

	return 1;
}



// After a Medic entered a checkpoint, a timer is created. This function is called when the timer runs out
public Medic_LoadUnload(playerid)
{
	// Setup local variables
	new Name[24];

	// Get the player name
	GetPlayerName(playerid, Name, sizeof(Name));

	// Check the JobStep
	switch (APlayerData[playerid][JobStep])
	{
		case 1: // Player must load his goods
		{
		    // Setup local variables
			new StartLoc[50], EndLoc[50], Load[50], RouteText[255], Float:x, Float:y, Float:z, UnloadMsg[100];
			// Set JobStep to 2 (unloading goods)
			APlayerData[playerid][JobStep] = 2;
			// Delete the loading-checkpoint
			DisablePlayerCheckpoint(playerid);
			// Get the startlocation, endlocation and the load texts
			format(StartLoc, 50, ALocations[APlayerData[playerid][JobLoc1]][LocationName]);
			format(EndLoc, 50, ALocations[APlayerData[playerid][JobLoc2]][LocationName]);
			format(Load, 50, ALoads[APlayerData[playerid][LoadID]][LoadName]);

			// Update the missiontext
			format(RouteText, 255, TXT_HaulingCargoFromToDeliver, Load, StartLoc, EndLoc);
            format(RouteText, 255, TXT_MedicPickupCargoAt, Load, StartLoc, EndLoc);
            format(RouteText, 255, TXT_MedicDeliverCargoTo, Load, StartLoc, EndLoc);
			// Set the TextDraw so the player can see it
			TextDrawSetString(APlayerData[playerid][MissionText], RouteText);

			// Grab the x, y, z positions for the second location (to unload the goods)
			x = ALocations[APlayerData[playerid][JobLoc2]][LocX];
			y = ALocations[APlayerData[playerid][JobLoc2]][LocY];
			z = ALocations[APlayerData[playerid][JobLoc2]][LocZ];
			// Create a checkpoint where the player should unload the goods
			SetPlayerCheckpoint(playerid, x, y, z, 7);
			format(UnloadMsg, 100, TXT_DeliverCargoTo, Load, EndLoc);
			SendClientMessage(playerid, 0xFFFFFFFF, UnloadMsg);
		}
		case 2: // Player is delivering his goods
		{
		    // Setup local variables
			new StartLoc[50], EndLoc[50], Load[50], Msg1[128], Msg2[128];

			// Get the startlocation, endlocation and the load texts
			format(StartLoc, 50, ALocations[APlayerData[playerid][JobLoc1]][LocationName]);
			format(EndLoc, 50, ALocations[APlayerData[playerid][JobLoc2]][LocationName]);
			format(Load, 50, ALoads[APlayerData[playerid][LoadID]][LoadName]);

			// Construct the message sent to all players that this player completed a Medic mission
			format(Msg1, 128, TXT_PlayerCompletedMedicJob, Name, Load);
			format(Msg2, 128, TXT_PlayerCompletedMedicJobInfo, StartLoc, EndLoc);
			SendClientMessageToAll(0xFFFFFFFF, Msg1);
			SendClientMessageToAll(0xFFFFFFFF, Msg2);



		    // Setup local variables
			new Float:x1, Float:y1, Float:x2, Float:y2, Float:Distance, Message[128], Payment;
			// Grab the x, y, z positions for the first location (to load the goods)
			x1 = ALocations[APlayerData[playerid][JobLoc1]][LocX];
			y1 = ALocations[APlayerData[playerid][JobLoc1]][LocY];
			// Grab the x, y, z positions for the second location (to unload the goods)
			x2 = ALocations[APlayerData[playerid][JobLoc2]][LocX];
			y2 = ALocations[APlayerData[playerid][JobLoc2]][LocY];
			// Calculate the distance between both points
			Distance = floatsqroot(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));

			// Calculate the payment for the player
			Payment = floatround((Distance * ALoads[APlayerData[playerid][LoadID]][PayPerUnit]), floatround_floor);
			// Reward the player (give cash and points)
			RewardPlayer(playerid, Payment, 5);

			// Send a message to let the player know he finished his mission and got paid
			format(Message, 128, TXT_MedicRewardJob, Payment);
			SendClientMessage(playerid, 0xFFFFFFFF, Message);

			// Increase the stats for completing a Medic job
			APlayerData[playerid][StatsMedicJobs]++;
			// Also save the data (in case the server crashes, progress would be lost)
			PlayerFile_Save(playerid);

			// End the current Medic job (clear mission-data)
			Medic_EndJob(playerid);
		}
	}

    // Enable the player again (he can move again)
	TogglePlayerControllable(playerid, 1);

	return 1;
}



// This function gets called when the Medic player dies (or changes class)
Medic_EndJob(playerid)
{
	// Kill the PlayerCheckTimer
	KillTimer(APlayerData[playerid][PlayerCheckTimer]);

	// Scan through all players (to reset them to their default colors for the Medic-player)
	for (new PlayerToCheck; PlayerToCheck < MAX_PLAYERS; PlayerToCheck++)
	{
		// Check if this player is connected
		if (IsPlayerConnected(PlayerToCheck))
		    if (APlayerData[PlayerToCheck][PlayerClass] == ClassTruckDriver) // Reset the playercolor for truckers (only truckers can carry Medic-loads)
		        SetPlayerMarkerForPlayer(playerid, PlayerToCheck, ColorClassTruckDriver);
	}

	// Check if a job has started
	if (APlayerData[playerid][JobStarted] == true)
	{
		// Clear all data about the job from the player, so he can start a new one
		APlayerData[playerid][JobStarted] = false;
		APlayerData[playerid][JobID] = 0;
		APlayerData[playerid][JobStep] = 0;
		APlayerData[playerid][LoadID] = 0;
		APlayerData[playerid][JobLoc1] = 0;
		APlayerData[playerid][JobLoc2] = 0;
		// Reset the missiontext
		TextDrawSetString(APlayerData[playerid][MissionText], Medic_NoJobText);
		// Kill the LoadingTimer
		KillTimer(APlayerData[playerid][LoadingTimer]);
	     
	}

	// Also cleanup the vehicle and trailer id's
	APlayerData[playerid][VehicleID] = 0;
	APlayerData[playerid][TrailerID] = 0;
    // Disable the checkpoint where he must bring his load
	DisablePlayerCheckpoint(playerid);

	return 1;
}

