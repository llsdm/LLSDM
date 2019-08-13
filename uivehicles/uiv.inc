#if defined UIVEHICLE
	#endinput
#endif
#define UIVEHICLE

const
	UIV_ANIMS = 0,
	UIV_TIMER = 300,
	
	UIV_MAX_WEAPON_ID = 13,
	UIV_MAX_KITS = 15,
	UIV_MAX_WEAPONS = 3,
	UIV_MAX_BACKPACKS = 10,
	UIV_MAX_AMMO = 5,
	UIV_MAX_AMMO_IN_TRUCK = 100,

	UIV_COLOR_WHITE = -1,
	UIV_COLOR_YELLOW = 0xFFFFFF00,
	UIV_COLOR_GREY = 0xFFAFAFAF,

	UIV_OPEN_DOORS = LLSDM_PARAMS_ON;

static enum //vehicleid
{
	AMBULANCE = 416,
	COLLECTOR = 428,
	TRUCK = 433,
	POLICE_VAN = 427,
	POLICE_LS = 596,
	POLICE_SF = 597,
	POLICE_LV = 598,
	POLICE_JEEP = 599
}

enum 
	uiv_info
	{
		uiv_index,
		uiv_object1,
		uiv_object2,
		uiv_size,
		bool:uiv_anim,
		Float:uiv_dist,
		bool:uiv_drop,
		bool:uiv_loot,
		uiv_weapon,
		uiv_time,
		uiv_timer,
		bool:uiv_hack,
		bool:uiv_death,
		uiv_pickup,
		uiv_kits,
		uiv_weapons[UIV_MAX_WEAPONS],
		uiv_backpacks,
		uiv_ammo[UIV_MAX_AMMO],
		uiv_ammoID[UIV_MAX_AMMO]
	};

new
	uiv_vehicleid[MAX_PLAYERS],
	uiv[MAX_VEHICLES][uiv_info];

#include "../LLSDM/uivehicles/uiv_collector.inc"
#include "../LLSDM/uivehicles/uiv_ambulance.inc"
#include "../LLSDM/uivehicles/uiv_police.inc"
#include "../LLSDM/uivehicles/uiv_truck.inc"

#include "../LLSDM/uivehicles/uiv_upload.inc"
#include "../LLSDM/uivehicles/uiv_editor.inc"


public OnGameModeInit()
{
	SetTimer(!"ShowUIVehicle", UIV_TIMER, true);

	#if defined uiv_OnGameModeInit
		uiv_OnGameModeInit();
	#endif

	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit uiv_OnGameModeInit
#if  defined uiv_OnGameModeInit
	forward uiv_OnGameModeInit();
#endif

stock CreateUIVehicle(modelid, Float:x, Float:y, Float:z, Float:a, color1 = -1, color2 = -1)
{
	new
		vehicleid,
		Float:py, Float:pz, Float:ry,
		object_1, object_2,
		size,
		Float:dist;

	vehicleid = CreateVehicle(modelid, x, y, z, a, color1, color2, 0);
	PutPlayerInVehicle(0, vehicleid, 0);

	switch (modelid)
	{
		#if defined UIV_AMBULANCE
			case AMBULANCE: py = -3.861553, pz = 0.509192, ry = 0.0, size = 120, dist = 4.5;
		#endif
		#if defined UIV_COLLECTOR
			case COLLECTOR: py = -3.100380, pz = 0.659992, ry = 0.0, size = 100, dist = 3.5;
		#endif
		#if defined UIV_TRUCK
			case TRUCK: py = -4.810566, pz = 1.009996, ry = 0.0, size = 200, dist = 5.3;
		#endif
		#if defined UIV_POLICE
			case POLICE_VAN: py = -3.720993, pz = 0.629997, ry = 0.0, size = 120, dist = 4.6;
			case POLICE_LS, POLICE_SF: py = -2.377349, pz = 0.296921, ry = -83.999946, size = 60, dist = 3.3;
			case POLICE_LV: py = -2.244102, pz = 0.361277, ry = -83.999946, size = 60, dist = 3.3;
			case POLICE_JEEP: py = -2.684899, pz = 0.400614, ry = -13.299999, size = 100, dist = 3.3;
		#endif
	}

	object_1 = CreateDynamicObject(19482, x, y, z, 0.0, 0.0, 0.0, -1, -1, -1, 300.000000);
	object_2 = CreateDynamicObject(19482, x, y, z, 0.0, 0.0, 0.0, -1, -1, -1, 300.000000);
	SetDynamicObjectMaterialText(object_1, 0, "F", 130, !"Arial", size-50, 0, -1, 0, 1);
	SetDynamicObjectMaterialText(object_2, 0, !"c", 130, !"Webdings", size, 0, -1, 0, 1);
	AttachDynamicObjectToVehicle(object_1, vehicleid, 0.0, py, pz, 0.000000, ry, -90.000000);
	AttachDynamicObjectToVehicle(object_2, vehicleid, 0.0, py, pz, 0.000000, ry, -90.000000);

	uiv[vehicleid][uiv_size] = size;
	uiv[vehicleid][uiv_object1] = object_1;
	uiv[vehicleid][uiv_object2] = object_2;
	uiv[vehicleid][uiv_dist] = dist;

	SetVehicleDrop(vehicleid);

	return vehicleid;
}

static stock SetVehicleDrop(vehicleid, bool:update = false)
{
	new
		modelid = GetVehicleModel(vehicleid);

	ResettingVehicleDropForPlayer();

	#if UIV_OPEN_DOORS == LLSDM_PARAMS_OFF
		static
			engine, lights, alarm, doors, bonnet, boot, objective;
		GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
		SetVehicleParamsEx(vehicleid, engine, lights, alarm, VEHICLE_PARAMS_ON, bonnet, 0, objective);
	#endif
	SetVehicleParamsCarDoors(vehicleid, 0, 0, 0, 0);
	
	uiv[vehicleid][uiv_loot] = false;
	uiv[vehicleid][uiv_drop] = true;

	switch (modelid)
	{
		#if defined UIV_AMBULANCE
			case AMBULANCE: return uiv[vehicleid][uiv_kits] = random(UIV_MAX_KITS)+1;
		#endif
		#if defined UIV_COLLECTOR
			case COLLECTOR:
			{	
				if (update)
					return 1;

				uiv[vehicleid][uiv_death] =
				uiv[vehicleid][uiv_hack] = false;
				uiv[vehicleid][uiv_time] =
				uiv[vehicleid][uiv_timer] = 0;
				uiv[vehicleid][uiv_pickup] = -1;
				return 1;
			}
		#endif
		#if defined UIV_TRUCK
			case TRUCK:
			{
				for (new i = 0; i < UIV_MAX_AMMO; i++)
				{
					uiv[vehicleid][uiv_ammo][i] = UIV_MAX_AMMO_IN_TRUCK;
					uiv[vehicleid][uiv_ammoID][i] = random(UIV_MAX_WEAPON_ID)+22;
				}
				return 1;
			}
		#endif
		#if defined UIV_POLICE
			case POLICE_VAN:
			{
				for (new i = 0; i < UIV_MAX_WEAPONS; i++)
					uiv[vehicleid][uiv_weapons][i] = random(UIV_MAX_WEAPON_ID)+22;

				uiv[vehicleid][uiv_backpacks] = random(4) == 0 ? 1 : random(UIV_MAX_BACKPACKS)+1;
				return 1;
			}
			case POLICE_LS..POLICE_JEEP: return uiv[vehicleid][uiv_weapon] = random(UIV_MAX_WEAPON_ID)+22;
		#endif
	}

	return 1;
}

stock ResettingVehicleDropForPlayer()
{
	static
		modelid;

	foreach(Player, i)
	{
		modelid = GetVehicleModel(uiv_vehicleid[i]);

		if (modelid == 0 || modelid == COLLECTOR)
			continue;

		TrunkOrRearDoorsOfVehicle(i);
		ClosePlayerDialog(i);
	}
	return 1;
}

forward ShowUIVehicle();
public ShowUIVehicle()
{
	static
		time,
		color,
		size,
		#if UIV_ANIMS == 1
			min_size,
		#endif
		string[3];

	for (new i = 1, j = GetVehiclePoolSize(); i <= j; i++)
	{
		if (!uiv[i][uiv_drop])
			continue;

		#if UIV_ANIMS == 0
			size = uiv[i][uiv_size];
			color = !(_:uiv[i][uiv_loot] + uiv[i][uiv_timer]) ? UIV_COLOR_WHITE : UIV_COLOR_YELLOW;
		#endif
		#if UIV_ANIMS == 1
			min_size = uiv[i][uiv_size] - 30;
			size = !uiv[i][uiv_anim] ? min_size : uiv[i][uiv_size];
			color = !(_:uiv[i][uiv_loot] + uiv[i][uiv_timer]) ? UIV_COLOR_WHITE : UIV_COLOR_YELLOW;
		#endif
		#if UIV_ANIMS == 2
			size = uiv[i][uiv_size];
			color = !(_:uiv[i][uiv_loot] + uiv[i][uiv_timer]) ? (!uiv[i][uiv_anim] ? UIV_COLOR_WHITE : UIV_COLOR_GREY) : UIV_COLOR_YELLOW;
		#endif
		#if UIV_ANIMS != 0
			uiv[i][uiv_anim] = !uiv[i][uiv_anim];
		#endif

		time = uiv[i][uiv_time];
		valstr(string, time);

		SetDynamicObjectMaterialText(uiv[i][uiv_object1], 0, time == 0 ? !"F" : string, 130, !"Arial", size-size/4, 0, color, 0, 1);
		SetDynamicObjectMaterialText(uiv[i][uiv_object2], 0, !"c", 130, !"Webdings", size, 0, color, 0, 1);
	}

	return 1;
}

stock HideUIVehicle(vehicleid)
{
	SetDynamicObjectMaterialText(uiv[vehicleid][uiv_object1], 0, !" ", 130, !"Arial", 100, 0, 0, 0, 1);
	SetDynamicObjectMaterialText(uiv[vehicleid][uiv_object2], 0, !" ", 130, !"Webdings", 100, 0, 0, 0, 1);
	return 1;
}

CMD:v(playerid, params[])
{
	static
		Float:x,
		Float:y,
		Float:z,
		id;
		
	id  = strval(params);

	GetPlayerPos(playerid, x, y, z);
	CreateUIVehicle(id, x, y, z, 90.0);
	//CreateVehicle(id, x, y, z, 90.0, -1, -1, 0);
	PutPlayerInVehicle(playerid, 1, 0);
	//CreateUIVehicle(id, 1557.4998,-1308.3341,16.9039,267.8281);
	return 1;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if (HOLDING(KEY_SECONDARY_ATTACK))
	{
		static
			modelid,
			Float:x, Float:y, Float:z, Float:a,
			Float:dist;

		for (new i = 1, j = GetVehiclePoolSize(); i <= j; i++)
		{
			if (IsVehicleStreamedIn(i, playerid))
			{		
				if (!uiv[i][uiv_drop])
					continue;

				if (uiv[i][uiv_loot])
					continue;

				dist = uiv[i][uiv_dist];
				GetVehicleTrunk(i, x, y, z, dist, a);

				if (IsPlayerInRangeOfPoint(playerid, 2.0, x, y, z))
				{
					ClearAnimations(playerid);
					SetPlayerFacingAngle(playerid, a);
					modelid = GetVehicleModel(i);

					switch (modelid)
					{
						#if defined UIV_AMBULANCE
							case AMBULANCE: return GiveKit(playerid, i);
						#endif
						#if defined UIV_COLLECTOR
							case COLLECTOR: return OpenCollectorVehicle(playerid, i);
						#endif
						#if defined UIV_TRUCK
							case TRUCK: return GiveAmmo(playerid, i);
						#endif
						#if defined UIV_POLICE
							case POLICE_VAN: return GiveWeapons(playerid, i);
							case POLICE_LS..POLICE_JEEP: return GiveWeapon(playerid, uiv[i][uiv_weapon], i);
						#endif
					}

					return 1;
				}
			}
		}
	}

	#if defined uiv_OnPlayerKeyStateChange
		uiv_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	#endif

	return 1;
}

#if defined _ALS_OnPlayerKeyStateChange
	#undef	OnPlayerKeyStateChange
#else
	#define	_ALS_OnPlayerKeyStateChange
#endif
#define OnPlayerKeyStateChange	uiv_OnPlayerKeyStateChange
#if defined uiv_OnPlayerKeyStateChange
	forward uiv_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif

public OnPlayerDeath(playerid, killerid, reason)
{
	if (uiv_vehicleid[playerid] != 0)
		TrunkOrRearDoorsOfVehicle(playerid);

	#if defined uiv_OnPlayerDeath
		uiv_OnPlayerDeath(playerid, killerid, reason);
	#endif

	return 1;
}

#if defined _ALS_OnPlayerDeath
	#undef OnPlayerDeath
#else
	#define _ALS_OnPlayerDeath
#endif
#define  OnPlayerDeath uiv_OnPlayerDeath
#if defined uiv_OnPlayerDeath
	forward uiv_OnPlayerDeath(playerid, killerid, reason);
#endif


public OnPlayerDisconnect(playerid, reason)
{
	if (uiv_vehicleid[playerid] != 0)
		TrunkOrRearDoorsOfVehicle(playerid);

	#if defined uiv_OnPlayerDisconnect
		uiv_OnPlayerDisconnect(playerid, reason);
	#endif

	return 1;
}

#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define  OnPlayerDisconnect uiv_OnPlayerDisconnect
#if defined uiv_OnPlayerDisconnect
	forward uiv_OnPlayerDisconnect(playerid, reason);
#endif

stock TrunkOrRearDoorsOfVehicle(playerid, vehicleid = 0)
{
	static
		modelid,
		engine, lights, alarm, doors, bonnet, boot, objective, trunk;

	if (vehicleid != 0)
	{
		uiv_vehicleid[playerid] = vehicleid;
		uiv[vehicleid][uiv_loot] = true;
		trunk = 1;
	}
	else
	{
		vehicleid = uiv_vehicleid[playerid];
		uiv[vehicleid][uiv_loot] = false;
		trunk =
		uiv_vehicleid[playerid] = 0;
	}

	modelid = GetVehicleModel(vehicleid);

	switch (modelid)
	{
		case AMBULANCE, POLICE_VAN:
		{
			GetVehicleParamsCarDoors(vehicleid, doors, bonnet, trunk, trunk);
			SetVehicleParamsCarDoors(vehicleid, doors, bonnet, 1, 1);
		}
		case POLICE_LS..POLICE_JEEP:
		{
			GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
			SetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, trunk, objective);
		}
	}

	return 1;
}

stock GetVehicleTrunk(vehicleid, &Float:x, &Float:y, &Float:z, Float:distance, &Float:angle)
{
	new 
		Float:dis;
	dis = dis/2.0 - distance;
	GetVehiclePos(vehicleid, x, y, z);
	GetVehicleZAngle(vehicleid, angle);
	x += (dis * floatsin(-angle, degrees));
	y += (dis * floatcos(-angle, degrees));
	return 1;
}
