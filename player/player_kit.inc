#if defined PLAYER_KIT
	#endinput
#endif
#define PLAYER_KIT

#define AttachKitToHand(%0)				SetPlayerAttachedObject(%0, AMMU_SLOT_KIT, 11736, 5, 0.108999, 0.054000, -0.033999, 81.800155, 56.799980, -99.399986, 0.515999, 0.479999, 1.000000)

const
	KIT_AUTO_SAVE = LLSDM_PARAMS_ON,
	Float:KIT_HEALTH = 30.0,
	KIT_TIMER_ANIM = 3500;

static
	kit_timer[MAX_PLAYERS];

stock PlayerKit(playerid)
{
	static
		get_kits;

	if (kit_timer[playerid] > 0)
		return 0;
	
	if (GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
		return 0;

	get_kits = GetPlayerSubject(playerid, bKits);

	if (get_kits == 0)
		return ShowPlayerReminder(playerid, !"У Вас нет аптечки", BACKPACK_REMINDER_DIALOG);

	SetPlayerArmedWeapon(playerid, 0);
	kit_timer[playerid] = SetTimerEx(!"KitTimer", KIT_TIMER_ANIM, false, "i", playerid);
	AttachKitToHand(playerid);
	ApplyAnimation(playerid, !"PED", !"GUM_EAT", 4.1, 0, 0, 0, 0, 0, 1);

	return 1;
}

stock AttachKitToPlayer(playerid)
{
	new
		get_kits = GetPlayerSubject(playerid, bKits);

	if (get_kits != 0)
	{
		if (pInfo[playerid][pBackpackLvl] != 0)
			return SetPlayerAttachedObject(playerid, AMMU_SLOT_KIT, 11736, 1, -0.026000, -0.148000, -0.272000, 175.500106, 12.899991, 4.100001, 0.516000, 0.479999, 1.000000);
		else
			return SetPlayerAttachedObject(playerid, AMMU_SLOT_KIT, 11736, 7, 0.054999, -0.028000, -0.081999, 175.500106, 2.399990, -8.599996, 0.515999, 0.479999, 1.000000);
	}
	else
		return RemovePlayerAttachedObject(playerid, AMMU_SLOT_KIT);
}

forward KitTimer(playerid);
public KitTimer(playerid) 
{
	static
		Float:health;

	if (GetPlayerAnimationIndex(playerid) == 1157)
	{		
		GivePlayerSubject(playerid, bKits, -1);
		#if KIT_AUTO_SAVE == LLSDM_PARAMS_ON
			SaveBackpack(playerid);
		#endif
		GetPlayerHealth(playerid, health);
		SetPlayerHealth(playerid, health + KIT_HEALTH);
		if (health + KIT_HEALTH > 100.0)
		{
			if (health + KIT_HEALTH > 110.0)
			{
				SetPlayerDrunkLevel(playerid, 3000);
				SendClientMessage(playerid, COLOR_ERROR, !"Передозировка");
			}
			SetPlayerHealth(playerid, 100.0);
		}
	}

	kit_timer[playerid] = 0;
	AttachKitToPlayer(playerid);

	return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
	KillTimer(kit_timer[playerid]);
	kit_timer[playerid] = 0;
	RemovePlayerAttachedObject(playerid, AMMU_SLOT_KIT);

	#if defined kit_OnPlayerDeath
		kit_OnPlayerDeath(playerid, killerid, reason);
	#endif
		
	return 1;
}

#if defined _ALS_OnPlayerDeath
	#undef OnPlayerDeath
#else
	#define _ALS_OnPlayerDeath
#endif
#define  OnPlayerDeath kit_OnPlayerDeath
#if defined kit_OnPlayerDeath
	forward kit_OnPlayerDeath(playerid, killerid, reason);
#endif

public OnPlayerDisconnect(playerid, reason)
{
	KillTimer(kit_timer[playerid]);
	kit_timer[playerid] = 0;
	
	RemovePlayerAttachedObject(playerid, AMMU_SLOT_KIT);

	#if defined kit_OnPlayerDisconnect
		kit_OnPlayerDisconnect(playerid, reason);
	#endif

	return 1;
}

#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define  OnPlayerDisconnect kit_OnPlayerDisconnect
#if defined kit_OnPlayerDisconnect
	forward kit_OnPlayerDisconnect(playerid, reason);
#endif
