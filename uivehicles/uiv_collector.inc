#if defined UIV_COLLECTOR
	#endinput
#endif
#define UIV_COLLECTOR

#if !defined YellowPlayerIcon
	#define YellowPlayerIcon(%0) \
		(SetPlayerColor(%0, COLOR_YELLOW))
#endif

static enum
{
	UIV_COL_GIVE_PLAYER_EXP = 1,
	UIV_COL_GIVE_PLAYER_MONEY = 5,
	UIV_COL_TIME_TO_HACH = 3,
	UIV_COL_TIMER_SPEED_RESPAWN_BAG = 15000,
	UIV_COL_PLAYER_TIMER_SPEED = 5000,
	
	#if defined PLAYER_AFK_CHECKER
		UIV_COL_TIME_SEC_IN_AFK = 20,
		UIV_COL_TIME_IN_AFK = UIV_COL_TIME_SEC_IN_AFK/(UIV_COL_PLAYER_TIMER_SPEED/1000),
	#endif
	
	UIV_COL_AUTO_SAVE = LLSDM_PARAMS_ON
};

static
	collector_vehicleid[MAX_PLAYERS],
	collector_timer_money[MAX_PLAYERS],
	collector_playerid[LLSDM_MAX_PLAYERS_WITH_BAG] = {-1, ...};
	
#if defined PLAYER_AFK_CHECKER
	static
		collector_afk_checker[MAX_PLAYERS char];
#endif

stock OpenCollectorVehicle(playerid, vehicleid)
{
	if (uiv[vehicleid][uiv_timer] > 0)
	{
		return 0;
	}

	if (uiv[vehicleid][uiv_hack])
	{
		return TakePlayerBagWithMoney(playerid, vehicleid);
	}
	else
	{
		uiv[vehicleid][uiv_time] = UIV_COL_TIME_TO_HACH;
		uiv[vehicleid][uiv_timer] = SetTimerEx(!"CollectorVehicleTimer", 1000, true, "ii", playerid, vehicleid);
	}

	return 1;
}

forward CollectorVehicleTimer(playerid, vehicleid);
public CollectorVehicleTimer(playerid, vehicleid)
{
	static
		deaths,
		Float:x, Float:y, Float:z;

	GetVehiclePos(vehicleid, x, y, z);

	uiv[vehicleid][uiv_time]--;

	if (uiv[vehicleid][uiv_time] > 0)
	{
		if (pInfo[playerid][pDeaths] != deaths)
		{
			uiv[vehicleid][uiv_death] = true;
		}

		deaths = pInfo[playerid][pDeaths];
			
		if (uiv[vehicleid][uiv_death])
		{
			return 1;
		}

		if (!IsPlayerInRangeOfPoint(playerid, 20.0, x, y, z))
		{
			KillTimer(uiv[vehicleid][uiv_timer]);

			uiv[vehicleid][uiv_time] =
			uiv[vehicleid][uiv_timer] = 0;
		}

		return 1;
	}

	KillTimer(uiv[vehicleid][uiv_timer]);
	SetVehicleParamsCarDoors(vehicleid, 0, 0, 1, 1);

	uiv[vehicleid][uiv_hack] = true;
	uiv[vehicleid][uiv_death] = false;
	uiv[vehicleid][uiv_time] =
	uiv[vehicleid][uiv_timer] = 0;

	return 1;
}

static stock TakePlayerBagWithMoney(playerid, vehicleid)
{
	if (pInfo[playerid][pBag])
	{
		return 0;
	}

	new 
		str[18] = !"Игрок {E3E35D}";

	strcat(str, pInfo[playerid][pName]);
	strcat(str, !" {C8D8E3}взял сумку с деньгами");
	SendClientMessageToAll(COLOR_SFTIMES, str);
	YellowPlayerIcon(playerid);
	AddPlayerIDInArrayCollector(playerid);

	collector_timer_money[playerid] = SetTimerEx(!"BigMoneyRewardTimer", UIV_COL_PLAYER_TIMER_SPEED, true, "i", playerid);
	pInfo[playerid][pBag] = true;
	sInfo[sPlayersWithBag]++;

	AttachBagToPlayer(playerid);

	if (uiv[vehicleid][uiv_pickup] != -1)
	{
		DestroyPickup(uiv[vehicleid][uiv_pickup]);
		KillTimer(uiv[vehicleid][uiv_timer]);
		uiv[vehicleid][uiv_timer] = 0;
		uiv[vehicleid][uiv_pickup] = -1;
	}
	else if (collector_vehicleid[playerid] == 0)
	{
		uiv[vehicleid][uiv_drop] = false;
		HideUIVehicle(vehicleid);
	}

	collector_vehicleid[playerid] = vehicleid;

	return 1;
}

forward BigMoneyRewardTimer(playerid);
public BigMoneyRewardTimer(playerid)
{
	#if defined PLAYER_AFK_CHECKER
		if (IsPlayerAFK(playerid))
		{
			if (++collector_afk_checker{playerid} == UIV_COL_TIME_IN_AFK)
			{
				new
					vehicleid = collector_vehicleid[playerid];

				SetVehicleParamsCarDoors(vehicleid, 0, 0, 0, 0);
				KillTimer(collector_timer_money[playerid]);
				RemovePlayerAttachedObject(playerid, AMMU_SLOT_MONEY_BAG);
				ClearPlayerIDFromArrayCollector(playerid);
				InvisiblePlayerIcon(playerid);

				uiv[vehicleid][uiv_timer] = 0;
				uiv[vehicleid][uiv_pickup] = -1;
				uiv[vehicleid][uiv_drop] = true;
				uiv[vehicleid][uiv_hack] = false;

				collector_vehicleid[playerid] =
				collector_timer_money[playerid] =
				collector_afk_checker{playerid} =
				pInfo[playerid][pBag] = false;
				
				sInfo[sPlayersWithBag]--;
			}

			return 0;
		}
	#endif

	#if LLSDM_RESPAWN_WITH_SAVED == 0
		pInfo[playerid][pExpLife] += UIV_COL_GIVE_PLAYER_EXP;
	#endif
	pInfo[playerid][pExp] += UIV_COL_GIVE_PLAYER_EXP;
	pInfo[playerid][pMoney] += UIV_COL_GIVE_PLAYER_MONEY;
	pInfo[playerid][pBagMoney] += UIV_COL_GIVE_PLAYER_MONEY;
	#if LLSDM_RESPAWN_WITH_SAVED == 1
		if (pInfo[playerid][pExp] > LLSDM_MAX_VALUER_MONEY_EXP)
		{
			pInfo[playerid][pExp] = LLSDM_MAX_VALUER_MONEY_EXP;
		}
		if (pInfo[playerid][pMoney] > LLSDM_MAX_VALUER_MONEY_EXP)
		{
			pInfo[playerid][pMoney] = LLSDM_MAX_VALUER_MONEY_EXP;
		}
	#endif

	#if defined PLAYER_AFK_CHECKER
		collector_afk_checker{playerid} = 0;
	#endif

	#if defined TD_PLAYER_HUD
		UpdateHudExperience(playerid);
	#endif

	#if UIV_COL_AUTO_SAVE == LLSDM_PARAMS_ON
		if (pInfo[playerid][pBagMoney] % 100 == 0)
		{
			SaveExp(playerid);
		}
	#endif
	
	return 1;
}

stock DeathPlayerWithBagMoney(playerid)
{
	if (!pInfo[playerid][pBag])
	{
		return 0;
	}
	
	static
		vehicleid,
		Float:x, Float:y, Float:z;

	GetPlayerPos(playerid, x, y, z);
	vehicleid = collector_vehicleid[playerid];
	uiv[vehicleid][uiv_pickup] = CreatePickup(1550, 3, x, y, z, -1);
	uiv[vehicleid][uiv_timer] = SetTimerEx(!"RestoreCollectorVehicleTimer", UIV_COL_TIMER_SPEED_RESPAWN_BAG, false, "ii", playerid, vehicleid);
	KillTimer(collector_timer_money[playerid]);
	RemovePlayerAttachedObject(playerid, AMMU_SLOT_MONEY_BAG);
	ClearPlayerIDFromArrayCollector(playerid);
	collector_timer_money[playerid] =
	collector_vehicleid[playerid] =
	pInfo[playerid][pBag] = false;
	sInfo[sPlayersWithBag]--;
	InvisiblePlayerIcon(playerid);

	return 1;
}

forward RestoreCollectorVehicleTimer(playerid, vehicleid);
public RestoreCollectorVehicleTimer(playerid, vehicleid)
{
	SetVehicleParamsCarDoors(vehicleid, 0, 0, 0, 0);
	DestroyPickup(uiv[vehicleid][uiv_pickup]);

	uiv[vehicleid][uiv_timer] = 0;
	uiv[vehicleid][uiv_pickup] = -1;
	uiv[vehicleid][uiv_drop] = true;
	uiv[vehicleid][uiv_hack] = false;
	
	return 1;
}

stock AttachBagToPlayer(playerid)
{
	if (pInfo[playerid][pBag])
	{
		if (pInfo[playerid][pBackpackLevel] != 0)
		{
			return SetPlayerAttachedObject(playerid, AMMU_SLOT_MONEY_BAG, 1550, 1,0.098999, -0.186999, 0.175999, -104.399940, 82.500068, 170.299896, 0.475999, 0.486000, 0.756996);
		}
		else
		{
			return SetPlayerAttachedObject(playerid, AMMU_SLOT_MONEY_BAG, 1550, 1, 0.154998, -0.157998, 0.070998, -104.399940, 82.500068, -118.700164, 0.475998, 0.486000, 0.756995);
		}
	}
	else
	{
		return RemovePlayerAttachedObject(playerid, AMMU_SLOT_MONEY_BAG);
	}
}

static stock AddPlayerIDInArrayCollector(playerid)
{
	for (new i = 0; i < MAX_COLLECTOR_VEHICLES; i++)
	{
		if (collector_playerid[i] == -1)
		{
			return collector_playerid[i] = playerid;
		}
	}

	return 1;
}

stock ClearPlayerIDFromArrayCollector(playerid)
{
	for (new i = 0, index_i = 0; i < MAX_COLLECTOR_VEHICLES; i++)
	{
		if (collector_playerid[i] == playerid)
		{
			index_i = i == MAX_COLLECTOR_VEHICLES - 1 ? 0 : 1;
			collector_playerid[i] = collector_playerid[i+index_i];
			collector_playerid[i+index_i] = -1;
			return i;
		}
	}

	return -1;
}

stock GetPlayerIDInArrayCollector(index)
{
	return collector_playerid[index];
}

public OnPlayerPickUpPickup(playerid, pickupid)
{
	for (new i = 1, j = GetVehiclePoolSize(); i <= j; i++)
	{
		if (pickupid == uiv[i][uiv_pickup])
		{
			TakePlayerBagWithMoney(playerid, i);
			break;
		}
	}
	
	#if defined uiv_collector_OnPlayerPickup
		uiv_collector_OnPlayerPickup(playerid, pickupid);
	#endif

	return 1;
}

#if defined _ALS_OnPlayerPickUpPickup
	#undef OnPlayerPickUpPickup
#else
	#define _ALS_OnPlayerPickUpPickup
#endif
#define OnPlayerPickUpPickup uiv_collector_OnPlayerPickup
#if defined uiv_collector_OnPlayerPickup
	forward uiv_collector_OnPlayerPickup(playerid, pickupid);
#endif

public OnPlayerDeath(playerid, killerid, reason)
{
	DeathPlayerWithBagMoney(playerid);

	#if defined PLAYER_AFK_CHECKER
		collector_afk_checker{playerid} = 0;
	#endif

	#if defined uiv_collector_OnPlayerDeath
		uiv_collector_OnPlayerDeath(playerid, killerid, reason);
	#endif

	return 1;
}

#if defined _ALS_OnPlayerDeath
	#undef OnPlayerDeath
#else
	#define _ALS_OnPlayerDeath
#endif
#define OnPlayerDeath uiv_collector_OnPlayerDeath
#if defined uiv_collector_OnPlayerDeath
	forward uiv_collector_OnPlayerDeath(playerid, killerid, reason);
#endif

public OnPlayerDisconnect(playerid, reason)
{
	DeathPlayerWithBagMoney(playerid);

	#if defined PLAYER_AFK_CHECKER
		collector_afk_checker{playerid} = 0;
	#endif

	#if defined uiv_collector_OnPlayerDis
		uiv_collector_OnPlayerDis(playerid, reason);
	#endif

	return 1;
}

#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect uiv_collector_OnPlayerDis
#if defined uiv_collector_OnPlayerDis
	forward uiv_collector_OnPlayerDis(playerid, reason);
#endif

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	new
		modelid = GetVehicleModel(vehicleid);

	if (modelid == COLLECTOR)
	{
		SetVehicleParamsEx(vehicleid, VEHICLE_PARAMS_OFF, VEHICLE_PARAMS_OFF, VEHICLE_PARAMS_OFF, VEHICLE_PARAMS_ON, VEHICLE_PARAMS_OFF, VEHICLE_PARAMS_OFF, VEHICLE_PARAMS_OFF);
	}

	#if defined uiv_collector_OnPlayerEnterVeh
		uiv_collector_OnPlayerEnterVeh(playerid, vehicleid, ispassenger);
	#endif

	return 1;
}

#if defined _ALS_OnPlayerEnterVehicle
	#undef OnPlayerEnterVehicle
#else
	#define _ALS_OnPlayerEnterVehicle
#endif
#define OnPlayerEnterVehicle uiv_collector_OnPlayerEnterVeh
#if defined uiv_collector_OnPlayerEnterVeh
	forward uiv_collector_OnPlayerEnterVeh(playerid, vehicleid, ispassenger);
#endif