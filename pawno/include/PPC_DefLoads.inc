// Setup a custom type that holds all data about a load
enum TLoad
{
	LoadName[50], // The name of the load
	bool:Mafia, // Holds "true" if this load is wanted by the mafia
	Float:PayPerUnit, // Holds the price for every meter to haul this type of load (this gets multiplied by the distance to calculate the payment)
	PCV_Required, // This holds the vehicle-type the player needs to use this load (and automatically the player's class)
	FromLocations[30], // This array holds all loading-points for this load
	ToLocations[30] // This array holds all unloading-points for this load
}

new ALoads[][TLoad] =
{
	// LoadName, MafiaLoad, PayPerUnit, VehicleNeeded, From-Locations, To-Locations

	// Dummy Load (never used)
	{"Dummy", false, 0.00, 0, {0}, {0}}, // LoadID 0

	// Loads for ore trailer
	{"Gravel", false, 10.00, PCV_TruckerOreTrailer, {11}, {1, 2, 3}}, // LoadID 1
	{"Pietris", false, 77.00, PCV_TruckerOreTrailer, {63}, {12}}, // LoadID 2
	{"Rocks", false, 33.00, PCV_TruckerOreTrailer, {11}, {1, 2, 3, 4, 5}}, // LoadID 3
	{"Coal", false, 33.00, PCV_TruckerOreTrailer, {12}, {6, 7, 8}}, // LoadID 4
	{"Ore", false, 33.00, PCV_TruckerOreTrailer, {12}, {6, 9}}, // LoadID 5
	{"Logs", false, 33.00, PCV_TruckerOreTrailer, {13}, {7, 10}}, // LoadID 6
	{"Woodchips", false, 33.00, PCV_TruckerOreTrailer, {10}, {14}}, // LoadID 7
	{"Dry Waste", false, 33.00, PCV_TruckerOreTrailer, {6, 15, 16}, {17, 18, 19}}, // LoadID 8
	{"Debris", false, 33.00, PCV_TruckerOreTrailer, {17, 19}, {6, 18, 20}}, // LoadID 9
	{"Wheat", false, 33.00, PCV_TruckerOreTrailer, {21, 22}, {18, 23, 24}}, // LoadID 10

	// Loads for liquids trailer
	{"Unleaded Fuel", true, 100.00, PCV_TruckerFluidsTrailer, {8, 25, 26}, {27, 28, 29, 30, 31, 32, 33, 34}}, // LoadID 11
	{"Diesel Fuel", true, 100.00, PCV_TruckerFluidsTrailer, {8, 25, 26}, {27, 28, 29, 30, 31, 32, 33, 34}}, // LoadID 12
	{"Aviation Fuel", true, 100.00, PCV_TruckerFluidsTrailer, {8, 25, 26}, {35, 36}}, // LoadID 13
	{"Crude Oil", false, 100.00, PCV_TruckerFluidsTrailer, {8, 25, 26}, {6}}, // LoadID 14
	{"Liquid Nitrogen", false, 100.00, PCV_TruckerFluidsTrailer, {37, 38}, {39, 40}}, // LoadID 15
	{"Chemicals", false, 100.00, PCV_TruckerFluidsTrailer, {37}, {6, 15, 39, 40}}, // LoadID 16
	{"Pure Water", false, 100.00, PCV_TruckerFluidsTrailer, {37}, {15, 40, 41}}, // LoadID 17
	{"Grease", false, 100.00, PCV_TruckerFluidsTrailer, {8, 25}, {6, 10, 14, 42}}, // LoadID 18
	{"Fertilizer", false, 100.00, PCV_TruckerFluidsTrailer, {37, 38}, {21, 22}}, // LoadID 19
	{"Milk", false, 100.00, PCV_TruckerFluidsTrailer, {21, 22}, {43, 44, 45}}, // LoadID 20
	{"Beer", true, 100.00, PCV_TruckerFluidsTrailer, {41}, {44, 46}}, // LoadID 21
	{"Ethanol", false, 100.00, PCV_TruckerFluidsTrailer, {37, 41}, {26, 39, 40}}, // LoadID 22
	

	// Loads for cargo trailer
	{"Bautura", false, 83.00, PCV_TruckerCargoTrailer, {136}, {144, 139}}, // LoadID 23
	{"Drinks", false, 100.00, PCV_TruckerCargoTrailer, {15, 54, 55}, {49, 50, 51, 52, 53}}, // LoadID 24
	{"Bottled Beer", true, 100.00, PCV_TruckerCargoTrailer, {56}, {57, 58, 59, 60, 61}}, // LoadID 25
	{"Luxury Goods", false, 100.00, PCV_TruckerCargoTrailer, {24, 55}, {47, 48, 50}}, // LoadID 26
	{"Electronics", false, 100.00, PCV_TruckerCargoTrailer, {167}, {142}}, // LoadID 27
	{"Azot", true, 100.00, PCV_TruckerCargoTrailer, {152}, {140, 63, 6, 22}}, // LoadID 28
	{"Tablete", true, 150.00, PCV_TruckerCargoTrailer, {149}, {150, 121, 50, 143}}, // LoadID 29
	{"Building Materials", false, 10.00, PCV_TruckerCargoTrailer, {4}, {1, 2, 3, 5}}, // LoadID 30
	{"Turbine", false, 85.00, PCV_TruckerCargoTrailer, {134}, {143}}, // LoadID 31
	{"Busteni", true, 80.00, PCV_TruckerCargoTrailer, {148}, {142, 146, 5, 1}}, // LoadID 32
	{"TnT", false, 111.00, PCV_TruckerCargoTrailer, {151}, {150, 142, 63}}, // LoadID 33
	{"Masini de Lux", true, 21.00, PCV_TruckerCargoTrailer, {137}, {51, 61, 138, 139, 140, 141}}, // LoadID 60
	{"Bere", true, 80.00, PCV_TruckerCargoTrailer, {41}, {136, 61, 52, 55}}, // LoadID 61
	{"Hasis", true, 44.00, PCV_TruckerCargoTrailer, {142}, {139, 140, 136, 141, 52, 61, 51}}, // LoadID 62
	{"Cocos", false, 88.77, PCV_TruckerCargoTrailer, {143}, {136, 61, 52, 55}}, // LoadID 63
	{"Portocale", true, 75.00, PCV_TruckerCargoTrailer, {144}, {136, 61, 52, 55, 48}}, // LoadID 64
	{"Mazare", true, 60.00, PCV_TruckerCargoTrailer, {145}, {146, 140, 139, 51}}, // LoadID 65
	{"Buteli Gas", true, 77.00, PCV_TruckerCargoTrailer, {147}, {145}}, // LoadID 66
	{"Gas Pur", true, 53.33, PCV_TruckerCargoTrailer, {37}, {147}}, // LoadID 67
	{"Capre", true, 70.00, PCV_TruckerCargoTrailer, {42}, {143, 145, 146}}, // LoadID 68
	{"Aluminiu", true, 290.00, PCV_TruckerCargoTrailer, {169}, {142, 51}}, // LoadID 78
	{"Lapte", true, 300.00, PCV_TruckerCargoTrailer, {170}, {40, 55, 51}}, // LoadID 79
	{"Lubrifiant", true, 350.00, PCV_TruckerCargoTrailer, {171}, {136, 61, 40}}, // LoadID 80
	
	
	//Medic related 
	{"Inna", false, 120.00, PCV_MedicVan, {41, 136, 142}, {160, 161, 162}}, // LoadID 69
	{"Guta", false, 150.00, PCV_MedicVan, {63, 11}, {160, 161, 162}}, // LoadID 70
	{"Basescu", false, 160.00, PCV_MedicVan, {61}, {160, 161, 162}}, // LoadID 74
	{"Lady Gaga", false, 170.00, PCV_MedicVan, {139}, {160, 161, 162}}, // LoadID 75
	{"Gigi Becali", false, 110.00, PCV_MedicVan, {59}, {160, 161, 162}}, // LoadID 76
	{"Elodia", false, 150.00, PCV_MedicVan, {63, 11}, {160, 161, 162}}, // LoadID 77
	
	
	//PAdurar
	{"Brad", true, 150.00, PCV_PadurarPadurar, {174}, {175, 177, 143}}, // LoadID 81
	{"Fag", true, 170.00, PCV_PadurarPadurar, {174}, {176, 177, 140}}, // LoadID 82
	
	//Taxi LOads de la 100
	{"Elodia", false, 150.00, PCV_TaxiTaxi, {149}, {142}}, // 
	{"Rihanna", false, 130.00, PCV_TaxiTaxi, {61}, {34}}, // 
	{"Nicola", false, 120.00, PCV_TaxiTaxi, {40}, {22}}, // 
	{"Sony", false, 100.00, PCV_TaxiTaxi, {31}, {103}}, // 
	{"Delia", false, 190.00, PCV_TaxiTaxi, {136}, {137, 142, 63, 61}}, //
	{"Osama Bilanden", false, 200.00, PCV_TaxiTaxi, {50}, {57}}, // 	
	{"Ion Iliescu", false, 90.00, PCV_TaxiTaxi, {121}, {160}}, // 	

	
	//Conducator Tren related
	{"Pasageri", false, 150.00, PCV_SoferTren, {163, 164, 165, 172, 173}, {165, 164, 163, 172, 173}}, // LoadID 77

	
	//Gunoier
	{"Cauciucuri", false, 150.00, PCV_GTrash, {167}, {166}}, // LoadID 78
	{"Mizerie", false, 200.00, PCV_GTrash, {168}, {166}}, // LoadID 79
	
	// Loads for cement truck
	{"Cement", false, 21.00, PCV_TruckerCementTruck, {12}, {1, 2, 3, 4}}, // LoadID 34
	
	
	//marinar
	{"Munitie", false, 893.00, PCV_MarinarBoat, {157}, {158, 159}}, // LoadID 46
	{"Cargo", false, 530.00, PCV_MarinarBoat, {156}, {157}}, // LoadID 47
	{"Peste", false, 350.00, PCV_MarinarBoat, {121}, {157}}, // LoadID 48
	{"Petrol", false, 750.00, PCV_MarinarBoat, {156}, {157}}, // LoadID 69
	{"Deseuri Toxice", false, 200.00, PCV_MarinarBoat, {156}, {157}}, // LoadID 70
	
	
	

	// Loads for truckers without trailer
	{"Hirtie", true, 70.60, PCV_TruckerNoTrailer, {136}, {143}}, // LoadID 35
	{"Drinks", false, 100.60, PCV_TruckerNoTrailer, {15, 54, 55}, {49, 50, 51, 52, 53}}, // LoadID 36
	{"Bottled Beer", true, 100.60, PCV_TruckerNoTrailer, {56}, {57, 58, 59, 60, 61}}, // LoadID 37
	{"Luxury Goods", false, 100.60, PCV_TruckerNoTrailer, {24, 55}, {47, 48, 50}}, // LoadID 38
	{"Electronics", true, 100.60, PCV_TruckerNoTrailer, {7, 24, 48}, {50, 51, 62, 63}}, // LoadID 39
	{"Sport Equipment", false, 100.60, PCV_TruckerNoTrailer, {47, 48}, {50, 53, 57}}, // LoadID 40
	{"Boards", false, 100.60, PCV_TruckerNoTrailer, {10}, {4, 7, 18, 22}}, // LoadID 41
	{"Building Materials", false, 10.60, PCV_TruckerNoTrailer, {4}, {1, 2, 3, 5}}, // LoadID 42
	{"LiveStock", false, 100.60, PCV_TruckerNoTrailer, {21, 22}, {23, 43, 47}}, // LoadID 43
	{"Meat", false, 100.60, PCV_TruckerNoTrailer, {43}, {44, 49, 50, 51, 52, 53}}, // LoadID 44
	{"Paper", false, 100.60, PCV_TruckerNoTrailer, {14}, {9, 62}}, // LoadID 45

	// Loads for pilots
	{"Passengers", false, 100.00, PCV_PilotPlane, {121, 122, 125, 126, 130, 131, 134}, {121, 122, 125, 126, 130, 131, 134}}, // LoadID 71
	{"Cargo", false, 100.00, PCV_PilotPlane, {123, 124, 127, 128, 129, 132, 133, 135}, {123, 124, 127, 128, 129, 132, 133, 135}}, // LoadID 72
	{"Passengers", false, 100.00, PCV_PilotHelicopter, {121, 122, 125, 126, 130, 131, 134}, {121, 122, 125, 126, 130, 131, 134}}, // LoadID 73


	// Loads for mafia
	{"Food", false, 111.50, PCV_MafiaVan, {7, 44, 47, 48}, {49, 50, 51, 52, 53}}, // LoadID 49
	{"Drinks", false, 71.50, PCV_MafiaVan, {15, 54, 55}, {49, 50, 51, 52, 53}}, // LoadID 50
	{"Bottled Beer", true, 111.50, PCV_MafiaVan, {56}, {57, 58, 59, 60, 61}}, // LoadID 51
	{"Luxury Goods", false, 71.50, PCV_MafiaVan, {24, 55}, {47, 48, 50}}, // LoadID 52
	{"Electronics", true, 111.50, PCV_MafiaVan, {7, 24, 48}, {50, 51, 62, 63}}, // LoadID 53
	{"Sport Equipment", false, 11.50, PCV_MafiaVan, {47, 48}, {50, 53, 57}}, // LoadID 54
	{"Boards", false, 111.50, PCV_MafiaVan, {10}, {4, 7, 18, 22}}, // LoadID 55
	{"Building Materials", false, 111.50, PCV_MafiaVan, {4}, {1, 2, 3, 5}}, // LoadID 56
	{"LiveStock", false, 111.50, PCV_MafiaVan, {21, 22}, {23, 43, 47}}, // LoadID 57
	{"Meat", false, 111.50, PCV_MafiaVan, {43}, {44, 49, 50, 51, 52, 53}}, // LoadID 58
	{"Paper", false, 73.50, PCV_MafiaVan, {14}, {9, 62}} // LoadID 59
};



// This function returns a string (array) that holds all ProductID's that are linked to a certain vehicletype (and player class)
stock Product_GetList(PCV_Needed, &NumProducts)
{
	// Setup local variables
	new ProductList[50];

	// Loop through all products
	for (new i; i < sizeof(ALoads); i++)
	{
		// Check if there aren't 50 products found (and added to the ProductList) yet
		if (NumProducts < 50)
		{
			// Check if the current product has the same PCV_Needed
			if (ALoads[i][PCV_Required] == PCV_Needed)
			{
				// Add the ProductID to the ProductList
				ProductList[NumProducts] = i;
				// Increase the counter NumProducts
				NumProducts++;
			}
		}
	}

	// Return the ProductList
	return ProductList;
}

// This function returns a random products for the given vehicletype (and player class)
stock Product_GetRandom(PCV_Needed)
{
	// Setup local variables
	new ProductList[50], NumProducts;

	// Get the entire product-list for this vehicle and class, and also the amount of products
	ProductList = Product_GetList(PCV_Needed, NumProducts);

	// Get a random product from this list and return it
	return ProductList[random(NumProducts)];
}

// This function returns a random startlocation from the given product (load)
stock Product_GetRandomStartLoc(ProductID)
{
	// Setup local variables
	new NumProducts;

	// First find out how many valid start-locations there are in this product
	for (new i; i < 30; i++)
	{
		// If the product has a valid location in this index
		if (ALoads[ProductID][FromLocations][i] != 0)
		    NumProducts++; // Count the number of valid start-locations
		else // A start-location with ID 0 has been found (dummy-location)
		    break; // Stop counting
	}

	// Return the LocationID that's stored at a random index
	return ALoads[ProductID][FromLocations][random(NumProducts)];
}

// This function returns a random endlocation from the given product (load)
stock Product_GetRandomEndLoc(ProductID)
{
	// Setup local variables
	new NumProducts;

	// First find out how many valid end-locations there are in this product
	for (new i; i < 30; i++)
	{
		// If the product has a valid location in this index
		if (ALoads[ProductID][ToLocations][i] != 0)
		    NumProducts++; // Count the number of valid end-locations
		else // An end-location with ID 0 has been found (dummy-location)
		    break; // Stop counting
	}

	// Return the LocationID that's stored at a random index
	return ALoads[ProductID][ToLocations][random(NumProducts)];
}

