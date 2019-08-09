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

	pInfo[playerid][pExpLife] =
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
	pInfo[playerid][pSecondWeapon] =
	pInfo[playerid][pAmmo][0] =
	pInfo[playerid][pAmmo][1] =

	pInfo[playerid][pBag] =
	pInfo[playerid][pBackpackLvl] =
	pInfo[playerid][pBackpackSize] = 0;
  
  pInfo[playerid][pHealth] = 0.0;

	for (new i = 0; i < MAX_BACKPACK_SLOTS; i++)
	{
		backpack_index[playerid][i] =
		backpack_number[playerid][i] = 0;
	}
  
	#if defined BILLBOARDS
		GetKillLeader();
	#endif

	return 1;
}
