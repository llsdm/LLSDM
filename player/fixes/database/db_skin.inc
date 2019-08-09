#if defined DB_SKIN
	#endinput
#endif
#define DB_SKIN

public OnGameModeInit()
{
	for (new i = 1; i <= 300; i++)
		AddPlayerClass(i,349.0453,193.2271,1014.1797, 286.25,-1,-1,-1,-1,-1,-1);

	#if defined db_skin_OnGameModeInit
		db_skin_OnGameModeInit();
	#endif

	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit db_skin_OnGameModeInit
#if  defined db_skin_OnGameModeInit
	forward db_skin_OnGameModeInit();
#endif

public OnPlayerRequestSpawn(playerid) 
{ 
	if (pInfo[playerid][pSkin] == 0)
	{
		pInfo[playerid][pSkin] = GetPlayerSkin(playerid);
		CreateNewAccount(playerid, pInfo[playerid][pPassword], pInfo[playerid][pEmail], pInfo[playerid][pSkin]);
		return 1;
	}

	#if defined db_skin_OnPlayerRequestSpawn
		db_skin_OnPlayerRequestSpawn(playerid);
	#endif

	return 1;
}

#if defined _ALS_OnPlayerRequestSpawn
	#undef OnPlayerRequestSpawn
#else
	#define _ALS_OnPlayerRequestSpawn
#endif
#define OnPlayerRequestSpawn db_skin_OnPlayerRequestSpawn
#if  defined db_skin_OnPlayerRequestSpawn
	forward db_skin_OnPlayerRequestSpawn(playerid);
#endif

public OnPlayerRequestClass(playerid) 
{
	if (GetPlayerState(playerid) == PLAYER_STATE_WASTED)
		SpawnPlayer(playerid);

	#if defined db_skin_OnPlayerRequestClass
		db_skin_OnPlayerRequestClass(playerid);
	#endif

	return 1;
}

#if defined _ALS_OnPlayerRequestClass
	#undef OnPlayerRequestClass
#else
	#define _ALS_OnPlayerRequestClass
#endif
#define OnPlayerRequestClass db_skin_OnPlayerRequestClass
#if  defined db_skin_OnPlayerRequestClass
	forward db_skin_OnPlayerRequestClass(playerid);
#endif

stock PlayerSelection(playerid)
{
	TogglePlayerSpectating(playerid, false);
	SetPlayerInterior(playerid, 3);
	SetPlayerVirtualWorld(playerid, playerid);
	SetPlayerPos(playerid, 349.0453, 193.2271, 1014.1797);
	SetPlayerFacingAngle(playerid, 286.25);
	SetPlayerCameraPos(playerid, 352.9164, 194.5702, 1014.1875);
	SetPlayerCameraLookAt(playerid, 349.0453, 193.2271, 1014.1797);

	return 1;
}
