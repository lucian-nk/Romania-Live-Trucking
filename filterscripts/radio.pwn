#include 					<a_samp>
#include 					<zcmd>
//=====================================//
#define		DIALOG_RADIO 	2012
//=====================================//
new string[256], pName[MAX_PLAYER_NAME];

public OnFilterScriptInit()
{
	print("\n--------------------------------------");
	print("DuReX's Radio Filterscript v1.0 loaded!");
	print("--------------------------------------\n");
	return 1;
}
public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(dialogid == DIALOG_RADIO)
    {
        if(response)
        {
            switch(listitem)
			{
 				case 0: return cmd_radioorange(playerid);
				case 1:return cmd_radiohit(playerid);
				case 2: return cmd_contactfm(playerid);
				case 3: return cmd_radiohiphop(playerid);
				case 4: return cmd_romanianmanele(playerid);
				case 5: return cmd_radioliveromania(playerid);
				case 6: return cmd_profm(playerid);
				case 7: return cmd_radiowish(playerid);
				case 8: return cmd_radiotube(playerid);
				case 9: return cmd_radiomafia(playerid);
				case 10: return cmd_greudedifuzat(playerid);
				case 11: return cmd_radiostarmusik(playerid);
				case 12: return cmd_stopradio(playerid);
        	}
   		}
        return 1;
    }
 	return 0;
}
CMD:radio(playerid, params[])
{
    new sradio[1900];
    strcat(sradio, "{FFFFFF}Radio ORANGE {FF0000}\t\t\t /radioorange\n", 1900 );
    strcat(sradio, "{FFFFFF}Radio HiT FM {FF0000}\t\t\t /radiohit\n", 1900 );
    strcat(sradio, "{FFFFFF}Contact FM {FF0000}\t\t\t /contactfm\n", 1900 );
    strcat(sradio, "{FFFFFF}Radio Romanian Hip-Hop {FF0000}\t /radiohiphop\n", 1900 );
    strcat(sradio, "{FFFFFF}Radio Romanian Manele {FF0000}\t /romanianmanele\n", 1900 );
    strcat(sradio, "{FFFFFF}Radio Romanian Popular {FF0000}\t /romanianpopular\n", 1900 );
    strcat(sradio, "{FFFFFF}Pro FM {FF0000}\t\t\t\t /profm\n", 1900 );
    strcat(sradio, "{FFFFFF}Radio GMusic Rock {FF0000}\t\t /gmusic\n", 1900 );
    strcat(sradio, "{FFFFFF}radio-tube.pl Dubstep {FF0000}\t\t /radiotube\n", 1900 );
    strcat(sradio, "{FFFFFF}Radio Mafia {FF0000}\t\t\t /radiomafia\n", 1900 );
    strcat(sradio, "{FFFFFF}Radio Greu de Difuzat {FF0000}\t\t /greudedifuzat\n", 1900 );
    strcat(sradio, "{FFFFFF}Radio Star Musik {FF0000}\t\t /radiostarmusik\n", 1900 );
    strcat(sradio, "{FF0000}Opreste radioul \t\t /stopradio", 1900 );
 	ShowPlayerDialog(playerid, DIALOG_RADIO, DIALOG_STYLE_LIST, "{FFFFFF}Meniu {FF0000}Radio", sradio, "Selecteaza","Inchide");
	return 1;
}
CMD:radiohit(playerid)
{
    GetPlayerName(playerid,pName,MAX_PLAYER_NAME);
    format(string,sizeof string,"{FF0000}%s {FFFFFF}asculta {FF0000}Radio HiT FM (/radiohit)",pName);
    SendClientMessageToAll(0xFFFFFFAA,string);
	PlayAudioStreamForPlayer(playerid, "http://www.radio-hit.ro/asculta.m3u");
	GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~n~~w~buffering ~r~radio hit~w~...", 1500, 3);
	return 1;
}
CMD:radioorange(playerid)
{
    GetPlayerName(playerid,pName,MAX_PLAYER_NAME);
    format(string,sizeof string,"{FF0000}%s {FFFFFF}asculta {FF0000}Radio ORANGE (/radioorange)",pName);
    SendClientMessageToAll(0xFFFFFFAA,string);
	PlayAudioStreamForPlayer(playerid, "http://s13.myradiostream.com:21824");
	GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~n~~w~buffering ~r~radio ORANGE~w~...", 1500, 3);
	return 1;
	}
CMD:contactfm(playerid)
{
	GetPlayerName(playerid,pName,MAX_PLAYER_NAME);
    format(string,sizeof string,"{FF0000}%s {FFFFFF}asculta {FF0000}Contact FM (/contactfm)",pName);
    SendClientMessageToAll(0xFFFFFFAA,string);
	PlayAudioStreamForPlayer(playerid, "http://www.contactfm.ro/listen.pls");
	GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~n~~w~buffering ~r~contact fm~w~...", 1500, 3);
	return 1;
}
CMD:radiohiphop(playerid)
{
	GetPlayerName(playerid,pName,MAX_PLAYER_NAME);
    format(string,sizeof string,"{FF0000}%s {FFFFFF}asculta {FF0000}Radio Hip-Hop (/radiohiphop)",pName);
    SendClientMessageToAll(0xFFFFFFAA,string);
	PlayAudioStreamForPlayer(playerid, "http://radioromanian.net/hiphop.pls");
	GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~n~~w~buffering ~r~radio hip-hop~w~...", 1500, 3);
	return 1;
}
CMD:radioliveromania(playerid)
{
    GetPlayerName(playerid,pName,MAX_PLAYER_NAME);
    format(string,sizeof string,"{FF0000}%s {FFFFFF}asculta {FF0000}RadioLiveRomania (/radiolive)",pName);
    SendClientMessageToAll(0xFFFFFFAA,string);
	PlayAudioStreamForPlayer(playerid, "http://95.64.36.139:9875");
	GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~n~~w~buffering ~r~radio Live Romania~w~...", 1500, 3);
	return 1;
}
CMD:romanianmanele(playerid)
{
    GetPlayerName(playerid,pName,MAX_PLAYER_NAME);
    format(string,sizeof string,"{FF0000}%s {FFFFFF}asculta {FF0000}Radio Romanian Manele (/romanianmanele)",pName);
    SendClientMessageToAll(0xFFFFFFAA,string);
	PlayAudioStreamForPlayer(playerid, "http://radioromanian.net/manele.pls");
	GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~n~~w~buffering ~r~radio romanian manele~w~...", 1500, 3);
	return 1;
}
CMD:profm(playerid)
{
    GetPlayerName(playerid,pName,MAX_PLAYER_NAME);
    format(string,sizeof string,"{FF0000}%s {FFFFFF}asculta {FF0000}Pro FM (/profm)",pName);
    SendClientMessageToAll(0xFFFFFFAA,string);
	PlayAudioStreamForPlayer(playerid, "http://stream.profm.ro:8012/profm.mp3");
	GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~n~~w~buffering ~r~pro fm~w~...", 1500, 3);
	return 1;
}
CMD:radiowish(playerid)
{
    GetPlayerName(playerid,pName,MAX_PLAYER_NAME);
    format(string,sizeof string,"{FF0000}%s {FFFFFF}asculta {FF0000}Radio Wish (/radiowish)",pName);
    SendClientMessageToAll(0xFFFFFFAA,string);
	PlayAudioStreamForPlayer(playerid, "http://www.radiowish.ro/live.m3u");
	GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~n~~w~buffering ~r~radio wish~w~...", 1500, 3);
	return 1;
}
CMD:radiotube(playerid)
{
    GetPlayerName(playerid,pName,MAX_PLAYER_NAME);
    format(string,sizeof string,"{FF0000}%s {FFFFFF}asculta {FF0000}radio-tube.pl Dubstep (/radiotube)",pName);
    SendClientMessageToAll(0xFFFFFFAA,string);
	PlayAudioStreamForPlayer(playerid, "http://s4.radiohost.pl:8154/listen.pls");
	GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~n~~w~buffering ~r~radio-tube.pl dubstep~w~...", 1500, 3);
	return 1;
}
CMD:radiomafia(playerid)
{
    GetPlayerName(playerid,pName,MAX_PLAYER_NAME);
    format(string,sizeof string,"{FF0000}%s {FFFFFF}asculta {FF0000}Radio Mafia (/radiomafia)",pName);
    SendClientMessageToAll(0xFFFFFFAA,string);
	PlayAudioStreamForPlayer(playerid, "http://www.radiomafia.ro/listen.m3u");
	GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~n~~w~buffering ~r~radio mafia~w~...", 1500, 3);
	return 1;
}
CMD:greudedifuzat(playerid)
{
    GetPlayerName(playerid,pName,MAX_PLAYER_NAME);
    format(string,sizeof string,"{FF0000}%s {FFFFFF}asculta {FF0000}Radio Greu de Difuzat (/greudedifuzat)",pName);
    SendClientMessageToAll(0xFFFFFFAA,string);
	PlayAudioStreamForPlayer(playerid, "http://www.greudedifuzat.eu/greudedifuzat.m3u");
	GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~n~~w~buffering ~r~radio greu de difuzat~w~...", 1500, 3);
	return 1;
}
CMD:radiostarmusik(playerid)
{
    GetPlayerName(playerid,pName,MAX_PLAYER_NAME);
    format(string,sizeof string,"{FF0000}%s {FFFFFF}asculta {FF0000}Radio Star Musik (/radiostarmusik)",pName);
    SendClientMessageToAll(0xFFFFFFAA,string);
	PlayAudioStreamForPlayer(playerid, "http://78.129.224.11:26767");
	GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~n~~w~buffering ~r~radio star musik~w~...", 1500, 3);
	return 1;
}
CMD:stopradio(playerid)
{
    PlayAudioStreamForPlayer(playerid, "Radio oprit.");
	StopAudioStreamForPlayer(playerid);
	return 1;
}
//End of the script. © 2012 [RNG]DuReX.=======================================//
