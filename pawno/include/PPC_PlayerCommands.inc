// This commands allows the player to send a private message to another player

COMMAND:pm(playerid, params[])

{

	// Setup local variables

	new OtherPlayer, Message[128], Msg1[128], Msg2[128], YourName[24], OtherPlayerName[24];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/pm", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		if (sscanf(params, "us[128]", OtherPlayer, Message)) SendClientMessage(playerid, 0xFF0000AA, "[RLT]: \"/pm <ID/Nume Jucator> <Mesaj>\"");

		else

		{

			// Check if that other player is online

			if (IsPlayerConnected(OtherPlayer))

			{

			    // Check if the player isn't muted

			    if (APlayerData[playerid][Muted] == false)

			    {

				    // Get both names

					GetPlayerName(playerid, YourName, sizeof(YourName));

					GetPlayerName(OtherPlayer, OtherPlayerName, sizeof(OtherPlayerName));

				    // Construct the message that is sent to yourself

					format(Msg1, 128, "{808080}I-ai transmis lui %s{FFFFFF}: %s", OtherPlayerName, Message);

					// Construct the message that is sent to the other player

					format(Msg2, 128, "%s{FFFFFF} ti-a transmis: %s", YourName, Message);

					// Send the messages

					SendClientMessage(playerid, 0xFFFFFFFF, Msg1);

					SendClientMessage(OtherPlayer, 0xFFFFFFFF, Msg2);

				}

				else

				    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}Ai mute");

			}

			else

			    SendClientMessage(playerid, 0xFF0000FF, "Jucatorul nu este Online");

		}

	}

	else

	 return 0;



	// Let the server know that this was a valid command

	return 1;
}

CMD:vsay(playerid, params[])

{
    if (APlayerData[playerid][VPlayerLevel] < 1) return SendClientMessage(playerid, 0xFF0000FF, "Nu esti vip !");

    new sendername[MAX_PLAYER_NAME], string[120];

    GetPlayerName(playerid, sendername, sizeof(sendername));

    if(isnull(params)) return SendClientMessage(playerid, 0xFFFFFFF,"[RLT]: /vsay [text]");

    format(string, sizeof(string), "{ff0000}[{00ff00}Anunt{ffffff}] {ff0000}VIP {00ff00}%s: {0099ff}%s ", sendername, params);

	if (APlayerData[playerid][Muted] == false)

    SendClientMessageToAll(0xFFB300C8, string);

    return 1;

}

CMD:contact(playerid, params[])

{
	    if(IsPlayerConnected(playerid))
	    {
            SendClientMessage(playerid, 0x33CCFFAA,"___________________________________________");
			SendClientMessage(playerid, 0x33CCFFAA,"{FFFFFF}Contact fondator(i) / scripter(i) (ID Skype)");
			SendClientMessage(playerid, 0x33CCFFAA,"{FFFFFF}Skype{ff0000} Fondator si Scripter: Lucian50 (lucian_nk)");
			SendClientMessage(playerid, 0x33CCFFAA,"{ffffff}Skype{00ff00} Fondator: sdk (igor.goit)");
			SendClientMessage(playerid, 0x33CCFFAA,"{ffffff}Skype{00ff00} Owner: -");
			SendClientMessage(playerid, 0x33CCFFAA,"___________________________________________");
		}
		return 1;
}

CMD:credits(playerid, params[])

{
	    if(IsPlayerConnected(playerid))
	    {
            SendClientMessage(playerid, 0x33CCFFAA,"___________________________________________");
			SendClientMessage(playerid, 0x33CCFFAA,"{FFFFFF}Lista fondator(i) / scripter(i)");
			SendClientMessage(playerid, 0x33CCFFAA,"{FFFFFF}Fondator si scripter:{00ff00} Lucian50");
			SendClientMessage(playerid, 0x33CCFFAA,"{ffffff}Fondator:{00ff00} sdk");
			SendClientMessage(playerid, 0x33CCFFAA,"{ffffff}Owner:{00ff00} -");
			SendClientMessage(playerid, 0x33CCFFAA,"___________________________________________");
		}
		return 1;
}

CMD:vc(playerid, params[])

{
    if (APlayerData[playerid][VPlayerLevel] < 1) return SendClientMessage(playerid, 0xFF0000FF, "Nu esti vip !");

    new sendername[MAX_PLAYER_NAME], string[120];

    GetPlayerName(playerid, sendername, sizeof(sendername));

    if(isnull(params)) return SendClientMessage(playerid, 0xFFFFFFF,"[RLT]: /vc [text]");

    format(string, sizeof(string), "{ff0000}[VIP] {00ff00}%s: {0099ff}%s ", sendername, params);

	if (APlayerData[playerid][Muted] == false)

    SendClientMessageToAll(0xFFB300C8, string);

    return 1;

}

COMMAND:rangeban(playerid, params[])

{

	// Setup local variables

	new PlayerToBan, PlayerIP[16], FirstPartsOfIP[16], BanCmd[24], Reason[128], Msg[128], Name[24], AdminName[24];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/rangeban", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 3

		if (APlayerData[playerid][PlayerLevel] >= 3)

		{

			if (sscanf(params, "us[128]", PlayerToBan, Reason))

				SendClientMessage(playerid, 0xFF0000AA, "[RLT]: \"/rangeban <ID/Nume Jucator> <Motiv>\"");

			else

			{

				if (IsPlayerConnected(PlayerToBan))

				{

					// Get the names of the player and the admin who executed the ban

					GetPlayerName(playerid, AdminName, sizeof(AdminName));

					GetPlayerName(PlayerToBan, Name, sizeof(Name));



					// Get the player's IP-address

					GetPlayerIp(PlayerToBan, PlayerIP, 16);



					// Inform the player about his ban

					format(Msg, 128, "{FF0000}Ai fost ip-range banat permanent de catre {FFFF00}%s", AdminName);

					SendClientMessage(PlayerToBan, 0xFFFFFFFF, Msg);

					format(Msg, 128, "{FF0000}Motivul: {FFFF00}%s", Reason);

					SendClientMessage(PlayerToBan, 0xFFFFFFFF, Msg);



					// Get the first three digits from the player's ip, so the fourth part can be added from 0 to 255

					FirstPartsOfIP = GetFirstThreeDigitsFromIP(PlayerIP);

					// Ban the entire range of IP-addresses of the player

					for (new i; i < 256; i++)

					{

					    format(BanCmd, 24, "banip %s%i", FirstPartsOfIP, i); // Construct the RCon command to ban every IP

                        SendRconCommand(BanCmd); // Execute the command

					}

					// Finally kick the player (the RCon command doesn't kick you out automatically)

					Kick(PlayerToBan);



					// Inform everybody else which player was ip-range-banned

					format(Msg, 128, "{808080}%s %s i-a dat ip-range ban lui{FFFF00}%s", AdminLevelName[APlayerData[playerid][PlayerLevel]], AdminName, Name);

					SendClientMessageToAll(0xFFFFFFFF, Msg);

				}

			}

		}

		else

		    return 0;

	}

	else

	    return 0;



	return 1;

}

// Lets the player add new houses

COMMAND:createhouse(playerid, params[])

{

	// Setup local variables

	new HPrice, MaxLevel, HouseID;



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/createhouse", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 7

		if (APlayerData[playerid][PlayerLevel] >= 7)

		{

			// Check if the player isn't inside a vehicle

			if (GetPlayerVehicleSeat(playerid) == -1)

			{

				if (sscanf(params, "ii", HPrice, MaxLevel)) SendClientMessage(playerid, 0xFF0000AA, "[RLT]: \"/createhouse <Pret> <Level Maxim (1-10)>\"");

				else

				{

					// Check if the player entered a proper maxlevel

					if ((MaxLevel >= 1) && (MaxLevel <= 10))

					{

						// Find the first free HouseID

						for (HouseID = 1; HouseID < MAX_HOUSES; HouseID++)

							if (AHouseData[HouseID][PickupID] == 0) // Check if an empty house-index has been found (PickupID is 0)

							    break; // Stop searching, the first free HouseID has been found now



					    // Check if the house-limit hasn't been reached yet

						if (HouseID < MAX_HOUSES)

						{

						    // Setup some local variables

							new Float:x, Float:y, Float:z, Msg[128];

							// Get the player's position

							GetPlayerPos(playerid, x, y, z);

							// Set some default data

							AHouseData[HouseID][HouseX] = x;

							AHouseData[HouseID][HouseY] = y;

							AHouseData[HouseID][HouseZ] = z;

							AHouseData[HouseID][HouseLevel] = 1;

							AHouseData[HouseID][HouseMaxLevel] = MaxLevel;

							AHouseData[HouseID][HousePrice] = HPrice;

							AHouseData[HouseID][Owned] = false;



							// Add the pickup and 3DText at the location of the house-entrance (where the player is standing when he creates the house)

							House_CreateEntrance(HouseID);



							// Save the house

							HouseFile_Save(HouseID);



							// Inform the player that he created a new house

							format(Msg, 128, "{00FF00}Ai creeat casa cu id {FF00FF}%i{00FF00}", HouseID);

							SendClientMessage(playerid, 0xFFFFFFFF, Msg);

						}

						else

						    SendClientMessage(playerid, 0xFF0000FF, "Numarul maxim de case a fost atins");

					}

					else

					    SendClientMessage(playerid, 0xFF0000FF, "Nivelul casei poate fi cuprins intre 1 si 10");

				}

			}

			else

			    SendClientMessage(playerid, 0xFF0000FF, "Nu poti creea o casa din masina");

		}

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}

// This command lets the player delete a house

COMMAND:delhouse(playerid, params[])

{

	// Setup local variables

	new file[100], Msg[128];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/delhouse", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least

		if (APlayerData[playerid][PlayerLevel] >= 7)

		{

			// Make sure the player isn't inside a vehicle

			if (GetPlayerVehicleID(playerid) == 0)

			{

				// Loop through all player-owned houses

				for (new HouseID = 1; HouseID < MAX_HOUSES; HouseID++)

				{

					// Check if the house exists

					if (AHouseData[HouseID][PickupID] != 0)

					{

						// Check if the house has no owner

						if (AHouseData[HouseID][Owned] == false)

						{

							// Check if the player is in range of the house-pickup

							if (IsPlayerInRangeOfPoint(playerid, 2.5, AHouseData[HouseID][HouseX], AHouseData[HouseID][HouseY], AHouseData[HouseID][HouseZ]))

							{

								// Clear all data of the house

	                            AHouseData[HouseID][HouseName] = 0;

	                            AHouseData[HouseID][Insurance] = 0;

	                            AHouseData[HouseID][HouseX] = 0.0;

	                            AHouseData[HouseID][HouseY] = 0.0;

	                            AHouseData[HouseID][HouseZ] = 0.0;

	                            AHouseData[HouseID][HouseLevel] = 0;

	                            AHouseData[HouseID][HouseMaxLevel] = 0;

	                            AHouseData[HouseID][HousePrice] = 0;

	                            AHouseData[HouseID][Owned] = false;

	                            AHouseData[HouseID][Owner] = 0;

	                            AHouseData[HouseID][HouseName] = 0;

	                            AHouseData[HouseID][HouseName] = 0;

	                            AHouseData[HouseID][HouseName] = 0;

								// Destroy the mapicon, 3DText and pickup for the house

								DestroyDynamicPickup(AHouseData[HouseID][PickupID]);

								DestroyDynamicMapIcon(AHouseData[HouseID][MapIconID]);

								DestroyDynamic3DTextLabel(AHouseData[HouseID][DoorText]);

	                            AHouseData[HouseID][PickupID] = 0;

	                            AHouseData[HouseID][MapIconID] = 0;



								// Delete the House-file

								format(file, sizeof(file), HouseFile, HouseID); // Construct the complete filename for this house-file

								if (fexist(file)) // Make sure the file exists

									fremove(file); // Delete the file



								// Also let the player know he deleted the house

								format(Msg, 128, "{00FF00}Ai sters casa cu id {FFFF00}%i", HouseID);

								SendClientMessage(playerid, 0xFFFFFFFF, Msg);



								// Exit the function

								return 1;

							}

						}

					}

				}



				// There was no house in range, so let the player know about it

				SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}Nici o casa prin preajma pentru a o sterge");

			}

			else

			    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}Nu poti sterge case din masina");

		}

		else

		    return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// This command lets the player buy a house when he's standing in range of a house that isn't owned yet

COMMAND:buyhouse(playerid, params[])

{

	// Setup local variables

	new Msg[128];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/buyhouse", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Make sure the player isn't inside a vehicle

		if (GetPlayerVehicleID(playerid) == 0)

		{

			// Check if the player is near a house-pickup

			for (new i = 1; i < sizeof(AHouseData); i++)

			{

				// Check if this house is created (it would have a valid pickup in front of the door)

				if (AHouseData[i][PickupID] != 0)

				{

					// Check if the player is in range of the house-pickup

					if (IsPlayerInRangeOfPoint(playerid, 2.5, AHouseData[i][HouseX], AHouseData[i][HouseY], AHouseData[i][HouseZ]))

					{

					    // Check if the house isn't owned yet

					    if (AHouseData[i][Owned] == false)

					    {

					        // Check if the player can afford this house

					        if (APlayerData[playerid][PlayerMoney] >= AHouseData[i][HousePrice])

					            House_SetOwner(playerid, i); // Give ownership of the house to the player

					        else

					            SendClientMessage(playerid, 0xFF0000FF, "Nu poti cumpara aceasta casa"); // The player cannot afford this house

					    }

					    else

					    {

					        // Let the player know that this house is already owned by a player

							format(Msg, 128, "{FF0000}Aceasta casa este a jucatorului {00FF00}%s{FFFFFF}", AHouseData[i][Owner]);

							SendClientMessage(playerid, 0xFFFFFFFF, Msg);

					    }



						// The player was in range of a house-pickup, so stop searching for the other house pickups

					    return 1;

					}

				}

			}



			// All houses have been processed, but the player wasn't in range of any house-pickup, let him know about it

			SendClientMessage(playerid, 0xFF0000FF, "Pentru a cumpara o casa, trebuie sa fii langa o casa");

		}

		else

		    SendClientMessage(playerid, 0xFF0000FF, "Nu poti cumpara o casa din masina");

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// This command lets the player enter the house/business if he's the owner

COMMAND:enter(playerid, params[])

{

	// Setup local variables

	new HouseID, hLevel, BusID, BusType;



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/enter", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Make sure the player isn't inside a vehicle

		if (GetPlayerVehicleID(playerid) == 0)

		{

			// Loop through all houses

			for (HouseID = 1; HouseID < MAX_HOUSES; HouseID++)

			{

				// Check if this house exists

				if (AHouseData[HouseID][PickupID] != 0)

				{

					// Check if the player is in range of the house-pickup

					if (IsPlayerInRangeOfPoint(playerid, 2.5, AHouseData[HouseID][HouseX], AHouseData[HouseID][HouseY], AHouseData[HouseID][HouseZ]))

					{

						// Check if the house is closed to the public

						if (AHouseData[HouseID][HouseOpened] == false)

						{

							// The house isn't open to the public, so keep anyone out who isn't the owner of the house

							if (House_PlayerIsOwner(playerid, HouseID) == 0)

							{

							    // Let the player know that this house isn't open to the public and he can't enter it

								SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}Aceasta casa nu este deschisa public, nu poti intra in ea");

							    return 1;

							}

						}



						// The house is open to the public, or the player trying to enter is the owner, so let the player inside the house



					    // Get the level of the house

						hLevel = AHouseData[HouseID][HouseLevel];

						// Set the worldid so other players cannot see him anymore

						SetPlayerVirtualWorld(playerid, 5000 + HouseID);

						// Set the player inside the interior of the house

						SetPlayerInterior(playerid, AHouseInteriors[hLevel][InteriorID]);

						// Set the position of the player at the spawn-location of the house's interior

						SetPlayerPos(playerid, AHouseInteriors[hLevel][IntX], AHouseInteriors[hLevel][IntY], AHouseInteriors[hLevel][IntZ]);

						// Also set a tracking-variable to enable /housemenu to track in which house the player is

						APlayerData[playerid][CurrentHouse] = HouseID;

						// Also let the player know he can use /housemenu to upgrade/exit his house

						SendClientMessage(playerid, 0xFFFFFFFF, "{00FF00}Foloseste {FFFF00}/housemenu{00FF00} pentru a vedea optiunile casei");



						// Exit the function

						return 1;

					}

				}

			}



			// Loop through all player-owned businesses

			for (new i; i < MAX_BUSINESSPERPLAYER; i++)

			{

			    // Get the business-id at the selected slot from the player

			    BusID = APlayerData[playerid][Business][i];



				// Check if the player has owned a business in this slot

				if (BusID != 0)

				{

					// Check if the player is in range of the business-pickup

					if (IsPlayerInRangeOfPoint(playerid, 2.5, ABusinessData[BusID][BusinessX], ABusinessData[BusID][BusinessY], ABusinessData[BusID][BusinessZ]))

					{

					    // Get the business-type

					    BusType = ABusinessData[BusID][BusinessType];

						// Set the worldid so other players cannot see him anymore

						SetPlayerVirtualWorld(playerid, 1000 + playerid);

						// Set the player inside the interior of the business

						SetPlayerInterior(playerid, ABusinessInteriors[BusType][InteriorID]);



						// Set the position of the player at the spawn-location of the business's interior

						SetPlayerPos(playerid, ABusinessInteriors[BusType][IntX], ABusinessInteriors[BusType][IntY], ABusinessInteriors[BusType][IntZ]);

						// Also set a tracking-variable to enable /busmenu to track in which business the player is

						APlayerData[playerid][CurrentBusiness] = BusID;

						// Also let the player know he can use /busmenu to upgrade/exit his business

						SendClientMessage(playerid, 0xFFFFFFFF, "{00FF00}Foloseste {FFFF00}/busmenu{00FF00} pentru a vedea optiunile business-ului");



						// Exit the function

						return 1;

					}

				}

			}

		}

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// This command opens a menu when you're inside your house to allow to access the options of your house

COMMAND:housemenu(playerid, params[])

{

	// Setup local variables

	new OptionsList[200], DialogTitle[200];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/housemenu", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player is inside a house

		if (APlayerData[playerid][CurrentHouse] != 0)

		{

			format(DialogTitle, sizeof(DialogTitle), "Selecteaza optiunea pentru %s", AHouseData[APlayerData[playerid][CurrentHouse]][HouseName]);



			format(OptionsList, sizeof(OptionsList), "%sScimba Numele Casei\n", OptionsList);

			format(OptionsList, sizeof(OptionsList), "%sModernizeaza casa\n", OptionsList);

			format(OptionsList, sizeof(OptionsList), "%sCumpara vehicul\n", OptionsList);

			format(OptionsList, sizeof(OptionsList), "%sCumpara Assigurare\n", OptionsList);

			format(OptionsList, sizeof(OptionsList), "%sVinde vehicul\n", OptionsList);

			format(OptionsList, sizeof(OptionsList), "%sVinde Casa\n", OptionsList);

			format(OptionsList, sizeof(OptionsList), "%sDeschide casa\n", OptionsList);

			format(OptionsList, sizeof(OptionsList), "%sInchide casa\n", OptionsList);

			format(OptionsList, sizeof(OptionsList), "%sIesire\n", OptionsList);

			// Show the housemenu

			ShowPlayerDialog(playerid, DialogHouseMenu, DIALOG_STYLE_LIST, DialogTitle, OptionsList, "Select", "Anulare");

		}

		else

		    SendClientMessage(playerid, 0xFF0000FF, "Nu esti in casa");

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}







// This command allows you to port a vehicle from your house to your location

COMMAND:getcar(playerid, params[])

{

	// Setup local variables

	new HouseList[1000];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/getcar", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player is not jailed

		if (APlayerData[playerid][PlayerJailed] == 0)

		{

			// Check if the player is not inside a vehicle

			if (GetPlayerVehicleID(playerid) == 0)

			{

				// Ask to which house the player wants to add his vehicle

				for (new i; i < MAX_HOUSESPERPLAYER; i++)

				{

					// Check if this houseindex is occupied

					if (APlayerData[playerid][Houses][i] != 0)

						format(HouseList, 1000, "%s{00FF00}%s{FFFFFF}\n", HouseList, AHouseData[APlayerData[playerid][Houses][i]][HouseName]);

					else

						format(HouseList, 1000, "%s{FFFFFF}%s{FFFFFF}\n", HouseList, "Acest slot nu detine nici o masina");

				}

				ShowPlayerDialog(playerid, DialogGetCarSelectHouse, DIALOG_STYLE_LIST, "Alege casa din care sa-ti aduci masina:", HouseList, "Select", "Anulare");

			}

			else

				SendClientMessage(playerid, 0xFF0000FF, "Nu poti aduce masina casei la tine in timp ce esti in alta masina");

		}

		else

		    SendClientMessage(playerid, 0xFF0000FF, "Nu poti folosi /getcar in timp ce esti arestat");

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// This command checks if the player is inside a vehicle that he owns and if he's in range of the house where the vehicle is assigned to

COMMAND:park(playerid, params[])

{

	// Setup local variables

	new Float:x, Float:y, Float:z, Float:rot, vid, HouseID, Msg[128];

	new engine,lights,alarm,doors,bonnet,boot,objective;



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/park", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player is inside a vehicle (he must be the driver)

		if (GetPlayerVehicleSeat(playerid) == 0)

		{

			// Get the vehicle-id

			vid = GetPlayerVehicleID(playerid);

			// Get the HouseID to which this vehicle belongs

			HouseID = AVehicleData[vid][BelongsToHouse];



			// Check if the vehicle is owned (owner-check is not really required, as another player would get kicked out very fast)

			// AND it must belong to a house that the player owns

			if ((AVehicleData[vid][Owned] == true) && (HouseID != 0))

			{

				// Check if the vehicle is in range of the house-entrance (you cannot park a vehicle further away from your house than 150m)

				if (IsPlayerInRangeOfPoint(playerid, ParkRange, AHouseData[HouseID][HouseX], AHouseData[HouseID][HouseY], AHouseData[HouseID][HouseZ]))

				{

					// Get the player's position and angle

					GetVehiclePos(vid, x, y, z);

					GetVehicleZAngle(vid, rot);

					// Save those values for the vehicle

					AVehicleData[vid][SpawnX] = x;

					AVehicleData[vid][SpawnY] = y;

					AVehicleData[vid][SpawnZ] = z;

					AVehicleData[vid][SpawnRot] = rot;



					// Find the vehicle in the player's houses

					for (new i; i < MAX_HOUSESPERPLAYER; i++)

					{

						// Get the HouseID of the current house

					    HouseID = APlayerData[playerid][Houses][i];



						// Loop through all carslots of this house to find the vehicle-id

						for (new CarSlot; CarSlot < 10; CarSlot++)

						{

							// Check if this carslot holds the same vehicle-id

						    if (AHouseData[HouseID][VehicleIDs][CarSlot] == vid)

						    {

			                    House_ReplaceVehicle(HouseID, CarSlot); // Re-create the vehicle at the same spot the player wants to park his vehicle

			                    PutPlayerInVehicle(playerid, AHouseData[HouseID][VehicleIDs][CarSlot], 0);

								// Turn on the engine

								GetVehicleParamsEx(AHouseData[HouseID][VehicleIDs][CarSlot], engine, lights, alarm, doors, bonnet, boot, objective);

								SetVehicleParamsEx(AHouseData[HouseID][VehicleIDs][CarSlot], 1, lights, alarm, doors, bonnet, boot, objective);

			                    break; // Stop the for-loop

							}

						}

					}



					// Let the player know he parked his vehicle

					SendClientMessage(playerid, 0x00FF00FF, "Masina a fost parcata");



					// Save the player-file (and his houses)

					PlayerFile_Save(playerid);

				}

				else

				{

				    format(Msg, 128, "{FF0000}Trebuie sa fii in jurul a %im de casa pentru a parca masina", ParkRange);

				    SendClientMessage(playerid, 0xFFFFFFFF, Msg);

				}

			}

			else

			    SendClientMessage(playerid, 0xFF0000FF, "No poti parca masina atat timp cat tu nu esti proprietarul ei");

		}

		else

		    SendClientMessage(playerid, 0xFF0000FF, "Trebuie sa conduci propria masina pentru a o parca");

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}







// Lets the player rent a vehicle

COMMAND:rentcar(playerid, params[])

{

	// Setup local variables

	new VehicleClassList[1000];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/rentcar", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Make sure the player isn't inside a vehicle

		if (GetPlayerVehicleID(playerid) == 0)

		{

			// Check if the player is near a cardealerpickup

			for (new i; i < sizeof(ACarDealerPickups); i++)

			{

				// Check if a valid cardealerpickup is found

				if (ACarDealerPickups[i][PickupID] != 0)

				{

					// Check if the player is in range of the cardealerpickup

					if(IsPlayerInRangeOfPoint(playerid, 2.5, ACarDealerPickups[i][pux], ACarDealerPickups[i][puy], ACarDealerPickups[i][puz]))

					{

					    // Let the player choose a vehicle-class

						format(VehicleClassList, 1000, "%s{00FF00}%s{FFFFFF}\n", VehicleClassList, "Biciclete");

						format(VehicleClassList, 1000, "%s{40FF00}%s{FFFFFF}\n", VehicleClassList, "Barci");

						format(VehicleClassList, 1000, "%s{80FF00}%s{FFFFFF}\n", VehicleClassList, "Convertibles");

						format(VehicleClassList, 1000, "%s{B0FF00}%s{FFFFFF}\n", VehicleClassList, "Helicopters");

						format(VehicleClassList, 1000, "%s{FFFF00}%s{FFFFFF}\n", VehicleClassList, "Industrial vehicles");

						format(VehicleClassList, 1000, "%s{B0FF40}%s{FFFFFF}\n", VehicleClassList, "Low-riders");

						format(VehicleClassList, 1000, "%s{80FF80}%s{FFFFFF}\n", VehicleClassList, "Off-Road vehicles");

						format(VehicleClassList, 1000, "%s{40FFB0}%s{FFFFFF}\n", VehicleClassList, "Avioane");

						format(VehicleClassList, 1000, "%s{00FFFF}%s{FFFFFF}\n", VehicleClassList, "Public Service vehicles");

						format(VehicleClassList, 1000, "%s{00B0FF}%s{FFFFFF}\n", VehicleClassList, "Vehicule RC");

						format(VehicleClassList, 1000, "%s{0080FF}%s{FFFFFF}\n", VehicleClassList, "Saloon vehicles");

						format(VehicleClassList, 1000, "%s{0040FF}%s{FFFFFF}\n", VehicleClassList, "Vehicule sport");

						format(VehicleClassList, 1000, "%s{0000FF}%s{FFFFFF}\n", VehicleClassList, "Station wagons");

						format(VehicleClassList, 1000, "%s{4000FF}%s{FFFFFF}\n", VehicleClassList, "Remorci");

						format(VehicleClassList, 1000, "%s{8000FF}%s{FFFFFF}\n", VehicleClassList, "Vehicule unice");

						// Ask which vehicle class the player wants to see to buy a vehicle

						ShowPlayerDialog(playerid, DialogRentCarClass, DIALOG_STYLE_LIST, "Selecteaza vehicul:", VehicleClassList, "Select", "Anulare");

						// Exit the function

						return 1;

					}

				}

			}



			// The player wasn't in range of a cardealer

			SendClientMessage(playerid, 0xFF0000FF, "Nu poti inchiria un vehicul atat timp cat nu esti langa cardealer");

		}

		else

		    SendClientMessage(playerid, 0xFF0000FF, "Nu poti inchiria un vehicul atat timp cat esti in alt vehicul");

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}

// This command teleports you to your selected house

COMMAND:gohome(playerid, params[])

{

	// Setup local variables

	new HouseList[1000];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/gohome", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		if (APlayerData[playerid][JobStarted] == true && APlayerData[playerid][VehicleTimerTime] != 0) {

			SendClientMessage(playerid, 0xFF0000FF, "Nu te poti teleporta la casa in timpul misiunii");

		}

		// Check if the player has a wanted level of less than 1

		if (GetPlayerWantedLevel(playerid) < 1)

		{

			// Check if the player is not jailed

			if (APlayerData[playerid][PlayerJailed] == 0)

			{

				// Check if the player is not inside a vehicle

				if (GetPlayerVehicleID(playerid) == 0)

				{

					// Ask to which house the player wants to add his vehicle

					for (new i; i < MAX_HOUSESPERPLAYER; i++)

					{

						// Check if this houseindex is occupied

						if (APlayerData[playerid][Houses][i] != 0)

							format(HouseList, 1000, "%s{00FF00}%s{FFFFFF}\n", HouseList, AHouseData[APlayerData[playerid][Houses][i]][HouseName]);

						else

							format(HouseList, 1000, "%s{FFFFFF}%s{FFFFFF}\n", HouseList, "Slotul nu detine nici o casa");

					}

					ShowPlayerDialog(playerid, DialogGoHome, DIALOG_STYLE_LIST, "Selecteaza casa la care vrei sa mergi:", HouseList, "Select", "Anulare");

				}

				else

					SendClientMessage(playerid, 0xFF0000FF, "Nu te poti teleporta la casa dintr-un vehicul");

			}

			else

			    SendClientMessage(playerid, 0xFF0000FF, "Nu poti folosi /gohome in jail");

		}

		else

			SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}Nu poti folosi /gohome in timp ce esti cautat de politie");

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}







// Gives the player the cash he requests

COMMAND:cash(playerid, params[])

{

	new Amount, Msg[128];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/cash", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		if (APlayerData[playerid][PlayerLevel] >= 5)

		{

			if (sscanf(params, "i", Amount)) SendClientMessage(playerid, 0xFF0000AA, "[RLT]: \"/cash <suma>\"");

			else

			{

				// Check if the player gave himself too much at once

				if (Amount > 100000000)

				{

				    // Inform the player and quit the command

					SendClientMessage(playerid, 0xFF0000AA, "Nu iti poti da mai mult de 100000000 ( 100kk )");

					return 1;

				}



				// Reward the player (give cash and points)

				RewardPlayer(playerid, Amount, 0);

				format(Msg, 128, "Ai Primit $%i", Amount);

				SendClientMessage(playerid, 0x00FF00AA, Msg);

			}

		}

		else

		    return 0;

	}

	else

	    return 0;



	return 1;

}

// Detaches the trailer from the vehicle

COMMAND:detach(playerid, params[])

{

	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/detach", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Detach the trailer from the vehicle

		DetachTrailerFromVehicle(GetPlayerVehicleID(playerid));

		// Send the player a message that the trailer has been detached

		SendClientMessage(playerid, 0x0000FFFF, "Remorca a fost detasata de camion");

	}

	else

		return 0;



	// Let the server know that this was a valid command

	return 1;

}



// Puts the player's vehicle back onto his wheels

COMMAND:flip(playerid, params[])

{

	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/flip", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Setup some local variables

		new Float:x = 0.0, Float:y = 0.0, Float:z = 2.0;

		// Check if the player is inside a vehicle

		if(IsPlayerInAnyVehicle(playerid))

			SetCameraBehindPlayer(playerid);

		// Get the player's position

		GetPlayerPos(playerid, x, y, z);

		// Set the vehicle on the player's coordinates

		SetVehiclePos(GetPlayerVehicleID(playerid), x, y, z);

		// Let the vehicle point north

		SetVehicleZAngle(GetPlayerVehicleID(playerid), 0.0);

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// Repairs the player's vehicle

COMMAND:repair(playerid, params[])

{

	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/repair", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 1

		if (APlayerData[playerid][PlayerLevel] >= 1)

		{

		    // Check if the player is inside a vehicle

			if(!IsPlayerInAnyVehicle(playerid))

				return SendClientMessage(playerid, 0xFF0000FF, "Nu esti intr-un vehicul"); // Let the player know he's not inside a vehicle and let the server know that this was a valid command

			// Fully repair the vehicle (damage value and bodywork)

			RepairVehicle(GetPlayerVehicleID(playerid));

			// Send the player a message to inform him that his vehicle has been repaired

			SendClientMessage(playerid, 0x00FF00FF, "Vehiculul a fost reparat");

		}

		else

		    return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// Repairs all vehicles

COMMAND:repairall(playerid, params[])

{

	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/repairall", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 3

		if (APlayerData[playerid][PlayerLevel] >= 3)

		{

			// Loop through all vehicles

			for (new i; i < 2000; i++)

				RepairVehicle(i); // Fully repair the vehicle (damage value and bodywork)



			// Send all players a message to inform them that all vehicles have been repaired

			SendClientMessageToAll(0x00FFFFC8, "[RLT]{80FF00}Toate Masinile au fost Reparate!");

		}

		else

		    return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// Heals all players

COMMAND:healall(playerid, params[])

{

	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/healall", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 3

		if (APlayerData[playerid][PlayerLevel] >= 3)

		{

			// Loop through all players

			for (new i; i < MAX_PLAYERS; i++)

				if (IsPlayerConnected(i)) // Check if the player is connected

				        SetPlayerHealth(i, 100.0); // Heal the player



			// Send all players a message to inform them that all players have been healed

			SendClientMessageToAll(0x00FFFFC8, "[RLT]{80FF00}Toti jucatori au primit viata 100!");

		}

		else

		    return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}





// da la toti 1.000.000$

COMMAND:cadou(playerid, params[])

{

	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/cadou", params);

	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 7

		if (APlayerData[playerid][PlayerLevel] >= 7)

		{

			// Loop through all players

			for (new i; i < MAX_PLAYERS; i++)

				if (IsPlayerConnected(i)) // Check if the player is connected

						RewardPlayer(i, 1000000, 5);

			// Send all players a message to inform them that all players have been healed

			SendClientMessageToAll(0x00FFFFC8, "[RLT]:{80FF00}Toti jucatori au primit 1.000.000$ si 5 scor cadou!");

		}

		else

		    return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}

// da la toti 1.000.000$

COMMAND:megacadou(playerid, params[])

{

	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/megacadou", params);

	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 8

		if (APlayerData[playerid][PlayerLevel] >= 8)

		{

			// Loop through all players

			for (new i; i < MAX_PLAYERS; i++)

				if (IsPlayerConnected(i)) // Check if the player is connected

						RewardPlayer(i, 50000000, 50);

			// Send all players a message to inform them that all players have been healed

			SendClientMessageToAll(0x00FFFFC8, "[RLT]:{80FF00}Toti jucatori online au primit 50.000.000$ si 50 scor cadou!");

		}

		else

		    return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}

// Kills the player

COMMAND:kill(playerid, params[])

{

	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/kill", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player has a wanted level of less than 3

		if (GetPlayerWantedLevel(playerid) < 5)

		{

			// Check if the player isn't in jail

			if (APlayerData[playerid][PlayerJailed] == 0)

			{

			    // Force the player back into class-selection

				ForceClassSelection(playerid);

				// Kill the player (required after ForceClassSelection)

				SetPlayerHealth(playerid, 0.0);

			}

			else

			    SendClientMessage(playerid, 0xFF0000FF, "Nu poti folosi /kill in inchisoare");

		}

		else

		    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}Nu poti folosi /kill daca esti cautat de politie");

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// Lets the player choose another class

COMMAND:reclass(playerid, params[])

{

	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/reclass", params);

	if (GetPlayerState(playerid) == PLAYER_STATE_WASTED || GetPlayerState(playerid) == PLAYER_STATE_NONE)

        return 0;



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player has a wanted level of less than 3

		if (GetPlayerWantedLevel(playerid) < 5)

		{

			// Check if the player isn't in jail

			if (APlayerData[playerid][PlayerJailed] == 0)

			{

			    // Force the player back into class-selection

				ForceClassSelection(playerid);

				// Kill the player (required after ForceClassSelection)

				SetPlayerHealth(playerid, 0.0);

			}

			else

			    SendClientMessage(playerid, 0xFF0000FF, "Nu poti folosi /reclass in inchisoare");

		}

		else

		    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}Nu poti folosi /reclass in timp ce esti cautat de politie");

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// Starts a job

COMMAND:work(playerid, params[])

{

	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/work", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// First check if the player already has a job

		if (APlayerData[playerid][JobStarted] == false)

		{

		    // Check the player's class

			switch (APlayerData[playerid][PlayerClass])

			{

				case ClassTruckDriver:

				{

					// Get the id of the convoy (if the player is in a convoy)

					new Convoy = APlayerData[playerid][ConvoyID];



					// Check if the player is part of a convoy AND is not the leader

					if ((APlayerData[playerid][InConvoy] == true) && (AConvoys[Convoy][Members][0] != playerid))

					{

						// Let the player know he's not the leader of his convoy and cannot start a job

						SendClientMessage(playerid, 0xFF0000FF, "Nu esti liderul convoyului, nu poti da startul");

						// Exit the function

						return 1;

					}



					// A convoy-leader proceeds here, and also a normal player (no convoy-member)



					// Check if the player is the driver of a vehicle

					if (GetPlayerVehicleSeat(playerid) == 0)

					{

						// Check if the player is inside a valid trucking vehicle

						switch (GetVehicleModel(GetPlayerVehicleID(playerid)))

						{

							case VehicleFlatbed, VehicleDFT30, VehicleCementTruck, VehicleSecuricar: // Flatbed, DFT-30, CementTruck

								if (APlayerData[playerid][TruckerLicense] == 1) // Check if the player has acquired a truckers license

									ShowPlayerDialog(playerid, DialogTruckerJobMethod, DIALOG_STYLE_LIST, "Select method:", "Setup your own load and route\r\nAuto assigned load", "Select", "Anulare");

								else

								    Trucker_StartRandomJob(playerid); // Start a random job



							case VehicleLineRunner, VehicleTanker, VehicleRoadTrain: // Player is driving a truck which needs a trailer

								if(IsTrailerAttachedToVehicle(GetPlayerVehicleID(playerid))) // Check if there is a trailer attached

									if (APlayerData[playerid][TruckerLicense] == 1) // Check if the player has acquired a truckers license

										ShowPlayerDialog(playerid, DialogTruckerJobMethod, DIALOG_STYLE_LIST, "Select method:", "Setup your own load and route\r\nAuto assigned load", "Select", "Anulare");

									else

									    Trucker_StartRandomJob(playerid); // Start a random job

								else

								    SendClientMessage(playerid, 0xFF0000FF, "Ai nevoie de o remorca");



							default: SendClientMessage(playerid, 0xFF0000FF, "Trebuie sa fii soferul tirului pentru a da start jobului");

						}

					}

					else

		                SendClientMessage(playerid, 0xFF0000FF, "Trebuie sa fii soferul tirului pentru a da start jobului");

				}

				case ClassPilot:

				{

					// Check if the player is the driver of a vehicle

					if (GetPlayerVehicleSeat(playerid) == 0)

					{

						// Check if the player is inside a valid piloting vehicle

						switch (GetVehicleModel(GetPlayerVehicleID(playerid)))

						{

							case VehicleShamal, VehicleNevada, VehicleMaverick, VehicleCargobob: // Plane (Shamal), Plane (Nevada), helicopter (Maverick)

								Pilot_StartRandomJob(playerid); // Start a random piloting job

							default: SendClientMessage(playerid, 0xFF0000FF, "You need to be the driver of a piloting vehicle to start a job");

						}

					}

					else

		                SendClientMessage(playerid, 0xFF0000FF, "You need to be the driver of a piloting vehicle to start a job");

				}

				case ClassBusDriver:

				{

					// Check if the player is the driver of a vehicle

					if (GetPlayerVehicleSeat(playerid) == 0)

						if (GetVehicleModel(GetPlayerVehicleID(playerid)) == VehicleCoach) // Check if the player is inside a valid busdriver vehicle

							if (APlayerData[playerid][BusLicense] == 1) // Check if the player has acquired a busdriver license

								ShowPlayerDialog(playerid, DialogBusJobMethod, DIALOG_STYLE_LIST, "Select method:", "Choose your own busroute\r\nAuto assigned busroute", "Select", "Cancel");

							else

								BusDriver_StartJob(playerid, random(sizeof(ABusRoutes))); // Start a random job

						else

			                SendClientMessage(playerid, 0xFF0000FF, "You need to be the driver of a bus to start a job");

					else

		                SendClientMessage(playerid, 0xFF0000FF, "You need to be the driver of a bus to start a job");
				}
				
				case ClassSofer:

				{

					// Check if the player is the driver of a vehicle

					if (GetPlayerVehicleSeat(playerid) == 0)

						if (GetVehicleModel(GetPlayerVehicleID(playerid)) == VehicleTren) // Check if the player is inside a valid busdriver vehicle

							if (APlayerData[playerid][SoferLicense] == 1) // Check if the player has acquired a busdriver license

								ShowPlayerDialog(playerid, DialogSoferJobMethod, DIALOG_STYLE_LIST, "Alege varianta:", "Alege o cursa prestabilita\r\nAlege o cursa la intamplare", "Select", "Anulare");

							else

								Sofer_StartRandomJob(playerid); // Start a random piloting job

						else

			                SendClientMessage(playerid, 0xFF0000FF, "Iti trebuie Un Tren pentru a incepe sa faci curse");

					else

		                SendClientMessage(playerid, 0xFF0000FF, "Iti trebuie un Tren pentru a incepe sa faci curse");

				}

				case ClassMarinar:

				{

					if (GetPlayerVehicleSeat(playerid) == 0)

						if (GetVehicleModel(GetPlayerVehicleID(playerid)) == VehicleReefer) //

							if (APlayerData[playerid][MarinarLicense] == 1)

								    ShowPlayerDialog(playerid, DialogMarinarJobMethod, DIALOG_STYLE_LIST, "Alege varianta:", "Alege o cursa prestabilita\r\nAlege o cursa la intamplare", "Select", "Anulare");

							else

								Marinar_StartRandomJob(playerid);

						else

			                SendClientMessage(playerid, 0xFF0000FF, "Iti trebuie o Barca pentru a incepe");

					else

		                SendClientMessage(playerid, 0xFF0000FF, "Iti trebuie o Barca pentru a incepe sa faci curse");

				}

				case ClassTaxi:

				{

					if (GetPlayerVehicleSeat(playerid) == 0)

						if (GetVehicleModel(GetPlayerVehicleID(playerid)) == VehicleTaxi) //

							if (APlayerData[playerid][TaxiLicense] == 1)

								    ShowPlayerDialog(playerid, DialogTaxiJobMethod, DIALOG_STYLE_LIST, "Alege varianta:", "Alege o cursa prestabilita\r\nAlege o cursa la intamplare", "Select", "Anulare");

							else

								Taxi_StartRandomJob(playerid);

						else

			                SendClientMessage(playerid, 0xFF0000FF, "Iti trebuie un Taxi pentru a incepe");

					else

		                SendClientMessage(playerid, 0xFF0000FF, "Iti trebuie un Taxi pentru a incepe sa faci curse");

				}

				case ClassG:

				{

					// Check if the player is the driver of a vehicle

					if (GetPlayerVehicleSeat(playerid) == 0)

					{

						// Check if the player is inside a valid  vehicle

						switch (GetVehicleModel(GetPlayerVehicleID(playerid)))

						{

							case VehicleTrash:

								G_StartRandomJob(playerid); // Start a random G job

							default: SendClientMessage(playerid, 0xFF0000FF, "Trebuie sa fi in Masina de Gunoi");

						}

					}

					else

		                SendClientMessage(playerid, 0xFF0000FF, "Trebuie sa fii in Masina de Gunoi");

				}

				case ClassMedic:

				{

					// Check if the player is the driver of a vehicle

					if (GetPlayerVehicleSeat(playerid) == 0)

					{

						// Check if the player is inside a valid piloting vehicle

						switch (GetVehicleModel(GetPlayerVehicleID(playerid)))

						{

							case VehicleAmbulance: // Van (Ambulance)

								Medic_StartRandomJob(playerid); // Start a random Medic job

							default: SendClientMessage(playerid, 0xFF0000FF, "Trebuie sa fii soferul unei ambulante pt a incepe o misiune");

						}

					}

					else

		                SendClientMessage(playerid, 0xFF0000FF, "Trebuie sa fii intr-o ambulanta");

				}

				case ClassMafia:

				{

					// Check if the player is the driver of a vehicle

					if (GetPlayerVehicleSeat(playerid) == 0)

					{

						// Check if the player is inside a valid piloting vehicle

						switch (GetVehicleModel(GetPlayerVehicleID(playerid)))

						{

							case VehicleBullet, VehicleSandking, VehicleStretch, VehicleNRG500:

								Mafia_StartRandomJob(playerid); // Start a random mafia job

							default: SendClientMessage(playerid, 0xFF0000FF, "You need to be the driver of a mafia vehicle to start a job");

						}

					}

					else

		                SendClientMessage(playerid, 0xFF0000FF, "You need to be the driver of a mafia vehicle to start a job");

				}

				case ClassCourier:

				{

					// Check if the player is the driver of a vehicle

					if (GetPlayerVehicleSeat(playerid) == 0)

					{

						// Check if the player is inside a valid courier vehicle

						switch (GetVehicleModel(GetPlayerVehicleID(playerid)))

						{

							case VehicleBurrito, VehicleSecuricar, VehiclePicador, VehicleSANNewsMaverick: // 

								Courier_StartJob(playerid); // Start a random courier job

							default: SendClientMessage(playerid, 0xFF0000FF, "You need to be the driver of a courier vehicle to start a job");

						}

					}

					else

		                SendClientMessage(playerid, 0xFF0000FF, "You need to be the driver of a courier vehicle to start a job");

				}

				case ClassPboy:

				{

					// Check if the player is the driver of a vehicle

					if (GetPlayerVehicleSeat(playerid) == 0)

					{

						// Check if the player is inside a valid Pizza Boy vehicle

						switch (GetVehicleModel(GetPlayerVehicleID(playerid)))

						{

							case VehiclePboy: // 

								Pboy_StartJob(playerid); // Start a random Pizza Boy job

							default: SendClientMessage(playerid, 0xFF0000FF, "Trebuie sa fi pe un motor pt a livra Pizza");

						}

					}

					else

		                SendClientMessage(playerid, 0xFF0000FF, "Ai Nevoie de o masina motor pt a livra Pizza");

				}

				case ClassPadurar:

				{

					if (GetPlayerVehicleSeat(playerid) == 0)

						if (GetVehicleModel(GetPlayerVehicleID(playerid)) == VehicleDFT30) //

							if (APlayerData[playerid][PadurarLicense] == 1)

								    ShowPlayerDialog(playerid, DialogPadurarJobMethod, DIALOG_STYLE_LIST, "Alege varianta:", "Alege o cursa prestabilita\r\nAlege o cursa la intamplare", "Select", "Anulare");

							else

								Padurar_StartRandomJob(playerid);

						else

			                SendClientMessage(playerid, 0xFF0000FF, "Iti trebuie o Masina pentru a incepe");

					else

		                SendClientMessage(playerid, 0xFF0000FF, "Iti trebuie o Masina pentru a incepe sa faci curse");

				}

				case ClassRoadWorker:

				{

					// Check if the player is the driver of a vehicle

					if (GetPlayerVehicleSeat(playerid) == 0)

					{

						// Check if the player is inside a valid courier vehicle

						switch (GetVehicleModel(GetPlayerVehicleID(playerid)))

						{

							case VehicleUtilityVan, VehicleTowTruck: // Utility Van, Towtruck

								Roadworker_StartRandomJob(playerid); // Start a random roadworker job

							default: SendClientMessage(playerid, 0xFF0000FF, "You need to be the driver of a roadworker vehicle to start a job");

						}

					}

					else

		                SendClientMessage(playerid, 0xFF0000FF, "You need to be the driver of a roadworker vehicle to start a job");

				}

				default: SendClientMessage(playerid, 0xFF0000FF, "Nu poti face joburi");

			}

		}

		else // Send a message to let the player know he already has a job

		    SendClientMessage(playerid, 0xFF0000FF, "Esti intr-un job");

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// Stops the current job

COMMAND:stopwork(playerid, params[])

{

	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/stopwork", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

	    // Check if the player has a job started

		if (APlayerData[playerid][JobStarted] == true)

		{

		    // Check the class of the player

			switch (APlayerData[playerid][PlayerClass])

			{

				case ClassTruckDriver: Trucker_EndJob(playerid); // Stop any trucker job

				case ClassBusDriver: BusDriver_EndJob(playerid); // Stop any busdriver job

				case ClassPilot: Pilot_EndJob(playerid); // Stop any pilot job

				case ClassMedic: Medic_EndJob(playerid); // Stop any Medic job

				case ClassMafia: Mafia_EndJob(playerid); // Stop any mafia job

				case ClassCourier: Courier_EndJob(playerid);

				case ClassPboy: Pboy_EndJob(playerid);

				case ClassSofer: Sofer_EndJob(playerid);

				case ClassG: G_EndJob(playerid);

				case ClassPadurar: Padurar_EndJob(playerid);

				case ClassMarinar: Marinar_EndJob(playerid);

				case ClassTaxi: Taxi_EndJob(playerid);

				case ClassRoadWorker: Roadworker_EndJob(playerid);

				default: SendClientMessage(playerid, 0xFF0000FF, "Your class has no job to end");

			}



			// Inform the player that he failed the mission

			GameTextForPlayer(playerid, "~w~You ~r~failed~w~ your mission. You lost ~y~$10000~w~ to cover expenses.", 5000, 4);

			// Reduce the player's cash by 1000

			RewardPlayer(playerid, -10000, 0);

		}

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// Displays the player's coordinates on the map

COMMAND:loc(playerid, params[])

{

	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/loc", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 3

		if (APlayerData[playerid][PlayerLevel] >= 3)

		{

		    // Setup some local variables

			new Message[200], Float:x, Float:y, Float:z, Float:rot, Interior, World;

			// Get the player's position

			GetPlayerPos(playerid, x, y, z);

			// Check if the player is on foot or in a vehicle

			if (GetPlayerVehicleSeat(playerid) == -1)

				GetPlayerFacingAngle(playerid, rot); // Get the player's angle

			else

			    GetVehicleZAngle(GetPlayerVehicleID(playerid), rot);



			// Get the interior where the player is located

			Interior = GetPlayerInterior(playerid);

			// Get the virtual world of the player

			World = GetPlayerVirtualWorld(playerid);

			// combine the position and angle into a proper message

		    format(Message, sizeof(Message), "Location: X=%4.2f, Y=%4.2f, Z=%4.2f, rotation=%4.2f, interior=%i, world=%i", x, y, z, rot, Interior, World);

		    // Send the message with the coordinates and the angle of the player

			SendClientMessage(playerid, 0xFF0000AA, Message);

		}

		else

		    return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// Saves the location into a file

COMMAND:saveloc(playerid, params[])

{

	new File:LocFile, LineForFile[255], LineMsg[255];

	new Float:x, Float:y, Float:z, LocName[255], ID;



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/saveloc", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 5

		if (APlayerData[playerid][PlayerLevel] >= 4)

		{

			if (sscanf(params, "is[255]", ID, LocName)) SendClientMessage(playerid, 0xFF0000AA, "[RLT]: \"/saveloc <ID> <LocationName>\"");

			else

			{

				if (!fexist("ServerData/Locations.txt"))

				{

				    LocFile = fopen("ServerData/Locations.txt", io_write); // Create the file

					fclose(LocFile); // Close the file

				}



				// Get the player's position

				GetPlayerPos(playerid, x, y, z);

				// Combine all the data in a proper structure, so it can be used directly for setting up the ALocations array

			    format(LineForFile, sizeof(LineForFile), "\t{\"%s\", %4.2f, %4.2f, %4.2f}, // ID = %i", LocName, x, y, z, ID);



				LocFile = fopen("ServerData/Locations.txt", io_append); // Open the locationfile for appending data to it

				fwrite(LocFile, LineForFile); // Append the data to the end of the file

				fwrite(LocFile, "\r\n"); // Start a new line, or all the data is saved in one line

				fclose(LocFile); // Close the file



				// Let the player know what data has been saved

				format(LineMsg, 255, "Data has been saved: %s", LineForFile);

				SendClientMessage(playerid, 0x808080FF, LineMsg);

			}

		}

		else

		    return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// Lets the player choose where he wants to respawn (costs $200)

COMMAND:rescue(playerid, params[])

{

	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/rescue", params);

	

	if (GetPlayerState(playerid) == PLAYER_STATE_WASTED || GetPlayerState(playerid) == PLAYER_STATE_NONE)

		return 0;

	

	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player has a wanted level of less than 3

		if (GetPlayerWantedLevel(playerid) < 3)

		{

			// Check if the player isn't in jail

			if (APlayerData[playerid][PlayerJailed] == 0)

			{

				if (APlayerData[playerid][JobStarted] == false)

				{

					// Make sure you can't use "/rescue" when you're inside a vehicle (doesn't respawn you at the requested coords

					// and puts a random item (bottle, sigarette, ...) in the player's hands

					if (GetPlayerVehicleID(playerid) == 0)

					{

					    // Create a dialog based on the player's class

						switch (APlayerData[playerid][PlayerClass])

						{

							case ClassTruckDriver: // Ask where the trucker player wants to respawn

								ShowPlayerDialog(playerid, DialogRescue, DIALOG_STYLE_LIST, "Choose trucker spawn point:", "Las Venturas", "Spawn", "Anulare");

							case ClassBusDriver: // Ask where the busdriver wants to respawn

								ShowPlayerDialog(playerid, DialogRescue, DIALOG_STYLE_LIST, "Choose busdriver spawn point:", "Las Venturas", "Spawn", "Anulare");

							case ClassPilot: // Ask where the pilot wants to respawn

								ShowPlayerDialog(playerid, DialogRescue, DIALOG_STYLE_LIST, "Choose pilot spawn point:", "Las Venturas", "Spawn", "Anulare");

							case ClassSofer: // Ask where the pilot wants to respawn

								ShowPlayerDialog(playerid, DialogRescue, DIALOG_STYLE_LIST, "Conducator Tren spawn point:", "Ls Gara", "Spawn", "Anulare");

							case ClassG: // Ask where the pilot wants to respawn

								ShowPlayerDialog(playerid, DialogRescue, DIALOG_STYLE_LIST, "G spawn place:", "Groapa De Gunoi:", "Spawn", "Anulare");

							case ClassMarinar: // Ask where the pilot wants to respawn

								ShowPlayerDialog(playerid, DialogRescue, DIALOG_STYLE_LIST, "Marinar Spawn:", "Sf BBC:", "Spawn", "Anulare");

							case ClassTaxi:

								ShowPlayerDialog(playerid, DialogRescue, DIALOG_STYLE_LIST, "Taxi :", "Ls Spawn:", "Spawn", "Anulare");

							case ClassMedic: // Ask where the pilot wants to respawn

								ShowPlayerDialog(playerid, DialogRescue, DIALOG_STYLE_LIST, "Choose Medic spawn point:", "Los Santos", "Spawn", "Anulare");

							case ClassPolice: // Ask where the police player wants to respawn

								ShowPlayerDialog(playerid, DialogRescue, DIALOG_STYLE_LIST, "Choose police spawn point:", "Las Venturas", "Spawn", "Anulare");

							case ClassCourier: // Ask where the courier player wants to respawn

								ShowPlayerDialog(playerid, DialogRescue, DIALOG_STYLE_LIST, "Choose courier spawn point:", "Las Venturas", "Spawn", "Anulare");

							case ClassFBY: // Ask where the courier player wants to respawn

								ShowPlayerDialog(playerid, DialogRescue, DIALOG_STYLE_LIST, "Choose FBI spawn point:", "Ls Santos", "Spawn", "Anulare");

							case ClassPboy: // Ask where the courier player wants to respawn

								ShowPlayerDialog(playerid, DialogRescue, DIALOG_STYLE_LIST, "Choose courier spawn point:", "Los Santos", "Spawn", "Anulare");

							case ClassPadurar: // Ask where the courier player wants to respawn

								ShowPlayerDialog(playerid, DialogRescue, DIALOG_STYLE_LIST, "Choose courier spawn point:", "In Padure", "Spawn", "Anulare");

						}

					}

					else

						SendClientMessage(playerid, 0xFF0000FF, "You cannot use '/rescue' when you're inside a vehicle"); // "/rescue" doesn't work inside a vehicle

				}

				else

				    SendClientMessage(playerid, 0xFF0000FF, "You cannot use rescue when doing a job"); // "/rescue" doesn't work during a job

			}

			else

			    SendClientMessage(playerid, 0xFF0000FF, "You cannot use /rescue when you're in jail");

		}

		else

		    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}You cannot use /rescue when you're wanted");

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}

// Increases the player's wanted level by 1

COMMAND:wanted(playerid, params[])

{

	new OtherPlayer, Stars;



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/wanted", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 2

		if (APlayerData[playerid][PlayerLevel] >= 2)

		{

			if (sscanf(params, "ui", OtherPlayer, Stars)) SendClientMessage(playerid, 0xFF0000AA, "[RLT]: \"/wanted <OtherPlayer> <Stars>\"");

			else

				if (IsPlayerConnected(OtherPlayer)) // If the player is a valid playerid (he's connected)

					SetPlayerWantedLevel(OtherPlayer, Stars);

				else

				    SendClientMessage(playerid, 0xFF0000FF, "That player isn't online");

		}

		else

		    return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}

// Lets the player choose a motorcycle to spawn

COMMAND:bike(playerid, params[])

{

	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/bike", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 1

		if (APlayerData[playerid][PlayerLevel] >= 1)

		{

			// Make sure the player isn't inside a vehicle

			if (GetPlayerVehicleID(playerid) == 0)

			{

				// Ask which motorcycle the player wants to have

				ShowPlayerDialog(playerid, DialogBike, DIALOG_STYLE_LIST, "Choose a motorcycle:", "Bike\r\nBMX\r\nMountain Bike\r\nFaggio\r\nPboy\r\nBF-400\r\nNRG-500\r\nPCJ-600\r\nFCR-900\r\nFreeway\r\nWayfarer\r\nSanchez\r\nQuad", "Spawn", "Anulare");

				// Let the server know that this was a valid command

				return 1;

			}

		}

		else

		    return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}

// Lets the player choose a car to spawn (in a split list which shows only 10 cars at a time)

COMMAND:car(playerid, params[])

{

	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/car", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 1

		if (APlayerData[playerid][PlayerLevel] >= 1)

		{

			// Make sure the player isn't inside a vehicle

			if (GetPlayerVehicleID(playerid) == 0)

				CarList_Create(playerid); // Create a list of cars (only the first 10 cars) and show the dialog so the player can choose a car

		}

		else

		    return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}







// Lets the player choose a plane to spawn (in a split list which shows only 10 planes at a time)

COMMAND:plane(playerid, params[])

{

	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/plane", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 1

		if (APlayerData[playerid][PlayerLevel] >= 1)

		{

			// Make sure the player isn't inside a vehicle

			if (GetPlayerVehicleID(playerid) == 0)

				PlaneList_Create(playerid); // Create a list of planes (only the first 10 planes) and show the dialog so the player can choose a plane

		}

		else

		    return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}







// Lets the player choose a trailer to spawn (in a split list which shows only 10 trailers at a time)

COMMAND:trailer(playerid, params[])

{

	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/trailer", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 1

		if (APlayerData[playerid][PlayerLevel] >= 1)

		{

			// Make sure the player isn't inside a vehicle

			if (GetPlayerVehicleID(playerid) == 0)

				TrailerList_Create(playerid); // Create a list of trailers (only the first 10 trailers) and show the dialog so the player can choose a trailer

		}

		else

		    return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// Lets the player choose a boat to spawn

COMMAND:boat(playerid, params[])

{

	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/boat", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 1

		if (APlayerData[playerid][PlayerLevel] >= 1)

		{

			// Make sure the player isn't inside a vehicle

			if (GetPlayerVehicleID(playerid) == 0)

			{

				// Ask which motorcycle the player wants to have

				ShowPlayerDialog(playerid, DialogBoat, DIALOG_STYLE_LIST, "Choose a boat:", "Coastguard\nDinghy\nJetmax\nLaunch\nMarquis\nPredator\nReefer\nSpeeder\nSquallo\nTropic", "Spawn", "Anulare");

				// Let the server know that this was a valid command

				return 1;

			}

		}

		else

		    return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}







// Jail a player

COMMAND:jail(playerid, params[])

{

	new PlayerToJail, JailTime, Reason[128], Msg[128], Name[24], AdminName[24];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/jail", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 1

		if (APlayerData[playerid][PlayerLevel] >= 1)

		{

			if (sscanf(params, "uis[128]", PlayerToJail, JailTime, Reason)) SendClientMessage(playerid, 0xFF0000AA, "[RLT]: \"/jail <PlayerToJail> <JailTime> <Reason>\"");

			else

				if (IsPlayerConnected(PlayerToJail)) // If the player is a valid playerid (he's connected)

				{

				    // Jail the player

					Police_JailPlayer(PlayerToJail, JailTime);

					// Get the name of the player who jailed the player

					GetPlayerName(playerid, AdminName, sizeof(AdminName));

					// Get the name of the player who's being sent to jail

					GetPlayerName(PlayerToJail, Name, sizeof(Name));

					// Send the jailed player a message who jailed him, why he's been jailed and how long

					format(Msg, 128, "You have been jailed by %s %s for %i seconds", AdminLevelName[APlayerData[playerid][PlayerLevel]], AdminName, JailTime);

					SendClientMessage(PlayerToJail, 0xFF0000FF, Msg);

					format(Msg, 128, "Reason: %s", Reason);

					SendClientMessage(PlayerToJail, 0xFF0000FF, Msg);

					format(Msg, 128, "{00FF00}You have jailed {FFFF00}%s{00FF00} for {FFFF00}%i{00FF00} seconds", Name, JailTime);

					SendClientMessage(playerid, 0xFFFFFFFF, Msg);

				}

				else

				    SendClientMessage(playerid, 0xFF0000FF, "That player isn't online");

		}

		else

		    return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// Warn a player

COMMAND:warn(playerid, params[])

{

	new PlayerToWarn, Reason[128], ReasonMsg[128], Name[24];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/warn", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 1

		if (APlayerData[playerid][PlayerLevel] >= 1)

		{

			if (sscanf(params, "us[128]", PlayerToWarn, Reason)) SendClientMessage(playerid, 0xFF0000AA, "[RLT]: \"/warn <PlayerToWarn> <Reason>\"");

			else

				if (IsPlayerConnected(PlayerToWarn)) // If the player is a valid playerid (he's connected)

				{

					// Increase the number of warnings

					APlayerData[PlayerToWarn][Warnings]++;



					// Get the name of the player who warned the player

					GetPlayerName(playerid, Name, sizeof(Name));

					// Send the warned player a message who warned him and why he's been warned

					format(ReasonMsg, 128, "You have been warned by %s %s", AdminLevelName[APlayerData[playerid][PlayerLevel]], Name);

					SendClientMessage(PlayerToWarn, 0xFF0000FF, ReasonMsg);

					format(ReasonMsg, 128, "Reason: %s", Reason);

					SendClientMessage(PlayerToWarn, 0xFF0000FF, ReasonMsg);

					format(ReasonMsg, 128, "~w~Warning %i/%i: ~r~%s~w~", APlayerData[PlayerToWarn][Warnings], AutoKickWarnings, Reason);

					GameTextForPlayer(PlayerToWarn, ReasonMsg, 5000, 4);



					// Get the name of the warned player

					GetPlayerName(PlayerToWarn, Name, sizeof(Name));

					// Let the admin know who has been warned and why

					format(ReasonMsg, 128, "You have warned %s (warnings: %i/%i)", Name, APlayerData[PlayerToWarn][Warnings], AutoKickWarnings);

					SendClientMessage(playerid, 0x00FF00FF, ReasonMsg);

					format(ReasonMsg, 128, "Reason: %s", Reason);

					SendClientMessage(playerid, 0xFF0000FF, ReasonMsg);



					// Automatically kick the player if he got 3 warnings (if autokick is enabled)

					if ((APlayerData[PlayerToWarn][Warnings] == AutoKickWarnings) && (AutoKickAfterWarn == 1))

						Kick(PlayerToWarn);

				}

				else

				    SendClientMessage(playerid, 0xFF0000FF, "That player isn't online");

		}

		else

		    return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// Kicks a player with a reason

COMMAND:kick(playerid, params[])

{

	new PlayerToKick, Reason[128], ReasonMsg[128], Name[24];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/kick", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 1

		if (APlayerData[playerid][PlayerLevel] >= 1)

		{

			if (sscanf(params, "us[128]", PlayerToKick, Reason)) SendClientMessage(playerid, 0xFF0000AA, "[RLT]: \"/kick <PlayerToKick> <Reason>\"");

			else

				if (IsPlayerConnected(PlayerToKick)) // If the player is a valid playerid (he's connected)

				{

					// Get the name of the player who warned the player

					GetPlayerName(playerid, Name, sizeof(Name));

					// Send the warned player a message who kicked him and why he's been kicked

					format(ReasonMsg, 128, "You have been kicked by %s %s", AdminLevelName[APlayerData[playerid][PlayerLevel]], Name);

					SendClientMessage(PlayerToKick, 0xFF0000FF, ReasonMsg);

					format(ReasonMsg, 128, "Reason: %s", Reason);

					SendClientMessage(PlayerToKick, 0xFF0000FF, ReasonMsg);

					// Kick the player

					Kick(PlayerToKick);

				}

				else

				    SendClientMessage(playerid, 0xFF0000FF, "That player isn't online");

		}

		else

		    return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// Bans a player for (days, hours, minutes, seconds)

COMMAND:ban(playerid, params[])

{

	// Setup local variables

	new PlayerToBan, Days, Hours, Reason[128], TotalBanTime, Msg[128], Name[24], AdminName[24];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/ban", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 3

		if (APlayerData[playerid][PlayerLevel] >= 3)

		{

			if (sscanf(params, "uiis[128]", PlayerToBan, Days, Hours, Reason))

				SendClientMessage(playerid, 0xFF0000AA, "[RLT]: \"/ban <PlayerToBan> <Days> <Hours> <Reason>\"");

			else

			{

				if (IsPlayerConnected(PlayerToBan))

				{

					// Get the names of the player and the admin who executed the ban

					GetPlayerName(playerid, AdminName, sizeof(AdminName));

					GetPlayerName(PlayerToBan, Name, sizeof(Name));



					// Increase the number of bans

					APlayerData[PlayerToBan][Bans]++;

					// Calculate the total bantime (when the player can login again)

					TotalBanTime = (Days * 86400) + (Hours * 3600) + gettime();

					// Check if this is the player's 5th ban

					if (APlayerData[PlayerToBan][Bans] == 5)

						APlayerData[PlayerToBan][BanTime] = 2147483640; // Make the ban permanent (as high as it can go)

					else

						APlayerData[PlayerToBan][BanTime] = TotalBanTime; // Store this value for the player



					// Inform the player about his ban

					// Check if this is the player's 5th ban

					if (APlayerData[PlayerToBan][Bans] == 5)

					{

						format(Msg, 128, "You have been banned permanently by %s, this was your 5th ban", AdminName);

						SendClientMessage(PlayerToBan, 0x808080FF, Msg);

					}

					else

					{

						format(Msg, 128, "You have been banned by %s for %i days and %i hours", AdminName, Days, Hours);

						SendClientMessage(PlayerToBan, 0x808080FF, Msg);

						format(Msg, 128, "Reason: %s", Reason);

						SendClientMessage(PlayerToBan, 0x808080FF, Msg);

						format(Msg, 128, "You've been banned %i times now, 5th time is permament", APlayerData[PlayerToBan][Bans]);

						SendClientMessage(PlayerToBan, 0x808080FF, Msg);

					}



					// Kick the player (his data will be saved)

					Kick(PlayerToBan);



					// Inform everybody else which player was banned and for how long

					format(Msg, 128, "%s %s has banned %s for %i days and %i hours", AdminLevelName[APlayerData[playerid][PlayerLevel]], AdminName, Name, Days, Hours);

					SendClientMessageToAll(0x808080FF, Msg);

				}

			}

		}

		else

		    return 0;

	}

	else

	    return 0;



	return 1;

}



// Unbans a player (cleares the ban-time)

COMMAND:unban(playerid, params[])

{

	// Setup local variables

	new PlayerToUnban[24], Msg[128], Name[24];

	new file[100], File:PFile, LineForFile[100];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/unban", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 3

		if (APlayerData[playerid][PlayerLevel] >= 3)

		{

			if (sscanf(params, "s[128]", PlayerToUnban))

				SendClientMessage(playerid, 0xFF0000AA, "[RLT]: \"/unban <PlayerToUnban>\"");

			else

			{

			    // Get the name of the admin

				GetPlayerName(playerid, Name, sizeof(Name));



				// Construct the complete filename for this player's account

				format(file, sizeof(file), PlayerFile, PlayerToUnban);



				// Check if the file exists

				if (fexist(file))

				{

					PFile = fopen(file, io_append); // Open the playerfile for appending (this command only appends a new line to overwrite the bantime)



					format(LineForFile, 100, "BanTime 0\r\n"); // Construct the line: "BanTime <0>"

					fwrite(PFile, LineForFile); // And save it to the file



					fclose(PFile); // Close the file



					// Inform everybody else which player was unbanned

					format(Msg, 128, "%s %s has un-banned %s", AdminLevelName[APlayerData[playerid][PlayerLevel]], Name, PlayerToUnban);

					SendClientMessageToAll(0x808080FF, Msg);

				}

				else

				    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}There is no account with that playername");

			}

		}

		else

		    return 0;

	}

	else

	    return 0;



	return 1;

}



// Spawns the object at the location given by the player

COMMAND:object(playerid, params[])

{

    // Setup local variables

	new ObjectModel, ObjID, Msg[128], Float:x, Float:y, Float:z, Float:Angle;



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/object", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 5

		if (APlayerData[playerid][PlayerLevel] >= 5)

		{

			if (sscanf(params, "iffff", ObjectModel, x, y, z, Angle)) SendClientMessage(playerid, 0xFF0000AA, "[RLT]: \"/object <ObjectModel> <x> <y> <z> <Angle>\"");

			else

			{

				// Spawn the object 5 units north of the player

				ObjID = CreateObject(ObjectModel, x, y, z, 0.0, 0.0, Angle, 250.0);

				// Inform the player about it

				format(Msg, 128, "You spawned object-id %i (model-id = %i) at coords: x=%4.2f, y=%4.2f, z=%4.2f", ObjID, ObjectModel, x, y, z);

				SendClientMessage(playerid, 0x00FF00FF, Msg);

			}

		}

		else

		    return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// Spawns the pickup at the location given by the player

COMMAND:pickup(playerid, params[])

{

    // Setup local variables

	new PickupModel, PickID, Msg[128], Float:x, Float:y, Float:z, PickupType;



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/pickup", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 5

		if (APlayerData[playerid][PlayerLevel] >= 5)

		{

			if (sscanf(params, "ifffi", PickupModel, x, y, z, PickupType)) SendClientMessage(playerid, 0xFF0000AA, "[RLT]: \"/pickup <PickupModel> <x> <y> <z> <PickupType>\"");

			else

			{

				// Spawn the pickup

				PickID = CreatePickup(PickupModel, PickupType, x, y, z, -1);

				// Inform the player about it

				format(Msg, 128, "You spawned pickup-id %i (model-id = %i) at coords: x=%4.2f, y=%4.2f, z=%4.2f", PickID, PickupModel, x, y, z);

				SendClientMessage(playerid, 0x00FF00FF, Msg);

			}

		}

		else

		    return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// Spawns the vehicle at the location given by the player

COMMAND:vehicle(playerid, params[])

{

    // Setup local variables

	new VehicleModel, vID, Msg[128], Float:x, Float:y, Float:z, Float:Angle, SpawnDelay;



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/vehicle", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 5

		if (APlayerData[playerid][PlayerLevel] >= 5)

		{

			if (sscanf(params, "iffffi", VehicleModel, x, y, z, Angle, SpawnDelay)) SendClientMessage(playerid, 0xFF0000AA, "[RLT]: \"/vehicle <VehicleModel> <x> <y> <z> <Angle> <SpawnDelay>\"");

			else

			{

				// Spawn the vehicle at the location specified by the player (also set max-fuel and save the model for the vehicle)

				vID = Vehicle_Create(VehicleModel, x, y, z, Angle, random(126), random(126), SpawnDelay);

				// Inform the player about it

				format(Msg, 128, "You spawned vehicle-id %i (model-id = %i) at coords: x=%4.2f, y=%4.2f, z=%4.2f", vID, VehicleModel, x, y, z);

				SendClientMessage(playerid, 0x00FF00FF, Msg);

			}

		}

		else

		    return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}

// Ports the player to the given coordinates

COMMAND:portloc(playerid, params[])

{

	// Setup local variables

	new Float:x, Float:y, Float:z, PortMsg[128];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/portloc", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 1

		if (APlayerData[playerid][PlayerLevel] >= 1)

		{

			// Check if the player has a wanted level of less than 3

			if (GetPlayerWantedLevel(playerid) < 3)

			{

				// Check if the player is not jailed

				if (APlayerData[playerid][PlayerJailed] == 0)

				{

					if (sscanf(params, "fff", x, y, z)) SendClientMessage(playerid, 0xFF0000AA, "[RLT]: \"/portloc <x> <y> <z>\"");

					else

					{

						// Port the player to the given location

						SetPlayerPos(playerid, x, y, z);

						// Let the player know about it

						format(PortMsg, 128, "You have been ported to location: %4.2f, %4.2f, %4.2f", x, y, z);

						SendClientMessage(playerid, 0x00FF00FF, PortMsg);

					}

				}

				else

				    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}You cannot use /portloc when you're in jail");

			}

			else

			    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}You cannot use /portloc when you're wanted");

		}

		else

		    return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// Ports the player to the given player

COMMAND:port(playerid, params[])

{

	// Setup local variables

	new OtherPlayer, Float:x, Float:y, Float:z, PortMsg[128], IntID, WorldID;



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/port", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 1

		if (APlayerData[playerid][PlayerLevel] >= 1)

		{

			// Check if the player has a wanted level of less than 3

			if (GetPlayerWantedLevel(playerid) < 3)

			{

				// Check if the player is not jailed

				if (APlayerData[playerid][PlayerJailed] == 0)

				{

					if (sscanf(params, "u", OtherPlayer)) SendClientMessage(playerid, 0xFF0000AA, "[RLT]: \"/port <OtherPlayer>\"");

					else

					{

						// Check if that other player is online

						if (IsPlayerConnected(OtherPlayer))

						{

							// Get the location of the other player

							GetPlayerPos(OtherPlayer, x, y, z);

							IntID = GetPlayerInterior(OtherPlayer);

							WorldID = GetPlayerVirtualWorld(OtherPlayer);

							// Port the player to the given location

							SetPlayerVirtualWorld(playerid, WorldID);

							SetPlayerInterior(playerid, IntID);

							SetPlayerPos(playerid, x, y, z + 3.0);

							// Let the player know about it

							format(PortMsg, 128, "You have been ported to location: %4.2f, %4.2f, %4.2f", x, y, z + 3.0);

							SendClientMessage(playerid, 0x00FF00FF, PortMsg);

						}

						else

						    SendClientMessage(playerid, 0xFF0000FF, "That player isn't online");

					}

				}

				else

				    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}You cannot use /port when you're in jail");

			}

			else

			    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}You cannot use /port when you're wanted");

		}

		else

		    return 0;

	}

	else

	    return 0;




	// Let the server know that this was a valid command

	return 1;

}

// Ports one player to another player

COMMAND:tele(playerid, params[])

{

	// Setup local variables

	new Player1, Player2, Float:x, Float:y, Float:z, PortMsg[128], IntID, WorldID, Name[24], AdminName[24];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/tele", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 1

		if (APlayerData[playerid][PlayerLevel] >= 1)

		{

			if (sscanf(params, "uu", Player1, Player2)) SendClientMessage(playerid, 0xFF0000AA, "[RLT]: \"/tele <PlayerToPort> <TargetPlayer>\"");

			else

			{

				// Check if player1 is online

				if (APlayerData[Player1][LoggedIn] == true)

				{

					// Check if player2 is online

					if (APlayerData[Player2][LoggedIn] == true)

					{

					    // Get the name of the admin and the second player

					    GetPlayerName(playerid, AdminName, sizeof(AdminName));

					    GetPlayerName(Player2, Name, sizeof(Name));

						// Get the location of the second player

						GetPlayerPos(Player2, x, y, z);

						IntID = GetPlayerInterior(Player2);

						WorldID = GetPlayerVirtualWorld(Player2);

						// Port the first player to player2's location

						SetPlayerVirtualWorld(Player1, WorldID);

						SetPlayerInterior(Player1, IntID);

						SetPlayerPos(Player1, x, y, z + 3.0);

						// Let the first player know he's been ported

						format(PortMsg, 128, "{00FF00}You have been ported to player {FFFF00}%s{00FF00} by {FFFF00}%s", Name, AdminName);

						SendClientMessage(Player1, 0xFFFFFFFF, PortMsg);

					}

					else

					    SendClientMessage(playerid, 0xFF0000FF, "Player2 isn't online");

				}

				else

				    SendClientMessage(playerid, 0xFF0000FF, "Player1 isn't online");

			}

		}

		else

		    return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// Ports the player to the given vehicle

COMMAND:portvehicle(playerid, params[])

{

	// Setup local variables

	new Car, Float:x, Float:y, Float:z, PortMsg[128];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/portvehicle", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 1

		if (APlayerData[playerid][PlayerLevel] >= 1)

		{

			// Check if the player has a wanted level of less than 3

			if (GetPlayerWantedLevel(playerid) < 3)

			{

				// Check if the player is not jailed

				if (APlayerData[playerid][PlayerJailed] == 0)

				{

					if (sscanf(params, "i", Car)) SendClientMessage(playerid, 0xFF0000AA, "[RLT]: \"/portvehicle <CarID>\"");

					else

					{

						// Get the location of the car

						GetVehiclePos(Car, x, y, z);

						// Port the player to the given location

						SetPlayerPos(playerid, x, y, z + 3.0);

						// Let the player know about it

						format(PortMsg, 128, "You have been ported to location: %4.2f, %4.2f, %4.2f", x, y, z + 3.0);

						SendClientMessage(playerid, 0x00FF00FF, PortMsg);

					}

				}

				else

				    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}You cannot use /portvehicle when you're in jail");

			}

			else

			    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}You cannot use /portvehicle when you're wanted");

		}

		else

		    return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// Sets the admin-level of another player

COMMAND:setlevel(playerid, params[])

{

	// Setup local variables

	new OtherPlayer, Level, Msg[128], Name[24], AdminName[24], OldLevel;



	// Send the command to all admins so they can see it

	//SendAdminText(playerid, "/setlevel", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin rcon 

		if (APlayerData[playerid][PlayerLevel] >= 8)

		{

			if (sscanf(params, "ui", OtherPlayer, Level)) SendClientMessage(playerid, 0xFF0000AA, "[RLT]: \"/setlevel <ID/Nume> <Nivel>\"");

			else

			{

				// Check if that other player is online

				if (IsPlayerConnected(OtherPlayer))

				{

				    // Get the old level of the other player

				    OldLevel = APlayerData[OtherPlayer][PlayerLevel];

					// Get the playername of the admin

					GetPlayerName(playerid, AdminName, sizeof(AdminName));

					// Also get the name of the player that has been promoted

					GetPlayerName(OtherPlayer, Name, sizeof(Name));

					// Store the level of the player

					APlayerData[OtherPlayer][PlayerLevel] = Level;

					// Let all players know about it

					if (OldLevel != Level)

					{

						// Check if the player has been promoted or demoted

						if (OldLevel < Level)

							format(Msg, 128, "Jucatorul %s a fost promovat la gradul %s de catre %s", Name, AdminLevelName[Level], AdminName);

						if (OldLevel > Level)

							format(Msg, 128, "Jucatorul %s a fost retrogradat la gradul %s de catre %s", Name, AdminLevelName[Level], AdminName);

						SendClientMessageToAll(0x00FF00FF, Msg);

					}

					else

						SendClientMessage(playerid, 0xFF0000FF, "[RLT]: Levelul jucatorului este acelasi");

				}

				else

				    SendClientMessage(playerid, 0xFF0000FF, "[RLT]: Acest jucator nu este online");

			}

		}

		else

		    return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}

// Refuel the player's vehicle

COMMAND:fuel(playerid, params[])

{

	// Setup local variables

	new vID;



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/fuel", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 1

		if (APlayerData[playerid][PlayerLevel] >= 1)

		{

			// Check if the player is inside a vehicle

			if (IsPlayerInAnyVehicle(playerid))

			{

			    // Get the vehicleid

			    vID = GetPlayerVehicleID(playerid);

			    // Refuel the vehicle

			    AVehicleData[vID][Fuel] = MaxFuel;

				// Let the player know about it

				SendClientMessage(playerid, 0x00FF00FF, "Your vehicle is refuelled");

			}

			else

				SendClientMessage(playerid, 0x00FF00FF, "You're not driving a vehicle");

		}

		else

		    return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



COMMAND:fly(playerid, params[])

{

	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/fly", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 3

		if (APlayerData[playerid][PlayerLevel] >= 3)

		{

			// Equip the player with a jetpack

			SetPlayerSpecialAction(playerid, 2);

		}

		else

		    return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}

COMMAND:paint(playerid, params[])

{

    // Setup local variables

	new paintjobid, vid;



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/paint", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player is the driver of the vehicle

		if (GetPlayerVehicleSeat(playerid) == 0)

		{

			if (sscanf(params, "i", paintjobid)) SendClientMessage(playerid, 0xFF0000AA, "[RLT]: \"/paint <paintjobid (0-2)>\"");

			else

			{

			    // Check if the player entered a correct paintjob-id

			    if ((paintjobid >= 0) && (paintjobid <= 2))

				{

					// Get the vehicle-id

					vid = GetPlayerVehicleID(playerid);

					// Check if the player is the owner of the vehicle

					if (AVehicleData[vid][Owned] == true)

					{

						// Change the paintjob of the player's vehicle

						ChangeVehiclePaintjob(vid, paintjobid);

						// Also save the paintjob for the vehicle

						AVehicleData[vid][PaintJob] = paintjobid + 1;



						// Also set the vehiclecolor to 1 (white), so the paintjob has it's full color

						ChangeVehicleColor(vid, 1, 1);

						// Also save the colors for the vehicle

						AVehicleData[vid][Color1] = 1;

						AVehicleData[vid][Color2] = 1;



						// Let the player pay for the paintjob

						RewardPlayer(playerid, -500, 0);

						// Inform the player about it

						SendClientMessage(playerid, 0x00FF00FF, "You repainted your vehicle for $500");

						// Save the player-file (along with the houses and businesses)

						PlayerFile_Save(playerid);

					}

					else

					    SendClientMessage(playerid, 0xFFFFFFFF, "You're not the owner of the vehicle");

				}

				else

				    SendClientMessage(playerid, 0xFF0000AA, "You need to enter a paintjob-id from 0 to 2");

			}

		}

		else

			SendClientMessage(playerid, 0xFF0000FF, "You must be inside a vehicle you own to apply a paintjob");

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}

COMMAND:color1(playerid, params[])

{

	// Setup local variables

	new ColorList[1000];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/color1", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player is the driver of the vehicle

		if (GetPlayerVehicleSeat(playerid) == 0)

		{

			// Check if the player is the owner of the vehicle

			if (AVehicleData[GetPlayerVehicleID(playerid)][Owned] == true)

			{

				// Construct the colorlist

				format(ColorList, sizeof(ColorList), "%s{FFFFFF}%s\n", ColorList, "Black (removes paintjob)"); // Color 0

				format(ColorList, sizeof(ColorList), "%s{FFFFFF}%s\n", ColorList, "White"); // Color 1



				for (new i = 2; i < sizeof(AVehicleColors); i++)

					format(ColorList, sizeof(ColorList), "%s%s%s\n", ColorList, AVehicleColors[i], "CarColor");



				// Show the dialog with all the colors

				ShowPlayerDialog(playerid, DialogPrimaryCarColor, DIALOG_STYLE_LIST, "Choose a primary color:", ColorList, "Select", "Anulare");

			}

			else

			    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}You're not the owner of the vehicle");

		}

		else

			SendClientMessage(playerid, 0xFF0000FF, "You must be inside a vehicle to apply a color");

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// Re-colors the given vehicle (lets you choose the first color)

COMMAND:color2(playerid, params[])

{

	// Setup local variables

	new ColorList[1000];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/color2", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player is the driver of the vehicle

		if (GetPlayerVehicleSeat(playerid) == 0)

		{

			// Check if the player is the owner of the vehicle

			if (AVehicleData[GetPlayerVehicleID(playerid)][Owned] == true)

			{

				// Construct the colorlist

				format(ColorList, sizeof(ColorList), "%s{FFFFFF}%s\n", ColorList, "Black"); // Color 0

				format(ColorList, sizeof(ColorList), "%s{FFFFFF}%s\n", ColorList, "White"); // Color 1



				for (new i = 2; i < sizeof(AVehicleColors); i++)

					format(ColorList, sizeof(ColorList), "%s%s%s\n", ColorList, AVehicleColors[i], "CarColor");



				// Show the dialog with all the colors

				ShowPlayerDialog(playerid, DialogSedundaryCarColor, DIALOG_STYLE_LIST, "Choose a secundary color:", ColorList, "Select", "Anulare");

			}

			else

			    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}You're not the owner of the vehicle");

		}

		else

			SendClientMessage(playerid, 0x00FF00FF, "You must be inside a vehicle to apply a color");

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}

// Starts or stops the engine of your vehicle

COMMAND:engine(playerid, params[])

{

    // Setup local variables

	new vehicleid, engine,lights,alarm,doors,bonnet,boot,objective;



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/engine", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 1

		if (APlayerData[playerid][PlayerLevel] >= 1)

		{

			// Get the player's vehicle

			vehicleid = GetPlayerVehicleID(playerid);



			// Get the current status of the vehicle

			GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);



			// Check if the player is inside a vehicle

			if (vehicleid != 0)

			{

				if (sscanf(params, "i", engine)) SendClientMessage(playerid, 0xFF0000AA, "[RLT]: \"/engine <EngineStatus (0/1)>\"");

				else

				{

					// Set the engine to the value that was passed by the player and leave all other parameters alone

					SetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);

				}

			}

			else

				SendClientMessage(playerid, 0x00FF00FF, "You must be inside a vehicle to toggle your engine");

		}

		else

		    return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}

// Asks which vehicle parameter you wanna toggle

COMMAND:caroption(playerid, params[])

{

	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/caroption", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 3

		if (APlayerData[playerid][PlayerLevel] >= 3)

		{

			// Let the player select a weather-type

			ShowPlayerDialog(playerid, DialogCarOption, DIALOG_STYLE_LIST, "Select option for your vehicle:", "Engine\nLights\nAlarm\nDoors\nBonnet\nBoot\nObjective", "Toggle", "Anulare");

		}

		else

		    return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// Sets the global weather

COMMAND:weather(playerid, params[])

{

	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/weather", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 4

		if (APlayerData[playerid][PlayerLevel] >= 4)

		{

			// Let the player select a weather-type

			ShowPlayerDialog(playerid, DialogWeather, DIALOG_STYLE_LIST, "Select weather type:", "Normal\nStormy\nFoggy\nScorching Hot\nDull, cloudy, rainy\nSandstorm\nGreen Fog\nDark, cloudy, brown\nExtremely bright\nDark toxic clouds\nBlack & white sky", "Select", "Anulare");

		}

		else

		    return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}

// This command lists all online admins

COMMAND:admins(playerid, params[])

{

	// Setup local variables

	new AdminList[500], Name[24];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/admins", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Scan through all players

		for (new i; i < MAX_PLAYERS; i++)

		{

			// Check if this player is connected

			if (IsPlayerConnected(i))

			{

				// Get the name of the player

				GetPlayerName(i, Name, sizeof(Name));



				// Check if this player is an RCON admin

				if (IsPlayerAdmin(i))

				{

					// Add all admin players to the list

					format(AdminList, 500, "%s%s: %s (id: %i), Level: %i (RCON admin)\n", AdminList, AdminLevelName[APlayerData[i][PlayerLevel]], Name, i, APlayerData[i][PlayerLevel]); // Add the name of the admin-player to the list

					// Re-start the for loop (skipping the remaining code for this iteration)

					continue;

				}



				//Check if that player is an admin (using the PlayerLevel)

				if (APlayerData[i][PlayerLevel] > 0)

				{

					// Add all admin players to the list

					format(AdminList, 500, "%s%s: %s (id: %i), Level: %i\n", AdminList, AdminLevelName[APlayerData[i][PlayerLevel]], Name, i, APlayerData[i][PlayerLevel]); // Add the name of the admin-player to the list

				}

			}

		}



		// Check if there were admin-names added to the list

		if (strlen(AdminList) > 0)

		    ShowPlayerDialog(playerid, DialogNoResponse, DIALOG_STYLE_MSGBOX, "Administratori Online", AdminList, "OK", "");

		else

			SendClientMessage(playerid, 0xFF0000FF, "Momentan 0 admini online"); // No admins are online

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}

COMMAND:convoy(playerid, params[])

{

	// Setup local variables

	new ConvoyList[750], Name[24], NumMembers, ConvoyStatus[10];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/convoy", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Create the list of convoys with all their data

		for (new i; i < MAX_CONVOYS; i++)

		{

		    // Check if this is an empty convoy (not created yet by a player)

			if (AConvoys[i][Status] == CONVOY_EMPTY)

			{

				// Setup data for an empty convoy (one which hasn't been chosen yet)

				NumMembers = 0;

				format(Name, 24, "None");

				format(ConvoyStatus, 10, "Empty");

			}

			else

			{

				// Get the name of the convoy-leader

				GetPlayerName(AConvoys[i][Members][0], Name, sizeof(Name));

				// Calculate the members in the convoy

				NumMembers = Convoy_CountMembers(i);

				// Set the status of the convoy

				switch (AConvoys[i][Status])

				{

					case CONVOY_OPEN: format(ConvoyStatus, 10, "Open");

					case CONVOY_FULL: format(ConvoyStatus, 10, "Full");

					case CONVOY_CLOSED: format(ConvoyStatus, 10, "Closed");

				}

			}



			// Put all data together to form the content of the entire dialog

			format(ConvoyList, sizeof(ConvoyList), "%sLeader: {00FF00}%s{FFFFFF}, members: {FF0000}%i{FFFFFF}, Status: {00FF00}%s{FFFFFF}\n", ConvoyList, Name, NumMembers, ConvoyStatus);

		}



		// Show the dialog

		ShowPlayerDialog(playerid, DialogSelectConvoy, DIALOG_STYLE_LIST, "Select convoy:", ConvoyList, "Select", "Anulare");

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// Allows the leader to kick a member from the convoy

COMMAND:convoykick(playerid, params[])

{

	// Setup local variables

	new Convoy, LeaderID, OtherPlayer, LeaderName[24], MemberName[24], Msg[128];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/convoykick", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		Convoy = APlayerData[playerid][ConvoyID]; // Get the convoy of the player

		LeaderID = AConvoys[Convoy][Members][0]; // Get the leader of his convoy



		// Check if this player is part of a convoy

		if (APlayerData[playerid][InConvoy] == true)

		{

			// Check if this player is the leader of the convoy

			if (LeaderID == playerid)

			{

				if (sscanf(params, "u", OtherPlayer)) SendClientMessage(playerid, 0xFF0000AA, "[RLT]: \"/convoykick <OtherPlayerID>\"");

				else

				{

					// Check if that other player is part of the convoy

					if ((APlayerData[OtherPlayer][InConvoy] == true) && (APlayerData[OtherPlayer][ConvoyID] == Convoy))

					{

					    // Kick the other player from the convoy

						Convoy_Leave(OtherPlayer);

						// Get the names of the leader and member

						GetPlayerName(playerid, LeaderName, sizeof(LeaderName));

						GetPlayerName(OtherPlayer, MemberName, sizeof(MemberName));

						// Inform the leader that he has kicked the other player

						format(Msg, 128, "You've kicked {0000FF}%s{00FF00} from the convoy", MemberName);

						SendClientMessage(playerid, 0x00FF00FF, Msg);

						// Inform the leader that he has kicked the other player

						format(Msg, 128, "Leader {0000FF}%s{00FF00} kicked you from the convoy", LeaderName);

						SendClientMessage(OtherPlayer, 0x00FF00FF, Msg);

					}

					else

					    SendClientMessage(playerid, 0xFF0000FF, "You cannot kick a player that's not part of your convoy");

				}

			}

			else

			    SendClientMessage(playerid, 0xFF0000FF, "You need to be the leader of a convoy to kick another convoy-member");

		}

		else

		    SendClientMessage(playerid, 0xFF0000FF, "You need to be the leader of a convoy to kick another convoy-member");

	}

	else

		return 0;



	// Let the server know that this was a valid command

	return 1;

}

// Allows a convoy-member to leave the convoy

COMMAND:convoyleave(playerid, params[])

{

	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/convoyleave", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if this player is part of a convoy

		if (APlayerData[playerid][InConvoy] == true)

		{

		    // Kick the other player from the convoy

			Convoy_Leave(playerid);

			// Inform the player that he left the convoy

			SendClientMessage(playerid, 0x00FF00FF, "Ai iesit din convoy");

		}

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// Allows the leader to cancel a convoy

COMMAND:convoycancel(playerid, params[])

{

	// Setup local variables

	new Convoy, LeaderID;



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/convoycancel", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		Convoy = APlayerData[playerid][ConvoyID]; // Get the convoy of the player

		LeaderID = AConvoys[Convoy][Members][0]; // Get the leader of his convoy



		// Check if this player is part of a convoy

		if (APlayerData[playerid][InConvoy] == true)

		{

			// Check if this player is the leader of the convoy

			if (LeaderID == playerid)

				Convoy_Cancel(Convoy); // Cancel the convoy, kicking every other member from it

			else

			    SendClientMessage(playerid, 0xFF0000FF, "Trebuie sa fii liderul convoyului pentru a-l anula");

		}

		else

		    SendClientMessage(playerid, 0xFF0000FF, "You need to be the leader of a convoy to cancel it");

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// Displays all members in the convoy

COMMAND:convoymembers(playerid, params[])

{

	// Setup local variables

	new Name[24], MemberList[1000], Convoy;



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/convoymembers", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the member is in a convoy

		if (APlayerData[playerid][InConvoy] == true)

		{

			// Get the convoyID of the member

			Convoy = APlayerData[playerid][ConvoyID];



			// Loop through all members

			for (new i; i < CONVOY_MAX_MEMBERS; i++)

			{

			    if (AConvoys[Convoy][Members][i] != -1) // Check if this member-spot is occupied

				{

					// Get the name of the member

					GetPlayerName(AConvoys[Convoy][Members][i], Name, sizeof(Name));

					// Add the membernames to the list

					format(MemberList, 1000, "%s%s\n", MemberList, Name);

				}

			}



			// Show the dialog

			ShowPlayerDialog(playerid, DialogConvoyMembers, DIALOG_STYLE_LIST, "Convoy-members", MemberList, "OK", "Cancel");

		}

		else

		    SendClientMessage(playerid, 0xFF0000FF, "Nu esti membrul / liderul unui convoy");

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}

COMMAND:stats(playerid, params[])

{

	new StatsMsg[1000], Name[24], TitleMsg[128];

	SendAdminText(playerid, "/stats", params);

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Construct the stats

        if (APlayerData[playerid][TruckerLicense] == 1)

		format(StatsMsg, 1000, "%s{FFFFFF}Licenta de tir: {00FF00}Da\n", StatsMsg, APlayerData[playerid][TruckerLicense]);

		else

		format(StatsMsg, 1000, "%s{FFFFFF}Licenta de tir: {00FF00}Nu\n", StatsMsg, APlayerData[playerid][TruckerLicense]);

		if (APlayerData[playerid][BusLicense] == 1)

		format(StatsMsg, 1000, "%s{FFFFFF}Licenta de autobuz: {00FF00}Da\n", StatsMsg, APlayerData[playerid][BusLicense]);

		else

		format(StatsMsg, 1000, "%s{FFFFFF}Licenta de autobuz: {00FF00}Nu\n", StatsMsg, APlayerData[playerid][BusLicense]);

        if (APlayerData[playerid][MarinarLicense] == 1)

		format(StatsMsg, 1000, "%s{FFFFFF}Licenta de Marinar: {00FF00}Da\n", StatsMsg, APlayerData[playerid][MarinarLicense]);

		else

		format(StatsMsg, 1000, "%s{FFFFFF}Licenta de Mainar: {00FF00}Nu\n", StatsMsg, APlayerData[playerid][MarinarLicense]);

		if (APlayerData[playerid][PadurarLicense] == 1)

		format(StatsMsg, 1000, "%s{FFFFFF}Licenta de Padurar: {00FF00}Da\n", StatsMsg, APlayerData[playerid][PadurarLicense]);

		else

		format(StatsMsg, 1000, "%s{FFFFFF}Licenta de Padurar: {00FF00}Nu\n", StatsMsg, APlayerData[playerid][PadurarLicense]);

		format(StatsMsg, 1000, "Kilometers Condusi: {00FF00}%f{FFFFFF}\n", (APlayerData[playerid][StatsMetersDriven] / 1000));

		format(StatsMsg, 1000, "%sFinished trucker jobs: {00FF00}%i{FFFFFF}\n", StatsMsg, APlayerData[playerid][StatsTruckerJobs]);

		format(StatsMsg, 1000, "%sFinished convoy jobs: {00FF00}%i{FFFFFF}\n", StatsMsg, APlayerData[playerid][StatsConvoyJobs]);

		format(StatsMsg, 1000, "%sFinished busdriver routes: {00FF00}%i{FFFFFF}\n", StatsMsg, APlayerData[playerid][StatsBusDriverJobs]);

		format(StatsMsg, 1000, "%sFinished pilot jobs: {00FF00}%i{FFFFFF}\n", StatsMsg, APlayerData[playerid][StatsPilotJobs]);

		format(StatsMsg, 1000, "%sFinished Conducator Tren jobs: {00FF00}%i{FFFFFF}\n", StatsMsg, APlayerData[playerid][StatsSoferJobs]);

		format(StatsMsg, 1000, "%sFinished Marinar jobs: {00FF00}%i{FFFFFF}\n", StatsMsg, APlayerData[playerid][StatsMarinarJobs]);

		format(StatsMsg, 1000, "%sFinished Taxi jobs: {00FF00}%i{FFFFFF}\n", StatsMsg, APlayerData[playerid][StatsTaxiJobs]);

		format(StatsMsg, 1000, "%sFinished Medic jobs: {00FF00}%i{FFFFFF}\n", StatsMsg, APlayerData[playerid][StatsMedicJobs]);

		format(StatsMsg, 1000, "%sFinished Gunoier jobs: {00FF00}%i{FFFFFF}\n", StatsMsg, APlayerData[playerid][StatsGJobs]);

		format(StatsMsg, 1000, "%sFinished Padurar jobs: {00FF00}%i{FFFFFF}\n", StatsMsg, APlayerData[playerid][StatsPadurarJobs]);

		format(StatsMsg, 1000, "%sFinished courier jobs: {00FF00}%i{FFFFFF}\n", StatsMsg, APlayerData[playerid][StatsCourierJobs]);

		format(StatsMsg, 1000, "%sFinished Pizza Boy jobs: {00FF00}%i{FFFFFF}\n", StatsMsg, APlayerData[playerid][StatsPboyJobs]);

		format(StatsMsg, 1000, "%sFinished roadworker jobs: {00FF00}%i{FFFFFF}\n", StatsMsg, APlayerData[playerid][StatsRoadworkerJobs]);

		format(StatsMsg, 1000, "%sMasini reparate: {00FF00}%i{FFFFFF}\n", StatsMsg, APlayerData[playerid][StatsAssistance]);

		format(StatsMsg, 1000, "%sFinished mafia jobs: {00FF00}%i{FFFFFF}\n", StatsMsg, APlayerData[playerid][StatsMafiaJobs]);

		format(StatsMsg, 1000, "%sDelivered stolen mafia-loads: {00FF00}%i{FFFFFF}\n", StatsMsg, APlayerData[playerid][StatsMafiaStolen]);

		format(StatsMsg, 1000, "%sFined players: {00FF00}%i{FFFFFF}\n", StatsMsg, APlayerData[playerid][StatsPoliceFined]);

		format(StatsMsg, 1000, "%sFined players Fbi: {00FF00}%i{FFFFFF}\n", StatsMsg, APlayerData[playerid][StatsFBYFined]);

		format(StatsMsg, 1000, "%sJailed players: {00FF00}%i{FFFFFF}\n", StatsMsg, APlayerData[playerid][StatsPoliceJailed]);

		format(StatsMsg, 1000, "%sJailed players by Fbi: {00FF00}%i{FFFFFF}\n", StatsMsg, APlayerData[playerid][StatsFBYJailed]);

		GetPlayerName(playerid, Name, sizeof(Name));

		format(TitleMsg, 128, "Informatile lui %s:", Name);

		ShowPlayerDialog(playerid, DialogStats, DIALOG_STYLE_MSGBOX, TitleMsg, StatsMsg, "OK", "");

	}

	else

	    return 0;

	return 1;

}

COMMAND:createcamera(playerid, params[])

{

	// Setup local variables

	new Float:x, Float:y, Float:z, Float:Angle, MaxSpeed, file[100], File:PFile, LineForFile[100], Msg[128];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/createcamera", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 5

		if (APlayerData[playerid][PlayerLevel] >= 5)

		{

			if (sscanf(params, "i", MaxSpeed)) SendClientMessage(playerid, 0xFF0000AA, "[RLT]: \"/createcamera <max_speed>\"");

			else

			{

				// Get player's position and facing angle

				GetPlayerPos(playerid, x, y, z);

				GetPlayerFacingAngle(playerid, Angle);

				z = z - 1.0; // Adjust camera Z-coordinate 1m lower than normal (otherwise the camera floats in the air)



				// Move the player a bit, otherwise he could get stuck inside the camera-object

				SetPlayerPos(playerid, x, y + 1.0, z + 1.0);



				// Save the camera to a file

				for (new CamID; CamID < MAX_CAMERAS; CamID++)

				{

					// Check if this index is free

					if (ACameras[CamID][CamSpeed] == 0)

					{

					    // Setup this camera (create the objects and store the data)

                        SetupSpeedCamera(CamID, x, y, z, Angle, MaxSpeed);



					    // Save the file

						format(file, sizeof(file), CameraFile, CamID); // Construct the complete filename for this camera-file



						PFile = fopen(file, io_write); // Open the camera-file for writing



						format(LineForFile, 100, "CamX %f\r\n", x);

						fwrite(PFile, LineForFile); // And save it to the file

						format(LineForFile, 100, "CamY %f\r\n", y);

						fwrite(PFile, LineForFile); // And save it to the file

						format(LineForFile, 100, "CamZ %f\r\n", z);

						fwrite(PFile, LineForFile); // And save it to the file

						format(LineForFile, 100, "CamAngle %f\r\n", Angle);

						fwrite(PFile, LineForFile); // And save it to the file

						format(LineForFile, 100, "CamSpeed %i\r\n", MaxSpeed);

						fwrite(PFile, LineForFile); // And save it to the file



						fclose(PFile); // Close the file



						// Let the player know he created a new camera

						format(Msg, 128, "You've created a speed-camera with ID: %i", CamID);

						SendClientMessage(playerid, 0x00FF00FF, Msg);



						// Exit the function

						return 1;

					}

				}



				// In case all camera-slots are occupied (100 camera's have been created already), let the player know about it

				format(Msg, 128, "{FF0000}You cannot create more than %i speedcamera's", MAX_CAMERAS);

				SendClientMessage(playerid, 0xFFFFFFFF, Msg);

			}

		}

		else

		    return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// This command allows you to delete a speedcamera

COMMAND:delcamera(playerid, params[])

{

	// Setup local variables

	new file[100], Msg[128];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/delcamera", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 5

		if (APlayerData[playerid][PlayerLevel] >= 5)

		{

				// Loop through all camera's

			for (new CamID; CamID < MAX_CAMERAS; CamID++)

			{

				// Check if this index is used

				if (ACameras[CamID][CamSpeed] != 0)

				{

					// Check if the player is in range of the camera

					if (IsPlayerInRangeOfPoint(playerid, 5.0, ACameras[CamID][CamX], ACameras[CamID][CamY], ACameras[CamID][CamZ]))

					{

					    // Delete the file

						format(file, sizeof(file), CameraFile, CamID); // Construct the complete filename for this camera-file

						if (fexist(file)) // Make sure the file exists

							fremove(file); // Delete the file



						// Delete both camera objects

					    DestroyObject(ACameras[CamID][CamObj2]);

						Delete3DTextLabel(ACameras[CamID][LabelID]);

						// Also clear the data from memory

					    ACameras[CamID][CamX] = 0.0;

					    ACameras[CamID][CamY] = 0.0;

					    ACameras[CamID][CamZ] = 0.0;

					    ACameras[CamID][CamAngle] = 0.0;

					    ACameras[CamID][CamSpeed] = 0;

                        ACameras[CamID][CamObj2] = 0;



						// Let the player know he deleted a camera

						format(Msg, 128, "You've deleted speed-camera %i", CamID);

						SendClientMessage(playerid, 0x00FF00FF, Msg);



						// Exit the function

						return 1;

					}

				}

			}



			// In case the player wasn't near a speedcamera, inform him about it

			SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}You must be near a speedcamera to delete it");

		}

		else

		    return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}

// This command ports a player to the player who executed the command

COMMAND:get(playerid, params[])

{

	// Setup local variables

	new OtherPlayer, Float:x, Float:y, Float:z, PortMsg[128], IntID, WorldID, Name[24];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/get", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 1

		if (APlayerData[playerid][PlayerLevel] >= 1)

		{

			if (sscanf(params, "u", OtherPlayer)) SendClientMessage(playerid, 0xFF0000AA, "[RLT]: \"/get <OtherPlayer>\"");

			else

			{

				// Check if that other player is online

				if (IsPlayerConnected(OtherPlayer))

				{

					// Get the name of the other player

					GetPlayerName(OtherPlayer, Name, sizeof(Name));

					// Get the location of the player

					GetPlayerPos(playerid, x, y, z);

					IntID = GetPlayerInterior(playerid);

					WorldID = GetPlayerVirtualWorld(playerid);

					// Port the other player to this player

					SetPlayerVirtualWorld(OtherPlayer, WorldID);

					SetPlayerInterior(OtherPlayer, IntID);

					SetPlayerPos(OtherPlayer, x, y, z + 3.0);

					// Let the player know about it

					format(PortMsg, 128, "{00FF00}You have ported {FFFF00}%s{00FF00} to your location", Name);

					SendClientMessage(playerid, 0xFFFFFFFF, PortMsg);

				}

				else

				    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}That player isn't online");

			}

		}

		else

		    return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}

// This command deleted all vehicles that are spawned using /car, /plane, /bike, /trailer

COMMAND:cleanupcars(playerid, params[])

{

	// Setup local variables

	new CarsDeleted, Msg[128];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/cleanupcars", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 3

		if (APlayerData[playerid][PlayerLevel] >= 3)

		{

		    // Loop through all vehicles

		    for (new vid; vid < 2000; vid++)

		    {

				// Check if this vehicle exists (check the model), otherwise all empty slots are processed as well

				if (AVehicleData[vid][Model] != 0)

				{

					// Check if the vehicle is NOT a static vehicle

					if (AVehicleData[vid][StaticVehicle] == false)

					{

						// Check if the vehicle is NOT owned by anybody (this leaves all vehicles spawned with /car, /trailer, /plane)

						if (AVehicleData[vid][Owned] == false)

						{

							// Count the cars that have been deleted

							CarsDeleted++;

							// Delete the vehicle and clear the data

							DestroyVehicle(vid);

							AVehicleData[vid][Owned] = false;

							AVehicleData[vid][Owner] = 0;

							AVehicleData[vid][Model] = 0;

							AVehicleData[vid][PaintJob] = 0;

							for (new i; i < 14; i++)

							    AVehicleData[vid][Components][i] = 0;

							AVehicleData[vid][SpawnX] = 0.0;

							AVehicleData[vid][SpawnY] = 0.0;

							AVehicleData[vid][SpawnZ] = 0.0;

							AVehicleData[vid][SpawnRot] = 0.0;

							AVehicleData[vid][BelongsToHouse] = 0;

						}

					}

				}

		    }



			// Let the player know how many vehicles have been cleaned up

			format(Msg, 128, "{00FF00}Total number of vehicles cleaned up: {FFFF00}%i", CarsDeleted);

			SendClientMessage(playerid, 0xFFFFFFFF, Msg);

		}

		else

		    return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// This command allows the player to call for assistance

COMMAND:assist(playerid, params[])

{

	// Setup local variables

	new bool:AssistOnline = false, Msg[128], Name[24];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/assist", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Get the player's name

		GetPlayerName(playerid, Name, sizeof(Name));

		// Preset the message that needs to be sent to assistance players

		format(Msg, 128, "{00FF00}Jucatorul {FFFF00}%s{00FF00} are nevoie de un mecanic, du-te si ajuta-l !", Name);



		// Check if there is at least one assistance player online

		for (new i; i < MAX_PLAYERS; i++)

		{

			// Check if this player is connected

			if (IsPlayerConnected(i))

			{

				// Check if this player is assistance class

				if (APlayerData[i][PlayerClass] == ClassAssistance)

				{

					// Set the flag to indicate that at least one assistance player is online

				    AssistOnline = true;

				    // Send the assistance player a message to inform him who needs assistance

				    SendClientMessage(i, 0xFFFFFFFF, Msg);

				}

			}

		}



		// Check if there is at least one assistance player online

		if (AssistOnline == true)

		{

			// Set yourself as "AssistanceNeeded"

			APlayerData[playerid][AssistanceNeeded] = true;

			// Let the player know he called for assistance

			SendClientMessage(playerid, 0xFFFFFFFF, "{00FF00}Ai chemat un mecanic");

		}

		else // No assistance is online

		{

			// Check if the player is the driver of a vehicle

			if (GetPlayerVehicleSeat(playerid) == 0)

			{

				// Fully repair the vehicle (damage value and bodywork)

				RepairVehicle(GetPlayerVehicleID(playerid));

				// Also re-fuel the vehicle

				AVehicleData[GetPlayerVehicleID(playerid)][Fuel] = MaxFuel;

				// Let the player pay for the repairs and refuel (default $2000)

				RewardPlayer(playerid, -5000, 0);

				// Let the player know he spent $2000 for auto-repair because there were no assistance players online

			    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}Vehiculul tau a fost auto-reparat si i s-a facut automat plinul pentru $5000");

			    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}Deoarece nu este nici un mecanic online.");

			}

		}

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// This command adds nitro to the player's vehicle

COMMAND:nos(playerid, params[])

{

	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/nos", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 1

		if (APlayerData[playerid][PlayerLevel] >= 1)

		{

			// Check if the player is the driver of a vehicle

			if (GetPlayerVehicleSeat(playerid) == 0)

			{

				// Check if the vehicle isn't owned (owned vehicle's need to buy nitro at mod garages)

				if (AVehicleData[GetPlayerVehicleID(playerid)][Owned] == true)

					AddVehicleComponent(GetPlayerVehicleID(playerid), 1010); // Add nitro to the player's vehicle

			}

		}

		else

		    return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// This command let's an admin spectate another player

COMMAND:spec(playerid, params[])

{

	// Setup local variables

	new OtherPlayer, Name[24], Msg[128];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/spec", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 1

		if (APlayerData[playerid][PlayerLevel] >= 3)

		{

			if (sscanf(params, "u", OtherPlayer)) SendClientMessage(playerid, 0xFF0000AA, "[RLT]: \"/spec <OtherPlayer>\"");

			else

			{

				// Check if that other player is online

				if (IsPlayerConnected(OtherPlayer))

				{

					// Get the player's name

					GetPlayerName(OtherPlayer, Name, sizeof(Name));



				    // Turn spectating on

				    TogglePlayerSpectating(playerid, 1);



					// Check if the other player is driving a vehicle

					if (GetPlayerVehicleSeat(OtherPlayer) == -1)

					{

						// The other player is on foot, so spectate him

						PlayerSpectatePlayer(playerid, OtherPlayer);

						SetPlayerInterior(playerid, GetPlayerInterior(OtherPlayer));

						APlayerData[playerid][SpectateID] = OtherPlayer;

						APlayerData[playerid][SpectateType] = ADMIN_SPEC_TYPE_PLAYER;

					}

					else

					{

						// The other player is in a vehicle, so spectate the vehicle

						PlayerSpectateVehicle(playerid, GetPlayerVehicleID(OtherPlayer));

						APlayerData[playerid][SpectateID] = OtherPlayer;

						APlayerData[playerid][SpectateVehicle] = GetPlayerVehicleID(OtherPlayer);

						APlayerData[playerid][SpectateType] = ADMIN_SPEC_TYPE_VEHICLE;

					}



					format(Msg, 128, "{00FF00}Il privesti pe {FFFF00}%s", Name);

					SendClientMessage(playerid, 0xFFFFFFFF, Msg);

				}

				else

				    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}Acest jucator nu este online");

			}

		}

		else

		    return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// This command ends the spectate mode

COMMAND:endspec(playerid, params[])

{

	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/endspec", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 1

		if (APlayerData[playerid][PlayerLevel] >= 3)

		{

			// Check if the player is spectating

			if (GetPlayerState(playerid) == PLAYER_STATE_SPECTATING)

			{

			    TogglePlayerSpectating(playerid, 0);

				APlayerData[playerid][SpectateID] = -1;

				APlayerData[playerid][SpectateVehicle] = -1;

				APlayerData[playerid][SpectateType] = ADMIN_SPEC_TYPE_NONE;

			}

			else

			    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}You are not spectating");

		}

		else

		    return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}







// Lets the player add new businesses

COMMAND:createbusiness(playerid, params[])

{

	// Setup local variables

	new BusinessList[2000];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/createbusiness", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 7

		if (APlayerData[playerid][PlayerLevel] >= 7)

		{

			// Check if the player isn't inside a vehicle

			if (GetPlayerVehicleSeat(playerid) == -1)

			{

				// Construct the list of businesses

				for (new BusType = 1; BusType < sizeof(ABusinessInteriors); BusType++)

				{

				    format(BusinessList, sizeof(BusinessList), "%s%s\n", BusinessList, ABusinessInteriors[BusType][InteriorName]);

				}



				// Let the player choose a business-type via a dialog

				ShowPlayerDialog(playerid, DialogCreateBusSelType, DIALOG_STYLE_LIST, "Alege tipul afacerii:", BusinessList, "Select", "Anulare");

			}

			else

			    SendClientMessage(playerid, 0xFF0000FF, "You can't be inside a vehicle to create a business");

		}

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;
}



// This command lets the player delete a business

COMMAND:delbusiness(playerid, params[])

{

	// Setup local variables

	new file[100], Msg[128];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/delbusiness", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 5

		if (APlayerData[playerid][PlayerLevel] >= 5)

		{

			// Make sure the player isn't inside a vehicle

			if (GetPlayerVehicleID(playerid) == 0)

			{

				// Loop through all player-owned businesses

				for (new BusID = 1; BusID < MAX_BUSINESS; BusID++)

				{

					// Check if the business exists

					if (ABusinessData[BusID][PickupID] != 0)

					{

						// Check if the business has no owner

						if (ABusinessData[BusID][Owned] == false)

						{

							// Check if the player is in range of the business-pickup

							if (IsPlayerInRangeOfPoint(playerid, 2.5, ABusinessData[BusID][BusinessX], ABusinessData[BusID][BusinessY], ABusinessData[BusID][BusinessZ]))

							{

								// Clear all data of the business

	                            ABusinessData[BusID][BusinessName] = 0;

	                            ABusinessData[BusID][BusinessX] = 0.0;

	                            ABusinessData[BusID][BusinessY] = 0.0;

	                            ABusinessData[BusID][BusinessZ] = 0.0;

	                            ABusinessData[BusID][BusinessType] = 0;

	                            ABusinessData[BusID][BusinessLevel] = 0;

	                            ABusinessData[BusID][LastTransaction] = 0;

	                            ABusinessData[BusID][Owned] = false;

	                            ABusinessData[BusID][Owner] = 0;

								// Destroy the mapicon, 3DText and pickup for the house

								DestroyDynamicPickup(ABusinessData[BusID][PickupID]);

								DestroyDynamicMapIcon(ABusinessData[BusID][MapIconID]);

								DestroyDynamic3DTextLabel(ABusinessData[BusID][DoorText]);

	                            ABusinessData[BusID][PickupID] = 0;

	                            ABusinessData[BusID][MapIconID] = 0;



								// Delete the business-file

								format(file, sizeof(file), BusinessFile, BusID); // Construct the complete filename for this business-file

								if (fexist(file)) // Make sure the file exists

									fremove(file); // Delete the file



								// Also let the player know he deleted the business

								format(Msg, 128, "{00FF00}Ai sters afacerea cu ID: {FFFF00}%i", BusID);

								SendClientMessage(playerid, 0xFFFFFFFF, Msg);



								// Exit the function

								return 1;

							}

						}

					}

				}



				// There was no house in range, so let the player know about it

				SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}Nicio afacerere prin preajma care poate fi stearsa");

			}

			else

			    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}You can't be inside a vehicle to delete a business");

		}

		else

		    return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// This command lets the player buy a business when he's standing in range of a business that isn't owned yet

COMMAND:buybus(playerid, params[])

{

	// Setup local variables

	new Msg[128], BusType;



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/buybus", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Make sure the player isn't inside a vehicle

		if (GetPlayerVehicleID(playerid) == 0)

		{

			// Check if the player is near a business-pickup

			for (new i = 1; i < sizeof(ABusinessData); i++)

			{

				// Check if this business is created (it would have a valid pickup in front of the door)

				if (ABusinessData[i][PickupID] != 0)

				{

					// Check if the player is in range of the business-pickup

					if (IsPlayerInRangeOfPoint(playerid, 2.5, ABusinessData[i][BusinessX], ABusinessData[i][BusinessY], ABusinessData[i][BusinessZ]))

					{

					    // Check if the business isn't owned yet

					    if (ABusinessData[i][Owned] == false)

					    {

							// Get the type of business

							BusType = ABusinessData[i][BusinessType];

					        // Check if the player can afford this type of business business

					        if (APlayerData[playerid][PlayerMoney] >= ABusinessInteriors[BusType][BusPrice])

					            Business_SetOwner(playerid, i); // Give ownership of the business to the player

					        else

					            SendClientMessage(playerid, 0xFF0000FF, "You cannot afford this business"); // The player cannot afford this business

					    }

					    else

					    {

					        // Let the player know that this business is already owned by a player

							format(Msg, 128, "{FF0000}Aceasta afacere este detinuta de {00FF00}%s{FFFFFF}", ABusinessData[i][Owner]);

							SendClientMessage(playerid, 0xFFFFFFFF, Msg);

					    }



						// The player was in range of a business-pickup, so stop searching for the other business pickups

					    return 1;

					}

				}

				else

				    return 1; // If there are no more houses (no more pickup-id's found), stop searching

			}



			// All businesses have been processed, but the player wasn't in range of any business-pickup, let him know about it

			SendClientMessage(playerid, 0xFF0000FF, "To buy a business, you have to be near a business-pickup");

		}

		else

		    SendClientMessage(playerid, 0xFF0000FF, "You can't buy a business when you're inside a vehicle");

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// This command opens a menu when you're inside your business to allow to access the options of your business

COMMAND:busmenu(playerid, params[])

{

	// Setup local variables

	new OptionsList[200], DialogTitle[200];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/busmenu", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player is inside a business

		if (APlayerData[playerid][CurrentBusiness] != 0)

		{

			format(DialogTitle, sizeof(DialogTitle), "Selecteaza optiunea pentru %s", ABusinessData[APlayerData[playerid][CurrentBusiness]][BusinessName]);



			format(OptionsList, sizeof(OptionsList), "%sSchimba numele afacerii\n", OptionsList);

			format(OptionsList, sizeof(OptionsList), "%sImbunatateste afacerea\n", OptionsList);

			format(OptionsList, sizeof(OptionsList), "%sPreia castigurile afacerii\n", OptionsList);

			format(OptionsList, sizeof(OptionsList), "%sVinde afacerea\n", OptionsList);

			format(OptionsList, sizeof(OptionsList), "%sIesi din afacere\n", OptionsList);

			// Show the businessmenu

			ShowPlayerDialog(playerid, DialogBusinessMenu, DIALOG_STYLE_LIST, DialogTitle, OptionsList, "Select", "Cancel");

		}

		else

		    SendClientMessage(playerid, 0xFF0000FF, "Nu esti intr-o afacere");

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// This command teleports you to your selected business

COMMAND:gobus(playerid, params[])

{

	// Setup local variables

	new BusinessList[1000], BusID, BusType, Earnings;



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/gobus", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player is not jailed

		if (APlayerData[playerid][PlayerJailed] == 0)

		if (APlayerData[playerid][JobStarted] == false)

		{

			// Check if the player has a wanted level of less than 3

			if (GetPlayerWantedLevel(playerid) < 3)

			{

				// Check if the player is not inside a vehicle

				if (GetPlayerVehicleID(playerid) == 0)

				{

					// Ask to which business the player wants to port

					for (new i; i < MAX_BUSINESSPERPLAYER; i++)

					{

						// Get the business-id

					    BusID = APlayerData[playerid][Business][i];



						// Check if this businessindex is occupied

						if (BusID != 0)

						{

							// Get the business-type

							BusType = ABusinessData[BusID][BusinessType];

							Earnings = (BusinessTransactionTime - ABusinessData[BusID][LastTransaction]) * ABusinessInteriors[BusType][BusEarnings] * ABusinessData[BusID][BusinessLevel];

							format(BusinessList, 1000, "%s{00FF00}%s{FFFFFF} (castig: $%i)\n", BusinessList, ABusinessData[BusID][BusinessName], Earnings);

						}

						else

							format(BusinessList, 1000, "%s{FFFFFF}%s{FFFFFF}\n", BusinessList, "Empty business-slot");

					}

					ShowPlayerDialog(playerid, DialogGoBusiness, DIALOG_STYLE_LIST, "Choose the business to go to:", BusinessList, "Select", "Anulare");

				}

				else

					SendClientMessage(playerid, 0xFF0000FF, "You need to be on-foot to port to your business");

			}

			else

			    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}You cannot use /gobus when you're wanted");

		}

		else

		    SendClientMessage(playerid, 0xFF0000FF, "You cannot use /gobus when you're in jail");

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// Mutes a player (he cannot talk anymore)

COMMAND:mute(playerid, params[])

{

	// Setup local variables

	new Msg[128], Name[24], AdminName[24], Reason[128], OtherPlayer;



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/mute", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 1

		if (APlayerData[playerid][PlayerLevel] >= 1)

		{

			if (sscanf(params, "us[128]", OtherPlayer, Reason)) SendClientMessage(playerid, 0xFF0000AA, "[RLT]: \"/mute <OtherPlayer> <Reason>\"");

			else

			{

				// Check if the otherplayer is online

				if (IsPlayerConnected(OtherPlayer))

				{

					// Get the player-names

					GetPlayerName(playerid, AdminName, sizeof(AdminName));

					GetPlayerName(OtherPlayer, Name, sizeof(Name));

					// Mute the other player

					APlayerData[OtherPlayer][Muted] = true;

					// Let the other player know that he has been muted

					format(Msg, 128, "{FF0000}Ai primit mut de la {FFFF00}%s {FF0000}deoarece {FFFF00}%s", AdminName, Reason);

					SendClientMessage(OtherPlayer, 0xFFFFFFFF, Msg);

					// Let the admin know who he has muted

					format(Msg, 128, "{00FF00}You have muted {FFFF00}%s", Name);

					SendClientMessage(playerid, 0xFFFFFFFF, Msg);

					// Save the player-stats

					PlayerFile_Save(OtherPlayer);

				}

				else

				    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}That player isn't online");

			}

		}

		else

		    return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// Un-mutes a player (he cannot talk anymore)

COMMAND:unmute(playerid, params[])

{

	// Setup local variables

	new Msg[128], Name[24], AdminName[24], OtherPlayer;



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/unmute", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 1

		if (APlayerData[playerid][PlayerLevel] >= 1)

		{

			if (sscanf(params, "u", OtherPlayer)) SendClientMessage(playerid, 0xFF0000AA, "[RLT]: \"/unmute <OtherPlayer>\"");

			else

			{

				// Check if the otherplayer is online

				if (IsPlayerConnected(OtherPlayer))

				{

					// Get the player-names

					GetPlayerName(playerid, AdminName, sizeof(AdminName));

					GetPlayerName(OtherPlayer, Name, sizeof(Name));

					// Un-mute the other player

					APlayerData[OtherPlayer][Muted] = false;

					// Let the other player know that he has been un-muted

					format(Msg, 128, "{FF0000}You have been un-muted by {FFFF00}%s", AdminName);

					SendClientMessage(OtherPlayer, 0xFFFFFFFF, Msg);

					// Let the admin know who he has un-muted

					format(Msg, 128, "{00FF00}You have un-muted {FFFF00}%s", Name);

					SendClientMessage(playerid, 0xFFFFFFFF, Msg);

					// Save the player-stats

					PlayerFile_Save(OtherPlayer);

				}

				else

				    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}That player isn't online");

			}

		}

		else

		    return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// Let's the admins see which players are still muted

COMMAND:mutes(playerid, params[])

{

	// Setup local variables

	new PlayerList[1000], Name[24];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/mutes", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 1

		if (APlayerData[playerid][PlayerLevel] >= 1)

		{

			// Loop through all players

			for (new i; i < MAX_PLAYERS; i++)

			{

				// Check if that player is online

				if (IsPlayerConnected(i))

				{

				    if (APlayerData[i][Muted] == true)

					{

						// Get the player's name

						GetPlayerName(i, Name, sizeof(Name));

						// Add his name and ID to the list

						format(PlayerList, sizeof(PlayerList), "%s%s (ID: %i)\n", PlayerList, Name, i);

					}

				}

			}



			// Show the list of muted players to the admin

			if (strlen(PlayerList) != 0)

				ShowPlayerDialog(playerid, DialogNoResponse, DIALOG_STYLE_LIST, "Muted players:", PlayerList, "OK", "Cancel");

			else

			    SendClientMessage(playerid, 0xFFFFFFFF, "{00FF00}There are no muted players");

		}

		else

		    return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}

// Transfer money to another player

COMMAND:givecash(playerid, params[])

{

	// Setup local variables

	new Msg[128], Name[24], OtherName[24], OtherPlayer, Money;



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/givecash", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		if (sscanf(params, "ui", OtherPlayer, Money)) SendClientMessage(playerid, 0xFF0000AA, "[RLT]: \"/givecash <OtherPlayer> <Money>\"");

		else

		{

			// Check if the otherplayer is online

			if (IsPlayerConnected(OtherPlayer))

			{

				// Get the player-names

				GetPlayerName(playerid, Name, sizeof(Name));

				GetPlayerName(OtherPlayer, OtherName, sizeof(OtherName));



				// Check if the money has a positive value (to prevent stealing money using negative values)

				if (Money > 0)

				{

					// Check if the player has enough money

					if (APlayerData[playerid][PlayerMoney] >= Money)

					{

						// Transfer the money

						RewardPlayer(playerid, -Money, 0);

						RewardPlayer(OtherPlayer, Money, 0);

						// Let the other player know that he has received money

						format(Msg, 128, "{00FF00}Ai primit{FFFF00}$%i{00FF00} de la {FFFF00}%s", Money, Name);

						SendClientMessage(OtherPlayer, 0xFFFFFFFF, Msg);

						// Let the player know he gave money to somebody else

						format(Msg, 128, "{00FF00}Ai Dat {FFFF00}$%i{00FF00} la {FFFF00}%s", Money, OtherName);

						SendClientMessage(playerid, 0xFFFFFFFF, Msg);

						// Save the player-stats

						PlayerFile_Save(playerid);

						PlayerFile_Save(OtherPlayer);

					}

					else

					    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}You don't have enough money");

				}

				else

				    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}You must use values higher than 0");

			}

			else

			    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}That player isn't online");

		}

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// Respawns the given vehicle

COMMAND:respawn(playerid, params[])

{

	// Setup local variables

	new vid, Msg[128];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/respawn", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 1

		if (APlayerData[playerid][PlayerLevel] >= 1)

		{

			if (sscanf(params, "i", vid)) SendClientMessage(playerid, 0xFF0000AA, "[RLT]: \"/respawn <Vehicle-id>\"");

			else

			{

				// Check if the vehicle-id is valid

				if ((vid > 0) && (vid < 2000))

				{

					// Check if the vehicle exists

					if (AVehicleData[vid][Model] != 0)

					{

					    // Force the vehicle to respawn

						SetVehicleToRespawn(vid);

						// Let the player know he respawned the vehicle

						format(Msg, 128, "{00FF00}You've respawned vehicle {FFFF00}%i", vid);

						SendClientMessage(playerid, 0xFFFFFFFF, Msg);

					}

				}

				else

				    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}You have to use a vehicle-id between 1 and 1999");

			}

		}

		else

		    return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// Creates a spikestrip (can only be used by police players)

COMMAND:spike(playerid, params[])

{

	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/spike", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player if a police player

		if (APlayerData[playerid][PlayerClass] == ClassPolice)

		{

			// Check if the player is on foot

			if (GetPlayerVehicleSeat(playerid) == -1)

			{

				// Try to create a spikestrip

				SpikeStrip_Create(playerid);

			}

			else

			    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}You must be on foot to place a spikestrip");

		}

		else

			return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// This command ejects a player from his vehicle

COMMAND:eject(playerid, params[])

{

	// Setup local variables

	new Name[24], AdminName[24], Msg[128], OtherPlayer;



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/eject", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 2

		if (APlayerData[playerid][PlayerLevel] >= 2)

		{

			if (sscanf(params, "u", OtherPlayer)) SendClientMessage(playerid, 0xFF0000AA, "[RLT]: \"/eject <OtherPlayer>\"");

			else

			{

			    // Check if the player is logged in

				if (APlayerData[OtherPlayer][LoggedIn] == true)

				{

					// Check if the other player is driving a vehicle

					if (GetPlayerVehicleSeat(OtherPlayer) != -1)

					{

						// Get the names of the players

						GetPlayerName(playerid, AdminName, sizeof(AdminName));

						GetPlayerName(OtherPlayer, Name, sizeof(Name));

						// Eject the player from the vehicle

						RemovePlayerFromVehicle(OtherPlayer);

						// Let the player know he's been ejected from his vehicle

						format(Msg, 128, "{FF0000}You've been ejected from your vehicle by {FFFF00}%s", AdminName);

						SendClientMessage(OtherPlayer, 0xFFFFFFFF, Msg);

						// Inform the admin that he ejected the player

						format(Msg, 128, "{00FF00}You've ejected {FFFF00}%s{00FF00} from his vehicle", Name);

						SendClientMessage(playerid, 0xFFFFFFFF, Msg);

					}

					else

					    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}That player isn't inside a vehicle");

				}

				else

				    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}That player isn't connected");

			}

		}

		else

			return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// This command lets you talk only to players of the same class

COMMAND:say(playerid, params[])

{

	// Setup local variables

	new Name[24], Msg[128], Message[128];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/say", params);



	// Get the player's name

	GetPlayerName(playerid, Name, sizeof(Name));



	if (APlayerData[playerid][Muted] == false)

	{

		if (sscanf(params, "s[128]", Message)) SendClientMessage(playerid, 0xFF0000AA, "[RLT]: \"/say <Your Message>\"");

		else

		{

			// Loop through all players

			for (new i; i < MAX_PLAYERS; i++)

			{

			    // Check if the player is logged in

				if (APlayerData[i][LoggedIn] == true)

				{

				    // Check if the other player has the same class

				    if (APlayerData[i][PlayerClass] == APlayerData[playerid][PlayerClass])

				    {

						format(Msg, 128, "{B0B0B0}%s said: {FFFFFF}%s", Name, Message);

						SendClientMessage(i, 0xFFFFFFFF, Msg);

				    }

				}

			}

		}

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}

// Clamp an owned vehicle (remove it completely)

COMMAND:clamp(playerid, params[])

{

	// Setup local variables

	new vid, Reason[128], HouseID, HouseOwner, Name[24], AdminName[24], Msg[128];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/clamp", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 5

		if (APlayerData[playerid][PlayerLevel] >= 6)

		{

			if (sscanf(params, "is[128]", vid, Reason)) SendClientMessage(playerid, 0xFF0000AA, "[RLT]: \"/clamp <vehicleid> <reason>\"");

			else

			{

			    // Get the HouseID to which this vehicle belongs

				HouseID = AVehicleData[vid][BelongsToHouse];



				// Check if the vehicle belongs to a house

				if (HouseID != 0)

				{

					//Also set the new location of the vehicle inside the KACC Military fuels hangar

					AVehicleData[vid][SpawnX] = 233.23;

					AVehicleData[vid][SpawnY] = 1872.56;

					AVehicleData[vid][SpawnZ] = 55.38;

					AVehicleData[vid][SpawnRot] = 60.0;



					// Search all the players to see who owns the house

					for (new i; i < MAX_PLAYERS; i++)

					{

						// Loop through all the houses this player owns

						for(new j; j < MAX_HOUSESPERPLAYER; j++)

						{

						    // Check if the player owns this house

							if (APlayerData[i][Houses][j] == HouseID)

							{

							    // Store the houseowner

							    HouseOwner = i;



								// Find the CarSlot where this vehicle exists

								for (new CarSlot; CarSlot < 10; CarSlot++)

								{

									// Check if the vehicle is stored in this carslot

									if (AHouseData[HouseID][VehicleIDs][CarSlot] == vid)

									{

										vid = House_ReplaceVehicle(HouseID, CarSlot); // Re-create the vehicle at the KACC Military fuels hangar

										// Set the vehicle as clamped (clamping needs to be done after re-creating the vehice, otherwise the wrong id can be clamped)

										AVehicleData[vid][Clamped] = true;

									}

								}



								break;

							}

						}

					}



					// Get the name of the admin and owner of the house

					GetPlayerName(playerid, AdminName, sizeof(AdminName));

					GetPlayerName(HouseOwner, Name, sizeof(Name));



					// Let the admin know who's vehicle he deleted

					format(Msg, 128, "{00FF00}You've clamped a vehicle that was owned by {FFFF00}%s", Name);

					SendClientMessage(playerid, 0xFFFFFFFF, Msg);

					// Let the player know who deleted his vehicle

					format(Msg, 128, "{FF0000}A vehicle you owned was clamped by admin {FFFF00}%s", AdminName);

					SendClientMessage(HouseOwner, 0xFFFFFFFF, Msg);

					format(Msg, 128, "{FF0000}It belongs to house: {FFFF00}%s", AHouseData[HouseID][HouseName]);

					SendClientMessage(HouseOwner, 0xFFFFFFFF, Msg);

					format(Msg, 128, "{FF0000}Reason: {FFFF00}%s", Reason);

					SendClientMessage(HouseOwner, 0xFFFFFFFF, Msg);

					// Save the player's datafile (and his houses/businesses/vehicles)

					PlayerFile_Save(HouseOwner);

				}

				else

				    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}That vehicle doesn't belong to a player, you cannot clamp it");

			}

		}

		else

		    return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// This command can be used to unclamp all your vehicles at once

COMMAND:unclamp(playerid, params[])

{

	// Setup local variables

	new HouseID, vid, ClampedVehicles, UnclampPrice, Msg[128];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/unclamp", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Loop through all vehicles owned by this player

		for (new HouseSlot; HouseSlot < MAX_HOUSESPERPLAYER; HouseSlot++)

		{

			// Get the HouseID that exists on this index

			HouseID = APlayerData[playerid][Houses][HouseSlot];



			// check if this house-slot is used

			if (HouseID != 0)

			{

				// Loop through all vehicles assigned to this house

				for (new CarSlot; CarSlot < 10; CarSlot++)

				{

					// Get the vehicle-id of the vehicle in this carslot

					vid = AHouseData[HouseID][VehicleIDs][CarSlot];



					// Check if this carslot is used

					if (vid != 0)

					{

						// Check if this vehicle is clamped

						if (AVehicleData[vid][Clamped] == true)

						    ClampedVehicles++; // Count the clamped vehicles

					}

				}

			}

		}



		// Check if there were any clamped vehicles

		if (ClampedVehicles > 0)

		{

			// Calculate the price to unclamp all the player's vehicles

			UnclampPrice = ClampedVehicles * UnclampPricePerVehicle;



			// Construct the message to inform the player how many vehicles have been clamped and how much it costs to un-clamp them

			format(Msg, 128, "You have %i clamped vehicles, it will cost you $%i to unclamp them", ClampedVehicles, UnclampPrice);

		    // Show a dialog that informs the player how many vehicles have been clamped and how much it costs to un-clamp them

			ShowPlayerDialog(playerid, DialogUnclampVehicles, DIALOG_STYLE_MSGBOX, TXT_AreYouSure, Msg, "Unclamp", TXT_DialogButtonCancel);

		}

		else

		    SendClientMessage(playerid, 0xFFFFFFFF, "{00FF00}You don't have any clamped vehicles");

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// This command displays the rules of the server

COMMAND:rules(playerid, params[])

{

	// Setup local variables

	new Msg[2000];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/rules", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Construct the rules

		format(Msg, 2000, "%s1. Nu se injura pe chat veti primi mute\n", Msg);

		format(Msg, 2000, "%s2. Nu se cere admin de la admini, Daca cereti puteti lua mute sau ban\n", Msg);

		format(Msg, 2000, "%s3. Nu se cere bani scor de la admini,Daca cereti puteti lua mute sau ban\n", Msg);

		format(Msg, 2000, "%s4. Nu folositi Hakuri daca veti folosi veti lua ban kick automat de la servar sau de la un admin\n", Msg);

		format(Msg, 2000, "%s5. Nu cereti Vip\n", Msg);

		format(Msg, 2000, "%s6. Nu faceti spam\n", Msg);

		format(Msg, 2000, "%s7. Nu furati masina cuiva fara un motiv bun\n", Msg);

		format(Msg, 2000, "%s8. Nu faceti abuz de comezi\n", Msg);

		format(Msg, 2000, "%s9. Daca cineva va injura faceti poza (f8) si puneti pe forum\n", Msg);

		format(Msg, 2000, "%s10. Forum: http://forum.4gametech.com\n", Msg);

		format(Msg, 2000, "%s11. ---------------Spor La joc-----------\n",Msg);

	    // Show a dialog that shows the rules

		ShowPlayerDialog(playerid, DialogRules, DIALOG_STYLE_MSGBOX, "Regulile serverului:", Msg, "Accept", TXT_DialogButtonCancel);

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}





// Report a player for breaking the rules

COMMAND:report(playerid, params[])

{

	// Setup local variables

	new OtherPlayer, Name[24], Reason[128], Msg[128];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/report", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		if (sscanf(params, "us[128]", OtherPlayer, Reason)) SendClientMessage(playerid, 0xFF0000AA, "[RLT]: \"/report <OtherPlayer> <Your report>\"");

		else

		{

		    // Check if that other player is logged in

		    if (APlayerData[OtherPlayer][LoggedIn] == true)

		    {

				// Send the report to all admins and add the report to the report-list so admins can review it

				SendReportToAdmins(OtherPlayer, Reason);



				// Get the name of the offender

				GetPlayerName(OtherPlayer, Name, sizeof(Name));

				// Let the player know he reported the other player

				format(Msg, 128, "{00FF00}You've reported {FFFF00}%s", Name);

				SendClientMessage(playerid, 0xFFFFFFFF, Msg);

			}

			else

			    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}That player isn't connected");

		}

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// Lets the admins see the list of reports

COMMAND:rep(playerid, params[])

{

	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/rep", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 1

		if (APlayerData[playerid][PlayerLevel] >= 1)

		{

			// Add the first report to the list (if it exists)

			if (AReports[0][ReportUsed] == true)

			    format(ReportList, 5000, "%s: %s\n", AReports[0][ReportName], AReports[0][ReportReason]);



			// Construct the report-dialog

			for (new i = 1; i < 50; i++)

			{

				// Check if the ReportID has been used already

				if (AReports[i][ReportUsed] == true)

				{

				    format(ReportList, 5000, "%s%s: %s\n", ReportList, AReports[i][ReportName], AReports[i][ReportReason]);

				}

			}



			// Show all the reports

			ShowPlayerDialog(playerid, DialogReports, DIALOG_STYLE_LIST, "Reports list:", ReportList, "OK", "Cancel");

		}

		else

		    return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// Enables the trucker to overload himself

COMMAND:overload(playerid, params[])

{

	// Setup local variables

	new vModel, bool:ValidOverLoad = false, Float:x, Float:y, Float:z, Name[24], Msg[128];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/overload", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the playeris a trucker

		if (APlayerData[playerid][PlayerClass] == ClassTruckDriver)

		{

			// Check if he has already started a job

			if (APlayerData[playerid][JobStarted] == true)

			{

				// Check if the player has already loaded his load

				if (APlayerData[playerid][JobStep] == 2)

				{

					// Check if the player isn't overloaded already

					if (APlayerData[playerid][Overloaded] == false)

					{

						// Get the coordinates of the loading point

						x = ALocations[APlayerData[playerid][JobLoc1]][LocX];

						y = ALocations[APlayerData[playerid][JobLoc1]][LocY];

						z = ALocations[APlayerData[playerid][JobLoc1]][LocZ];



					    // Check if the player is still near the loading point

					    if (IsPlayerInRangeOfPoint(playerid, 25.0, x, y, z))

					    {

							// Get the vehicle-model of the player's vehicle

							vModel = GetVehicleModel(APlayerData[playerid][VehicleID]);



							// Check if the trucker is driving a trucking vehicle that can be overloaded

							switch (vModel)

							{

								case VehicleFlatbed, VehicleDFT30: ValidOverLoad = true; // Flatbed and DFT-30 can be overloaded

								case VehicleLineRunner, VehicleTanker, VehicleRoadTrain:

								{

									switch (GetVehicleModel(APlayerData[playerid][TrailerID]))

									{

										case VehicleTrailerCargo, VehicleTrailerCargo2, VehicleTrailerOre: ValidOverLoad = true; // Cargo and ore trailer can be overloaded

									}

								}

							}



							// Check if the vehicle is valid for overloading

							if (ValidOverLoad == true)

							{

								// Set overloaded for this player to True

							    APlayerData[playerid][Overloaded] = true;

							    // Add 2 to the player's wanted level

							    SetPlayerWantedLevel(playerid, GetPlayerWantedLevel(playerid) + 2);

							    // Let the player know he has been overloaded now

							    SendClientMessage(playerid, 0xFFFFFFFF, "{00FF00}You have overloaded your truck, watch out for the police");

								// Inform the police this trucker is overloaded

								GetPlayerName(playerid, Name, sizeof(Name));

								format(Msg, 128, "{00FF00}Trucker {FFFF00}%s{00FF00} is overloaded, pursue and fine him", Name);

								Police_SendMessage(Msg);

							}

							else

							    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}Your vehicle cannot be overloaded");

						}

						else

						    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}You must be near the loading point to overload your truck");

					}

					else

					    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}You are overloaded already");

				}

				else

				    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}You must load your truck first");

			}

			else

			    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}You haven't started a job yet");

		}

		else

			return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// This command resets a player's money, score and stats to 0 (if chosen)

COMMAND:resetplayer(playerid, params[])

{

	// Setup local variables

	new Name[24], AdminName[24], Reason[128], Msg[128], OtherPlayer, ClearMoney, ClearScore, ClearStats;



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/resetplayer", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 5

		if (APlayerData[playerid][PlayerLevel] >= 5)

		{

			if (sscanf(params, "uiiis[128]", OtherPlayer, ClearMoney, ClearScore, ClearStats, Reason)) SendClientMessage(playerid, 0xFF0000AA, "[RLT]: \"/resetplayer <OtherPlayer> <Money (0/1)> <Score (0/1)> <Stats (0/1)> <Reason>\"");

			else

			{

			    // Check if the other player is logged in

				if (APlayerData[OtherPlayer][LoggedIn] == true)

				{

					// Check if there is at least one parameter given to be cleared, otherwise exit the command

					if ((ClearMoney + ClearScore + ClearStats) == 0)

						return 1;



					// Get the names of both players

					GetPlayerName(playerid, AdminName, sizeof(AdminName));

					GetPlayerName(OtherPlayer, Name, sizeof(Name));



					// Reset the other player's money to 0

					if (ClearMoney == 1)

					{

						APlayerData[OtherPlayer][PlayerMoney] = 0;

						format(Msg, 128, "{FF0000}Your money has been reset by {FFFF00}%s", AdminName);

						SendClientMessage(OtherPlayer, 0xFFFFFFFF, Msg);

						format(Msg, 128, "{00FF00}You've reset the money of player {FFFF00}%s", Name);

						SendClientMessage(playerid, 0xFFFFFFFF, Msg);

					}



					// Reset the other player's score to 0

					if (ClearScore == 1)

					{

						APlayerData[OtherPlayer][PlayerScore] = 0;

						format(Msg, 128, "{FF0000}Your score has been reset by {FFFF00}%s", AdminName);

						SendClientMessage(OtherPlayer, 0xFFFFFFFF, Msg);

						format(Msg, 128, "{00FF00}You've reset the score of player {FFFF00}%s", Name);

						SendClientMessage(playerid, 0xFFFFFFFF, Msg);

					}



					// Reset the other player's stats to 0

					if (ClearStats == 1)

					{

						APlayerData[OtherPlayer][StatsTruckerJobs] = 0;

						APlayerData[OtherPlayer][StatsConvoyJobs] = 0;

						APlayerData[OtherPlayer][StatsBusDriverJobs] = 0;

						APlayerData[OtherPlayer][StatsPilotJobs] = 0;

						APlayerData[OtherPlayer][StatsSoferJobs] = 0;

						APlayerData[OtherPlayer][StatsMarinarJobs] = 0;

						APlayerData[OtherPlayer][StatsTaxiJobs] = 0;

						APlayerData[OtherPlayer][StatsMedicJobs] = 0;

						APlayerData[OtherPlayer][StatsGJobs] = 0;

						APlayerData[OtherPlayer][StatsMafiaJobs] = 0;

						APlayerData[OtherPlayer][StatsMafiaStolen] = 0;

						APlayerData[OtherPlayer][StatsPoliceFined] = 0;

						APlayerData[OtherPlayer][StatsFBYFined] = 0;

						APlayerData[OtherPlayer][StatsPoliceJailed] = 0;

						APlayerData[OtherPlayer][StatsFBYJailed] = 0;

						APlayerData[OtherPlayer][StatsCourierJobs] = 0;

						APlayerData[OtherPlayer][StatsPboyJobs] = 0;

						APlayerData[OtherPlayer][StatsAssistance] = 0;

						APlayerData[OtherPlayer][StatsRoadworkerJobs] = 0;

						APlayerData[OtherPlayer][StatsMetersDriven] = 0.0;

						format(Msg, 128, "{FF0000}Your stats have been reset by {FFFF00}%s", AdminName);

						SendClientMessage(OtherPlayer, 0xFFFFFFFF, Msg);

						format(Msg, 128, "{00FF00}You've reset the stats of player {FFFF00}%s", Name);

						SendClientMessage(playerid, 0xFFFFFFFF, Msg);

					}



					// Let the other player know the reason too

					format(Msg, 128, "{FF0000}Reason: {FFFF00}%s", Reason);

					SendClientMessage(OtherPlayer, 0xFFFFFFFF, Msg);



					// Save the other player's account

					PlayerFile_Save(OtherPlayer);

				}

				else

				    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}That player isn't connected");

			}

		}

		else

			return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// This command searches every house and business that the player owns and restores the data for it in the player's account

COMMAND:fixplayer(playerid, params[])

{

	// Setup local variables

	new Name[24], AdminName[24], Msg[128], OtherPlayer;



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/fixplayer", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 5

		if (APlayerData[playerid][PlayerLevel] >= 5)

		{

			if (sscanf(params, "u", OtherPlayer)) SendClientMessage(playerid, 0xFF0000AA, "[RLT]: \"/fixplayer <OtherPlayer>\"");

			else

			{

			    // Check if the other player is logged in

				if (APlayerData[OtherPlayer][LoggedIn] == true)

				{

					// Get the names of both players

					GetPlayerName(playerid, AdminName, sizeof(AdminName));

					GetPlayerName(OtherPlayer, Name, sizeof(Name));



					// Clear the houses and businesses that the player owns right now

					for (new i; i < MAX_HOUSESPERPLAYER; i++)

					    APlayerData[OtherPlayer][Houses][i] = 0;



					for (new i; i < MAX_BUSINESSPERPLAYER; i++)

					    APlayerData[OtherPlayer][Business][i] = 0;



					// Now search through all houses and re-add them to the player

					for (new HouseID = 1; HouseID < MAX_HOUSES; HouseID++)

						if (AHouseData[HouseID][Owned] == true) // Check if the house is owned by somebody

							if (strcmp(AHouseData[HouseID][Owner], Name, false) == 0) // Check if the player is the owner of the house

							{

								for (new i; i < MAX_HOUSESPERPLAYER; i++) // Loop through all houses the player owns

								    if (APlayerData[OtherPlayer][Houses][i] == 0) // Check if the houseslot is free

								    {

										APlayerData[OtherPlayer][Houses][i] = HouseID; // Store the HouseID

										break; // Stop searching for more free slots

								    }

							}



					// Now search through all businesses and re-add them to the player

					for (new BusID = 1; BusID < MAX_BUSINESS; BusID++)

						if (ABusinessData[BusID][Owned] == true) // Check if the business is owner by someone

							if (strcmp(ABusinessData[BusID][Owner], Name, false) == 0) // Check if the player is the owner of the business

							{

								for (new i; i < MAX_BUSINESSPERPLAYER; i++) // Loop through all businesses the player owns

								    if (APlayerData[OtherPlayer][Business][i] == 0) // Check if the businessslot is free

								    {

										APlayerData[OtherPlayer][Business][i] = BusID; // Store the BusID

										break; // Stop searching for more free slots

								    }

							}



					// Let the other player know his property has been restored

					format(Msg, 128, "{00FF00}Your property has been restored by: {FFFF00}%s", AdminName);

					SendClientMessage(OtherPlayer, 0xFFFFFFFF, Msg);



					// Save the other player's account

					PlayerFile_Save(OtherPlayer);

				}

				else

				    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}That player isn't connected");

			}

		}

		else

			return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// This command sets a skin for the player

COMMAND:setskin(playerid, params[])

{

	// Setup local variables

	new Msg[128], Skin;



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/setskin", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 4

		if (APlayerData[playerid][PlayerLevel] >= 4)

		{

			if (sscanf(params, "i", Skin)) SendClientMessage(playerid, 0xFF0000AA, "[RLT]: \"/setskin <skin-id (0-299)>\"");

			else

			{

				// Check if the player entered a valid skin-id

				if ((Skin >= 0) && (Skin <= 299))

				{

				    // Set the skin for the player

				    SetPlayerSkin(playerid, Skin);

					// Let the other player know the reason too

					format(Msg, 128, "{00FF00}You've chosen skin-id: {FFFF00}%i", Skin);

					SendClientMessage(playerid, 0xFFFFFFFF, Msg);

				}

				else

					SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}Invalid skin-id, you can only use skins 0-299");

			}

		}

		else

			return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// Bans a player by his ip

COMMAND:ipban(playerid, params[])

{

	// Setup local variables

	new PlayerToBan, Reason[128], Msg[128], Name[24], AdminName[24];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/ipban", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 3

		if (APlayerData[playerid][PlayerLevel] >= 3)

		{

			if (sscanf(params, "us[128]", PlayerToBan, Reason))

				SendClientMessage(playerid, 0xFF0000AA, "[RLT]: \"/ipban <PlayerToBan> <Reason>\"");

			else

			{

				if (IsPlayerConnected(PlayerToBan))

				{

					// Get the names of the player and the admin who executed the ban

					GetPlayerName(playerid, AdminName, sizeof(AdminName));

					GetPlayerName(PlayerToBan, Name, sizeof(Name));



					// Inform the player about his ban

					format(Msg, 128, "{FF0000}You have been ip-banned permanently by {FFFF00}%s", AdminName);

					SendClientMessage(PlayerToBan, 0xFFFFFFFF, Msg);

					format(Msg, 128, "{FF0000}Reason: {FFFF00}%s", Reason);

					SendClientMessage(PlayerToBan, 0xFFFFFFFF, Msg);



					// Ban the player with a reason

					BanEx(PlayerToBan, Reason);



					// Inform everybody else which player was ip-banned

					format(Msg, 128, "{808080}%s %s has ip-banned {FFFF00}%s", AdminLevelName[APlayerData[playerid][PlayerLevel]], AdminName, Name);

					SendClientMessageToAll(0xFFFFFFFF, Msg);

				}

			}

		}

		else

		    return 0;

	}

	else

	    return 0;



	return 1;

}

// Sets the score of another player

COMMAND:setscore(playerid, params[])

{

	// Setup local variables

	new Msg[128], Name[24], OtherName[24], OtherPlayer, pScore;



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/setscore", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 6

		if (APlayerData[playerid][PlayerLevel] >= 6)

		{

			if (sscanf(params, "ui", OtherPlayer, pScore)) SendClientMessage(playerid, 0xFF0000AA, "[RLT]: \"/setscore <OtherPlayer> <Score>\"");

			else

			{

				// Check if the otherplayer is online

				if (IsPlayerConnected(OtherPlayer))

				{

					// Get the player-names

					GetPlayerName(playerid, Name, sizeof(Name));

					GetPlayerName(OtherPlayer, OtherName, sizeof(OtherName));



					// Set the other player's score

					APlayerData[OtherPlayer][PlayerScore] = pScore;

					// Let the other player know that his score has been changed

					format(Msg, 128, "{00FF00}Your score has been set to {FFFF00}%i{00FF00} by {FFFF00}%s", pScore, Name);

					SendClientMessage(OtherPlayer, 0xFFFFFFFF, Msg);

					// Let the player know he has set the score of the other player

					format(Msg, 128, "{00FF00}You've set the score of {FFFF00}%s{00FF00} to {FFFF00}%i", OtherName, pScore);

					SendClientMessage(playerid, 0xFFFFFFFF, Msg);

					// Save the other player's account

					PlayerFile_Save(OtherPlayer);

				}

				else

				    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}That player isn't online");

			}

		}

		else

		    return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// Allows the player to setup a bank account, login to his bank account, or use his bank account after he logged in to his bank account

COMMAND:bank(playerid, params[])

{

	// Setup local variables

	new file[100], Name[24];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/bank", params);



    // Get the playername

	format(Name, sizeof(Name), APlayerData[playerid][PlayerName]);

	// Construct the complete filename for this player's bank-account

	format(file, sizeof(file), BankFile, Name);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player doesn't have a bank account

		if (!fexist(file))

		{

			// Ask for a password to setup his bank account

			ShowPlayerDialog(playerid, DialogBankPasswordRegister, DIALOG_STYLE_INPUT, "Enter password", "Please enter a password to register your bank account:", TXT_DialogButtonSelect, TXT_DialogButtonCancel);

		}

		else // The player has a bank account

		{

			// If the player hasn't logged in to his bank account yet

			if (APlayerData[playerid][BankLoggedIn] == false)

			{

				// Ask for the password to login to his bank account

				ShowPlayerDialog(playerid, DialogBankPasswordLogin, DIALOG_STYLE_INPUT, "Enter password", "Please enter your password to login to your bank account:", TXT_DialogButtonSelect, TXT_DialogButtonCancel);

			}

			else // The player has logged in to his bank account already

			{

			    // Show the main bank menu dialog

				ShowBankMenu(playerid);

			}

		}

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// This command lists all help-items for which the player can get information about it

COMMAND:help(playerid, params[])

{

	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/help", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Create the dialog that lists all help-items

        HelpList_Create(playerid);

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// This command allows you to change your password for logging in

COMMAND:changepassword(playerid, params[])

{

	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/changepassword", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Show the dialog where the player must enter his old password

		ShowPlayerDialog(playerid, DialogOldPassword, DIALOG_STYLE_INPUT, "Enter old password:", "Enter your old password here:", "OK", "Cancel");

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



// This command opens a menu where you can choose neons lights for your vehicle

COMMAND:neon(playerid, params[])

{

	// Setup local variables

	new OptionsList[200], DialogTitle[200];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/neon", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player is the driver of a vehicle

		if (GetPlayerVehicleSeat(playerid) == 0)

		{

			format(DialogTitle, sizeof(DialogTitle), "Select neon lights:");



			format(OptionsList, sizeof(OptionsList), "%sPolice lights\n", OptionsList);

			format(OptionsList, sizeof(OptionsList), "%sRed lights\n", OptionsList);

			format(OptionsList, sizeof(OptionsList), "%sBlue lights\n", OptionsList);

			format(OptionsList, sizeof(OptionsList), "%sGreen lights\n", OptionsList);

			format(OptionsList, sizeof(OptionsList), "%sYellow lights\n", OptionsList);

			format(OptionsList, sizeof(OptionsList), "%sPink lights\n", OptionsList);

			format(OptionsList, sizeof(OptionsList), "%sWhite lights\n", OptionsList);

			format(OptionsList, sizeof(OptionsList), "%sRemove neons\n", OptionsList);

			// Show the neon menu

			ShowPlayerDialog(playerid, DialogNeon, DIALOG_STYLE_LIST, DialogTitle, OptionsList, "Select", "Cancel");

		}

		else

		    SendClientMessage(playerid, 0xFF0000FF, "You're not the driver of a vehicle");

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}

CMD:freeze(playerid,params[])

{
    if(APlayerData[playerid][PlayerLevel] < 1)
    {
        new id;
        if(sscanf(params,"u",id)) return SendClientMessage(playerid,0xFF0000AA,"[RLT]: /freeze [ID / Nume]");
        if(!IsPlayerConnected(id)) return SendClientMessage(playerid,0xFF0000AA,"[RLT]: ID / Nume invalid");
        TogglePlayerControllable(id,0);
        SendClientMessage(playerid,0xFF0000AA,"Ai fost inghetat de catre un admin");
    }
    return 1;
}

CMD:unfreeze(playerid,params[])

{
    if(APlayerData[playerid][PlayerLevel] < 1)
    {
        new id;
        if(sscanf(params,"u",id)) return SendClientMessage(playerid,0xFF0000AA,"[RLT]: /unfreeze [ID / Nume]");
        if(!IsPlayerConnected(id)) return SendClientMessage(playerid,0xFF0000AA,"[RLT]: ID / Nume invalid");
        TogglePlayerControllable(id,1);
        SendClientMessage(playerid,0xFF0000AA,"Ai fost dezghetat de catre un admin");
    }
    return 1;
}

CMD:slap(playerid, params[])

{

 

    SendAdminText(playerid, "/slap", params);

    {

      new ID;

      if(APlayerData[playerid][PlayerLevel] < 3) return SendClientMessage(playerid, -1, "you are not adm.");

      if(sscanf(params, "u", ID)) return SendClientMessage(playerid, -1, "Use: /slap [ID]");

      new Float:Pos[3];

      GetPlayerPos(ID, Pos[0], Pos[1], Pos[2]);

      SetPlayerPos(ID, Pos[0], Pos[1], Pos[2]+10);

    }

    return 1;

}

CMD:jump(playerid, params[])

{



    SendAdminText(playerid, "/jump", params);

    {

      new ID;

      if(APlayerData[playerid][PlayerLevel] < 5) return SendClientMessage(playerid, -1, "you are not adm.");

      if(sscanf(params, "u", ID)) return SendClientMessage(playerid, -1, "Use: /jump [ID]");

      new Float:Pos[3];

      GetPlayerPos(ID, Pos[0], Pos[1], Pos[2]);

      SetPlayerPos(ID, Pos[0], Pos[1], Pos[2]+30);

    }

    return 1;

}

CMD:fire(playerid, params[])

{

    SendAdminText(playerid, "/fire", params);

    {

      new ID;

      if(APlayerData[playerid][PlayerLevel] < 5) return SendClientMessage(playerid, -1, "you are not adm.");

      if(sscanf(params, "u", ID)) return SendClientMessage(playerid, -1, "Use: /fire [ID]");

	  SendClientMessage(playerid, -1, "Comanda /fire folosita Datele au fost salvate Nu folosi fire fara un motiv bun");

      new Float:Pos[3];

      GetPlayerPos(ID, Pos[0], Pos[1], Pos[2]);

      CreateExplosion(Pos[0], Pos[1], Pos[2], 9, 5.0);

    }

    return 1;

}

CMD:superslap(playerid, params[])

{

    SendAdminText(playerid, "/superslap", params);

    {

      new ID;

      if(APlayerData[playerid][PlayerLevel] < 5) return SendClientMessage(playerid, -1, "You are not adm.");

      if(sscanf(params, "u", ID)) return SendClientMessage(playerid, -1, "Use: /superslap [ID]");

      new Float:Pos[3];

      GetPlayerPos(ID, Pos[0], Pos[1], Pos[2]);

      SetPlayerPos(ID, Pos[0], Pos[1], Pos[2]+1000);

    }

    return 1;

}

CMD:minigun(playerid, params[])

{

   SendAdminText(playerid, "/minigun", params);

   {

     if(APlayerData[playerid][PlayerLevel] < 8) return SendClientMessage(playerid, -1, "Nu Ai Lv 8.");

     GivePlayerWeapon(playerid, 38, 500);

     SendClientMessage(playerid, -1, "Ai Primit un minigun Ha Ha Ha...");

   }

   return 1;

}

COMMAND:ann(playerid, params[])

{

	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/ann", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 2

		if (APlayerData[playerid][PlayerLevel] >= 2)

		{

                        GameTextForAll(params,4000,3);

		}

		else	

                    return 0;	    

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}

CMD:ooc(playerid, params[])

{

    new sendername[MAX_PLAYER_NAME], string[120];

    GetPlayerName(playerid, sendername, sizeof(sendername));

    if(isnull(params)) return SendClientMessage(playerid, 0xFFFFFFF,"Correct [RLT]: /ooc [text]");

    format(string, sizeof(string), "(( %s: %s ))", sendername, params);

	if (APlayerData[playerid][Muted] == false)

    SendClientMessageToAll(0xFFB300C8, string);

    return 1;

}

COMMAND:wantedallzero(playerid, params[])

{

	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/wantedallzero", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 7

		if (APlayerData[playerid][PlayerLevel] >= 6)
		{

			// Loop through all players

			for (new i; i < MAX_PLAYERS; i++)

				if (IsPlayerConnected(i)) // Check if the player is connected

				       SetPlayerWantedLevel(i, 0);



			// Send all players a message to inform them that all players have been healed

			SendClientMessageToAll(0x00FFFFC8, "[Info]{80FF00}Un Admin A Luat Stelele la Toti!");

		}

		else

		    return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}

CMD:getall(playerid,params[])

{

    if (APlayerData[playerid][PlayerLevel] >= 7)

    {

        new Float:x,Float:y,Float:z, interior = GetPlayerInterior(playerid);

        GetPlayerPos(playerid,x,y,z);

        new pCount;

        for(new i = 0; i < MAX_PLAYERS; i++)

            {

                    if(!IsPlayerConnected(i) || i == playerid) continue;

                    pCount++;

                    PlayerPlaySound(i,1057,0.0,0.0,0.0);

					

                    SetPlayerPos(i,x+(playerid/4)+5,y+(playerid/4),z);

                    SetPlayerInterior(i,interior);

            }

		if(pCount == 0) return SendClientMessage(playerid,0xFFFFFFFF,"No players online!");

        SendClientMessageToAll(0xFFFFFFFF,"Toti Playeri au fost Teleportati");

    }

    else return SendClientMessage(playerid,0xFFFFFFFF,"Nu Ai lv 7 Admin pt a folosi aceasta Commanda!");

    return 1;

}

CMD:mosu(playerid, params[])

{

    SetPlayerAttachedObject(playerid, 3, 19065, 2, 0.120000, 0.040000, -0.003500, 0, 100, 100, 1.4, 1.4, 1.4);

	SendClientMessage(playerid, 0xFFB6C1, "HoHoHo");

	return 1;
}

COMMAND:cc(playerid, params[])

{

	SendAdminText(playerid, "/cc", params);

	if (APlayerData[playerid][PlayerLevel] >= 2)

	for(new i=0; i<50; i++) SendClientMessageToAll(-1," ");

	return 1;

}

// Heals all players

COMMAND:armourall(playerid, params[])

{

	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/armourall", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 3

		if (APlayerData[playerid][PlayerLevel] >= 3)

		{

			// Loop through all players

			for (new i; i < MAX_PLAYERS; i++)

				if (IsPlayerConnected(i)) // Check if the player is connected

				       SetPlayerArmour(i, 100.0); // Armour the player



			// Send all players a message to inform them that all players have been healed

			SendClientMessageToAll(0x00FFFFC8, "[Info]{80FF00}Toti Jucatori au primit Armura 100!");

		}

		else

		    return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}

// Restarts the server

COMMAND:restart(playerid, params[])

{

	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/restart", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 7

		if (APlayerData[playerid][PlayerLevel] >= 7)

		{

			// Let everyone know that the server will be restarted in 2 minutes

			GameTextForAll("Server restart in 2 minute!", 5000, 3);

			SendClientMessageToAll(0xA0A0A0, "Server restart in 2 minute!");

			// Start the next timer which warns the players again that server will be restarted in 1 minute

			SetTimer("Timer_Restart_WarnPlayers", 1000 * 60, false);

		}

		else

		    return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}

forward Timer_Restart_WarnPlayers();

public Timer_Restart_WarnPlayers()

{

	// Let everyone know that the server will be restarted in 1 minutes

	GameTextForAll("Server restart in 1 minute!", 5000, 3);

	SendClientMessageToAll(0xA0A0A0, "Server restart in 1 minutes!");

	// Start the next timer

	SetTimer("Timer_Restart_Kick", 1000 * 60, false);

	// Change the hostname of the server and it's password

	SendRconCommand("hostname Pending Restart");

	SendRconCommand("password Delya");



	return 1;

}

forward Timer_Restart_Kick();

public Timer_Restart_Kick()

{

	// Let everyone know that the server is kicking all players before restarting

	GameTextForAll("Server restarting:Reconect!", 5000, 3);

	// Kick all players

	for(new i; i < MAX_PLAYERS; i++)

		Kick(i);

	// Start the next timer that will restart the server

	SetTimer("Timer_Restart_Reboot", 1000 * 5, false);



	return 1;

}

forward Timer_Restart_Reboot();

public Timer_Restart_Reboot()

{

	// Restart the server

	SendRconCommand("exit");

	return 1;

}

COMMAND:cmds(playerid, params[])

{

	// Setup local variables

	new Msg[2000];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/cmds", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Construct the rules max 35

		format(Msg, 2000, "%s{FFFFFF}/cmds - {DD9322}Vezi toate comenzile servarului\n", Msg);
		
		format(Msg, 2000, "%s{FFFFFF}/fineme - {DD9322}Iti seteaza wanted level 0 pentru 500k si 1 scor\n", Msg);

		format(Msg, 2000, "%s{FFFFFF}/vcmds - {DD9322}Arata comezile de la Vip\n", Msg);

		format(Msg, 2000, "%s{FFFFFF}/work - {DD9322}Incepi lucrul\n", Msg);

		format(Msg, 2000, "%s{FFFFFF}/stopwork - {DD9322}Opresti lucrul\n", Msg);

		format(Msg, 2000, "%s{FFFFFF}/admins - {DD9322}Vezi toti admini oline\n", Msg);

		format(Msg, 2000, "%s{FFFFFF}/kill - {DD9322}Te Omori\n", Msg);

		format(Msg, 2000, "%s{FFFFFF}/ooc [Mesaj] - {DD9322}Mesaj colorat\n", Msg);

		format(Msg, 2000, "%s{FFFFFF}/stats - {DD9322}Arata statusul\n", Msg);

		format(Msg, 2000, "%s{FFFFFF}/neon - {DD9322}Pui neoane\n", Msg);

		format(Msg, 2000, "%s{FFFFFF}/mosu - {DD9322}Iti da o caciula de moss\n", Msg);

		format(Msg, 2000, "%s{FFFFFF}/spike - {DD9322}Pui o Capcana [Politia doar]\n", Msg);

		format(Msg, 2000, "%s{FFFFFF}/flip - {DD9322}Pui masina inapoi pe roti\n", Msg);

		format(Msg, 2000, "%s{FFFFFF}/getcar - {DD9322}Iti aduci la tine masina personala\n", Msg);

		format(Msg, 2000, "%s{FFFFFF}/givecash [id] [suma] - {DD9322}Dai bani la o anumita pesoana \n", Msg);

		format(Msg, 2000, "%s{FFFFFF}/gohome - {DD9322}Mergi la casa ta\n", Msg);

		format(Msg, 2000, "%s{FFFFFF}/gobus  - {DD9322}Mergi la afacerea ta\n", Msg);

		format(Msg, 2000, "%s{FFFFFF}/color [1]sau[2] - {DD9322}Vopsesti masina pesonala\n", Msg);

		format(Msg, 2000, "%s{FFFFFF}/enter - {DD9322}Intri in casa sau in afacerea ta\n", Msg);

		format(Msg, 2000, "%s{FFFFFF}/bank - {DD9322}Creezi cont bancar pui sau scoti bani\n", Msg);

		format(Msg, 2000, "%s{FFFFFF}/convoy - {DD9322}Crezi un convoy sau intri in unul\n", Msg);

		format(Msg, 2000, "%s{FFFFFF}/detach - {DD9322}Detasezi remorca\n", Msg);

		format(Msg, 2000, "%s{FFFFFF}/housemenu - {DD9322}Meniu casei cumperi masini etc\n", Msg);

		format(Msg, 2000, "%s{FFFFFF}/busmenu  - {DD9322}Arata meniul afaceri\n", Msg);

		format(Msg, 2000, "%s{FFFFFF}/overload - {DD9322}Incarci dublu\n", Msg);

		format(Msg, 2000, "%s{FFFFFF}/park - {DD9322}Parcheaza masnia\n", Msg);

		format(Msg, 2000, "%s{FFFFFF}/pm <ID><Text> - {DD9322}Dai mesaj privat\n", Msg);

		format(Msg, 2000, "%s{FFFFFF}/changepassword - {DD9322}Iti scimbi parola\n", Msg);

		format(Msg, 2000, "%s{FFFFFF}/assist - {DD9322}Chemi un mechanic\n", Msg);

		format(Msg, 2000, "%s{FFFFFF}/convoycancel - {DD9322}Anulezi convoyul\n", Msg);

		format(Msg, 2000, "%s{FFFFFF}/convoykick [ID] - {DD9322}Dai kick din convoi\n", Msg);

		format(Msg, 2000, "%s{FFFFFF}/convoyleave - {DD9322}Parasesti convoyul\n", Msg);

		format(Msg, 2000, "%s{FFFFFF}/paint [0]&[1]&[2] - {DD9322}Paint superb pt unele masini\n", Msg);

		format(Msg, 2000, "%s{FFFFFF}/reclass - {DD9322}Schimbi clasa\n", Msg);

		format(Msg, 2000, "%s{FFFFFF}/rescue - {DD9322}Te duce la firma\n", Msg);

		format(Msg, 2000, "%s{FFFFFF}/rules - {DD9322}Regulamentul serverului RLT\n", Msg);
		
		format(Msg, 2000, "%s{FFFFFF}/contact - {DD9322}ID-uri de contact fondatori / owneri\n", Msg);
		
		format(Msg, 2000, "%s{FFFFFF}/credits - {DD9322}Lista fondatorilor / ownerilor\n", Msg);



		

	    // Show a dialog that shows the rules

		ShowPlayerDialog(playerid, DialogComezile1, DIALOG_STYLE_MSGBOX, "Comezile Jucatori:", Msg, "Oky", "");

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



COMMAND:giveallgun(playerid, params[]) //Da Arme la toti

{

	SendAdminText(playerid, "/giveallgun", params);

    if(APlayerData[playerid][PlayerLevel] >= 7) {

		new ArmaID, gunname[32], string[150], name[MAX_PLAYER_NAME];

		

		if(sscanf(params,"d",ArmaID)) return SendClientMessage(playerid,0x00FFFFC8,"[RLT]: /giveallgun [weapon id]");

		if(1 > ArmaID > 46) return SendClientMessage(playerid,0x00FFFFC8,"ERROR: Weapons ID is of 1-46!");

        for (new i; i < MAX_PLAYERS; i++)

        {

            GivePlayerWeapon(i,ArmaID,300);

        }

        GetWeaponName(ArmaID,gunname,sizeof(gunname));

		GetPlayerName(playerid, name, sizeof(name));

		format(string,sizeof(string),"[Info] Adminul %s a dat la toti arma %s cu 300 ammo",name,gunname);

		SendClientMessageToAll(0x00FFFFC8,string);

    }

    else SendClientMessage(playerid,0x00FFFFC8,"Nu ai admin lv 7 pentru a folosi aceasta comanda");

    return 1;

}

CMD:givegun(playerid, params[])

{
	if(APlayerData[playerid][PlayerLevel] >= 6)
	{
	    new target, gun, string[128];
		if(sscanf(params, "ud", target, gun))
		{
		    SendClientMessage(playerid, COLOR_GREY, "[RLT]: /givegun <ID/Nume> <ID arma>");
		    return 1;
		}
	 	if(gun < 1 || gun > 47) { SendClientMessage(playerid, COLOR_GREY, "ID-ul armei trebuie sa fie cuprins intre 1 si 47"); return 1; }
	 	if(IsPlayerConnected(target))
		{
		    if(target != INVALID_PLAYER_ID && gun <= 20 || gun >= 22)
			{
                GivePlayerWeapon(target, gun, 50000);
               	format(string, sizeof(string), "Administratorul %s ti-a dat o arma", GetName(playerid));
               	SendClientMessage(target, COLOR_GREY, string);
               	format(string, sizeof(string), "I-ai dat jucatorului %s o arma", GetName(target));
               	SendClientMessage(playerid, COLOR_GREY, string);
            }
   		}
	}
	else
	{
	   	SendClientMessage(playerid, COLOR_GREY, "Nu ai admin lv 6 pentru a utiliza aceasta comanda");
	    return 1;
 	}
	return 1;
}

COMMAND:setvip(playerid, params[])

{

	new OtherPlayer, Level, Msg[128], Name[24], AdminName[24], OldLevel;

	SendAdminText(playerid, "/setvip", params);

	if (APlayerData[playerid][LoggedIn] == true)

	{

		if (APlayerData[playerid][PlayerLevel] >= 8)

		{

			if (sscanf(params, "ui", OtherPlayer, Level)) SendClientMessage(playerid, 0xFF0000AA, "Utilizare: \"/setvip <OtherPlayer> <VipLevel>\"");

			else

			{

				// Check if that other player is online

				if (IsPlayerConnected(OtherPlayer))

				{

				    // Get the old level of the other player

				    OldLevel = APlayerData[OtherPlayer][VPlayerLevel];

					// Get the playername of the admin

					GetPlayerName(playerid, AdminName, sizeof(AdminName));

					// Also get the name of the player that has been promoted

					GetPlayerName(OtherPlayer, Name, sizeof(Name));

					// Store the level of the player

					APlayerData[OtherPlayer][VPlayerLevel] = Level;

					// Let all players know about it

					if (OldLevel != Level)

					{

						// Check if the player has been promoted or demoted

						if (OldLevel < Level)

							format(Msg, 128, "Playerul %s a fost promovat la %s de %s", Name, VLevelName[Level], AdminName);

						if (OldLevel > Level)

							format(Msg, 128, "Playerul %s a primit demote la %s de %s", Name, VLevelName[Level], AdminName);

						SendClientMessageToAll(0x00FF00FF, Msg);

					}

					else

						SendClientMessage(playerid, 0xFF0000FF, "Nivelul playerului nu s-a schimbat");

				}

				else

				    SendClientMessage(playerid, 0xFF0000FF, "Playerul nu este online");

			}

		}

		else

		    return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}

COMMAND:vips(playerid, params[])

{

	// Setup local variables

	new VipList[500], Name[24];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/vips", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Scan through all players

		for (new i; i < MAX_PLAYERS; i++)

		{

			// Check if this player is connected

			if (IsPlayerConnected(i))

			{

				// Get the name of the player

				GetPlayerName(i, Name, sizeof(Name));



				//Check if that player is an admin (using the PlayerLevel)

				if (APlayerData[i][VPlayerLevel] > 0)

				{

					// Add all admin players to the list

					format(VipList, 500, "%s%s: %s (id: %i), Vip-level: %i\n", VipList, VLevelName[APlayerData[i][VPlayerLevel]], Name, i, APlayerData[i][VPlayerLevel]); // Add the name of the admin-player to the list

				}

			}

		}



		// Check if there were admin-names added to the list

		if (strlen(VipList) > 0)

		    ShowPlayerDialog(playerid, DialogVipioline, DIALOG_STYLE_LIST, "Vipi online:", VipList, "OK", "Cancel");

		else

			SendClientMessage(playerid, 0xFF0000FF, "Nu este niciun vip online"); // No admins are online

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}



//if ((APlayerData[playerid][PlayerLevel] >= 1) || (APlayerData[playerid][VPlayerLevel] >= 1))



//Comenzi VIP

COMMAND:vskin(playerid, params[])

{

	// Setup local variables

	new Msg[128], Skin;



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/vskin", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's vip is 1

		if (APlayerData[playerid][VPlayerLevel] >= 2)

		{

			if (sscanf(params, "i", Skin)) SendClientMessage(playerid, 0xFF0000AA, "[RLT]: \"/vskin <skin-id (0-299)>\"");

			else

			{

				// Check if the player entered a valid skin-id

				if ((Skin >= 0) && (Skin <= 299))

				{

				    // Set the skin for the player

				    SetPlayerSkin(playerid, Skin);

					// Let the other player know the reason too

					format(Msg, 128, "{00FF00}Noul tau skin este: {FFFF00}%i", Skin);

					SendClientMessage(playerid, 0xFFFFFFFF, Msg);

				}

				else

					SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}Id skin invalid, poti sa folosesti doar skinurile cu id cuprins intre 1 si 299");

			}

		}

		else

			return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}

CMD:vheal(playerid, params[]) 

{

	if (APlayerData[playerid][VPlayerLevel] < 1) return SendClientMessage(playerid, 0xFF0000FF, "Nu Esti Vip !");

	{

	SetPlayerHealth(playerid, 100.0);

	SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}Ai Primit Viata 100");

	}

	return 1;

}

CMD:vfix(playerid, params[])

{

    if (APlayerData[playerid][VPlayerLevel] < 1) return SendClientMessage(playerid, 0xFF0000FF, "Nu Esti Vip !");

    if(!IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, red, "[ERROR]You are not in a vehicle!");

    RepairVehicle(GetPlayerVehicleID(playerid));

    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);

    SendClientMessage(playerid, green, "Masina ta a fost reparata!");

    return 1;

}

CMD:vfly(playerid, params[])

{

    if (APlayerData[playerid][VPlayerLevel] < 3) return SendClientMessage(playerid, 0xFF0000FF, "Nu Esti Vip !");

    SendClientMessage(playerid,green,"Jetpack Spawned.");

    SetPlayerSpecialAction(playerid, 2);

    return 1;

}

CMD:vtunelv(playerid, params[])

{

   

    if (APlayerData[playerid][VPlayerLevel] < 3) return SendClientMessage(playerid, 0xFF0000FF, "Nu Esti Vip !");

    if(GetPlayerWantedLevel(playerid) >= 1)

        return SendClientMessage(playerid, red, "Esti Cautat De Politie Nu Te Poti Teleporta Acuma.");

    {

        if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)

        {

            new veh = GetPlayerVehicleID(playerid);

            SetVehiclePos(veh, 2386.84, 1034.57,   10.82);

            SetVehicleVirtualWorld(veh, 0);

            LinkVehicleToInterior(veh, 0);

            SetPlayerInterior(playerid, 0);

            SetPlayerVirtualWorld(playerid, 0);

            PutPlayerInVehicle(playerid, veh, 0);

            GameTextForPlayer(playerid,"Ai fost teleportat la Tuning Lv!",4500,3);

        }

        else

        {

            SetPlayerPos(playerid, 2386.84, 1034.57,   10.82);

            SetPlayerInterior(playerid, 0);

            SetPlayerVirtualWorld(playerid, 0);

            GameTextForPlayer(playerid,"Ai fost teleportat la Tuning Lv!",4500,3);

        }

    }

    return 1;

}

CMD:vlicenta(playerid, params[])

{



    if (APlayerData[playerid][VPlayerLevel] < 2) return SendClientMessage(playerid, 0xFF0000FF, "Nu esti vip level 2 !");

    if(GetPlayerWantedLevel(playerid) >= 1)

        return SendClientMessage(playerid, red, "Esti cautat de politie, nu te poti teleporta.");

    {

        if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)

        {

            new veh = GetPlayerVehicleID(playerid);

            SetVehiclePos(veh, -2034.59,  -99.27, 35.16);

            SetVehicleVirtualWorld(veh, 0);

            LinkVehicleToInterior(veh, 0);

            SetPlayerInterior(playerid, 0);

            SetPlayerVirtualWorld(playerid, 0);

            PutPlayerInVehicle(playerid, veh, 0);

            GameTextForPlayer(playerid,"~r~Ai fost teleportat la locul de unde iti iei licenta!",4500,3);

        }

        else

        {

            SetPlayerPos(playerid, -2034.59,  -99.27, 35.16);

            SetPlayerInterior(playerid, 0);

            SetPlayerVirtualWorld(playerid, 0);

            GameTextForPlayer(playerid,"~r~Ai fost teleportat la locul de unde iti iei licenta!",4500,3);

        }

    }

    return 1;

}

CMD:vturn(playerid, params[])

{



    if (APlayerData[playerid][VPlayerLevel] < 3) return SendClientMessage(playerid, 0xFF0000FF, "Nu esti vip level 3 !");

    if(GetPlayerWantedLevel(playerid) >= 1)

        return SendClientMessage(playerid, red, "Esti cautat de politie, nu te poti teleporta.");

    {

        if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)

        {

            new veh = GetPlayerVehicleID(playerid);

            SetVehiclePos(veh, 1538.67, -1343.19,  329.46);

            SetVehicleVirtualWorld(veh, 0);

            LinkVehicleToInterior(veh, 0);

            SetPlayerInterior(playerid, 0);

            SetPlayerVirtualWorld(playerid, 0);

            PutPlayerInVehicle(playerid, veh, 0);

            GameTextForPlayer(playerid,"~r~Ai fost teleportat la Star Tower!",4500,3);

        }

        else

        {

            SetPlayerPos(playerid, 1538.67, -1343.19,  329.46);

            SetPlayerInterior(playerid, 0);

            SetPlayerVirtualWorld(playerid, 0);

            GameTextForPlayer(playerid,"~r~Ai fost teleportat la Star Tower!",4500,3);

        }

    }

    return 1;

}

CMD:vtunesf(playerid, params[])

{



    if (APlayerData[playerid][VPlayerLevel] < 3) return SendClientMessage(playerid, 0xFF0000FF, "Nu Esti Vip !");

    if(GetPlayerWantedLevel(playerid) >= 1)

        return SendClientMessage(playerid, red, "Esti Cautat De Politie Nu Te Poti Teleporta Acuma.");

    {

        if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)

        {

            new veh = GetPlayerVehicleID(playerid);

            SetVehiclePos(veh, -2704.37, 217.21, 4.17);

            SetVehicleVirtualWorld(veh, 0);

            LinkVehicleToInterior(veh, 0);

            SetPlayerInterior(playerid, 0);

            SetPlayerVirtualWorld(playerid, 0);

            PutPlayerInVehicle(playerid, veh, 0);

            GameTextForPlayer(playerid,"Ai fost teleportat la Tuning Sf",4500,3);

        }

        else

        {

            SetPlayerPos(playerid, -2704.37, 217.21, 4.17);

            SetPlayerInterior(playerid, 0);

            SetPlayerVirtualWorld(playerid, 0);

            GameTextForPlayer(playerid,"Ai fost teleportat la Tuning Sf",4500,3);

        }

    }

    return 1;
}

CMD:chilliad(playerid, params[])

{



    if (APlayerData[playerid][VPlayerLevel] < 3) return SendClientMessage(playerid, 0xFF0000FF, "Nu esti un jucator VIP");

    if(GetPlayerWantedLevel(playerid) >= 1)

        return SendClientMessage(playerid, red, "Esti cautat de polite, asa ca nu te poti teleporta.");

    {

        if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)

        {

            new veh = GetPlayerVehicleID(playerid);

            SetVehiclePos(veh, -2335.8875,-1626.1935,483.7057);

            SetVehicleVirtualWorld(veh, 0);

            LinkVehicleToInterior(veh, 0);

            SetPlayerInterior(playerid, 0);

            SetPlayerVirtualWorld(playerid, 0);

            PutPlayerInVehicle(playerid, veh, 0);

            GameTextForPlayer(playerid,"Ai fost teleportat pe muntele Chilliad",4500,3);

        }

        else

        {

            SetPlayerPos(playerid, -2335.8875,-1626.1935,483.7057);

            SetPlayerInterior(playerid, 0);

            SetPlayerVirtualWorld(playerid, 0);

            GameTextForPlayer(playerid,"Ai fost teleportat pe muntele Chilliad",4500,3);

        }

    }

    return 1;

}

CMD:bucuresti(playerid, params[])

{



    if (APlayerData[playerid][VPlayerLevel] < 3) return SendClientMessage(playerid, 0xFF0000FF, "Nu esti un jucator VIP");

    if(GetPlayerWantedLevel(playerid) >= 1)

        return SendClientMessage(playerid, red, "Esti cautat de polite, asa ca nu te poti teleporta.");

    {

        if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)

        {

            new veh = GetPlayerVehicleID(playerid);

            SetVehiclePos(veh, -3607.8901,1849.9470,5.0859);

            SetVehicleVirtualWorld(veh, 0);

            LinkVehicleToInterior(veh, 0);

            SetPlayerInterior(playerid, 0);

            SetPlayerVirtualWorld(playerid, 0);

            PutPlayerInVehicle(playerid, veh, 0);

            GameTextForPlayer(playerid,"Ai fost teleportat la Bucuresti",4500,3);

        }

        else

        {

            SetPlayerPos(playerid, -3607.8901,1849.9470,5.0859);

            SetPlayerInterior(playerid, 0);

            SetPlayerVirtualWorld(playerid, 0);

            GameTextForPlayer(playerid,"Ai fost teleportat la Bucuresti",4500,3);

        }

    }

    return 1;

}

CMD:constanta(playerid, params[])

{



    if (APlayerData[playerid][VPlayerLevel] < 3) return SendClientMessage(playerid, 0xFF0000FF, "Nu esti un jucator VIP");

    if(GetPlayerWantedLevel(playerid) >= 1)

        return SendClientMessage(playerid, red, "Esti cautat de polite, asa ca nu te poti teleporta.");

    {

        if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)

        {

            new veh = GetPlayerVehicleID(playerid);

            SetVehiclePos(veh, -3607.4414,-100.8154,5.2106);

            SetVehicleVirtualWorld(veh, 0);

            LinkVehicleToInterior(veh, 0);

            SetPlayerInterior(playerid, 0);

            SetPlayerVirtualWorld(playerid, 0);

            PutPlayerInVehicle(playerid, veh, 0);

            GameTextForPlayer(playerid,"Ai fost teleportat la Constanta",4500,3);

        }

        else

        {

            SetPlayerPos(playerid, -3607.4414,-100.8154,5.2106);

            SetPlayerInterior(playerid, 0);

            SetPlayerVirtualWorld(playerid, 0);

            GameTextForPlayer(playerid,"Ai fost teleportat la Constanta",4500,3);

        }

    }

    return 1;

}

CMD:cityville(playerid, params[])

{



    if (APlayerData[playerid][VPlayerLevel] < 3) return SendClientMessage(playerid, 0xFF0000FF, "Nu esti un jucator VIP");

    if(GetPlayerWantedLevel(playerid) >= 1)

        return SendClientMessage(playerid, red, "Esti cautat de polite, asa ca nu te poti teleporta.");

    {

        if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)

        {

            new veh = GetPlayerVehicleID(playerid);

            SetVehiclePos(veh, 5464.2964,-1760.3164,8.5993);

            SetVehicleVirtualWorld(veh, 0);

            LinkVehicleToInterior(veh, 0);

            SetPlayerInterior(playerid, 0);

            SetPlayerVirtualWorld(playerid, 0);

            PutPlayerInVehicle(playerid, veh, 0);

            GameTextForPlayer(playerid,"Ai fost teleportat la Cityvile",4500,3);

        }

        else

        {

            SetPlayerPos(playerid, 5464.2964,-1760.3164,8.5993);

            SetPlayerInterior(playerid, 0);

            SetPlayerVirtualWorld(playerid, 0);

            GameTextForPlayer(playerid,"Ai fost teleportat la Cityville",4500,3);

        }

    }

    return 1;

}

CMD:vtunels(playerid, params[])

{



    if (APlayerData[playerid][VPlayerLevel] < 3) return SendClientMessage(playerid, 0xFF0000FF, "Nu Esti Vip !");

    if(GetPlayerWantedLevel(playerid) >= 1)

        return SendClientMessage(playerid, red, "Esti Cautat De Politie, Nu Te Poti Teleporta.");

    {

        if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)

        {

            new veh = GetPlayerVehicleID(playerid);

            SetVehiclePos(veh, 2645.01, -2026.11,   13.54);

            SetVehicleVirtualWorld(veh, 0);

            LinkVehicleToInterior(veh, 0);

            SetPlayerInterior(playerid, 0);

            SetPlayerVirtualWorld(playerid, 0);

            PutPlayerInVehicle(playerid, veh, 0);

            GameTextForPlayer(playerid,"Ai fost teleportat la Tuning Ls",4500,3);

        }

        else

        {

            SetPlayerPos(playerid, 2645.01, -2026.11,   13.54);

            SetPlayerInterior(playerid, 0);

            SetPlayerVirtualWorld(playerid, 0);

            GameTextForPlayer(playerid,"Ai fost teleportat la Tuning Ls",4500,3);

        }

    }

    return 1;

}

CMD:varmour(playerid, params[]) 

{

    if (APlayerData[playerid][VPlayerLevel] < 2) return SendClientMessage(playerid, 0xFF0000FF, "Nu esti vip level 2 !");

	SetPlayerArmour(playerid, 100);

	return 1;

}

CMD:vnos(playerid, params[]) 

{

	if (APlayerData[playerid][VPlayerLevel] < 1) return SendClientMessage(playerid, 0xFF0000FF, "Nu Esti Vip !");

	if(!IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, red, "[ERROR]You must in vehicle to use this command");

    switch(GetVehicleModel( GetPlayerVehicleID(playerid) ))

	{

		case 448,461,462,463,468,471,509,510,521,522,523,581,586,449:

		return SendClientMessage(playerid,red,"[ERROR] You can not tune this vehicle!");

	}

	AddVehicleComponent(GetPlayerVehicleID(playerid), 1010);

	SendClientMessage(playerid, green, "Nos has been added");

	return 1;

}

CMD:vport(playerid, params[])

{

	new pid;

    if (APlayerData[playerid][VPlayerLevel] < 2) return SendClientMessage(playerid, 0xFF0000FF, "Nu Esti Vip !");

	if(sscanf(params,"u",pid)) SendClientMessage(playerid,green,"[RLT]: /vport [Id / Nume]");

	else

	{

	    new Float:X,Float:Y,Float:Z,pint,name[MAX_PLAYER_NAME],name2[MAX_PLAYER_NAME],string[40],string2[39];

	    GetPlayerName(playerid,name,sizeof(name));

	    GetPlayerName(pid,name2,sizeof(name2));

	    GetPlayerPos(pid,X,Y,Z);

	    pint = GetPlayerInterior(pid);

	    SetPlayerPos(playerid,X+1,Y,Z);

	    SetPlayerInterior(playerid,pint);

		format(string,sizeof(string),"[VIP]Te-ai teleportat la %s",name2);

		format(string2,sizeof(string2),"[VIP]%s s-a teleportat la tine",name);

		SendClientMessage(playerid,green,string);

		SendClientMessage(pid,green,string2);

		return 1;

		}

	return 1;

}

CMD:vget(playerid, params[])

{

	new pid;

    if (APlayerData[playerid][VPlayerLevel] < 3) return SendClientMessage(playerid, 0xFF0000FF, "Nu Esti Vip !");

	if(sscanf(params,"u",pid)) SendClientMessage(playerid,green,"[RLT]: /vget [ID]");

	else

	{

	    new Float:X,Float:Y,Float:Z,pint,name[MAX_PLAYER_NAME],name2[MAX_PLAYER_NAME],string[44],string2[45];

	    GetPlayerName(playerid,name,sizeof(name));

	    GetPlayerName(pid,name2,sizeof(name2));

	    GetPlayerPos(playerid,X,Y,Z);

	    pint = GetPlayerInterior(playerid);

	    SetPlayerPos(pid,X+1,Y,Z);

	    SetPlayerInterior(pid,pint);

		format(string,sizeof(string),"[Vip]Ai teleportat pe %s la tine",name2);

		format(string2,sizeof(string2),"Ai fost teleportat la [Vip]%s",name);

		SendClientMessage(playerid,green,string);

		SendClientMessage(pid,green,string2);

		return 1;

		}

	return 1;

}

CMD:vcamera(playerid, params[])

{

    if (APlayerData[playerid][VPlayerLevel] < 2) return SendClientMessage(playerid, 0xFF0000FF, "Nu Esti Vip !");

	for(new i = 0; i < MAX_PLAYERS; i++)

	if(IsPlayerConnected(i))

	GivePlayerWeapon(playerid, 43,50);

	SendClientMessage(playerid, red, "[Vip]Ai Primit O Camera Foto");

    return 1;



}

CMD:velgt(playerid, params[])

{

	if (APlayerData[playerid][VPlayerLevel] < 3) return SendClientMessage(playerid, 0xFF0000FF, "Nu Esti Vip !");

  	AddVehicleComponent(  GetPlayerVehicleID(playerid), 1034 );

	AddVehicleComponent(  GetPlayerVehicleID(playerid), 1038 );

	AddVehicleComponent(  GetPlayerVehicleID(playerid), 1147 );

	AddVehicleComponent(  GetPlayerVehicleID(playerid), 1010 );

	AddVehicleComponent(  GetPlayerVehicleID(playerid), 1073 );

	ChangeVehiclePaintjob(  GetPlayerVehicleID(playerid), 0 );

	PlayerPlaySound( playerid, 1133, 0.0, 0.0, 0.0 );

	return 1;

}

CMD:god(playerid, params[])

{
    //new str3[128];
    new str1[128], str2[128], admin[MAX_PLAYER_NAME], p[MAX_PLAYER_NAME], id, Float: health1, Float:health2;
    if(!IsPlayerAdmin(playerid)) return SendClientMessage(playerid, 0xFF0000AA, "Trebuie sa fii Admin Rcon pentru a folosi aceasta comanda");

//Make yourself god by typing only: /god
    GetPlayerHealth(playerid, health1);
    //format(str3, sizeof(str3), "health: %f.", health1); With these lines I found out that if you set a player's health to 9999~~.0,
    //SendClientMessage(playerid, COLOR_ORANGE, str3);    his health value becomes actually 0.0 and so I got the code working, took me hours, damn.
    if(sscanf(params, "d", id)) //do not change "d" with "u" or in /god [ID] format,
    {                         //you will receive message "ERROR: Player is not connected." even if you enter valid id.
        if (health1==0.0)
        {
        SetPlayerHealth(playerid, 100.0);
        return SendClientMessage(playerid,0x00FF00AA, "Inapoi la mortalitate");
        }

        if (health1>0.0)
        {
        SetPlayerHealth(playerid, 9999999999999999.0);
        return SendClientMessage(playerid, 0x00FF00AA, "Ai viata infinita acum");
        }
    }

//Make a player of your server god with /god [ID]
    if(IsPlayerConnected(id))
    {
        GetPlayerName(playerid, admin, MAX_PLAYER_NAME);
        GetPlayerName(id, p, MAX_PLAYER_NAME);
        GetPlayerHealth(id, health2);

        if (health2>0.0)
        {
            SetPlayerHealth(id, 9999999999999999.0);
            format(str2, sizeof(str2), "You have successfully turned %s into god.", p);
            SendClientMessage(playerid, 0x00FF00AA, str2);
            format(str1, sizeof(str1), "Admin %s has turned you into god!", admin);
            SendClientMessage(id, 0x00FF00AA, str1);
        }

        if (health2==0)
        {
            SetPlayerHealth(id, 100.0);
            format(str2, sizeof(str2), "You have turned god %s into human.", p);
            SendClientMessage(playerid, 0x00FF00AA, str2);
            return SendClientMessage(id, 0x00FF00AA, "Inapoi la mortalitate");
        }
    }
    else SendClientMessage(playerid, 0xFF0000AA, "ERROR: Player is not connected.");
    return 1;
}

COMMAND:rcmds(playerid, params[])

{

	// Setup local variables

	new Msg[2000];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/rcmds", params);



	// Check if the player has logged in
	
	if(!IsPlayerAdmin(playerid))

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Construct the rules max 35

		format(Msg, 2000, "%s{FF9900}Rcon: {66FF00}/god [ID] - {6666FF}Dai viata infinita unui jucator sau tie\n", Msg);











	    // Show a dialog that shows the rules

		ShowPlayerDialog(playerid, DialogComezile2, DIALOG_STYLE_MSGBOX, "Comenzile de Rcon:", Msg, "Ok", "Cancel");

	}

	else

	    return 0;

	return 1;
}

COMMAND:acmds(playerid, params[])

{

	// Setup local variables

	new Msg[2000];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/acmds", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Construct the rules max 35

		format(Msg, 2000, "%s{FF9900}Level 1: {66FF00}/acmds1 - {6666FF}Comenzi admin level 1\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 2: {66FF00}/acmds2 - {6666FF}Comenzi admin level 2\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 3: {66FF00}/acmds3 - {6666FF}Comenzi admin level 3\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 4: {66FF00}/acmds4 - {6666FF}Comenzi admin level 4\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 5: {66FF00}/acmds5 - {6666FF}Comenzi admin level 5\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 6: {66FF00}/acmds6 - {6666FF}Comenzi admin level 6\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 7: {66FF00}/acmds7 - {6666FF}Comenzi admin level 7\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 8: {66FF00}/acmds8 - {6666FF}Comenzi admin level 8\n", Msg);

		

		

		

		



	    // Show a dialog that shows the rules

		ShowPlayerDialog(playerid, DialogComezile2, DIALOG_STYLE_MSGBOX, "Comezile de Admin de pe server:", Msg, "Ok", "Cancel");

	}

	else

	    return 0;

	return 1;
}

COMMAND:acmds1(playerid, params[])

{

	// Setup local variables

	new Msg[2000];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/acmds1", params);



	// Check if the player has logged in

	if (APlayerData[playerid][PlayerLevel] >= 1)

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Construct the rules max 35

		format(Msg, 2000, "%s{FF9900}Level 1: {66FF00}/ac - {6666FF}Vorbesti pe chatul administratorilor\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 1: {66FF00}/car - {6666FF}Spawnezi  o Masina\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 1: {66FF00}/bike - {6666FF}Spawnezi  o Motocicleta\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 1: {66FF00}/plane - {6666FF}Spawnezi  un Elicopter\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 1: {66FF00}/boat - {6666FF}Spawnezi  o Barca\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 1: {66FF00}/ann - {6666FF}Dai un anunt\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 1: {66FF00}/rep - {6666FF}Vezi reporturile\n", Msg);
		
		format(Msg, 2000, "%s{FF9900}Level 1: {66FF00}/amess - {6666FF}Dai un mesaj pe chat ca administrator\n", Msg);
		
		format(Msg, 2000, "%s{FF9900}Level 1: {66FF00}/freeze - {6666FF}Ingheti un jucator\n", Msg);
		
		format(Msg, 2000, "%s{FF9900}Level 1: {66FF00}/unfreeze - {6666FF}Dezgheti un jucator\n", Msg);











	    // Show a dialog that shows the rules

		ShowPlayerDialog(playerid, DialogComezile2, DIALOG_STYLE_MSGBOX, "Comenzi Admin level 1:", Msg, "Ok", "Cancel");

	}

	else

	    return 0;

	return 1;
}

COMMAND:acmds2(playerid, params[])

{

	// Setup local variables

	new Msg[2000];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/acmds2", params);



	// Check if the player has logged in

	if (APlayerData[playerid][PlayerLevel] >= 2)

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Construct the rules max 35

		format(Msg, 2000, "%s{FF9900}Level 2: {66FF00}/healall - {6666FF}Setezi viata 100 tuturor jucatorilor\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 2: {66FF00}/kick [Id/Nume] - {6666FF}Dai afara de pe server un jucator\n", Msg);
		
		format(Msg, 2000, "%s{FF9900}Level 2: {66FF00}/eject [Id/Nume] - {6666FF}Dai afara din masina un jucator\n", Msg);
		
		format(Msg, 2000, "%s{FF9900}Level 2: {66FF00}/cc - {6666FF}Stergi chatul\n", Msg);
		
		format(Msg, 2000, "%s{FF9900}Level 2: {66FF00}/ann - {6666FF}Dai un anunt\n", Msg);
		
		format(Msg, 2000, "%s{FF9900}Level 2: {66FF00}/porthouse [ID] - {6666FF}Te teleportezi la o casa\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 2: {66FF00}/portbus [ID] - {6666FF}Dai afara de pe server un jucator\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 2: {66FF00}/properties - {6666FF}Vezi proprietatile unui jucator\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 2: {66FF00}/propertyid - {6666FF}Vezi id-ul afacerii\n", Msg);
		
		format(Msg, 2000, "%s{6666FF}+ Comenzile /acmds1\n", Msg);











	    // Show a dialog that shows the rules

		ShowPlayerDialog(playerid, DialogComezile2, DIALOG_STYLE_MSGBOX, "Comenzi Admin level 2:", Msg, "Ok", "Cancel");

	}

	else

	    return 0;

	return 1;
}

COMMAND:acmds3(playerid, params[])

{

	// Setup local variables

	new Msg[2000];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/acmds3", params);



	// Check if the player has logged in

	if (APlayerData[playerid][PlayerLevel] >= 3)

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Construct the rules max 35

		format(Msg, 2000, "%s{FF9900}Level 3: {66FF00}/ban [ID] [Zile] [Ore] [Minute] [Motiv] - {6666FF}Banezi un jucator\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 3: {66FF00}/armourall - {6666FF}Setezi armura 100 la toti\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 3: {66FF00}/repairall - {6666FF}Repari toate masinile de pe server\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 3: {66FF00}/loc - {6666FF}Te teleportezi intr-un loc\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 3: {66FF00}/fly - {6666FF}Iti spawnezi jetpack\n", Msg);
		
		format(Msg, 2000, "%s{FF9900}Level 3: {66FF00}/caroption - {6666FF}Afisezi optiunile masinii\n", Msg);
		
		format(Msg, 2000, "%s{FF9900}Level 3: {66FF00}/cleanupcars - {6666FF}Stergi vehiculele spawnate de catre admini\n", Msg);

		format(Msg, 2000, "%s{6666FF}+ Comenzile /acmds1 + /acmds2\n", Msg);










	    // Show a dialog that shows the rules

		ShowPlayerDialog(playerid, DialogComezile2, DIALOG_STYLE_MSGBOX, "Comenzi Admin level 3:", Msg, "Ok", "Cancel");

	}

	else

	    return 0;

	return 1;
}

COMMAND:acmds4(playerid, params[])

{

	// Setup local variables

	new Msg[2000];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/acmds4", params);



	// Check if the player has logged in

	if (APlayerData[playerid][PlayerLevel] >= 4)

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Construct the rules max 35

		format(Msg, 2000, "%s{FF9900}Level 4: {66FF00}/weather - {6666FF}Schimbi vremea\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 4: {66FF00}/setskin [ID (0-299)]- {6666FF}Iti schimb aspectul ( Skinul )\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 4: {66FF00}/giveallgun [ID] - {6666FF}Dai o arma tuturor\n", Msg);
		
		format(Msg, 2000, "%s{FF9900}Level 4: {66FF00}/saveloc - {6666FF}Iti salvezi locatia\n", Msg);
		
		format(Msg, 2000, "%s{FF9900}Level 4: {66FF00}/spec - {6666FF}Te uiti la un jucator\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 4: {66FF00}/endspec - {6666FF}Anulezi comanda /spec\n", Msg);

		format(Msg, 2000, "%s{6666FF}+ Comenzile /acmds1 + /acmds2 + /acmds3\n", Msg);
		








	    // Show a dialog that shows the rules

		ShowPlayerDialog(playerid, DialogComezile2, DIALOG_STYLE_MSGBOX, "Comenzi Admin level 4:", Msg, "Ok", "Cancel");

	}

	else

	    return 0;

	return 1;
}

COMMAND:acmds5(playerid, params[])

{

	// Setup local variables

	new Msg[2000];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/acmds5", params);



	// Check if the player has logged in

	if (APlayerData[playerid][PlayerLevel] >= 5)

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Construct the rules max 35

		format(Msg, 2000, "%s{FF9900}Level 5: {66FF00}/cash [Suma] - {6666FF}Iti dai bani\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 5: {66FF00}/wanted [ID] [Stele]- {6666FF}Setezi wanted levelul unui jucator\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 5: {66FF00}/saveloc [ID] [Nume]- {6666FF}Iti salvezi locatia\n", Msg);
		
		format(Msg, 2000, "%s{FF9900}Level 5: {66FF00}/object [Model] [X] [Y] [Z] [Angle] - {6666FF}Spawnezi un obiect\n", Msg);
		
		format(Msg, 2000, "%s{FF9900}Level 5: {66FF00}/vehicle [Model] [X] [Y] [Z] [Angle] [SpawnDelay] - {6666FF}Spawnezi un vehicul \n", Msg);
		
		format(Msg, 2000, "%s{FF9900}Level 5: {66FF00}/anunt [Mesaj] - {6666FF}Dai un anunt ( cu optiuni avansate )\n", Msg);

		format(Msg, 2000, "%s{6666FF}+ Comenzile /acmds1 + /acmds2 + /acmds3 + /acmds4\n", Msg);









	    // Show a dialog that shows the rules

		ShowPlayerDialog(playerid, DialogComezile2, DIALOG_STYLE_MSGBOX, "Comenzi Admin level 5:", Msg, "Ok", "Cancel");

	}

	else

	    return 0;

	return 1;
}

COMMAND:acmds6(playerid, params[])

{

	// Setup local variables

	new Msg[2000];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/acmds6", params);



	// Check if the player has logged in

	if (APlayerData[playerid][PlayerLevel] >= 6)

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Construct the rules max 35

		format(Msg, 2000, "%s{FF9900}Level 6: {66FF00}/rangeban [ID/Nume] [Motiv] - {6666FF}Dai ban pe ip si nume unui jucator\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 6: {66FF00}/clamp - {6666FF}Ridici o masina\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 6: {66FF00}/cadou - {6666FF}Dai un cadou in valoare de 1kk si 5 scor tuturor\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 6: {66FF00}/ipban [ID/Nume] [Motiv] - {6666FF}Banezi ip-ul unui jucator\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 6: {66FF00}/setscore [Id/Nume] [Scor] - {6666FF}Setezi scorul unui jucator\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 6: {66FF00}/wantedallzero - {6666FF}Setezi wanted level-ul tuturor la 0 \n", Msg);
		
		format(Msg, 2000, "%s{FF9900}Level 6: {66FF00}/givegun - {6666FF}Dai o arma unui jucator\n", Msg);

		format(Msg, 2000, "%s{6666FF}+ Comenzile /acmds1 + /acmds2 + /acmds3 + /acmds4 + /acmds5\n", Msg);









	    // Show a dialog that shows the rules

		ShowPlayerDialog(playerid, DialogComezile2, DIALOG_STYLE_MSGBOX, "Comenzi Admin level 6:", Msg, "Ok", "Cancel");

	}

	else

	    return 0;

	return 1;
}

COMMAND:acmds7(playerid, params[])

{

	// Setup local variables

	new Msg[2000];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/acmds7", params);



	// Check if the player has logged in

	if (APlayerData[playerid][PlayerLevel] >= 7)

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Construct the rules max 35

		format(Msg, 2000, "%s{FF9900}Level 7: {66FF00}/createhouse [Pret] [Level Maxim] - {6666FF}Creezi o casa\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 7: {66FF00}/delhouse - {6666FF}Stergi o casa\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 7: {66FF00}/unban [Nume]- {6666FF}Dai unban unui jucator\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 7: {66FF00}/pickup [Model Pickup] [X] [Y] [Z] [Tip Pickup] - {6666FF}Creezi un pickup\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 7: {66FF00}/createcamera [Viteza maxima Admisa] - {6666FF}Creezi un radar\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 7: {66FF00}/delcamera - {6666FF}Stergi un radar\n", Msg);
		
		format(Msg, 2000, "%s{FF9900}Level 7: {66FF00}/getall - {6666FF}Teleportezi toti jucatorii la tine\n", Msg);

		format(Msg, 2000, "%s{6666FF}+ Comenzile /acmds1 + /acmds2 + /acmds3 + /acmds4 + /acmds5 + /acmds6\n", Msg);









	    // Show a dialog that shows the rules

		ShowPlayerDialog(playerid, DialogComezile2, DIALOG_STYLE_MSGBOX, "Comenzi Admin level 7:", Msg, "Ok", "Cancel");

	}

	else

	    return 0;

	return 1;
}

COMMAND:acmds8(playerid, params[])

{

	// Setup local variables

	new Msg[2000];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/acmds8", params);



	// Check if the player has logged in

	if (APlayerData[playerid][PlayerLevel] >= 8)

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Construct the rules max 35

		format(Msg, 2000, "%s{FF9900}Level 8: {66FF00}/megacadou - {6666FF}Dai un cadou in valoare de 50kk + 50 scor tuturor\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 8: {66FF00}/createbusiness - {6666FF}Creezi o afacere\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 8: {66FF00}/delbusiness - {6666FF}Stergi o afacere\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 8: {66FF00}/resetplayer [ID/Nume] [Bani] [Scor] [Status] [Motiv] - {6666FF}Resetezi contul unui jucator\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 8: {66FF00}/fixplayer ][ID/Nume] - {6666FF}Repari contul unui jucator\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 8: {66FF00}/restart - {6666FF}Dai restart server-ului\n", Msg);
		
		format(Msg, 2000, "%s{FF9900}Level 8: {66FF00}/setvip - {6666FF}Setezi levelul VIP al unui jucator\n", Msg);
		
		format(Msg, 2000, "%s{FF9900}Level 8: {66FF00}/setlevel - {6666FF}Setezi levelul de Admin al unui jucator\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 8: {66FF00}/god [ID]- {6666FF}Faci un jucator invincibil\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 8: {66FF00}/delproperty - {6666FF}Stergi o proprietate\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 8: {66FF00}/evict112 - {6666FF}Setezi casa / afacerea nedetinuta\n", Msg);

		format(Msg, 2000, "%s{6666FF}+ Comenzile /acmds1 + /acmds2 + /acmds3 + /acmds4 + /acmds5 + /acmds6 + /acmds7\n", Msg);









	    // Show a dialog that shows the rules

		ShowPlayerDialog(playerid, DialogComezile2, DIALOG_STYLE_MSGBOX, "Comenzi Admin level 8:", Msg, "Ok", "Cancel");

	}

	else

	    return 0;

	return 1;
}

COMMAND:vcmds(playerid, params[])

{

	// Setup local variables

	new Msg[2000];



	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/vcmds", params);



	if (APlayerData[playerid][VPlayerLevel] < 1) return SendClientMessage(playerid, 0xFF0000FF, "Nu esti Vip!");

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Construct the rules max 35

		format(Msg, 2000, "%s{FF9900}Level 1: {FFFFFF}/vc [Text] - {DD9322}Vorbesti pe chatul VIP\n", Msg);
		
		format(Msg, 2000, "%s{FF9900}Level 1: {FFFFFF}/vsay [Text] - {DD9322}Dai un anunt ca VIP\n", Msg);
		
		format(Msg, 2000, "%s{FF9900}Level 1: {FFFFFF}/vport [ID] - {DD9322}Te teleporteaza la persoana Dorita\n", Msg);
		
		format(Msg, 2000, "%s{FF9900}Level 1: {FFFFFF}/vnos - {DD9322}Iti pui Nitro\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 1: {FFFFFF}/vheal - {DD9322}Iti setezi viata la 100\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 1: {FFFFFF}/vfix - {DD9322}Iti repari Masina\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 2: {FFFFFF}/vskin [ID] - {DD9322}Iti ei un skin\n", Msg);
		
		format(Msg, 2000, "%s{FF9900}Level 2: {FFFFFF}/vcamera - {DD9322}Iti ei o camera foto\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 2: {FFFFFF}/vlicenta - {DD9322}Te teleporteaza la licente\n", Msg);
		
		format(Msg, 2000, "%s{FF9900}Level 2: {FFFFFF}/vget [ID] - {DD9322}Aduci persoana dorita la tine\n", Msg);
		
		format(Msg, 2000, "%s{FF9900}Level 2: {FFFFFF}/vtunels - {DD9322}Te teleporteaza la tune LS\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 2: {FFFFFF}/vtunesf - {DD9322}Te teleporteaza la tune SF\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 2: {FFFFFF}/vtunelv - {DD9322}Te teleporteaza la tune LV\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 3: {FFFFFF}/varmour - {DD9322}Iti setezi armoura 100\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 3: {FFFFFF}/vfly - {DD9322}Iti ei un jetpack\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 3: {FFFFFF}/velgt - {DD9322}Iti tunezi masina aleatoriu\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 3: {FFFFFF}/vturn - {DD9322}Te teleporteaza la Star Tower Ls\n", Msg);
		
		format(Msg, 2000, "%s{FF9900}Level 3: {FFFFFF}/chilliad - {DD9322}Te teleportezi pe muntele chilliad\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 3: {FFFFFF}/bucuresti - {DD9322}Te teleportezi la Bucuresti\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 3: {FFFFFF}/constanta - {DD9322}Te teleportezi la Constanta\n", Msg);

		format(Msg, 2000, "%s{FF9900}Level 3: {FFFFFF}/cityville - {DD9322}Te teleportezi la Cityville\n", Msg);

	    // Show a dialog that shows the rules

		ShowPlayerDialog(playerid, DialogComezile2, DIALOG_STYLE_MSGBOX, "Comenzile jucatorilor VIP:", Msg, "Oky", "");

	}

	else

	    return 0;

	return 1;

}

COMMAND:amess(playerid,params[])

{

	// Setup local variables

	new Msg[128], Name[24], Message[128];



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 1

		if (APlayerData[playerid][PlayerLevel] >= 1)

		{

			if (sscanf(params, "s[128]", Message)) SendClientMessage(playerid, 0xFF0000AA, "[RLT]: \"/amess <Mesaj>\"");

			else

			{

				GetPlayerName(playerid, Name, sizeof(Name));

				format(Msg, sizeof(Msg), "%s (%s) : %s", Name, AdminLevelName[APlayerData[playerid][PlayerLevel]], Message);

				SendClientMessageToAll(0xFF6347FF, Msg);

			}

		}

		else

			return 0;

	}

	else

		return 0;



	return 1;

}

COMMAND:anunt(playerid, params[])

{

	// Send the command to all admins so they can see it

	SendAdminText(playerid, "/anunt", params);



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player's admin-level is at least 5

		if (APlayerData[playerid][PlayerLevel] >= 5)

		{

            GameTextForAll(params,6000,1);

		}

		else

            return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;
}

COMMAND:forum(playerid, params[])

{
    SendClientMessage(playerid, 0xFF0000AA, "{AFAFAF}Adresa forumului nostru este: {0066CC}FORUM.{FFFF00}4GameTech{11FF00}.COM");
    GameTextForPlayer(playerid,"~n~~n~~n~~n~~n~~n~~n~~w~Forum.4GameTech~w~.COM",5000,4);
   	return 1;
}

COMMAND:ac(playerid, params[])

{

	// Setup local variables

	new Name[24], Msg[128], Message[128];



	// Get the player's name

	GetPlayerName(playerid, Name, sizeof(Name));



	// Check if the player has logged in

	if (APlayerData[playerid][LoggedIn] == true)

	{

		// Check if the player is an admin

		if (APlayerData[playerid][PlayerLevel] >= 1)

		{

			if (sscanf(params, "s[128]", Message)) SendClientMessage(playerid, 0xFF0000AA, "[RLT]: \"/ac <Message>\"");

			else

			{

				// Loop through all players

				for (new i; i < MAX_PLAYERS; i++)

				{

				    // Check if the player is logged in

					if (APlayerData[i][LoggedIn] == true)

					{

					    // Check if the other player is also an admin

					    if (APlayerData[i][PlayerLevel] > 0)

					    {

							format(Msg, 128, "{B0B0B0}[Admin]%s: {FFFFFF}%s", Name, Message);

							SendClientMessage(i, 0xFFFFFFFF, Msg);

					    }

					}

				}

			}

		}

		else

		    return 0;

	}

	else

	    return 0;



	// Let the server know that this was a valid command

	return 1;

}

CMD:respawnall(playerid,params[])

{

    new sendername[30],string[60];

    if(APlayerData[playerid][PlayerLevel] < 1) return SendClientMessage(playerid, 0xFF0000FF, "Comanda restrictionata administratorilor");

    for(new car = 0; car <= 268; car++)

    if((IsVehicleEmpty(car) && !IsTrailerAttachedToVehicle(car) && GetVehicleModel(car) !=435 && GetVehicleModel(car) !=450 && GetVehicleModel(car) !=584 && GetVehicleModel(car) !=591) || (IsVehicleEmpty(car) && IsTrailerAttachedToVehicle(car) !=GetVehicleTrailer(car)))

    {

        SetVehicleToRespawn(car);

    }

    GetPlayerName(playerid,sendername,sizeof(sendername));

    format(string, sizeof(string), "[RLT]: Masinile au fost respawnate de catre %s.", sendername);

    SendClientMessageToAll(0xFFFFFFFF,string);

    return 1;

}

