#if defined UIV_COLLECTOR
	#endinput
#endif
#define UIV_COLLECTOR

#define YellowPlayerIcon(%0) \
	(SetPlayerColor(%0, COLOR_YELLOW))

const
	UIV_C_TIME_TO_HACH = 3,
	UIV_C_TIME_TO_RESPAWN_BAG = 15000,
	UIV_C_TIME_TO_TIMER = 5000,
	UIV_C_AUTO_SAVE = LLSDM_PARAMS_ON;


static
	collector_vehicleid[MAX_PLAYERS],
	collector_timer_money[MAX_PLAYERS];

stock OpenCollectorVehicle(playerid, vehicleid)
{
	if (uiv[vehicleid][uiv_timer] > 0)
		return 0;

	if (uiv[vehicleid][uiv_hack])
		return TakePlayerBagWithMoney(playerid, vehicleid);
	else
	{
		uiv[vehicleid][uiv_time] = UIV_C_TIME_TO_HACH;
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
			uiv[vehicleid][uiv_death] = true;

		deaths = pInfo[playerid][pDeaths];
			
		if (uiv[vehicleid][uiv_death])
			return 1;

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
	if (pInfo[playerid][pBag] != 0)
		return 0;

	new 
		str[18] = !"Игрок {E3E35D}";

	strcat(str, pInfo[playerid][pName]);
	strcat(str, !" {C8D8E3}взял сумку с деньгами");
	SendClientMessageToAll(COLOR_SFTIMES, str);
	YellowPlayerIcon(playerid);

	collector_timer_money[playerid] = SetTimerEx(!"BigMoneyRewardTimer", UIV_C_TIME_TO_TIMER, true, "i", playerid);
	pInfo[playerid][pBag] = 1;

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
	if (IsPlayerAFK(playerid))
		return 0;
		
	pInfo[playerid][pExpLife]++;
	pInfo[playerid][pExp]++;
	pInfo[playerid][pMoney]++;
	pInfo[playerid][pBagMoney]++;

	#if UIV_C_AUTO_SAVE == LLSDM_PARAMS_ON
		if (pInfo[playerid][pBagMoney] % 100 == 0)
			SaveExp(playerid);
	#endif
	
	return 1;
}

stock DeathPlayerWithBagMoney(playerid)
{
	if (pInfo[playerid][pBag] == 0)
		return 0;
	
	static
		vehicleid,
		Float:x, Float:y, Float:z;

	GetPlayerPos(playerid, x, y, z);
	vehicleid = collector_vehicleid[playerid];
	uiv[vehicleid][uiv_pickup] = CreatePickup(1550, 3, x, y, z, -1);
	uiv[vehicleid][uiv_timer] = SetTimerEx(!"RestoreCollectorVehicleTimer", UIV_C_TIME_TO_RESPAWN_BAG, false, "ii", playerid, vehicleid);
	KillTimer(collector_timer_money[playerid]);
	RemovePlayerAttachedObject(playerid, AMMU_SLOT_MONEY_BAG);
	collector_timer_money[playerid] =
	collector_vehicleid[playerid] = 0;
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
	if (pInfo[playerid][pBag] == 1)
	{
		if (pInfo[playerid][pBackpackLvl] != 0)
			return SetPlayerAttachedObject(playerid, AMMU_SLOT_MONEY_BAG, 1550, 1,0.098999, -0.186999, 0.175999, -104.399940, 82.500068, 170.299896, 0.475999, 0.486000, 0.756996);
		else
			return SetPlayerAttachedObject(playerid, AMMU_SLOT_MONEY_BAG, 1550, 1, 0.154998, -0.157998, 0.070998, -104.399940, 82.500068, -118.700164, 0.475998, 0.486000, 0.756995);
	}
	else
	{
		return RemovePlayerAttachedObject(playerid, AMMU_SLOT_MONEY_BAG);
	}
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
	
	#if defined collector_OnPlayerPickUpPickup
		collector_OnPlayerPickUpPickup(playerid, pickupid);
	#endif

	return 1;
}

#if defined _ALS_OnPlayerPickUpPickup
	#undef OnPlayerPickUpPickup
#else
	#define _ALS_OnPlayerPickUpPickup
#endif
#define  OnPlayerPickUpPickup collector_OnPlayerPickUpPickup
#if defined collector_OnPlayerPickUpPickup
	forward collector_OnPlayerPickUpPickup(playerid, pickupid);
#endif

public OnPlayerDeath(playerid, killerid, reason)
{
	pInfo[playerid][pExpLife] =
	pInfo[playerid][pMoney] = 0;

	DeathPlayerWithBagMoney(playerid);

	#if defined collector_OnPlayerDeath
		collector_OnPlayerDeath(playerid, killerid, reason);
	#endif

	return 1;
}

#if defined _ALS_OnPlayerDeath
	#undef OnPlayerDeath
#else
	#define _ALS_OnPlayerDeath
#endif
#define  OnPlayerDeath collector_OnPlayerDeath
#if defined collector_OnPlayerDeath
	forward collector_OnPlayerDeath(playerid, killerid, reason);
#endif

public OnPlayerDisconnect(playerid, reason)
{
	DeathPlayerWithBagMoney(playerid);

	#if defined collector_OnPlayerDisconnect
		collector_OnPlayerDisconnect(playerid, reason);
	#endif

	return 1;
}

#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define  OnPlayerDisconnect collector_OnPlayerDisconnect
#if defined collector_OnPlayerDisconnect
	forward collector_OnPlayerDisconnect(playerid, reason);
#endif

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	new
		modelid = GetVehicleModel(vehicleid);

	if (modelid == COLLECTOR)
		SetVehicleParamsEx(vehicleid, VEHICLE_PARAMS_OFF, VEHICLE_PARAMS_OFF, VEHICLE_PARAMS_OFF, VEHICLE_PARAMS_ON, VEHICLE_PARAMS_OFF, VEHICLE_PARAMS_OFF, VEHICLE_PARAMS_OFF);

	#if defined collector_OnPlayerEnterVehicle
		collector_OnPlayerEnterVehicle(playerid, vehicleid, ispassenger);
	#endif

	return 1;
}

#if defined _ALS_OnPlayerEnterVehicle
	#undef OnPlayerEnterVehicle
#else
	#define _ALS_OnPlayerEnterVehicle
#endif
#define  OnPlayerEnterVehicle collector_OnPlayerEnterVehicle
#if defined collector_OnPlayerEnterVehicle
	forward collector_OnPlayerEnterVehicle(playerid, vehicleid, ispassenger);
#endif
