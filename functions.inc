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

stock GetVector(&Float:x, &Float:y, Float:angle)
{
	new
		Float:cx = x,
		Float:cy = y;

	x = cx*floatcos(angle, degrees)-cy*floatsin(angle, degrees);
	y = cx*floatsin(angle, degrees)+cy*floatcos(angle, degrees);

	return 1;
}

stock AddDelimiterToInt(value, const space[] = "-")
{
	new
		string[16],
		i,
		k,
		v = 3,
		s;

	format(string, sizeof string, "%i", value >= 0 ? value : -value);

	k = strlen(string);
	i = k/3;
	k %= 3;

	if (i != 0)
	{
		if (k != 0)
		{
			strins(string, space, k);
			k++;
		}

		while (--i > 0)
		{
			k += v;
			strins(string, space, k);
			v++;
		}
	}

	if (value < 0)
		strins(string, "-", 0);

	return string;
}


stock ShowPlayerReminder(playerid, const reminder[], dialogid = 0)
{
	new
		string[36] =!"{FFFF00}";
	strcat(string, reminder);
	return ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_MSGBOX, !" ", string, !"Закрыть", "");
}