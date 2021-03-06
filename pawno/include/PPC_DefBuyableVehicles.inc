// This file holds an array of defined buyable vehicles, used in the /buycar and /rentcar dialogs


#define VClassBike          1
#define VClassBoat          2
#define VClassConvertible   3
#define VClassHelicopter    4
#define VClassIndustrial    5
#define VClassLowRider      6
#define VClassOffRoad       7
#define VClassPlane         8
#define VClassPublic        9
#define VClassRCVehicle     10
#define VClassSaloons       11
#define VClassSportCar      12
#define VClassStationCar    13
#define VClassTrailer       14
#define VClassUnique        15

enum TBuyableVehicle
{
	CarName[50], // Holds the name of the vehicle
	VehicleClass, // Holds the ID of the vehicleclass
	CarModel, // Holds the model-ID of the vehicle
	Price // Holds the price for the vehicle (renting it will be 10% of this price)
}

new ABuyableVehicles[][TBuyableVehicle] =
{
	{"Admiral", VClassSaloons, 445, 50000},
	{"Alpha", VClassSportCar, 602, 5000000},
	{"Ambulance", VClassPublic, 416, 5000000},
	{"Andromada", VClassPlane, 592, 50000000},
	{"Article Trailer", VClassTrailer, 591, 5000000},
	{"AT400", VClassPlane, 577, 500000000},
	{"Baggage", VClassUnique, 485, 500000},
	{"Baggage Trailer A", VClassTrailer, 606, 5000000},
	{"Baggage Trailer B", VClassTrailer, 607, 5000000},
	{"Bandito", VClassOffRoad, 568, 5000000},
	{"Banshee", VClassSportCar, 429, 5000000},
	{"Barracks", VClassPublic, 433, 5000000},
	{"Beagle", VClassPlane, 511, 5000000},
	{"Benson", VClassIndustrial, 499, 5000000},
	{"Berkley's RC Van", VClassIndustrial, 459, 5000000},
	{"BF Injection", VClassOffRoad, 424, 5000000},
	{"BF-400", VClassBike, 581, 5000000},
	{"Bike", VClassBike, 509, 5000000},
	{"Blade", VClassLowRider, 536, 5000000},
	{"Blista Compact", VClassSportCar, 496, 5000000},
	{"Bloodring Banger", VClassSaloons, 504, 5000000},
	{"BMX", VClassBike, 481, 500000},
	{"Bobcat", VClassIndustrial, 422, 500000},
	{"Boxville 1", VClassIndustrial, 498, 500000},
	{"Boxville 2", VClassIndustrial, 609, 500000},
	{"Bravura", VClassSaloons, 401, 500000},
	{"Broadway", VClassLowRider, 575, 500000},
//	{"Brownstreak (train)", VClassUnique, 538, 500000},
	{"Buccaneer", VClassSaloons, 518, 500000},
	{"Buffalo", VClassSportCar, 402, 500000},
	{"Bullet", VClassSportCar, 541, 1150000},
	{"Burrito", VClassIndustrial, 482, 5000000},
	{"Bus", VClassPublic, 431, 5000000},
	{"Cabbie", VClassPublic, 438, 500000},
	{"Caddy", VClassUnique, 457, 500000},
	{"Cadrona", VClassSaloons, 527, 500000},
	{"Camper", VClassUnique, 483, 500000},
	{"Cargo Trailer", VClassTrailer, 435, 9500000},
	{"Cargobob", VClassHelicopter, 548, 500100},
	{"Cement Truck", VClassIndustrial, 524, 5011000},
	{"Cheetah", VClassSportCar, 415, 501000},
	{"Clover", VClassSaloons, 542, 510000},
	{"Club", VClassSportCar, 589, 5011000},
	{"Coach", VClassPublic, 437, 510000},
	{"Coastguard", VClassBoat, 472, 5110000},
	{"Combine Harvester", VClassUnique, 532, 510000},
	{"Comet", VClassConvertible, 480, 510000},
	{"Cropduster", VClassPlane, 512, 510000},
	{"DFT-30", VClassIndustrial, 578, 5110000},
	{"Dinghy", VClassBoat, 473, 510000},
	{"Dodo", VClassPlane, 593, 510000},
	{"Dozer", VClassUnique, 486, 510000},
	{"Dumper", VClassUnique, 406, 510000},
	{"Dune", VClassOffRoad, 573, 510000},
	{"Elegant", VClassSaloons, 507, 510000},
	{"Elegy", VClassSaloons, 562, 5010000},
	{"Emperor", VClassSaloons, 585, 501000},
	{"Enforcer", VClassPublic, 427, 510000},
	{"Esperanto", VClassSaloons, 419, 510000},
	{"Euros", VClassSportCar, 587, 510000},
	{"Faggio", VClassBike, 462, 510000},
	{"Farm Trailer", VClassTrailer, 610, 510000},
	{"FBI Rancher", VClassPublic, 490, 510000},
	{"FBI Truck", VClassPublic, 528, 510000},
	{"FCR-900", VClassBike, 521, 5001000},
	{"Feltzer", VClassConvertible, 533, 510000},
	{"Firetruck", VClassPublic, 407, 510000},
	{"Firetruck LA", VClassPublic, 544, 501000},
	{"Flash", VClassSportCar, 565, 510000},
	{"Flatbed", VClassIndustrial, 455, 510000},
	{"Fluids Trailer", VClassTrailer, 584, 510000},
	{"Forklift", VClassUnique, 530, 510000},
	{"Fortune", VClassSaloons, 526, 510000},
	{"Freeway", VClassBike, 463, 510000},
//	{"Freight (train)", VClassUnique, 537, 500000000},
//	{"Freight Box Trailer (train)", VClassTrailer, 590, 50000},
//	{"Freight Flat Trailer (train)", VClassTrailer, 569, 50000},
	{"Glendale", VClassSaloons, 466, 510000},
	{"Glendale Shit", VClassSaloons, 604, 510000},
	{"Greenwood", VClassSaloons, 492, 510000},
	{"Hermes", VClassSaloons, 474, 510000},
	{"Hotdog", VClassUnique, 588, 510000},
	{"Hotknife", VClassUnique, 434, 510000},
	{"Hotring Racer 1", VClassSportCar, 494, 510000},
	{"Hotring Racer 2", VClassSportCar, 502, 510000},
	{"Hotring Racer 3", VClassSportCar, 503, 510000},
	{"HPV1000", VClassPublic, 523, 510000},
	{"Hunter", VClassHelicopter, 425, 5500000},
	{"Huntley", VClassOffRoad, 579, 550000},
	{"Hustler", VClassUnique, 545, 550000},
	{"Hydra", VClassPlane, 520, 5500000},
	{"Infernus", VClassSportCar, 411, 5500000},
	{"Intruder", VClassSaloons, 546, 550000},
	{"Jester", VClassSportCar, 559, 5550000},
	{"Jetmax", VClassBoat, 493, 5550000},
	{"Journey", VClassUnique, 508, 550000},
	{"Kart", VClassUnique, 571, 5055000},
	{"Landstalker", VClassOffRoad, 400, 550000},
	{"Launch", VClassBoat, 595, 505500},
	{"Leviathan", VClassHelicopter, 417, 505000},
	{"Linerunner", VClassIndustrial, 403, 5550000},
	{"Majestic", VClassSaloons, 517, 505000},
	{"Manana", VClassSaloons, 410, 505000},
	{"Marquis", VClassBoat, 484, 500050},
	{"Maverick", VClassHelicopter, 487, 5055000},
	{"Merit", VClassSaloons, 551, 505000},
	{"Mesa", VClassOffRoad, 500, 500500},
	{"Monster", VClassOffRoad, 444, 5550000},
	{"Monster A", VClassOffRoad, 556, 5055000},
	{"Monster B", VClassOffRoad, 557, 5066000},
	{"Moonbeam", VClassStationCar, 418, 505000},
	{"Mountain Bike", VClassBike, 510, 500},
	{"Mower", VClassUnique, 572, 500100},
	{"Mr Whoopee", VClassUnique, 423, 550000},
	{"Mule", VClassIndustrial, 414, 508000},
	{"Nebula", VClassSaloons, 516, 508000},
	{"Nevada", VClassPlane, 553, 570000},
	{"Newsvan", VClassIndustrial, 5982, 50000},
	{"NRG-500", VClassBike, 522, 570000},
	{"Oceanic", VClassSaloons, 467, 550000},
	{"Ore Trailer", VClassTrailer, 450, 5660000},
	{"Packer", VClassIndustrial, 443, 545000},
	{"Patriot", VClassOffRoad, 470, 5450000},
	{"PCJ-600", VClassBike, 461, 5450000},
	{"Perenniel", VClassStationCar, 404, 50000},
	{"Phoenix", VClassSportCar, 603, 5041000},
	{"Picador", VClassIndustrial, 600, 50000},
	{"Pizzaboy", VClassBike, 448, 50000},
	{"Police Car (LSPD)", VClassPublic, 596, 6500000},
	{"Police Car (LVPD)", VClassPublic, 598, 6500000},
	{"Police Car (SFPD)", VClassPublic, 597, 6500000},
	{"Police Maverick", VClassHelicopter, 497, 5500000},
	{"Police Ranger", VClassPublic, 599, 5900000},
	{"Pony", VClassIndustrial, 413, 1500000},
	{"Predator", VClassBoat, 430, 4450000},
	{"Premier", VClassSaloons, 426, 4450000},
	{"Previon", VClassSaloons, 436, 4450000},
	{"Primo", VClassSaloons, 547, 1450000},
	{"Quad", VClassBike, 471, 1450000},
	{"Raindance", VClassHelicopter, 563, 5770000},
	{"Rancher 1", VClassOffRoad, 489, 5770000},
	{"Rancher 2", VClassOffRoad, 505, 570000},
//	{"RC Bandit", VClassRCVehicle, 441, 50000},
//	{"RC Baron", VClassRCVehicle, 464, 50000},
//	{"RC Cam", VClassRCVehicle, 594, 50000},
//	{"RC Goblin", VClassRCVehicle, 501, 50000},
//	{"RC Raider", VClassRCVehicle, 465, 50000},
//	{"RC Tiger", VClassRCVehicle, 564, 50000},
	{"Reefer", VClassBoat, 453, 570000},
	{"Regina", VClassStationCar, 479, 410000},
	{"Remington", VClassLowRider, 534, 50000},
	{"Rhino", VClassPublic, 432, 70000000},
	{"Roadtrain", VClassIndustrial, 515, 9991000},
	{"Romero", VClassUnique, 442, 150000},
	{"Rumpo", VClassIndustrial, 440, 150000},
	{"Rustler", VClassPlane, 476, 2250000},
	{"Sabre", VClassSportCar, 475, 2250000},
	{"Sadler", VClassIndustrial, 543, 510000},
	{"Sadler Shit", VClassIndustrial, 605, 5110000},
	{"SAN News Maverick", VClassHelicopter, 488, 5000000},
	{"Sanchez", VClassBike, 468, 5500000},
	{"Sandking", VClassOffRoad, 495, 500000},
	{"Savanna", VClassLowRider, 567, 500000},
	{"Seasparrow", VClassHelicopter, 447, 1500000},
	{"Securicar", VClassUnique, 428, 500000},
	{"Sentinel", VClassSaloons, 405, 500000},
	{"Shamal", VClassPlane, 519, 500000},
	{"Skimmer", VClassPlane, 460, 500000},
	{"Slamvan", VClassLowRider, 535, 1150000},
	{"Solair", VClassStationCar, 458, 1150000},
	{"Sparrow", VClassHelicopter, 469, 1150000},
	{"Speeder", VClassBoat, 452, 110000},
	{"Squallo", VClassBoat, 446, 150000},
	{"Stafford", VClassSaloons, 580, 110000},
	{"Stallion", VClassConvertible, 439, 150000},
	{"Stratum", VClassStationCar, 561, 1500100},
//	{"Streak Trailer (train)", VClassTrailer, 570, 50000},
	{"Stretch", VClassUnique, 409, 50452000},
	{"Stuntplane", VClassPlane, 513, 61110000},
	{"Sultan", VClassSaloons, 560, 50000000},
	{"Sunrise", VClassSaloons, 550, 5110000},
	{"Super GT", VClassSportCar, 506,9990000},
	{"S.W.A.T.", VClassPublic, 601, 51110000},
	{"Sweeper", VClassUnique, 574, 11150000},
	{"Tahoma", VClassLowRider, 566, 1150000},
	{"Tampa", VClassSaloons, 549, 1500100},
	{"Tanker", VClassIndustrial, 514, 511000},
	{"Taxi", VClassPublic, 420, 5001100},
	{"Tornado", VClassLowRider, 576, 5000000},
	{"Towtruck", VClassUnique, 525, 5000000},
	{"Tractor", VClassIndustrial, 531, 5000000},
//	{"Tram", VClassUnique, 449, 5011000},
	{"Trashmaster", VClassIndustrial, 408, 5011000},
	{"Tropic", VClassBoat, 454, 5140000},
	{"Tug", VClassUnique, 583, 5540000},
	{"Tug Stairs Trailer", VClassTrailer, 608, 5440000},
	{"Turismo", VClassSportCar, 451, 5011000},
	{"Uranus", VClassSportCar, 558, 51100000},
	{"Utility Trailer", VClassTrailer, 611, 5440000},
	{"Utility Van", VClassIndustrial, 552, 5011000},
	{"Vincent", VClassSaloons, 540, 5740000},
	{"Virgo", VClassSaloons, 491, 5057000},
	{"Voodoo", VClassLowRider, 412, 5750000},
	{"Vortex", VClassUnique, 539, 5007500},
	{"Walton", VClassIndustrial, 478, 501000},
	{"Washington", VClassSaloons, 421, 5014000},
	{"Wayfarer", VClassBike, 586, 5040400},
	{"Willard", VClassSaloons, 529, 5004100},
	{"Windsor", VClassConvertible, 555, 5410000},
    {"Yankee", VClassIndustrial, 456, 5450000},
	{"Yosemite", VClassIndustrial, 554, 1150000},
	{"ZR-350", VClassSportCar, 477, 4150000}
};



// This function searches the ABuyableVehicles array to search for the model and returns the index in the array
VehicleBuyable_GetIndex(vModel)
{
	// Loop through all vehicles in the ABuyableVehicles array
	for (new i; i < sizeof(ABuyableVehicles); i++)
	{
	    // Check if the model of the current vehicle is the same as the given model
		if (ABuyableVehicles[i][CarModel] == vModel)
		    return i; // Return the index of the array where the carmodel was found
	}

	return -1;
}

