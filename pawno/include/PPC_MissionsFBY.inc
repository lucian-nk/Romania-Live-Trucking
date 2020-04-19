// Forward the function to timer to check players every second to see if they're wanted
forward FBY_CheckWantedPlayers(playerid);
forward UnjailPlayer(playerid);



// This timer is created every time a player changes his class to FBY
public FBY_CheckWantedPlayers(playerid)
{
	// Scan through all players
	for (new PlayerToCheck; PlayerToCheck < MAX_PLAYERS; PlayerToCheck++)
	{
		// check if this player is connected
		if (IsPlayerConnected(PlayerToCheck))
		{
			//Check if that player is wanted
			if (GetPlayerWantedLevel(PlayerToCheck) > 0 && PlayerToCheck != playerid)
			    SetPlayerMarkerForPlayer(playerid, PlayerToCheck, 0xFF0000FF); // Make that player red to the FBY-player
			else
			{
				// Reset the playercolor based on the player's class
			    switch (APlayerData[PlayerToCheck][PlayerClass])
			    {
			        case ClassTruckDriver: SetPlayerMarkerForPlayer(playerid, PlayerToCheck, ColorClassTruckDriver);
			        case ClassBusDriver: SetPlayerMarkerForPlayer(playerid, PlayerToCheck, ColorClassBusDriver);
			        case ClassPilot: SetPlayerMarkerForPlayer(playerid, PlayerToCheck, ColorClassPilot);
			        case ClassFBY: SetPlayerMarkerForPlayer(playerid, PlayerToCheck, ColorClassFBY);
			        case ClassMafia: SetPlayerMarkerForPlayer(playerid, PlayerToCheck, ColorClassMafia);
			        case ClassCourier: SetPlayerMarkerForPlayer(playerid, PlayerToCheck, ColorClassCourier);
			        case ClassAssistance: SetPlayerMarkerForPlayer(playerid, PlayerToCheck, ColorClassAssistance);
			    }
			}
		}
	}
}

// This function gets called when a FBY player presses the SECUNDAIRY FIRE button (to warn nearby wanted players)
FBY_WarnNearbyPlayers(playerid)
{
	// Setup local variables
	new Float:x, Float:y, Float:z, Name[24], Msg[128];

	// Scan through all players
	for (new PlayerToCheck; PlayerToCheck < MAX_PLAYERS; PlayerToCheck++)
	{
		// check if this player is connected
		if (IsPlayerConnected(PlayerToCheck))
		{
			// Check if the current player is wanted
			if (GetPlayerWantedLevel(PlayerToCheck) > 0 && PlayerToCheck != playerid)
			{
			    // Get the position of this player
			    GetPlayerPos(PlayerToCheck, x, y, z);
			    // Check if the FBY-player is in range of the player
				if (IsPlayerInRangeOfPoint(playerid, 50.0, x, y, z))
				{
					GameTextForPlayer(PlayerToCheck, TXT_FBYWarnPlayer, 3000, 4); // Warn the player
					// Also start a timer which gives the player a chance to stop and get a fine
					// If he doesn't stop, the player will be sent to jail when he gets fined
					if (APlayerData[PlayerToCheck][FBYWarnedMe] == false)
					{
					    APlayerData[PlayerToCheck][FBYWarnedMe] = true;
						APlayerData[PlayerToCheck][Value_FBYCanJailMe] = 60;
						APlayerData[PlayerToCheck][Timer_FBYCanJailMe] = SetTimerEx("Timer_FBYCanJailPlayer", 5000, true, "i", PlayerToCheck);
					}

					// Let the FBY player know that he warned the player
					GetPlayerName(PlayerToCheck, Name, sizeof(Name));
					format(Msg, 128, "{00FF00}You've warned {FFFF00}%s", Name);
					SendClientMessage(playerid, 0xFFFFFFFF, Msg);
				}
			}
		}
	}

	return 1;
}

// This function gets called when a FBY player presses the FIRE key (to fine nearby wanted players) when he's on foot
FBY_FineNearbyPlayers(playerid)
{
	// Setup local variables
	new Float:x, Float:y, Float:z;

	// Scan through all players
	for (new PlayerToCheck; PlayerToCheck < MAX_PLAYERS; PlayerToCheck++)
	{
		// check if this player is connected
		if (IsPlayerConnected(PlayerToCheck))
		{
			// Check if the other player isn't the same FBY player
			if (PlayerToCheck != playerid)
			{
				// Check if the current player is wanted and the wanted player is driving slowly (below 30 kph)
				if ((GetPlayerWantedLevel(PlayerToCheck) > 0) && (APlayerData[PlayerToCheck][PlayerSpeed] < 30))
				{
				    // Get the position of this player
				    GetPlayerPos(PlayerToCheck, x, y, z);

				    // Check if the FBY-player is in range of the player (FBY player and wanted player must be within 10 meters of eachother)
					if (IsPlayerInRangeOfPoint(playerid, 10.0, x, y, z))
					{
					    // Fine the player
						FBY_PayFine(playerid, PlayerToCheck);

						// Exit the function
						return 1;
					}

					// Check if the FBY-player is in range of the player (he can be inside his vehicle or on foot)
					if (IsPlayerInRangeOfPoint(playerid, 50.0, x, y, z))
					{
						GameTextForPlayer(PlayerToCheck, TXT_FBYWarnPlayer, 3000, 4); // Warn the player
						// Also start a timer which gives the player a chance to stop and get a fine
						// If he doesn't stop, the player will be sent to jail when he gets fined
						if (APlayerData[PlayerToCheck][FBYWarnedMe] == false)
						{
						    APlayerData[PlayerToCheck][FBYWarnedMe] = true;
							APlayerData[PlayerToCheck][Value_FBYCanJailMe] = DefaultWarnTimeBeforeJail;
							APlayerData[PlayerToCheck][Timer_FBYCanJailMe] = SetTimerEx("Timer_FBYCanJailPlayer", 5000, true, "i", PlayerToCheck);
						}
					}
				}
			}
		}
	}

	return 1;
}

// Pay the FBY player and fine the player
FBY_PayFine(playerid, PlayerToFine)
{
	// Setup local variables
	new FBYName[24], FinedPlayerName[24], FBYMsg[200], PlayerMsg[200], JailTime, Fine;

	// Get the names of the FBY player and the wanted player
	GetPlayerName(playerid, FBYName, 24);
	GetPlayerName(PlayerToFine, FinedPlayerName, 24);

	// Check if the wanted player's timer hasn't ran out yet
	if (APlayerData[PlayerToFine][FBYCanJailMe] == false)
	{
		// Calculate the fine
		Fine = GetPlayerWantedLevel(PlayerToFine) * DefaultFinePerStar;
		// Reward the FBY player (give cash and points)
		RewardPlayer(playerid, Fine, GetPlayerWantedLevel(PlayerToFine));
		// Let the FBY player know that he fined the player
		format(FBYMsg, 200, TXT_FBYFinedPlayerReward, FinedPlayerName, Fine);
		SendClientMessage(playerid, 0xFFFFFFFF, FBYMsg);
		// Let the wanted player pay the fine
		RewardPlayer(PlayerToFine, -Fine, 0);
		format(PlayerMsg, 200, TXT_PlayerGotFinedByFBY, FBYName, Fine);
		SendClientMessage(PlayerToFine, 0xFFFFFFFF, PlayerMsg);
		// Let the other players know that the FBY player has fined the wanted player
		format(FBYMsg, 200, TXT_FBYFinedPlayer, FBYName, FinedPlayerName);
		SendClientMessageToAll(0xFFFFFFFF, FBYMsg);
		// Increase the stats for fining a player
		APlayerData[playerid][StatsFBYFined]++;
	}
	else // The wanted player didn't pull over, now the FBY player has the right to send him to jail and double the fine
	{
	    // Set jailtime
	    JailTime = DefaultJailTime;
		// Calculate the fine (double the normal fine)
		Fine = GetPlayerWantedLevel(PlayerToFine) * DefaultFinePerStar * 2;
		// Reward the FBY player (give cash and points)
		RewardPlayer(playerid, Fine, GetPlayerWantedLevel(PlayerToFine));
		// Let the FBY player know that he jailed the wanted player
		format(FBYMsg, 200, TXT_FBYJailedPlayerReward, FinedPlayerName, Fine);
		SendClientMessage(playerid, 0xFFFFFFFF, FBYMsg);
		// Let the wanted player pay a double fine
		RewardPlayer(PlayerToFine, -Fine, 0);
		// Let the player know he's been jailed and for how long
		format(PlayerMsg, 200, TXT_PlayerGotJailedByFBY, FBYName, (JailTime / 60));
		SendClientMessage(PlayerToFine, 0xFFFFFFFF, PlayerMsg);
		// Let the other players know that the FBY player has jailed the wanted player
		format(FBYMsg, 200, TXT_FBYJailedPlayer, FBYName, FinedPlayerName, (JailTime / 60));
		SendClientMessageToAll(0xFFFFFFFF, FBYMsg);
		// Teleport the player to jail
		FBY_JailPlayer(PlayerToFine, JailTime);
		// Increase the stats for jailing a player
		APlayerData[playerid][StatsFBYJailed]++;
	}

	// Clear the wanted player's wanted status (the speedometer will automatically clear all data and kill the timer)
	SetPlayerWantedLevel(PlayerToFine, 0);

	// Also save the data (in case the server crashes, progress would be lost)
	PlayerFile_Save(playerid);
	PlayerFile_Save(PlayerToFine);

	return 1;
}

// This function ports the player inside the jail and sets a timer to get him back out
FBY_JailPlayer(playerid, JailTime)
{
	// First remove the player from his vehicle
	RemovePlayerFromVehicle(playerid);
	// Set the player in the virtual world of the jail (so other players cannot see the jailed players on their radar)
	SetPlayerVirtualWorld(playerid, WORLD_JAIL);
	// Set player interior to the FBY station in San Fierro
	SetPlayerInterior(playerid, 10);
	// Put the player inside the jail
	SetPlayerPos(playerid, 220.0, 110.0, 999.1);

	// Store the jailtime for this player
	APlayerData[playerid][PlayerJailed] = JailTime;
	// Start the jailtimer, which checks every second if the player is allowed to get out
	KillTimer(APlayerData[playerid][PlayerJailedTimer]);
	APlayerData[playerid][PlayerJailedTimer] = SetTimerEx("UnjailPlayer", 1000, true, "i", playerid);

	// If the player started a job, let it fail
	if (APlayerData[playerid][JobStarted] == true)
	{
		// Stop any job that may have started
		switch (APlayerData[playerid][PlayerClass])
		{
			case ClassTruckDriver: Trucker_EndJob(playerid);
			case ClassBusDriver: BusDriver_EndJob(playerid);
			case ClassPilot: Pilot_EndJob(playerid);
			case ClassFBY: FBY_EndJob(playerid);
			case ClassMafia: Mafia_EndJob(playerid);
			case ClassCourier: Courier_EndJob(playerid);
			case ClassAssistance: Assistance_EndJob(playerid);
		}

		// Inform the player that he failed the mission
		GameTextForPlayer(playerid, TXT_FailedMission, 5000, 4);
		// Reduce the player's cash by 1000
		RewardPlayer(playerid, -1000, 0);
	}

	return 1;
}
// This function gets called when the FBY player dies (or changes class)
FBY_EndJob(playerid)
{
	// Kill the PlayerCheckTimer
	KillTimer(APlayerData[playerid][PlayerCheckTimer]);

	// Scan through all players (to reset them to their default colors for the FBY-player)
	for (new PlayerToCheck; PlayerToCheck < MAX_PLAYERS; PlayerToCheck++)
	{
		// check if this player is connected
		if (IsPlayerConnected(PlayerToCheck))
		{
			// Reset the playercolor based on the player's class
		    switch (APlayerData[PlayerToCheck][PlayerClass])
		    {
		        case ClassTruckDriver: SetPlayerMarkerForPlayer(playerid, PlayerToCheck, ColorClassTruckDriver);
		        case ClassBusDriver: SetPlayerMarkerForPlayer(playerid, PlayerToCheck, ColorClassBusDriver);
		        case ClassPilot: SetPlayerMarkerForPlayer(playerid, PlayerToCheck, ColorClassPilot);
		        case ClassFBY: SetPlayerMarkerForPlayer(playerid, PlayerToCheck, ColorClassFBY);
		        case ClassMafia: SetPlayerMarkerForPlayer(playerid, PlayerToCheck, ColorClassMafia);
		        case ClassCourier: SetPlayerMarkerForPlayer(playerid, PlayerToCheck, ColorClassCourier);
		        case ClassAssistance: SetPlayerMarkerForPlayer(playerid, PlayerToCheck, ColorClassAssistance);
		    }
		}
	}

	return 1;
}

// This timer is started when a wanted player was warned by a FBY player
forward Timer_FBYCanJailPlayer(playerid);
public Timer_FBYCanJailPlayer(playerid)
{
	// Setup local variables
	new Msg[128];

	// Let the player know how much time he has left to pull over
	format(Msg, 128, "{FF0000}You have %i seconds to pull over and stop", APlayerData[playerid][Value_FBYCanJailMe]);
	SendClientMessage(playerid, 0xFFFFFFFF, Msg);

	// Check if the timer has ran out
	if (APlayerData[playerid][Value_FBYCanJailMe] == 0)
	{
	    // Set a switch that indicates that this player didn't stop when he got the warning from the FBY player
	    // When the FBY can catch him now, he'll be sent to jail and the fine is doubled
	    APlayerData[playerid][FBYCanJailMe] = true;
		// Also kill the timer, as it's not needed anymore
		KillTimer(APlayerData[playerid][Timer_FBYCanJailMe]);
		// Let the player know what consequences it will have by not stopping
		format(Msg, 128, "{FF0000}You didn't pull-over and stop, now the FBY can send you to jail immediately");
		SendClientMessage(playerid, 0xFFFFFFFF, Msg);
		format(Msg, 128, "{FF0000}Your fines will be doubled as well");
		SendClientMessage(playerid, 0xFFFFFFFF, Msg);
	}

	// Reduce the remaining time by 5 seconds
	APlayerData[playerid][Value_FBYCanJailMe] = APlayerData[playerid][Value_FBYCanJailMe] - 5;

	return 1;
}
// This function sends the given message to all FBY players
FBY_SendMessage(FBYMessage[])
{
	for (new FBYID; FBYID < MAX_PLAYERS; FBYID++) // Loop through all players
		if (APlayerData[FBYID][LoggedIn] == true) // Check if this player has logged in
		    if (APlayerData[FBYID][PlayerClass] == ClassFBY) // Check if this player is a FBY player
				SendClientMessage(FBYID, 0xFFFFFFFF, FBYMessage); // Send the message to the FBY player
}

