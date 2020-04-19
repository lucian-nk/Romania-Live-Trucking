stock FixHouses()
{
	// Setup local variables
	new file[100], File:PFile, Name[24], LineFromFile[100], ParameterName[50], ParameterValue[50];
	new bool:PlayerOwnedTheHouse = true, HousesFixed;

	// Loop through all houses
	for (new HouseID = 1; HouseID < MAX_HOUSES; HouseID++)
	{
		// Check if the house is owned
		if (AHouseData[HouseID][Owned] == true)
		{
			// Get the name of the owner
			format(Name, 24, AHouseData[HouseID][Owner]);
			// Construct the complete filename for this player's account
			format(file, sizeof(file), PlayerFile, Name);

			// Check if the player's datafile exists
			if (fexist(file))
			{
				PFile = fopen(file, io_read); // Open the playerfile for reading

				fread(PFile, LineFromFile); // Read the first line of the file

				// Keep reading until the end of the file is found (no more data)
				while (strlen(LineFromFile) > 0)
				{
					StripNewLine(LineFromFile); // Strip any newline characters from the LineFromFile
					sscanf(LineFromFile, "s[50]s[50]", ParameterName, ParameterValue); // Extract parametername and parametervalue

                    // If the parametername is correct ("House")
					if (strcmp(ParameterName, "House", false) == 0)
					{
					    // Check if the player owns this house
					    if (strval(ParameterValue) == HouseID)
                            PlayerOwnedTheHouse = true; // The player really owns the house
					}

                    // Read the next line of the file
					fread(PFile, LineFromFile);
				}

                // Close the player-file
				fclose(PFile);

				// Check if the player doesn't own the house
				if (PlayerOwnedTheHouse == false)
				{
					// Clear the ownership from the house
					AHouseData[HouseID][Owned] = false;
					AHouseData[HouseID][Owner] = 0;
					AHouseData[HouseID][HouseName] = 0;
					AHouseData[HouseID][HouseLevel] = 1;
					// Update the house-entrance
					House_UpdateEntrance(HouseID);
					// Save the house, hereby fixing the ownership-bug
					HouseFile_Save(HouseID);
					// Increase the number of houses that have been fixed
					HousesFixed++;
				}

				// Reset the variable that holds if the player owned the house, so the next house/owner can be processed
                PlayerOwnedTheHouse = false;
			}
		}
	}

	// All houses have been processed, now print a line to the server's console
	printf(TXT_HousesFixed, HousesFixed);
}
GameModeInit_VehiclesPickups()
{
	// Setup local variables
	new LastVehicleMsg[100], LastObjectMsg[100], LastHouseMsg[100], LastBusinessMsg[100], LastCameraMsg[100];

	// Add some trucks to all trucking depots
	GameModeInit_TruckDepots();
	GameModeInit_Politie();
	GameModeInit_Mafia();
	GameModeInit_Pilot();
	GameModeInit_Curier();
	GameModeInit_PizzaBoy();
	GameModeInit_Assistance();
	GameModeInit_RoadWork();
	GameModeInit_Medic();
	GameModeInit_Taxi();
	GameModeInit_Padurar();
	GameModeInit_Sofer();
	GameModeInit_Gunoier();
	GameModeInit_Busses();
	GameModeInit_Mape();
	GameModeInit_Marinar();
	GameModeInit_PickupsIcons();
	GameModeInit_Toll();
	Housing_LoadAll();
	Camera_LoadAll();
    Business_LoadAll();
	SetTimer("Business_TransactionTimer", 1000 * 60 * 60, true);
	IntrestTime_Load();
	SetTimer("Bank_IntrestTimer", 1000 * 60 * 60, true);
	format(LastVehicleMsg, 100, TXT_LastVehicleID, LastVehicleID);
	format(LastObjectMsg, 100, TXT_LastObjectID, LastObjectID);
	format(LastHouseMsg, 100, TXT_TotalHouses, TotalHouses);
	format(LastBusinessMsg, 100, TXT_TotalBusiness, TotalBusiness);
	format(LastCameraMsg, 100, TXT_TotalSpeedCameras, TotalCameras);
	print(TXT_DebugInfo);
	print("-------------------------------------");
	print(LastVehicleMsg);
	print(LastObjectMsg);
	print(LastHouseMsg);
	print(LastBusinessMsg);
	print(LastCameraMsg);
	print("-------------------------------------");
}
//Tirurile din LV
GameModeInit_TruckDepots()
{
	//Tirurile la truck LV 
	LastVehicleID = Vehicle_AddStatic(VehicleTrailerCargo,1302.3000500,1177.5999800,11.5000000,270.0000000,6,103,600); //Trailer 1
	LastVehicleID = Vehicle_AddStatic(VehicleTrailerCargo,1302.3000500,1173.3000500,11.5000000,270.0000000,6,103,600); //Trailer 1
	LastVehicleID = Vehicle_AddStatic(VehicleTrailerCargo,1302.3000500,1168.8000500,11.5000000,270.0000000,6,103,600); //Trailer 1
	LastVehicleID = Vehicle_AddStatic(VehicleTrailerCargo,1302.3000500,1155.5999800,11.5000000,270.0000000,6,103,600); //Trailer 1
	LastVehicleID = Vehicle_AddStatic(VehicleTrailerCargo,1302.3000500,1151.3000500,11.5000000,270.0000000,6,103,600); //Trailer 1
	LastVehicleID = Vehicle_AddStatic(VehicleTrailerCargo,1302.3000500,1147.3000500,11.5000000,270.0000000,6,103,600); //Trailer 1
	LastVehicleID = Vehicle_AddStatic(VehicleTrailerCargo,1302.3000500,1131.3000500,11.5000000,270.0000000,6,103,600); //Trailer 1
	LastVehicleID = Vehicle_AddStatic(VehicleTrailerCargo,1302.3000500,1126.4000200,11.5000000,270.0000000,6,103,600); //Trailer 1
	LastVehicleID = Vehicle_AddStatic(VehicleTrailerCargo,1302.3000500,1122.0000000,11.5000000,270.0000000,6,103,600); //Trailer 1
	LastVehicleID = Vehicle_AddStatic(VehicleTrailerCargo,1302.3000500,1108.0999800,11.5000000,270.0000000,6,103,600); //Trailer 1
	LastVehicleID = Vehicle_AddStatic(VehicleTrailerCargo,1302.3000500,1104.0999800,11.5000000,270.0000000,6,103,600); //Trailer 1
	LastVehicleID = Vehicle_AddStatic(VehicleTrailerCargo,1302.3000500,1100.0999800,11.5000000,270.0000000,6,103,600); //Trailer 1
	LastVehicleID = Vehicle_AddStatic(VehicleTrailerCargo,1431.9000200,930.2999900,11.6000000,0.0000000,6,103,600); //Trailer 1
	LastVehicleID = Vehicle_AddStatic(VehicleTrailerCargo,1426.4000200,930.2999900,11.6000000,0.0000000,6,103,600); //Trailer 1
	LastVehicleID = Vehicle_AddStatic(VehicleTrailerCargo,1421.8000500,930.2999900,11.6000000,0.0000000,6,103,600); //Trailer 1
	LastVehicleID = Vehicle_AddStatic(VehicleTrailerCargo,1408.1999500,930.2999900,11.6000000,0.0000000,6,103,600); //Trailer 1
	LastVehicleID = Vehicle_AddStatic(VehicleTrailerCargo,1403.4000200,930.2999900,11.6000000,0.0000000,6,103,600); //Trailer 1
	LastVehicleID = Vehicle_AddStatic(VehicleTrailerCargo,1398.9000200,930.2999900,11.6000000,0.0000000,6,103,600); //Trailer 1
	LastVehicleID = Vehicle_AddStatic(VehicleRoadTrain,1354.9000200,1161.9000200,11.8000000,180.0000000,6,103,600); //Roadtrain
	LastVehicleID = Vehicle_AddStatic(VehicleRoadTrain,1361.0999800,1161.9000200,11.8000000,180.0000000,6,103,600); //Roadtrain
	LastVehicleID = Vehicle_AddStatic(VehicleRoadTrain,1374.9000200,1161.9000200,11.8000000,180.0000000,6,103,600); //Roadtrain
	LastVehicleID = Vehicle_AddStatic(VehicleRoadTrain,1385.9000200,1161.9000200,11.8000000,180.0000000,6,103,600); //Roadtrain
	LastVehicleID = Vehicle_AddStatic(VehicleRoadTrain,1380.4000200,1161.9000200,11.8000000,180.0000000,6,103,600); //Roadtrain
	LastVehicleID = Vehicle_AddStatic(VehicleRoadTrain,1399.0000000,1161.9000200,11.8000000,180.0000000,6,103,600); //Roadtrain
	LastVehicleID = Vehicle_AddStatic(VehicleRoadTrain,1404.3000500,1161.9000200,11.8000000,180.0000000,6,103,600); //Roadtrain
	LastVehicleID = Vehicle_AddStatic(VehicleRoadTrain,1409.5000000,1161.9000200,11.8000000,180.0000000,6,103,600); //Roadtrain
	LastVehicleID = Vehicle_AddStatic(VehicleRoadTrain,1424.0999800,1161.9000200,11.8000000,180.0000000,6,103,600); //Roadtrain
	LastVehicleID = Vehicle_AddStatic(VehicleRoadTrain,1430.5999800,1161.9000200,11.8000000,180.0000000,6,103,600); //Roadtrain
	LastVehicleID = Vehicle_AddStatic(VehicleTrailerFluids,1474.3000500,1117.6999500,12.0000000,90.0000000,6,103,600); //Trailer 3
	LastVehicleID = Vehicle_AddStatic(VehicleTrailerFluids,1474.3000500,1113.4000200,12.0000000,90.0000000,6,103,600); //Trailer 3
	LastVehicleID = Vehicle_AddStatic(VehicleTrailerFluids,1474.3000500,1109.0999800,12.0000000,90.0000000,6,103,600); //Trailer 3
	LastVehicleID = Vehicle_AddStatic(VehicleTrailerFluids,1474.3000500,1096.0000000,12.0000000,90.0000000,6,103,600); //Trailer 3
	LastVehicleID = Vehicle_AddStatic(VehicleTrailerFluids,1474.3000500,1090.8000500,12.0000000,90.0000000,6,103,600); //Trailer 3
	LastVehicleID = Vehicle_AddStatic(VehicleTrailerFluids,1474.3000500,1086.3000500,12.0000000,90.0000000,6,103,600); //Trailer 3
	LastVehicleID = Vehicle_AddStatic(VehicleTrailerOre,1475.0999800,1072.1999500,11.5000000,90.0000000,6,103,600); //Trailer 2
	LastVehicleID = Vehicle_AddStatic(VehicleTrailerOre,1475.0999800,1067.1999500,11.5000000,90.0000000,6,103,600); //Trailer 2
	LastVehicleID = Vehicle_AddStatic(VehicleTrailerOre,1475.0999800,1061.9000200,11.5000000,90.0000000,6,103,600); //Trailer 2
	LastVehicleID = Vehicle_AddStatic(VehicleTrailerOre,1475.0999800,1048.5000000,11.5000000,90.0000000,6,103,600); //Trailer 2
	LastVehicleID = Vehicle_AddStatic(VehicleTrailerOre,1475.0999800,1044.5000000,11.5000000,90.0000000,6,103,600); //Trailer 2
	LastVehicleID = Vehicle_AddStatic(VehicleTrailerOre,1475.0999800,1040.0000000,11.5000000,90.0000000,6,103,600); //Trailer 2
	LastVehicleID = Vehicle_AddStatic(VehicleLineRunner,1477.3000500,930.0999800,11.5000000,0.0000000,6,103,600); //Linerunner
	LastVehicleID = Vehicle_AddStatic(VehicleLineRunner,1473.3000500,930.0999800,11.5000000,0.0000000,6,103,600); //Linerunner
	LastVehicleID = Vehicle_AddStatic(VehicleLineRunner,1469.5000000,930.0999800,11.5000000,0.0000000,6,103,600); //Linerunner
	LastVehicleID = Vehicle_AddStatic(VehicleLineRunner,1455.6999500,930.0999800,11.5000000,0.0000000,6,103,600); //Linerunner
	LastVehicleID = Vehicle_AddStatic(VehicleLineRunner,1450.4000200,930.0999800,11.5000000,0.0000000,6,103,600); //Linerunner
	LastVehicleID = Vehicle_AddStatic(VehicleLineRunner,1445.4000200,930.0999800,11.5000000,0.0000000,6,103,600); //Linerunner
	LastVehicleID = Vehicle_AddStatic(VehicleSunrise,1474.2266, 978.7180, 10.7164, 88.6751,6,103,600); //Sunrise
}	
// Masinile De LA Politie Si FBY
GameModeInit_Politie()
{
	LastVehicleID = Vehicle_AddStatic(VehicleFBIRancher, 337.3996000, -1532.3026000, 33.4524000, 323.9824000, 115, 116, 600); //FBIRancher
	LastVehicleID = Vehicle_AddStatic(VehicleFBIRancher, 345.1521000,- 1522.0698000, 33.3716000, 322.8959000, 115, 116, 600); //FBIRancher
	LastVehicleID = Vehicle_AddStatic(VehicleFBITruck, 324.5177000, -1551.7269000, 33.2746000, 156.6633000, 115, 116, 600); //FBITruck
	LastVehicleID = Vehicle_AddStatic(VehicleFBITruck, 361.7479000, -1503.9670000, 32.7995000, 132.7722000, 115, 116, 600); //FBITruck
	LastVehicleID = Vehicle_AddStatic(VehicleSWAT, 357.6819000, -1537.8867000, 33.1841000, 143.5682000, 115, 116, 600); //S.W.A.T. 
	LastVehicleID = Vehicle_AddStatic(VehicleEnforcer, 350.0858000, -1548.0468000, 33.3023000, 324.9844000, 115, 116, 600); //Enforcer
	LastVehicleID = Vehicle_AddStatic(VehiclePoliceLVPD,2251.89990234,2443.80004883,10.69999981,0.00000000,-1,-1,600); //Police Car (LVPD)
	LastVehicleID = Vehicle_AddStatic(VehiclePoliceLVPD,2256.10009766,2444.00000000,10.69999981,0.00000000,-1,-1,600); //Police Car (LVPD)
	LastVehicleID = Vehicle_AddStatic(VehiclePoliceLVPD,2260.30004883,2444.19995117,10.69999981,0.00000000,-1,-1,600); //Police Car (LVPD
	LastVehicleID = Vehicle_AddStatic(VehiclePoliceRanger,2269.80004883,2443.19995117,11.10000038,0.00000000,-1,-1,600); //Police Ranger
	LastVehicleID = Vehicle_AddStatic(VehiclePoliceRanger,2273.69995117,2443.10009766,11.10000038,0.00000000,-1,-1,600); //Police Ranger
	LastVehicleID = Vehicle_AddStatic(VehiclePoliceRanger,2277.80004883,2443.00000000,11.10000038,0.00000000,-1,-1,600); //Police Ranger
	LastVehicleID = Vehicle_AddStatic(VehiclePoliceRanger,2282.19995117,2442.89990234,11.10000038,0.00000000,-1,-1,600); //Police Ranger
	LastVehicleID = Vehicle_AddStatic(VehicleEnforcer,2251.60009766,2477.10009766,11.10000038,180.00000000,-1,-1,600); //VehicleEnforcer
	LastVehicleID = Vehicle_AddStatic(VehicleEnforcer,2256.69995117,2477.00000000,11.10000038,180.00000000,-1,-1,600); //Enforcer
	LastVehicleID = Vehicle_AddStatic(VehicleEnforcer,2260.80004883,2476.89990234,11.10000038,180.00000000,-1,-1,600); //Enforcer
	LastVehicleID = Vehicle_AddStatic(VehicleSWAT,2290.80004883,2444.19995117,10.39999962,0.00000000,-1,-1,600); //S.W.A.T. Van
	LastVehicleID = Vehicle_AddStatic(VehicleSWAT,2295.10009766,2444.10009766,10.39999962,0.00000000,-1,-1,600); //
	LastVehicleID = Vehicle_AddStatic(VehicleFBIRancher,2268.80004883,2476.80004883,11.10000038,180.00000000,-1,-1,600); //VehicleFBIRancher
	LastVehicleID = Vehicle_AddStatic(VehicleFBIRancher,2273.19995117,2476.69995117,11.10000038,180.00000000,-1,-1,600); //FBI Rancher
	LastVehicleID = Vehicle_AddStatic(VehicleFBIRancher,2277.69995117,2476.60009766,11.10000038,180.00000000,-1,-1,600); //FBI Rancher
	LastVehicleID = Vehicle_AddStatic(VehicleHPV1000,2282.30004883,2475.89990234,10.50000000,180.00000000,-1,-1,600); //HPV1000
	LastVehicleID = Vehicle_AddStatic(VehicleHPV1000,2290.4802,2476.4131,10.3909,177.1003, -1, -1, 600); //HPV1000
	LastVehicleID = Vehicle_AddStatic(VehicleHPV1000,2295.1228,2476.8179,10.3908,177.7041,-1,-1,600); //HPV1000
	LastVehicleID = Vehicle_AddStatic(VehicleHPV1000,2295.3313,2459.9211,10.3904,172.6345,-1,-1,600); //HPV1000
	LastVehicleID = Vehicle_AddStatic(VehicleHPV1000,2290.5654,2459.4302,10.3909,176.0132,-1,-1,600); //HPV1000
	LastVehicleID = Vehicle_AddStatic(VehicleSWAT,2282.2974,2457.4180,10.5791,182.0350,-1,-1,600); //S.W.A.T. Van
	LastVehicleID = Vehicle_AddStatic(VehicleSWAT,2277.7856,2458.3130,10.5791,181.3782,-1,-1,600); //S.W.A.T
	LastVehicleID = Vehicle_AddStatic(VehicleSWAT,2273.3789,2458.6575,10.5789,181.8136,-1,-1,600); //S.W.A.T. Van
	LastVehicleID = Vehicle_AddStatic(VehicleSWAT,2268.7515,2457.8318,10.5791,180.1682,-1,-1,600); //S.W.A.T
	LastVehicleID = Vehicle_AddStatic(VehiclePoliceRanger,2251.7351,2461.9214,11.0118,359.5804,-1,-1,600); //S.W.A.T
	LastVehicleID = Vehicle_AddStatic(VehiclePoliceRanger,2256.4702,2461.1443,11.0077,1.7750,-1,-1,600); //S.W.A.T. Van
	LastVehicleID = Vehicle_AddStatic(VehiclePoliceRanger,2260.6716,2461.3274,11.0112,359.8621,-1,-1,600); //S.W.A.T
}
//Masinile de la Mafia
GameModeInit_Mafia()
{
	LastVehicleID = Vehicle_AddStatic(VehicleBullet, -2198.3000500, 984.0000000, 79.6000000, 272.0000000, -1, 126, 600); //Bullet
	LastVehicleID = Vehicle_AddStatic(VehicleBullet, -2198.3000500, 990.0999800, 79.6000000, 272.0000000, -1, 126, 600); //Bullet
	LastVehicleID = Vehicle_AddStatic(VehicleBullet, -2198.3000500, 996.0999800, 79.6000000, 272.0000000, -1, 126, 600); //Bullet
	LastVehicleID = Vehicle_AddStatic(VehicleBullet, -2198.3000500, 1002.0999800, 79.6000000, 272.0000000, -1, 126, 600); //Bullet
	LastVehicleID = Vehicle_AddStatic(VehicleBullet, -2198.3000500, 1008.4000200, 79.6000000, 272.0000000, -1, 126, 600); //Bullet
	LastVehicleID = Vehicle_AddStatic(VehicleSandking, -2198.0000000, 1035.0999800, 80.5000000, 178.0000000, 1, 73, 600); //Sandking
	LastVehicleID = Vehicle_AddStatic(VehicleSandking, -2189.8000500, 1035.0000000, 80.3000000, 177.9950000, -1, 166, 600); //Sandking
	LastVehicleID = Vehicle_AddStatic(VehicleSandking, -2182.5000000, 1035.0000000, 80.3000000, 177.9950000, 89, -1, 600); //Sandking
	LastVehicleID = Vehicle_AddStatic(VehicleStretch, -2179.6001000, 999.2000100, 79.8000000, 0.0000000, 39, 135, 600); //Stretch
	LastVehicleID = Vehicle_AddStatic(VehicleStretch, -2179.6240200, 982.1149900, 79.8000000, 0.0000000, 39, 135, 600); //Stretch
	LastVehicleID = Vehicle_AddStatic(VehicleRoadTrain, -2194.8999000, 967.2999900, 81.2000000, 0.0000000, 3, 56, 600); //Roadtrain
	LastVehicleID = Vehicle_AddStatic(VehicleRoadTrain, -2183.1001000, 967.2999900, 81.2000000, 0.0000000, 3, 56, 600); //Roadtrain
	LastVehicleID = Vehicle_AddStatic(VehicleRoadTrain, -2189.0000000, 967.0999800, 81.2000000, 0.0000000, 3, 56, 600); //Roadtrain
	LastVehicleID = Vehicle_AddStatic(VehicleNRG500, -2204.3200700, 1055.5820300, 79.6730000, 182.0000000, -1, 137, 600); //NRG-500
	LastVehicleID = Vehicle_AddStatic(VehicleNRG500, -2206.9829100, 1055.7819800, 79.6730000, 182.0000000, -1, 137, 600); //NRG-500
	LastVehicleID = Vehicle_AddStatic(VehicleNRG500, -2209.5659200, 1055.6960400, 79.6730000, 182.0000000, -1, 137, 600); //NRG-50
}
//Avioane Aeroport Lv
GameModeInit_Pilot()
{
	LastVehicleID = Vehicle_AddStatic(VehicleShamal, 1615.0, 1630.0, 11.8, 180.0, random(126), random(126), 300); // Plane: Shamal
	LastVehicleID = Vehicle_AddStatic(VehicleShamal, 1590.0, 1630.0, 11.8, 180.0, random(126), random(126), 300); // Plane: Shamal
	LastVehicleID = Vehicle_AddStatic(VehicleShamal, 1565.0, 1630.0, 11.8, 180.0, random(126), random(126), 300); // Plane: Shamal
	LastVehicleID = Vehicle_AddStatic(VehicleNevada, 1545.0, 1640.0, 11.8, 90.0, random(126), random(126), 300); // Plane: Nevada
	LastVehicleID = Vehicle_AddStatic(VehicleNevada, 1545.0, 1675.0, 11.8, 90.0, random(126), random(126), 300); // Plane: Nevada
	LastVehicleID = Vehicle_AddStatic(VehicleNevada, 1545.0, 1710.0, 11.8, 90.0, random(126), random(126), 300); // Plane: Nevada
	LastVehicleID = Vehicle_AddStatic(VehicleMaverick, 1650.0, 1557, 10.9, 90.0, random(126), random(126), 300); // Helicopter: Maverick
	LastVehicleID = Vehicle_AddStatic(VehicleMaverick, 1650.0, 1542, 10.9, 90.0, random(126), random(126), 300); // Helicopter: Maverick
	LastVehicleID = Vehicle_AddStatic(VehicleMaverick, 1635.0, 1534, 10.9, 0.0, random(126), random(126), 300); // Helicopter: Maverick	
}
//Masinile de la mechanic (assistence)
GameModeInit_Assistance()
{
	LastVehicleID = Vehicle_AddStatic(VehicleTowTruck, 2183.78735352, 2778.38867188, 10.71031380, 91.99963379, 6, 6, 600); //Tow Truck
	LastVehicleID = Vehicle_AddStatic(VehicleTowTruck, 2198.99707031, 2787.81933594, 10.71031380, 177.99499512, 6, 6, 600); //Tow Truck
	LastVehicleID = Vehicle_AddStatic(VehicleTowTruck, 2202.83935547, 2787.74926758, 10.71031380, 177.99499512, 6, 6, 600); //Tow Truck
	LastVehicleID = Vehicle_AddStatic(VehicleTowTruck, 2192.21679688, 2778.29931641, 10.71031380, 91.99951172, 6, 6, 600); //Tow Truck
	LastVehicleID = Vehicle_AddStatic(VehicleSparrow, 2191.91235352, 2798.88842773, 15.64682961, 180.00000000, 6, 6, 600); //Sparrow
	LastVehicleID = Vehicle_AddStatic(VehicleSparrow, 2203.31738281, 2798.86132812, 15.64682961, 180.00000000, 6, 6, 600); //Sparrow	
}	
// Add busses to the bus-depots
GameModeInit_Curier()
{
	LastVehicleID = Vehicle_AddStatic(VehicleBurrito, 1053.41076660, 1917.57165527, 11.07031250, 0.00000000, 17, 17, 600); //Burrito
	LastVehicleID = Vehicle_AddStatic(VehicleBurrito, 1060.31750488, 1917.54052734, 11.07031250, 0.00000000, 17, 17, 600); //Burrito
	LastVehicleID = Vehicle_AddStatic(VehicleSecuricar, 1068.07116699, 1917.14294434, 11.07010269, 0.00000000, 17, 17, 600); //Securicar
	LastVehicleID = Vehicle_AddStatic(VehicleSecuricar, 1076.19995117, 1917.18774414, 11.07010269, 0.00000000, 17, 17, 600); //Securicar
	LastVehicleID = Vehicle_AddStatic(VehiclePicador, 1083.11523438, 1916.60302734, 10.66216087, 0.00000000, 17, 17, 600); //Picador
	LastVehicleID = Vehicle_AddStatic(VehiclePicador, 1091.25244141, 1916.71362305, 10.66216087, 0.00000000, 17, 17, 600); //Picador
	LastVehicleID = Vehicle_AddStatic(VehicleSANNewsMaverick, 1063.71118164, 1903.94226074, 17.81237793, 0.00000000, 17, 17, 600); //
	LastVehicleID = Vehicle_AddStatic(VehicleSANNewsMaverick, 1078.74731445, 1904.01049805, 17.81237793, 0.00000000, 17, 17, 600); //
}	
// Add busses to the bus-depots
GameModeInit_PizzaBoy()
{
	LastVehicleID = Vehicle_AddStatic(VehiclePizzaboy, 2096.5139, -1794.1666, 12.9888, 87.4861, 17, 17, 600); //
	LastVehicleID = Vehicle_AddStatic(VehiclePizzaboy, 2096.5713, -1797.1855, 12.9861, 90.7664, 17, 17, 600); //
	LastVehicleID = Vehicle_AddStatic(VehiclePizzaboy, 2096.6965, -1800.5247, 12.9792, 88.7354, 17, 17, 600); //
	LastVehicleID = Vehicle_AddStatic(VehiclePizzaboy, 2096.7354, -1816.7987, 12.9743, 90.7613, 17, 17, 600); //
	LastVehicleID = Vehicle_AddStatic(VehiclePizzaboy, 2096.4224, -1819.9376, 12.9800, 91.1479, 17, 17, 600); //
}	
// Marinile de la RoadWork
GameModeInit_RoadWork()
{
	LastVehicleID = Vehicle_AddStatic(VehicleTowTruck, -1866.5, -1731.75, 21.7, 30.0, random(126), random(126), 600); // Towtruck
	LastVehicleID = Vehicle_AddStatic(VehicleTowTruck, -1870.5, -1734.25, 21.7, 30.0, random(126), random(126), 600); // Towtruck
	LastVehicleID = Vehicle_AddStatic(VehicleTowTruck, -1874.5, -1736.75, 21.7, 30.0, random(126), random(126), 600); // Towtruck
	LastVehicleID = Vehicle_AddStatic(VehicleTowTruck, -1878.5, -1739.25, 21.7, 30.0, random(126), random(126), 600); // Towtruck
	LastVehicleID = Vehicle_AddStatic(VehicleTowTruck, -1882.5, -1741.75, 21.7, 30.0, random(126), random(126), 600); // Towtruck
	LastVehicleID = Vehicle_AddStatic(VehicleTowTruck, -1886.5, -1744.25, 21.7, 30.0, random(126), random(126), 600); // Towtruck
}	
// Ambulantele de la Medici
GameModeInit_Medic()
{
	LastVehicleID = Vehicle_AddStatic(VehicleAmbulance, 1177.1348,  -1308.7642, 14.0151, 269.6247, 6, 6, 600); // Ambulanta
	LastVehicleID = Vehicle_AddStatic(VehicleAmbulance, 1177.1008,  -1339.2208, 14.0709, 270.9928, 6, 6, 600); // Ambulanta
	LastVehicleID = Vehicle_AddStatic(VehicleAmbulance, 1182.3948,	-1315.9470,	13.7233, 178.4619, 6, 6, 600); // Ambulanta
	LastVehicleID = Vehicle_AddStatic(VehicleAmbulance, 1182.2238,	-1332.1465,	13.7304, 359.2700, 6, 6, 600); // Ambulanta
	LastVehicleID = Vehicle_AddStatic(VehicleAmbulance, 1183.7019,	-1320.3450,	13.7690, 270.2889, 6, 6, 600); // Ambulanta
	LastVehicleID = Vehicle_AddStatic(VehicleAmbulance, 1183.8320,	-1326.9783,	13.7233, 265.3643, 6, 6, 600); // Ambulanta
	LastVehicleID = Vehicle_AddStatic(VehicleAmbulance, 1178.8132,	-1356.3961,	14.2574, 271.4677, 6, 6, 600); // Ambulanta
	LastVehicleID = Vehicle_AddStatic(VehicleAmbulance, 1177.9354,	-1365.9036,	14.2068, 269.2316, 6, 6, 600); // Ambulanta

}
// Trenurile de la Gara din LV
GameModeInit_Sofer()
{
	LastVehicleID = Vehicle_AddStatic(VehicleTren, 1412.4000200,2632.3999000,12.4000000,270.0000000,6,6,600); //Freight
	LastVehicleID = Vehicle_AddStatic(VehicleTren, 1470.9000200,2632.3000500,12.4000000,90.0000000,6,6,600); //Freight
	LastVehicleID = Vehicle_AddStatic(VehicleTren, 1470.8994100,2632.2998000,12.4000000,90.0000000,6,6,600); //Freight
	LastVehicleID = Vehicle_AddStatic(VehicleTren, 1470.8994100,2632.2998000,12.4000000,90.0000000,6,6,600); //Freight
	LastVehicleID = Vehicle_AddStatic(VehicleTren, 1470.8994100,2632.2998000,12.4000000,90.0000000,6,6,600); //Freight
	LastVehicleID = Vehicle_AddStatic(VehicleTren, 1412.3994100,2632.3994100,12.4000000,270.0000000,6,6,600); //Freight
	LastVehicleID = Vehicle_AddStatic(VehicleTren, 1412.3994100,2632.3994100,12.4000000,270.0000000,6,6,600); //Freight
	LastVehicleID = Vehicle_AddStatic(VehicleTren, 1412.3994100,2632.3994100,12.4000000,270.0000000,6,6,600); //Freight
}	
//Masinile de la gunoieri
GameModeInit_Gunoier()
{
	LastVehicleID = Vehicle_AddStatic(VehicleTrash, -1852.9000200, -1519.0999800, 22.5000000, 179.7500000, 103,103, 600); //Trash
	LastVehicleID = Vehicle_AddStatic(VehicleTrash, -1828.5999800, -1519.5999800, 22.5000000, 179.7470000, 103,103, 600); //Trash
	LastVehicleID = Vehicle_AddStatic(VehicleTrash, -1805.1999500, -1519.8000500, 22.5000000, 179.7470000, 103,103, 600); //Trash
	LastVehicleID = Vehicle_AddStatic(VehicleTrash, -1769.0999800, -1547.0999800, 22.5000000, 89.7470000,  103,103, 600); //Trash
	LastVehicleID = Vehicle_AddStatic(VehicleTrash, -1769.3000500, -1571.0000000, 22.5000000, 89.7470000,  103,103, 600); //Trash
	LastVehicleID = Vehicle_AddStatic(VehicleTrash, -1769.0999800, -1595.1999500, 22.5000000, 89.7470000,  103,103, 600); //Trash
	LastVehicleID = Vehicle_AddStatic(VehicleTrash, -1887.6999500, -1596.0999800, 22.5000000, 268.497000,  103,103, 600); //Trash
	LastVehicleID = Vehicle_AddStatic(VehicleTrash, -1887.6999500, -1572.0999800, 22.5000000, 268.4950000, 103,103, 600); //Trash
	LastVehicleID = Vehicle_AddStatic(VehicleTrash, -1887.8000500, -1548.4000200, 22.5000000, 268.4950000, 103,103, 600); //Trash
}
// Autobuzele de  Sofer de autobuz
GameModeInit_Busses()
{
	LastVehicleID = Vehicle_AddStatic(VehicleCoach, 1712.0106,	1386.5013, 10.7778, 197.7943, 151, 151, 600); //Coach
	LastVehicleID = Vehicle_AddStatic(VehicleCoach, 1708.9176,	1399.3015, 10.7779, 194.7451, 151, 151, 600); //Coach
	LastVehicleID = Vehicle_AddStatic(VehicleCoach, 1706.0398,	1411.2001, 10.7740, 188.4698, 151, 151, 600); //Coach
	LastVehicleID = Vehicle_AddStatic(VehicleCoach, 1704.2737,	1423.8024, 10.7759, 180.3456, 151, 151, 600); //Coach
	LastVehicleID = Vehicle_AddStatic(VehicleCoach, 1704.0707,	1437.4196, 10.8805, 177.0414, 151, 151, 600); //Coach
	LastVehicleID = Vehicle_AddStatic(VehicleCoach, 1712.8793,	1472.9255, 10.9536, 158.8489, 151, 151, 600); //Coach
	LastVehicleID = Vehicle_AddStatic(VehicleCoach, 1717.1549,	1484.6989, 10.9498, 163.1978, 151, 151, 600); //Coach
	LastVehicleID = Vehicle_AddStatic(VehicleCoach, 1720.2587,	1495.3394, 10.9499, 166.3802, 151, 151, 600); //Coach
	LastVehicleID = Vehicle_AddStatic(VehicleCoach, 1723.1229,	1507.0199, 10.9461, 169.6809, 151, 151, 600); //Coach
	LastVehicleID = Vehicle_AddStatic(VehicleCoach, 1723.8621,	1519.4700, 10.9608, 176.8207, 151, 151, 600); //Coach
}	
// Barcile de la Marinar
GameModeInit_Marinar()
{
	LastVehicleID = Vehicle_AddStatic(VehicleReefer, -1441.2788000, 509.3466000, -0.3617000, 90.2032000, 6, 79, 600); //Reefer
	LastVehicleID = Vehicle_AddStatic(VehicleReefer, -1459.2029000, 508.8911000, -0.2413000, 84.8387000, 6, 79, 600); //Reefer
	LastVehicleID = Vehicle_AddStatic(VehicleReefer, -1458.9570000, 493.3850000, -0.2587000, 90.1025000, 6, 79, 600); //Reefer
	LastVehicleID = Vehicle_AddStatic(VehicleReefer, -1478.2164000, 488.1255000, -0.2335000, 90.5337000, 6, 79, 600); //Reefer
	LastVehicleID = Vehicle_AddStatic(VehicleReefer, -1496.2190000, 488.2180000, -0.2893000, 91.4266000, 6, 79, 600); //Reefer
}	
//Taxiurile de la Taximetrist
GameModeInit_Taxi()
{
	LastVehicleID = Vehicle_AddStatic(VehicleTaxi, 1737.5000000, -1857.9000200, 13.3000000, 270.0000000, 6, 6, 600); //Taxi
	LastVehicleID = Vehicle_AddStatic(VehicleTaxi, 1746.0000000, -1857.8000500, 13.3000000, 270.0000000, 6, 6, 600); //Taxi
	LastVehicleID = Vehicle_AddStatic(VehicleTaxi, 1753.8000500, -1857.8000500, 13.3000000, 270.0000000, 6, 6, 600); //Taxi
	LastVehicleID = Vehicle_AddStatic(VehicleTaxi, 1761.8000500, -1857.6999500, 13.3000000, 270.0000000, 6, 6, 600); //Taxi
	LastVehicleID = Vehicle_AddStatic(VehicleTaxi, 1770.3000500, -1857.6999500, 13.3000000, 270.0000000, 6, 6, 600); //Taxi
	LastVehicleID = Vehicle_AddStatic(VehicleTaxi, 1729.0000000, -1857.9000200, 13.3000000, 270.0000000, 6, 6, 600); //Taxi
}
//DFT30 de la PAdurar
GameModeInit_Padurar()
{
	LastVehicleID = Vehicle_AddStatic(VehicleDFT30, -691.0839000, -2118.5654000, 26.4387000, 313.0055000, 16, 16, 600); //DFT-30
	LastVehicleID = Vehicle_AddStatic(VehicleDFT30, -680.9407000, -2106.5620000, 26.2259000, 331.8592000, 16, 16, 600); //DFT-30
	LastVehicleID = Vehicle_AddStatic(VehicleDFT30, -673.4436000, -2090.4272000, 25.6411000, 339.2577000, 16, 16, 600); //DFT-30
	LastVehicleID = Vehicle_AddStatic(VehicleDFT30, -668.0729000, -2074.6919000, 25.7951000, 341.8092000, 16, 16, 600); //DFT-30
}
// Mape Impolrtante
GameModeInit_Mape()
{
	//MAPA DE LA MAFIE
	CreateDynamicObject(2773, -2220.69995, 1050, 79.5, 0, 0, 86);
	CreateDynamicObject(2773, -2210.67407, 1057.29297, 79.525, 0, 0, 178.745);
	CreateDynamicObject(2773, -2220.69995, 1052.19995, 79.5, 0, 0, 87.742);
	CreateDynamicObject(2773, -2218.80005, 1052.09998, 79.5, 0, 0, 85.742);
	CreateDynamicObject(2773, -2200.19995, 1011, 79.5, 0, 0, 88.742);
	CreateDynamicObject(2773, -2198.30005, 1011, 79.5, 0, 0, 89.492);
	CreateDynamicObject(2773, -2196.3999, 1011, 79.5, 0, 0, 90.239);
	CreateDynamicObject(2773, -2194.5, 1011, 79.5, 0, 0, 90.236);
	CreateDynamicObject(2773, -2185, 1011, 79.5, 0, 0, 90.486);
	CreateDynamicObject(2773, -2183.1001, 1011, 79.5, 0, 0, 90.236);
	CreateDynamicObject(2773, -2181.19995, 1011, 79.5, 0, 0, 90.236);
	CreateDynamicObject(2773, -2179.30005, 1011, 79.5, 0, 0, 90.236);
	CreateDynamicObject(2773, -2177.3999, 1011, 79.5, 0, 0, 90.236);
	CreateDynamicObject(2773, -2175.5, 1011, 79.5, 0, 0, 90.236);
	CreateDynamicObject(2773, -2173.6001, 1011, 79.5, 0, 0, 90.236);
	CreateDynamicObject(2773, -2192.59961, 1011, 79.5, 0, 0, 90.236);
	CreateDynamicObject(2773, -2202.6001, 1029.40002, 79.5, 0, 0, 180.472);
	CreateDynamicObject(2773, -2202.6001, 1031.30005, 79.5, 0, 0, 180.472);
	CreateDynamicObject(2773, -2202.6001, 1033.19995, 79.5, 0, 0, 179.722);
	CreateDynamicObject(2773, -2202.6001, 1035.09998, 79.5, 0, 0, 179.97);
	CreateDynamicObject(2773, -2202.6001, 1037, 79.5, 0, 0, 179.967);
	CreateDynamicObject(2773, -2194, 1037, 79.5, 0, 0, 179.72);
	CreateDynamicObject(2773, -2194, 1035.09998, 79.5, 0, 0, 179.72);
	CreateDynamicObject(2773, -2194, 1033.19995, 79.5, 0, 0, 179.97);
	CreateDynamicObject(2773, -2194, 1031.30005, 79.5, 0, 0, 179.967);
	CreateDynamicObject(2773, -2194, 1029.40002, 79.5, 0, 0, 179.967);
	CreateDynamicObject(2773, -2186.30005, 1029.40002, 79.5, 0, 0, 179.967);
	CreateDynamicObject(2773, -2186.30005, 1031.30005, 79.5, 0, 0, 179.967);
	CreateDynamicObject(2773, -2186.30005, 1033.19995, 79.5, 0, 0, 179.967);
	CreateDynamicObject(2773, -2186.30005, 1035.09998, 79.5, 0, 0, 179.967);
	CreateDynamicObject(2773, -2186.30005, 1037, 79.5, 0, 0, 179.967);
	CreateDynamicObject(1568, -2191.6001, 1011, 76.3, 0, 0, 0);
	CreateDynamicObject(1568, -2186, 1011, 76.3, 0, 0, 359.75);
	CreateDynamicObject(1568, -2186.30005, 1028.40002, 76.2, 0, 0, 0);
	CreateDynamicObject(1568, -2194, 1028.40002, 76.2, 0, 0, 0);
	CreateDynamicObject(1568, -2202.6001, 1028.40002, 76.2, 0, 0, 0);
	CreateDynamicObject(1568, -2217.84009, 1052.06799, 76.225, 0, 0, 0);
	CreateDynamicObject(1568, -2217.85693, 1049.875, 76.225, 0, 0, 0);
	CreateDynamicObject(1238, -2179.42285, 1005.23535, 79.268, 0, 0, 0);
	CreateDynamicObject(1238, -2179.84473, 988.48242, 79.318, 0, 0, 0);
	CreateDynamicObject(2773, -2218.7998, 1049.89941, 79.5, 0, 0, 87.742);
	CreateDynamicObject(2773, -2210.7229, 1055.38794, 79.525, 0, 0, 178.492);
	CreateDynamicObject(2773, -2208.23608, 1057.29199, 79.525, 0, 0, 178.489);
	CreateDynamicObject(2773, -2208.27905, 1055.38794, 79.525, 0, 0, 178.489);
	CreateDynamicObject(2773, -2205.81689, 1057.29395, 79.525, 0, 0, 178.489);
	CreateDynamicObject(2773, -2205.86304, 1055.36499, 79.525, 0, 0, 178.489);
	CreateDynamicObject(1568, -2210.72998, 1054.41296, 76.233, 0, 0, 0);
	CreateDynamicObject(1568, -2208.30005, 1054.40698, 76.233, 0, 0, 0);
	CreateDynamicObject(1568, -2205.89502, 1054.37695, 76.233, 0, 0, 0);
	CreateDynamicObject(3578, -2188.54907, 1016.39099, 78.111, 0, 0, 0);
	CreateDynamicObject(3578, -2188.54004, 1016.87598, 78.111, 0, 0, 0);
	CreateDynamicObject(3578, -2188.552, 1017.39301, 78.111, 0, 0, 0);
	CreateDynamicObject(3578, -2188.5481, 1017.89502, 78.111, 0, 0, 0);
	CreateDynamicObject(3578, -2188.54395, 1018.39697, 78.111, 0, 0, 0);
	CreateDynamicObject(3578, -2188.54004, 1018.89801, 78.111, 0, 0, 0);
	CreateDynamicObject(3578, -2188.53589, 1019.39899, 78.111, 0, 0, 0);
	CreateDynamicObject(3578, -2188.53394, 1019.87598, 78.111, 0, 0, 0);
	CreateDynamicObject(3578, -2188.52905, 1020.37799, 78.111, 0, 0, 0);
	CreateDynamicObject(3578, -2188.5249, 1020.88, 78.111, 0, 0, 0);
	CreateDynamicObject(3578, -2188.521, 1021.38202, 78.111, 0, 0, 0);
	CreateDynamicObject(3578, -2188.51709, 1021.88397, 78.111, 0, 0, 0);
	CreateDynamicObject(3578, -2188.51294, 1022.38599, 78.111, 0, 0, 0);
	CreateDynamicObject(3578, -2188.50903, 1022.888, 78.111, 0, 0, 0);
	CreateDynamicObject(3578, -2188.50488, 1023.39001, 78.111, 0, 0, 0);
	//Mapa la G sf la groapa de gunoi are objecte scoase
	CreateDynamicObject(3755,-1889.0000000,-1571.5999800,26.5000000,0.0000000,0.0000000,90.0000000); //object(las2warhus_las2) (1)
	CreateDynamicObject(8661,-1887.0996100,-1509.6992200,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (1)
	CreateDynamicObject(8661,-1847.3000500,-1509.6999500,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (2)
	CreateDynamicObject(8661,-1887.0999800,-1529.6999500,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (3)
	CreateDynamicObject(8661,-1887.0999800,-1549.5999800,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (4)
	CreateDynamicObject(8661,-1887.0999800,-1569.5000000,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (5)
	CreateDynamicObject(8661,-1887.0999800,-1589.1999500,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (6)
	CreateDynamicObject(8661,-1887.0999800,-1609.0999800,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (7)
	CreateDynamicObject(8661,-1887.0999800,-1629.0000000,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (8)
	CreateDynamicObject(8661,-1887.0999800,-1648.8000500,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (9)
	CreateDynamicObject(8661,-1887.0999800,-1668.6999500,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (10)
	CreateDynamicObject(8661,-1887.0999800,-1688.4000200,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (11)
	CreateDynamicObject(8661,-1887.0996100,-1708.1992200,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (12)
	CreateDynamicObject(8661,-1887.0999800,-1727.6999500,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (13)
	CreateDynamicObject(8661,-1887.0999800,-1747.5000000,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (14)
	CreateDynamicObject(8661,-1887.0999800,-1766.1999500,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (15)
	CreateDynamicObject(8661,-1847.3000500,-1529.5999800,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (16)
	CreateDynamicObject(8661,-1847.3000500,-1549.1999500,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (17)
	CreateDynamicObject(8661,-1847.3000500,-1568.5999800,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (18)
	CreateDynamicObject(8661,-1847.2998000,-1587.8994100,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (19)
	CreateDynamicObject(8661,-1847.3000500,-1607.5999800,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (20)
	CreateDynamicObject(8661,-1847.2998000,-1627.2998000,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (22)
	CreateDynamicObject(8661,-1847.3000500,-1646.8000500,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (24)
	CreateDynamicObject(8661,-1847.3000500,-1666.0999800,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (25)
	CreateDynamicObject(8661,-1847.3000500,-1685.5000000,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (27)
	CreateDynamicObject(8661,-1847.3000500,-1704.9000200,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (29)
	CreateDynamicObject(8661,-1847.3000500,-1724.0999800,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (30)
	CreateDynamicObject(8661,-1847.3000500,-1739.8000500,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (32)
	CreateDynamicObject(8661,-1926.3000500,-1629.0000000,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (36)
	CreateDynamicObject(8661,-1926.3000500,-1648.5000000,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (37)
	CreateDynamicObject(8661,-1926.3000500,-1668.0999800,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (38)
	CreateDynamicObject(8661,-1926.3000500,-1687.5999800,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (39)
	CreateDynamicObject(8661,-1926.5000000,-1707.9000200,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (40)
	CreateDynamicObject(8661,-1926.5000000,-1727.1999500,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (41)
	CreateDynamicObject(8661,-1926.5000000,-1746.8000500,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (42)
	CreateDynamicObject(8661,-1926.5000000,-1765.1999500,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (43)
	CreateDynamicObject(8661,-1808.5999800,-1509.6999500,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (47)
	CreateDynamicObject(8661,-1808.5999800,-1529.5000000,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (48)
	CreateDynamicObject(8661,-1808.5999800,-1549.0000000,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (49)
	CreateDynamicObject(8661,-1808.5999800,-1568.9000200,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (50)
	CreateDynamicObject(8661,-1808.5999800,-1588.6999500,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (51)
	CreateDynamicObject(8661,-1808.5999800,-1608.3000500,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (52)
	CreateDynamicObject(8661,-1808.5999800,-1628.0000000,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (53)
	CreateDynamicObject(8661,-1808.5999800,-1647.5000000,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (54)
	CreateDynamicObject(8661,-1808.5999800,-1667.0000000,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (55)
	CreateDynamicObject(8661,-1808.5999800,-1686.5999800,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (56)
	CreateDynamicObject(8661,-1808.5999800,-1705.9000200,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (57)
	CreateDynamicObject(8661,-1769.5000000,-1509.6999500,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (58)
	CreateDynamicObject(8661,-1769.5000000,-1529.5000000,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (59)
	CreateDynamicObject(8661,-1769.5000000,-1549.3000500,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (60)
	CreateDynamicObject(8661,-1769.5000000,-1568.9000200,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (61)
	CreateDynamicObject(8661,-1769.5000000,-1588.5999800,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (62)
	CreateDynamicObject(8661,-1769.5000000,-1608.5000000,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (63)
	CreateDynamicObject(8661,-1769.5000000,-1628.0000000,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (64)
	CreateDynamicObject(8661,-1769.5000000,-1647.3000500,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (65)
	CreateDynamicObject(8661,-1769.5000000,-1667.0999800,20.9000000,0.0000000,0.0000000,0.0000000); //object(gnhtelgrnd_lvs) (66)
	CreateDynamicObject(8661,-1769.5000000,-1588.5999800,20.4000000,0.0000000,180.0000000,0.0000000); //object(gnhtelgrnd_lvs) (70)
	CreateDynamicObject(8661,-1769.5000000,-1569.4000200,20.4000000,0.0000000,179.9950000,0.0000000); //object(gnhtelgrnd_lvs) (71)
	CreateDynamicObject(8661,-1769.5000000,-1549.5999800,20.4000000,0.0000000,179.9950000,0.0000000); //object(gnhtelgrnd_lvs) (72)
	CreateDynamicObject(8661,-1769.5000000,-1530.0999800,20.4000000,0.0000000,179.9950000,0.0000000); //object(gnhtelgrnd_lvs) (73)
	CreateDynamicObject(8661,-1769.5000000,-1510.6999500,20.4000000,0.0000000,179.9950000,0.0000000); //object(gnhtelgrnd_lvs) (74)
	CreateDynamicObject(8661,-1769.5000000,-1509.8000500,20.4000000,0.0000000,179.9950000,0.0000000); //object(gnhtelgrnd_lvs) (75)
	CreateDynamicObject(8661,-1808.5999800,-1509.6999500,19.0000000,0.0000000,176.0000000,0.0000000); //object(gnhtelgrnd_lvs) (76)
	CreateDynamicObject(8661,-1808.5999800,-1529.5000000,19.0000000,0.0000000,175.9950000,0.0000000); //object(gnhtelgrnd_lvs) (77)
	CreateDynamicObject(8661,-1808.5999800,-1549.0999800,19.0000000,0.0000000,175.9950000,0.0000000); //object(gnhtelgrnd_lvs) (78)
	CreateDynamicObject(8661,-1808.5999800,-1568.5999800,19.0000000,0.0000000,175.9950000,0.0000000); //object(gnhtelgrnd_lvs) (79)
	CreateDynamicObject(8661,-1808.5999800,-1587.0999800,19.0000000,0.0000000,175.9950000,0.0000000); //object(gnhtelgrnd_lvs) (80)
	CreateDynamicObject(8661,-1847.3000500,-1509.6999500,17.6000000,0.0000000,180.0000000,0.0000000); //object(gnhtelgrnd_lvs) (81)
	CreateDynamicObject(8661,-1847.3000500,-1528.6999500,17.6000000,0.0000000,179.9950000,0.0000000); //object(gnhtelgrnd_lvs) (82)
	CreateDynamicObject(987,-1895.8994100,-1500.1992200,20.7000000,0.0000000,0.0000000,181.0000000); //object(elecfence_bar) (1)
	CreateDynamicObject(987,-1883.9000200,-1500.0000000,20.7000000,0.0000000,0.0000000,181.2500000); //object(elecfence_bar) (2)
	CreateDynamicObject(987,-1749.8000500,-1523.1999500,20.7000000,0.0000000,0.0000000,90.0000000); //object(elecfence_bar) (3)
	CreateDynamicObject(987,-1749.8000500,-1534.6999500,20.7000000,0.0000000,0.0000000,90.0000000); //object(elecfence_bar) (4)
	CreateDynamicObject(987,-1749.8000500,-1545.9000200,20.7000000,0.0000000,0.0000000,90.0000000); //object(elecfence_bar) (5)
	CreateDynamicObject(987,-1749.8000500,-1557.4000200,20.7000000,0.0000000,0.0000000,90.0000000); //object(elecfence_bar) (6)
	CreateDynamicObject(987,-1872.0000000,-1499.9000200,20.7000000,0.0000000,0.0000000,180.7470000); //object(elecfence_bar) (7)
	CreateDynamicObject(987,-1749.8000500,-1568.8000500,20.7000000,0.0000000,0.0000000,90.0000000); //object(elecfence_bar) (8)
	CreateDynamicObject(987,-1860.0999800,-1500.0999800,20.7000000,0.0000000,0.0000000,179.4920000); //object(elecfence_bar) (9)
	CreateDynamicObject(987,-1749.8000500,-1580.0999800,20.7000000,0.0000000,0.0000000,90.0000000); //object(elecfence_bar) (10)
	CreateDynamicObject(987,-1749.8000500,-1591.6999500,20.7000000,0.0000000,0.0000000,90.0000000); //object(elecfence_bar) (11)
	CreateDynamicObject(987,-1749.8000500,-1602.9000200,20.7000000,0.0000000,0.0000000,90.0000000); //object(elecfence_bar) (12)
	CreateDynamicObject(987,-1848.1999500,-1500.3000500,20.7000000,0.0000000,0.0000000,179.4890000); //object(elecfence_bar) (13)
	CreateDynamicObject(987,-1836.3000500,-1500.3000500,20.7000000,0.0000000,0.0000000,179.4890000); //object(elecfence_bar) (14)
	CreateDynamicObject(987,-1749.8000500,-1614.3000500,20.7000000,0.0000000,0.0000000,90.0000000); //object(elecfence_bar) (15)
	CreateDynamicObject(987,-1824.4000200,-1500.3000500,20.7000000,0.0000000,0.0000000,179.4890000); //object(elecfence_bar) (16)
	CreateDynamicObject(987,-1749.8000500,-1625.5999800,20.7000000,0.0000000,0.0000000,90.0000000); //object(elecfence_bar) (17)
	CreateDynamicObject(987,-1749.8000500,-1636.9000200,20.7000000,0.0000000,0.0000000,90.0000000); //object(elecfence_bar) (18)
	CreateDynamicObject(987,-1749.8000500,-1648.0000000,20.7000000,0.0000000,0.0000000,90.0000000); //object(elecfence_bar) (19)
	CreateDynamicObject(987,-1749.8000500,-1659.5000000,20.7000000,0.0000000,0.0000000,90.0000000); //object(elecfence_bar) (20)
	CreateDynamicObject(987,-1812.5000000,-1500.3000500,20.7000000,0.0000000,0.0000000,179.4890000); //object(elecfence_bar) (21)
	CreateDynamicObject(987,-1800.5000000,-1500.3000500,20.7000000,0.0000000,0.0000000,179.4890000); //object(elecfence_bar) (22)
	CreateDynamicObject(987,-1788.5999800,-1500.3000500,20.7000000,0.0000000,0.0000000,179.4890000); //object(elecfence_bar) (23)
	CreateDynamicObject(987,-1776.5999800,-1500.3000500,20.7000000,0.0000000,0.0000000,179.4890000); //object(elecfence_bar) (24)
	CreateDynamicObject(987,-1764.6999500,-1500.3000500,20.7000000,0.0000000,0.0000000,179.4890000); //object(elecfence_bar) (25)
	CreateDynamicObject(987,-1752.8000500,-1500.3000500,20.7000000,0.0000000,0.0000000,179.4890000); //object(elecfence_bar) (26)
	CreateDynamicObject(987,-1749.5000000,-1500.3000500,20.7000000,0.0000000,0.0000000,179.4890000); //object(elecfence_bar) (27)
	CreateDynamicObject(987,-1749.9000200,-1512.3000500,20.7000000,0.0000000,0.0000000,83.4890000); //object(elecfence_bar) (28)
	CreateDynamicObject(17031,-1762.9000200,-1509.0000000,16.8000000,8.0000000,0.0000000,52.0000000); //object(cunt_rockgp2_13) (1)
	CreateDynamicObject(3755,-1767.9000200,-1571.5000000,26.5000000,0.0000000,0.0000000,270.0000000); //object(las2warhus_las2) (3)
	CreateDynamicObject(17031,-1757.0996100,-1512.7998000,14.0000000,2.7360000,289.8140000,59.3590000); //object(cunt_rockgp2_13) (2)
	CreateDynamicObject(3755,-1828.3000500,-1518.0999800,26.4000000,0.0000000,0.0000000,359.5000000); //object(las2warhus_las2) (4)
	CreateDynamicObject(3330,-1754.5999800,-1594.5000000,-44.0000000,0.0000000,180.0000000,90.0000000); //object(cxrf_brigleg) (2)
	CreateDynamicObject(3330,-1754.5000000,-1573.5999800,-44.0000000,0.0000000,179.9950000,90.0000000); //object(cxrf_brigleg) (3)
	CreateDynamicObject(3330,-1754.1999500,-1531.1999500,-44.0000000,0.0000000,179.9950000,90.0000000); //object(cxrf_brigleg) (5)
	CreateDynamicObject(3330,-1790.8000500,-1504.8000500,-44.0000000,0.0000000,180.0000000,180.0000000); //object(cxrf_brigleg) (6)
	CreateDynamicObject(3330,-1813.5999800,-1504.5999800,-44.0000000,0.0000000,179.9950000,179.9950000); //object(cxrf_brigleg) (7)
	CreateDynamicObject(3330,-1861.8000500,-1504.5999800,-44.0000000,0.0000000,179.9950000,179.9950000); //object(cxrf_brigleg) (13)
	CreateDynamicObject(3330,-1885.1999500,-1504.5000000,-44.0000000,0.0000000,179.9950000,179.9950000); //object(cxrf_brigleg) (14)
	CreateDynamicObject(3330,-1907.3000500,-1504.5000000,-44.0000000,0.0000000,179.9950000,179.9950000); //object(cxrf_brigleg) (15)
	CreateDynamicObject(17031,-1921.8994100,-1501.8994100,11.7000000,7.9160000,351.9200000,355.1170000); //object(cunt_rockgp2_13) (3)
	CreateDynamicObject(5291,-1935.0000000,-1669.3000500,29.7000000,0.0000000,358.0000000,2.0000000); //object(snpedscrsap_las01) (2)
	CreateDynamicObject(5291,-1926.9000200,-1669.3000500,29.7000000,0.0000000,357.9950000,2.0000000); //object(snpedscrsap_las01) (3)
	CreateDynamicObject(5291,-1919.4000200,-1669.3000500,29.7000000,0.0000000,357.9950000,2.0000000); //object(snpedscrsap_las01) (4)
	CreateDynamicObject(5291,-1910.4000200,-1669.3000500,29.0000000,0.0000000,357.9950000,2.0000000); //object(snpedscrsap_las01) (5)
	CreateDynamicObject(5291,-1902.0999800,-1668.8000500,29.0000000,0.0000000,357.9950000,2.0000000); //object(snpedscrsap_las01) (6)
	CreateDynamicObject(1265,-1899.3000500,-1648.5999800,21.4000000,0.0000000,0.0000000,0.0000000); //object(blackbag2) (1)
	CreateDynamicObject(1265,-1897.0000000,-1648.1999500,21.2000000,0.0000000,0.0000000,0.0000000); //object(blackbag2) (2)
	CreateDynamicObject(1236,-1897.3000500,-1693.9000200,21.5000000,0.0000000,0.0000000,268.0000000); //object(rcyclbank01) (1)
	CreateDynamicObject(12957,-1898.0000000,-1645.3000500,21.5000000,359.4950000,0.0000000,129.9960000); //object(sw_pickupwreck01) (1)
	CreateDynamicObject(17031,-1759.1999500,-1660.5999800,15.5000000,7.9160000,351.9200000,177.1170000); //object(cunt_rockgp2_13) (5)
	CreateDynamicObject(17031,-1771.5999800,-1647.8000500,15.5000000,7.9100000,351.9140000,177.1160000); //object(cunt_rockgp2_13) (6)
	CreateDynamicObject(17031,-1784.0000000,-1647.8000500,15.5000000,7.9100000,351.9140000,177.1160000); //object(cunt_rockgp2_13) (7)
	CreateDynamicObject(17031,-1796.6999500,-1653.3000500,15.5000000,7.9100000,351.9140000,177.1160000); //object(cunt_rockgp2_13) (8)
	CreateDynamicObject(17031,-1808.0999800,-1650.0000000,11.8000000,7.9100000,351.9140000,349.1160000); //object(cunt_rockgp2_13) (9)
	CreateDynamicObject(17031,-1796.5999800,-1656.9000200,11.8000000,7.9050000,351.9090000,349.1130000); //object(cunt_rockgp2_13) (10)
	CreateDynamicObject(17031,-1791.0999800,-1674.1999500,10.6000000,7.9050000,351.9090000,321.1130000); //object(cunt_rockgp2_13) (11)
	CreateDynamicObject(2237,-1864.5999800,-1650.3000500,24.7000000,317.5000000,0.0000000,24.5000000); //object(cj_shovel2) (1)
	CreateDynamicObject(17031,-1759.9000200,-1646.3000500,14.3000000,7.9100000,351.9140000,177.1160000); //object(cunt_rockgp2_13) (12)
	CreateDynamicObject(17031,-1780.5999800,-1674.1999500,10.6000000,7.8990000,351.9090000,321.1080000); //object(cunt_rockgp2_13) (13)
	CreateDynamicObject(2228,-1860.9000200,-1650.0000000,25.7000000,0.0000000,0.0000000,0.0000000); //object(cj_shovel) (1)
	CreateDynamicObject(2237,-1859.8000500,-1656.0000000,24.9000000,317.4990000,0.0000000,224.5000000); //object(cj_shovel2) (2)
	CreateDynamicObject(2228,-1857.5999800,-1652.9000200,25.6000000,0.0000000,0.0000000,0.0000000); //object(cj_shovel) (2)
	CreateDynamicObject(2237,-1854.5000000,-1659.1999500,22.6000000,0.0000000,0.0000000,0.0000000); //object(cj_shovel2) (3)
	CreateDynamicObject(17031,-1747.5999800,-1506.5000000,-0.8000000,6.9430000,329.7500000,23.8460000); //object(cunt_rockgp2_13) (14)
	CreateDynamicObject(2237,-1857.3000500,-1647.4000200,25.5000000,317.4990000,0.0000000,24.5000000); //object(cj_shovel2) (4)
	CreateDynamicObject(3578,-1769.9000200,-1612.1999500,20.2000000,0.0000000,0.0000000,0.0000000); //object(dockbarr1_la) (1)
	CreateDynamicObject(3578,-1780.0999800,-1612.1999500,20.2000000,0.0000000,0.0000000,0.0000000); //object(dockbarr1_la) (2)
	CreateDynamicObject(3578,-1790.4000200,-1612.1999500,20.2000000,0.0000000,0.0000000,0.0000000); //object(dockbarr1_la) (3)
	CreateDynamicObject(3578,-1800.5999800,-1612.1999500,20.2000000,0.0000000,0.0000000,0.0000000); //object(dockbarr1_la) (4)
	CreateDynamicObject(3578,-1810.8000500,-1612.1999500,20.2000000,0.0000000,0.0000000,0.2500000); //object(dockbarr1_la) (5)
	CreateDynamicObject(3578,-1821.0000000,-1612.1999500,20.2000000,0.0000000,0.0000000,0.0000000); //object(dockbarr1_la) (6)
	CreateDynamicObject(3578,-1831.1999500,-1612.1999500,20.2000000,0.0000000,0.0000000,0.0000000); //object(dockbarr1_la) (7)
	CreateDynamicObject(3578,-1841.5000000,-1612.1999500,20.2000000,0.0000000,0.0000000,0.0000000); //object(dockbarr1_la) (8)
	CreateDynamicObject(3578,-1851.6999500,-1612.1999500,20.2000000,0.0000000,0.0000000,0.0000000); //object(dockbarr1_la) (9)
	CreateDynamicObject(3578,-1861.9000200,-1612.1999500,20.2000000,0.0000000,0.0000000,0.0000000); //object(dockbarr1_la) (10)
	CreateDynamicObject(3578,-1872.0999800,-1612.1999500,20.2000000,0.0000000,0.0000000,0.0000000); //object(dockbarr1_la) (11)
	CreateDynamicObject(3578,-1882.3000500,-1612.1999500,20.2000000,0.0000000,0.0000000,0.0000000); //object(dockbarr1_la) (12)
	CreateDynamicObject(3578,-1892.5000000,-1612.1999500,20.2000000,0.0000000,0.0000000,0.0000000); //object(dockbarr1_la) (13)
	CreateDynamicObject(3406,-1901.5999800,-1625.6999500,22.8000000,0.0000000,0.0000000,0.0000000); //object(cxref_woodjetty) (1)
	CreateDynamicObject(987,-1907.6999500,-1500.3000500,20.7000000,0.0000000,0.0000000,271.0000000); //object(elecfence_bar) (42)
	CreateDynamicObject(987,-1907.5000000,-1512.0999800,20.7000000,0.0000000,0.0000000,271.0000000); //object(elecfence_bar) (43)
	CreateDynamicObject(987,-1907.3000500,-1524.0000000,20.7000000,0.0000000,0.0000000,271.0000000); //object(elecfence_bar) (44)
	CreateDynamicObject(17031,-1911.5000000,-1565.3000500,7.7000000,7.9160000,351.9200000,173.1170000); //object(cunt_rockgp2_13) (15)
	CreateDynamicObject(3406,-1901.5999800,-1627.6999500,22.8000000,0.0000000,0.0000000,0.0000000); //object(cxref_woodjetty) (2)
	CreateDynamicObject(3406,-1894.4000200,-1627.6999500,20.7000000,0.0000000,28.0000000,0.0000000); //object(cxref_woodjetty) (3)
	CreateDynamicObject(3406,-1894.4000200,-1625.6999500,20.7000000,0.0000000,27.9990000,0.0000000); //object(cxref_woodjetty) (4)
	CreateDynamicObject(978,-1894.3000500,-1612.0999800,21.4000000,0.0000000,0.0000000,0.0000000); //object(sub_roadright) (4)
	CreateDynamicObject(978,-1894.3000500,-1612.3000500,21.4000000,0.0000000,0.0000000,180.0000000); //object(sub_roadright) (5)
	CreateDynamicObject(978,-1885.0999800,-1612.3000500,21.4000000,0.0000000,0.0000000,179.9950000); //object(sub_roadright) (7)
	CreateDynamicObject(978,-1875.8000500,-1612.3000500,21.4000000,0.0000000,0.0000000,179.9950000); //object(sub_roadright) (8)
	CreateDynamicObject(978,-1885.0000000,-1612.0999800,21.4000000,0.0000000,0.0000000,0.0000000); //object(sub_roadright) (9)
	CreateDynamicObject(978,-1875.6999500,-1612.0999800,21.4000000,0.0000000,0.0000000,0.0000000); //object(sub_roadright) (10)
	CreateDynamicObject(978,-1781.6999500,-1612.3000500,21.4000000,0.0000000,0.0000000,179.9950000); //object(sub_roadright) (11)
	CreateDynamicObject(978,-1772.4000200,-1612.3000500,21.4000000,0.0000000,0.0000000,179.9950000); //object(sub_roadright) (12)
	CreateDynamicObject(978,-1763.0999800,-1612.3000500,21.4000000,0.0000000,0.0000000,179.9950000); //object(sub_roadright) (13)
	CreateDynamicObject(978,-1781.6999500,-1612.0999800,21.4000000,0.0000000,0.0000000,0.0000000); //object(sub_roadright) (14)
	CreateDynamicObject(978,-1772.4000200,-1612.0999800,21.4000000,0.0000000,0.0000000,0.0000000); //object(sub_roadright) (15)
	CreateDynamicObject(978,-1763.0000000,-1612.0999800,21.4000000,0.0000000,0.0000000,0.0000000); //object(sub_roadright) (16)
	CreateDynamicObject(1597,-1887.1999500,-1613.6999500,23.6000000,0.0000000,0.0000000,90.0000000); //object(cntrlrsac1) (1)
	CreateDynamicObject(1597,-1827.5000000,-1563.3000500,23.4000000,0.0000000,0.0000000,180.0000000); //object(cntrlrsac1) (2)
	CreateDynamicObject(1597,-1781.0000000,-1613.6999500,23.6000000,0.0000000,0.0000000,90.0000000); //object(cntrlrsac1) (3)
	CreateDynamicObject(1597,-1769.8000500,-1613.6999500,23.6000000,0.0000000,0.0000000,90.0000000); //object(cntrlrsac1) (4)
	CreateDynamicObject(7236,-1798.0999800,-1667.9000200,43.5000000,0.0000000,0.0000000,0.0000000); //object(vegasplant03b) (1)
	CreateDynamicObject(7236,-1776.9000200,-1634.0000000,43.5000000,0.0000000,0.0000000,0.0000000); //object(vegasplant03b) (2)
	CreateDynamicObject(2780,-1773.5000000,-1633.8000500,66.4000000,0.0000000,0.0000000,0.0000000); //object(cj_smoke_mach) (1)
	CreateDynamicObject(2780,-1780.8000500,-1633.8000500,66.4000000,0.0000000,0.0000000,0.0000000); //object(cj_smoke_mach) (2)
	CreateDynamicObject(2780,-1777.0000000,-1641.0000000,66.4000000,0.0000000,0.0000000,0.0000000); //object(cj_smoke_mach) (3)
	CreateDynamicObject(2780,-1777.0000000,-1626.8000500,66.4000000,0.0000000,0.0000000,0.0000000); //object(cj_smoke_mach) (4)
	CreateDynamicObject(2780,-1795.9000200,-1659.5000000,66.4000000,0.0000000,0.0000000,0.0000000); //object(cj_smoke_mach) (5)
	CreateDynamicObject(2780,-1802.0999800,-1662.8000500,66.4000000,0.0000000,0.0000000,0.0000000); //object(cj_smoke_mach) (6)
	CreateDynamicObject(2780,-1803.3000500,-1667.8000500,66.4000000,0.0000000,0.0000000,0.0000000); //object(cj_smoke_mach) (7)
	CreateDynamicObject(2780,-1800.5000000,-1672.3000500,66.4000000,0.0000000,0.0000000,0.0000000); //object(cj_smoke_mach) (8)
	CreateDynamicObject(2780,-1795.5000000,-1674.5000000,66.4000000,0.0000000,0.0000000,0.0000000); //object(cj_smoke_mach) (9)
	CreateDynamicObject(2780,-1791.0000000,-1667.5000000,66.4000000,0.0000000,0.0000000,0.0000000); //object(cj_smoke_mach) (10)
	CreateDynamicObject(2780,-1790.5999800,-1663.1999500,66.2000000,0.0000000,0.0000000,0.0000000); //object(cj_smoke_mach) (11)
	CreateDynamicObject(13646,-1904.6999500,-1638.6999500,21.4000000,0.0000000,0.0000000,0.0000000); //object(ramplandpad) (1)
	CreateDynamicObject(13646,-1898.4000200,-1638.6999500,21.4000000,0.0000000,0.0000000,0.0000000); //object(ramplandpad) (2)
	CreateDynamicObject(13646,-1892.4000200,-1638.6999500,21.4000000,0.0000000,0.0000000,0.0000000); //object(ramplandpad) (3)
	CreateDynamicObject(11461,-1901.9000200,-1620.5999800,19.9000000,0.0000000,0.0000000,60.0000000); //object(des_nwwtower) (1)
	CreateDynamicObject(1597,-1877.0000000,-1613.6992200,23.6000000,0.0000000,0.0000000,90.0000000); //object(cntrlrsac1) (5)
	CreateDynamicObject(1597,-1827.5000000,-1572.9000200,23.4000000,0.0000000,0.0000000,179.9950000); //object(cntrlrsac1) (6)
	CreateDynamicObject(1597,-1827.5000000,-1582.5999800,23.4000000,0.0000000,0.0000000,179.9950000); //object(cntrlrsac1) (7)
	CreateDynamicObject(1597,-1827.5000000,-1592.1999500,23.4000000,0.0000000,0.0000000,179.9950000); //object(cntrlrsac1) (8)
	CreateDynamicObject(1597,-1827.5000000,-1553.5999800,23.4000000,0.0000000,0.0000000,179.9950000); //object(cntrlrsac1) (9)
	CreateDynamicObject(1597,-1827.5000000,-1601.9000200,23.4000000,0.0000000,0.0000000,179.9950000); //object(cntrlrsac1) (10)
	CreateDynamicObject(1597,-1827.5000000,-1543.9000200,23.4000000,0.0000000,0.0000000,179.9950000); //object(cntrlrsac1) (11)
	CreateDynamicObject(13646,-1864.4000200,-1654.3000500,23.3000000,0.0000000,330.0000000,30.0000000); //object(ramplandpad) (4)
	CreateDynamicObject(13646,-1860.0999800,-1657.3000500,23.3000000,0.0000000,330.0000000,60.0000000); //object(ramplandpad) (5)
	CreateDynamicObject(13646,-1854.0999800,-1653.8000500,23.3000000,0.0000000,330.0000000,150.0000000); //object(ramplandpad) (6)
	CreateDynamicObject(13646,-1853.8000500,-1646.3000500,23.3000000,0.0000000,330.0000000,210.0000000); //object(ramplandpad) (7)
	CreateDynamicObject(13646,-1862.8000500,-1646.0000000,23.3000000,0.0000000,330.0000000,300.0000000); //object(ramplandpad) (8)

	
	//Mapa facuta de arnold de mine la Spawn truckeri are si objecte scoase
	CreateDynamicObject(3755, 1392.59998, 1165.50000, 15.40000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3776, 1316.90002, 1075.90002, 18.50000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(11081, 1291.30005, 1091.19995, 15.70000,   0.00000, 0.00000, 359.75000);
	CreateDynamicObject(11461, 1353.00000, 1066.00000, 8.30000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3463, 1356.69995, 1147.59998, 10.80000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(3755, 1298.39941, 1138.89941, 15.30000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(3755, 1477.50000, 1078.59998, 15.40000,   0.00000, 0.00000, 270.00000);
	CreateDynamicObject(10814, 1479.80005, 1007.40002, 13.40000,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(3755, 1438.19995, 928.00000, 15.40000,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(8661, 1476.80005, 933.50000, 9.90000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(8661, 1477.00000, 953.40002, 9.90000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(8661, 1476.90002, 973.29999, 9.90000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(8661, 1436.90002, 973.29999, 9.90000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(8661, 1397.40002, 973.29999, 9.90000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(8661, 1437.00000, 953.40002, 9.90000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(8661, 1397.30005, 953.40002, 9.90000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(8661, 1436.90002, 933.50000, 9.90000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(8661, 1397.59998, 933.50000, 9.90000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(12930, 1488.59998, 922.29999, 10.70000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3578, 1491.80005, 983.29999, 9.20000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3578, 1481.50000, 983.29999, 9.20000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3578, 1471.19995, 983.29999, 9.20000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3578, 1460.90002, 983.29999, 9.20000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3578, 1450.59998, 983.29999, 9.20000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3578, 1440.30005, 983.29999, 9.20000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3578, 1430.00000, 983.29999, 9.20000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3578, 1419.69995, 983.29999, 9.20000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3578, 1409.40002, 983.29999, 9.20000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3578, 1399.09998, 983.29999, 9.20000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3578, 1388.80005, 983.29999, 9.20000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3578, 1382.59998, 983.29999, 9.20000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(8661, 1477.00000, 1012.70001, 9.90000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(8661, 1437.00000, 1012.70001, 9.90000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(8661, 1437.00000, 1032.50000, 9.90000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(8661, 1437.23865, 1051.84375, 9.90000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(8661, 1437.06335, 1071.50037, 9.90000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(8661, 1437.00000, 1091.40002, 9.90000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(8661, 1437.00000, 1111.19995, 9.90000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(8661, 1477.00000, 1032.40002, 9.90000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(8661, 1477.00000, 1052.19995, 9.90000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(8661, 1477.00000, 1072.00000, 9.90000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(8661, 1477.00000, 1091.40002, 9.90000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(8661, 1477.00000, 1111.19995, 9.90000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3578, 1492.09998, 1002.90002, 9.20000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3578, 1481.80005, 1002.90002, 9.20000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3578, 1471.59998, 1002.90002, 9.20000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3578, 1461.40002, 1002.90002, 9.20000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3578, 1451.19995, 1002.90002, 9.20000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3578, 1441.00000, 1002.90002, 9.20000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3578, 1430.80005, 1002.90002, 9.20000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3578, 1422.09998, 1002.90002, 9.20000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3578, 1417.19995, 1007.79999, 9.20000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(3578, 1417.19995, 1018.00000, 9.20000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(3578, 1417.19995, 1028.30005, 9.20000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(3578, 1417.19995, 1038.59998, 9.20000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(3578, 1417.19995, 1048.90002, 9.20000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(3578, 1417.19995, 1059.09998, 9.20000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(3578, 1417.19995, 1069.30005, 9.20000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(3578, 1417.19995, 1079.50000, 9.20000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(3578, 1417.19995, 1089.69995, 9.20000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(3578, 1417.19995, 1099.80005, 9.20000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(3578, 1417.19995, 1110.00000, 9.20000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(3578, 1417.19995, 1116.00000, 9.20000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(3578, 1422.09998, 1121.00000, 9.20000,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(3578, 1432.00000, 1121.00000, 9.20000,   0.00000, 0.00000, 179.99500);
	CreateDynamicObject(3578, 1442.00000, 1121.00000, 9.20000,   0.00000, 0.00000, 179.99500);
	CreateDynamicObject(3578, 1451.80005, 1121.00000, 9.20000,   0.00000, 0.00000, 179.99500);
	CreateDynamicObject(3578, 1461.50000, 1121.00000, 9.20000,   0.00000, 0.00000, 179.99500);
	CreateDynamicObject(3578, 1471.30005, 1121.00000, 9.20000,   0.00000, 0.00000, 179.99500);
	CreateDynamicObject(3578, 1481.00000, 1121.00000, 9.20000,   0.00000, 0.00000, 179.99500);
	CreateDynamicObject(3578, 1490.69995, 1121.00000, 9.20000,   0.00000, 0.00000, 179.99500);
	CreateDynamicObject(3578, 1492.19995, 1121.00000, 9.20000,   0.00000, 0.00000, 179.99500);
	CreateDynamicObject(615, 1402.59998, 902.09998, 8.00000,   0.00000, 0.00000, 211.50900);
	CreateDynamicObject(3749, 1495.40002, 993.20001, 15.70000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1267, 1385.00000, 918.00000, 24.20000,   0.00000, 0.00000, 60.00000);
	CreateDynamicObject(17031, 1366.19995, 984.79999, 2.70000,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(17031, 1370.19995, 933.20001, 2.70000,   0.00000, 0.00000, 179.99500);
	CreateDynamicObject(1267, 1486.39941, 1010.50000, 23.50000,   0.00000, 0.00000, 59.99600);
	CreateDynamicObject(16114, 1321.69995, 1054.50000, -2.70000,   0.00000, 0.00000, 60.00000);
	CreateDynamicObject(16114, 1264.30005, 1148.19995, 2.10000,   0.00000, 0.00000, 210.00000);
	CreateDynamicObject(3463, 1340.50000, 1063.09961, 8.60000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3463, 1380.09998, 1147.59998, 10.80000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(3463, 1404.50000, 1147.59998, 10.80000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(3463, 1428.09998, 1147.59998, 10.80000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(3463, 1459.59998, 1114.50000, 10.80000,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(3463, 1459.59998, 1090.69995, 10.80000,   0.00000, 0.00000, 179.99500);
	CreateDynamicObject(3463, 1459.59998, 1066.59998, 10.80000,   0.00000, 0.00000, 179.99500);
	CreateDynamicObject(3463, 1459.59998, 1043.19995, 10.80000,   0.00000, 0.00000, 179.99500);
	CreateDynamicObject(3463, 1474.09998, 945.90002, 10.80000,   0.00000, 0.00000, 270.00000);
	CreateDynamicObject(3463, 1450.40002, 945.90002, 10.80000,   0.00000, 0.00000, 270.00000);
	CreateDynamicObject(3463, 1426.00000, 945.90002, 10.80000,   0.00000, 0.00000, 270.00000);
	CreateDynamicObject(3463, 1403.09998, 945.90002, 10.80000,   0.00000, 0.00000, 270.00000);
	CreateDynamicObject(3463, 1316.19995, 1102.90002, 10.80000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3463, 1316.30005, 1126.59998, 10.80000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3463, 1316.30005, 1150.90002, 10.80000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3463, 1316.30005, 1174.30005, 10.80000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1215, 1296.30005, 1134.19995, 9.90000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1215, 1296.30005, 1143.09998, 9.90000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1215, 1296.30005, 1157.90002, 9.90000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1215, 1296.30005, 1166.69995, 9.90000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1215, 1296.30005, 1118.90002, 9.90000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1215, 1296.30005, 1110.09998, 9.90000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1215, 1411.40002, 1167.59998, 10.20000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1215, 1420.40002, 1167.59998, 10.20000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1215, 1396.80005, 1167.69995, 10.20000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1215, 1388.00000, 1167.69995, 10.20000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1215, 1372.40002, 1167.69995, 10.20000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1215, 1363.69995, 1167.69995, 10.20000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1215, 1479.69995, 1107.50000, 10.40000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1215, 1479.69995, 1098.59998, 10.40000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1215, 1479.69995, 1083.19995, 10.40000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1215, 1479.69995, 1074.40002, 10.40000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1215, 1479.69995, 1059.59998, 10.40000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1215, 1479.69995, 1050.80005, 10.40000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1215, 1467.09998, 925.40002, 10.30000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1215, 1458.09998, 925.40002, 10.30000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1215, 1442.80005, 925.40002, 10.30000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1215, 1434.00000, 925.40002, 10.30000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1215, 1419.40002, 925.40002, 10.30000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1215, 1410.30005, 925.40002, 10.30000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3406, 1391.40002, 931.00000, 11.00000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(3406, 1388.69995, 931.00000, 11.00000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(3406, 1388.69995, 938.09998, 8.80000,   0.00000, 30.00000, 90.00000);
	CreateDynamicObject(3406, 1391.40002, 938.09998, 8.80000,   0.00000, 29.99800, 90.00000);
	CreateDynamicObject(3406, 1384.90002, 931.00000, 11.00000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(3406, 1382.40002, 931.00000, 11.00000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(3406, 1384.90002, 938.09998, 8.80000,   0.00000, 29.99800, 90.00000);
	CreateDynamicObject(3406, 1382.40002, 938.09998, 8.80000,   0.00000, 29.99800, 90.00000);
	CreateDynamicObject(3406, 1367.00000, 1072.69995, 10.70000,   0.00000, 0.00000, 270.00000);
	CreateDynamicObject(3406, 1367.00000, 1079.90002, 9.00000,   0.00000, 329.99600, 270.00000);
	CreateDynamicObject(3406, 1364.69995, 1072.69995, 10.70000,   0.00000, 0.00000, 270.00000);
	CreateDynamicObject(3406, 1364.69995, 1079.90002, 9.00000,   0.00000, 329.99600, 270.00000);
	CreateDynamicObject(3406, 1371.00000, 1072.69995, 10.70000,   0.00000, 0.00000, 270.00000);
	CreateDynamicObject(3406, 1373.19995, 1072.69995, 10.70000,   0.00000, 0.00000, 270.00000);
	CreateDynamicObject(3406, 1371.00000, 1079.90002, 9.00000,   0.00000, 329.99600, 270.00000);
	CreateDynamicObject(3406, 1373.19995, 1079.90002, 9.00000,   0.00000, 329.99600, 270.00000);
	CreateDynamicObject(3406, 1377.19995, 1072.69995, 10.70000,   0.00000, 0.00000, 270.00000);
	CreateDynamicObject(3406, 1379.40002, 1072.69995, 10.70000,   0.00000, 0.00000, 270.00000);
	CreateDynamicObject(3406, 1383.19995, 1072.69995, 10.70000,   0.00000, 0.00000, 270.00000);
	CreateDynamicObject(3406, 1385.40002, 1072.69995, 10.70000,   0.00000, 0.00000, 270.00000);
	CreateDynamicObject(3406, 1388.90002, 1072.69995, 10.70000,   0.00000, 0.00000, 270.00000);
	CreateDynamicObject(3406, 1391.09998, 1072.69995, 10.70000,   0.00000, 0.00000, 270.00000);
	CreateDynamicObject(3406, 1377.19995, 1079.90002, 9.00000,   0.00000, 329.99600, 270.00000);
	CreateDynamicObject(3406, 1379.40002, 1079.90002, 9.00000,   0.00000, 329.99600, 270.00000);
	CreateDynamicObject(3406, 1383.19995, 1079.90002, 9.00000,   0.00000, 329.99600, 270.00000);
	CreateDynamicObject(3406, 1385.40002, 1079.90002, 9.00000,   0.00000, 329.99600, 270.00000);
	CreateDynamicObject(3406, 1388.90002, 1079.90002, 9.00000,   0.00000, 329.99600, 270.00000);
	CreateDynamicObject(3406, 1391.09998, 1079.90002, 9.00000,   0.00000, 329.99600, 270.00000);
	CreateDynamicObject(1267, 1335.40002, 1182.50000, 25.70000,   0.00000, 0.00000, 61.37000);
	CreateDynamicObject(1597, 1492.19995, 1003.70001, 12.50000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1597, 1482.40002, 1003.70001, 12.50000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1597, 1472.59998, 1003.70001, 12.50000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1597, 1462.80005, 1003.70001, 12.50000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1597, 1492.19995, 982.00000, 12.50000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1597, 1482.40002, 982.00000, 12.50000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1597, 1472.59998, 982.00000, 12.50000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1597, 1462.80005, 982.00000, 12.50000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(979, 1492.59998, 983.20001, 10.40000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(979, 1483.30005, 983.20001, 10.40000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(979, 1474.00000, 983.20001, 10.40000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(979, 1464.69995, 983.20001, 10.40000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(979, 1462.80005, 983.20001, 10.40000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(979, 1462.80005, 981.20001, 10.40000,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(979, 1472.09998, 981.20001, 10.40000,   0.00000, 0.00000, 179.99500);
	CreateDynamicObject(979, 1481.30005, 981.20001, 10.40000,   0.00000, 0.00000, 179.99500);
	CreateDynamicObject(979, 1490.59998, 981.20001, 10.40000,   0.00000, 0.00000, 179.99500);
	CreateDynamicObject(979, 1492.59998, 981.20001, 10.40000,   0.00000, 0.00000, 179.99500);
	CreateDynamicObject(979, 1492.59998, 1004.90002, 10.40000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(979, 1483.30005, 1004.90002, 10.40000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(979, 1474.00000, 1004.90002, 10.40000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(979, 1464.80005, 1004.90002, 10.40000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(979, 1462.50000, 1004.90002, 10.40000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(979, 1462.50000, 1002.90002, 10.40000,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(979, 1471.80005, 1002.90002, 10.40000,   0.00000, 0.00000, 179.99500);
	CreateDynamicObject(979, 1481.00000, 1002.90002, 10.40000,   0.00000, 0.00000, 179.99500);
	CreateDynamicObject(979, 1490.30005, 1002.90002, 10.40000,   0.00000, 0.00000, 179.99500);
	CreateDynamicObject(979, 1492.69995, 1002.90002, 10.40000,   0.00000, 0.00000, 179.99500);
	CreateDynamicObject(3406, 1492.19995, 979.59998, 10.60000,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(3406, 1492.19995, 977.59998, 10.60000,   0.00000, 0.00000, 179.99500);
	CreateDynamicObject(3406, 1485.09998, 977.59998, 8.40000,   0.00000, 30.00000, 180.00000);
	CreateDynamicObject(3406, 1485.09998, 979.59998, 8.40000,   0.00000, 29.99800, 179.99500);
	
	//mapa unload gunoierr lv are objecte scoase
	CreateDynamicObject(3749, 1483.30005, 2381.3999, 15.7, 0, 0, 0);
	CreateDynamicObject(987, 1557.19995, 2383.19995, 10, 0, 0, 180);
	CreateDynamicObject(987, 1557.19995, 2371.30005, 10, 0, 0, 90);
	CreateDynamicObject(987, 1545.59998, 2383.19995, 10, 0, 0, 180);
	CreateDynamicObject(987, 1557.19995, 2359.30005, 10, 0, 0, 90);
	CreateDynamicObject(987, 1557.19995, 2347.30005, 10, 0, 0, 90);
	CreateDynamicObject(987, 1557.19995, 2335.3999, 10, 0, 0, 90);
	CreateDynamicObject(987, 1534, 2383.19995, 10, 0, 0, 179.995);
	CreateDynamicObject(987, 1557.19995, 2323.30005, 10, 0, 0, 90);
	CreateDynamicObject(987, 1522.5, 2383.19995, 10, 0, 0, 179.995);
	CreateDynamicObject(987, 1511, 2383.19995, 10, 0, 0, 179.995);
	CreateDynamicObject(987, 1545.19995, 2323.30005, 10, 0, 0, 0);
	CreateDynamicObject(987, 1504.09998, 2383.19995, 10, 0, 0, 179.995);
	CreateDynamicObject(987, 1533.30005, 2323.30005, 10, 0, 0, 0);
	CreateDynamicObject(987, 1521.40002, 2323.30005, 10, 0, 0, 0);
	CreateDynamicObject(987, 1509.40002, 2323.30005, 10, 0, 0, 0);
	CreateDynamicObject(987, 1473.90002, 2383.19995, 10, 0, 0, 179.995);
	CreateDynamicObject(987, 1497.40002, 2323.30005, 10, 0, 0, 0);
	CreateDynamicObject(987, 1485.40002, 2323.30005, 10, 0, 0, 0);
	CreateDynamicObject(987, 1473.40002, 2323.30005, 10, 0, 0, 0);
	CreateDynamicObject(987, 1461.40002, 2323.30005, 10, 0, 0, 0);
	CreateDynamicObject(987, 1462.40002, 2383.19995, 10, 0, 0, 179.995);
	CreateDynamicObject(987, 1451, 2383.19995, 10, 0, 0, 179.995);
	CreateDynamicObject(987, 1439.69995, 2383.19995, 10, 0, 0, 179.995);
	CreateDynamicObject(987, 1449.5, 2323.30005, 10, 0, 0, 0);
	CreateDynamicObject(987, 1428.19995, 2383.19995, 10, 0, 0, 179.995);
	CreateDynamicObject(987, 1437.5, 2323.30005, 10, 0, 0, 0);
	CreateDynamicObject(987, 1425.59998, 2323.30005, 10, 0, 0, 0);
	CreateDynamicObject(987, 1413.59998, 2323.30005, 10, 0, 0, 0);
	CreateDynamicObject(987, 1416.90002, 2383.19995, 10, 0, 0, 179.995);
	CreateDynamicObject(987, 1401.69995, 2323.30005, 10, 0, 0, 0);
	CreateDynamicObject(987, 1409.19995, 2383.19995, 10, 0, 0, 179.995);
	CreateDynamicObject(987, 1397.40002, 2323.30005, 10, 0, 0, 0);
	CreateDynamicObject(987, 1397.40002, 2383.19995, 10, 0, 0, 270);
	CreateDynamicObject(987, 1397.40002, 2335.19995, 10, 0, 0, 270);
	CreateDynamicObject(987, 1397.40002, 2347.1001, 10, 0, 0, 270);
	CreateDynamicObject(987, 1397.40002, 2359, 10, 0, 0, 270);
	CreateDynamicObject(987, 1397.40002, 2371.19995, 10, 0, 0, 270);
	CreateDynamicObject(987, 1397.40002, 2365.19995, 10, 0, 0, 270);
	CreateDynamicObject(11081, 1410.19995, 2328.69995, 14.2, 0, 0, 180);
	CreateDynamicObject(1332, 1401.40002, 2343.6001, 10.9, 0, 0, 90);
	CreateDynamicObject(910, 1424.30005, 2377.19995, 11, 0, 0, 0);
	CreateDynamicObject(18246, 1414.80005, 2357.80005, 12, 0, 0, 270);
	CreateDynamicObject(18249, 1406.69995, 2344.30005, 6.1, 0, 0, 0);
	CreateDynamicObject(849, 1421.19995, 2329.5, 10, 0, 0, 0);
	CreateDynamicObject(1359, 1403.5, 2371.30005, 10.5, 0, 0, 0);
	CreateDynamicObject(18249, 1411.90002, 2356, 6.1, 0, 0, 0);
	CreateDynamicObject(3092, 1413.59998, 2362.80005, 10.4, 90, 210, 150);
	CreateDynamicObject(13649, 1413.5, 2354.1001, 11.5, 0, 30, 0);
	CreateDynamicObject(849, 1423.90002, 2328.69995, 10, 0, 0, 0);
	CreateDynamicObject(849, 1423.09998, 2326.6001, 10, 0, 0, 0);
	CreateDynamicObject(3073, 1427.09998, 2374.19995, 11.3, 0, 0, 0);
	CreateDynamicObject(1369, 1408.09998, 2371.3999, 10.4, 0, 0, 0);
	CreateDynamicObject(2890, 1515.30005, 2376.80005, 9.7, 0, 0, 270);
	CreateDynamicObject(3073, 1431.59998, 2374.1001, 11.3, 0, 0, 0);
	CreateDynamicObject(13649, 1413.40002, 2349.80005, 11.5, 0, 29.998, 0);
	CreateDynamicObject(2906, 1413.69995, 2354.30005, 12.1, 0, 0, 0);
	CreateDynamicObject(1440, 1412.40002, 2336, 10.1, 0, 0, 0);
	CreateDynamicObject(2890, 1438.59998, 2326.69995, 9.6, 0, 0, 179.995);
	CreateDynamicObject(2890, 1441.59998, 2326.69995, 9.6, 0, 0, 179.995);
	CreateDynamicObject(13649, 1408.5, 2346.3999, 11.5, 0, 29.998, 0);
	CreateDynamicObject(13649, 1408.19995, 2341.3999, 11.5, 0, 29.998, 0);
	CreateDynamicObject(3374, 1403.80005, 2363.8999, 11.3, 0, 0, 0);
	CreateDynamicObject(3374, 1403.69995, 2368.3999, 11.3, 0, 0, 0);
	CreateDynamicObject(1370, 1418.19995, 2371.3999, 10.4, 0, 0, 0);
	CreateDynamicObject(1370, 1419.09998, 2371.3999, 10.4, 0, 0, 0);
	CreateDynamicObject(1370, 1420, 2371.3999, 10.4, 0, 0, 0);
	CreateDynamicObject(1365, 1429.69995, 2325.69995, 10.9, 0, 0, 0);
	CreateDynamicObject(18248, 1435.09998, 2365.8999, 17.6, 0, 0, 0);
	CreateDynamicObject(1358, 1445.30005, 2325.30005, 10.9, 0, 0, 0);
	CreateDynamicObject(1358, 1449.30005, 2325.3999, 10.9, 0, 0, 0);
	CreateDynamicObject(1358, 1453.19995, 2325.5, 10.9, 0, 0, 0);
	CreateDynamicObject(12957, 1438.80005, 2365.30005, 21.1, 0, 0, 60);
	CreateDynamicObject(13591, 1413.69995, 2340.6001, 9.9, 0, 0, 90);
	CreateDynamicObject(12957, 1438.80005, 2365.30005, 10, 0, 0, 59.996);
	CreateDynamicObject(12957, 1438.69995, 2366.6001, 10, 0, 330, 330);
	CreateDynamicObject(12957, 1438.80005, 2362.80005, 10, 30, 0, 0);
	CreateDynamicObject(3092, 1414.09998, 2360.30005, 9.9, 90, 209.998, 149.996);
	CreateDynamicObject(18247, 1440.90002, 2330.6001, 14.3, 0, 0, 300);
	CreateDynamicObject(18250, 1541.30005, 2350.6001, 15.6, 0, 0, 270);
	CreateDynamicObject(18248, 1533, 2372.80005, 17.9, 0, 0, 280);
	CreateDynamicObject(3073, 1442.59998, 2335.6001, 13.8, 0, 0, 60);
	CreateDynamicObject(3252, 1447.69995, 2375.19995, 9.4, 0, 0, 355.995);
	CreateDynamicObject(18249, 1482.09998, 2330.30005, 14.2, 0, 0, 90);
	CreateDynamicObject(18249, 1509.40002, 2330.30005, 14.2, 0, 0, 90);
	CreateDynamicObject(2890, 1435.59961, 2326.69922, 9.6, 0, 0, 179.995);
	CreateDynamicObject(18249, 1419.90002, 2355.69995, 6.1, 0, 0, 30);
	CreateDynamicObject(13591, 1456.90002, 2370.80005, 10, 0, 0, 0);
	CreateDynamicObject(3460, 1552.90002, 2339.19995, 12.1, 0, 0, 0);
	CreateDynamicObject(3460, 1553.69995, 2361.19995, 13, 0, 0, 180);
	CreateDynamicObject(3460, 1534, 2361.5, 12.2, 0, 0, 210);
	CreateDynamicObject(3460, 1534.5, 2339.69995, 13.1, 0, 0, 330);
	CreateDynamicObject(1290, 1465.80005, 2379.3999, 14.8, 0, 0, 60);
	
	//Mapa de la Taxi facuta de mine Arnold 
	CreateDynamicObject(2773,1727.1999500,-1860.0000000,12.8000000,0.0000000,0.0000000,90.0000000); //object(cj_airprt_bar) (1)
	CreateDynamicObject(2773,1729.0999800,-1860.0000000,12.8000000,0.0000000,0.0000000,90.0000000); //object(cj_airprt_bar) (2)
	CreateDynamicObject(2773,1731.0000000,-1860.0000000,12.8000000,0.0000000,0.0000000,90.0000000); //object(cj_airprt_bar) (3)
	CreateDynamicObject(2773,1732.9000200,-1860.0000000,12.8000000,0.0000000,0.0000000,90.0000000); //object(cj_airprt_bar) (4)
	CreateDynamicObject(2773,1734.8000500,-1860.0000000,12.8000000,0.0000000,0.0000000,90.0000000); //object(cj_airprt_bar) (5)
	CreateDynamicObject(2773,1736.6999500,-1860.0000000,12.8000000,0.0000000,0.0000000,90.0000000); //object(cj_airprt_bar) (6)
	CreateDynamicObject(2773,1738.5999800,-1860.0000000,12.8000000,0.0000000,0.0000000,90.0000000); //object(cj_airprt_bar) (7)
	CreateDynamicObject(2773,1740.5000000,-1860.0000000,12.8000000,0.0000000,0.0000000,90.0000000); //object(cj_airprt_bar) (8)
	CreateDynamicObject(2773,1744.9000200,-1860.0000000,12.8000000,0.0000000,0.0000000,90.0000000); //object(cj_airprt_bar) (9)
	CreateDynamicObject(2773,1746.8000500,-1860.0000000,12.8000000,0.0000000,0.0000000,90.0000000); //object(cj_airprt_bar) (10)
	CreateDynamicObject(2773,1748.6999500,-1860.0000000,12.8000000,0.0000000,0.0000000,90.0000000); //object(cj_airprt_bar) (11)
	CreateDynamicObject(2773,1750.5999800,-1860.0000000,12.8000000,0.0000000,0.0000000,90.0000000); //object(cj_airprt_bar) (12)
	CreateDynamicObject(2773,1752.5000000,-1860.0000000,12.8000000,0.0000000,0.0000000,90.0000000); //object(cj_airprt_bar) (13)
	CreateDynamicObject(2773,1754.4000200,-1860.0000000,12.8000000,0.0000000,0.0000000,90.0000000); //object(cj_airprt_bar) (14)
	CreateDynamicObject(2773,1756.3000500,-1860.0000000,12.8000000,0.0000000,0.0000000,90.0000000); //object(cj_airprt_bar) (15)
	CreateDynamicObject(2773,1758.1999500,-1860.0000000,12.8000000,0.0000000,0.0000000,90.0000000); //object(cj_airprt_bar) (16)
	CreateDynamicObject(2773,1760.0999800,-1860.0000000,12.8000000,0.0000000,0.0000000,90.0000000); //object(cj_airprt_bar) (17)
	CreateDynamicObject(2773,1762.0000000,-1860.0000000,12.8000000,0.0000000,0.0000000,90.0000000); //object(cj_airprt_bar) (18)
	CreateDynamicObject(2773,1763.9000200,-1860.0000000,12.8000000,0.0000000,0.0000000,90.0000000); //object(cj_airprt_bar) (19)
	CreateDynamicObject(2773,1765.8000500,-1860.0000000,12.8000000,0.0000000,0.0000000,90.0000000); //object(cj_airprt_bar) (20)
	CreateDynamicObject(2773,1767.6999500,-1860.0000000,12.8000000,0.0000000,0.0000000,90.0000000); //object(cj_airprt_bar) (21)
	CreateDynamicObject(2773,1769.5999800,-1860.0000000,12.8000000,0.0000000,0.0000000,90.0000000); //object(cj_airprt_bar) (22)
	CreateDynamicObject(2773,1771.5000000,-1860.0000000,12.8000000,0.0000000,0.0000000,90.0000000); //object(cj_airprt_bar) (23)
	CreateDynamicObject(2773,1773.4000200,-1860.0000000,12.8000000,0.0000000,0.0000000,90.0000000); //object(cj_airprt_bar) (24)
	CreateDynamicObject(2774,1775.8000500,-1853.5000000,11.7000000,270.0000000,180.0000000,0.0000000); //object(cj_airp_pillars) (1)
	CreateDynamicObject(2774,1777.9000200,-1853.5000000,11.7000000,270.0000000,179.9950000,0.0000000); //object(cj_airp_pillars) (2)
	CreateDynamicObject(2774,1780.0000000,-1853.5000000,11.7000000,270.0000000,179.9950000,0.0000000); //object(cj_airp_pillars) (3)
	CreateDynamicObject(3526,1765.6999500,-1856.6999500,12.5000000,0.0000000,0.0000000,0.0000000); //object(vegasairportlight) (1)
	CreateDynamicObject(3526,1765.6999500,-1857.0000000,12.5000000,0.0000000,0.0000000,0.0000000); //object(vegasairportlight) (2)
	CreateDynamicObject(3526,1765.6999500,-1857.3000500,12.5000000,0.0000000,0.0000000,0.0000000); //object(vegasairportlight) (3)
	CreateDynamicObject(3526,1765.6999500,-1857.5999800,12.5000000,0.0000000,0.0000000,0.0000000); //object(vegasairportlight) (4)
	CreateDynamicObject(3526,1765.6999500,-1857.9000200,12.5000000,0.0000000,0.0000000,0.0000000); //object(vegasairportlight) (5)
	CreateDynamicObject(3526,1765.6999500,-1858.1999500,12.5000000,0.0000000,0.0000000,0.0000000); //object(vegasairportlight) (6)
	CreateDynamicObject(3526,1765.6999500,-1858.5000000,12.5000000,0.0000000,0.0000000,0.0000000); //object(vegasairportlight) (7)
	CreateDynamicObject(3526,1757.0999800,-1856.9000200,12.5000000,0.0000000,0.0000000,0.0000000); //object(vegasairportlight) (8)
	CreateDynamicObject(3526,1757.0999800,-1857.1999500,12.5000000,0.0000000,0.0000000,0.0000000); //object(vegasairportlight) (9)
	CreateDynamicObject(3526,1757.0999800,-1857.5999800,12.5000000,0.0000000,0.0000000,0.0000000); //object(vegasairportlight) (10)
	CreateDynamicObject(3526,1757.0999800,-1857.9000200,12.5000000,0.0000000,0.0000000,0.0000000); //object(vegasairportlight) (11)
	CreateDynamicObject(3526,1757.0999800,-1858.0999800,12.5000000,0.0000000,0.0000000,0.0000000); //object(vegasairportlight) (12)
	CreateDynamicObject(3526,1757.0999800,-1858.4000200,12.5000000,0.0000000,0.0000000,0.0000000); //object(vegasairportlight) (13)
	CreateDynamicObject(3526,1757.0999800,-1858.6999500,12.5000000,0.0000000,0.0000000,0.0000000); //object(vegasairportlight) (14)
	CreateDynamicObject(3526,1748.8000500,-1856.9000200,12.5000000,0.0000000,0.0000000,0.0000000); //object(vegasairportlight) (15)
	CreateDynamicObject(3526,1748.8000500,-1857.3000500,12.5000000,0.0000000,0.0000000,0.0000000); //object(vegasairportlight) (16)
	CreateDynamicObject(3526,1748.8000500,-1857.5999800,12.5000000,0.0000000,0.0000000,0.0000000); //object(vegasairportlight) (17)
	CreateDynamicObject(3526,1748.8000500,-1858.0000000,12.5000000,0.0000000,0.0000000,0.0000000); //object(vegasairportlight) (18)
	CreateDynamicObject(3526,1748.8000500,-1858.3000500,12.5000000,0.0000000,0.0000000,0.0000000); //object(vegasairportlight) (19)
	CreateDynamicObject(3526,1748.8000500,-1858.6999500,12.5000000,0.0000000,0.0000000,0.0000000); //object(vegasairportlight) (20)
	CreateDynamicObject(3526,1740.5000000,-1858.6999500,12.5000000,0.0000000,0.0000000,0.0000000); //object(vegasairportlight) (21)
	CreateDynamicObject(3526,1740.5000000,-1858.3000500,12.5000000,0.0000000,0.0000000,0.0000000); //object(vegasairportlight) (22)
	CreateDynamicObject(3526,1740.5000000,-1857.8000500,12.5000000,0.0000000,0.0000000,0.0000000); //object(vegasairportlight) (23)
	CreateDynamicObject(3526,1740.5000000,-1857.4000200,12.5000000,0.0000000,0.0000000,0.0000000); //object(vegasairportlight) (24)
	CreateDynamicObject(3526,1740.5000000,-1857.0999800,12.5000000,0.0000000,0.0000000,0.0000000); //object(vegasairportlight) (25)
	CreateDynamicObject(3526,1732.0000000,-1857.0999800,12.5000000,0.0000000,0.0000000,0.0000000); //object(vegasairportlight) (26)
	CreateDynamicObject(3526,1732.0000000,-1857.5000000,12.5000000,0.0000000,0.0000000,0.0000000); //object(vegasairportlight) (27)
	CreateDynamicObject(3526,1732.0000000,-1857.8000500,12.5000000,0.0000000,0.0000000,0.0000000); //object(vegasairportlight) (28)
	CreateDynamicObject(3526,1732.0000000,-1858.0999800,12.5000000,0.0000000,0.0000000,0.0000000); //object(vegasairportlight) (29)
	CreateDynamicObject(3526,1732.0000000,-1858.5000000,12.5000000,0.0000000,0.0000000,0.0000000); //object(vegasairportlight) (30)
	CreateDynamicObject(3526,1732.0000000,-1858.8000500,12.5000000,0.0000000,0.0000000,0.0000000); //object(vegasairportlight) (31)
	
	
	
	//Tribunal e la /Business
	CreateDynamicObject(16203, 199.42171, 1943.40210, -11.27340,   4.00000, 0.00000, 0.00000);
	CreateDynamicObject(19462, 118.61570, 1840.64380, -10.33400,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19462, 125.59570, 1840.63611, -10.33400,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19462, 122.11500, 1840.63708, -10.33400,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19462, 129.09309, 1840.63000, -10.33400,   0.00000, 90.00000, 0.06000);
	CreateDynamicObject(19462, 132.58360, 1840.62524, -10.33400,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19462, 136.06680, 1840.62354, -10.33400,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19462, 120.09940, 1835.81384, -8.62869,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19462, 129.70450, 1835.80933, -8.62870,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19462, 139.34070, 1835.80664, -8.62870,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19462, 120.58701, 1845.29517, -8.62869,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19462, 130.20790, 1845.28735, -8.62870,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19462, 139.83340, 1845.27502, -8.62870,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19462, 141.10066, 1841.67493, -8.62870,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19462, 141.09840, 1832.07336, -8.62870,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19462, 116.95528, 1841.47876, -8.62870,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19462, 117.67929, 1836.08447, -8.62870,   0.00000, 0.00000, 34.00000);
	CreateDynamicObject(19462, 116.29977, 1842.79541, -8.62870,   0.00000, 0.00000, -34.00000);
	CreateDynamicObject(19443, 126.27003, 1843.59265, -9.73977,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(19443, 126.26840, 1836.10205, -9.73980,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(14416, 127.14390, 1839.82971, -12.85770,   270.00000, 180.00000, 90.00000);
	CreateDynamicObject(19443, 125.40740, 1841.87830, -10.58220,   55.00000, 0.00000, 90.00000);
	CreateDynamicObject(19443, 125.42540, 1837.92651, -10.58840,   55.00000, 0.00000, 90.00000);
	CreateDynamicObject(19462, 124.58120, 1840.52539, -9.01580,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(16203, 199.02469, 1943.35571, -57.64060,   356.85840, 0.00000, 3.14159);
	CreateDynamicObject(19462, 118.61570, 1840.64380, -3.76720,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19462, 125.59570, 1840.63611, -3.76720,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19462, 122.11500, 1840.63708, -3.76720,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19462, 129.09309, 1840.63000, -3.76720,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19462, 132.58360, 1840.62524, -3.76720,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19462, 136.06680, 1840.62354, -3.76722,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19462, 120.09940, 1835.81384, -5.13390,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19462, 129.70450, 1835.80933, -5.13390,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19462, 139.34070, 1835.80664, -5.13390,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19462, 120.58700, 1845.29517, -5.13390,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19462, 130.20790, 1845.28735, -5.13390,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19462, 139.83340, 1845.27502, -5.13390,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19462, 141.10600, 1841.67969, -5.13390,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19462, 116.95530, 1841.47876, -5.13390,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19462, 117.67930, 1836.08447, -5.13390,   0.00000, 0.00000, 34.00000);
	CreateDynamicObject(19462, 116.29980, 1842.79541, -5.13390,   0.00000, 0.00000, -34.00000);
	CreateDynamicObject(19443, 126.27003, 1843.59265, -9.73977,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(19443, 126.26840, 1836.10205, -9.73980,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(19443, 123.59208, 1836.60742, -10.78840,   47.04000, 0.00000, 90.00000);
	CreateDynamicObject(19462, 121.08370, 1840.64038, -9.01580,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19462, 117.59660, 1840.41296, -9.01580,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(2207, 120.86348, 1839.70068, -8.93120,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2208, 119.77820, 1842.47803, -9.02900,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1491, 119.96560, 1837.71472, -10.65160,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2208, 119.95530, 1834.63354, -9.02900,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2773, 128.01480, 1842.87415, -9.73290,   0.00000, 0.00000, -33.00000);
	CreateDynamicObject(2773, 128.02470, 1836.92908, -9.73290,   0.00000, 0.00000, 33.00000);
	CreateDynamicObject(1808, 127.03208, 1844.77698, -10.24868,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1808, 127.74111, 1844.78210, -10.24868,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2108, 120.59449, 1844.79651, -8.91705,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2108, 120.75970, 1836.14673, -8.91705,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19376, 126.28200, 1846.75134, -14.19500,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19376, 126.27900, 1833.01526, -14.19500,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19376, 121.12360, 1840.42493, -3.83500,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(19376, 130.71831, 1840.22461, -3.83500,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(19376, 140.34370, 1840.08203, -3.83500,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(19376, 116.99040, 1839.23474, 1.76340,   45.00000, 0.00000, 0.00000);
	CreateDynamicObject(19376, 116.95780, 1842.66223, 1.76340,   -45.00000, 0.00000, 0.00000);
	CreateDynamicObject(19360, 125.69990, 1844.71252, -9.35170,   0.00000, 0.00000, 0.46000);
	CreateDynamicObject(19360, 125.71670, 1836.28528, -9.35170,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19360, 124.05220, 1837.80579, -9.35170,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19360, 124.05040, 1843.19409, -9.35170,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2173, 129.76610, 1837.51990, -10.24850,   0.00000, 0.00000, 33.00000);
	CreateDynamicObject(2173, 130.76740, 1842.65149, -10.24850,   0.00000, 0.00000, -330000.00000);
	CreateDynamicObject(1671, 130.79570, 1836.90405, -9.78230,   0.00000, 0.00000, -142.42000);
	CreateDynamicObject(1671, 131.30870, 1843.67334, -9.78230,   0.00000, 0.00000, -62.00000);
	CreateDynamicObject(19462, 139.55060, 1840.62756, -10.33400,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19462, 141.09840, 1832.07336, -5.13390,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2614, 117.11674, 1840.87561, -6.01756,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1714, 119.22440, 1840.65881, -8.92900,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1811, 132.79089, 1837.09814, -9.64640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1811, 132.79279, 1838.07300, -9.64640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1811, 132.79457, 1838.98291, -9.64640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1811, 132.79636, 1839.90198, -9.64640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1811, 132.80327, 1843.44092, -9.64640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1811, 132.80530, 1844.47913, -9.64640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1811, 132.90335, 1842.42468, -9.64640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1811, 134.32224, 1837.09265, -9.64640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1811, 135.87299, 1837.08777, -9.64640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1811, 137.31964, 1837.11621, -9.64640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1811, 138.82356, 1837.14587, -9.64640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1811, 134.32495, 1838.04736, -9.64640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1811, 135.88106, 1838.02136, -9.64640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1811, 137.36555, 1837.99683, -9.64640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1811, 138.86070, 1837.97119, -9.64640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1811, 134.28900, 1838.97180, -9.64640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1811, 135.84901, 1838.96021, -9.64640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1811, 137.38029, 1838.95837, -9.64640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1811, 138.89461, 1838.95642, -9.64640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1811, 134.23810, 1839.93152, -9.64640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1811, 135.81422, 1839.95056, -9.64640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1811, 137.38509, 1839.96997, -9.64640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1811, 138.91451, 1839.89368, -9.64640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1811, 134.26964, 1842.49634, -9.64640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1811, 135.71655, 1842.48779, -9.64640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1811, 137.34238, 1842.43262, -9.64640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1811, 134.24586, 1843.49854, -9.64640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1811, 135.73994, 1843.55786, -9.64640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1811, 137.31068, 1843.64734, -9.64640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1811, 134.27930, 1844.52832, -9.64640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1811, 135.73421, 1844.57568, -9.64640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1811, 137.38330, 1844.63342, -9.64640,   0.00000, 0.00000, 0.00000);
	
	
	//Statile de Autobuz
	LastObjectID = CreateDynamicObject(1257, -2571.25, 2316.0, 5.2, 0.0, 0.0, 180.0);
	LastObjectID = CreateDynamicObject(1257, -2333.25, 2371.5, 6.0, 0.0, 0.0, 320.0);
	LastObjectID = CreateDynamicObject(1257, -1467.0, 2679.0, 56.0, 0.0, 0.0, 90.0);
	LastObjectID = CreateDynamicObject(1257, -1528.5, 2543.0, 56.0, 0.0, 0.0, 270.0);
	LastObjectID = CreateDynamicObject(1257, -800.5, 1562.0, 27.4, 0.0, 0.0, 0.0);
	LastObjectID = CreateDynamicObject(1257, -853.5, 1529.5, 22.4, 0.0, 0.0, 180.0);
	LastObjectID = CreateDynamicObject(1257, -269.0, 2620.5, 63.2, 0.0, 0.0, 270.0);
	LastObjectID = CreateDynamicObject(1257, -45.5, 1206.5, 19.6, 0.0, 0.0, 90.0);
	LastObjectID = CreateDynamicObject(1257, -100.5, 1190.75, 20.0, 0.0, 0.0, 270.0);
	LastObjectID = CreateDynamicObject(1257, -249.5, 1010.75, 20.0, 0.0, 0.0, 270.0);
	LastObjectID = CreateDynamicObject(1257, -2172.5, -2309.5, 30.9, 0.0, 0.0, 230.0);
	LastObjectID = CreateDynamicObject(1257, -2094.25, -2503.0, 30.9, 0.0, 0.0, 322.0);
	LastObjectID = CreateDynamicObject(1257, 2263.75, -35.75, 26.7, 0.0, 0.0, 270.0);
	LastObjectID = CreateDynamicObject(1257, 2456.25, 1.0, 26.5, 0.0, 0.0, 180.0);
	LastObjectID = CreateDynamicObject(1257, 1290.25, 333.5, 19.8, 0.0, 0.0, 65.0);
	LastObjectID = CreateDynamicObject(1257, 1284.75, 319.5, 19.8, 0.0, 0.0, 245.0);
	LastObjectID = CreateDynamicObject(1257, 736.0, -522.5, 16.6, 0.0, 0.0, 90.0);
	LastObjectID = CreateDynamicObject(1257, 736.0, -537.75, 16.6, 0.0, 0.0, 270.0);
}
// Add some special pickups to the map
GameModeInit_PickupsIcons()
{
	// Add a pickup so the player can get a trucker/busdriver license and position a 3DTextLabel above it
	Pickup_License = CreatePickup(1274, 2, -2033.0, -100.0, 35.2, 0);
	Create3DTextLabel(TXT_PickupText, 0x008080FF, -2033.0, -100.0, 36.0, 30.0, 0);

	// Add all refuel-pickups to the world (including their icon)
	AddRefuelPickup(-1471.5, 1863.75, 32.7);
	AddRefuelPickup(-1326.5, 2677.5, 50.1);
	AddRefuelPickup(611.5, 1694.5, 7.0);
	AddRefuelPickup(-2249.25, -2559.0, 32.0);
	AddRefuelPickup(-1606.5, -2714.0, 48.6);
	AddRefuelPickup(-93.5, -1175.0, 2.3);
	AddRefuelPickup(1377.5, 457.0, 19.9);
	AddRefuelPickup(651.5, -565.5, 16.4);
	AddRefuelPickup(-1675.75, 412.75, 7.2);
	AddRefuelPickup(-2405.50, 976.25, 45.3);
	AddRefuelPickup(-2023.25, 156.75, 28.9);
	AddRefuelPickup(-1131.75, -204.25, 14.2);
	AddRefuelPickup(66.50, 1220.50, 18.9);
	AddRefuelPickup(350.50, 2537.50, 16.8);
	AddRefuelPickup(2147.00, 2747.75, 10.9);
	AddRefuelPickup(2639.75, 1106.00, 10.9);
	AddRefuelPickup(2115.00, 920.00, 10.9);
	AddRefuelPickup(2202.00, 2475.00, 10.9);
	AddRefuelPickup(1596.50, 2199.75, 10.9);
	AddRefuelPickup(1584.25, 1448.25, 10.9);
	AddRefuelPickup(1004.25, -940.50, 42.2);
	AddRefuelPickup(1935.00, -1772.75, 13.4);

	// Add all pickups for the cardealers (including their icon)
	AddCarDealerPickup(-1972.5, 288.5, 35.2); // Wang cars in Doherty (San Fierro)

	// Add some icons to the map (modding garages), they will only appear when the player discovers them
	CreateDynamicMapIcon(1039, -1032, 32, 27, 0, 0, 0, -1, 150.0); // Transfender, Los Santos
	CreateDynamicMapIcon(-1936, 235, 34, 27, 0, 0, 0, -1, 150.0); // Transfender, San Fierro
	CreateDynamicMapIcon(2385, 1034, 11, 27, 0, 0, 0, -1, 150.0); // Transfender, Las Venturas
	CreateDynamicMapIcon(2646, -2025, 14, 27, 0, 0, 0, -1, 150.0); // Loco Low Co, Los Santos
	CreateDynamicMapIcon(-2712, 218, 4, 27, 0, 0, 0, -1, 150.0); // Wheel Arch Angels, San Fierro
}



// This function creates all objects required for the toll-gates
GameModeInit_Toll()
{
	// Add toll-houses to the world
	CreateObject(9623, 1787.00, 695.50, 17.40, -3.5, 0.0, 350.25); //object(toll_sfw) (1)

	// Add a toll-gate to the world
	AddTollGate(3578, 1801.00, 692.66, 10.00, 1801.00, 692.66, 15.00, 0.0, 0.0, 350.25, 30);
	AddTollGate(3578, 1791.33, 694.44, 10.00, 1791.33, 694.44, 15.00, 0.0, 0.0, 350.25, 30);
	AddTollGate(3578, 1781.66, 696.22, 10.00, 1781.66, 696.22, 15.00, 0.0, 0.0, 350.25, 30);
	AddTollGate(3578, 1772.00, 698.00, 10.00, 1772.00, 698.00, 15.00, 0.0, 0.0, 350.25, 30);

	AddTollGate(3578, -2668.25, 1274.50, 50.0, -2668.25, 1274.50, 55.0, 0.0, 0.0, 0.0, 30);
	AddTollGate(3578, -2677.75, 1274.50, 50.0, -2677.75, 1274.50, 55.0, 0.0, 0.0, 0.0, 30);
	AddTollGate(3578, -2686.25, 1274.50, 50.0, -2686.25, 1274.50, 55.0, 0.0, 0.0, 0.0, 30);
	AddTollGate(3578, -2694.75, 1274.50, 50.0, -2694.75, 1274.50, 55.0, 0.0, 0.0, 0.0, 30);
}
// Add character models to the class-selection and set their default spawn coordinates (without weapons)
GameModeInit_Classes()
{
	AddPlayerClass(206, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0); // Class 0 = Truck driver
	AddPlayerClass(261, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0); // Class 1 = Truck driver
	AddPlayerClass(220, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0); // Class 2 = Truck driver
	AddPlayerClass(234, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0); // Class 3 = Truck driver
	AddPlayerClass(182, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0); // Class 4 = Truck driver
	AddPlayerClass(262, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0); // Class 5 = Truck driver
	AddPlayerClass(263, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0); // Class 6 = Truck driver
	AddPlayerClass(299, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0); // Class 7 = Truck driver

	AddPlayerClass(255, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0); // Class 8 = Bus driver
	AddPlayerClass(93, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0); // Class 9 = Bus driver

	AddPlayerClass(61, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0); // Class 10 = Pilot

	AddPlayerClass(283, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0); // Class 11 = Police
	AddPlayerClass(288, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0); // Class 12 = Police
	AddPlayerClass(141, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0); // Class 13 = Police

	AddPlayerClass(121, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0); // Class 14 = Mafia
	AddPlayerClass(122, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0); // Class 15 = Mafia
	AddPlayerClass(191, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0); // Class 16 = Mafia

	AddPlayerClass(193, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0); // Class 17 = Courier
	AddPlayerClass(23, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0); // Class 18 = Courier

	AddPlayerClass(14, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0); // Class 19 = Assistance

	AddPlayerClass(16, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0); // Class 20 = Roadworker
	AddPlayerClass(211, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0); // Class 21 = Roadworker
	AddPlayerClass(260, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0); // Class 22 = Roadworker
	
	AddPlayerClass(274, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0); // Class 23 = Medic
	AddPlayerClass(276, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0); // Class 24 = Medic
	
	AddPlayerClass(286, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0); // Class 25 = FBY
	AddPlayerClass(163, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0); // Class 26 = FBY
	AddPlayerClass(164, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0); // Class 27 = FBY
	
	AddPlayerClass(167, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0); // Class 28 = Pizza Boy
	AddPlayerClass(155, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0); // Class 29 = Pizza Boy
	AddPlayerClass(209, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0); // Class 30 = Pizza Boy
	
	AddPlayerClass(56, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0); // Class 31 = Conducator Tren
	AddPlayerClass(62, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0); // Class 32 = Conducator Tren
	AddPlayerClass(79, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0); // Class 33 = Conducator Tren
	
	AddPlayerClass(212, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0); // Class 34 = Gunoier 
	AddPlayerClass(137, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0); // Class 35 = Gunoier 
	AddPlayerClass(258, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0); // Class 36 = Gunoier 
	
	AddPlayerClass(90, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0); // Class 34 = Marinar	
	AddPlayerClass(45, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0); // Class 35 = Marinar
	AddPlayerClass(135, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0); // Class 36 = Marinar
	
	AddPlayerClass(170, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0); // Class 34 = Taxi	
	AddPlayerClass(186, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0); // Class 35 = Taxi
	AddPlayerClass(20, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0); // Class 36 = Taxi
	
	AddPlayerClass(94, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0); // Class 37 = Padurar
	AddPlayerClass(129, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0); // Class 38 = Padurar
	AddPlayerClass(159, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0); // Class 39 = Padurar
}
// This function is used to add refuelling pickups to the map
AddRefuelPickup(Float:x, Float:y, Float:z)
{
	// Add the pickup-id to the ARefuelPickups array
	for (new i; i < sizeof(ARefuelPickups); i++)
	{
		// If an empty array-index is found
		if (ARefuelPickups[i][PickupID] == 0)
		{
		    // Store the pickup-id in this empty slot
			ARefuelPickups[i][PickupID] = CreatePickup(1650, 1, x, y, z, 0); // Type 1, cannot be pickup up, exists all the time
			ARefuelPickups[i][pux] = x;
			ARefuelPickups[i][puy] = y;
			ARefuelPickups[i][puz] = z;

			// Add a 3DText message above the refuel-pickup
			Create3DTextLabel(TXT_PickupRefuel, 0x008080FF, x, y, z + 0.8, 30.0, 0);

			// Add an icon to the map for this refuel-spot
			CreateDynamicMapIcon(x, y, z, 56, 0, 0, 0, -1, 300.0);

			// Stop browsing through the array
			break;
		}
	}
}
// This function is used to add cardealer-pickups to the map
AddCarDealerPickup(Float:x, Float:y, Float:z)
{
	// Add the pickup-id to the ACarDealerPickups array
	for (new i; i < sizeof(ACarDealerPickups); i++)
	{
		// If an empty array-index is found
		if (ACarDealerPickups[i][PickupID] == 0)
		{
		    // Store the pickup-id in this empty slot
			ACarDealerPickups[i][PickupID] = CreatePickup(1274, 1, x, y, z, 0); // Type 1, cannot be pickup up, exists all the time
			ACarDealerPickups[i][pux] = x;
			ACarDealerPickups[i][puy] = y;
			ACarDealerPickups[i][puz] = z;

			// Add a 3DText message above the cardealer pickup
			Create3DTextLabel(TXT_PickupCarDealer, 0x008080FF, x, y, z + 0.8, 30.0, 0);

			// Add an icon to the map for this cardealer-spot
			CreateDynamicMapIcon(x, y, z, 55, 0, 0, 0, -1, 300.0);

			// Stop browsing through the array
			break;
		}
	}
}
// This function is used to add toll-gates to the map
AddTollGate(GateModel, Float:OX, Float:OY, Float:OZ, Float:CX, Float:CY, Float:CZ, Float:RX, Float:RY, Float:RZ, TollMoney)
{
	// Loop through all tollgates
	for (new TollGate; TollGate < MAX_TOLLGATES; TollGate++)
	{
		// Check if this is an empty entry
		if (ATollGates[TollGate][GateID] == 0)
		{
			// Create a new object for the toll-gate in it's closed status
			ATollGates[TollGate][GateID] = CreateObject(GateModel, CX, CY, CZ, RX, RY, RZ);
			// Set data
			ATollGates[TollGate][TollPrice] = TollMoney; // Set the price to pay for passing the toll-gate
			ATollGates[TollGate][GateStatus] = 0; // Set the status to CLOSED
			ATollGates[TollGate][OpenX] = OX; // Save the OpenX coordinates
			ATollGates[TollGate][OpenY] = OY; // Save the OpenY coordinates
			ATollGates[TollGate][OpenZ] = OZ; // Save the OpenZ coordinates
			ATollGates[TollGate][CloseX] = CX; // Save the CloseX coordinates
			ATollGates[TollGate][CloseY] = CY; // Save the CloseY coordinates
			ATollGates[TollGate][CloseZ] = CZ; // Save the CloseZ coordinates
			break; // Stop the for-loop
		}
	}
}
