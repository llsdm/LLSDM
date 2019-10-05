#if defined DB_SAVE
	#endinput
#endif
#define DB_SAVE

stock SaveLife(playerid)
{
	if (!IsPlayerAuthorized(playerid))
	{
		return 0;
	}

	static const
		str[] = "UPDATE `accounts` SET `pLife` = '%i' WHERE `pID` = '%i'";

	static
		string[sizeof str + 1 + 11 - 2*2];

	new
		result;

	#if LLSDM_RESPAWN_WITH_SAVED == 0
		result += pInfo[playerid][pExpLife]+pInfo[playerid][pMoney];
		result += pInfo[playerid][pExp]+pInfo[playerid][pMoney];

		result += pInfo[playerid][pWeapons][0]+pInfo[playerid][pWeapons][1]+pInfo[playerid][pAmmo][0]+pInfo[playerid][pAmmo][1]+pInfo[playerid][pWeapons][2];
		result += pInfo[playerid][pBackpackLevel];

		for (new i = 4; i < LLSDM_MAX_BACKPACK_SLOTS; i++)
		{
			result += backpack_index[playerid][i];
			result += backpack_number[playerid][i];
		}

		result = !!result;
	#else
		result = pInfo[playerid][pLife];
	#endif
 
	format(string, sizeof string, str,
		result,
		pInfo[playerid][pID]
	);
	mysql_tquery(mysql_connect_ID, string, "", "");

	return 1;
}

stock SaveExp(playerid)
{
	if (!IsPlayerAuthorized(playerid))
	{
		return 0;
	}

	#if LLSDM_RESPAWN_WITH_SAVED == 0
		static const
			str[] = "UPDATE `accounts` SET `pExpLife` = '%i', `pExp` = '%i', `pMoney` = '%i' WHERE `pID` = '%i'";

		static
			string[sizeof str + 4*11 - 4*2];
	 
		format(string, sizeof string, str,
			pInfo[playerid][pExpLife],
			pInfo[playerid][pExp],
			pInfo[playerid][pMoney],
			pInfo[playerid][pID]
		);
	#else
		static const
			str[] = "UPDATE `accounts` SET `pExp` = '%i', `pMoney` = '%i' WHERE `pID` = '%i'";

		static
			string[sizeof str + 3*11 - 3*2];
	 
		format(string, sizeof string, str,
			pInfo[playerid][pExp],
			pInfo[playerid][pMoney],
			pInfo[playerid][pID]
		);
	#endif

	mysql_tquery(mysql_connect_ID, string, "", "");

	return 1;
}

stock SaveHealth(playerid)
{
	if (!IsPlayerAuthorized(playerid))
	{
		return 0;
	}

	new
		Float:health;
	
	static const
		str[] = "UPDATE `accounts` SET `pHealth` = '%.0f' WHERE `pID` = '%i'";

	static
		string[sizeof str + 5*11 - 5*2];
 
 	GetPlayerHealth(playerid, health);
 
	format(string, sizeof string, str,
		health,
		pInfo[playerid][pID]
	);
	mysql_tquery(mysql_connect_ID, string, "", "");

	return 1;
}

stock SaveDeath(playerid)
{
	if (!IsPlayerAuthorized(playerid))
	{
		return 0;
	}
	
	static const
		str[] = "UPDATE `accounts` SET `pKillsLife` = '%i', `pKills` = '%i', `pTimeKill` = '%i', `pDeaths` = '%i' WHERE `pID` = '%i'";

	static
		string[sizeof str + 5*11 - 5*2];
 
	format(string, sizeof string, str,
		pInfo[playerid][pKillsLife],
		pInfo[playerid][pKills],
		pInfo[playerid][pTimeKill],
		pInfo[playerid][pDeaths],
		pInfo[playerid][pID]
	);
	mysql_tquery(mysql_connect_ID, string, "", "");

	return 1;
}

stock SaveWeapon(playerid)
{
	if (!IsPlayerAuthorized(playerid))
	{
		return 0;
	}
	
	static const
		str[] = "UPDATE `accounts` SET `pWeapons` = '%i|%i|%i', `pWeaponExp` = '%i|%i|%i', `pSecondWeapon` = '%i', `pAmmo` = '%i|%i' WHERE `pID` = '%i'";

	static
		string[sizeof str + MAX_WEAPONS*2 + MAX_WEAPONS*11 + 11 - 5*2];
 
	format(string, sizeof string, str,
		pInfo[playerid][pWeapons][0],
		pInfo[playerid][pWeapons][1],
		pInfo[playerid][pWeapons][2],
		pInfo[playerid][pWeaponExp][0],
		pInfo[playerid][pWeaponExp][1],
		pInfo[playerid][pWeaponExp][2],
		pInfo[playerid][pSecondWeapon],
		pInfo[playerid][pAmmo][0],
		pInfo[playerid][pAmmo][1],
		pInfo[playerid][pID]
	);
	mysql_tquery(mysql_connect_ID, string, "", "");

	return 1;
}

stock SaveBackpackLevel(playerid)
{
	if (!IsPlayerAuthorized(playerid))
	{
		return 0;
	}
	
	static const
		str[] = "UPDATE `accounts` SET `pBackpackLvl` = '%i', `pBackpackSize` = '%i' WHERE `pID` = '%i'";

	static
		string[sizeof str + 11*3 - 2*3];
 
	format(string, sizeof string, str,
		pInfo[playerid][pBackpackLevel],
		pInfo[playerid][pBackpackSize],
		pInfo[playerid][pID]
	);
	mysql_tquery(mysql_connect_ID, string, "", "");

	return 1;
}

stock SaveBackpack(playerid)
{
	if (!IsPlayerAuthorized(playerid))
	{
		return 0;
	}
	
	static const
		str[] = "UPDATE `accounts` SET `pBackpackIndex` = '%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i', `pBackpackNumber` = '%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i' WHERE `pID` = '%i'";

	static
		string[sizeof str + LLSDM_MAX_BACKPACK_SLOTS*2 + LLSDM_MAX_BACKPACK_SLOTS*11 + 11 - LLSDM_MAX_BACKPACK_SLOTS*2 - 2];
 
	format(string, sizeof string, str,
		backpack_index[playerid][0],
		backpack_index[playerid][1],
		backpack_index[playerid][2],
		backpack_index[playerid][3],
		backpack_index[playerid][4],
		backpack_index[playerid][5],
		backpack_index[playerid][6],
		backpack_index[playerid][7],
		backpack_index[playerid][8],
		backpack_index[playerid][9],
		backpack_index[playerid][10],
		backpack_index[playerid][11],
		backpack_index[playerid][12],
		backpack_index[playerid][13],
		backpack_index[playerid][14],
		backpack_index[playerid][15],
		backpack_index[playerid][16],
		backpack_index[playerid][17],
		backpack_index[playerid][18],
		backpack_number[playerid][0],
		backpack_number[playerid][1],
		backpack_number[playerid][2],
		backpack_number[playerid][3],
		backpack_number[playerid][4],
		backpack_number[playerid][5],
		backpack_number[playerid][6],
		backpack_number[playerid][7],
		backpack_number[playerid][8],
		backpack_number[playerid][9],
		backpack_number[playerid][10],
		backpack_number[playerid][11],
		backpack_number[playerid][12],
		backpack_number[playerid][13],
		backpack_number[playerid][14],
		backpack_number[playerid][15],
		backpack_number[playerid][16],
		backpack_number[playerid][17],
		backpack_number[playerid][18],
		pInfo[playerid][pID]
	);
	mysql_tquery(mysql_connect_ID, string, "", "");

	return 1;
}

stock SavePosition(playerid)
{
	if (!IsPlayerAuthorized(playerid))
	{
		return 0;
	}
	
	static const
		str[] = "UPDATE `accounts` SET `pPosition` = '%.02f|%.02f|%.02f|%.02f' WHERE `pID` = '%i'";

	static
		Float:pos_x, Float:pos_y, Float:pos_z, Float:angle,
		string[sizeof str + 7*4 + 11 - 5*4 - 2];

	GetPlayerPos(playerid, pos_x, pos_y, pos_z);
	GetPlayerFacingAngle(playerid, angle);
 
	format(string, sizeof string, str,
		pos_x,
		pos_y,
		pos_z,
		angle,
		pInfo[playerid][pID]
	);
	mysql_tquery(mysql_connect_ID, string, "", "");

	return 1;
}