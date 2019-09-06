#if defined LOST_VENTURAS
	#endinput
#endif
#define LOST_VENTURAS

public OnPlayerConnect(playerid)
{
	RemoveBuildingForPlayer(playerid, 7415, 983.5078, 2560.8984, 19.5078, 0.25);
	RemoveBuildingForPlayer(playerid, 7666, 984.3984, 2563.0625, 27.8125, 0.25);

	#if defined lost_venturas_OnPlayerConnect
		lost_venturas_OnPlayerConnect(playerid);
	#endif

	return 1;
}

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect lost_venturas_OnPlayerConnect
#if defined lost_venturas_OnPlayerConnect
	forward lost_venturas_OnPlayerConnect(playerid);
#endif

public OnGameModeInit()
{
	new
		objectid;

	CreateDynamicObject(7415, 2024.56555, 873.61115, 16.83311,   0.00000, 0.00000, 180.00000, -1, -1, -1, 500.0, 500.0);
	CreateDynamicObject(7666, 2024.02161, 871.40472, 25.02723,   0.00000, 0.00000, 180.00000, -1, -1, -1, 500.0, 500.0);

	objectid = CreateDynamicObject( 19477, 2023.040893, 869.807800, 19.653520, -6.200000, 0.000000, -30.329957, -1, -1, -1, 500.0, 500.0);
	SetDynamicObjectMaterialText(objectid, 0, "LOST", 130, "Calibri", 255, 1, -1, -23296, 1);

	objectid = CreateDynamicObject(19087, 2023.491333, 870.676818, 21.764383, 0.000000, 0.000000, -40.290004, -1, -1, -1, 500.0, 500.0);
	SetDynamicObjectMaterialText(objectid, 0, " ", 130, "Arial", 60, 0, -65536, -65536, 1);

	objectid = CreateDynamicObject( 19087, 2022.598632, 869.127014, 21.7, 0.000000, 0.000000, -40.290004, -1, -1, -1, 500.0, 500.0);
	SetDynamicObjectMaterialText(objectid, 0, " ", 130, "Arial", 60, 0, -65536, -65536, 1);

	#if defined lost_venturas_OnGameModeInit
		lost_venturas_OnGameModeInit();
	#endif

	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit lost_venturas_OnGameModeInit
#if defined lost_venturas_OnGameModeInit
	forward lost_venturas_OnGameModeInit();
#endif