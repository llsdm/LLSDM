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
		Float:pAirPos[4],
		pLife,
		Float:pHealth,
		Float:pLastDamage,
		#if LLSDM_RESPAWN_WITH_SAVED == 0
			pExpLife,
		#endif
		pExp,
		pMoney,
		pBagMoney,
		pKills,
		pTimeKill,
		pKillsLife,
		pDeaths,
		pWeapons[MAX_WEAPONS+1],
		pWeaponExp[MAX_WEAPONS+1],
		pSecondWeapon,
		pAmmo[MAX_WEAPONS],
		bool:pBag,
		pBackpackLevel,
		pBackpackSize,
	};

enum 
	server_info
	{
		sOnline,
		sPlayersWithBag
	};
	
new
	MAX_COLLECTOR_VEHICLES,

	bool:player_authorized[MAX_PLAYERS char],
	pInfo[MAX_PLAYERS][player_info],
	sInfo[server_info],

	backpack_index[MAX_PLAYERS][MAX_BACKPACK_SLOTS],
	backpack_number[MAX_PLAYERS][MAX_BACKPACK_SLOTS];

#define PlayerConnect				sInfo[sOnline]++
#define PlayerDisconnect			sInfo[sOnline]--

#define IsPlayerAuthorized(%0)		player_authorized{%0}
