#include <a_samp>
#include <time>
#define FILTERSCRIPT
forward settime(playerid);
new Text:Time2, Text:Date;

public settime(playerid)
{
	new string[256],year,month,day,hours,minutes,seconds;
	getdate(year, month, day), gettime(hours, minutes, seconds);
	format(string, sizeof string, "~r~%d/~y~%s%d/~b~%s%d", day, ((month < 10) ? ("0") : ("")), month, (year < 10) ? ("0") : (""), year);
	TextDrawSetString(Date, string);
	format(string, sizeof string,  (hours < 10) ? ("0") : (""), hours, (minutes < 10) ? ("0") : (""), minutes, (seconds < 10) ? ("0") : (""), seconds);
	TextDrawSetString(Time2, string);
}
public OnPlayerSpawn(playerid)
{
    TextDrawShowForPlayer(playerid, Time2);
	TextDrawShowForPlayer(playerid, Date);
	return 1;
}
public OnGameModeInit()
{

   	SetTimer("settime",1000,true);
	SetTimer("weatherchange",10800000,true);
    Date = TextDrawCreate(547.000000,11.000000,"--");
    TextDrawFont(Date,3);
    TextDrawLetterSize(Date,0.399999,1.600000);
    TextDrawColor(Date,0xffffffff);
    Time2 = TextDrawCreate(547.000000,28.000000,"--");
    TextDrawFont(Time2,3);
    TextDrawLetterSize(Time2,0.399999,1.600000);
    TextDrawColor(Time2,0xFFFFFFC8);
    SetTimer("settime",1000,true);
    return 1;
}

