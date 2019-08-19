#if defined FUNCTIONS
	#endinput
#endif
#define FUNCTIONS

#define floatrandom(%0) \
	(float(random(%0))+float(random(1000))/1000)
	
stock Float:frandom(Float:max) 
    return floatdiv(float(random(0)), floatdiv(float(cellmax), max)); 

#define PlayerKick(%0) \
	(SetTimerEx(!"NewKick", GetPlayerPing(%0), false, "i", %0))

forward NewKick(playerid);
public NewKick(playerid)
	return Kick(playerid);

#define HOLDING(%0) \
	((newkeys & (%0)) == (%0))

#define ClosePlayerDialog(%0) \
	(ShowPlayerDialog(%0, -1, DIALOG_STYLE_MSGBOX, " ", " ", " ", ""))

#define InvisiblePlayerIcon(%0) \
	(SetPlayerColor(%0, COLOR_WHITE_A))

stock ShowPlayerReminder(playerid, const reminder[], dialogid = 0)
{
	new
		string[36] =!"{FFFF00}";
	strcat(string, reminder);
	return ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_MSGBOX, !" ", string, !"Закрыть", "");
}