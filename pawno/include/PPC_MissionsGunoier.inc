// Forward the public function used as a timer to load/unload your vehicle
forward Gunoier_Raba_LoadUnload(playerid);



// This function is called when a pilot wants to start a job by entering "/work"
Gunoier_StartRandomJob(playerid)
{
	// Setup local variables
	new GunoierJobSet;

	// Check the vehicle-model of the player to decide which job the player can get
	if (GetVehicleModel(GetPlayerVehicleID(playerid)) == VehicleRaba)
           {
                        GunoierJobSet = Gunoier_Raba_SetRandomJob(playerid);
		    // Setup local variables
			new StartLoc[50], EndLoc[50], Load[50], RouteText[255], Float:x, Float:y, Float:z, LoadMsg[128];

			// Job has started
			APlayerData[playerid][JobStarted] = true;

			// Set jobstep to 1 (going to load the goods)
			APlayerData[playerid][JobStep] = 1;
			// Get the startlocation, endlocation and the load texts
			format(StartLoc, 50, ALocations[APlayerData[playerid][JobLoc1]][LocationName]);
			format(EndLoc, 50, ALocations[APlayerData[playerid][JobLoc2]][LocationName]);
			format(Load, 50, ALoads[APlayerData[playerid][LoadID]][LoadName]);
			// Combine it all into a string for the TextDraw (the player can see this all the time) to describe the mission
			format(RouteText, 255, TXT_TransportingFromToPickup, Load, StartLoc, EndLoc);
			// Set the TextDraw so the player can see it
			TextDrawSetString(APlayerData[playerid][MissionText], RouteText);
			// Grab the x, y, z positions for the first location
			x = ALocations[APlayerData[playerid][JobLoc1]][LocX];
			y = ALocations[APlayerData[playerid][JobLoc1]][LocY];
			z = ALocations[APlayerData[playerid][JobLoc1]][LocZ];
			// Create a checkpoint where the player should load the goods
			SetPlayerCheckpoint(playerid, x, y, z, 7);
                        APlayerData[playerid][VehicleTimerTime] = Job_TimeToFailMission;
			// Inform the player that he must load his goods
			format(LoadMsg, 128, TXT_PickupCargoAt, Load, StartLoc);
			SendClientMessage(playerid, 0xFFFFFFFF, LoadMsg);
	
	}

	return 1;
}

// This function sets a random job for a plane vehicle and returns 1 if a job has been set
// The function returns 0 if a job couldn't be set (if the player is driving an invalid vehicle to start piloting-jobs)
Gunoier_Raba_SetRandomJob(playerid)
{
	// If the player is the driver of the vehicle (GetPlayerVehicleSeat returns -1 if the player is not in a vehicle)
	if (GetPlayerVehicleSeat(playerid) == 0)
	{
		// Check the vehicle-model of the player to decide which job the player can get
		if (GetVehicleModel(GetPlayerVehicleID(playerid)) == VehicleRaba)
		{
			
				// Get a random LoadID from the pilot-products (only the planes)
				APlayerData[playerid][LoadID] = Product_GetRandom(PCV_GunoierRaba);
				// Also get a random start-location and end-location
				APlayerData[playerid][JobLoc1] = Product_GetRandomStartLoc(APlayerData[playerid][LoadID]);
				APlayerData[playerid][JobLoc2] = Product_GetRandomEndLoc(APlayerData[playerid][LoadID]);
                                APlayerData[playerid][VehicleTimerTime] = Job_TimeToFailMission;
				// Make sure the destination is not closeby (pilot-locations are ALL includes in the array)
				while (Locations_CheckDistance(APlayerData[playerid][JobLoc1], APlayerData[playerid][JobLoc2], 1000.0) == 0)
				{
				    // If both locations are too close together, keep searching for a random delivery-location that's further away
				    APlayerData[playerid][JobLoc2] = Product_GetRandomEndLoc(APlayerData[playerid][LoadID]);
				}
                                APlayerData[playerid][VehicleID] = GetPlayerVehicleID(playerid);
				// Return 1 to indicate that a job has been set correctly
				return 1;
		}
	}

	// If no job could be set correctly, return 0
	return 0;
}


// This function is called when a pilot enters a checkpoint
Gunoier_OnPlayerEnterCheckpoint(playerid)
{
	new LoadMsg[128];

    // Check the jobstep
    switch (APlayerData[playerid][JobStep])
    {
		// JobStep is 1 (pilot is loading his goods at the checkpoint)
 		case 1: format(LoadMsg, 128, TXT_LoadingGoods, ALoads[APlayerData[playerid][LoadID]][LoadName]);
		// JobStep is 2 (pilot is unloading his goods at the checkpoint)
		case 2: format(LoadMsg, 128, TXT_UnloadingGoods, ALoads[APlayerData[playerid][LoadID]][LoadName]);
    }

	// Disable the player's actions (he cannot move anymore)
	TogglePlayerControllable(playerid, 0);

	// Check the vehiclemodel of the player
	new vehicleid = GetPlayerVehicleID(playerid);
	switch (GetVehicleModel(vehicleid))
	{
	    case VehicleRaba: // A plane needs 5 seconds to load/unload
		{
			// Show the message to inform him what he's doing (loading/unloading)
			GameTextForPlayer(playerid, LoadMsg, 5000, 5);
			// Start a timer (Public function "LoadUnload(playerid)" gets called when the timer runs out)
			APlayerData[playerid][LoadingTimer] = SetTimerEx("Gunoier_Raba_LoadUnload", 5000, false, "d" , playerid);
		}
	}

	return 1;
}



// After a pilot entered a checkpoint, a timer is created. This function is called when the timer runs out
public Gunoier_Raba_LoadUnload(playerid)
{
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
			// Randomly set the load as overloaded (15% chance the load is overloaded)
			Gunoier_SetRandomOverloaded(playerid);


			// Update the missiontext
			format(RouteText, 255, TXT_TransportingFromToDeliver, Load, StartLoc, EndLoc);
			// Set the TextDraw so the player can see it
			TextDrawSetString(APlayerData[playerid][MissionText], RouteText);

			// Grab the x, y, z positions for the second location (to unload the goods)
			x = ALocations[APlayerData[playerid][JobLoc2]][LocX];
			y = ALocations[APlayerData[playerid][JobLoc2]][LocY];
			z = ALocations[APlayerData[playerid][JobLoc2]][LocZ];
			// Create a checkpoint where the player should unload the goods
			SetPlayerCheckpoint(playerid, x, y, z, 7);
			// Inform the player that he must unload his goods
			format(UnloadMsg, 100, TXT_DeliverCargoTo, Load, EndLoc);
			SendClientMessage(playerid, 0xFFFFFFFF, UnloadMsg);
		}
		case 2: // Player is delivering his goods
		{
		    // Setup local variables
			new StartLoc[50], EndLoc[50], Load[50], Msg1[128], Msg2[128], Name[24];

			// Get the player name
			GetPlayerName(playerid, Name, sizeof(Name));
			// Get the startlocation, endlocation and the load texts
			format(StartLoc, 50, ALocations[APlayerData[playerid][JobLoc1]][LocationName]);
			format(EndLoc, 50, ALocations[APlayerData[playerid][JobLoc2]][LocationName]);
			format(Load, 50, ALoads[APlayerData[playerid][LoadID]][LoadName]);

			// Construct the message sent to all players that this player completed a pilot mission
			format(Msg1, 128, TXT_PlayerCompletedGunoierJob, Name, Load);
			format(Msg2, 128, TXT_PlayerCompletedGunoierJobInfo, StartLoc, EndLoc);
			SendClientMessageToAll(0xFFFFFFFF, Msg1);
			SendClientMessageToAll(0xFFFFFFFF, Msg2);



		    // Setup local variables
			new Float:x1, Float:y1, Float:x2, Float:y2, Float:Distance, Message[128], Payment, Bonus;
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
			// Pay the player based on the distance between the loading-point and unloading-point
			RewardPlayer(playerid, Payment, 1);

			// Send a message to let the player know he finished his mission and got paid
			format(Message, 128, TXT_RewardJob, Payment);
			SendClientMessage(playerid, 0xFFFFFFFF, Message);
                        if (APlayerData[playerid][Overloaded] == true)
			{
			        // Calculate the bonus
			        Bonus = (Payment * 25) / 100;
				// Pay the bonus to the player
				RewardPlayer(playerid, Bonus, 0);
				// Send a message to let the player know he was overloaded and got paid
				format(Message, 128, TXT_TruckerBonusOverloaded, Bonus);
				SendClientMessage(playerid, 0xFFFFFFFF, Message);
			}
                        if (AVehicleData[APlayerData[playerid][VehicleID]][Owned] == true)
			{
			        // Calculate the bonus
			        Bonus = (Payment * 10) / 100;
				// Pay the bonus to the player
				RewardPlayer(playerid, Bonus, 0);
				// Send a message to let the player know he was overloaded and got paid
				format(Message, 128, TXT_TruckerBonusOwnVehicle, Bonus);
				SendClientMessage(playerid, 0xFFFFFFFF, Message);
			}
			// Increase the stats for completing a pilot job
			APlayerData[playerid][StatsGunoierJobs]++;
			// Also save the data (in case the server crashes, progress would be lost)
			PlayerFile_Save(playerid);

			// End the current pilot job (clear mission-data)
			Gunoier_EndJob(playerid);
		}
	}

    // Enable the player again (he can move again)
	TogglePlayerControllable(playerid, 1);
	// Start the engine again (in case the vehicle was a helicopter, where the engine was turned off by entering a checkpoint)
	new vehicleid = GetPlayerVehicleID(playerid);
	new engine,lights,alarm,doors,bonnet,boot,objective;
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	SetVehicleParamsEx(vehicleid, 1, lights, alarm, doors, bonnet, boot, objective);

	return 1;
}

Gunoier_SetRandomOverloaded(playerid)
{
	// Setup local variables
	new Name[24], Msg[128];

	// Check the vehicle model that the player is driving
	if (GetVehicleModel(GetPlayerVehicleID(playerid)) == VehicleRaba)
	{


	// The player wasn't driving one of the above vehicle models, so this one can be overloaded
	// There is a 15% chance that your load will be overloaded
	if (random(100) <= 10)
	{
		// Set overloaded for this player to True
	    APlayerData[playerid][Overloaded] = true;
	    // Add 2 to the player's wanted level
	    SetPlayerWantedLevel(playerid, GetPlayerWantedLevel(playerid) + 2);
		// Inform the police this trucker is overloaded
		GetPlayerName(playerid, Name, sizeof(Name));
                SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}Ai fost supra-incarcat,evita politia");
		format(Msg, 128, "{00FF00}{FFFF00}%s{00FF00} este supraincarcat, prinde-l si amendeaza-l", Name);
		Police_SendMessage(Msg);
	}
        }
	return 1;
}

// This function is used to cleanup the current job
Gunoier_EndJob(playerid)
{
	// Check if a job has started
	if (APlayerData[playerid][JobStarted] == true)
	{
		// Clear all data about the job from the player, so he can start a new one
		APlayerData[playerid][JobStarted] = false;
		APlayerData[playerid][JobStep] = 0;
		APlayerData[playerid][LoadID] = 0;
		APlayerData[playerid][JobLoc1] = 0;
		APlayerData[playerid][JobLoc2] = 0;

		// Delete the checkpoint
		DisablePlayerCheckpoint(playerid);
		// Reset the missiontext
		TextDrawSetString(APlayerData[playerid][MissionText], Gunoier_NoJobText);
		// Kill the LoadingTimer
		KillTimer(APlayerData[playerid][LoadingTimer]);
	}

	return 1;
}

