#if defined UIV_AMBULANCE
	#endinput
#endif
#define UIV_AMBULANCE

static enum
{
	UIV_AMBULANCE_DIALOG_D1 = 20,
	UIV_AMBULANCE_DIALOG_D2
};

stock GiveKit(playerid, vehicleid)
{
	static const
		str[] = "В машине %i аптечек";

	static
		string[sizeof str + 11 - 2];

	TrunkOrRearDoorsOfVehicle(playerid, vehicleid);

	format(string, sizeof string, str, uiv[vehicleid][uiv_kits]);

	return ShowPlayerDialog(playerid, UIV_AMBULANCE_DIALOG_D1, DIALOG_STYLE_MSGBOX, !"Карета скорой помощи", string, !"Взять", "Закрыть");
}

static stock TakeKit(playerid, vehicleid, num)
{
	static const
		str_1[] = "{FFFFFF}В машине осталось {FF0000}%i {FFFFFF}аптечек",
		str_2[] = "Вы забрали: {FF0000}%i";

	static
		backpack,
		top[sizeof str_1 + 11 - 2],
		string[sizeof str_2 + 11 - 2];

	backpack = GetBackpackSize(playerid);

	TrunkOrRearDoorsOfVehicle(playerid);

	if (num*BACKPACK_SIZE_KIT > backpack)
	{
		return ShowPlayerReminder(playerid, pInfo[playerid][pBackpackLevel] == 0 ? !"Найдите рюкзак" : !"Рюкзак переполнен!\nПовысьте его уровень");
	}

	GivePlayerKits(playerid, num);
	AttachKitToPlayer(playerid);
	uiv[vehicleid][uiv_kits] -= num;

	if (uiv[vehicleid][uiv_kits] == 0)
	{
		uiv[vehicleid][uiv_loot] =
		uiv[vehicleid][uiv_drop] = false;

		HideUIVehicle(vehicleid);
	}


	format(top, sizeof top, str_1, uiv[vehicleid][uiv_kits]);
	format(string, sizeof string, str_2, num);

	return ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, top, string, !"Закрыть", "");
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if (dialogid == UIV_AMBULANCE_DIALOG_D1)
	{
		if (response == 0)
		{
			return TrunkOrRearDoorsOfVehicle(playerid);
		}
		
		return ShowPlayerDialog(playerid, UIV_AMBULANCE_DIALOG_D2, DIALOG_STYLE_INPUT, !"Карета скорой помощи", !"Количество аптечек:", !"Взять", !"Закрыть");
	}
	if (dialogid == UIV_AMBULANCE_DIALOG_D2)
	{
		if (response == 0)
		{
			return TrunkOrRearDoorsOfVehicle(playerid);
		}

		new
			vehicleid = uiv_vehicleid[playerid],
			kits = strval(inputtext);

		if (uiv[vehicleid][uiv_kits] < kits)
		{
			kits = uiv[vehicleid][uiv_kits];
		}

		return TakeKit(playerid, vehicleid, kits);
	}

	#if defined uiv_ambulance_OnDialogResponse
		uiv_ambulance_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#endif

	return 0;
}

#if defined _ALS_OnDialogResponse
	#undef OnDialogResponse
#else
	#define _ALS_OnDialogResponse
#endif
#define OnDialogResponse uiv_ambulance_OnDialogResponse
#if defined uiv_ambulance_OnDialogResponse
	forward uiv_ambulance_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif