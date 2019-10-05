#if defined DB_REMOVE
	#endinput
#endif
#define DB_REMOVE

stock RemovePlayerInfo(playerid)
{
	pInfo[playerid][pName][0] =
	pInfo[playerid][pEmail][0] = 
	pInfo[playerid][pPassword][0] = EOS;

	pInfo[playerid][pID] =
	pInfo[playerid][pAdmin] =
	pInfo[playerid][pSkin] =
	pInfo[playerid][pLife] =

	pInfo[playerid][pExp] =
	pInfo[playerid][pMoney] =
	pInfo[playerid][pBagMoney] =

	pInfo[playerid][pKills] =
	pInfo[playerid][pTimeKill] =
	pInfo[playerid][pKillsLife] =
	pInfo[playerid][pDeaths] =

	pInfo[playerid][pWeapons][0] =
	pInfo[playerid][pWeapons][1] =
	pInfo[playerid][pWeapons][2] =
	pInfo[playerid][pWeaponExp][0] =
	pInfo[playerid][pWeaponExp][1] =
	pInfo[playerid][pWeaponExp][2] =
	pInfo[playerid][pSecondWeapon] =
	pInfo[playerid][pAmmo][0] =
	pInfo[playerid][pAmmo][1] =

	pInfo[playerid][pBackpackLevel] =
	pInfo[playerid][pBackpackSize] = 0;

	#if LLSDM_RESPAWN_WITH_SAVED == 0
		pInfo[playerid][pExpLife] = 0;
	#endif

	pInfo[playerid][pHealth] = 0.0;

	pInfo[playerid][pBag] = false;

	for (new i = 0; i < LLSDM_MAX_BACKPACK_SLOTS; i++)
	{
		backpack_index[playerid][i] =
		backpack_number[playerid][i] = 0;
	}

	player_authorized{playerid} = false;

	return 1;
}