#undef MAX_PLAYERS
#define MAX_PLAYERS 50

new bool:IntrestEnabled = false; // The intrest has been enabled (or disabled when false)
new Float:BankIntrest = 0.005; // The intrest a player receives every hour is by default 0.5% (0.005 means 0.1%)
								// Setting this to 1.0 would mean 100%, that would double the player's bank account every hour)

// Set timer-delay for exiting houses (this timer freezes a player when he exits a house, this allows the game to load the environment
// before the player starts to fall, also the player's vehicles assigned to the house he exits from, are respawned by this timer)
new ExitHouseTimer = 1000;
new ExitBusinessTimer = 1000;

// This allows you to toggle the red houses on the map (bought houses appear on the map as red house icons when this is set to "true")
new bool:ShowBoughtHouses = true;

// Define maximum fuel amount (default: 5000) and maximum price for a complete refuel (default: 1000)
// Changing MaxFuel changes how fast a vehicle will run without fuel
//      (setting it to 2500 for example, let's vehicles run out of fuel twice as fast)
// RefuelMaxPrice is the price you pay for a total refuel (when the vehicle has no more fuel), the price to pay is calculated
//      by the amount of fuel to refuel (pay 50% of RefuelMaxPrice when vehicle has half a fuel-tank left)
new MaxFuel = 5000;
new RefuelMaxPrice = 100000;

// Define housing parameters
#define MAX_HOUSES					5000 // Defines the maximum number of houses that can be created
#define MAX_HOUSESPERPLAYER			6 // Defines the maximum number of houses that any player can own
#define HouseUpgradePercent         70 // Defines the percentage for upgrading a house (house of 10m can be upgraded for 5m when set to 50)
#define ParkRange                  	5555555.555 // Defines the range for parking the vehicle around the house (default = 150m)

// Define business parameters
#define MAX_BUSINESS                5000 // Defines the maximum number of businesses that can be created
#define MAX_BUSINESSPERPLAYER		3 // Defines the maximum number of businesses that any player can own

// Defines for the toll-system
#define MAX_TOLLGATES				20

// Defines for spikestrips
#define MAX_SPIKESTRIPS             3 // Defines a maximum of 3 spikestrips

// Defines for the speedcameras
#define MAX_CAMERAS					300

// Arme Politie
new bool:PoliceGetsWeapons = true;
new APoliceWeapons[12] = {3, 22, 25, 46, 30, 32, 41};
new PoliceWeaponsAmmo = 700;


// Arme FBI
new bool:FBYGetsWeapons = true;
new AFBYWeapons[12] = {3, 17, 24, 27, 29, 31, 34, 41, 46};
new FBYWeaponsAmmo = 1000;


//Arme Mafia
new bool:MafiaGetsWeapons = true;
new AMafiaWeapons[12] = {4, 24, 28, 30, 34};
new MafiaWeaponsAmmo = 300;


// Jailing system variables
new DefaultJailTime = 60; // Set default jailtime to 1 minute
new DefaultFinePerStar = 20000; // Set the fine for each wanted level (star)
new DefaultWarnTimeBeforeJail = 30; // Allow the wanted player 30 seconds to pull over (always set this value to multiples of 5: 5, 10, 15, 20, ...)

// Courier variables
new Float:CourierJobRange = 1000.0;
new PaymentPerPackage = 100000;

// Pizza Boy variables
new Float:PboyJobRange = 500.0;
new Bani = 80500;



// Unclamp price per vehicle
new UnclampPricePerVehicle = 3000000;
