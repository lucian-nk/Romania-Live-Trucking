// Debug messages
#define TXT_DebugInfo "Informatii Debug"
#define TXT_HousesFixed "Houses that have been fixed: %i"
#define TXT_LastVehicleID "Last vehicle ID: %i"
#define TXT_LastObjectID "Last object ID: %i"
#define TXT_TotalHouses "%i case"
#define TXT_TotalBusiness "%i afaceri"
#define TXT_TotalSpeedCameras "%i radare"
#define TXT_MaxSpeedCamera "Viteza maxima:"

// Define the message that's sent to all players when a player joins the server
#define TXT_PlayerJoinedServer "[RLT] {22B8DD}Jucatorul '{FF8040}%s{FF8040}'  {0080FF}a intrat pe server {00FF40}"
#define TXT_PlayerLeftServer "[RLT] {22B8DD}Jucatorul '{FF8040}%s{FF8040}' {80FF00}%i{80FF00} {0080FF}a iesit de pe server"

// Banned texts (also kick messages)
#define TXT_StillBanned "[RLT]{FF0000}Esti banat" // Define the text that the player sees when he's still banned when trying to login
#define TXT_BannedDuration "{FF0000}Ramas: Zile: %i, Ore: %i, Minute: %i, Secunde: %i" // Define the remaining ban-time text
#define TXT_KickSpeedHack "{FF0000}Ai fost dat afara de pe server deoarece ai folosit speed-hack sau air braking"
#define TXT_KickJetPackHack "{FF0000}Ai fost dat afara de pe server deoarece ai folosit Jetpack Hack"
#define TXT_KickHealthHack "{FF0000}Ai fost dat afara de pe server deoarece ai folosit Health Hack"

// Dialog buttons
#define TXT_DialogButtonCancel "Anulare" // Define the text on the "Cancel"-button for dialogs
#define TXT_DialogButtonBuy "Cumpara" // Define the text on the "Buy"-button for dialogs
#define TXT_DialogButtonSpawn "Spawn"
#define TXT_DialogButtonSelect "Selectare"
#define TXT_DialogButtonYes "Da"
#define TXT_DialogButtonNo "Nu"

// Dialog entries
#define TXT_DialogEntryNext "Urmatorul"

// The register dialog
#define TXT_DialogRegisterTitle "{00FF40}Bine ai venit pe RLT!" // Define the title-message on top of the register-dialog
#define TXT_DialogRegisterMsg "{FF0000}Inregistreaza-te pe {FF0000}Romania {00FF40}Live {FF0000}Trucking{00FF40} introducand {FF0000}o {00FF40}Parola:{FF0000}\n" // Define the actual message in the register-dialog
#define TXT_DialogRegisterButton1 "Inregistrare" // Define the text on the "register" button for the register-dialog
#define TXT_AccountRegistered "{00FF00}Contul ti-a fost creeat cu succes"
#define TXT_RegisterEnterValidPassword "Va rugam sa introduceti o parola valida pentru a va inregistra:"
#define TXT_PlayerMustRegister "{FF0000}Trebuie sa te inregistrezi pentru a te putea juca!"

// The login dialog
#define TXT_DialogLoginTitle "{00FF40}Bine ai revenit !" // Define the title-message on top of the login-dialog
#define TXT_DialogLoginMsg "{FF0000}Introdu {00FF40}Parola {FF0000}ta pentru a te putea juca\nNume: {FF0000}Romania {FFFF00}Live {FF0000}Trucking\n{FF0000}DNS: {FFFF00}TRUCKING.4GameTech.COM:2520\n{FF0000}IP: {FFFF00}94.23.208.199:2520\n{FF0000}Forum: {FFFF00}forum.4gametech.com" // Define the actual message in the login-dialog
#define TXT_DialogLoginButton1 "Login" // Define the text on the "login" button for the login-dialog
#define TXT_LoggedIn "[RLT]{00FF00}Te-ai logat cu succes, bine-ai revenit!"
#define TXT_WrongPassword "{FF0000}Ai introdus gresit parola, vei fi dat afara de pe server"
#define TXT_LoginEnterValidPassword "Logheaza-te introducandu-ti parola:"
#define TXT_PlayerMustLogin "{FF0000}Trebuie sa te loghezi pentru a putea intra pe server, in caz contrar vei fi dat afara"
#define TXT_FailedLoginProperly "{FF0000}Ai gresit parola, incearca din nou"

// The license dialog
#define TXT_DialogLicenseTitle "Licente:" // Define the title-message on top of the licenses-dialog
#define TXT_DialogLicenseList "Licenta de camionagiu $7.000.000 ( 7kk ), 30 scor)\r\nLicenta sofer de autobuz ($25.000.000 ( 25kk ), 30 scor)\r\nLicenta conducator de Tren ($550.000.000 ( 550kk ), 1000 scor)\r\nLicenta marinar ($35.000.000 ( 35kk ), 1500 scor)\r\nLicenta taximetrist ($550.000.000 ( 550kk ), 2500 scor)\r\nLicenta Padurar ($950.000.000 ( 950kk ), 3500 scor)" // Define the licenses and their price
#define TXT_PickupText "Cumpara licenta" // Defines the text that's shown above the pickup for buying licenses
#define TXT_TruckerLicenseBought "{00FF00}Ti-ai cumparat licenta de Camionagiu"
#define TXT_TruckerLicenseNotEnoughMoney "{FF0000}Ai nevoie de $15.000.000 ( 15kk ) si 30 scor pentru a-ti cumpara licenta de Camionagiu"
#define TXT_TruckerLicenseOwned "{FF0000}Detii deja licenta de Camionagiu"
#define TXT_TruckerLicenseWrongClass "{FF0000}Trebuie sa fii Camionagiu pentru a cumpara licenta de camionagiu"
#define TXT_BusLicenseBought "{00FF00}Ti-ai cumparat licenta sofer de Autobuz"
#define TXT_BusLicenseNotEnoughMoney "{FF0000}Ai nevoie de $25.000.000 ( 25kk ) si 300 scor pentru a-ti cumpara licenta sofer de Autobuz"
#define TXT_BusLicenseOwned "{FF0000}Detii deja licenta Sofer de Autobuz"
#define TXT_BusLicenseWrongClass "{FF0000}Trebuie sa fii Sofer de Autobuz pentru a-ti cumpara licenta Sofer de Autobuz"



// Dialog related for /car, /plane, ...
#define TXT_DialogCarTitle "Selecteaza masina dorita (page %i):"
#define TXT_DialogPlaneTitle "Selecteaza avionul dorit (page %i):"
#define TXT_DialogTrailerTitle "Selecteaza remorca dorita (page %i):"
#define TXT_PlayerSpawnedVehicle "{00FF00}%s a creeat un autovehicul cu id = %i"
#define TXT_ChangedWeather "{00FF00}Ai schimbat vremea cu succes")
#define TXT_DialogCommandTitle "Lista comenzilor (page %i):"

// Trucker related
#define TXT_PlayerCompletedTruckJob "{1515EA}[RLT Work] {FFFF33}Camionagiul %s a transportat %s "
#define TXT_PlayerCompletedTruckJobInfo "{FFFF33}De la %s, la %s"
#define TXT_TruckerBonusOverloaded "{00FF00}De asemenea ai primit un bonus deoarece ai transportat dublu: $%i"
#define TXT_TruckerBonusMafiaLoad "{00FF00}De asemenea ai primit un bonus deoarece ai livrat doua pachete: $%i"
#define TXT_TruckerBonusOwnVehicle "{00FF00}De asemenea ai primit un bonus deoarece ti-ai folosit propriul camion: $%i"
#define TXT_TruckerMustEnterVehicle "{FF0000}Trebuie sa intri in vehiculul anterior sau sa-ti reatasezi remorca"
#define TXT_TruckerOverloaded "{FF0000}Ai incarcat dublu! Ai grija la politie!"
#define TXT_TruckerMafiaInterested "~r~Mafia este interesta de Marfa ta~w~"
#define TXT_TruckerDialogSelectLoad "Selecteaza pachet:"
#define TXT_TruckerDialogSelectStartLoc "Selecteaza punctul de incarcare:"
#define TXT_TruckerDialogSelectEndLoc "Selecteaza punctul de descarcare:"
#define TXT_NeedVehicleToProceed "{FF0000}Trebuie sa fii in masina pentru a continua"
#define TXT_NeedTrailerToProceed "{FF0000}Ai nevoie de o Remorca"
#define TXT_NeedOnFootToProceed "{FF0000}Trebuie sa fii jos pentru a continua"




//Conducator Tren
#define TXT_SoferDialogSelectLoad "Selecteaza pachet:"
#define TXT_SoferDialogSelectStartLoc "Selecteaza punctul de incarcare:"
#define TXT_SoferDialogSelectEndLoc "Selecteaza punctul de descarcare:"
#define TXT_PlayerCompletedSoferJob "{1515EA}[Work] {FFFF33}Conducatorul de Tren %s a dus %s "
#define TXT_PlayerCompletedSoferJobInfo "{FFFF33}De la %s La %s"
#define TXT_trasporta "~w~Trasporting ~b~%s~w~ de la %s la ~r~%s~w~"
#define TXT_L1 "~r~Loading %s... ~w~Please Wait"
#define TXT_UnloadingGoods "~r~Unloading %s... ~w~Please Wait"
#define TXT_TruckerLoadingGoods "~r~Loading Your Truck... ~w~Please Wait"
#define TXT_TruckerUnloadingGoods "~r~Unloading Your Truck... ~w~Please Wait"
#define TXT_T1 "~w~Transporting ~b~%s~w~ from ~r~%s~w~ to %s"
#define TXT_P1 "{00FF00}Preia Pasageri de la %s at %s"
#define TXT_D1 "{00FF00}Du pasageri din %s la %s"
#define TXT_SoferLicenseBought "{00FF00}You have acquired your Tren's license"
#define TXT_SoferLicenseNotEnoughMoney "{FF0000}Ai nevoie de $25.000.000 si 1000 scor pentru a cumpara licenta conducator de tren"
#define TXT_SoferLicenseOwned "{FF0000}Ai deja o licenta"
#define TXT_SoferLicenseWrongClass "{FF0000}Trebuie sa fii Conducator Tren to buy a Tren's license"
#define TXT_SoferBonusOverloaded "{00FF00}You also earned a bonus for being overloaded: $%i"
#define TXT_SoferBonusMafiaLoad "{00FF00}You also earned a bonus for delivering a mafia pasager: $%i"
#define TXT_SoferBonusOwnVehicle "{00FF00}De asemenea ai primit un bonus in valoare de: $%i"
#define TXT_SoferMustEnterVehicle "{FF0000}Trebuie sa intri in vehicul sau sa reatasezi remorca"
#define TXT_SoferOverloaded "{FF0000}You have been overloaded! Avoid the police!"
#define TXT_SoferMafiaInterested "~r~Mafia Este Interesta De Un Pasager~w~"
#define TXT_SoferLoadingGoods "~r~Se incarca... ~w~Asteapta"
#define TXT_SoferUnloadingGoods "~r~Se descarca... ~w~Asteapta"



//Marinar
#define TXT_MarinarDialogSelectLoad "Selecteaza Marfa:"
#define TXT_MarinarDialogSelectStartLoc "Select loading point:"
#define TXT_MarinarDialogSelectEndLoc "Select unloading point:"
#define TXT_PlayerCompletedMarinarJob "{1515EA}[Work] {FFFF33}Marinarul %s A Dus %s "
#define TXT_PlayerCompletedMarinarJobInfo "{FFFF33}De La %s La %s"
#define TXT_UnloadingGoods "~r~Unloading %s... ~w~Please Wait"
#define TXT_T11 "~w~Transporti ~b~%s~w~ de la ~r~%s~w~ la %s"
#define TXT_P11 "{00FF00}Preia Marfa de la %s at %s"
#define TXT_D11 "{00FF00}Du Marfa din %s la %s"
#define TXT_MarinarLicenseBought "{00FF00}Felicitari Ai primit licenta de Marinar" 
#define TXT_MarinarLicenseNotEnoughMoney "{FF0000}Ai nevoie de $35.000.000 si 800 scor pentru a cumpara o licenta de Marinar"
#define TXT_MarinarLicenseOwned "{FF0000}Ai Deja Licenta"
#define TXT_MarinarLicenseWrongClass "{FF0000}You must be a Marinar to buy a Marinar's license"
#define TXT_MarinarBonusOverloaded "{00FF00}You also earned a bonus for being overloaded: $%i"
#define TXT_MarinarBonusMafiaLoad "{00FF00}Ai Primit deasemenea un bonus ca ai transportat marfa in siguranta: $%i"
#define TXT_MarinarBonusOwnVehicle "{00FF00}You also earned a bonus: $%i"
#define TXT_MarinarMustEnterVehicle "{FF0000}You must enter your vehicle or re-attach your trailer"
#define TXT_MarinarOverloaded "{FF0000}You have been overloaded! Avoid the police!"
#define TXT_MarinarMafiaInterested "~r~Mafia Vrea Sa Te Fure~w~"
#define TXT_MarinarLoadingGoods "~r~Loading... ~w~Please Wait"
#define TXT_MarinarUnloadingGoods "~r~Unloading... ~w~Please Wait"





//Taximetrist
#define TXT_TaxiDialogSelectLoad "Selecteaza Pasageri:"
#define TXT_TaxiDialogSelectStartLoc "Select loading point:"
#define TXT_TaxiDialogSelectEndLoc "Select unloading point:"
#define TXT_PlayerCompletedTaxiJob "{1515EA}[Work] {FFFF33}Taximetristul %s A Dus pe %s "
#define TXT_PlayerCompletedTaxiJobInfo "{FFFF33}De La %s La %s"
#define TXT_T12 "~w~Duci pe ~b~%s~w~ de la ~r~%s~w~ la %s"
#define TXT_T14 "~w~Duci pe ~b~%s~w~ de la %s la ~r~%s~w~"
#define TXT_P12 "{00FF00}Preia pe %s de la %s"
#define TXT_D12 "{00FF00}Du Pasageru %s la %s"
#define TXT_TaxiLicenseBought "{00FF00}Felicitari Ai primit licenta de Taxi" 
#define TXT_TaxiLicenseNotEnoughMoney "{FF0000}Ai nevoie de $55.000.000 si 500 scor pentru a cumpara o licenta de Taximetrist"
#define TXT_TaxiLicenseOwned "{FF0000}Ai Deja Licenta"
#define TXT_TaxiLicenseWrongClass "{FF0000}You must be a Taxi to buy a Taxi's license"
#define TXT_TaxiBonusOverloaded "{00FF00}You also earned a bonus Mita: $%i"
#define TXT_TaxiBonusMafiaLoad "{00FF00}Ai Primit deasemenea un bonus ca ai fost rapid: $%i"
#define TXT_TaxiBonusOwnVehicle "{00FF00}You also earned a bonus: $%i"
#define TXT_TaxiMustEnterVehicle "{FF0000}You must enter your vehicle"
#define TXT_TaxiOverloaded "{FF0000}Ai luat Mita de la un pasager! Evita Politia FBI!"
#define TXT_TaxiMafiaInterested "~r~[Radio] Ai Grije la Mafie Se aude ca vor sa te fure~w~"
#define TXT_TaxiLoadingGoods "~r~Pasagerul Urca~w~Asteapta"
#define TXT_TaxiUnloadingGoods "~r~Pasagerul Coboara ~w~Asteapta"






//Padurar
#define TXT_PadurarDialogSelectLoad "Selecteaza Marfa:"
#define TXT_PadurarDialogSelectStartLoc "Select loading point:"
#define TXT_PadurarDialogSelectEndLoc "Select unloading point:"
#define TXT_PlayerCompletedPadurarJob "{1515EA}[Work] {FFFF33}Padurarul %s A Dus %s "
#define TXT_PlayerCompletedPadJobInfo "{FFFF33}De La %s La %s"
#define TXT_T13 "~w~Duci ~b~%s~w~ de la ~r~%s~w~ la %s"
#define TXT_T15 "~w~Duci ~b~%s~w~ de la %s la ~r~%s~w~"
#define TXT_P13 "{00FF00}Preia %s de la %s"
#define TXT_D13 "{00FF00}Du  %s la %s"
#define TXT_PadurarLicenseBought "{00FF00}Felicitari Ai primit licenta de Padurar" 
#define TXT_PadurarLicenseNotEnoughMoney "{FF0000}Ai nevoie de $95.000.000 si 700 scor pentru a cumpara o licenta de Padurar"
#define TXT_PadurarLicenseOwned "{FF0000}Ai Deja Licenta"
#define TXT_PadurarLicenseWrongClass "{FF0000}You must be a Padurar to buy a Padurar's license"
#define TXT_PadurarBonusOverloaded "{00FF00}You also earned a bonus Mita: $%i"
#define TXT_PadurarBonusMafiaLoad "{00FF00}Ai Primit deasemenea un bonus ca ai fost rapid: $%i"
#define TXT_PadurarBonusOwnVehicle "{00FF00}You also earned a bonus: $%i"
#define TXT_PadurarMustEnterVehicle "{FF0000}You must enter your vehicle"
#define TXT_PadurarOverloaded "{FF0000}Ai taiat un copac nemarcat! Evita Politia FBI!"
#define TXT_PadurarMafiaInterested "~r~Ai Grije la Mafie Se aude ca vor sa te fure~w~"
#define TXT_PadurarLoadingGoods "~r~Se Incarca ~w~Asteapta"
#define TXT_PadurarUnloadingGoods "~r~Se descarca ~w~Asteapta"





















// Busdriver related
#define TXT_PlayerCompletedBusLine "{FFFFFF}Soferul de autobuz {FF00FF}%s{FFFFFF} a completat linia {0000FF}%i{FFFFFF}"
#define TXT_BusDriverMissionPassed "Mission ended" // Define the game-text that shows when the player passed a busdriver mission
#define TXT_BusDriverJobInfo "~w~Line ~y~%i~w~ (~g~%s~w~): ~b~%i~w~ on bus"
#define TXT_BusDriverBusStopInfo "~w~Line ~y~%i~w~ (~g~%s~w~): ~b~%i~w~ on bus, ~b~%i~w~ on busstop"
#define TXT_BusDriverReward "~g~You've earned $%i~w~"
#define TXT_BusDriverMustEnterBus "{FF0000}You must enter your bus"
#define TXT_SelectBusRoute "Select busroute:"
#define TXT_BusdriverAlreadyDoingJob "{FF0000}You're already doing a job"

// Mafia related
#define TXT_PlayerCompletedMafiaJob "{FFFFFF}Mafia {FF00FF}%s{FFFFFF} A transportat cu suces {0000FF}%s{FFFFFF}"
#define TXT_PlayerCompletedMafiaJobInfo "de la {00FF00}%s{FFFFFF} la {00FF00}%s{FFFFFF}"
#define TXT_MafiaMustEnterVehicle "{FF0000}You must enter your vehicle"
#define TXT_MafiaDeliverStolenLoad "~w~Bring the ~b~stolen load~w~ to the ~r~mafia-hideout~w~"
#define TXT_MafiaDeliveredStolenLoad "{00FF00}You delivered a stolen mafia-load, you earned $5000"


// Police related
#define TXT_PoliceWarnPlayer "~r~Aci Politia! Trage pe Dreapta!~w~"
#define TXT_PoliceFinedPlayerReward "{00FF00}Ai Amendat pe %s Si ai primit $%i"
#define TXT_PlayerGotFinedByPolice "{FF0000}Ai fost prins de politistul %s Si ai platit o Amenda de $%i"
#define TXT_PoliceFinedPlayer "{00FF00}Politistul %s A amendat pe %s"
#define TXT_PoliceJailedPlayerReward "{00FF00}You have jailed %s and earned $%i"
#define TXT_PlayerGotJailedByPolice "{FF0000}Ai fost bagat la puscarie de %s pentru %i minutes"
#define TXT_PoliceJailedPlayer "{00FF00}Politistu %s A bagat la puscarie pe %s Pentru %i minutes"




//FBY related
#define TXT_FBYWarnPlayer "~r~Aci FBY ! Opreste Automobilul !~w~"
#define TXT_FBYFinedPlayerReward "{00FF00}Ai amendat pe %s si ai primit $%i"
#define TXT_PlayerGotFinedByFBY "{FF0000}Ai fost prins de {1515EA}[FBY]%s {FF0000}si ai platit o amenda de $%i"
#define TXT_FBYFinedPlayer "{1515EA}[FBY]%s {00FF00}A amendat pe %s"
#define TXT_FBYJailedPlayerReward "{00FF00}Lai bagat la puscar pe %s si ai primit $%i"
#define TXT_PlayerGotJailedByFBY "{FF0000}Ai fost prins si bagat la puscarie de %s timp de %i minutes"
#define TXT_FBYJailedPlayer "{1515EA}[FBY]%s {00FF00}A la bagat la puscarie pe %s timp de %i minutes"



// Pilot related
#define TXT_PlayerCompletedPilotJob "{1515EA}[Work] {00FFFF}Pilotul %s A Trasportat Cu Suces %s"
#define TXT_PlayerCompletedPilotJobInfo "De La %s La %s"


// Gunoier related
#define TXT_PlayerCompletedGJob "{0000FF}[Work] {800000}Gunoierul %s A Dus %s"
#define TXT_PlayerCompletedGJobInfo "{800000}De La %s La %s"




// Medic related
#define TXT_PlayerCompletedMedicJob "{FFFFFF}Medicu {FF00FF}%s{FFFFFF} A dus pe {0000FF}%s{FFFFFF}"
#define TXT_PlayerCompletedMedicJobInfo "de la {00FF00}%s{FFFFFF} la {00FF00}%s{FFFFFF}"
#define TXT_TransportingFromToDeliver2 "~w~Salveaza pe ~b~%s~w~ din %s si duo/l la ~r~%s~w~"
#define TXT_TransportingFromToPickup2 "~w~Salveaza pe ~b~%s~w~ din ~r~%s~w~ si duo/l la %s"
#define TXT_UnloadingGoods2 "~r~Spitalu preia ranitul/a %s... ~w~Asteapta"
#define TXT_LoadingGoods2 "~r~Se preia ranitul/a %s... ~w~Asteapta"


// Courier related
#define TXT_CourierMustEnterVehicle "{FF0000}You must enter your vehicle"
#define TXT_PlayerCompletedCourierJob "{FFFFFF}Courier {FF00FF}%s{FFFFFF} succesfully delivered {0000FF}%i{FFFFFF} packages"
#define TXT_PackageDeliveredGameText "Package delivered"
#define TXT_PackageDeliveredMessage "{00FF00}Package delivered"



//Pizza Boy related
#define TXT_PboyMustEnterVehicle "{FF0000}Trebuie sa intri in masina"
#define TXT_PlayerCompletedPboyJob "{FFFFFF}Pizza Boy {FF00FF}%s{FFFFFF} succesfully delivered {0000FF}%i{FFFFFF} Pizza"
#define TXT_PackageDeliveredpizzaGameText "Pizza Livrata"
#define TXT_PackageDeliveredpizzaMessage "{00FF00}Pizza Livrata"



// Roadworker related
#define TXT_RepairSpeedcamera "~w~Repara ~r~radarul~w~ indicat"
#define TXT_TowBrokenVehicle "~w~Tow the ~r~broken vehicle~w~ near ~b~%s~w~ to the shredder"
#define TXT_DeliverBrokenVehicle "~w~Tow the broken vehicle near ~b~%s~w~ to the ~r~shredder~w~"
#define TXT_RoadworkerMustEnterVehicle "{FF0000}You must enter your vehicle or re-attach your trailer"
#define TXT_RoadworkerMissionPassed "Mission ended" // Define the game-text that shows when the player passed a roadworker mission

// Job related, for all classes
#define TXT_RewardJob "{FF0000}Ai terminat misiunea. Drept ca rasplata ai primit $%i"
#define TXT_FailedMission "~w~Ai ~r~pierdut~w~ misiunea. Ai platit ~y~$1000~w~ ca despagubire." // Define game-text when player fails a mission

// Class related
#define TXT_ClassTrucker "Truck driver" // Define the game-text that shows when the player is choosing classes (this one = trucker)
#define TXT_ClassBusDriver "Bus driver" // Define the game-text that shows when the player is choosing classes (this one = bus-driver)
#define TXT_ClassPilot "Pilot" // Define the game-text that shows when the player is choosing classes (this one = pilot)
#define TXT_ClassMedic "Medic" // Define the game-text that shows when the player is choosing classes (this one = Medic)
#define TXT_ClassPolice "Police" // Define the game-text that shows when the player is choosing classes (this one = police)
#define TXT_ClassFBY "FBY" // Define the game-text that shows when the player is choosing classes (this one = FBY)
#define TXT_ClassMafia "Mafia" // Define the game-text that shows when the player is choosing classes (this one = mafia)
#define TXT_ClassCourier "Courier" // Define the game-text that shows when the player is choosing classes (this one = courier)
#define TXT_ClassPboy "Pizza Boy" // Define the game-text that shows when the player is choosing classes (this one = Pizza Boy)
#define TXT_ClassAssistance "Assistance" // Define the game-text that shows when the player is choosing classes (this one = assistance)
#define TXT_ClassRoadWorker "Road worker" // Define the game-text that shows when the player is choosing classes (this one = roadworker)
#define TXT_ClassSofer "Conducator Tren" // Define the game-text that shows when the player is choosing classes (this one = Conducator Tren)
#define TXT_ClassG "Gunoier" // Define the game-text that shows when the player is choosing classes (this one = Gunoier)
#define TXT_ClassMarinar "Marinar" // Define the game-text that shows when the player is choosing classes (this one = Gunoier)
#define TXT_ClassTaxi "Taximetrist" // Define the game-text that shows when the player is choosing classes (this one = Taximetrist)
#define TXT_ClassPadurar "Padurar" // Define the game-text that shows when the player is choosing classes (this one = Padurar)





// No-job texts for all classes
#define Trucker_NoJobText "Scrie \"~y~/work~w~\" pentru a incepe munca"
#define BusDriver_NoJobText "Scrie \"~y~/work~w~\" pentru a incepe munca"
#define Pilot_NoJobText "Scrie \"~y~/work~w~\" pentru a incepe munca"
#define Medic_NoJobText "Scrie \"~y~/work~w~\" pentru a incepe munca"
#define Police_NoJobText "~r~'RMB'~w~ fine (jos), ~r~'LCTRL'~w~ avertizare (intr-un vehicul)"
#define FBY_NoJobText "~r~'RMB'~w~ fine (jos), ~r~'LCTRL'~w~ avertizare (intr-un vehicul)"
#define Mafia_NoJobText "Scrie \"~y~/work~w~\" pentru a incepe munca"
#define Courier_NoJobText "Scrie \"~y~/work~w~\" pentru a incepe munca"
#define Pboy_NoJobText "Scrie \"~y~/work~w~\" pentru a incepe munca"
#define Assistance_NoJobText "~r~'RMB'~w~ benzina, ~r~'LCTRL'~w~ reparatii"
#define RoadWorker_NoJobText "Scrie \"~y~/work~w~\" pentru a incepe munca"
#define Sofer_NoJobText "Scrie \"~y~/work~w~\" pentru a incepe munca"
#define Marinar_NoJobText "Scrie \"~y~/work~w~\" pentru a incepe munca"
#define Taxi_NoJobText "Scrie \"~y~/work~w~\" pentru a incepe munca"
#define Padurar_NoJobText "Scrie \"~y~/work~w~\" pentru a incepe munca"


// Command related
#define TXT_PlayerRescued "{0000FF}Ai fost respawnat. Ai pierdut $200"

// Fuel related
#define TXT_Refuelling "~g~Se realimenteaza..." // Define the game-text that shows when you're refuelling your vehicle
#define TXT_PickupRefuel "Apasa H\n pentru a Realimenta"
#define TXT_RefuelledVehicle "{FF0000}Ai realimentat, cost: $%i"
#define TXT_CannotRefuelVehicle "{FF0000}Nu ai destui bani"

// Gametexts for loading/unloading
#define TXT_LoadingGoods "~r~Se Incarca %s... ~w~Asteapta"
#define TXT_UnloadingGoods "~r~Unloading %s... ~w~Please Wait"
#define TXT_TruckerLoadingGoods "~r~Loading Your Truck... ~w~Please Wait"
#define TXT_TruckerUnloadingGoods "~r~Unloading Your Truck... ~w~Please Wait"
#define TXT_TransportingFromToPickup "~w~Transporting ~b~%s~w~ from ~r~%s~w~ to %s"
#define TXT_TransportingFromToDeliver "~w~Transporting ~b~%s~w~ from %s to ~r~%s~w~"
#define TXT_HaulingCargoFromToPickup "~w~Duci ~b~%s~w~ de la ~r~%s~w~ la %s"
#define TXT_HaulingCargoFromToDeliver "~w~Duci ~b~%s~w~ de la %s la ~r~%s~w~"
#define TXT_PickupCargoAt "{00FF00}Pickup the %s de la %s"
#define TXT_DeliverCargoTo "{00FF00}Deliver the %s la %s"

// Cardealer related
#define TXT_PickupCarDealer "Foloseste \"/rentcar\"\n pentru a inchiria o masina"
#define TXT_BuyRentCarEmptyList "{FF0000}Aceasta este goala, administratorul a dezactivat vehiculele de aceasta clasa"
#define TXT_RentBike "Inchiriaza biciclete:"
#define TXT_RentBoat "Inchiriaza barci:"
#define TXT_RentConvertible "Rent a convertible:"
#define TXT_RentHelicopter "Rent a helicopter:"
#define TXT_RentIndustrial "Rent an industrail vehicle:"
#define TXT_RentLowRider "Rent a low-rider:"
#define TXT_RentOffRoad "Rent an off-road vehicle:"
#define TXT_RentPlane "Inchiriaza avioane:"
#define TXT_RentPublicService "Rent a public service vehicle:"
#define TXT_RentRC "Rent a RC vehicle:"
#define TXT_RentSaloon "Rent a saloon vehicle:"
#define TXT_RentSport "Rent a sport vehicle:"
#define TXT_RentStationWagon "Rent a station wagon:"
#define TXT_RentTrailer "Rent a trailer:"
#define TXT_RentUnique "Rent a unique vehicle:"
#define TXT_AlreadyRentedVehicle "{FF0000}You already had a rented vehicle, but it has been replaced by the new one"
#define TXT_PlayerRentsVehicle "{00FF00}You have rented a {FFFF00}%s{00FF00} for ${FFFF00}%i{00FF00}"
#define TXT_RentingTooExpensive "{FF0000}Nu detii banii necesari pentru cumpararea acestui vehicul"
#define TXT_BuyBike "Buy a bike:"
#define TXT_BuyBoat "Buy a boat:"
#define TXT_BuyConvertible "Buy a convertible:"
#define TXT_BuyHelicopter "Buy a helicopter:"
#define TXT_BuyIndustrial "Buy an industrail vehicle:"
#define TXT_BuyLowRider "Buy a low-rider:"
#define TXT_BuyOffRoad "Buy an off-road vehicle:"
#define TXT_BuyPlane "Buy a plane:"
#define TXT_BuyPublicService "Buy a public service vehicle:"
#define TXT_BuyRC "Buy a RC vehicle:"
#define TXT_BuySaloon "Buy a saloon vehicle:"
#define TXT_BuySport "Buy a sport vehicle:"
#define TXT_BuyStationWagon "Buy a station wagon:"
#define TXT_BuyTrailer "Buy a trailer:"
#define TXT_BuyUnique "Buy a unique vehicle:"



// Jail related
#define TXT_JailTimer "~w~Arestat: ~r~%i~w~"

// Speedometer related
#define TXT_SpeedometerSpeed "~w~Viteza: ~y~%i~w~ kmh"
#define TXT_SpeedometerFuel "~w~Benzina: %s"
#define TXT_SpeedometerCannotUseVehicle "{FF0000}Nu poti folosi acest vehicul, este detinut de: \"{FFFF00}%s{FF0000}\""
#define TXT_SpeedometerClampedVehicle "{FF0000}This vehicle is clamped, you cannot use it"
#define TXT_SpeedometerClampedVehicle2 "{FF0000}You can unclamp it by using {FFFF00}/unclamp"
#define TXT_PlayerCaughtSpeeding "{FF0000}Ai fost prins de radar. (Viteza Ta: %d km/h, iar Viteza Limita: %d km/h)"

// Toll-gate related
#define TXT_PlayerPaysToll "Ai platit $%i la vama"

// Convoy related
#define TXT_PlayerStartsConvoy "Jucatorul {00FF00}%s{FFFFFF} a deschis un {00FF00}convoy{FFFFFF}, alatura-te lui folosind comanda \"/convoy\""
#define TXT_PlayerJoinedConvoy "Jucatorul {00FF00}%s{FFFFFF} a intrat in convoy"
#define TXT_YouJoinedConvoy "{00FF00}Ai intrat in convoy"
#define TXT_WaitingLeaderJob "Se asteapta ca liderul sa dea startul"
#define TXT_WaitingMembersToLoadCargo "Se asteapta ca toti sa incarce"
#define TXT_WaitingMembersToUnLoadCargo "Se asteapta ca toti sa descarce"
#define TXT_ConvoyFull "{FF0000}Acest convoy este a atins limita maxima a jucatorilor"
#define TXT_ConvoyEnRoute "This convoy is en-route to it's destination, you cannot join it"
#define TXT_LeaderCancelledConvoy "{FF0000}Liderul a inchis convoy-ul"
#define TXT_MeetOtherConvoyMembers "{00FF00}Meet the other members of the convoy at the loading point"
#define TXT_ConvoyDistanceForLeader "{00FF00}Fiecare trebuie sa stea la cel mult 500m de tine"
#define TXT_ConvoyDistanceForMember "{00FF00}Stai la cel mult 500m de liderul convoy-ului"
#define TXT_MemberNeedsCargoTrailer "Ai Nevoi de o remorca Cargo"
#define TXT_MemberNeedsOreTrailer "Ai Nevoie de o remorca Ore"
#define TXT_MemberNeedsFluidsTrailer "Ai Nevoie de o Cisterna"
#define TXT_AllMembersSameTrailer "{00FF00}Toti membrii convoy-ului au aceeasi remorca, Convoy-ul poate Continua"
#define TXT_AllMembersNotSameTrailer "{FF0000}Unii membri ai Convoy-ului nu au aceeasi remorca precum liderul"
#define TXT_AllMembersLoadedCargo "{00FF00}Toata lumea a incarcat, Convoy-ul este gata De plecare catre punctul De Descarcare"
#define TXT_MemberKickedByDistance "{FF0000}Nu ai tinut pasul cu Celalalti colegi din convoy asa ca ai primit Kick"
#define TXT_MemberFellBehind "Jucatorul {00FF00}%s{FFFFFF} fell behind and is kicked from the convoy"
#define TXT_FinishedConvoy "{00FF00}Ai terminat convoy-ul. Drept rasplata ai primit: $%i"
#define TXT_LeaderInfoBar "Membrii: ~g~%i~w~, Cel mai Aproape: ~g~%s~w~, Distanta: ~r~%3.1f~w~"
#define TXT_MemberInfoBar "Lider: ~r~%s~w~, Distanta: ~r~%3.1f~w~, Membrii: ~r~%i~w~"
#define TXT_CannotJoinJobStarted "{FF0000}You already started a job, you cannot create or join a convoy"
#define TXT_ConvoyAllreadyJoined "{FF0000}Esti Deja in Convoy"
#define TXT_ConvoyNeedsTruckerClass "{FF0000}Trebuie sa fii camionagiu Pentru a face un Convoy"


// Timed messages
#define TXT_TimedRefuel "PONT {1515EA}[RLT] {E6D11A}Ai ramas fara benzina? Du-te la o Bezinarie Si apasa H"
#define TXT_TimedConvoy "{1515EA}[RLT] {E6D11A}In fiecare saptamana se va actualiza gamemodeul"
#define TXT_TimedGohome "PONT {1515EA}[RLT] {E6D11A}Folosind comanda \"/gohome\" poti ajunge la casa ta"
#define TXT_TimedLicense "PONT {1515EA}[RLT] {E6D11A}Spune adio misiunilor random. Mergi chiar acum la scoala de soferi din SF Si achizitioneaza o Licenta"
#define TXT_TimedSpeedTraps "PONT {1515EA}[RLT] {E6D11A}Ai grije la radare! Politia / FBI este cu ochii pe tine"
#define TXT_TimedTip3 "PONT {1515EA}[RLT] {E6D11A}Iti place serverul? Adauga-l la favorite: 94.23.208.199:2494"






// House-related
#define TXT_DefaultHouseName "Casa lui %s"
#define TXT_PlayerBoughtHouse "{33FF33}Ai cumparat casa la pretul de ${FFCC33}%i"
#define TXT_PlayerOwnsMaxHouses "{FF0000}Ai atins numarul maxim admis de case pe jucator"
#define TXT_ExitHouseReloadEnv "Se incarca mapa..."
#define TXT_PickupHouseOwned "%s\nPropietar: %s\nNivelul Casei: %i\n/enter"
#define TXT_PickupHouseForSale "De Vanzare\n$%i\nNivel maxim: %i\n/buyhouse"
#define TXT_DialogOldHouseName "Vechiul nume al casei: %s"
#define TXT_DialogEnterNewHouseName "Redenumeste casa"
#define TXT_DialogSelectHouseUpgrade "Selecteaza:"
#define TXT_HouseReachedMaxLevel "{FF0000}Casa ta a atins nivelul maxim admis, nu o mai poti moderniza"
#define TXT_DialogBuyCarSelectClass "Clasa Vehiculului:"
#define TXT_HouseHasMaxVehicles "{FF0000}This house has the maximum amount of house-cars already"
#define TXT_AlreadyBoughtRecentVehicle "{FF0000}You already bought a vehicle recently, use \"/getcar\" and \"/park\" to park it before buying a new one"
#define TXT_EmptyCarSlot "%s{FFFFFF}Empty car-slot{FFFFFF}\n"
#define TXT_SelectVehicleToSell "Selecteaza masina de vanzare:"
#define TXT_SelectVehicleToGet "Select vehicle to port to your location:"
#define TXT_NoHouseVehicles "{FF0000}This house has no vehicles assigned to it"
#define TXT_SureSellHouse "Are you sure you want to sell your house for $%i?"
#define TXT_AreYouSure "Esti sigur?"
#define TXT_CannotSellHouseWithCars "{FF0000}Nu poti vinde o casa ce inca are masini"
#define TXT_PlayerUpgradedHouse "{00FF00}Ti-ai modernizat casa la levelul %i pentru $%i"
#define TXT_CannotAffordUpgrade "{FF0000}Nu ai banii necesari"
#define TXT_NoHouseInSlot "{FF0000}You don't have a house in this house-slot"
#define TXT_ChangedHouseName "{00FF00}You've changed the name of your house"
#define TXT_PlayerBoughtVehicle "{00FF00}Ti-ai cumparat {FFFF00}%s{00FF00} pentru ${FFFF00}%i{00FF00}"
#define TXT_PlayerMustUseGetcarAndPark "{00FF00}Now get outside and use \"{FFFF00}/getcar{00FF00}\" to spawn it, then use \"{FFFF00}/park{00FF00}\" to park it near your house"
#define TXT_PlayerMustUsePark "{00FF00}Ai adus masina la tine foloseste \"{FFFF00}/park{00FF00}\" pt a ramine acolo"
#define TXT_CannotAffordVehicle "{FF0000}You can't afford to buy this vehicle"
#define TXT_PlayerSoldHouse "{00FF00}Ti-ai vandut casa"
#define TXT_PlayerSoldVehicle "{00FF00}Ti-ai vandut {FFFF00}%s{00FF00} pentru ${FFFF00}%i{00FF00}"
#define TXT_NoVehicleInSlot "{FF0000}No vehicle exists in this vehicle-slot"
#define TXT_DialogTitleBuyInsurance "Cumperi asigurare?"
#define TXT_DialogBuyInsurance "Esti Sigur ca Vrei sa Cumperi Asigurarea cu $%i?"
#define TXT_HouseAlreadyHasInsurance "{FF0000}Aceasta casa este deja asigurata"
#define TXT_PlayerBoughtInsurance "{00FF00}Ti-ai cumparat asigurare pentru toate vehiculele acestei case pentru $%i"
#define TXT_CannotAffordInsurance "{FF0000}Nu Iti Permiti Licenta"





// Business related
#define TXT_PickupBusinessOwned "%s\nProprietar: %s\nNivel afacere: %i\n/enter"
#define TXT_PickupBusinessForSale "%s\nDe vanzare\n$%i\nVenit: $%i\n/buybus - Cumpara"
#define TXT_DefaultBusinessName "Afacerea lui %s"
#define TXT_PlayerBoughtBusiness "{33FF33}Ai cumparat afacerea in valoare de ${FFCC33}%i"
#define TXT_PlayerOwnsMaxBusinesses "{FF0000}Ai atins numarul maxim admis al afaceriilor pe jucator"
#define TXT_NoBusinessInSlot "{FF0000}Nu detii o afacere in acest slot"
#define TXT_DialogOldBusinessName "Vechiul nume al afacerii: %s"
#define TXT_DialogEnterNewBusinessName "Da un alt nume afacerii tale"
#define TXT_ChangedBusinessName "{00FF00}Ai schimbat numele afacerii"
#define TXT_BusinessReachedMaxLevel "{FF0000}Afacerea ta a atins nivelul maxim admis, nu o mai poti moderniza"
#define TXT_SureSellBusiness "Esti sigur ca vrei sa-ti vinzi afacerea pentru $%i?"
#define TXT_PlayerSoldBusiness "{00FF00}Ti-ai vandut afacerea"

