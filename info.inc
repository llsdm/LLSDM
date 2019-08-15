#if defined LLSDM_INFO
	#endinput
#endif
#define LLSDM_INFO

enum 
	player_info
	{
		pID,
		pAdmin,
		pName[MAX_PLAYER_NAME],
		pPassword[MAX_PLAYER_PASSWORD],
		pEmail[MAX_PLAYER_EMAIL],
		pSkin,
		pLife,
		Float:pHealth,
		Float:pLastDamage,
		pExpLife,
		pExp,
		pMoney,
		pBagMoney,
		pKills,
		pTimeKill,
		pKillsLife,
		pDeaths,
		pWeapons[MAX_WEAPONS+1],
		pSecondWeapon,
		pAmmo[MAX_WEAPONS],
		pBag,
		pBackpackLvl,
		pBackpackSize,
	};

enum 
	server_info
	{
		sOnline
	};
	

new
	pInfo[MAX_PLAYERS][player_info],
	sInfo[server_info],
	backpack_index[MAX_PLAYERS][MAX_BACKPACK_SLOTS],
	backpack_number[MAX_PLAYERS][MAX_BACKPACK_SLOTS];

#define PlayerConnect			sInfo[sOnline]++
#define PlayerDisconnect		sInfo[sOnline]--
