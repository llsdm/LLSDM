#if defined PLAYER_BACKPACK
	#endinput
#endif
#define PLAYER_BACKPACK

enum
{
	PLAYER_BACKPACK_DIALOG = 30,
	PLAYER_BACKPACK_REM_DIALOG
};

static enum
{
	bImprove,
	bBag,
	bPerks,
	bSecondWeapon,
	bAmmoColt45,
	bAmmoSilenced,
	bAmmoDeagle,
	bAmmoShotgun,
	bAmmoSawedoff,
	bAmmoCombatShotgun,
	bAmmoUzi,
	bAmmoMP5,
	bAmmoAK47,
	bAmmoM4,
	bAmmoTec9,
	bAmmoRifle,
	bAmmoSniper,
	bKits,
	bBaters
};

const
	PLAYER_BACKPACK_AUTO_SAVE = LLSDM_PARAMS_ON,
	PLAYER_BACKPACK_AUTO_RECHARGE = LLSDM_PARAMS_ON;

const
	NO_BACKPACK = 45,
	
	BACKPACK_LVL_SIZE = 100,
	BACKPACK_LVL_PRICE = 300,
	BACKPACK_SIZE_KIT = 15,
	BACKPACK_SIZE_AMMO = 2,
	
	BACKPACK_MIN_INDEX = bAmmoColt45,
	BACKPACK_DIFFERENCE_IN_INDEX = 22-bAmmoColt45;
	
static const
	backpack_weapon_type_id[] =
	{
		0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1
	},
	backpack_weapon_ammo[] =
	{
		17, 17, 7, 5, 4, 7, 50, 30, 30, 50, 50, 1, 1
	},
	backpack_str[][] =
	{
		"Улучшить",
		"Прибыль с сумки",
		"Перки",
		"Сменить основное оружие",
		"Патроны для Colt 45",
		"Патроны для Silenced",
		"Патроны для Deagle",
		"Патроны для Shotgun",
		"Патроны для Sawed-off",
		"Патроны для Combat Shotgun",
		"Патроны для Uzi",
		"Патроны для MP5",
		"Патроны для AK-47",
		"Патроны для M4",
		"Патроны для Tec-9",
		"Патроны для Rifle",
		"Патроны для Sniper",
		"Аптечка",
		"Барьеры"
	};

static
	backpack_listitem[MAX_PLAYERS][MAX_BACKPACK_SLOTS];

static stock GivePlayerSubject(playerid, index, num)
{
	new
		id;

	for (new i = BACKPACK_MIN_INDEX; i < MAX_BACKPACK_SLOTS; i++)
	{
		id = backpack_index[playerid][i];

		if (id == index || id == 0)
		{
			backpack_index[playerid][i] = index;
			backpack_number[playerid][i] += num;

			#if PLAYER_BACKPACK_AUTO_SAVE == LLSDM_PARAMS_ON
				SaveBackpack(playerid);
				SaveWeapon(playerid);
			#endif

			return 1;
		}
	}
	return 1;
}

static stock GivePlayerSubjectIndex(playerid, index, num)
{
	backpack_number[playerid][index] += num;

	#if PLAYER_BACKPACK_AUTO_SAVE == LLSDM_PARAMS_ON
		SaveBackpack(playerid);
		SaveWeapon(playerid);
	#endif
		
	return 1;
}

stock PickUpPlayerAmmo(playerid, weaponid, ammo, bool:clear_ammo = true)
{
	new
		index,
		typeid = backpack_weapon_type_id[weaponid-22];

	weaponid -= BACKPACK_DIFFERENCE_IN_INDEX;

	if (clear_ammo)
		pInfo[playerid][pAmmo][typeid] = 0;

	for (new i = BACKPACK_MIN_INDEX; i < MAX_BACKPACK_SLOTS; i++)
	{
		index = backpack_index[playerid][i];

		if (index == weaponid || index == 0)
		{
			if (ammo > 0)
			{
				backpack_index[playerid][i] = weaponid;
				backpack_number[playerid][i] += ammo;

				#if PLAYER_BACKPACK_AUTO_SAVE == LLSDM_PARAMS_ON
					SaveBackpack(playerid);
					SaveWeapon(playerid);
				#endif
			}

			return 1;
		}
	}
	return 1;
}

static stock ReplacePlayerWeapon(playerid, bool:show_backpack = false)
{
	new
		weaponid = pInfo[playerid][pWeapons][1];

	PickUpPlayerAmmo(playerid, weaponid, pInfo[playerid][pAmmo][1]);

	pInfo[playerid][pWeapons][1] = pInfo[playerid][pWeapons][2];
	pInfo[playerid][pWeapons][2] = weaponid;
	pInfo[playerid][pSecondWeapon] = !pInfo[playerid][pSecondWeapon];

	ResetPlayerWeapons(playerid);

	if (pInfo[playerid][pAmmo][0] != 0)
		GivePlayerWeapon(playerid, pInfo[playerid][pWeapons][0], pInfo[playerid][pAmmo][0]);

	if (show_backpack)
		OpenBackpack(playerid);

	#if PLAYER_BACKPACK_AUTO_SAVE == LLSDM_PARAMS_ON
		SaveBackpack(playerid);
		SaveWeapon(playerid);
	#endif

	return 1;
}

static stock CheckBackpackIndex(playerid, index = BACKPACK_MIN_INDEX)
{
	new
		index_i;

	for (new i = index; i < MAX_BACKPACK_SLOTS; i++)
	{
		if (backpack_number[playerid][i] == 0)
		{
			index_i = i == MAX_BACKPACK_SLOTS - 1 ? 0 : 1;
			backpack_number[playerid][i] = backpack_number[playerid][i+index_i];
			backpack_number[playerid][i+index_i] = 0;
			backpack_index[playerid][i] = backpack_index[playerid][i+index_i];
			backpack_index[playerid][i+index_i] = 0;
		}
	}
	return 1;
}

stock GetPlayerSubject(playerid, index, &index_i = 0)
{
	new
		id;

	for (new i = BACKPACK_MIN_INDEX; i < MAX_BACKPACK_SLOTS; i++)
	{
		id = backpack_index[playerid][i];

		if (id == index)
		{
			index_i = i;
			return backpack_number[playerid][i];
		}
	}
	return 0;
}

stock GetBackpackSize(playerid)
{
	new
		index,
		number,
		size;

	for (new i = BACKPACK_MIN_INDEX; i < MAX_BACKPACK_SLOTS; i++)
	{
		index = backpack_index[playerid][i];
		number = backpack_number[playerid][i];

		if (number != 0)
		{
			switch (index)
			{
				case bKits: size += BACKPACK_SIZE_KIT*number;
				default: size += BACKPACK_SIZE_AMMO*number;
			}
		}
	}

	size = pInfo[playerid][pBackpackSize]-size;
	return size;
}

stock GivePlayerKits(playerid, num)
	return GivePlayerSubject(playerid, bKits, num);

stock GetPlayerKits(playerid)
	return GetPlayerSubject(playerid, bKits);

static stock OpenBackpack(playerid)
{
	static const
		str_t1[] = "Рюкзак {BFFF00}%i lvl. [%i/%i] {1E90FF}E%i",
		str_t2[] = "Карманы {BFFF00}[%i/%i]";

	static
		size,
		listitem,
		exp_life,
		backpack,
		price,
		bag,
		index,
		number,
		second,

		str[40],
		title[sizeof str_t1 + 11*2 - 2*2],
		string[500];

	size =
	listitem = 0;
	exp_life = pInfo[playerid][pExpLife];
	backpack = pInfo[playerid][pBackpackLvl];
	price = backpack*BACKPACK_LVL_PRICE;
	price = (exp_life >= price && backpack > 0) ? price : 0;
	bag = pInfo[playerid][pBagMoney];
	second  = pInfo[playerid][pWeapons][2];
	string[0] = EOS;

	strcat(string, "Предмет\t\tКоличество\n");

	if (price != 0)
	{
		format(string, sizeof string, "%s%s\t\t{1E90FF}E%i{FFFFFF}\n", string, backpack_str[bImprove], price);
		backpack_listitem[playerid][listitem] = bImprove;
		listitem++;
	}

	if (bag > 0)
	{
		format(string, sizeof string, "%s%s\t\t{1E90FF}E%i{FFFFFF}\n", string, backpack_str[bBag], bag);
		backpack_listitem[playerid][listitem] = bBag;
		listitem++;
	}

	if (second != 0 && backpack != 0)
	{
		format(string, sizeof string, "%s%s\t\t \n", string, backpack_str[bSecondWeapon]);
		backpack_listitem[playerid][listitem] = bSecondWeapon;
		listitem++;
	}

	for (new i = BACKPACK_MIN_INDEX; i < MAX_BACKPACK_SLOTS; i++)
	{
		index = backpack_index[playerid][i];
		number = backpack_number[playerid][i];

		if (number != 0)
		{
			format(str, sizeof str, "%s\t\t%i\n", backpack_str[index], number);
			strcat(string, str);

			switch (index)
			{
				case bKits: size += BACKPACK_SIZE_KIT*number;
				default: size += BACKPACK_SIZE_AMMO*number;
			}

			backpack_listitem[playerid][listitem] = index;
			listitem++;
		}
	}

	if (backpack)
		format(title, sizeof title, str_t1, backpack, size, pInfo[playerid][pBackpackSize], pInfo[playerid][pExpLife]);
	else
		format(title, sizeof title, str_t2, size, pInfo[playerid][pBackpackSize]);

	if (listitem == 0)
		return ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, title, !"Пусто", !"Закрыть", "");

	return ShowPlayerDialog(playerid, PLAYER_BACKPACK_DIALOG, DIALOG_STYLE_TABLIST_HEADERS, title, string, !"Взять", !"Закрыть");
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if (HOLDING(KEY_YES))
	{
		if (IsPlayerAuthorized(playerid))
		{
			return OpenBackpack(playerid);
		}
	}

	#if defined player_backpack_OnPlayerNewKey
		player_backpack_OnPlayerNewKey(playerid, newkeys, oldkeys);
	#endif

	return 1;
}

#if defined _ALS_OnPlayerKeyStateChange
	#undef	OnPlayerKeyStateChange
#else
	#define	_ALS_OnPlayerKeyStateChange
#endif
#define OnPlayerKeyStateChange	player_backpack_OnPlayerNewKey
#if defined player_backpack_OnPlayerNewKey
	forward player_backpack_OnPlayerNewKey(playerid, newkeys, oldkeys);
#endif

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if (dialogid == PLAYER_BACKPACK_DIALOG)
	{
		if (response == 0)
			return 0;

		new
			index = backpack_listitem[playerid][listitem];

		switch (index)
		{
			case bImprove:
			{
				pInfo[playerid][pExpLife] -= BACKPACK_LVL_PRICE*pInfo[playerid][pBackpackLvl];
				pInfo[playerid][pBackpackLvl]++;
				pInfo[playerid][pBackpackSize] = pInfo[playerid][pBackpackLvl]*BACKPACK_LVL_SIZE;

				#if PLAYER_BACKPACK_AUTO_SAVE == LLSDM_PARAMS_ON
					SaveBackpackLvl(playerid);
					SaveExp(playerid);
				#endif

				return OpenBackpack(playerid);
			}
			case bBag: return OpenBackpack(playerid);
			case bSecondWeapon: return ReplacePlayerWeapon(playerid, true);
			case bKits: return PlayerKit(playerid);
			default: 
			{
				new
					weaponid = index+BACKPACK_DIFFERENCE_IN_INDEX,
					typeid = backpack_weapon_type_id[weaponid-22],
					ammo = backpack_weapon_ammo[weaponid-22],
					ammo_in_weap = pInfo[playerid][pAmmo][typeid],
					index_i,
					get_ammo = GetPlayerSubject(playerid, index, index_i);

				if (pInfo[playerid][pWeapons][typeid] != weaponid)
				{
					if (pInfo[playerid][pWeapons][2] != weaponid)
						return ShowPlayerReminder(playerid, !"У Вас нет этого оружия", PLAYER_BACKPACK_REM_DIALOG);
					else
					{
						PickUpPlayerAmmo(playerid, pInfo[playerid][pWeapons][typeid], pInfo[playerid][pAmmo][typeid]);
						ReplacePlayerWeapon(playerid);
					}
				}

				if (ammo == ammo_in_weap)
					return OpenBackpack(playerid);

				if (get_ammo+ammo_in_weap > ammo)
					get_ammo = ammo-ammo_in_weap;

				pInfo[playerid][pAmmo][typeid] += get_ammo;
				GivePlayerSubjectIndex(playerid, index_i, -get_ammo);

				if (backpack_number[playerid][index_i] == 0)
					CheckBackpackIndex(playerid, index_i);

				#if PLAYER_BACKPACK_AUTO_SAVE == LLSDM_PARAMS_ON
					SaveBackpack(playerid);
					SaveWeapon(playerid);
				#endif

				ApplyAnimation(playerid,!"RIFLE",!"RIFLE_load", 2, 0, 1, 1 , 0, 1000, 1);
				return GivePlayerWeapon(playerid, weaponid, get_ammo);
			}
		}

		return 1;
	}
	if (dialogid == PLAYER_BACKPACK_REM_DIALOG)
		return OpenBackpack(playerid);

	#if defined player_backpack_OnPlayerDialogs
		player_backpack_OnPlayerDialogs(playerid, dialogid, response, listitem, inputtext);
	#endif

	return 0;
}

#if defined _ALS_OnDialogResponse
	#undef OnDialogResponse
#else
	#define _ALS_OnDialogResponse
#endif
#define OnDialogResponse player_backpack_OnPlayerDialogs
#if defined player_backpack_OnPlayerDialogs
	forward player_backpack_OnPlayerDialogs(playerid, dialogid, response, listitem, inputtext[]);
#endif

public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{	
	static
		#if PLAYER_BACKPACK_AUTO_RECHARGE == LLSDM_PARAMS_ON
			get_ammo,
			index,
			index_i,
			ammo_in_weap,
		#endif
		typeid,
		ammo;
	
	typeid = backpack_weapon_type_id[weaponid-22];
	ammo = pInfo[playerid][pAmmo][typeid];

	if (ammo >= 0)
	{
		ammo = pInfo[playerid][pAmmo][typeid]--;

		#if defined TD_PLAYER_HUD
			UpdateHudWeaponAmmo(playerid, weaponid, ammo);
		#endif

		#if PLAYER_BACKPACK_AUTO_RECHARGE == LLSDM_PARAMS_ON
			index = weaponid-BACKPACK_DIFFERENCE_IN_INDEX;

			if (ammo == 1)
			{
				get_ammo = GetPlayerSubject(playerid, index, index_i);

				if (get_ammo > 0)
				{
					ammo = backpack_weapon_ammo[weaponid-22];
					ammo_in_weap = pInfo[playerid][pAmmo][typeid];

					if (get_ammo+ammo_in_weap > ammo)
						get_ammo = ammo-ammo_in_weap;

					pInfo[playerid][pAmmo][typeid] += get_ammo;
					GivePlayerSubjectIndex(playerid, index_i, -get_ammo);

					if (backpack_number[playerid][index_i] == 0)
						CheckBackpackIndex(playerid, index_i);

					#if PLAYER_BACKPACK_AUTO_SAVE == LLSDM_PARAMS_ON
						SaveBackpack(playerid);
						SaveWeapon(playerid);
					#endif

					GivePlayerWeapon(playerid, weaponid, get_ammo);
					ApplyAnimation(playerid, !"RIFLE", !"RIFLE_load", 2, 0, 1, 1 , 0, 1000, 1);
				}
			}
		#endif
	}

	#if defined player_backpack_OnPlayerWShot
		player_backpack_OnPlayerWShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ);
	#endif

	return 1;
}

#if defined _ALS_OnPlayerWeaponShot
	#undef OnPlayerWeaponShot
#else
	#define _ALS_OnPlayerWeaponShot
#endif
#define OnPlayerWeaponShot player_backpack_OnPlayerWShot
#if defined player_backpack_OnPlayerWShot
	forward player_backpack_OnPlayerWShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ);
#endif

public OnPlayerDeath(playerid, killerid, reason)
{
	for (new i = 0; i < MAX_BACKPACK_SLOTS; i++)
	{
		backpack_index[playerid][i] =
		backpack_number[playerid][i] = 
		backpack_listitem[playerid][i] = 0;
	}
	pInfo[playerid][pBackpackLvl] = 0;
	pInfo[playerid][pBackpackSize] = NO_BACKPACK;

	RemovePlayerAttachedObject(playerid, AMMU_SLOT_BACKPACK);
	ClosePlayerDialog(playerid);
	
	#if PLAYER_BACKPACK_AUTO_SAVE == LLSDM_PARAMS_ON
		SaveBackpackLvl(playerid);
		SaveBackpack(playerid);
		SaveWeapon(playerid);
	#endif

	#if defined player_backpack_OnPlayerDeath
		player_backpack_OnPlayerDeath(playerid, killerid, reason);
	#endif

	return 1;
}

#if defined _ALS_OnPlayerDeath
	#undef OnPlayerDeath
#else
	#define _ALS_OnPlayerDeath
#endif
#define OnPlayerDeath player_backpack_OnPlayerDeath
#if defined player_backpack_OnPlayerDeath
	forward player_backpack_OnPlayerDeath(playerid, killerid, reason);
#endif

public OnPlayerDisconnect(playerid, reason)
{
	for (new i = 0; i < MAX_BACKPACK_SLOTS; i++)
		backpack_listitem[playerid][i] = 0;

	RemovePlayerAttachedObject(playerid, AMMU_SLOT_BACKPACK);

	#if defined player_backpack_OnPlayerDis
		player_backpack_OnPlayerDis(playerid, reason);
	#endif

	return 1;
}

#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect player_backpack_OnPlayerDis
#if defined player_backpack_OnPlayerDis
	forward player_backpack_OnPlayerDis(playerid, reason);
#endif