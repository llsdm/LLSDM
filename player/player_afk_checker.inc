#if defined PLAYER_AFK_CHECKER
	#endinput
#endif
#define PLAYER_AFK_CHECKER

static enum
{
	PLAYER_AFK_TICK = 1000
}

static
	player_afk[MAX_PLAYERS];

stock IsPlayerAFK(playerid)
{
	if (GetTickCount() - player_afk[playerid] > PLAYER_AFK_TICK)
		return 1;
	else
		return 0;
}

public OnPlayerUpdate(playerid)
{
	player_afk[playerid] = GetTickCount();

	#if defined afk_check_OnPlayerUpdate
		afk_check_OnPlayerUpdate(playerid);
	#endif

	return 1;
}

#if defined _ALS_OnPlayerUpdate
	#undef OnPlayerUpdate
#else
	#define _ALS_OnPlayerUpdate
#endif
#define OnPlayerUpdate afk_check_OnPlayerUpdate
#if defined afk_check_OnPlayerUpdate
	forward afk_check_OnPlayerUpdate(playerid);
#endif

public OnPlayerDisconnect(playerid, reason)
{
	player_afk[playerid] = 0;

	#if defined afk_check_OnPlayerDisconnect
		afk_check_OnPlayerDisconnect(playerid, reason);
	#endif

	return 1;
}

#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect afk_check_OnPlayerDisconnect
#if defined afk_check_OnPlayerDisconnect
	forward afk_check_OnPlayerDisconnect(playerid, reason);
#endif
