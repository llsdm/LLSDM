#if defined FIX_LOADING_ANIMATIONS
	#endinput
#endif
#define FIX_LOADING_ANIMATIONS

static
	bool:animloading[MAX_PLAYERS char];

PreloadAnimLib(playerid, animlib[])
{
	ApplyAnimation(playerid,animlib,"null",0.0,0,0,0,0,0);
}

public OnPlayerSpawn(playerid)
{
	if (animloading{playerid} == false)
	{
		PreloadAnimLib(playerid, !"BOMBER");
		PreloadAnimLib(playerid, !"RAPPING");
		PreloadAnimLib(playerid, !"SHOP");
		PreloadAnimLib(playerid, !"BEACH");
		PreloadAnimLib(playerid, !"SMOKING");
		PreloadAnimLib(playerid, !"FOOD");
		PreloadAnimLib(playerid, !"ON_LOOKERS");
		PreloadAnimLib(playerid, !"DEALER");
		PreloadAnimLib(playerid, !"CRACK");
		PreloadAnimLib(playerid, !"CARRY");
		PreloadAnimLib(playerid, !"COP_AMBIENT");
		PreloadAnimLib(playerid, !"PARK");
		PreloadAnimLib(playerid, !"INT_HOUSE");
		PreloadAnimLib(playerid, !"FOOD");
		PreloadAnimLib(playerid, !"CRIB");
		PreloadAnimLib(playerid, !"ROB_BANK");
		PreloadAnimLib(playerid, !"JST_BUISNESS");
		PreloadAnimLib(playerid, !"PED");
		PreloadAnimLib(playerid, !"OTB");
		animloading{playerid} = true;
	}

	#if defined fix_la_OnPlayerSpawn
		fix_la_OnPlayerSpawn(playerid);
	#endif

	return 1;
}

public OnPlayerConnect(playerid)
{
	animloading{playerid} = false;

	#if defined fix_la_OnPlayerConnect
		fix_la_OnPlayerConnect(playerid);
	#endif
		
	return 1;
}

#if defined _ALS_OnPlayerSpawn
	#undef OnPlayerSpawn
#else
	#define _ALS_OnPlayerSpawn
#endif
#define OnPlayerSpawn fix_la_OnPlayerSpawn
#if  defined fix_la_OnPlayerSpawn
forward fix_la_OnPlayerSpawn(playerid);
#endif

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect fix_la_OnPlayerConnect
#if  defined fix_la_OnPlayerConnect
forward fix_la_OnPlayerConnect(playerid);
#endif
