#if defined UIV_TRUCK
	#endinput
#endif
#define UIV_TRUCK

static enum
{
	UIV_TRUCK_DIALOG_AMMO_ID = 40,
	UIV_TRUCK_DIALOG_AMMO_NUM_ID
};

static
	truck_listitem[MAX_PLAYERS char];

stock GiveAmmo(playerid, vehicleid)
{
	static const
		str_t[] = "Патроны\tКоличество\n",
		str_a[] = "Патроны для %s\t%i/%i\n";

	const
		size = sizeof str_a + MAX_WEAPON_NAME + 4*2 - (2*3 + 2);

	new
		name[MAX_WEAPON_NAME],
		str[size],
		string[size*UIV_MAX_AMMO+sizeof str_t-2];

	strcat(string, str_t);

	for (new i = 0; i < UIV_MAX_AMMO; i++)
	{
		if (uiv[vehicleid][uiv_ammo][i] == 0)
		{
			break;
		}

		GetWeaponName(uiv[vehicleid][uiv_ammoID][i], name, MAX_WEAPON_NAME);
		format(str, sizeof str, str_a, name, uiv[vehicleid][uiv_ammo][i], UIV_MAX_AMMO_IN_TRUCK);
		strcat(string, str);
	}

	TrunkOrRearDoorsOfVehicle(playerid, vehicleid);

	return ShowPlayerDialog(playerid, UIV_TRUCK_DIALOG_AMMO_ID, DIALOG_STYLE_TABLIST_HEADERS, !"Военный грузовик", string, !"Взять", !"Закрыть");
}

static stock TakeAmmo(playerid, vehicleid, listitem, num)
{
	static const
		str_1[] = "{FFFFFF}Патроны для {FF0000}%s",
		str_2[] = "{FFFFFF}Вы взяли: %i\nУ вас в наличии %i патронов для %s";

	static
		ammo,
		result,
		index_i,
		backpack,
		weaponid,
		name[MAX_WEAPON_NAME],
		top[sizeof str_1 + MAX_WEAPON_NAME],
		string[sizeof str_2 + 11 + MAX_WEAPON_NAME - 2*2];

	backpack = GetBackpackSize(playerid);
	weaponid = uiv[vehicleid][uiv_ammoID][listitem];
	truck_listitem{playerid} = 0;

	TrunkOrRearDoorsOfVehicle(playerid);

	if (num*BACKPACK_SIZE_AMMO > backpack)
	{
		return ShowPlayerReminder(playerid, pInfo[playerid][pBackpackLevel] == 0 ? !"Найдите рюкзак" : !"Рюкзак переполнен!\nПовысьте его уровень");
	}

	PickUpPlayerAmmo(playerid, weaponid, num, false);
	uiv[vehicleid][uiv_ammo][listitem] -= num;
	GetWeaponName(uiv[vehicleid][uiv_ammoID][listitem], name, MAX_WEAPON_NAME);
	ammo = GetPlayerSubject(playerid, weaponid-BACKPACK_DIFFERENCE_IN_INDEX);

	for (new i = 0; i < UIV_MAX_AMMO; i++)
	{
		if (uiv[vehicleid][uiv_ammo][i] == 0)
		{
			index_i = i == UIV_MAX_AMMO - 1 ? 0 : 1;
			uiv[vehicleid][uiv_ammo][i] = uiv[vehicleid][uiv_ammo][i+index_i];
			uiv[vehicleid][uiv_ammo][i+index_i] = 0;
			uiv[vehicleid][uiv_ammoID][i] = uiv[vehicleid][uiv_ammoID][i+index_i];
			uiv[vehicleid][uiv_ammoID][i+index_i] = 0;
		}

		result += uiv[vehicleid][uiv_ammo][i];
	}

	if (result == 0)
	{
		uiv[vehicleid][uiv_drop] = false;
		HideUIVehicle(vehicleid);
	}

	result = 0;

	format(top, sizeof top, str_1, name);
	format(string, sizeof string, str_2, num, ammo, name);

	return ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, top, string, !"Закрыть", "");
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if (dialogid == UIV_TRUCK_DIALOG_AMMO_ID)
	{
		if (response == 0)
		{
			return TrunkOrRearDoorsOfVehicle(playerid);
		}

		truck_listitem{playerid} = listitem;
		
		return ShowPlayerDialog(playerid, UIV_TRUCK_DIALOG_AMMO_NUM_ID, DIALOG_STYLE_INPUT, !"Военный грузовик", !"Количество патронов:", !"Взять", !"Закрыть");
	}
	if (dialogid == UIV_TRUCK_DIALOG_AMMO_NUM_ID)
	{
		if (response == 0)
		{
			return TrunkOrRearDoorsOfVehicle(playerid);
		}

		new
			listitemid = truck_listitem{playerid},
			vehicleid = uiv_vehicleid[playerid],
			ammo = strval(inputtext);

		if (uiv[vehicleid][uiv_ammo][listitemid] < ammo)
		{
			ammo = uiv[vehicleid][uiv_ammo][listitemid];
		}

		return TakeAmmo(playerid, vehicleid, listitemid, ammo);
	}
	#if defined uiv_truck_OnDialogResponse
		uiv_truck_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#endif

	return 0;
}

#if defined _ALS_OnDialogResponse
	#undef OnDialogResponse
#else
	#define _ALS_OnDialogResponse
#endif
#define OnDialogResponse uiv_truck_OnDialogResponse
#if defined uiv_truck_OnDialogResponse
	forward uiv_truck_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif

public OnPlayerDisconnect(playerid, reason)
{
	truck_listitem{playerid} = 0;

	#if defined uiv_truck_OnPlayerDisconnect
		uiv_truck_OnPlayerDisconnect(playerid, reason);
	#endif

	return 1;
}

#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect uiv_truck_OnPlayerDisconnect
#if defined uiv_truck_OnPlayerDisconnect
	forward uiv_truck_OnPlayerDisconnect(playerid, reason);
#endif