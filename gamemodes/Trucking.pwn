#pragma tabsize 0
#include <a_samp>
#include <zcmd>
#define COL_WHITE 0xEFEFEFFF
#define EMBED_WHITE {EFEFEF}
#define CO_ORANGE 0xFF9900AA
#define CO_YELLOW 0xFFFF00FF
#define CO_RED 0xFF0000FF
#define green 0x16EB43FF
#define red 0xFF0000AA
#define blue 0x33CCFFAA
#define vBlue 0x0259EAAA
#define vRed 0xFF0000AA
#define vGreen 0x16EB43FF
#define vPurple 0xB360FDFF
#define vPink 0xCCFF00FF
#define vYellow 0xFFFF00FF
#define vGrey 0xC0C0C0FF
#define vOrange 0xFFA500FF
#define vBrown 0x800000FF
#define COLOR_BLUE 0x375FFFFF
#define COLOR_GREY 0xAFAFAFAA
#define COLOR_GREEN 0x33AA33AA
#define COLOR_RED 0xAA3333AA
#define COLOR_YELLOW 0xFFFF00AA
#define COLOR_MEDBLUE 0x0091FFFF
#define COLOR_YELLOW 0xFFFF00AA
#define COLOR_YELLOW2 0xF5DEB3AA
#define PRESSED(%0) \
    (((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))

new PlayersBeforePolice	= 0;
new XDeaths[MAX_PLAYERS];
new LastDeath[MAX_PLAYERS];
//Includes
#include <dutils>
#include <sscanf2>
#include <streamer>
#include <JunkBuster>
#include <PPC_DefTexts>
#include <PPC_ServerSettings>
#include <PPC_Defines>
#include <PPC_DefLocations>
#include <PPC_DefLoads>
#include <PPC_DefCars>
#include <PPC_DefPlanes>
#include <PPC_DefTrailers>
#include <PPC_DefBuyableVehicles>
#include <PPC_GlobalTimer>
#include <PPC_Common>
#include <PPC_Housing>
#include <PPC_Business>
#include <PPC_GameModeInit>
#include <PPC_FileOperations>
#include <PPC_Speedometer>
#include <PPC_Extras>
#include <PPC_MissionsTrucking>
#include <PPC_MissionsBus>
#include <PPC_MissionsPilot>
#include <PPC_MissionsPolice>
#include <PPC_MissionsMafia>
#include <PPC_MissionsAssistance>
#include <PPC_MissionsCourier>
#include <PPC_MissionsRoadworker>
#include <PPC_Convoys>
#include <PPC_Dialogs>
#include <PPC_PlayerCommands>
#include <PPC_Toll>
#include <PPC_MissionMedic>
#include <PPC_MissionsFBY>
#include <PPC_MissionsPboy>
#include <PPC_MissionsSofer>
#include <PPC_MissionsG>
#include <PPC_MissionsMarinar>
#include <PPC_MissionsTaxi>
#include <PPC_MissionsPadurar>

// The main function (used only once when the server loads)
main()
{
	// Print some standard lines to the server's console
	print("\n----------------------------------");
	print("-----");
	print("Response: case 1");
	print("----------------------------------\n");
}
// This callback gets called when the server initializes the gamemode
public OnGameModeInit()
{
	GameModeInit_VehiclesPickups(); // Add all static vehicles and pickups when the server starts that are required (also load the houses)
	GameModeInit_Classes(); // Add character models to the class-selection (without weapons)

	Convoys_Init(); // Setup textdraws and default data for convoys

	ShowPlayerMarkers(1); // Show players on the entire map (and on the radar)
	ShowNameTags(1); // Show player names (and health) above their head
	ManualVehicleEngineAndLights(); // Let the server control the vehicle's engine and lights
	EnableStuntBonusForAll(0); // Disable stunt bonus for all players
	DisableInteriorEnterExits(); // Removes all building-entrances in the game
	UsePlayerPedAnims(); // Use CJ's walking animation

	// Start the timer that will show timed messages every 2 minutes
	SetTimer("Timer_TimedMessages", 1000 * 60 * 5, true);
	// Start the timer that will show a random bonus mission for truckers every 5 minutes
	SetTimer("ShowRandomBonusMission", 1000 * 60 * 5, true);
	// Start the timer that checks the toll-gates
	SetTimer("Toll", 1000, true);
	
	//Infinite Nitro
	SetTimer("NitroReset", 3000, 1);
	// Fix the bugged houses (after fixing the houses, you can remove this line, as it's not needed anymore)
	FixHouses();

	// While the gamemode starts, start the global timer, and run it every second
	SetTimer("GlobalTimer", 1000, true);
	//Semne de circulatie
	new Bucuresti = CreateObject(19353, -2466.9526, 2236.5502, 9.8563, 0.0000, 0.0000, 89.7577);
	SetObjectMaterialText(Bucuresti, "Bucuresti", 0, 90, "Arial", 24, 1, -65281, 0, 1);
	
	new Cityville = CreateObject(19353, 2872.2746, -1975.9941, 18.1231, -0.2999, -1.2000, -179.5621);
	SetObjectMaterialText(Cityville, "CityVille", 0, 50, "Arial", 30, 0, -65536, 0, 1);
	
	new CirtVille2 = CreateObject(19353, 2872.1218, -1969.6002, 18.0155, -0.7999, 1.6000, -179.3623);
	SetObjectMaterialText(CirtVille2, "CityVille", 0, 50, "Arial", 30, 0, -65536, 0, 1);

	new Ls = CreateObject(19353, 2874.5537, -1958.7592, 18.2131, 0.0000, 0.0000, 0.1665);
	SetObjectMaterialText(Ls, "Los Santos", 0, 50, "Arial", 24, 0, -16776961, 0, 1);

	new Ls2 = CreateObject(19353, 2874.5607, -1952.4980, 18.1431, 0.0000, 0.0000, 0.7731);
	SetObjectMaterialText(Ls2, "Los Santos", 0, 50, "Arial", 24, 0, -65536, 0, 1);

	new welcome = CreateObject(19353, 1454.4317, 997.2934, 9.7993, -1.0999, -90.0998, -93.5626);
	SetObjectMaterialText(welcome, "RLT iti ureaza Distractie placuta! ", 0, 140, "Arial", 24, 0, -65536, 0, 1);

	new Bucuresti3 = CreateObject(19353, -2469.3129, 1861.7662, 10.1755, -0.0999, 0.0000, 89.7867);
	SetObjectMaterialText(Bucuresti3, "Bucuresti >", 0, 50, "Arial", 24, 0, -65536, 0, 1);

	new BucurestiConstanta = CreateObject(19353, -2496.6354, 1833.8712, 10.0333, -0.3000, 9.1999, -0.2132);
	SetObjectMaterialText(BucurestiConstanta, "^^Bucuresti^^Constanta^^", 0, 100, "Arial", 24, 0, -65536, 0, 1);

	new CosBuc = CreateObject(19353, -3555.2246, 1834.0633, 10.2248, 0.0000, 0.0000, -0.7132);
	SetObjectMaterialText(CosBuc, "<<Constanta ^^>>Bucuresti^^", 0, 100, "Arial", 24, 0, -65536, 0, 1);

	new Bucuresti7 = CreateObject(19353, -3613.9943, 1833.9085, 10.4303, -0.4999, 0.0000, -0.7132);
	SetObjectMaterialText(Bucuresti7, "^^Bucuresti^^", 0, 60, "Arial", 24, 0, -65536, 0, 1);

	new Constantaint = CreateObject(19353, -3596.8090, 1618.6654, 10.7107, 0.0000, 0.0000, 90.4867);
	SetObjectMaterialText(Constantaint, "Constanta", 0, 60, "Arial", 24, 0, -65536, 0, 1);

	new Bineaivenit = CreateObject(19353, 1450.1817, 994.3056, 9.7671, 0.0999, -90.0000, -89.9389);
	SetObjectMaterialText(Bineaivenit, "Bine Ai venit!", 0, 60, "Arial", 20, 0, -16776961, 0, 1);
	
	return 1;
}
// This callback gets called when a player connects to the server
public OnPlayerConnect(playerid)
{
	// Always allow NPC's to login without password or account

	if (IsPlayerNPC(playerid))
 		return 1;

	// Setup local variables
	new Name[MAX_PLAYER_NAME], NewPlayerMsg[128], HouseID;

	// Setup a PVar to allow cross-script money-transfers (only from filterscript to this mainscript) and scorepoints
	SetPVarInt(playerid, "PVarMoney", 0);
	SetPVarInt(playerid, "PVarScore", 0);

	// Get the playername
	GetPlayerName(playerid, Name, sizeof(Name));
	// Also store this name for the player
	GetPlayerName(playerid, APlayerData[playerid][PlayerName], 24);

	// Send a message to all players to let them know somebody else joined the server
	format(NewPlayerMsg, 128, TXT_PlayerJoinedServer, Name, playerid);
	SendClientMessageToAll(0xFFFFFFFF, NewPlayerMsg);

	// Try to load the player's datafile ("PlayerFile_Load" returns "1" is the file has been read, "0" when the file cannot be read)
	if (PlayerFile_Load(playerid) == 1)
	{
		// Check if the player is still banned
		if (APlayerData[playerid][BanTime] < gettime()) // Player ban-time is passed
			ShowPlayerDialog(playerid, DialogLogin, DIALOG_STYLE_INPUT, TXT_DialogLoginTitle, TXT_DialogLoginMsg, TXT_DialogLoginButton1, TXT_DialogButtonCancel);
		else // Player is still banned
		{
			ShowRemainingBanTime(playerid); // Show the remaining ban-time to the player is days, hours, minutes, seconds
			Kick(playerid); // Kick the player
		}
	}
	else
	ShowPlayerDialog(playerid, DialogRegister, DIALOG_STYLE_INPUT, TXT_DialogRegisterTitle, TXT_DialogRegisterMsg, TXT_DialogRegisterButton1, TXT_DialogButtonCancel);

	// The houses have been loaded but not the cars, so load all vehicles assigned to the player's houses
	for (new HouseSlot; HouseSlot < MAX_HOUSESPERPLAYER; HouseSlot++)
	{
	    // Get the HouseID from this slot
	    HouseID = APlayerData[playerid][Houses][HouseSlot];
	    // Check if there is a house in this slot
		if (HouseID != 0)
		    HouseFile_Load(HouseID, true); // Load the cars of the house
	}

	// Speedometer setup
	Speedometer_Setup(playerid);

	// MissionText TextDraw setup
	APlayerData[playerid][MissionText] = TextDrawCreate(320.0, 430.0, " "); // Setup the missiontext at the bottom of the screen
	TextDrawAlignment(APlayerData[playerid][MissionText], 2); // Align the missiontext to the center
	TextDrawUseBox(APlayerData[playerid][MissionText], 1); // Set the missiontext to display inside a box
	TextDrawBoxColor(APlayerData[playerid][MissionText], 0x00000066); // Set the box color of the missiontext
	TextDrawFont(APlayerData[playerid][MissionText], 1);//set stilu de scris text


	// Display a message if the player hasn't accepted the rules yet
	if (APlayerData[playerid][RulesRead] == false)
 	SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}Nu ai Acceptat {FFFF00}/rules{FF0000}");


	RemoveBuildingForPlayer(playerid, 8116, 1435.5859, 952.5859, 15.5234, 0.25);
	RemoveBuildingForPlayer(playerid, 8117, 1447.4141, 1056.1875, 15.7813, 0.25);
	RemoveBuildingForPlayer(playerid, 8118, 1343.6875, 1130.3906, 13.5313, 0.25);
	RemoveBuildingForPlayer(playerid, 8119, 1486.9766, 1104.5703, 13.8203, 0.25);
	RemoveBuildingForPlayer(playerid, 8160, 1417.6328, 1152.3438, 13.5547, 0.25);
	RemoveBuildingForPlayer(playerid, 8163, 1316.2578, 1129.3828, 15.8750, 0.25);
	RemoveBuildingForPlayer(playerid, 998, 1393.7734, 927.0938, 10.7344, 0.25);
	RemoveBuildingForPlayer(playerid, 1365, 1392.2188, 939.7188, 10.9609, 0.25);
	RemoveBuildingForPlayer(playerid, 1219, 1392.4531, 956.2109, 10.0625, 0.25);
	RemoveBuildingForPlayer(playerid, 1219, 1392.4531, 953.3828, 10.0625, 0.25);
	RemoveBuildingForPlayer(playerid, 1219, 1392.4531, 950.4844, 10.0625, 0.25);
	RemoveBuildingForPlayer(playerid, 1219, 1392.4531, 947.6641, 10.0625, 0.25);
	RemoveBuildingForPlayer(playerid, 998, 1393.8672, 969.4922, 10.7344, 0.25);
	RemoveBuildingForPlayer(playerid, 640, 1399.0078, 969.2734, 10.5156, 0.25);
	RemoveBuildingForPlayer(playerid, 1358, 1379.0313, 980.7656, 11.0703, 0.25);
	RemoveBuildingForPlayer(playerid, 8066, 1435.5859, 952.5859, 15.5234, 0.25);
	RemoveBuildingForPlayer(playerid, 1616, 1420.5469, 969.0547, 16.4297, 0.25);
	RemoveBuildingForPlayer(playerid, 640, 1436.0703, 969.2734, 10.5156, 0.25);
	RemoveBuildingForPlayer(playerid, 1420, 1432.7188, 1013.7109, 9.8203, 0.25);
	RemoveBuildingForPlayer(playerid, 1420, 1436.1953, 1013.7109, 9.8203, 0.25);
	RemoveBuildingForPlayer(playerid, 1616, 1430.9453, 1026.1875, 16.4297, 0.25);
	RemoveBuildingForPlayer(playerid, 1219, 1447.2422, 1012.7656, 10.0313, 0.25);
	RemoveBuildingForPlayer(playerid, 1219, 1444.4141, 1012.7656, 10.0313, 0.25);
	RemoveBuildingForPlayer(playerid, 1219, 1450.1406, 1012.7656, 10.0313, 0.25);
	RemoveBuildingForPlayer(playerid, 1219, 1452.9609, 1012.7656, 10.0313, 0.25);
	RemoveBuildingForPlayer(playerid, 1331, 1303.2188, 1102.7188, 10.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1338, 1303.2344, 1107.8906, 10.4922, 0.25);
	RemoveBuildingForPlayer(playerid, 1438, 1384.8828, 1101.3750, 9.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 1420, 1384.0391, 1111.6250, 9.8203, 0.25);
	RemoveBuildingForPlayer(playerid, 1616, 1430.9453, 1063.3359, 16.4297, 0.25);
	RemoveBuildingForPlayer(playerid, 1338, 1430.5391, 1077.7813, 10.4922, 0.25);
	RemoveBuildingForPlayer(playerid, 1338, 1428.6172, 1075.2500, 10.4922, 0.25);
	RemoveBuildingForPlayer(playerid, 1684, 1429.2734, 1094.3203, 11.3281, 0.25);
	RemoveBuildingForPlayer(playerid, 1219, 1437.6797, 1099.3750, 10.0313, 0.25);
	RemoveBuildingForPlayer(playerid, 1219, 1447.2422, 1099.3750, 10.0313, 0.25);
	RemoveBuildingForPlayer(playerid, 1219, 1444.4141, 1099.3750, 10.0313, 0.25);
	RemoveBuildingForPlayer(playerid, 8067, 1447.4141, 1056.1875, 15.7813, 0.25);
	RemoveBuildingForPlayer(playerid, 1219, 1450.1406, 1099.3750, 10.0313, 0.25);
	RemoveBuildingForPlayer(playerid, 1219, 1312.8906, 1128.3594, 10.0625, 0.25);
	RemoveBuildingForPlayer(playerid, 1420, 1384.0391, 1125.2891, 9.8203, 0.25);
	RemoveBuildingForPlayer(playerid, 1338, 1405.9688, 1127.0938, 10.4922, 0.25);
	RemoveBuildingForPlayer(playerid, 1431, 1409.0469, 1126.0391, 10.3594, 0.25);
	RemoveBuildingForPlayer(playerid, 1219, 1312.8906, 1134.0781, 10.0625, 0.25);
	RemoveBuildingForPlayer(playerid, 1219, 1312.8906, 1136.8984, 10.0625, 0.25);
	RemoveBuildingForPlayer(playerid, 1219, 1312.8906, 1131.1719, 10.0625, 0.25);
	RemoveBuildingForPlayer(playerid, 8074, 1316.2578, 1129.3828, 15.8750, 0.25);
	RemoveBuildingForPlayer(playerid, 8065, 1343.6875, 1130.3906, 13.5313, 0.25);
	RemoveBuildingForPlayer(playerid, 1616, 1319.6719, 1152.8594, 14.8047, 0.25);
	RemoveBuildingForPlayer(playerid, 640, 1356.6484, 1152.9453, 10.5156, 0.25);
	RemoveBuildingForPlayer(playerid, 640, 1336.8672, 1158.6484, 10.5156, 0.25);
	RemoveBuildingForPlayer(playerid, 1420, 1384.0391, 1138.7891, 9.8203, 0.25);
	RemoveBuildingForPlayer(playerid, 1420, 1384.0391, 1151.9688, 9.8203, 0.25);
	RemoveBuildingForPlayer(playerid, 8069, 1417.6328, 1152.3438, 13.5547, 0.25);
	RemoveBuildingForPlayer(playerid, 640, 1348.5547, 1163.9063, 10.5156, 0.25);
	RemoveBuildingForPlayer(playerid, 1334, 1338.8047, 1164.1563, 10.9297, 0.25);
	RemoveBuildingForPlayer(playerid, 659, 1353.1328, 1181.4766, 10.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 680, 1339.1328, 1181.4297, 9.7969, 0.25);
	RemoveBuildingForPlayer(playerid, 615, 1373.5469, 1181.2969, 7.1875, 0.25);
	RemoveBuildingForPlayer(playerid, 629, 1364.5781, 1179.6328, 10.0625, 0.25);
	RemoveBuildingForPlayer(playerid, 712, 1400.0313, 1180.0078, 18.9688, 0.25);
	RemoveBuildingForPlayer(playerid, 680, 1414.7344, 1180.2344, 9.7969, 0.25);
	RemoveBuildingForPlayer(playerid, 998, 1477.3828, 927.0938, 10.7344, 0.25);
	RemoveBuildingForPlayer(playerid, 1438, 1476.0078, 935.3594, 9.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 1420, 1477.7813, 938.6484, 9.8203, 0.25);
	RemoveBuildingForPlayer(playerid, 1420, 1477.7813, 940.0156, 9.8203, 0.25);
	RemoveBuildingForPlayer(playerid, 1331, 1478.1250, 963.5625, 10.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1616, 1465.0391, 969.0547, 16.4297, 0.25);
	RemoveBuildingForPlayer(playerid, 640, 1471.7422, 969.2734, 10.5156, 0.25);
	RemoveBuildingForPlayer(playerid, 1331, 1478.1250, 967.0703, 10.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 659, 1494.8750, 985.8516, 9.8203, 0.25);
	RemoveBuildingForPlayer(playerid, 674, 1487.3906, 1001.6719, 9.7656, 0.25);
	RemoveBuildingForPlayer(playerid, 998, 1464.3203, 1023.2734, 10.7344, 0.25);
	RemoveBuildingForPlayer(playerid, 640, 1463.8828, 1018.5469, 10.5156, 0.25);
	RemoveBuildingForPlayer(playerid, 640, 1463.8828, 1056.0703, 10.5156, 0.25);
	RemoveBuildingForPlayer(playerid, 1331, 1464.2188, 1081.7422, 10.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 640, 1463.8828, 1092.7969, 10.5156, 0.25);
	RemoveBuildingForPlayer(playerid, 8073, 1486.9766, 1104.5703, 13.8203, 0.25);
	RemoveBuildingForPlayer(playerid, 1420, 1428.7500, 1127.5078, 9.8203, 0.25);
	RemoveBuildingForPlayer(playerid, 1420, 1427.8359, 1127.5078, 9.8203, 0.25);
	RemoveBuildingForPlayer(playerid, 1420, 1426.9219, 1127.5078, 9.8203, 0.25);
	RemoveBuildingForPlayer(playerid, 657, 1432.3203, 1180.0547, 9.9688, 0.25);
	

	RemoveBuildingForPlayer(playerid, 8113, 1665.1719, 687.0469, 14.3906, 0.25);
	RemoveBuildingForPlayer(playerid, 8114, 1634.7188, 772.8438, 13.8203, 0.25);
	RemoveBuildingForPlayer(playerid, 8115, 1695.4922, 673.2188, 13.8203, 0.25);
	RemoveBuildingForPlayer(playerid, 8159, 1665.5625, 753.8281, 14.3906, 0.25);
	RemoveBuildingForPlayer(playerid, 8254, 1665.1719, 687.0469, 14.3906, 0.25);
	RemoveBuildingForPlayer(playerid, 8255, 1665.5625, 753.8281, 14.3906, 0.25);
	RemoveBuildingForPlayer(playerid, 1358, 1679.6953, 767.4297, 11.0078, 0.25);
	RemoveBuildingForPlayer(playerid, 8078, 1634.7188, 772.8438, 13.8203, 0.25);
	RemoveBuildingForPlayer(playerid, 1335, 1651.0547, 774.8047, 10.9453, 0.25);
	RemoveBuildingForPlayer(playerid, 8077, 1695.4922, 673.2188, 13.8203, 0.25);
	RemoveBuildingForPlayer(playerid, 1219, 1709.0547, 744.4297, 10.9141, 0.25);
	RemoveBuildingForPlayer(playerid, 1219, 1709.0547, 747.0781, 10.9141, 0.25);

    RemoveBuildingForPlayer(playerid,  3276, -1427.8516, -1600.0859, 101.4844, 0.25);
	RemoveBuildingForPlayer(playerid,  3276, -1439.2656, -1600.3359, 101.4844, 0.25);
	RemoveBuildingForPlayer(playerid,  3276, -1451.1016, -1599.6016, 101.5547, 0.25);
	RemoveBuildingForPlayer(playerid,  3276, -1462.6484, -1599.2031, 101.6328, 0.25);
	RemoveBuildingForPlayer(playerid,  3276, -1420.6563, -1594.0313, 101.4844, 0.25);
	RemoveBuildingForPlayer(playerid,  3276, -1468.4766, -1593.0625, 101.4844, 0.25);
	RemoveBuildingForPlayer(playerid,  3276, -1417.7969, -1583.0313, 101.4844, 0.25);
	RemoveBuildingForPlayer(playerid,  3276, -1468.9766, -1581.4844, 101.4844, 0.25);
	RemoveBuildingForPlayer(playerid,  3276, -1470.7422, -1535.7734, 101.4844, 0.25);
	RemoveBuildingForPlayer(playerid,  3276, -1471.7031, -1524.7422, 101.4844, 0.25);
	RemoveBuildingForPlayer(playerid,  3276, -1469.2422, -1569.8125, 101.4844, 0.25);
	RemoveBuildingForPlayer(playerid,  3276, -1469.6250, -1558.2578, 101.4844, 0.25);
	RemoveBuildingForPlayer(playerid,  3276, -1470.0000, -1546.9766, 101.4844, 0.25);
	RemoveBuildingForPlayer(playerid,  3276, -1411.1641, -1561.1016, 101.4844, 0.25);
	RemoveBuildingForPlayer(playerid,  3276, -1414.6016, -1572.0938, 101.4844, 0.25);
	RemoveBuildingForPlayer(playerid,  3276, -1403.1719, -1528.8359, 101.4844, 0.25);
	RemoveBuildingForPlayer(playerid,  3276, -1402.6719, -1540.2031, 101.4844, 0.25);
	RemoveBuildingForPlayer(playerid,  3276, -1406.4219, -1550.8438, 101.4844, 0.25);
	RemoveBuildingForPlayer(playerid,  3276, -1405.3828, -1517.0469, 101.4844, 0.25);
	RemoveBuildingForPlayer(playerid,  3276, -1407.5938, -1505.7188, 101.4844, 0.25);
	RemoveBuildingForPlayer(playerid,  3276, -1472.4531, -1513.1563, 101.4844, 0.25);
	RemoveBuildingForPlayer(playerid,  3276, -1409.4922, -1494.2422, 101.4844, 0.25);
	RemoveBuildingForPlayer(playerid,  3276, -1472.0547, -1501.3281, 101.4844, 0.25);
	RemoveBuildingForPlayer(playerid,  3276, -1470.5313, -1489.8906, 101.4844, 0.25);
	RemoveBuildingForPlayer(playerid,  3276, -1411.0078, -1482.7969, 101.4844, 0.25);
	RemoveBuildingForPlayer(playerid,  3276, -1468.2656, -1478.3203, 101.4844, 0.25);
	RemoveBuildingForPlayer(playerid,  3276, -1467.5469, -1467.2422, 101.4844, 0.25);
	RemoveBuildingForPlayer(playerid,  3276, -1468.2188, -1455.6875, 101.4844, 0.25);
	RemoveBuildingForPlayer(playerid,  3276, -1411.9531, -1461.7578, 101.0391, 0.25);
	RemoveBuildingForPlayer(playerid,  17055, -1439.2422, -1446.6563, 102.9297, 0.25);
	RemoveBuildingForPlayer(playerid,  3276, -1412.2656, -1450.2266, 101.0391, 0.25);
	RemoveBuildingForPlayer(playerid,  3276, -1463.4297, -1447.6406, 101.4844, 0.25);
	RemoveBuildingForPlayer(playerid,  3276, -1452.9609, -1443.3516, 101.4844, 0.25);
	RemoveBuildingForPlayer(playerid,  3276, -1441.4609, -1440.7891, 101.4844, 0.25);
	RemoveBuildingForPlayer(playerid,  3276, -1417.9766, -1443.6797, 100.7969, 0.25);
	RemoveBuildingForPlayer(playerid,  3276, -1429.5313, -1441.8203, 101.0391, 0.25);
	RemoveBuildingForPlayer(playerid,  3276, -1399.4063, -1422.2891, 106.1641, 0.25);
	RemoveBuildingForPlayer(playerid,  8229, 1142.0313, 1362.5000, 12.4844, 0.25);
	RemoveBuildingForPlayer(playerid,  735, 1191.0859, 693.9922, 7.9297, 0.25);
	RemoveBuildingForPlayer(playerid, 	615, 1128.3672, 728.2578, 9.8672, 0.25);
	RemoveBuildingForPlayer(playerid,  615, 1148.6172, 728.2578, 9.8672, 0.25);
	RemoveBuildingForPlayer(playerid,  673, 1162.8203, 733.7266, 9.2656, 0.25);
	RemoveBuildingForPlayer(playerid,  615, 1167.6016, 728.2578, 9.8672, 0.25);
	RemoveBuildingForPlayer(playerid,  775, 1199.5156, 733.8672, 9.6641, 0.25);
	RemoveBuildingForPlayer(playerid,  735, 1064.8359, 693.9922, 8.3906, 0.25);
	RemoveBuildingForPlayer(playerid,  735, 1100.1484, 693.9922, 7.9297, 0.25);
	RemoveBuildingForPlayer(playerid,  736, 1042.2969, 751.2656, 20.4063, 0.25);
	RemoveBuildingForPlayer(playerid,  736, 1060.3750, 751.2656, 20.4063, 0.25);
	RemoveBuildingForPlayer(playerid,  736, 1068.4063, 748.7266, 20.9922, 0.25);
	RemoveBuildingForPlayer(playerid,  736, 1069.1953, 761.9063, 20.4063, 0.25);
	RemoveBuildingForPlayer(playerid,  736, 1095.3750, 774.2891, 20.4063, 0.25);
	RemoveBuildingForPlayer(playerid,  3246, -378.8906, -1040.8828, 57.8594, 0.25);
	RemoveBuildingForPlayer(playerid,  3425, -365.8750, -1060.8359, 69.2891, 0.25);
	RemoveBuildingForPlayer(playerid,  3250, -348.6719, -1041.9609, 58.3125, 0.25);
	RemoveBuildingForPlayer(playerid,  727, -343.4219, -1077.3281, 59.1172, 0.25);
	RemoveBuildingForPlayer(playerid,  1447, -89.9297, -1133.7500, 1.3906, 0.25);
	RemoveBuildingForPlayer(playerid,  1438, -87.0547, -1132.6797, 0.0469, 0.25);
	RemoveBuildingForPlayer(playerid,  1462, -84.3750, -1116.0938, 0.2578, 0.25);
	RemoveBuildingForPlayer(playerid,  1447, -84.0547, -1117.2188, 1.3906, 0.25);





	RemoveBuildingForPlayer(playerid, 785, -1629.0781, -2269.7188, 27.5156, 0.25);
	RemoveBuildingForPlayer(playerid, 785, -1585.3984, -2211.6406, 8.1328, 0.25);
	RemoveBuildingForPlayer(playerid, 791, -1629.0781, -2269.7188, 27.5156, 0.25);
	RemoveBuildingForPlayer(playerid, 18258, -1638.3594, -2239.4297, 30.7500, 0.25);
	RemoveBuildingForPlayer(playerid, 18259, -1633.2266, -2238.8359, 30.3906, 0.25);
	RemoveBuildingForPlayer(playerid, 791, -1585.3984, -2211.6406, 8.1328, 0.25);
	RemoveBuildingForPlayer(playerid, 791, -1622.8438, -2211.5938, 21.8750, 0.25);
	RemoveBuildingForPlayer(playerid, 8120, 1610.8594, 902.8750, 13.5547, 0.25);
	RemoveBuildingForPlayer(playerid, 8121, 1737.3281, 905.1172, 13.8203, 0.25);
	RemoveBuildingForPlayer(playerid, 8122, 1727.7031, 950.5391, 13.2109, 0.25);
	RemoveBuildingForPlayer(playerid, 8123, 1668.1484, 1101.7500, 13.8203, 0.25);
	RemoveBuildingForPlayer(playerid, 8156, 1715.5000, 1094.7969, 14.8203, 0.25);
	RemoveBuildingForPlayer(playerid, 8157, 1621.6328, 1094.7969, 14.8203, 0.25);
	RemoveBuildingForPlayer(playerid, 8158, 1727.8047, 1018.6328, 14.8203, 0.25);
	RemoveBuildingForPlayer(playerid, 8162, 1606.6797, 1031.6563, 13.0859, 0.25);
	RemoveBuildingForPlayer(playerid, 8166, 1608.9141, 971.7188, 13.2109, 0.25);
	RemoveBuildingForPlayer(playerid, 8259, 1693.0000, 902.8750, 13.5547, 0.25);
	RemoveBuildingForPlayer(playerid, 1438, 1685.5625, 889.8359, 9.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 1358, 1689.1641, 889.2813, 11.0078, 0.25);
	RemoveBuildingForPlayer(playerid, 1438, 1702.8906, 889.9531, 9.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 1334, 1635.9844, 892.2109, 10.9297, 0.25);
	RemoveBuildingForPlayer(playerid, 8063, 1610.8594, 902.8750, 13.5547, 0.25);
	RemoveBuildingForPlayer(playerid, 1420, 1602.2813, 955.0313, 9.8203, 0.25);
	RemoveBuildingForPlayer(playerid, 8059, 1608.9141, 971.7188, 13.2109, 0.25);
	RemoveBuildingForPlayer(playerid, 1420, 1605.1797, 955.0313, 9.8203, 0.25);
	RemoveBuildingForPlayer(playerid, 8057, 1606.6797, 1031.6563, 13.0859, 0.25);
	RemoveBuildingForPlayer(playerid, 1420, 1618.0469, 1003.1406, 9.8203, 0.25);
	RemoveBuildingForPlayer(playerid, 8294, 1599.9531, 1039.2578, 17.3203, 0.25);
	RemoveBuildingForPlayer(playerid, 1687, 1595.8047, 1052.4609, 17.6016, 0.25);
	RemoveBuildingForPlayer(playerid, 1687, 1595.8047, 1046.4375, 17.6016, 0.25);
	RemoveBuildingForPlayer(playerid, 1334, 1598.6250, 1060.6563, 10.9297, 0.25);
	RemoveBuildingForPlayer(playerid, 1215, 1592.7578, 1074.1250, 10.2891, 0.25);
	RemoveBuildingForPlayer(playerid, 1334, 1603.0078, 1060.6563, 10.9297, 0.25);
	RemoveBuildingForPlayer(playerid, 1215, 1610.8438, 1074.1250, 10.2891, 0.25);
	RemoveBuildingForPlayer(playerid, 1215, 1618.9297, 1074.1250, 10.2891, 0.25);
	RemoveBuildingForPlayer(playerid, 659, 1651.9219, 900.3594, 9.8203, 0.25);
	RemoveBuildingForPlayer(playerid, 676, 1654.5078, 900.3906, 10.1328, 0.25);
	RemoveBuildingForPlayer(playerid, 676, 1649.3281, 900.3906, 10.1328, 0.25);
	RemoveBuildingForPlayer(playerid, 1687, 1630.5938, 909.1953, 17.7188, 0.25);
	RemoveBuildingForPlayer(playerid, 1687, 1624.9219, 909.1953, 17.7188, 0.25);
	RemoveBuildingForPlayer(playerid, 1440, 1667.9375, 907.2500, 10.2109, 0.25);
	RemoveBuildingForPlayer(playerid, 1440, 1666.7734, 905.2344, 10.2109, 0.25);
	RemoveBuildingForPlayer(playerid, 1421, 1668.3438, 899.6875, 10.5000, 0.25);
	RemoveBuildingForPlayer(playerid, 1334, 1668.0547, 911.7969, 10.9297, 0.25);
	RemoveBuildingForPlayer(playerid, 1215, 1669.6875, 915.3906, 10.2578, 0.25);
	RemoveBuildingForPlayer(playerid, 1215, 1676.9375, 915.3906, 10.2578, 0.25);
	RemoveBuildingForPlayer(playerid, 1215, 1685.0078, 915.3906, 10.2578, 0.25);
	RemoveBuildingForPlayer(playerid, 8062, 1693.0000, 902.8750, 13.5547, 0.25);
	RemoveBuildingForPlayer(playerid, 640, 1688.9453, 915.5234, 10.5156, 0.25);
	RemoveBuildingForPlayer(playerid, 1215, 1692.9766, 915.3906, 10.2578, 0.25);
	RemoveBuildingForPlayer(playerid, 1420, 1710.0859, 904.2344, 14.3906, 0.25);
	RemoveBuildingForPlayer(playerid, 1420, 1713.7500, 904.2344, 14.3906, 0.25);
	RemoveBuildingForPlayer(playerid, 1420, 1709.5156, 913.0547, 9.8203, 0.25);
	RemoveBuildingForPlayer(playerid, 1420, 1708.6016, 913.0547, 9.8203, 0.25);
	RemoveBuildingForPlayer(playerid, 1498, 1713.7656, 912.3516, 9.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 1215, 1700.3438, 915.3906, 10.2578, 0.25);
	RemoveBuildingForPlayer(playerid, 1219, 1725.8125, 933.0234, 10.9141, 0.25);
	RemoveBuildingForPlayer(playerid, 1219, 1727.0078, 933.0234, 10.4688, 0.25);
	RemoveBuildingForPlayer(playerid, 1219, 1725.7578, 933.0234, 10.0625, 0.25);
	RemoveBuildingForPlayer(playerid, 1219, 1724.1016, 933.0234, 10.4688, 0.25);
	RemoveBuildingForPlayer(playerid, 1219, 1722.9375, 933.0234, 10.0625, 0.25);
	RemoveBuildingForPlayer(playerid, 1219, 1726.8750, 932.8828, 11.3594, 0.25);
	RemoveBuildingForPlayer(playerid, 1219, 1728.6641, 933.0234, 10.0625, 0.25);
	RemoveBuildingForPlayer(playerid, 1219, 1728.4688, 933.0234, 10.9141, 0.25);
	RemoveBuildingForPlayer(playerid, 1219, 1729.8203, 933.0234, 10.4688, 0.25);
	RemoveBuildingForPlayer(playerid, 1219, 1731.4766, 933.0234, 10.0625, 0.25);
	RemoveBuildingForPlayer(playerid, 1616, 1707.3047, 950.0391, 14.1328, 0.25);
	RemoveBuildingForPlayer(playerid, 1687, 1712.0703, 941.9766, 17.4141, 0.25);
	RemoveBuildingForPlayer(playerid, 8064, 1727.7031, 950.5391, 13.2109, 0.25);
	RemoveBuildingForPlayer(playerid, 1334, 1732.7422, 967.8359, 10.9297, 0.25);
	RemoveBuildingForPlayer(playerid, 1438, 1723.3281, 987.6563, 9.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 1215, 1707.3359, 990.5234, 10.2891, 0.25);
	RemoveBuildingForPlayer(playerid, 8075, 1737.3281, 905.1172, 13.8203, 0.25);
	RemoveBuildingForPlayer(playerid, 1365, 1745.0703, 987.1328, 10.9609, 0.25);
	RemoveBuildingForPlayer(playerid, 1358, 1752.8984, 980.3984, 10.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 1420, 1620.9531, 1003.1406, 9.8203, 0.25);
	RemoveBuildingForPlayer(playerid, 674, 1657.3516, 1013.5313, 9.7656, 0.25);
	RemoveBuildingForPlayer(playerid, 657, 1644.2422, 1013.9531, 9.9688, 0.25);
	RemoveBuildingForPlayer(playerid, 676, 1650.0469, 1013.1250, 10.1406, 0.25);
	RemoveBuildingForPlayer(playerid, 676, 1652.1719, 1013.1250, 10.1406, 0.25);
	RemoveBuildingForPlayer(playerid, 1231, 1652.6406, 1033.9844, 12.5859, 0.25);
	RemoveBuildingForPlayer(playerid, 1684, 1632.3203, 1035.3047, 11.3281, 0.25);
	RemoveBuildingForPlayer(playerid, 1245, 1631.4375, 1045.1328, 11.1719, 0.25);
	RemoveBuildingForPlayer(playerid, 1231, 1661.9922, 1033.9844, 12.5859, 0.25);
	RemoveBuildingForPlayer(playerid, 659, 1667.3203, 1055.7109, 9.8203, 0.25);
	RemoveBuildingForPlayer(playerid, 1231, 1671.3516, 1033.9844, 12.5859, 0.25);
	RemoveBuildingForPlayer(playerid, 1231, 1680.7031, 1033.9844, 12.5859, 0.25);
	RemoveBuildingForPlayer(playerid, 680, 1672.3516, 1055.7344, 9.7969, 0.25);
	RemoveBuildingForPlayer(playerid, 1215, 1632.4688, 1074.1250, 10.2891, 0.25);
	RemoveBuildingForPlayer(playerid, 1215, 1649.9063, 1074.1250, 10.2891, 0.25);
	RemoveBuildingForPlayer(playerid, 1358, 1653.0234, 1076.9688, 11.0078, 0.25);
	RemoveBuildingForPlayer(playerid, 8058, 1621.6328, 1094.7969, 14.8203, 0.25);
	RemoveBuildingForPlayer(playerid, 8076, 1668.1484, 1101.7500, 13.8203, 0.25);
	RemoveBuildingForPlayer(playerid, 998, 1677.4609, 1079.3906, 10.6094, 0.25);
	RemoveBuildingForPlayer(playerid, 998, 1677.4609, 1069.0938, 10.6094, 0.25);
	RemoveBuildingForPlayer(playerid, 998, 1677.4609, 1110.2813, 10.6094, 0.25);
	RemoveBuildingForPlayer(playerid, 998, 1677.4609, 1099.9844, 10.6094, 0.25);
	RemoveBuildingForPlayer(playerid, 998, 1677.4609, 1089.6875, 10.6094, 0.25);
	RemoveBuildingForPlayer(playerid, 1219, 1684.1016, 1084.9531, 10.0625, 0.25);
	RemoveBuildingForPlayer(playerid, 1219, 1684.1016, 1086.6094, 10.4688, 0.25);
	RemoveBuildingForPlayer(playerid, 1219, 1684.1016, 1087.8594, 10.0625, 0.25);
	RemoveBuildingForPlayer(playerid, 1219, 1684.1016, 1085.1484, 10.9141, 0.25);
	RemoveBuildingForPlayer(playerid, 1219, 1684.1016, 1087.7969, 10.9141, 0.25);
	RemoveBuildingForPlayer(playerid, 1219, 1684.1016, 1083.7891, 10.4688, 0.25);
	RemoveBuildingForPlayer(playerid, 1219, 1684.1016, 1089.5156, 10.4688, 0.25);
	RemoveBuildingForPlayer(playerid, 1219, 1684.1016, 1090.6797, 10.0625, 0.25);
	RemoveBuildingForPlayer(playerid, 1219, 1684.1016, 1082.1328, 10.0625, 0.25);
	RemoveBuildingForPlayer(playerid, 998, 1682.9219, 1063.2891, 10.6094, 0.25);
	RemoveBuildingForPlayer(playerid, 1358, 1683.8828, 1112.9844, 10.9453, 0.25);
	RemoveBuildingForPlayer(playerid, 998, 1693.2188, 1063.2891, 10.6094, 0.25);
	RemoveBuildingForPlayer(playerid, 1215, 1686.5078, 1074.1250, 10.2891, 0.25);
	RemoveBuildingForPlayer(playerid, 1438, 1706.7344, 1005.3125, 9.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 1215, 1707.3359, 1007.8203, 10.2891, 0.25);
	RemoveBuildingForPlayer(playerid, 8061, 1727.8047, 1018.6328, 14.8203, 0.25);
	RemoveBuildingForPlayer(playerid, 1215, 1707.3359, 1021.3828, 10.2891, 0.25);
	RemoveBuildingForPlayer(playerid, 1215, 1707.3359, 1047.5938, 10.2891, 0.25);
	RemoveBuildingForPlayer(playerid, 1215, 1707.3359, 1029.4063, 10.2891, 0.25);
	RemoveBuildingForPlayer(playerid, 1616, 1708.0234, 1049.0469, 16.0781, 0.25);
	RemoveBuildingForPlayer(playerid, 998, 1713.8047, 1063.2891, 10.6094, 0.25);
	RemoveBuildingForPlayer(playerid, 998, 1703.5078, 1063.2891, 10.6094, 0.25);
	RemoveBuildingForPlayer(playerid, 8060, 1715.5000, 1094.7969, 14.8203, 0.25);
	RemoveBuildingForPlayer(playerid, 1215, 1704.5859, 1074.1250, 10.2891, 0.25);
	RemoveBuildingForPlayer(playerid, 1215, 1712.6797, 1074.1250, 10.2891, 0.25);
	RemoveBuildingForPlayer(playerid, 1219, 1719.7891, 1050.0156, 10.0625, 0.25);
	RemoveBuildingForPlayer(playerid, 1219, 1718.1328, 1050.0156, 10.4688, 0.25);
	RemoveBuildingForPlayer(playerid, 1219, 1716.8828, 1050.0156, 10.0625, 0.25);
	RemoveBuildingForPlayer(playerid, 1219, 1719.5938, 1050.0156, 10.9141, 0.25);
	RemoveBuildingForPlayer(playerid, 1219, 1720.9453, 1050.0156, 10.4688, 0.25);
	RemoveBuildingForPlayer(playerid, 1219, 1722.6016, 1050.0156, 10.0625, 0.25);
	RemoveBuildingForPlayer(playerid, 998, 1724.1016, 1063.2891, 10.6094, 0.25);
	RemoveBuildingForPlayer(playerid, 1215, 1726.4609, 1074.1250, 10.2891, 0.25);
	RemoveBuildingForPlayer(playerid, 1334, 1745.3594, 1049.3906, 10.9297, 0.25);
	RemoveBuildingForPlayer(playerid, 1219, 1740.2344, 1050.0156, 10.0625, 0.25);
	RemoveBuildingForPlayer(playerid, 1219, 1738.5781, 1050.0156, 10.4688, 0.25);
	RemoveBuildingForPlayer(playerid, 1219, 1737.3281, 1050.0156, 10.0625, 0.25);
	RemoveBuildingForPlayer(playerid, 1219, 1740.0391, 1050.0156, 10.9141, 0.25);
	RemoveBuildingForPlayer(playerid, 1219, 1741.3906, 1050.0156, 10.4688, 0.25);
	RemoveBuildingForPlayer(playerid, 1219, 1743.0469, 1050.0156, 10.0625, 0.25);
	RemoveBuildingForPlayer(playerid, 998, 1744.6953, 1063.2891, 10.6094, 0.25);
	RemoveBuildingForPlayer(playerid, 998, 1734.3984, 1063.2891, 10.6094, 0.25);
	RemoveBuildingForPlayer(playerid, 1616, 1745.1094, 1074.3984, 16.0781, 0.25);
	RemoveBuildingForPlayer(playerid, 1215, 1743.6719, 1074.1250, 10.2891, 0.25);
	RemoveBuildingForPlayer(playerid, 1503, 1584.1875, 1115.3516, 10.2109, 0.25);

	RemoveBuildingForPlayer(playerid, 18499, -1849.5156, -1701.1563, 32.9531, 0.25);
	RemoveBuildingForPlayer(playerid, 18555, -1813.8047, -1615.5625, 29.8516, 0.25);
	RemoveBuildingForPlayer(playerid, 18556, -1907.6172, -1666.6797, 29.8516, 0.25);
	RemoveBuildingForPlayer(playerid, 18557, -1857.2969, -1617.9766, 26.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 18560, -1874.3438, -1680.9531, 25.4375, 0.25);
	RemoveBuildingForPlayer(playerid, 18255, -1939.9141, -1731.4844, 24.9453, 0.25);
	RemoveBuildingForPlayer(playerid, 18251, -1907.6172, -1666.6797, 29.8516, 0.25);
	RemoveBuildingForPlayer(playerid, 18252, -1888.9766, -1633.2734, 24.4844, 0.25);
	RemoveBuildingForPlayer(playerid, 18253, -1888.8047, -1604.1328, 23.3750, 0.25);
	RemoveBuildingForPlayer(playerid, 18247, -1874.3438, -1680.9531, 25.4375, 0.25);
	RemoveBuildingForPlayer(playerid, 18245, -1849.5156, -1701.1563, 32.9531, 0.25);
	RemoveBuildingForPlayer(playerid, 18248, -1852.2578, -1676.2188, 28.6172, 0.25);
	RemoveBuildingForPlayer(playerid, 18249, -1818.8125, -1675.5391, 27.0703, 0.25);
	RemoveBuildingForPlayer(playerid, 18246, -1857.8359, -1573.3750, 23.3125, 0.25);
	RemoveBuildingForPlayer(playerid, 18250, -1857.2969, -1617.9766, 26.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 18254, -1813.8047, -1615.5625, 29.8516, 0.25);
	RemoveBuildingForPlayer(playerid, 18608, -1818.4531, -1613.0391, 32.7891, 0.25);

	RemoveBuildingForPlayer(playerid, 7693, 1517.3906, 2343.2813, 9.8203, 0.25);
	RemoveBuildingForPlayer(playerid, 1413, 1400.4922, 2323.0703, 11.0938, 0.25);
	RemoveBuildingForPlayer(playerid, 1412, 1405.7656, 2323.0781, 11.0938, 0.25);
	RemoveBuildingForPlayer(playerid, 1412, 1411.0391, 2323.0781, 11.0938, 0.25);
	RemoveBuildingForPlayer(playerid, 1412, 1421.5938, 2323.0781, 11.0938, 0.25);
	RemoveBuildingForPlayer(playerid, 1412, 1416.3203, 2323.0781, 11.0938, 0.25);
	RemoveBuildingForPlayer(playerid, 1413, 1426.8750, 2323.0703, 11.0938, 0.25);
	RemoveBuildingForPlayer(playerid, 3474, 1425.1328, 2334.2813, 16.7422, 0.25);
	RemoveBuildingForPlayer(playerid, 1412, 1447.9766, 2323.0781, 11.0938, 0.25);
	RemoveBuildingForPlayer(playerid, 1412, 1442.6953, 2323.0781, 11.0938, 0.25);
	RemoveBuildingForPlayer(playerid, 1412, 1437.4219, 2323.0781, 11.0938, 0.25);
	RemoveBuildingForPlayer(playerid, 1412, 1432.1484, 2323.0781, 11.0938, 0.25);
	RemoveBuildingForPlayer(playerid, 1412, 1469.0781, 2323.0781, 11.0938, 0.25);
	RemoveBuildingForPlayer(playerid, 1412, 1463.8047, 2323.0781, 11.0938, 0.25);
	RemoveBuildingForPlayer(playerid, 1412, 1458.5234, 2323.0781, 11.0938, 0.25);
	RemoveBuildingForPlayer(playerid, 1413, 1453.2500, 2323.0703, 11.0938, 0.25);
	RemoveBuildingForPlayer(playerid, 3460, 1482.7500, 2388.8438, 13.7656, 0.25);
	RemoveBuildingForPlayer(playerid, 7513, 1517.3906, 2343.2813, 9.8203, 0.25);
	XDeaths[playerid] = 0;
	LastDeath[playerid] = 0;
	return 1;
}
// This function shows the player how long his ban still is when he tries to login (in days, hours, minutes, seconds)
ShowRemainingBanTime(playerid)
{
	// Setup local variables
	new TotalBanTime, Days, Hours, Minutes, Seconds, Msg[128];

	// Get the total ban-time
	TotalBanTime = APlayerData[playerid][BanTime] - gettime();

	// Calculate days
	if (TotalBanTime >= 86400)
	{
		Days = TotalBanTime / 86400;
		TotalBanTime = TotalBanTime - (Days * 86400);
	}
	// Calculate hours
	if (TotalBanTime >= 3600)
	{
		Hours = TotalBanTime / 3600;
		TotalBanTime = TotalBanTime - (Hours * 3600);
	}
	// Calculate minutes
	if (TotalBanTime >= 60)
	{
		Minutes = TotalBanTime / 60;
		TotalBanTime = TotalBanTime - (Minutes * 60);
	}
	// Calculate seconds
	Seconds = TotalBanTime;

	// Display the remaining ban-time for this player
	SendClientMessage(playerid, 0xFFFFFFFF, TXT_StillBanned);
	format(Msg, 128, TXT_BannedDuration, Days, Hours, Minutes, Seconds);
	SendClientMessage(playerid, 0xFFFFFFFF, Msg);
}
// This callback gets called when a player disconnects from the server
public OnPlayerDisconnect(playerid, reason)
{
	// Always allow NPC's to logout without password or account
	if (IsPlayerNPC(playerid))
		return 1;

	// Setup local variables
	new Name[24], Msg[128], HouseID;

	// Get the playername
	GetPlayerName(playerid, Name, sizeof(Name));

	// Stop spectate mode for all players who are spectating this player
	for (new i; i < MAX_PLAYERS; i++)
	    if (IsPlayerConnected(i)) // Check if the player is connected
	        if (GetPlayerState(i) == PLAYER_STATE_SPECTATING) // Check if this player is spectating somebody
	            if (APlayerData[i][SpectateID] == playerid) // Check if this player is spectating me
		   		{
					TogglePlayerSpectating(i, 0); // Turn off spectate-mode
					APlayerData[i][SpectateID] = INVALID_PLAYER_ID;
					APlayerData[i][SpectateType] = ADMIN_SPEC_TYPE_NONE;
					SendClientMessage(i, 0xFFFFFFFF, "{FF0000}Target player has logged off, ending spectate mode");
				}

	// Send a message to all players to let them know somebody left the server
	format(Msg, 128, TXT_PlayerLeftServer, Name, playerid);
	SendClientMessageToAll(0xFFFFFFFF, Msg);

	// If the player entered a proper password (the player has an account)
	if (strlen(APlayerData[playerid][PlayerPassword]) != 0)
	{
	    // Save the player data and his houses
		PlayerFile_Save(playerid);
	}

	// Stop any job that may have started (this also clears all mission data)
	switch (APlayerData[playerid][PlayerClass])
	{
		case ClassTruckDriver: Trucker_EndJob(playerid); // Stop any trucker job
		case ClassBusDriver: BusDriver_EndJob(playerid); // Stop any busdriver job
		case ClassPilot: Pilot_EndJob(playerid); // Stop any pilot job
		case ClassPolice: Police_EndJob(playerid); // Stop any police job
		case ClassFBY: FBY_EndJob(playerid); // Stop any FBY job
		case ClassMafia: Mafia_EndJob(playerid); // Stop any mafia job
		case ClassAssistance: Assistance_EndJob(playerid);
		case ClassRoadWorker: Roadworker_EndJob(playerid);
		case ClassMedic: Medic_EndJob(playerid); // Stop any Medic job
		case ClassSofer: Sofer_EndJob(playerid); // Stop any Sofer job
		case ClassMarinar: Marinar_EndJob(playerid); // Stop any Marinar job
		case ClassTaxi: Taxi_EndJob(playerid); // Stop any Taxi job
		case ClassPadurar: Padurar_EndJob(playerid); // Stop any Padurar job
		case ClassG: G_EndJob(playerid); // Stop any G job
	}

	// If the player is part of a convoy, kick him from it
	Convoy_Leave(playerid);

	// Unload all the player's house-vehicles to make room for other player's vehicles
	for (new HouseSlot; HouseSlot < MAX_HOUSESPERPLAYER; HouseSlot++)
	{
	    // Get the HouseID from this slot
	    HouseID = APlayerData[playerid][Houses][HouseSlot];
	    // Check if there is a house in this slot
		if (HouseID != 0)
		{
		    // Unload the cars of the house
		    House_RemoveVehicles(HouseID);
			// Set the house so it cannot be entered by anyone (close the house)
			AHouseData[HouseID][HouseOpened] = false;
		}
	}

	// Clear the data in the APlayerData array to make sure the next player with the same id doesn't hold wrong data
	APlayerData[playerid][SpectateID] = -1;
	APlayerData[playerid][SpectateVehicle] = -1;
	APlayerData[playerid][SpectateType] = ADMIN_SPEC_TYPE_NONE;
	APlayerData[playerid][LoggedIn] = false;
	APlayerData[playerid][AssistanceNeeded] = false;
	APlayerData[playerid][PlayerPassword] = 0;
	APlayerData[playerid][PlayerLevel] = 0;
	APlayerData[playerid][VPlayerLevel] = 0;
	APlayerData[playerid][PlayerJailed] = 0;
	APlayerData[playerid][PlayerFrozen] = 0; // Clearing this variable automatically kills the frozentimer
	APlayerData[playerid][Bans] = 0;
	APlayerData[playerid][BanTime] = 0;
	APlayerData[playerid][Muted] = false;
	APlayerData[playerid][RulesRead] = false;
	APlayerData[playerid][AutoReportTime] = 0;
	APlayerData[playerid][TruckerLicense] = 0;
	APlayerData[playerid][SoferLicense] = 0;
	APlayerData[playerid][MarinarLicense] = 0;
	APlayerData[playerid][TaxiLicense] = 0;
	APlayerData[playerid][PadurarLicense] = 0;
	APlayerData[playerid][BusLicense] = 0;
	APlayerData[playerid][PlayerClass] = 0;
	APlayerData[playerid][Warnings] = 0;
	APlayerData[playerid][PlayerMoney] = 0;
	APlayerData[playerid][PlayerScore] = 0;
	for (new HouseSlot; HouseSlot < MAX_HOUSESPERPLAYER; HouseSlot++)
	APlayerData[playerid][Houses][HouseSlot] = 0;
	for (new BusSlot; BusSlot < MAX_BUSINESSPERPLAYER; BusSlot++)
	APlayerData[playerid][Business][BusSlot] = 0;
	APlayerData[playerid][CurrentHouse] = 0;

	// Clear bank account info
	APlayerData[playerid][BankPassword] = 0;
	APlayerData[playerid][BankLoggedIn] = false;
	APlayerData[playerid][BankMoney] = 0;

	// Clear stats
	APlayerData[playerid][StatsTruckerJobs] = 0;
	APlayerData[playerid][StatsConvoyJobs] = 0;
	APlayerData[playerid][StatsBusDriverJobs] = 0;
	APlayerData[playerid][StatsPilotJobs] = 0;
	APlayerData[playerid][StatsSoferJobs] = 0;
	APlayerData[playerid][StatsMarinarJobs] = 0;
	APlayerData[playerid][StatsTaxiJobs] = 0;
	APlayerData[playerid][StatsPadurarJobs] = 0;
	APlayerData[playerid][StatsGJobs] = 0;
	APlayerData[playerid][StatsMedicJobs] = 0;
	APlayerData[playerid][StatsMafiaJobs] = 0;
	APlayerData[playerid][StatsMafiaStolen] = 0;
	APlayerData[playerid][StatsPoliceFined] = 0;
	APlayerData[playerid][StatsFBYFined] = 0;
	APlayerData[playerid][StatsPoliceJailed] = 0;
	APlayerData[playerid][StatsFBYJailed] = 0;
	APlayerData[playerid][StatsCourierJobs] = 0;
	APlayerData[playerid][StatsPboyJobs] = 0;
	APlayerData[playerid][StatsRoadworkerJobs] = 0;
	APlayerData[playerid][StatsAssistance] = 0;
	APlayerData[playerid][StatsMetersDriven] = 0.0;

	// Clear police warnings
	APlayerData[playerid][PoliceCanJailMe] = false;
	APlayerData[playerid][PoliceWarnedMe] = false;
	APlayerData[playerid][Value_PoliceCanJailMe] = 0;
	
	APlayerData[playerid][FBYCanJailMe] = false;
	APlayerData[playerid][FBYWarnedMe] = false;
	APlayerData[playerid][Value_FBYCanJailMe] = 0;

	// Make sure the jailtimer has been destroyed
	KillTimer(APlayerData[playerid][PlayerJailedTimer]);
	KillTimer(APlayerData[playerid][Timer_PoliceCanJailMe]);
	KillTimer(APlayerData[playerid][Timer_FBYCanJailMe]);

	// Destroy the speedometer TextDraw for this player and the timer, also set the speed to 0
	Speedometer_Cleanup(playerid);

	// Also destroy the missiontext TextDraw for this player
	TextDrawDestroy(APlayerData[playerid][MissionText]);

	// Destroy a rented vehicle is the player had any
	if (APlayerData[playerid][RentedVehicleID] != 0)
	{
		// Clear the data for the already rented vehicle
		AVehicleData[APlayerData[playerid][RentedVehicleID]][Model] = 0;
		AVehicleData[APlayerData[playerid][RentedVehicleID]][Fuel] = 0;
		AVehicleData[APlayerData[playerid][RentedVehicleID]][Owned] = false;
		AVehicleData[APlayerData[playerid][RentedVehicleID]][Owner] = 0;
		AVehicleData[APlayerData[playerid][RentedVehicleID]][PaintJob] = 0;
		for (new j; j < 14; j++)
		{
			AVehicleData[APlayerData[playerid][RentedVehicleID]][Components][j] = 0;
		}
		// Destroy the vehicle
		DestroyVehicle(APlayerData[playerid][RentedVehicleID]);
		// Clear the RentedVehicleID
		APlayerData[playerid][RentedVehicleID] = 0;
	}

	return 1;
}
// This callback gets called whenever a player uses the chat-box
public OnPlayerText(playerid, text[])
{
	// Block the player's text if he has been muted
    if (APlayerData[playerid][Muted] == true || APlayerData[playerid][LoggedIn] == false)
	{
		// Let the player know he's still muted
		SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}Inca esti mut");

		// Don't allow his text to be sent to the chatbox
		return 0;
	}
	if(stringContainsIP(text))
	{
    new
        szMsg[128]
    ;
    GetPlayerName(playerid, szMsg, MAX_PLAYER_NAME);

    format(szMsg, sizeof(szMsg), "ATENTIE! %s Incearca sa faca Reclama!", szMsg);
    SendClientMessageToAll(0xFF0000FF, szMsg);
    Kick(playerid);

    return 0;
	}
  	//return 1;
	new msg[128]; // The string. We do not need to have it larger than 128, because a message can't be larger than that.
    if(IsPlayerAdmin(playerid))
    {
          format(msg, sizeof(msg),"{FF80FF}(id:%d):{00FFFF}%s", playerid, text);
    }
    else
    if (APlayerData[playerid][PlayerLevel] >= 1)
    {
	      format(msg, sizeof(msg),"{FFFF00}(id:%d):{00FF00}%s", playerid, text);
	}
	else
	if (APlayerData[playerid][VPlayerLevel] >= 1)
    {
	      format(msg, sizeof(msg),"{FFFF00}(id:%d):{FFFF80}%s", playerid, text);
	}
	else
 	format(msg, sizeof(msg),"{FFFF00}(id:%d):{FFFFFF}%s", playerid, text); // The formatted message. Remember, %d means integer (whole number) and %s is string - they are associated with playerid, respectively text.
    SendPlayerMessageToAll(playerid, msg); // SendPlayerMessageToAll will send a message from the player to everyone, like what would happen normally when a player chats, but with the message we choose.
    return 0;
}
// This callback gets called when a player interacts with a dialog
public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	// Select the proper dialog to process
	switch (dialogid)
	{
		case DialogRegister: Dialog_Register(playerid, response, inputtext); // The "Register"-dialog
		case DialogLogin: Dialog_Login(playerid, response, inputtext); // The "Login"-dialog
		case DialogStatsOtherPlayer: Dialog_StatsOtherPlayer(playerid, response, listitem);
		case DialogStatsHouse: Dialog_StatsHouse(playerid, response, listitem);
		case DialogStatsGoHouse: Dialog_StatsGoHouse(playerid, response, listitem);
		case DialogStatsGoBusiness: Dialog_StatsGoBusiness(playerid, response, listitem);
		case DialogRescue: Dialog_Rescue(playerid, response, listitem); // The rescue-dialog
		case DialogBuyLicenses: Dialog_BuyLicenses(playerid, response, listitem); // The license-dialog (allows the player to buy trucker/busdriver licenses)
		case DialogRules: Dialog_Rules(playerid, response);
		case DialogComezile1: Dialog_Comezile1(playerid, response);
		case DialogComezile2: Dialog_Comezile2(playerid, response);
		case DialogTruckerJobMethod: Dialog_TruckerSelectJobMethod(playerid, response, listitem); // The work-dialog for truckers (shows the loads he can carry and lets the player choose the load)
		case DialogTruckerSelectLoad: Dialog_TruckerSelectLoad(playerid, response, listitem); // The load-selection dialog for truckers (shows the startlocations for the selected load and let the player choose his startlocation)
		case DialogTruckerStartLoc: Dialog_TruckerSelectStartLoc(playerid, response, listitem); // The start-location dialog for truckers (shows the endlocations for the selected load and let the player choose his endlocation)
		case DialogTruckerEndLoc: Dialog_TruckerSelectEndLoc(playerid, response, listitem); // The end-location dialog for truckers (processes the selected endlocation and starts the job)

		//Conducator tren licenta
		case DialogSoferJobMethod: Dialog_SoferSelectJobMethod(playerid, response, listitem); // 
		case DialogSoferSelectLoad: Dialog_SoferSelectLoad(playerid, response, listitem); // 
		case DialogSoferStartLoc: Dialog_SoferSelectStartLoc(playerid, response, listitem); //
		case DialogSoferEndLoc: Dialog_SoferSelectEndLoc(playerid, response, listitem); //
		
		//Marinar Licenta
		case DialogMarinarJobMethod: Dialog_MarinarSelectJobMethod(playerid, response, listitem); //
		case DialogMarinarSelectLoad: Dialog_MarinarSelectLoad(playerid, response, listitem); //
		case DialogMarinarStartLoc: Dialog_MarinarSelectStartLoc(playerid, response, listitem); //
		case DialogMarinarEndLoc: Dialog_MarinarSelectEndLoc(playerid, response, listitem); //

		//Taxi Licenta
		case DialogTaxiJobMethod: Dialog_TaxiSelectJobMethod(playerid, response, listitem); //
		case DialogTaxiSelectLoad: Dialog_TaxiSelectLoad(playerid, response, listitem); //
		case DialogTaxiStartLoc: Dialog_TaxiSelectStartLoc(playerid, response, listitem); //
		case DialogTaxiEndLoc: Dialog_TaxiSelectEndLoc(playerid, response, listitem); //
		
		
		
		//Padurar Licenta
		case DialogPadurarJobMethod: Dialog_PadurarSelectJobMethod(playerid, response, listitem); //Padurar
		case DialogPadurarSelectLoad: Dialog_PadurarSelectLoad(playerid, response, listitem); //Padurar
		case DialogPadurarStartLoc: Dialog_PadurarSelectStartLoc(playerid, response, listitem); //Padurar
		case DialogPadurarEndLoc: Dialog_PadurarSelectEndLoc(playerid, response, listitem); //Padurar

	
		case DialogBusJobMethod: Dialog_BusSelectJobMethod(playerid, response, listitem); // The work-dialog for busdrivers (process the options to choose own busroute or auto-assigned busroute)
		case DialogBusSelectRoute: Dialog_BusSelectRoute(playerid, response, listitem); // Choose the busroute and start the job

		case DialogCourierSelectQuant: Dialog_CourierSelectQuant(playerid, response, listitem);
		case DialogPboySelectQuant: Dialog_PboySelectQuant(playerid, response, listitem);

		case DialogBike: Dialog_Bike(playerid, response, listitem); // The bike-dialog
		case DialogCar: Dialog_Car(playerid, response, listitem); // The car-dialog (which uses a split dialog structure)
		case DialogPlane: Dialog_Plane(playerid, response, listitem); // The plane-dialog (which uses a split dialog structure)
		case DialogTrailer: Dialog_Trailer(playerid, response, listitem); // The trailer-dialog (which uses a split dialog structure)
		case DialogBoat: Dialog_Boat(playerid, response, listitem); // The boat-dialog
		case DialogNeon: Dialog_Neon(playerid, response, listitem); // The neon-dialog

		case DialogRentCarClass: Dialog_RentProcessClass(playerid, response, listitem); // The player chose a vehicleclass from where he can rent a vehicle
		case DialogRentCar: Dialog_RentCar(playerid, response, listitem); // The player chose a vehicle from the list of vehicles from the vehicleclass he chose before

		case DialogPrimaryCarColor: Dialog_PrimaryCarColor(playerid, response, listitem);
		case DialogSedundaryCarColor: Dialog_SedundaryCarColor(playerid, response, listitem);

		case DialogWeather: Dialog_Weather(playerid, response, listitem); // The weather dialog
		case DialogCarOption: Dialog_CarOption(playerid, response, listitem); // The caroption dialog

		case DialogSelectConvoy: Dialog_SelectConvoy(playerid, response, listitem);

		case DialogHouseMenu: Dialog_HouseMenu(playerid, response, listitem); // Process the main housemenu
		case DialogUpgradeHouse: Dialog_UpgradeHouse(playerid, response, listitem); // Process the house-upgrade menu
		case DialogGoHome: Dialog_GoHome(playerid, response, listitem); // Port to one of your houses
		case DialogHouseNameChange: Dialog_ChangeHouseName(playerid, response, inputtext); // Change the name of your house
		case DialogSellHouse: Dialog_SellHouse(playerid, response); // Sell the house
		case DialogBuyCarClass: Dialog_BuyCarClass(playerid, response, listitem); // The player chose a vehicleclass from where he can buy a vehicle
		case DialogBuyCar: Dialog_BuyCar(playerid, response, listitem); // The player chose a vehicle from the list of vehicles from the vehicleclass he chose before
		case DialogSellCar: Dialog_SellCar(playerid, response, listitem);
		case DialogBuyInsurance: Dialog_BuyInsurance(playerid, response);
		case DialogGetCarSelectHouse: Dialog_GetCarSelectHouse(playerid, response, listitem);
		case DialogGetCarSelectCar: Dialog_GetCarSelectCar(playerid, response, listitem);
		case DialogUnclampVehicles: Dialog_UnclampVehicles(playerid, response);

		case DialogCreateBusSelType: Dialog_CreateBusSelType(playerid, response, listitem);
		case DialogBusinessMenu: Dialog_BusinessMenu(playerid, response, listitem);
		case DialogGoBusiness: Dialog_GoBusiness(playerid, response, listitem);
		case DialogBusinessNameChange: Dialog_ChangeBusinessName(playerid, response, inputtext); // Change the name of your business
		case DialogSellBusiness: Dialog_SellBusiness(playerid, response); // Sell the business

		case DialogBankPasswordRegister: Dialog_BankPasswordRegister(playerid, response, inputtext);
		case DialogBankPasswordLogin: Dialog_BankPasswordLogin(playerid, response, inputtext);
		case DialogBankOptions: Dialog_BankOptions(playerid, response, listitem);
		case DialogBankDeposit: Dialog_BankDeposit(playerid, response, inputtext);
		case DialogBankWithdraw: Dialog_BankWithdraw(playerid, response, inputtext);
		case DialogBankTransferMoney: Dialog_BankTransferMoney(playerid, response, inputtext);
		case DialogBankTransferName: Dialog_BankTransferName(playerid, response, inputtext);
		case DialogBankCancel: Dialog_BankCancel(playerid, response);

		case DialogHelpItemChosen: Dialog_HelpItemChosen(playerid, response, listitem);
		case DialogHelpItem: Dialog_HelpItem(playerid, response);

		case DialogOldPassword: Dialog_OldPassword(playerid, response, inputtext);
		case DialogNewPassword: Dialog_NewPassword(playerid, response, inputtext);
		case DialogConfirmPassword: Dialog_ConfirmPassword(playerid, response);
		
	}
    if(dialogid == DialogWEAPONS) {
        if(response) {
            if(listitem == 0) {
                RewardPlayer(playerid, -10000, 0);
    			GivePlayerWeapon(playerid, 22, 500);
    			SendClientMessage(playerid, COLOR_GREEN, "*Ai cumparat 9mm with 500 Ammo!*");
            }
            if(listitem == 1) {
                RewardPlayer(playerid, -12000, 0);
			 	GivePlayerWeapon(playerid, 23, 500);
 			 	SendClientMessage(playerid, COLOR_GREEN, "*Ai cumparat Silenced 9mm with 500 Ammo!*");
            }
            if(listitem == 2) {
                RewardPlayer(playerid, -50000, 0);
    			GivePlayerWeapon(playerid, 24, 500);
    			SendClientMessage(playerid, COLOR_GREEN, "*Ai cumparat Desert Deagle with 500 Ammo!*");
            }
            if(listitem == 3) {
                RewardPlayer(playerid, -300000, 0);
    			GivePlayerWeapon(playerid, 25, 550);
    			SendClientMessage(playerid, COLOR_GREEN, "*Ai cumparat Shotgun with 550 Ammo!*");
            }
            if(listitem == 4) {
                RewardPlayer(playerid, -120000, 0);
    			GivePlayerWeapon(playerid, 26, 550);
    			SendClientMessage(playerid, COLOR_GREEN, "*Ai cumparat Sawnoff Shotgun with 550 Ammo!*");
            }
            if(listitem == 5) {
                RewardPlayer(playerid, -140000, 0);
    			GivePlayerWeapon(playerid, 27, 550);
    			SendClientMessage(playerid, COLOR_GREEN, "*Ai cumparat Combat Shotgun with 550 Ammo!*");
            }
            if(listitem == 6) {
            	RewardPlayer(playerid, -160000, 0);
   				GivePlayerWeapon(playerid, 28, 750);
    			SendClientMessage(playerid, COLOR_GREEN, "*Ai cumparat Micro SMG/Uzi with 750 Ammo!*");
            }
            if(listitem == 7) {
       	    	RewardPlayer(playerid, -180000, 0);
    			GivePlayerWeapon(playerid, 32, 750);
    			SendClientMessage(playerid, COLOR_GREEN, "*Ai cumparat Tec-9 with 750 Ammo!*");
            }
            if(listitem == 8) {
       	    	RewardPlayer(playerid, -200000, 0);
    			GivePlayerWeapon(playerid, 29, 750);
    			SendClientMessage(playerid, COLOR_GREEN, "*Ai cumparat MP5 with 750 Ammo!*");
            }
            if(listitem == 9) {
    	 		RewardPlayer(playerid, -230000, 0);
    			GivePlayerWeapon(playerid, 30, 750);
    			SendClientMessage(playerid, COLOR_GREEN, "*Ai cumparat AK-47 with 750 Ammo!*");
            }
            if(listitem == 10) {
    	 		RewardPlayer(playerid, -260000, 0);
    			GivePlayerWeapon(playerid, 31, 750);
    			SendClientMessage(playerid, COLOR_GREEN, "*Ai cumparat M4 with 750 Ammo!*");
            }
            if(listitem == 11) {
  	 		 	RewardPlayer(playerid, -280000, 0);
    			GivePlayerWeapon(playerid, 34, 50);
    			SendClientMessage(playerid, COLOR_GREEN, "*Ai cumparat Sniper Rifle with 50 Ammo!*");
            }
            if(listitem == 12) {
 		 	 	RewardPlayer(playerid, -10000, 0);
    			GivePlayerWeapon(playerid, 46, 1);
    			SendClientMessage(playerid, COLOR_GREEN, "*Ai cumparat Parachute!*");
            }
        }
    }
    return 1;
}

// this callback gets called when a player clicks on another player on the scoreboard
public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
	if (APlayerData[playerid][PlayerLevel] >= 1)
	{
		new Name[24], DialogTitle[128], PlayerStatList[3000], PlayerIP[16], NumHouses, NumBusinesses;
		GetPlayerName(clickedplayerid, Name, sizeof(Name));
		format(DialogTitle, 128, "Statistics of player: %s", Name);
	    GetPlayerIp(clickedplayerid, PlayerIP, sizeof(PlayerIP));
		format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}IP Jucator: {00FF00}%s\n", PlayerStatList, PlayerIP);
		format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Nivel admin: {FF0000}%i\n", PlayerStatList, APlayerData[clickedplayerid][PlayerLevel]);
		format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Nivel VIP: {00FF00}%i\n", PlayerStatList, APlayerData[clickedplayerid][VPlayerLevel]);
		switch(APlayerData[clickedplayerid][PlayerClass])
		{
			case ClassTruckDriver: format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Clasa: {00FF00}Camionagiu\n", PlayerStatList);
			case ClassBusDriver: format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Clasa: {00FF00}Sofer de Autobuz\n", PlayerStatList);
			case ClassPilot: format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Clasa: {00FF00}Pilot\n", PlayerStatList);
			case ClassSofer: format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Clasa: {00FF00}Conducator de Tren\n", PlayerStatList);
			case ClassG: format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Clasa: {00FF00}Gunoier\n", PlayerStatList);
			case ClassMarinar: format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Clasa: {00FF00}Marinar\n", PlayerStatList);
			case ClassTaxi: format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Clasa: {00FF00}Taximetrist\n", PlayerStatList);
			case ClassPadurar: format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Clasa: {00FF00}Padurar\n", PlayerStatList);
			case ClassPolice: format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Clasa: {00FF00}Politist\n", PlayerStatList);
			case ClassFBY: format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Clasa: {00FF00}FBI\n", PlayerStatList);
			case ClassMafia: format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Clasa: {00FF00}Mafia\n", PlayerStatList);
			case ClassCourier: format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Clasa: {00FF00}Curier\n", PlayerStatList);
			case ClassPboy: format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Clasa: {00FF00}Baiat cu Pizza\n", PlayerStatList);
			case ClassAssistance: format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Clasa: {00FF00}Mecanic\n", PlayerStatList);
			case ClassMedic: format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Clasa: {00FF00}Medic\n", PlayerStatList);
		}
		// Add money and score of the player to the list
		format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Bani: {00FF00}%i\n", PlayerStatList, APlayerData[clickedplayerid][PlayerMoney]);
		format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Scor: {00FF00}%i\n", PlayerStatList, APlayerData[clickedplayerid][PlayerScore]);
		// Add wanted-level of the player to the list
		format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Nivel wanted: {00FF00}%i\n", PlayerStatList, GetPlayerWantedLevel(clickedplayerid));
		// Add truckerlicense and busdriver license of the player to the list
		if (APlayerData[clickedplayerid][TruckerLicense] == 1)
			format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Licenta camionagiu: {00FF00}Da\n", PlayerStatList);
		else
			format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Licenta camionagiu: {00FF00}Nu\n", PlayerStatList);

		if (APlayerData[clickedplayerid][SoferLicense] == 1)
			format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Licenta conducator de tren: {00FF00}Da\n", PlayerStatList);
		else
			format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Licenta conducator de tren: {00FF00}Nu\n", PlayerStatList);
		if (APlayerData[clickedplayerid][BusLicense] == 1)
			format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Licenta sofer de autobuz: {00FF00}Da\n", PlayerStatList);
		else
			format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Licenta sofer de autobuz: {00FF00}Nu\n", PlayerStatList);
		if (APlayerData[clickedplayerid][MarinarLicense] == 1)
			format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Licenta marinar: {00FF00}Da\n", PlayerStatList);
		else
			format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Licenta marinar: {00FF00}Nu\n", PlayerStatList);
		if (APlayerData[clickedplayerid][TaxiLicense] == 1)
			format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Licenta taximetrist: {00FF00}Da\n", PlayerStatList);
		else
			format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Licenta taximetrist: {00FF00}Nu\n", PlayerStatList);
		if (APlayerData[clickedplayerid][PadurarLicense] == 1)
			format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Licenta padurar: {00FF00}Da\n", PlayerStatList);
		else
			format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Licenta padurar: {00FF00}Nu\n", PlayerStatList);
			
		format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Completed trucker jobs: {00FF00}%i\n", PlayerStatList, APlayerData[clickedplayerid][StatsTruckerJobs]);
		format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Completed convoy jobs: {00FF00}%i\n", PlayerStatList, APlayerData[clickedplayerid][StatsConvoyJobs]);
		format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Completed busdriver jobs: {00FF00}%i\n", PlayerStatList, APlayerData[clickedplayerid][StatsBusDriverJobs]);
		format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Completed pilot jobs: {00FF00}%i\n", PlayerStatList, APlayerData[clickedplayerid][StatsPilotJobs]);
		format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Completed Conducator Tren jobs: {00FF00}%i\n", PlayerStatList, APlayerData[clickedplayerid][StatsSoferJobs]);
		format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Completed Medic jobs: {00FF00}%i\n", PlayerStatList, APlayerData[clickedplayerid][StatsMedicJobs]);
		format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Completed Gunoier jobs: {00FF00}%i\n", PlayerStatList, APlayerData[clickedplayerid][StatsGJobs]);
		format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Completed Marinar jobs: {00FF00}%i\n", PlayerStatList, APlayerData[clickedplayerid][StatsMarinarJobs]);
		format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Completed Taxi jobs: {00FF00}%i\n", PlayerStatList, APlayerData[clickedplayerid][StatsTaxiJobs]);
		format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Completed Padurar jobs: {00FF00}%i\n", PlayerStatList, APlayerData[clickedplayerid][StatsPadurarJobs]);
		format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Completed mafia jobs: {00FF00}%i\n", PlayerStatList, APlayerData[clickedplayerid][StatsMafiaJobs]);
		format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Stolen mafia-loads: {00FF00}%i\n", PlayerStatList, APlayerData[clickedplayerid][StatsMafiaStolen]);
		format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Fined players: {00FF00}%i\n", PlayerStatList, APlayerData[clickedplayerid][StatsPoliceFined]);
		format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Fined players Fbi: {00FF00}%i\n", PlayerStatList, APlayerData[clickedplayerid][StatsFBYFined]);
		format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Jailed players: {00FF00}%i\n", PlayerStatList, APlayerData[clickedplayerid][StatsPoliceJailed]);
		format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Jailed players Fbi: {00FF00}%i\n", PlayerStatList, APlayerData[clickedplayerid][StatsFBYJailed]);
		format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Completed courier jobs: {00FF00}%i\n", PlayerStatList, APlayerData[clickedplayerid][StatsCourierJobs]);
		format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Completed Pizza Boy jobs: {00FF00}%i\n", PlayerStatList, APlayerData[clickedplayerid][StatsPboyJobs]);
		format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Completed roadworker jobs: {00FF00}%i\n", PlayerStatList, APlayerData[clickedplayerid][StatsRoadworkerJobs]);
		format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Assisted players: {00FF00}%i\n", PlayerStatList, APlayerData[clickedplayerid][StatsAssistance]);
		format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Meters driven: {00FF00}%f\n", PlayerStatList, APlayerData[clickedplayerid][StatsMetersDriven]);
		for (new i; i < MAX_HOUSESPERPLAYER; i++)
			if (APlayerData[clickedplayerid][Houses][i] != 0)
			    NumHouses++;
		for (new i; i < MAX_BUSINESSPERPLAYER; i++)
			if (APlayerData[clickedplayerid][Business][i] != 0)
			    NumBusinesses++;
		format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Case: {00FF00}%i\n", PlayerStatList, NumHouses);
		format(PlayerStatList, sizeof(PlayerStatList), "%s{FFFFFF}Afaceri: {00FF00}%i\n", PlayerStatList, NumBusinesses);
		APlayerData[playerid][DialogOtherPlayer] = clickedplayerid;
		ShowPlayerDialog(playerid, DialogStatsOtherPlayer, DIALOG_STYLE_LIST, DialogTitle, PlayerStatList, TXT_DialogButtonSelect, TXT_DialogButtonCancel); // Let the player buy a license
	}
	return 1;
}
// This callback gets called when a player picks up any pickup
public OnPlayerPickUpPickup(playerid, pickupid)
{
	// If the player picks up the Buy_License pickup at the driving school in Doherty
	if (pickupid == Pickup_License)
	    // Ask the player which license he wants to buy
		ShowPlayerDialog(playerid, DialogBuyLicenses, DIALOG_STYLE_LIST, TXT_DialogLicenseTitle, TXT_DialogLicenseList, TXT_DialogButtonBuy, TXT_DialogButtonCancel); // Let the player buy a license

	return 1;
}
// This callback gets called when a player spawns somewhere
public OnPlayerSpawn(playerid)
{

	SetPlayerWorldBounds(playerid, 20000.0000, -20000.0000, 20000.0000, -20000.0000);
	// Always allow NPC's to spawn without logging in
	if (IsPlayerNPC(playerid))
		return 1;

	// Check if the player properly logged in by typing his password
	if (APlayerData[playerid][LoggedIn] == false)
	{
		SendClientMessage(playerid, 0xFFFFFFFF, TXT_FailedLoginProperly);
	    Kick(playerid); // Kick the player if he didn't log in properly
	}

	// Setup local variables
	new missiontext[200];

	// Spawn the player in the global world (where everybody plays the game)
    SetPlayerVirtualWorld(playerid, 0);
	SetPlayerInterior(playerid, 0);
	// Also set a variable that tracks in which house the player currently is
	APlayerData[playerid][CurrentHouse] = 0;

	// Disable the clock
	TogglePlayerClock(playerid, 0);

	// Delete all weapons from the player
	ResetPlayerWeapons(playerid);

	// Set the missiontext based on the chosen class
	switch (APlayerData[playerid][PlayerClass])
	{
		case ClassTruckDriver: // Truck-driver class
		{
			format(missiontext, sizeof(missiontext), Trucker_NoJobText); // Preset the missiontext
			SetPlayerColor(playerid, ColorClassTruckDriver); // Set the playercolor (chatcolor for the player and color on the map)
		}
		case ClassBusDriver: // Bus-driver class
		{
			format(missiontext, sizeof(missiontext), BusDriver_NoJobText); // Preset the missiontext
			SetPlayerColor(playerid, ColorClassBusDriver); // Set the playercolor (chatcolor for the player and color on the map)
		}
		case ClassPilot: // Pilot class
		{
			format(missiontext, sizeof(missiontext), Pilot_NoJobText); // Preset the missiontext
			SetPlayerColor(playerid, ColorClassPilot); // Set the playercolor (chatcolor for the player and color on the map)
		}
		case ClassPolice: // Police class
		{
			format(missiontext, sizeof(missiontext), Police_NoJobText); // Preset the missiontext
			SetPlayerColor(playerid, ColorClassPolice); // Set the playercolor (chatcolor for the player and color on the map)
			// Start the PlayerCheckTimer to scan for wanted players (be sure the timer has been destroyed first)
			KillTimer(APlayerData[playerid][PlayerCheckTimer]);
			APlayerData[playerid][PlayerCheckTimer] = SetTimerEx("Police_CheckWantedPlayers", 1000, true, "i", playerid);
			// Check if the police player can get weapons
			if (PoliceGetsWeapons == true)
			{
			    // Give up to 12 weapons to the player
				for (new i; i < 12; i++)
				    GivePlayerWeapon(playerid, APoliceWeapons[i], PoliceWeaponsAmmo);
			}
		}
		case ClassFBY: // FBY class
		{
			format(missiontext, sizeof(missiontext), FBY_NoJobText); // Preset the missiontext
			SetPlayerColor(playerid, ColorClassFBY); // Set the playercolor (chatcolor for the player and color on the map)
			// Start the PlayerCheckTimer to scan for wanted players (be sure the timer has been destroyed first)
			KillTimer(APlayerData[playerid][PlayerCheckTimer]);
			APlayerData[playerid][PlayerCheckTimer] = SetTimerEx("FBY_CheckWantedPlayers", 1000, true, "i", playerid);
			// Check if the police player can get weapons
			if (FBYGetsWeapons == true)
			{
			    // Give up to 12 weapons to the player
				for (new i; i < 12; i++)
				    GivePlayerWeapon(playerid, AFBYWeapons[i], FBYWeaponsAmmo);
			}
		}
		case ClassMafia: // Mafia class
		{
			format(missiontext, sizeof(missiontext), Mafia_NoJobText); // Preset the missiontext
			SetPlayerColor(playerid, ColorClassMafia); // Set the playercolor (chatcolor for the player and color on the map)
			// Start the PlayerCheckTimer to scan for players that carry mafia-loads (be sure the timer has been destroyed first)
			KillTimer(APlayerData[playerid][PlayerCheckTimer]);
			APlayerData[playerid][PlayerCheckTimer] = SetTimerEx("Mafia_CheckMafiaLoads", 1000, true, "i", playerid);
			if (MafiaGetsWeapons == true)
            {
                // Give up to 12 weapons to the player
                for (new i; i < 12; i++)
                    GivePlayerWeapon(playerid, AMafiaWeapons[i], MafiaWeaponsAmmo);
            }
		}
		case ClassCourier: // Courier class
		{
			format(missiontext, sizeof(missiontext), Courier_NoJobText); // Preset the missiontext
			SetPlayerColor(playerid, ColorClassCourier); // Set the playercolor (chatcolor for the player and color on the map)
		}
		case ClassPboy: // Pizza Boy class
		{
			format(missiontext, sizeof(missiontext), Pboy_NoJobText); // Preset the missiontext
			SetPlayerColor(playerid, ColorClassPboy); // Set the playercolor (chatcolor for the player and color on the map)
		}
		case ClassAssistance: // Assistance class
		{
			format(missiontext, sizeof(missiontext), Assistance_NoJobText); // Preset the missiontext
			SetPlayerColor(playerid, ColorClassAssistance); // Set the playercolor (chatcolor for the player and color on the map)
			// Start the PlayerCheckTimer to scan for players who need assistance (be sure the timer has been destroyed first)
			KillTimer(APlayerData[playerid][PlayerCheckTimer]);
			APlayerData[playerid][PlayerCheckTimer] = SetTimerEx("Assistance_CheckPlayers", 1000, true, "i", playerid);
		}
		case ClassRoadWorker: // Roadworker class
		{
			format(missiontext, sizeof(missiontext), RoadWorker_NoJobText); // Preset the missiontext
			SetPlayerColor(playerid, ColorClassRoadWorker); // Set the playercolor (chatcolor for the player and color on the map)
		}
		case ClassMedic: // Medic class
		{
			format(missiontext, sizeof(missiontext), Medic_NoJobText); // Preset the missiontext
			SetPlayerColor(playerid, ColorClassMedic); // Set the playercolor (chatcolor for the player and color on the map)
		}
		case ClassSofer: // Conducator Tren class
		{
			format(missiontext, sizeof(missiontext), Sofer_NoJobText); // Preset the missiontext
			SetPlayerColor(playerid, ColorClassSofer); // Set the playercolor (chatcolor for the player and color on the map)
		}
		case ClassG: // G class
		{
			format(missiontext, sizeof(missiontext), Trucker_NoJobText); // Preset the missiontext
			SetPlayerColor(playerid, ColorClassG); // Set the playercolor (chatcolor for the player and color on the map)
		}
		case ClassMarinar: // Marinar class
		{
			format(missiontext, sizeof(missiontext), Marinar_NoJobText);
			SetPlayerColor(playerid, ColorClassMarinar);
		}
		case ClassTaxi: // Taxi class
		{
			format(missiontext, sizeof(missiontext), Taxi_NoJobText);
			SetPlayerColor(playerid, ColorClassTaxi);
		}
		case ClassPadurar: // Taxi class
		{
			format(missiontext, sizeof(missiontext), Padurar_NoJobText);
			SetPlayerColor(playerid, ColorClassPadurar);
		}
	}

	// Set the missiontext
	TextDrawSetString(APlayerData[playerid][MissionText], missiontext);
	// Show the missiontext for this player
	TextDrawShowForPlayer(playerid, APlayerData[playerid][MissionText]);

	// If the player spawns and his jailtime hasn't passed yet, put him back in jail
	if (APlayerData[playerid][PlayerJailed] != 0)
	    Police_JailPlayer(playerid, APlayerData[playerid][PlayerJailed]);

	if (APlayerData[playerid][PlayerJailed] != 0)
	    FBY_JailPlayer(playerid, APlayerData[playerid][PlayerJailed]);


	return 1;
}
// This callback gets called whenever a player enters a checkpoint
public OnPlayerEnterCheckpoint(playerid)
{
	// Check the player's class
	switch (APlayerData[playerid][PlayerClass])
	{
		case ClassTruckDriver: // Truckdriver class
			Trucker_OnPlayerEnterCheckpoint(playerid); // Process the checkpoint (load or unload goods)
		case ClassBusDriver: // BusDriver class
		{
			GameTextForPlayer(playerid, TXT_BusDriverMissionPassed, 3000, 4); // Show a message to let the player know he finished his job
			BusDriver_EndJob(playerid); // End the current mission
		}
		case ClassPilot: // Pilot class
			Pilot_OnPlayerEnterCheckpoint(playerid); // Process the checkpoint (load or unload)
		case ClassMafia: // Mafia class
			Mafia_OnPlayerEnterCheckpoint(playerid);
		case ClassCourier: // Courier class
			Courier_OnPlayerEnterCheckpoint(playerid);
		case ClassPboy: // Pizza Boy class
			Pboy_OnPlayerEnterCheckpoint(playerid);
		case ClassMedic: // Medic class
			Medic_OnPlayerEnterCheckpoint(playerid); // Process the checkpoint (load or unload)
		case ClassSofer: // Conducator tren class
			Sofer_OnPlayerEnterCheckpoint(playerid); // Process the checkpoint (load or unload)
		case ClassG: // G class
			G_OnPlayerEnterCheckpoint(playerid); // Process the checkpoint (load or unload)
		case ClassMarinar: // Marinar class
			Marinar_OnPlayerEnterCheckpoint(playerid); // Process the checkpoint (load or unload)
		case ClassTaxi: // Taxi class
			Taxi_OnPlayerEnterCheckpoint(playerid); // Process the checkpoint (load or unload)
		case ClassPadurar: // Padurar class
			Padurar_OnPlayerEnterCheckpoint(playerid); // Process the checkpoint (load or unload)

		case ClassRoadWorker: // Roadworker class
		{
			// Only end the mission when doing "repair-speedcamera" jobtype (checkpoint is the base of the roadworker)
			if (APlayerData[playerid][JobID] == 1) // Repairing speedcamera's
			{
				GameTextForPlayer(playerid, TXT_RoadworkerMissionPassed, 3000, 4); // Show a message to let the player know he finished his job
				Roadworker_EndJob(playerid); // End the current mission
			}
			if (APlayerData[playerid][JobID] == 2) // Towing broken vehicle to shredder
           Roadworker_EnterCheckpoint(playerid);
		}
	}

	return 1;
}
// This callback gets called when a player enters a race-checkpoint
public OnPlayerEnterRaceCheckpoint(playerid)
{
	// Check the player's class
	switch (APlayerData[playerid][PlayerClass])
	{
		case ClassBusDriver: // BusDriver class
		    Bus_EnterRaceCheckpoint(playerid); // Process the checkpoint
		case ClassRoadWorker: // Roadworker class
			Roadworker_EnterRaceCheckpoint(playerid);
	}

	return 1;
}
// This callback gets called whenever a player dies
public OnPlayerDeath(playerid, killerid, reason)
{
	// Setup local variables
	new VictimName[24], KillerName[24], Msg[128];
	// Clear the missiontext
	TextDrawSetString(APlayerData[playerid][MissionText], " ");
	// Hide the missiontext for this player (when the player is choosing a class, it's not required to show any mission-text)
	TextDrawHideForPlayer(playerid, APlayerData[playerid][MissionText]);

	// Stop any job that may have started
	switch (APlayerData[playerid][PlayerClass])
	{
		case ClassTruckDriver: Trucker_EndJob(playerid);
		case ClassBusDriver: BusDriver_EndJob(playerid);
		case ClassPilot: Pilot_EndJob(playerid);
		case ClassPolice: Police_EndJob(playerid);
		case ClassFBY: FBY_EndJob(playerid);
		case ClassMafia: Mafia_EndJob(playerid);
		case ClassCourier: Courier_EndJob(playerid);
		case ClassPboy: Pboy_EndJob(playerid);
		case ClassAssistance: Assistance_EndJob(playerid);
		case ClassRoadWorker: Roadworker_EndJob(playerid);
		case ClassMedic: Medic_EndJob(playerid);
		case ClassSofer: Sofer_EndJob(playerid);
		case ClassG: G_EndJob(playerid);
		case ClassMarinar: Marinar_EndJob(playerid);
		case ClassTaxi: Taxi_EndJob(playerid);
		case ClassPadurar: Padurar_EndJob(playerid);
	}

	// If the player is part of a convoy, kick him from it
	Convoy_Leave(playerid);

	// If another player kills you, he'll get an extra star of his wanted level if he's isn't a police officer
	if (killerid != INVALID_PLAYER_ID && APlayerData[killerid][PlayerClass] != ClassPolice)
	if (killerid != INVALID_PLAYER_ID && APlayerData[playerid][PlayerClass] != ClassFBY)
	{
		// Increase the wanted level of the killer by one star
	    SetPlayerWantedLevel(killerid, GetPlayerWantedLevel(killerid) + 1);
	    // Get the name of the killed player and the killer
	    GetPlayerName(playerid, VictimName, sizeof(VictimName));
	    GetPlayerName(killerid, KillerName, sizeof(KillerName));
	    // Let the killed know the police are informed about the kill
		format(Msg, 128, "{FF0000}Ai omorat pe {FFFF00}%s{FF0000},iar acum esti cautat de politie / FBY", VictimName);
		SendClientMessage(killerid, 0xFFFFFFFF, Msg);
		// Inform all police players about the kill
		format(Msg, 128, "{00FF00}Jucatorul {FFFF00}%s{00FF00} a omorat pe {FFFF00}%s{00FF00}, urmareste-l si amendeaza-l.", KillerName, VictimName);
		Police_SendMessage(Msg);
		FBY_SendMessage(Msg);
	}
	if(XDeaths[playerid] == 0)
    {
       LastDeath[playerid] = gettime();
    }
    XDeaths[playerid]++;
    if(XDeaths[playerid] == 5)
    {
        if((gettime() - LastDeath[playerid]) <= 5)
        {
            SendClientMessage(playerid,0,"{FFBF00}Buna Nobule, Flodeaz-o Pe Mata!");
            format(Msg, 128, "[Junkbuster]Am Dat ipban pt Flood (fakekill) la un Idiot care acum o Flodeaza Pe Ma-sa");
			SendClientMessageToAll(0xFF0080C8, Msg);
			for (new i; i < MAX_PLAYERS; i++)
			if (IsPlayerConnected(i)) // Check if the player is connected
			SetPlayerWantedLevel(i, 0);
			else
            BanEx(playerid,"Bannat pentru FakeKill");
        }else
        if((gettime() - LastDeath[playerid]) > 5)
        {
            XDeaths[playerid]=0;
        }
    }
	return 1;
}
// This callback gets called when the player is selecting a class (but hasn't clicked "Spawn" yet)
public OnPlayerRequestClass(playerid, classid)
{
 	SetPlayerInterior(playerid,0);
	SetPlayerPos(playerid,1595.5172,1449.9033,33.8483);
	SetPlayerFacingAngle(playerid, 78.0);
	SetPlayerCameraPos(playerid,1589.9000,1449.9033,36.0100);
	SetPlayerCameraLookAt(playerid,1595.5172,1449.9033,33.8483);

	// Display a short message to inform the player about the class he's about to choose
	switch (classid)
	{
		case 0, 1, 2, 3, 4, 5, 6, 7: // Classes that will be truckdrivers
		{
			// Display the name of the class
            GameTextForPlayer(playerid, TXT_ClassTrucker, 3000, 4);
			// Store the class for the player (truckdriver)
			APlayerData[playerid][PlayerClass] = ClassTruckDriver;
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_BEER);
		}
		case 8, 9: // Classes that will be bus-drivers
		{
			// Display the name of the class
            GameTextForPlayer(playerid, TXT_ClassBusDriver, 3000, 4);
			// Store the class for the player (busdriver)
			APlayerData[playerid][PlayerClass] = ClassBusDriver;
			SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DANCE1);
		}
		case 10: // Classes that will be Pilot
		{
			// Display the name of the class
            GameTextForPlayer(playerid, TXT_ClassPilot, 3000, 4);
			// Store the class for the player (pilot)
			APlayerData[playerid][PlayerClass] = ClassPilot;
			ApplyAnimation(playerid,"FAT","IDLE_tired",4.0,1,0,0,0,0);
		 	PlayerPlaySound(playerid, 4802, 0.0, 0.0, 10.0);
		}
		case 11, 12, 13: // Classes that will be police
		{
			// Display the name of the class
            GameTextForPlayer(playerid, TXT_ClassPolice, 3000, 4);
			// Store the class for the player (police)
			APlayerData[playerid][PlayerClass] = ClassPolice;
			ApplyAnimation(playerid, "ped", "cower", 3.0, 1, 0, 0, 0, 0); // Taking Cover
		}
		case 14, 15, 16: // Classes that will be mafia
		{
			// Display the name of the class
			GameTextForPlayer(playerid, TXT_ClassMafia, 3000, 4);
			// Store the class for the player (mafia)
			APlayerData[playerid][PlayerClass] = ClassMafia;
			ApplyAnimation(playerid,"PED","WALK_DRUNK",4.0,1,1,1,1,0);
		}
		case 17, 18: // Classes that will be courier
		{
			// Display the name of the class
			GameTextForPlayer(playerid, TXT_ClassCourier, 3000, 4);
			// Store the class for the player (courier)
			APlayerData[playerid][PlayerClass] = ClassCourier;
			SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DANCE3);
		}
		case 19: // Classes that will be assistance
		{
			// Display the name of the class
			GameTextForPlayer(playerid, TXT_ClassAssistance, 3000, 4);
			// Store the class for the player (assistance)
			APlayerData[playerid][PlayerClass] = ClassAssistance;
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_SMOKE_CIGGY);
		}
		case 20, 21, 22: // Classes that will be roadworker
		{
			// Display the name of the class
			GameTextForPlayer(playerid, TXT_ClassRoadWorker, 3000, 4);
			// Store the class for the player (roadworker)
			APlayerData[playerid][PlayerClass] = ClassRoadWorker;
			SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DANCE4);
		}
		case 23, 24: // Classes that will be Medic
		{
			// Display the name of the class
			GameTextForPlayer(playerid, TXT_ClassMedic, 3000, 4);
			// Store the class for the player (roadworker)
			APlayerData[playerid][PlayerClass] = ClassMedic;
			ApplyAnimation(playerid, "CRACK", "crckdeth2", 4.0, 1, 0, 0, 0, 0); // Dieing of Crack
			
		}
		case 25, 26, 27: // Classes that will be FBY
		{
			// Display the name of the class
            GameTextForPlayer(playerid, TXT_ClassFBY, 3000, 4);
			// Store the class for the player (FBY)
			APlayerData[playerid][PlayerClass] = ClassFBY;
			SetPlayerSpecialAction (playerid,SPECIAL_ACTION_HANDSUP);
		}
		case 28, 29, 30: // Classes that will be Pizza Boy
		{
			// Display the name of the class
			GameTextForPlayer(playerid, TXT_ClassPboy, 3000, 4);
			// Store the class for the player (Pizza Boy)
			APlayerData[playerid][PlayerClass] = ClassPboy;
			ApplyAnimation(playerid, "FOOD", "EAT_Burger", 3.0, 0, 0, 0, 0, 0); // Eat Burger
		}
		case 31, 32, 33: // Classes that will be Conducator Tren
		{
			// Display the name of the class
			GameTextForPlayer(playerid, TXT_ClassSofer, 3000, 4);
			// Store the class for the player (Conducator Tren)
			APlayerData[playerid][PlayerClass] = ClassSofer;
			ApplyAnimation(playerid, "ON_LOOKERS", "wave_loop", 4.0, 1, 0, 0, 0, 0); // Wave
		}
		case 34, 35, 36: // Classes that will be G
		{
			// Display the name of the class
			GameTextForPlayer(playerid, TXT_ClassG, 3000, 4);
			// Store the class for the player (G)
			APlayerData[playerid][PlayerClass] = ClassG;
			ApplyAnimation(playerid, "SWEET", "sweet_ass_slap", 4.0, 0, 0, 0, 0, 0); // Ass Slapping
		}
		case 37, 38, 39: // Classes that will be Marinar
		{
			// Display the name of the class
			GameTextForPlayer(playerid, TXT_ClassMarinar, 3000, 4);
			// Store the class for the player (Marinar)
			APlayerData[playerid][PlayerClass] = ClassMarinar;
			SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DANCE2);
		}
		case 40, 41, 42: // Classes that will be Taxi
		{
			// Display the name of the class
			GameTextForPlayer(playerid, TXT_ClassTaxi, 3000, 4);
			// Store the class for the player (Marinar)
			APlayerData[playerid][PlayerClass] = ClassTaxi;
			ApplyAnimation(playerid,"BLOWJOBZ","BJ_STAND_LOOP_W",4.0,1,0,0,0,-1);
		}
		case 43, 44, 45: // Classes that will be Padurar
		{
			// Display the name of the class
			GameTextForPlayer(playerid, TXT_ClassPadurar, 3000, 4);
			// Store the class for the player (Padurar)
			APlayerData[playerid][PlayerClass] = ClassPadurar;
			ApplyAnimation(playerid,"DANCING","DNCE_M_B",4.0,1,0,0,0,-1);
		}
		
	}
	return 1;
}
// This callback is called when the player attempts to spawn via class-selection
public OnPlayerRequestSpawn(playerid)
{
	new Index, Float:x, Float:y, Float:z, Float:Angle, Name[24], Msg[128];

	// Get the player's name
	GetPlayerName(playerid, Name, sizeof(Name));

	// Choose a random spawnlocation based on the player's class
	switch (APlayerData[playerid][PlayerClass])
	{
		case ClassTruckDriver:
		{
			Index = random(sizeof(ASpawnLocationsTrucker)); // Get a random array-index to chose a random spawnlocation
			x = ASpawnLocationsTrucker[Index][SpawnX]; // Get the X-position for the spawnlocation
			y = ASpawnLocationsTrucker[Index][SpawnY]; // Get the Y-position for the spawnlocation
			z = ASpawnLocationsTrucker[Index][SpawnZ]; // Get the Z-position for the spawnlocation
			Angle = ASpawnLocationsTrucker[Index][SpawnAngle]; // Get the rotation-angle for the spawnlocation
			format(Msg, 128, "{00FF00}Jucatorul {FFFF00}%s{00FF00} s-a alaturat {FFFF00}Camionagiilor", Name);
		}
		case ClassBusDriver:
		{
			Index = random(sizeof(ASpawnLocationsBusDriver));
			x = ASpawnLocationsBusDriver[Index][SpawnX]; // Get the X-position for the spawnlocation
			y = ASpawnLocationsBusDriver[Index][SpawnY]; // Get the Y-position for the spawnlocation
			z = ASpawnLocationsBusDriver[Index][SpawnZ]; // Get the Z-position for the spawnlocation
			Angle = ASpawnLocationsBusDriver[Index][SpawnAngle]; // Get the rotation-angle for the spawnlocation
			format(Msg, 128, "{00FF00}Jucatorul {FFFF00}%s{00FF00} s-a alaturat {FFFF00}Soferilor de Autobuz", Name);
		}
		case ClassPilot:
		{
			Index = random(sizeof(ASpawnLocationsPilot));
			x = ASpawnLocationsPilot[Index][SpawnX]; // Get the X-position for the spawnlocation
			y = ASpawnLocationsPilot[Index][SpawnY]; // Get the Y-position for the spawnlocation
			z = ASpawnLocationsPilot[Index][SpawnZ]; // Get the Z-position for the spawnlocation
			Angle = ASpawnLocationsPilot[Index][SpawnAngle]; // Get the rotation-angle for the spawnlocation
			format(Msg, 128, "{00FF00}Jucatorul {FFFF00}%s{00FF00} s-a alaturat {FFFF00}Pilotilor", Name);
		}
		case ClassPolice:
		{
		    // Count the number of normal players (all classes except police) and count the amount of police players
		    new NormalPlayers, PolicePlayers, bool:CanSpawnAsCop = false;

			// Block this check if PlayersBeforePolice is set to 0 (this allows anyone to join as police)
			if (PlayersBeforePolice > 0)
			{
				// Loop through all players
				for (new pid; pid < MAX_PLAYERS; pid++)
				{
					// Exclude this player, as he doesn't have a class yet, he's still choosing here
					if (pid != playerid)
					{
					    // Also exclude all players who are still in the class-selection screen, as they don't have a class selected yet
					    if (GetPlayerInterior(pid) != 14)
					    {
							// Check if this player is logged in
							if (APlayerData[pid][LoggedIn] == true)
							{
								// Count the amount of normal players and police players
								switch (APlayerData[pid][PlayerClass])
								{
									case ClassPolice:
									    PolicePlayers++;
									case ClassTruckDriver, ClassBusDriver, ClassPilot, ClassMafia, ClassCourier, ClassAssistance, ClassRoadWorker, ClassMedic, ClassG, ClassPboy:
								    	NormalPlayers++;
								}
							}
						}
					}
				}
				// Check if there are less police players than allowed
				if (PolicePlayers < (NormalPlayers / PlayersBeforePolice))
				    CanSpawnAsCop = true; // There are less police players than allowed, so the player can choose this class
				else
				    CanSpawnAsCop = false; // The maximum amount of police players has been reached, the player can't choose to be a cop

				// Check if the player isn't allowed to spawn as police
				if (CanSpawnAsCop == false)
				{
					// Let the player know the maximum amount of cops has been reached
					GameTextForPlayer(playerid, "Numarul maxim de politisti a fost atins.", 5000, 4);
					SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}The maximum amount of cops has been reached already, please select another class");
					return 0; // Don't allow the player to spawn as police player
				}
			}

			// If the player has less than 100 scorepoints
		    if (APlayerData[playerid][PlayerScore] < 1000)
		    {
				// Let the player know he needs 100 scorepoints
				GameTextForPlayer(playerid, "Ai nevoie de 1000 scor pentru a te alatura Politistilor", 5000, 4);
				SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}Ai nevoie de 1000 scor pentru a te alatura politistilor.");
				return 0; // Don't allow the player to spawn as police player
		    }
			// If the player has a wanted level
		    if (GetPlayerWantedLevel(playerid) > 0)
		    {
				// Let the player know he cannot have a wanted level to join police
				GameTextForPlayer(playerid, "You are not allowed to choose police class when you're wanted", 5000, 4);
				SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}You are not allowed to choose police class when you're wanted");
				return 0; // Don't allow the player to spawn as police player
		    }
		    
			Index = random(sizeof(ASpawnLocationsPolice));
			x = ASpawnLocationsPolice[Index][SpawnX]; // Get the X-position for the spawnlocation
			y = ASpawnLocationsPolice[Index][SpawnY]; // Get the Y-position for the spawnlocation
			z = ASpawnLocationsPolice[Index][SpawnZ]; // Get the Z-position for the spawnlocation
			Angle = ASpawnLocationsPolice[Index][SpawnAngle]; // Get the rotation-angle for the spawnlocation
			format(Msg, 128, "{00FF00}Jucatorul {FFFF00}%s{00FF00} s-a alaturat {FFFF00}Politistilor", Name);
		}
		case ClassFBY:
		{
			// If the player has less than 100 scorepoints
		    if (APlayerData[playerid][PlayerScore] < 4000)
		    {
				// Let the player know he needs 100 scorepoints
				GameTextForPlayer(playerid, "Ai nevoie de 4000 scor pentru a te alatura agentilor FBI", 5000, 4);
				SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}Ai nevoie de 4000 scor pentru a te alatura agentilor FBI");
				return 0; // Don't allow the player to spawn as police player
		    }
			// If the player has a wanted level
		    if (GetPlayerWantedLevel(playerid) > 0)
		    {
				// Let the player know he cannot have a wanted level to join police
				GameTextForPlayer(playerid, "You are not allowed to choose FBI class when you're wanted", 5000, 4);
				SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}You are not allowed to choose FBI class when you're wanted");
				return 0; // Don't allow the player to spawn as police player
		    }

			Index = random(sizeof(ASpawnLocationsFBY));
			x = ASpawnLocationsFBY[Index][SpawnX]; // Get the X-position for the spawnlocation
			y = ASpawnLocationsFBY[Index][SpawnY]; // Get the Y-position for the spawnlocation
			z = ASpawnLocationsFBY[Index][SpawnZ]; // Get the Z-position for the spawnlocation
			Angle = ASpawnLocationsFBY[Index][SpawnAngle]; // Get the rotation-angle for the spawnlocation
			format(Msg, 128, "{00FF00}Jucatorul {FFFF00}%s{00FF00} s-a alaturat {FFFF00}agentilor FBI", Name);
		}
		case ClassMafia:
		{
			Index = random(sizeof(ASpawnLocationsMafia));
			x = ASpawnLocationsMafia[Index][SpawnX]; // Get the X-position for the spawnlocation
			y = ASpawnLocationsMafia[Index][SpawnY]; // Get the Y-position for the spawnlocation
			z = ASpawnLocationsMafia[Index][SpawnZ]; // Get the Z-position for the spawnlocation
			Angle = ASpawnLocationsMafia[Index][SpawnAngle]; // Get the rotation-angle for the spawnlocation
			format(Msg, 128, "{00FF00}Jucatorul {FFFF00}%s{00FF00} s-a alaturat {FFFF00}Mafiei", Name);
		}
		case ClassCourier:
		{
			Index = random(sizeof(ASpawnLocationsCourier));
			x = ASpawnLocationsCourier[Index][SpawnX]; // Get the X-position for the spawnlocation
			y = ASpawnLocationsCourier[Index][SpawnY]; // Get the Y-position for the spawnlocation
			z = ASpawnLocationsCourier[Index][SpawnZ]; // Get the Z-position for the spawnlocation
			Angle = ASpawnLocationsCourier[Index][SpawnAngle]; // Get the rotation-angle for the spawnlocation
			format(Msg, 128, "{00FF00}Jucatorul {FFFF00}%s{00FF00} s-a alaturat {FFFF00}Curierilor", Name);
		}
		case ClassPboy:
		{
			Index = random(sizeof(ASpawnLocationsPboy));
			x = ASpawnLocationsPboy[Index][SpawnX]; // Get the X-position for the spawnlocation
			y = ASpawnLocationsPboy[Index][SpawnY]; // Get the Y-position for the spawnlocation
			z = ASpawnLocationsPboy[Index][SpawnZ]; // Get the Z-position for the spawnlocation
			Angle = ASpawnLocationsPboy[Index][SpawnAngle]; // Get the rotation-angle for the spawnlocation
			format(Msg, 128, "{00FF00}Jucatorul {FFFF00}%s{00FF00} s-a alaturat {FFFF00}Baietilor cu Pizza", Name);
		}
		case ClassAssistance:
		{
			Index = random(sizeof(ASpawnLocationsAssistance));
			x = ASpawnLocationsAssistance[Index][SpawnX]; // Get the X-position for the spawnlocation
			y = ASpawnLocationsAssistance[Index][SpawnY]; // Get the Y-position for the spawnlocation
			z = ASpawnLocationsAssistance[Index][SpawnZ]; // Get the Z-position for the spawnlocation
			Angle = ASpawnLocationsAssistance[Index][SpawnAngle]; // Get the rotation-angle for the spawnlocation
			format(Msg, 128, "{00FF00}Jucatorul {FFFF00}%s{00FF00} s-a alaturat {FFFF00}Mecanicilor", Name);
		}
		case ClassRoadWorker:
		{
			Index = random(sizeof(ASpawnLocationsRoadWorker));
			x = ASpawnLocationsRoadWorker[Index][SpawnX]; // Get the X-position for the spawnlocation
			y = ASpawnLocationsRoadWorker[Index][SpawnY]; // Get the Y-position for the spawnlocation
			z = ASpawnLocationsRoadWorker[Index][SpawnZ]; // Get the Z-position for the spawnlocation
			Angle = ASpawnLocationsRoadWorker[Index][SpawnAngle]; // Get the rotation-angle for the spawnlocation
			format(Msg, 128, "{00FF00}Jucatorul {FFFF00}%s{00FF00} s-a alaturat {FFFF00}Lucratorilor rutieri", Name);
		}
		case ClassMedic:
		{
			Index = random(sizeof(ASpawnLocationsMedic));
			x = ASpawnLocationsMedic[Index][SpawnX]; // Get the X-position for the spawnlocation
			y = ASpawnLocationsMedic[Index][SpawnY]; // Get the Y-position for the spawnlocation
			z = ASpawnLocationsMedic[Index][SpawnZ]; // Get the Z-position for the spawnlocation
			Angle = ASpawnLocationsMedic[Index][SpawnAngle]; // Get the rotation-angle for the spawnlocation
			format(Msg, 128, "{00FF00}Jucatorul {FFFF00}%s{00FF00} s-a alaturat {FFFF00}Medicilor", Name);
		}
		case ClassG:
		{
			Index = random(sizeof(ASpawnLocationsG));
			x = ASpawnLocationsG[Index][SpawnX]; // Get the X-position for the spawnlocation
			y = ASpawnLocationsG[Index][SpawnY]; // Get the Y-position for the spawnlocation
			z = ASpawnLocationsG[Index][SpawnZ]; // Get the Z-position for the spawnlocation
			Angle = ASpawnLocationsG[Index][SpawnAngle]; // Get the rotation-angle for the spawnlocation
			format(Msg, 128, "{00FF00}Jucatorul {FFFF00}%s{00FF00} s-a alaturat {FFFF00}Gunoierilor", Name);
		}
		case ClassSofer:
		{
			Index = random(sizeof(ASpawnLocationsSofer));
			x = ASpawnLocationsSofer[Index][SpawnX]; // Get the X-position for the spawnlocation 
			y = ASpawnLocationsSofer[Index][SpawnY]; // Get the Y-position for the spawnlocation
			z = ASpawnLocationsSofer[Index][SpawnZ]; // Get the Z-position for the spawnlocation
			Angle = ASpawnLocationsSofer[Index][SpawnAngle]; // Get the rotation-angle for the spawnlocation
			format(Msg, 128, "{00FF00}Jucatorul {FFFF00}%s{00FF00} s-a alaturat {FFFFFF}Conducatorilor de Tren", Name);
		}
		case ClassMarinar:
		{
			Index = random(sizeof(ASpawnLocationsMarinar));
			x = ASpawnLocationsMarinar[Index][SpawnX]; // Get the X-position for the spawnlocation
			y = ASpawnLocationsMarinar[Index][SpawnY]; // Get the Y-position for the spawnlocation
			z = ASpawnLocationsMarinar[Index][SpawnZ]; // Get the Z-position for the spawnlocation
			Angle = ASpawnLocationsMarinar[Index][SpawnAngle]; // Get the rotation-angle for the spawnlocation
			format(Msg, 128, "{00FF00}Jucatorul {FFFF00}%s{00FF00} s-a alaturat {FFFF00}Marinarilor", Name);
		}
		case ClassTaxi:
		{
			Index = random(sizeof(ASpawnLocationsTaxi));
			x = ASpawnLocationsTaxi[Index][SpawnX]; // Get the X-position for the spawnlocation
			y = ASpawnLocationsTaxi[Index][SpawnY]; // Get the Y-position for the spawnlocation
			z = ASpawnLocationsTaxi[Index][SpawnZ]; // Get the Z-position for the spawnlocation
			Angle = ASpawnLocationsTaxi[Index][SpawnAngle]; // Get the rotation-angle for the spawnlocation
			format(Msg, 128, "{00FF00}Jucatorul {FFFF00}%s{00FF00} s-a alaturat {FFFF00}Taximetristilor", Name);
		}
		case ClassPadurar:
		{
			Index = random(sizeof(ASpawnLocationsPadurar));
			x = ASpawnLocationsPadurar[Index][SpawnX]; // Get the X-position for the spawnlocation
			y = ASpawnLocationsPadurar[Index][SpawnY]; // Get the Y-position for the spawnlocation
			z = ASpawnLocationsPadurar[Index][SpawnZ]; // Get the Z-position for the spawnlocation
			Angle = ASpawnLocationsPadurar[Index][SpawnAngle]; // Get the rotation-angle for the spawnlocation
			format(Msg, 128, "{00FF00}Jucatorul {FFFF00}%s{00FF00} s-a alaturat {FFFF00}Padurarilor", Name);
		}


	}

	// Spawn the player with his chosen skin at a random location based on his class
	SetSpawnInfo(playerid, 0, GetPlayerSkin(playerid), x, y, z, Angle, 0, 0, 0, 0, 0, 0);
	// Send the message to all players (who joined which class)
	SendClientMessageToAll(0xFFFFFFFF, Msg);

    return 1;
}


// This callback gets called when a vehicle respawns at it's spawn-location (where it was created)
public OnVehicleSpawn(vehicleid)
{
	// Set the vehicle as not-wanted by the mafia
	AVehicleData[vehicleid][MafiaLoad] = false;
	// Also reset the fuel to maximum (only for non-owned vehicles)
	if (AVehicleData[vehicleid][Owned] == false)
		AVehicleData[vehicleid][Fuel] = MaxFuel;

	// Re-apply the paintjob (if any was applied)
	if (AVehicleData[vehicleid][PaintJob] != 0)
	{
	    // Re-apply the paintjob
		ChangeVehiclePaintjob(vehicleid, AVehicleData[vehicleid][PaintJob] - 1);
	}

	// Also update the car-color
	ChangeVehicleColor(vehicleid, AVehicleData[vehicleid][Color1], AVehicleData[vehicleid][Color2]);

	// Re-add all components that were installed (if they were there)
	for (new i; i < 14; i++)
	{
		// Remove all mods from the vehicle (all added mods applied by hackers will hopefully be removed this way when the vehicle respawns)
        RemoveVehicleComponent(vehicleid, GetVehicleComponentInSlot(vehicleid, i));

	    // Check if the componentslot has a valid component-id
		if (AVehicleData[vehicleid][Components][i] != 0)
	        AddVehicleComponent(vehicleid, AVehicleData[vehicleid][Components][i]); // Add the component to the vehicle
	}

    return 1;
}



// This callback is called when the vehicle leaves a mod shop
public OnVehicleRespray(playerid, vehicleid, color1, color2)
{
	// Let the player pay $150 for changing the color (if they have been changed)
	if ((AVehicleData[vehicleid][Color1] != color1) || (AVehicleData[vehicleid][Color2] != color2))
	{
		RewardPlayer(playerid, -15000, 0);
		SendClientMessage(playerid, 0xFFFFFFFF, "{00FF00}Ai schimbat culoarea masini pentru $15000");
	}

	// Save the colors
	AVehicleData[vehicleid][Color1] = color1;
	AVehicleData[vehicleid][Color2] = color2;

	// If the primary color is black, remove the paintjob
	if (color1 == 0)
		AVehicleData[vehicleid][PaintJob] = 0;

	return 1;
}



// This callback gets called when a player enters or exits a mod-shop
public OnEnterExitModShop(playerid, enterexit, interiorid)
{
	return 1;
}



// This callback gets called whenever a player mods his vehicle
public OnVehicleMod(playerid, vehicleid, componentid)
{
	// When the player changes a component of his vehicle, reduce the price of the component from the player's money
	APlayerData[playerid][PlayerMoney] = APlayerData[playerid][PlayerMoney] - AVehicleModPrices[componentid - 1000];

	// Store the component in the AVehicleData array
	AVehicleData[vehicleid][Components][GetVehicleComponentType(componentid)] = componentid;

	return 1;
}



// This callback gets called whenever a player VIEWS at a paintjob in a mod garage (viewing automatically applies it)
public OnVehiclePaintjob(playerid, vehicleid, paintjobid)
{
	// Store the paintjobid for the vehicle (add 1 to the value, otherwise checking for an applied paintjob is difficult)
    AVehicleData[vehicleid][PaintJob] = paintjobid + 1;

	return 1;
}
// This callback gets called whenever a player enters a vehicle
public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	// Setup local variables
	new engine, lights, alarm, doors, bonnet, boot, objective;

	// Check if the vehicle has fuel
	if (AVehicleData[vehicleid][Fuel] > 0)
	{
		// Start the engine and turn on the lights
		GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
		SetVehicleParamsEx(vehicleid, 1, 1, alarm, doors, bonnet, boot, objective);
	}

	// Store the player's current location and interior-id, otherwise anti-airbreak hack code could kick you
	GetPlayerPos(playerid, APlayerData[playerid][PreviousX], APlayerData[playerid][PreviousY], APlayerData[playerid][PreviousZ]);
	APlayerData[playerid][PreviousInt] = GetPlayerInterior(playerid);

	return 1;
}
// This callback gets called when a player exits his vehicle
public OnPlayerExitVehicle(playerid, vehicleid)
{
	// Setup local variables
	new engine, lights, alarm, doors, bonnet, boot, objective;

	// Check if the player is the driver of the vehicle
	if (GetPlayerVehicleSeat(playerid) == 0)
	{
		// Turn off the lights and engine
		GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
		SetVehicleParamsEx(vehicleid, 0, 0, alarm, doors, bonnet, boot, objective);
	}

	// Chech if the player is a pilot
	if (APlayerData[playerid][PlayerClass] == ClassPilot)
	{
	    // If the pilot started a job --> as soon as a pilot leaves his plane while doing a job, he fails his mission
		if (APlayerData[playerid][JobStarted] == true)
		{
		    // End the job (clear data)
			Pilot_EndJob(playerid);
			// Inform the player that he failed the mission
			GameTextForPlayer(playerid, TXT_FailedMission, 5000, 4);
			// Reduce the player's cash by 1000
			RewardPlayer(playerid, -1000, 0);
		}
	}
	if (APlayerData[playerid][PlayerClass] == ClassMedic)
	{
	    // If the Medic started a job --> as soon as a pilot leaves his plane while doing a job, he fails his mission
		if (APlayerData[playerid][JobStarted] == true)
		{
		    // End the job (clear data)
			Medic_EndJob(playerid);
			// Inform the player that he failed the mission
			GameTextForPlayer(playerid, TXT_FailedMission, 5000, 4);
			// Reduce the player's cash by 1000
			RewardPlayer(playerid, -1000, 0);
		}
	}
	if (APlayerData[playerid][PlayerClass] == ClassG)
	{
	    // If the G started a job --> as soon as a pilot leaves his plane while doing a job, he fails his mission
		if (APlayerData[playerid][JobStarted] == true)
		{
		    // End the job (clear data)
			G_EndJob(playerid);
			// Inform the player that he failed the mission
			GameTextForPlayer(playerid, TXT_FailedMission, 5000, 4);
			// Reduce the player's cash by 1000
			RewardPlayer(playerid, -1000, 0);
		}
	}
	return 1;
}
// This callback gets called whenever a vehicle enters the water or is destroyed (explodes)
public OnVehicleDeath(vehicleid)
{
	// Get the houseid to which this vehicle belongs
	new HouseID = AVehicleData[vehicleid][BelongsToHouse];

	// Check if this vehicle belongs to a house
	if (HouseID != 0)
	{
		// If the house doesn't have insurance for it's vehicles
		if (AHouseData[HouseID][Insurance] == 0)
		{
		    // Delete the vehicle, clear the data and remove it from the house it belongs to
			Vehicle_Delete(vehicleid);

		    // Save the house (and linked vehicles)
		    HouseFile_Save(HouseID);
		}
	}

	return 1;
}
// This callback gets called when the player changes state
public OnPlayerStateChange(playerid,newstate,oldstate)
{
	// Setup local variables
	new vid, Name[24], Msg[128], engine, lights, alarm, doors, bonnet, boot, objective;

	switch (newstate)
	{
		case PLAYER_STATE_DRIVER: // Player became the driver of a vehicle
		{
			// Get the ID of the player's vehicle
			vid = GetPlayerVehicleID(playerid);
			// Get the player's name (the one who is trying to enter the vehicle)
			GetPlayerName(playerid, Name, sizeof(Name));

			// Check if the vehicle is owned
			if (AVehicleData[vid][Owned] == true)
			{
				// Check if the vehicle is owned by somebody else (strcmp will not be 0)
				if (strcmp(AVehicleData[vid][Owner], Name, false) != 0)
				{
					// Force the player out of the vehicle
					RemovePlayerFromVehicle(playerid);
					// Turn off the lights and engine
					GetVehicleParamsEx(vid, engine, lights, alarm, doors, bonnet, boot, objective);
					SetVehicleParamsEx(vid, 0, 0, alarm, doors, bonnet, boot, objective);
					// Let the player know he cannot use somebody else's vehicle
					format(Msg, 128, TXT_SpeedometerCannotUseVehicle, AVehicleData[vid][Owner]);
					SendClientMessage(playerid, 0xFFFFFFFF, Msg);
				}
				// Check if the vehicle is clamped
				if (AVehicleData[vid][Clamped] == true)
				{
					// Force the player out of the vehicle
					RemovePlayerFromVehicle(playerid);
					// Turn off the lights and engine
					GetVehicleParamsEx(vid, engine, lights, alarm, doors, bonnet, boot, objective);
					SetVehicleParamsEx(vid, 0, 0, alarm, doors, bonnet, boot, objective);
					// Let the player know he cannot use a clamped vehicle
					format(Msg, 128, TXT_SpeedometerClampedVehicle);
					SendClientMessage(playerid, 0xFFFFFFFF, Msg);
					format(Msg, 128, TXT_SpeedometerClampedVehicle2);
					SendClientMessage(playerid, 0xFFFFFFFF, Msg);
				}
			}

			// Check if the player is not a cop
			if (APlayerData[playerid][PlayerClass] != ClassPolice)
			{
				// First check if the vehicle is a static vehicle (player can still use a bought cop-car that he bought in his house,
				// as a bought vehicle isn't static)
				if (AVehicleData[vid][StaticVehicle] == true)
				{
					// Check if the entered vehicle is a cop vehicle
					switch (GetVehicleModel(vid))
					{
						case VehiclePoliceLSPD, VehiclePoliceSFPD, VehiclePoliceLVPD, VehicleHPV1000, VehiclePoliceRanger:
						{
							// Force the player out of the vehicle
							RemovePlayerFromVehicle(playerid);
							// Turn off the lights and engine
							GetVehicleParamsEx(vid, engine, lights, alarm, doors, bonnet, boot, objective);
							SetVehicleParamsEx(vid, 0, 0, alarm, doors, bonnet, boot, objective);
							// Let the player know he cannot use a cop car
							SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}Nu poti folosi o masina a politiei daca nu esti politist");
						}
					}
				}
			}
			if (APlayerData[playerid][PlayerClass] != ClassFBY)
			{
				// First check if the vehicle is a static vehicle (player can still use a bought cop-car that he bought in his house,
				// as a bought vehicle isn't static)
				if (AVehicleData[vid][StaticVehicle] == true)
				{
					// Check if the entered vehicle is a FBY vehicle
					switch (GetVehicleModel(vid))
					{
						case VehiclePoliceLSPD:
						{
							// Force the player out of the vehicle
							RemovePlayerFromVehicle(playerid);
							// Turn off the lights and engine
							GetVehicleParamsEx(vid, engine, lights, alarm, doors, bonnet, boot, objective);
							SetVehicleParamsEx(vid, 0, 0, alarm, doors, bonnet, boot, objective);
							// Let the player know he cannot use a cop car
							SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}Nu poti folosi o masina a FBY-ului daca nu esti unui dintre ei");
						}
					}
				}
			}
			// Check if the player is not a pilot
			if (APlayerData[playerid][PlayerClass] != ClassPilot)
			{
				// First check if the vehicle is a static vehicle (player can still use a bought plane that he bought in his house,
				// as a bought vehicle isn't static)
				if (AVehicleData[vid][StaticVehicle] == true)
				{
					// Check if the entered vehicle is a plane or helicopter vehicle
					switch (GetVehicleModel(vid))
					{
						case VehicleShamal, VehicleNevada, VehicleStuntPlane, VehicleDodo, VehicleMaverick, VehicleCargobob:
						{
							// Force the player out of the vehicle
							RemovePlayerFromVehicle(playerid);
							// Turn off the lights and engine
							GetVehicleParamsEx(vid, engine, lights, alarm, doors, bonnet, boot, objective);
							SetVehicleParamsEx(vid, 0, 0, alarm, doors, bonnet, boot, objective);
							// Let the player know he cannot use a cop car
							SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}Nu poti folosi un avion / elicopter daca nu esti pilot");
						}
					}
				}
			}
		}
	}

	return 1;
}
// This callback gets called whenever a player presses a key
public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	// Debug the keypresses
//	DebugKeys(playerid, newkeys, oldkeys);

	// ****************************************************************************************
	// NOTE: the keys are messed up, so the code may look strange when testing for certain keys
	// ****************************************************************************************

	// Fining and jailing players when you're police and press the correct keys
	// Check the class of the player
	switch (APlayerData[playerid][PlayerClass])
	{
		case ClassPolice:
		{
		    // If the police-player pressed the RMB key (AIM key) when OUTSIDE his vehicle
			if (((newkeys & KEY_HANDBRAKE) && !(oldkeys & KEY_HANDBRAKE)) && (GetPlayerVehicleID(playerid) == 0))
				Police_FineNearbyPlayers(playerid);

		    // If the police-player pressed the LCTRL (SECUNDAIRY key) key when INSIDE his vehicle
			if (((newkeys & KEY_ACTION) && !(oldkeys & KEY_ACTION)) && (GetPlayerVehicleID(playerid) != 0))
				Police_WarnNearbyPlayers(playerid);
		}
		case ClassFBY:
		{
		    // If the police-player pressed the RMB key (AIM key) when OUTSIDE his vehicle
			if (((newkeys & KEY_HANDBRAKE) && !(oldkeys & KEY_HANDBRAKE)) && (GetPlayerVehicleID(playerid) == 0))
				FBY_FineNearbyPlayers(playerid);

		    // If the FBY-player pressed the LCTRL (SECUNDAIRY key) key when INSIDE his vehicle
			if (((newkeys & KEY_ACTION) && !(oldkeys & KEY_ACTION)) && (GetPlayerVehicleID(playerid) != 0))
				FBY_WarnNearbyPlayers(playerid);
		}
		case ClassAssistance:
		{
		    // If the assistance-player pressed the RMB key (AIM key) when OUTSIDE his vehicle
			if (((newkeys & KEY_HANDBRAKE) && !(oldkeys & KEY_HANDBRAKE)) && (GetPlayerVehicleID(playerid) == 0))
				Assistance_FixVehicle(playerid);

		    // If the police-player pressed the LCTRL (SECUNDAIRY key) key when INSIDE his vehicle
			if (((newkeys & KEY_ACTION) && !(oldkeys & KEY_ACTION)) && (GetPlayerVehicleID(playerid) != 0))
				Assistance_FixOwnVehicle(playerid);
		}
	}

	// Trying to attach the closest vehicle to the towtruck when the player pressed FIRE when inside a towtruck
	// Check if the player is inside a towtruck
	if(GetVehicleModel(GetPlayerVehicleID(playerid)) == VehicleTowTruck)
	{
		// Check if the player pushed the fire-key
		if(newkeys & KEY_FIRE)
		{
			// Get the vehicle-id of the closest vehicle
			new closest = GetClosestVehicle(playerid);
			if(VehicleToPlayer(playerid, closest) < 10) // Check if the closest vehicle is within 10m from the player
				AttachTrailerToVehicle(closest, GetPlayerVehicleID(playerid)); // Attach the vehicle to the towtruck
		}
	}
	//Motorul de pe N
	if(PRESSED(KEY_NO))
    {
        if(IsPlayerInAnyVehicle(playerid))
        if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
        {
        	new vehid;
	        vehid = GetPlayerVehicleID(playerid);
	        new
			iEngine, iLights, iAlarm,
			iDoors, iBonnet, iBoot,
			iObjective;
			GetVehicleParamsEx(vehid, iEngine, iLights, iAlarm, iDoors, iBonnet, iBoot, iObjective);
			if(iEngine == 1) // Engine is on
			{
				SetVehicleParamsEx(vehid, 0, iLights, iAlarm, iDoors, iBonnet, iBoot, iObjective); // Turn it off
				SendClientMessage(playerid, 0xFFFFFFFF, "[RLT]{FF0000}Ai oprit motorul");
				return 1;
			}
			else // Engine is off
			{
			    SetVehicleParamsEx(vehid, 1, iLights, iAlarm, iDoors, iBonnet, iBoot, iObjective); // Turn it on
			    SendClientMessage(playerid, 0xFFFFFFFF, "[RLT]{FF0000}Ai pornit motorul");
			    return 1;
			}
		}
	}
	//Porbagaj Num 6
	if(PRESSED(KEY_ANALOG_RIGHT))
    {
        if(IsPlayerInAnyVehicle(playerid))
        if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
        {
        	new vehid;
	        vehid = GetPlayerVehicleID(playerid);
	        new
			iEngine, iLights, iAlarm,
			iDoors, iBonnet, iBoot,
			iObjective;
			GetVehicleParamsEx(vehid, iEngine, iLights, iAlarm, iDoors, iBonnet, iBoot, iObjective);
			if(iBoot == 1) // porbagaj inchis
			{
				SetVehicleParamsEx(vehid, iEngine, iLights, iAlarm, iDoors, iBonnet, 0, iObjective); // Turn it off
				SendClientMessage(playerid, 0xFFFFFFFF, "[RLT]{FF0000}Ai inchis portbajaul");
				return 1;
			}
			else // porbagaj deschis
			{
			    SetVehicleParamsEx(vehid, iEngine, iLights, iAlarm, iDoors, iBonnet, 1, iObjective); // Turn it on
			    SendClientMessage(playerid, 0xFFFFFFFF, "[RLT]{FF0000}Ai deschis portbagajul");
			    return 1;
			}
		}
	}
	//Capota Num 4
	if(PRESSED(KEY_ANALOG_LEFT))
    {
        if(IsPlayerInAnyVehicle(playerid))
        if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
        {
        	new vehid;
	        vehid = GetPlayerVehicleID(playerid);
	        new
			iEngine, iLights, iAlarm,
			iDoors, iBonnet, iBoot,
			iObjective;
			GetVehicleParamsEx(vehid, iEngine, iLights, iAlarm, iDoors, iBonnet, iBoot, iObjective);
			if(iBonnet == 1) // capota jos
			{
				SetVehicleParamsEx(vehid, iEngine, iLights, iAlarm, iDoors, 0, iBoot, iObjective); // Turn it off
				SendClientMessage(playerid, 0xFFFFFFFF, "[RLT]{FF0000}Ai închis capota");
				return 1;
			}
			else // capota sus
			{
			    SetVehicleParamsEx(vehid, iEngine, iLights, iAlarm, iDoors, 1, iBoot, iObjective); // Turn it on
			    SendClientMessage(playerid, 0xFFFFFFFF, "[RLT]{FF0000}Ai deschis capota");
			    return 1;
			}
		}
	}
	//Faruri de pe Y
	if(PRESSED(KEY_YES))
    {
        if(IsPlayerInAnyVehicle(playerid))
        if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
        {
        	new vehid;
	        vehid = GetPlayerVehicleID(playerid);
	        new
			iEngine, iLights, iAlarm,
			iDoors, iBonnet, iBoot,
			iObjective;
			GetVehicleParamsEx(vehid, iEngine, iLights, iAlarm, iDoors, iBonnet, iBoot, iObjective);
			if(iLights == 1) // capota jos
			{
				SetVehicleParamsEx(vehid, iEngine, 0, iAlarm, iDoors, iBonnet, iBoot, iObjective); // Turn it off
				SendClientMessage(playerid, 0xFFFFFFFF, "[RLT]{FF0000}Ai oprit farurile");
				return 1;
			}
			else // capota sus
			{
			    SetVehicleParamsEx(vehid, iEngine, 1, iAlarm, iDoors, iBonnet, iBoot, iObjective); // Turn it on
			    SendClientMessage(playerid, 0xFFFFFFFF, "[RLT]{FF0000}Ai aprins farurile");
			    return 1;
			}
		}
	}
	// Refuel a vehicle when driving a vehicle and pressing the HORN key
	// Check if the player presses the HORN key
	if ((newkeys & KEY_CROUCH) && !(oldkeys & KEY_CROUCH))
	{
		// Check if the player is driving a vehicle
		if (GetPlayerVehicleSeat(playerid) == 0)
		{
			// Loop through all ARefuelPickups
			for (new i; i < sizeof(ARefuelPickups); i++)
			{
				// Check if the player is in range of a refuelpickup
				if(IsPlayerInRangeOfPoint(playerid, 2.5, ARefuelPickups[i][pux], ARefuelPickups[i][puy], ARefuelPickups[i][puz]))
				{
					// Show a message that the player's vehicle is refuelling
					GameTextForPlayer(playerid, TXT_Refuelling, 3000, 4);
					// Don't allow the player to move again (the timer will allow it after refuelling)
					TogglePlayerControllable(playerid, 0);
				       // Start a timer (let the player wait until the vehicle is refuelled)
				    SetTimerEx("RefuelVehicle", 5000, false, "i", playerid);
				    // Stop the search
					break;
				}
			}
		}
	}

	return 1;
}
forward VehicleToPlayer(playerid,vehicleid);
// Get the distance between the vehicle and the player
public VehicleToPlayer(playerid, vehicleid)
{
	// Setup local variables
	new Float:pX, Float:pY, Float:pZ, Float:cX, Float:cY, Float:cZ, Float:distance;
	// Get the player position
	GetPlayerPos(playerid, pX, pY, pZ);
	// Get the vehicle position
	GetVehiclePos(vehicleid, cX, cY, cZ);
	// Calculate the distance
	distance = floatsqroot(floatpower(floatabs(floatsub(cX, pX)), 2) + floatpower(floatabs(floatsub(cY, pY)), 2) + floatpower(floatabs(floatsub(cZ, pZ)), 2));
	// Return the distance to the calling routine
	return floatround(distance);
}



forward GetClosestVehicle(playerid);
// Find the vehicle closest to the player
public GetClosestVehicle(playerid)
{
	// Setup local variables
	new Float:distance = 99999.000+1, Float:distance2, result = -1;
	// Loop through all vehicles
	for(new i = 0; i < MAX_VEHICLES; i++)
	{
		// First check if the player isn't driving the current vehicle that needs to be checked for it's distance to the player
		if (GetPlayerVehicleID(playerid) != i)
		{
			// Get the distance between player and vehicle
			distance2 = VehicleToPlayer(playerid, i);
			// Check if the distance is smaller than the previous distance
			if(distance2 < distance)
			{
				// Store the distance
				distance = distance2;
				// Store the vehicle-id
				result = i;
			}
		}
	}

	// Return the vehicle-id of the closest vehicle
	return result;
}
forward NitroReset();
public NitroReset()
{
	for(new i = 0; i<MAX_PLAYERS; i++)
	{
	    if(!IsPlayerInInvalidNosVehicle(i,GetPlayerVehicleID(i))) //ty @ [fackin'] luke //notice the "!"
		{
    		    new vehicle = GetPlayerVehicleID(i);
		    	AddVehicleComponent(vehicle, 1010);
		}
	}
}
//-------------------------[ IsPlayerInValidNosVehicle ]-------------------------------
IsPlayerInInvalidNosVehicle(playerid,vehicleid)
{
    #define MAX_INVALID_NOS_VEHICLES 29

    new InvalidNosVehicles[MAX_INVALID_NOS_VEHICLES] =
    {
	581,523,462,521,463,522,461,448,468,586,
	509,481,510,472,473,493,595,484,430,453,
	452,446,454,590,569,537,538,570,449
    };

    vehicleid = GetPlayerVehicleID(playerid);

    if(IsPlayerInVehicle(playerid,vehicleid))
    {
		for(new i = 0; i < MAX_INVALID_NOS_VEHICLES; i++)
		{
		    if(GetVehicleModel(vehicleid) == InvalidNosVehicles[i])
		    {
		        return true;
		    }
		}
    }
    return false;
}
// end of it!
// This function is used to debug the key-presses
stock DebugKeys(playerid, newkeys, oldkeys)
{
	// Debug keys
	if ((newkeys & KEY_FIRE) && !(oldkeys & KEY_FIRE))
		SendClientMessage(playerid, 0x0000FFFF, "You pressed the KEY_FIRE key");
	if ((newkeys & KEY_ACTION) && !(oldkeys & KEY_ACTION))
		SendClientMessage(playerid, 0x0000FFFF, "You pressed the KEY_ACTION key");
	if ((newkeys & KEY_CROUCH) && !(oldkeys & KEY_CROUCH))
		SendClientMessage(playerid, 0x0000FFFF, "You pressed the KEY_CROUCH key");
	if ((newkeys & KEY_SPRINT) && !(oldkeys & KEY_SPRINT))
		SendClientMessage(playerid, 0x0000FFFF, "You pressed the KEY_SPRINT key");
	if ((newkeys & KEY_SECONDARY_ATTACK) && !(oldkeys & KEY_SECONDARY_ATTACK))
		SendClientMessage(playerid, 0x0000FFFF, "You pressed the KEY_SECONDARY_ATTACK key");
	if ((newkeys & KEY_JUMP) && !(oldkeys & KEY_JUMP))
		SendClientMessage(playerid, 0x0000FFFF, "You pressed the KEY_JUMP key");
	if ((newkeys & KEY_LOOK_RIGHT) && !(oldkeys & KEY_LOOK_RIGHT))
		SendClientMessage(playerid, 0x0000FFFF, "You pressed the KEY_LOOK_RIGHT key");
	if ((newkeys & KEY_HANDBRAKE) && !(oldkeys & KEY_HANDBRAKE))
		SendClientMessage(playerid, 0x0000FFFF, "You pressed the KEY_HANDBRAKE key");
	if ((newkeys & KEY_LOOK_LEFT) && !(oldkeys & KEY_LOOK_LEFT))
		SendClientMessage(playerid, 0x0000FFFF, "You pressed the KEY_LOOK_LEFT key");
	if ((newkeys & KEY_SUBMISSION) && !(oldkeys & KEY_SUBMISSION))
		SendClientMessage(playerid, 0x0000FFFF, "You pressed the KEY_SUBMISSION key");
	if ((newkeys & KEY_LOOK_BEHIND) && !(oldkeys & KEY_LOOK_BEHIND))
		SendClientMessage(playerid, 0x0000FFFF, "You pressed the KEY_LOOK_BEHIND key");
	if ((newkeys & KEY_WALK) && !(oldkeys & KEY_WALK))
		SendClientMessage(playerid, 0x0000FFFF, "You pressed the KEY_WALK key");
	if ((newkeys & KEY_ANALOG_UP) && !(oldkeys & KEY_ANALOG_UP))
		SendClientMessage(playerid, 0x0000FFFF, "You pressed the KEY_ANALOG_UP key");
	if ((newkeys & KEY_ANALOG_DOWN) && !(oldkeys & KEY_ANALOG_DOWN))
		SendClientMessage(playerid, 0x0000FFFF, "You pressed the KEY_ANALOG_DOWN key");
	if ((newkeys & KEY_ANALOG_LEFT) && !(oldkeys & KEY_ANALOG_LEFT))
		SendClientMessage(playerid, 0x0000FFFF, "You pressed the KEY_ANALOG_LEFT key");
	if ((newkeys & KEY_ANALOG_RIGHT) && !(oldkeys & KEY_ANALOG_RIGHT))
		SendClientMessage(playerid, 0x0000FFFF, "You pressed the KEY_ANALOG_RIGHT key");
	if ((newkeys & KEY_UP) && !(oldkeys & KEY_UP))
		SendClientMessage(playerid, 0x0000FFFF, "You pressed the KEY_UP key");
	if ((newkeys & KEY_DOWN) && !(oldkeys & KEY_DOWN))
		SendClientMessage(playerid, 0x0000FFFF, "You pressed the KEY_DOWN key");
	if ((newkeys & KEY_LEFT) && !(oldkeys & KEY_LEFT))
		SendClientMessage(playerid, 0x0000FFFF, "You pressed the KEY_LEFT key");
	if ((newkeys & KEY_RIGHT) && !(oldkeys & KEY_RIGHT))
		SendClientMessage(playerid, 0x0000FFFF, "You pressed the KEY_RIGHT key");

	return 1;
}
stock stringContainsIP(const szStr[])
{
    new
        iDots,
        i
    ;
    while(szStr[i] != EOS)
    {
        if('0' <= szStr[i] <= '9')
        {
            do
            {
                if(szStr[i] == '.')
                    iDots++;

                i++;
            }
            while(('0' <= szStr[i] <= '9') || szStr[i] == '.' || szStr[i] == ':');
        }
        if(iDots > 2)
            return 1;
        else
            iDots = 0;

        i++;
    }
    return 0;
}

stock IsVehicleEmpty(vid)
{
	for(new i=0; i<MAX_PLAYERS; i++)
	{
		if(IsPlayerInVehicle(i, vid)) return 0;
	}
	return 1;
}

stock GetName(playerid)
{
    new szName[MAX_PLAYER_NAME];
    GetPlayerName(playerid, szName, sizeof(szName));
    return szName;
}
