forward Marinar_LoadUnload(playerid);
Marinar_OnPlayerEnterCheckpoint(playerid)
{
	if (GetPlayerVehicleID(playerid) == APlayerData[playerid][VehicleID])
	{
		if (APlayerData[playerid][TrailerID] == GetVehicleTrailer(GetPlayerVehicleID(playerid)))
		{
		    switch (APlayerData[playerid][JobStep])
		    {
				// JobStep is 1 (truckdriver is loading his goods at the checkpoint)
		 		case 1: GameTextForPlayer(playerid, TXT_MarinarLoadingGoods, 5000, 4);
				// JobStep is 2 (truckdriver is unloading his goods at the checkpoint) or 3 (unloading for convoys)
				case 2, 3: GameTextForPlayer(playerid, TXT_MarinarUnloadingGoods, 5000, 4);
		    }
			TogglePlayerControllable(playerid, 0);
			APlayerData[playerid][LoadingTimer] = SetTimerEx("Marinar_LoadUnload", 5000, false, "d" , playerid);
		}
		else
		    SendClientMessage(playerid, 0xFFFFFFFF, TXT_NeedTrailerToProceed);
	}
	else
	    SendClientMessage(playerid, 0xFFFFFFFF, "Ai Nevoie De O Barca pentru A Continua");

	return 1;
}
public Marinar_LoadUnload(playerid)
{
	if (APlayerData[playerid][InConvoy] == true)
	{
	    if (APlayerData[playerid][JobStep] == 1)
		{
	        APlayerData[playerid][JobStep] = 2; 
			TextDrawSetString(APlayerData[playerid][MissionText], TXT_WaitingMembersToLoadCargo);
		}
		if (APlayerData[playerid][JobStep] == 3)
		{
	        APlayerData[playerid][JobStep] = 4; 
	    	TextDrawSetString(APlayerData[playerid][MissionText], TXT_WaitingMembersToUnLoadCargo);
		}
		DisablePlayerCheckpoint(playerid); 
		TogglePlayerControllable(playerid, 1); 
		return 1; 
	}
	switch (APlayerData[playerid][JobStep])
	{
		case 1: // Player must load his goods
		{
			new StartLoc[50], EndLoc[50], Load[50], RouteText[255], Float:x, Float:y, Float:z, UnloadMsg[100];
			APlayerData[playerid][JobStep] = 2;
			DisablePlayerCheckpoint(playerid);
			format(StartLoc, 50, ALocations[APlayerData[playerid][JobLoc1]][LocationName]);
			format(EndLoc, 50, ALocations[APlayerData[playerid][JobLoc2]][LocationName]);
			format(Load, 50, ALoads[APlayerData[playerid][LoadID]][LoadName]);
			Marinar_SetRandomOverloaded(playerid);
			format(RouteText, 255, TXT_trasporta, Load, StartLoc, EndLoc);
			if (APlayerData[playerid][Overloaded] == true)
			{
				format(RouteText, 255, "%s%s", RouteText, " ~r~(OL)~w~");
				SendClientMessage(playerid, 0xFFFFFFFF, TXT_MarinarOverloaded);
			}
			if (ALoads[APlayerData[playerid][LoadID]][Mafia] == true)
			{
				format(RouteText, 255, "%s%s", RouteText, " ~r~(ML)~w~");
				GameTextForPlayer(playerid, TXT_MarinarMafiaInterested, 5000, 4);
				APlayerData[playerid][MafiaLoad] = true;
				if (APlayerData[playerid][TrailerID] == 0)
				    AVehicleData[APlayerData[playerid][VehicleID]][MafiaLoad] = true; // The player has no trailer, so set his main vehicle as wanted by the mafia
				else
                    AVehicleData[APlayerData[playerid][TrailerID]][MafiaLoad] = true; // The player has a trailer, so set his trailer as wanted by the mafia
			}
			TextDrawSetString(APlayerData[playerid][MissionText], RouteText);
			x = ALocations[APlayerData[playerid][JobLoc2]][LocX];
			y = ALocations[APlayerData[playerid][JobLoc2]][LocY];
			z = ALocations[APlayerData[playerid][JobLoc2]][LocZ];
			SetPlayerCheckpoint(playerid, x, y, z, 7);
			format(UnloadMsg, 100, TXT_D11, Load, EndLoc);
			SendClientMessage(playerid, 0xFFFFFFFF, UnloadMsg);
		}
		case 2:
		{
			new StartLoc[50], EndLoc[50], Load[50], Msg1[128], Msg2[128], Name[24], BonusMsg[128];
			GetPlayerName(playerid, Name, sizeof(Name));
			format(StartLoc, 50, ALocations[APlayerData[playerid][JobLoc1]][LocationName]);
			format(EndLoc, 50, ALocations[APlayerData[playerid][JobLoc2]][LocationName]);
			format(Load, 50, ALoads[APlayerData[playerid][LoadID]][LoadName]);
			format(Msg1, 128, TXT_PlayerCompletedMarinarJob, Name, Load);
			format(Msg2, 128, TXT_PlayerCompletedMarinarJobInfo, StartLoc, EndLoc);
			SendClientMessageToAll(0xFFFFFFFF, Msg1);
			SendClientMessageToAll(0xFFFFFFFF, Msg2);
			new Float:x1, Float:y1, Float:x2, Float:y2, Float:Distance, Message[128], Payment, Bonus;
			x1 = ALocations[APlayerData[playerid][JobLoc1]][LocX];
			y1 = ALocations[APlayerData[playerid][JobLoc1]][LocY];
			x2 = ALocations[APlayerData[playerid][JobLoc2]][LocX];
			y2 = ALocations[APlayerData[playerid][JobLoc2]][LocY];
			Distance = floatsqroot(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));
			Payment = floatround((Distance * ALoads[APlayerData[playerid][LoadID]][PayPerUnit]), floatround_floor);
			if (RandomBonusMission[MissionFinished] == false)
			{
				// Check all paramters (load, startlocation and end-location)
				if (RandomBonusMission[RandomLoad] == APlayerData[playerid][LoadID])
					if (RandomBonusMission[RandomStartLoc] == APlayerData[playerid][JobLoc1])
						if (RandomBonusMission[RandomEndLoc] == APlayerData[playerid][JobLoc2])
						{
						    Payment = Payment * 2;
                            RandomBonusMission[MissionFinished] = true;
							format(BonusMsg, 128, "{80FF00}[BONUS] {E6D11A}Marinarul %s A terminat Misiunea Bonus", Name);
							SendClientMessageToAll(0xFFFFFFFF, BonusMsg);
						}
			}
			RewardPlayer(playerid, Payment, 0);
			format(Message, 128, TXT_RewardJob, Payment);
			SendClientMessage(playerid, 0xFFFFFFFF, Message);
			if (APlayerData[playerid][Overloaded] == true)
			{
			    Bonus = (Payment * 25) / 100;
				RewardPlayer(playerid, Bonus, 0);
				format(Message, 128, TXT_MarinarBonusOverloaded, Bonus);
				SendClientMessage(playerid, 0xFFFFFFFF, Message);
			}
			if (APlayerData[playerid][MafiaLoad] == true)
			{
			    Bonus = (Payment * 50) / 100;
				RewardPlayer(playerid, Bonus, 0);
				format(Message, 128, TXT_MarinarBonusMafiaLoad, Bonus);
				SendClientMessage(playerid, 0xFFFFFFFF, Message);
			}
			if (AVehicleData[APlayerData[playerid][VehicleID]][Owned] == true)
			{
			    Bonus = (Payment * 20) / 100;
				RewardPlayer(playerid, Bonus, 0);
				format(Message, 128, TXT_MarinarBonusOwnVehicle, Bonus);
				SendClientMessage(playerid, 0xFFFFFFFF, Message);
			}
			if (Distance > 3000.0)
				RewardPlayer(playerid, 0, 4);
			else
				RewardPlayer(playerid, 0, 1); 
			APlayerData[playerid][StatsMarinarJobs]++;
			PlayerFile_Save(playerid);
			Marinar_EndJob(playerid);
		}
	}
	TogglePlayerControllable(playerid, 1);
	return 1;
}
Marinar_SetRandomOverloaded(playerid)
{
	new Name[24], Msg[128];
	switch (GetVehicleModel(GetPlayerVehicleID(playerid)))
	{
		case VehicleCementTruck: return 0; // A cementtruck cannot be overloaded
		case VehicleLineRunner, VehicleTanker, VehicleRoadTrain: // When driving a LineRunner, Tanker or RoadTrain
		{
			if (GetVehicleModel(GetVehicleTrailer(GetPlayerVehicleID(playerid))) == VehicleTrailerFluids) return 0;
		}
	}
	if (random(100) <= 35)
	{
	    APlayerData[playerid][Overloaded] = true;
	    SetPlayerWantedLevel(playerid, GetPlayerWantedLevel(playerid) + 2);
		GetPlayerName(playerid, Name, sizeof(Name));
		format(Msg, 128, "{00FF00}Marinalul {FFFF00}%s{00FF00} A incarcat Peste limita legala Urmarester si Amedeazal", Name);
		Police_SendMessage(Msg);
	}
	return 1;
}
Marinar_StartRandomJob(playerid)
{
	if (Marinar_SetRandomJob(playerid) != 0)
	{
		new StartLoc[50], EndLoc[50], Load[50], RouteText[255], Float:x, Float:y, Float:z, LoadMsg[128];
		APlayerData[playerid][JobStarted] = true;
		APlayerData[playerid][JobStep] = 1;
		format(StartLoc, 50, ALocations[APlayerData[playerid][JobLoc1]][LocationName]);
		format(EndLoc, 50, ALocations[APlayerData[playerid][JobLoc2]][LocationName]);
		format(Load, 50, ALoads[APlayerData[playerid][LoadID]][LoadName]);
		format(RouteText, 255, TXT_T11, Load, StartLoc, EndLoc);
		TextDrawSetString(APlayerData[playerid][MissionText], RouteText);
		x = ALocations[APlayerData[playerid][JobLoc1]][LocX];
		y = ALocations[APlayerData[playerid][JobLoc1]][LocY];
		z = ALocations[APlayerData[playerid][JobLoc1]][LocZ];
		SetPlayerCheckpoint(playerid, x, y, z, 7);
		APlayerData[playerid][VehicleTimerTime] = Job_TimeToFailMission;
		format(LoadMsg, 128, TXT_P11, Load, StartLoc);
		SendClientMessage(playerid, 0xFFFFFFFF, LoadMsg);
	}
	return 1;
}
Marinar_SetRandomJob(playerid)
{
	if (GetPlayerVehicleSeat(playerid) == 0)
	{
		switch (GetVehicleModel(GetPlayerVehicleID(playerid)))
		{
			case VehicleReefer, VehicleDinghy:
				return Marinar_SetRandomJobData(playerid, PCV_MarinarBoat);
			case VehicleCementTruck:
				return Marinar_SetRandomJobData(playerid, PCV_MarinarBoat);
			case VehicleLineRunner, VehicleTanker, VehicleRoadTrain:
			{
				// Select a job based on the trailer model of the player
				switch (GetVehicleModel(GetVehicleTrailer(GetPlayerVehicleID(playerid))))
				{
					case VehicleTrailerCargo, VehicleTrailerCargo2: 
						return Marinar_SetRandomJobData(playerid, PCV_MarinarBoat);
					case VehicleTrailerOre:
						return Marinar_SetRandomJobData(playerid, PCV_MarinarBoat);
					case VehicleTrailerFluids:
						return Marinar_SetRandomJobData(playerid, PCV_MarinarBoat);
				}
			}
		}
	}
	return 0;
}
Marinar_SetRandomJobData(playerid, PCV_Needed)
{
    APlayerData[playerid][LoadID] = Product_GetRandom(PCV_Needed);
    APlayerData[playerid][JobLoc1] = Product_GetRandomStartLoc(APlayerData[playerid][LoadID]);
    APlayerData[playerid][JobLoc2] = Product_GetRandomEndLoc(APlayerData[playerid][LoadID]);
	APlayerData[playerid][VehicleID] = GetPlayerVehicleID(playerid);
	APlayerData[playerid][TrailerID] = GetVehicleTrailer(GetPlayerVehicleID(playerid));
	return 1;
}
Marinar_EndJob(playerid)
{
	if (APlayerData[playerid][JobStarted] == true)
	{
		if (APlayerData[playerid][TrailerID] == 0)
		    AVehicleData[APlayerData[playerid][VehicleID]][MafiaLoad] = false; 
		else
			AVehicleData[APlayerData[playerid][TrailerID]][MafiaLoad] = false;
		APlayerData[playerid][JobStarted] = false;
		APlayerData[playerid][JobStep] = 0;
		APlayerData[playerid][JobID] = 0;
		APlayerData[playerid][VehicleTimerTime] = 0;
		APlayerData[playerid][VehicleID] = 0;
		APlayerData[playerid][TrailerID] = 0;
		APlayerData[playerid][LoadID] = 0;
		APlayerData[playerid][JobLoc1] = 0;
		APlayerData[playerid][JobLoc2] = 0;
		APlayerData[playerid][MafiaLoad] = false;

		DisablePlayerCheckpoint(playerid);
		TextDrawSetString(APlayerData[playerid][MissionText], Marinar_NoJobText);
		KillTimer(APlayerData[playerid][LoadingTimer]);
		if (APlayerData[playerid][Overloaded] == true)
		{
			// Clear the overloaded status of the player
		    APlayerData[playerid][Overloaded] = false;

		    // Check if the player has a wanted level of 2 or higher
			if (GetPlayerWantedLevel(playerid) >= 2)
				SetPlayerWantedLevel(playerid, GetPlayerWantedLevel(playerid) - 2); //
			else
				SetPlayerWantedLevel(playerid, 0); //
		}
	}
	return 1;
}