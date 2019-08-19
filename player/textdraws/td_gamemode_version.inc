#if defined TD_GAMEMODE_VERSION
	#endinput
#endif
#define TD_GAMEMODE_VERSION

static enum
{
	TD_GAMEMODE_VERSION_SHOW = LLSDM_PARAMS_ON
};

static
	Text:td_gm_version;

public OnGameModeInit()
{
	td_gm_version = TextDrawCreate(638.3331, 440.1333, !""#SETTING_VERSION"");
	TextDrawLetterSize(td_gm_version, 0.1709, 0.8241);
	TextDrawAlignment(td_gm_version, 3);
	TextDrawColor(td_gm_version, -1);
	TextDrawBackgroundColor(td_gm_version, 255);
	TextDrawFont(td_gm_version, 1);
	TextDrawSetProportional(td_gm_version, 1);
	TextDrawSetShadow(td_gm_version, 0);

	#if defined td_gm_version_OnGameModeInit
		td_gm_version_OnGameModeInit();
	#endif

	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit td_gm_version_OnGameModeInit
#if  defined td_gm_version_OnGameModeInit
	forward td_gm_version_OnGameModeInit();
#endif

public OnPlayerConnect(playerid)
{
	#if TD_GAMEMODE_VERSION_SHOW == LLSDM_PARAMS_ON
		TextDrawShowForPlayer(playerid, td_gm_version);
	#endif

	#if defined td_gm_version_OnPlayerConnect
		td_gm_version_OnPlayerConnect(playerid);
	#endif

	return 1;
}

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect td_gm_version_OnPlayerConnect
#if defined td_gm_version_OnPlayerConnect
	forward td_gm_version_OnPlayerConnect(playerid);
#endif