#if defined TD_PLAYER_MAP
	#endinput
#endif
#define TD_PLAYER_MAP

static enum
{
	TD_MAP_TIMER_SPEED = 1000
};

static enum Float:
{
	TD_MAP_POS_X = 206.5200,
	TD_MAP_POS_Y = 82.7549,
	TD_MAP_SIZE_X = 226.6600,
	TD_MAP_SIZE_Y = 282.0700,
	TD_MAP_POS_ERROR_X = 1.8,
	TD_MAP_POS_ERROR_Y = -7.5
};

static
	bool:td_map_open[MAX_PLAYERS char],
	bool:td_map_show[MAX_PLAYERS char],

	Float:td_map_save_pos[MAX_PLAYERS],
	td_map_player_timer[MAX_PLAYERS],

	Text:td_map,
	Text:td_map_icon,

	PlayerText:td_map_player_n[MAX_PLAYERS][2],
	PlayerText:td_map_player_market[MAX_PLAYERS],
	PlayerText:td_map_markets[MAX_PLAYERS][LLSDM_MAX_PLAYERS_WITH_BAG];

public OnGameModeInit()
{
	//icon
	td_map_icon = TextDrawCreate(601.5297, 109.7599, !"samaps:map");
	TextDrawTextSize(td_map_icon, 33.3300, 41.4700);
	TextDrawAlignment(td_map_icon, 1);
	TextDrawColor(td_map_icon, -1);
	TextDrawBackgroundColor(td_map_icon, 255);
	TextDrawFont(td_map_icon, 4);
	TextDrawSetProportional(td_map_icon, 0);
	TextDrawSetShadow(td_map_icon, 0);

	//map
	td_map = TextDrawCreate(TD_MAP_POS_X, TD_MAP_POS_Y, !"samaps:map");
	TextDrawTextSize(td_map, TD_MAP_SIZE_X, TD_MAP_SIZE_Y);
	TextDrawAlignment(td_map, 1);
	TextDrawColor(td_map, -1);
	TextDrawBackgroundColor(td_map, 255);
	TextDrawFont(td_map, 4);
	TextDrawSetProportional(td_map, 0);
	TextDrawSetShadow(td_map, 0);

	#if defined td_map_OnGameModeInit
		td_map_OnGameModeInit();
	#endif

	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit td_map_OnGameModeInit
#if defined td_map_OnGameModeInit
	forward td_map_OnGameModeInit();
#endif

public OnPlayerConnect(playerid)
{
	//N
	td_map_player_n[playerid][0] = CreatePlayerTextDraw(playerid, 624.8397, 138.7671, !"LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, td_map_player_n[playerid][0], 10.0000, 12.4399);
	PlayerTextDrawAlignment(playerid, td_map_player_n[playerid][0], 1);
	PlayerTextDrawColor(playerid, td_map_player_n[playerid][0], 170);
	PlayerTextDrawBackgroundColor(playerid, td_map_player_n[playerid][0], 255);
	PlayerTextDrawFont(playerid, td_map_player_n[playerid][0], 4);
	PlayerTextDrawSetProportional(playerid, td_map_player_n[playerid][0], 0);
	PlayerTextDrawSetShadow(playerid, td_map_player_n[playerid][0], 0);

	td_map_player_n[playerid][1] = CreatePlayerTextDraw(playerid, 626.4074, 139.3625, !"N");
	PlayerTextDrawLetterSize(playerid, td_map_player_n[playerid][1], 0.2809, 1.1768);
	PlayerTextDrawAlignment(playerid, td_map_player_n[playerid][1], 1);
	PlayerTextDrawColor(playerid, td_map_player_n[playerid][1], -1);
	PlayerTextDrawBackgroundColor(playerid, td_map_player_n[playerid][1], 255);
	PlayerTextDrawFont(playerid, td_map_player_n[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, td_map_player_n[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, td_map_player_n[playerid][1], 0);

	#if defined td_map_OnPlayerConnect
		td_map_OnPlayerConnect(playerid);
	#endif

	return 1;
}

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect td_map_OnPlayerConnect
#if defined td_map_OnPlayerConnect
	forward td_map_OnPlayerConnect(playerid);
#endif

public OnPlayerSpawn(playerid)
{
	if (td_map_show{playerid} == false)
	{
		td_map_show{playerid} = true;

		TextDrawShowForPlayer(playerid, td_map_icon);
		PlayerTextDrawShow(playerid, td_map_player_n[playerid][0]);
		PlayerTextDrawShow(playerid, td_map_player_n[playerid][1]);
	}

	#if defined td_map_OnPlayerSpawn
		td_map_OnPlayerSpawn(playerid);
	#endif

	return 1;
}

#if defined _ALS_OnPlayerSpawn
	#undef OnPlayerSpawn
#else
	#define _ALS_OnPlayerSpawn
#endif
#define OnPlayerSpawn td_map_OnPlayerSpawn
#if defined td_map_OnPlayerSpawn
	forward td_map_OnPlayerSpawn(playerid);
#endif

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if (HOLDING(KEY_NO))
	{
		if (IsPlayerAuthorized(playerid))
		{
			return OpenTextDrawMap(playerid);
		}
		
	}

	#if defined td_map_OnPlayerNewKey
		td_map_OnPlayerNewKey(playerid, newkeys, oldkeys);
	#endif

	return 1;
}

#if defined _ALS_OnPlayerKeyStateChange
	#undef	OnPlayerKeyStateChange
#else
	#define	_ALS_OnPlayerKeyStateChange
#endif
#define OnPlayerKeyStateChange	td_map_OnPlayerNewKey
#if defined td_map_OnPlayerNewKey
	forward td_map_OnPlayerNewKey(playerid, newkeys, oldkeys);
#endif

static stock OpenTextDrawMap(playerid)
{
	if (!td_map_open{playerid})
	{
		td_map_open{playerid} = true;

		//N
		PlayerTextDrawColor(playerid, td_map_player_n[playerid][0], -2147483393);
		PlayerTextDrawSetSelectable(playerid, td_map_player_n[playerid][0], 1); 
		PlayerTextDrawShow(playerid, td_map_player_n[playerid][0]);
		PlayerTextDrawShow(playerid, td_map_player_n[playerid][1]);
		PlayerTextDrawSetString(playerid, td_map_player_n[playerid][1], !"X");

		//map
		TextDrawShowForPlayer(playerid, td_map);

		//player
		CreatePlayerMarket(playerid);

		for (new i = 0; i < MAX_COLLECTOR_VEHICLES; i++)
		{
			td_map_markets[playerid][i] = CreatePlayerTextDraw(playerid, 0.0, 0.0, !" ");
		}

		td_map_player_timer[playerid] = SetTimerEx("UpdateMapMarkets", TD_MAP_TIMER_SPEED, true, "i", playerid);

		SelectTextDraw(playerid, -1523963137);
	}

	return 1;
}

static stock CloseTextDrawMap(playerid)
{
	if (td_map_open{playerid})
	{
		td_map_open{playerid} = false;

		//N
		PlayerTextDrawColor(playerid, td_map_player_n[playerid][0], 170);
		PlayerTextDrawSetSelectable(playerid, td_map_player_n[playerid][0], 0); 
		PlayerTextDrawShow(playerid, td_map_player_n[playerid][0]);
		PlayerTextDrawShow(playerid, td_map_player_n[playerid][1]);
		PlayerTextDrawSetString(playerid, td_map_player_n[playerid][1], !"N");

		//map
		TextDrawHideForPlayer(playerid, td_map);

		KillTimer(td_map_player_timer[playerid]);

		//player
		PlayerTextDrawDestroy(playerid, td_map_player_market[playerid]);

		for (new i = 0; i < MAX_COLLECTOR_VEHICLES; i++)
		{
			PlayerTextDrawDestroy(playerid, td_map_markets[playerid][i]);
		}

		CancelSelectTextDraw(playerid);
	}

	return 1;
}

static stock CreatePlayerMarket(playerid)
{
	new
		Float:x, Float:y, Float:z,
		Float:td_x, Float:td_y;

	GetPlayerPos(playerid, x, y, z); 

	td_x = (TD_MAP_POS_X + TD_MAP_SIZE_X * (x + 3000.0) / 6000.0)+TD_MAP_POS_ERROR_X; 
	td_y = (TD_MAP_POS_Y + TD_MAP_SIZE_Y * (3100.0 - y) / 6000.0)+TD_MAP_POS_ERROR_Y;

	td_map_player_market[playerid] = CreatePlayerTextDraw(playerid, td_x, td_y, !"hud:radar_light");
	PlayerTextDrawTextSize(playerid, td_map_player_market[playerid], -4.0000, 5.0000);
	PlayerTextDrawAlignment(playerid, td_map_player_market[playerid], 1);
	PlayerTextDrawColor(playerid, td_map_player_market[playerid], -16776961);
	PlayerTextDrawBackgroundColor(playerid, td_map_player_market[playerid], 255);
	PlayerTextDrawFont(playerid, td_map_player_market[playerid], 4);
	PlayerTextDrawSetProportional(playerid, td_map_player_market[playerid], 0);
	PlayerTextDrawSetShadow(playerid, td_map_player_market[playerid], 0);

	PlayerTextDrawShow(playerid, td_map_player_market[playerid]);

	return 1;
}

forward UpdateMapMarkets(playerid);
public UpdateMapMarkets(playerid)
{
	new
		targetid,
		Float:x, Float:y, Float:z,
		Float:td_x, Float:td_y;

	GetPlayerPos(playerid, x, y, z);

	if (td_map_save_pos[playerid] != x+y)
	{
		td_map_save_pos[playerid] = x+y; 

		td_x = (TD_MAP_POS_X + TD_MAP_SIZE_X * (x + 3000.0) / 6000.0)+TD_MAP_POS_ERROR_X; 
		td_y = (TD_MAP_POS_Y + TD_MAP_SIZE_Y * (3100.0 - y) / 6000.0)+TD_MAP_POS_ERROR_Y;

		PlayerTextDrawDestroy(playerid, td_map_player_market[playerid]);

		td_map_player_market[playerid] = CreatePlayerTextDraw(playerid, td_x, td_y, !"hud:radar_light");
		PlayerTextDrawTextSize(playerid, td_map_player_market[playerid], -4.0000, 5.0000);
		PlayerTextDrawAlignment(playerid, td_map_player_market[playerid], 1);
		PlayerTextDrawColor(playerid, td_map_player_market[playerid], -16776961);
		PlayerTextDrawBackgroundColor(playerid, td_map_player_market[playerid], 255);
		PlayerTextDrawFont(playerid, td_map_player_market[playerid], 4);
		PlayerTextDrawSetProportional(playerid, td_map_player_market[playerid], 0);
		PlayerTextDrawSetShadow(playerid, td_map_player_market[playerid], 0);

		PlayerTextDrawShow(playerid, td_map_player_market[playerid]);
	}

	for (new i = 0; i < MAX_COLLECTOR_VEHICLES; i++)
	{
		targetid = GetPlayerIDInArrayCollector(i);

		PlayerTextDrawDestroy(playerid, td_map_markets[playerid][i]);
		td_map_markets[playerid][i] = CreatePlayerTextDraw(playerid, td_x, td_y, !"hud:radar_light");

		if (targetid == -1)
		{
			continue;
		}

		if (playerid == targetid)
		{
			continue;
		}

		GetPlayerPos(targetid, x, y, z);

		td_x = (TD_MAP_POS_X + TD_MAP_SIZE_X * (x + 3000.0) / 6000.0) + TD_MAP_POS_ERROR_X; 
		td_y = (TD_MAP_POS_Y + TD_MAP_SIZE_Y * (3100.0 - y) / 6000.0) + TD_MAP_POS_ERROR_Y;

		PlayerTextDrawTextSize(playerid, td_map_markets[playerid][i], -4.0000, 5.0000);
		PlayerTextDrawAlignment(playerid, td_map_markets[playerid][i], 1);
		PlayerTextDrawColor(playerid, td_map_markets[playerid][i], -1);
		PlayerTextDrawBackgroundColor(playerid, td_map_markets[playerid][i], 255);
		PlayerTextDrawFont(playerid, td_map_markets[playerid][i], 4);
		PlayerTextDrawSetProportional(playerid, td_map_markets[playerid][i], 0);
		PlayerTextDrawSetShadow(playerid, td_map_markets[playerid][i], 0);

		PlayerTextDrawShow(playerid, td_map_markets[playerid][i]);
	}

	return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
	CloseTextDrawMap(playerid);

	#if defined td_map_OnPlayerDeath
		td_map_OnPlayerDeath(playerid, killerid, reason);
	#endif

	return 1;
}

#if defined _ALS_OnPlayerDeath
	#undef OnPlayerDeath
#else
	#define _ALS_OnPlayerDeath
#endif
#define OnPlayerDeath td_map_OnPlayerDeath
#if defined td_map_OnPlayerDeath
	forward td_map_OnPlayerDeath(playerid, killerid, reason);
#endif

public OnPlayerDisconnect(playerid, reason)
{
	td_map_open{playerid} =
	td_map_show{playerid} = false;

	KillTimer(td_map_player_timer[playerid]);

	TextDrawHideForPlayer(playerid, td_map);
	TextDrawHideForPlayer(playerid, td_map_icon);

	PlayerTextDrawDestroy(playerid, td_map_player_n[playerid][0]);
	PlayerTextDrawDestroy(playerid, td_map_player_n[playerid][1]);
	PlayerTextDrawDestroy(playerid, td_map_player_market[playerid]);

	for (new i = 0; i < MAX_COLLECTOR_VEHICLES; i++)
	{
		PlayerTextDrawShow(playerid, td_map_markets[playerid][i]);
	}

	CancelSelectTextDraw(playerid);

	#if defined td_map_OnPlayerDisconnect
		td_map_OnPlayerDisconnect(playerid, reason);
	#endif

	return 1;
}

#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect td_map_OnPlayerDisconnect
#if defined td_map_OnPlayerDisconnect
	forward td_map_OnPlayerDisconnect(playerid, reason);
#endif

public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
	if (playertextid == td_map_player_n[playerid][0])
	{
		return CloseTextDrawMap(playerid);
	}

	#if defined td_map_OnClickPlayerTextDraw
		td_map_OnClickPlayerTextDraw(playerid, PlayerText:playertextid);
	#endif

	return 0;
}

#if defined _ALS_OnClickPlayerTextDraw
	#undef OnPlayerClickPlayerTextDraw
#else
	#define _ALS_OnClickPlayerTextDraw
#endif
#define OnPlayerClickPlayerTextDraw td_map_OnClickPlayerTextDraw
#if defined td_map_OnClickPlayerTextDraw
	forward td_map_OnClickPlayerTextDraw(playerid, PlayerText:playertextid);
#endif

public OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	if (clickedid == Text:INVALID_TEXT_DRAW)
	{
		CloseTextDrawMap(playerid);
	}

	#if defined td_map_OnPlayerClickTextDraw
		td_map_OnPlayerClickTextDraw(playerid, Text:clickedid);
	#endif

	return 0;
}

#if defined _ALS_OnPlayerClickTextDraw
	#undef OnPlayerClickTextDraw
#else
	#define _ALS_OnPlayerClickTextDraw
#endif
#define OnPlayerClickTextDraw td_map_OnPlayerClickTextDraw
#if defined td_map_OnPlayerClickTextDraw
	forward td_map_OnPlayerClickTextDraw(playerid, Text:clickedid);
#endif