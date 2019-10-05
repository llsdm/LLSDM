#if defined PLAYER_AMMU
	#endinput
#endif
#define PLAYER_AMMU

static
	ammu_tick[MAX_PLAYERS];

public OnPlayerUpdate(playerid)
{
	if ((GetTickCount() - ammu_tick[playerid]) > 113)
	{
		ammu_tick[playerid] = GetTickCount();

		new
			weaponid_now,
			weaponid_t1,
			weaponid_t2,
			weaponid_t3,
			weapon_save,
			second_weapon;

		weaponid_now = GetPlayerWeapon(playerid);
		weaponid_t1 = pInfo[playerid][pWeapons][0];
		weaponid_t2 = pInfo[playerid][pWeapons][1];
		weaponid_t3 = pInfo[playerid][pWeapons][2];
		second_weapon = pInfo[playerid][pSecondWeapon];

		if (second_weapon == 1)
		{
			weapon_save = weaponid_t2;
			weaponid_t2 = weaponid_t3;
			weaponid_t3 = weapon_save;
		}

		if (weaponid_t1 != 0)
		{
			if (weaponid_now != weaponid_t1)
			{
				SetPlayerAttachedObject(playerid, AMMU_SLOT_WEAPON_1, GetWeaponModel(weaponid_t1), 8, -0.079998,-0.039999,0.108999,-103.399993,0.000000,0.000000,0.894000,1.000000,0.870999);
			}
			else
			{
				if (IsPlayerAttachedObjectSlotUsed(playerid, AMMU_SLOT_WEAPON_1))
				{
					RemovePlayerAttachedObject(playerid, AMMU_SLOT_WEAPON_1);
				}
			}
		}
		else if (IsPlayerAttachedObjectSlotUsed(playerid, AMMU_SLOT_WEAPON_1))
		{
			RemovePlayerAttachedObject(playerid, AMMU_SLOT_WEAPON_1);
		}
		if (weaponid_t2 != 0)
		{
			if (weaponid_now != weaponid_t2)
			{
				if (pInfo[playerid][pBackpackLevel] != 0)
				{
					SetPlayerAttachedObject(playerid, AMMU_SLOT_WEAPON_2, GetWeaponModel(weaponid_t2), 1, 0.334998,-0.221999,-0.150997,-134.300094,-17.299985,174.499954,0.893999,1.000000,0.870998);
				}
				else
				{
					SetPlayerAttachedObject(playerid, AMMU_SLOT_WEAPON_2, GetWeaponModel(weaponid_t2), 1, 0.289999, -0.074998, -0.144998, -8.799961, -2.899979, -169.699935, 0.893999,1.000000,0.870998);
				}
			}
			else
			{
				if (IsPlayerAttachedObjectSlotUsed(playerid, AMMU_SLOT_WEAPON_2))
				{
					RemovePlayerAttachedObject(playerid, AMMU_SLOT_WEAPON_2);
				}
			}
		}
		else if (IsPlayerAttachedObjectSlotUsed(playerid, AMMU_SLOT_WEAPON_2))
		{
			RemovePlayerAttachedObject(playerid, AMMU_SLOT_WEAPON_2);
		}
		if (weaponid_t3 != 0)
		{
			if (weaponid_now != weaponid_t3)
			{
				if (pInfo[playerid][pBag])
				{
					SetPlayerAttachedObject(playerid, AMMU_SLOT_WEAPON_3, GetWeaponModel(weaponid_t3), 1, 0.253000, -0.206999, 0.023000, 178.699569, -166.400131, 21.000001, 0.894000, 1.000000, 0.870999);
				}
				else
				{
					SetPlayerAttachedObject(playerid, AMMU_SLOT_WEAPON_3, GetWeaponModel(weaponid_t3), 1, 0.252999, -0.190998, 0.089000, 112.499572, -166.400131, 21.000001, 0.893999, 1.000000, 0.870998);
				}
			}
			else
			{
				if (IsPlayerAttachedObjectSlotUsed(playerid, AMMU_SLOT_WEAPON_3))
				{
					RemovePlayerAttachedObject(playerid, AMMU_SLOT_WEAPON_3);
				}
			}
		}
		else if (IsPlayerAttachedObjectSlotUsed(playerid, AMMU_SLOT_WEAPON_3))
		{
			RemovePlayerAttachedObject(playerid, AMMU_SLOT_WEAPON_3);
		}
	}

	#if defined player_at_weap_OnPlayerUpdate
		player_at_weap_OnPlayerUpdate(playerid);
	#endif

	return 1;
}

#if defined _ALS_OnPlayerUpdate
	#undef OnPlayerUpdate
#else
	#define _ALS_OnPlayerUpdate
#endif
#define OnPlayerUpdate player_at_weap_OnPlayerUpdate
#if defined player_at_weap_OnPlayerUpdate
forward player_at_weap_OnPlayerUpdate(playerid);
#endif

public OnPlayerDeath(playerid, killerid, reason)
{
	#if LLSDM_RESPAWN_WITH_SAVED == 0
		pInfo[playerid][pWeapons][0] =
		pInfo[playerid][pWeapons][1] =
		pInfo[playerid][pWeapons][2] =
		pInfo[playerid][pSecondWeapon] =
		pInfo[playerid][pAmmo][0] =
		pInfo[playerid][pAmmo][1] = 0;

		SaveWeapon(playerid);
	#endif

	RemovePlayerAttachedObject(playerid, AMMU_SLOT_WEAPON_1);
	RemovePlayerAttachedObject(playerid, AMMU_SLOT_WEAPON_2);
	RemovePlayerAttachedObject(playerid, AMMU_SLOT_WEAPON_3);

	ammu_tick[playerid] = 0;

	#if defined player_at_weap_OnPlayerDeath
		player_at_weap_OnPlayerDeath(playerid, killerid, reason);
	#endif

	return 1;
}

#if defined _ALS_OnPlayerDeath
	#undef OnPlayerDeath
#else
	#define _ALS_OnPlayerDeath
#endif
#define OnPlayerDeath player_at_weap_OnPlayerDeath
#if defined player_at_weap_OnPlayerDeath
	forward player_at_weap_OnPlayerDeath(playerid, killerid, reason);
#endif

public OnPlayerDisconnect(playerid, reason)
{
	ammu_tick[playerid] = 0;
	RemovePlayerAttachedObject(playerid, AMMU_SLOT_WEAPON_1);
	RemovePlayerAttachedObject(playerid, AMMU_SLOT_WEAPON_2);
	RemovePlayerAttachedObject(playerid, AMMU_SLOT_WEAPON_3);

	#if defined player_at_weap_OnPlayerDis
		player_at_weap_OnPlayerDis(playerid, reason);
	#endif

	return 1;
}

#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect player_at_weap_OnPlayerDis
#if defined player_at_weap_OnPlayerDis
	forward player_at_weap_OnPlayerDis(playerid, reason);
#endif

static stock GetWeaponModel(weaponid)
{
	switch (weaponid)
	{
		case 1: return 331;
		case 2..8: return weaponid+331;
		case 9: return 341;
		case 10..15: return weaponid+311;
		case 16..18: return weaponid+326;
		case 22..29: return weaponid+324;
		case 30, 31: return weaponid+325;
		case 32: return 372;
		case 33, 34: return weaponid+324;
		case 35..45:  return weaponid+324;
		case 46: return 371;
	}
	return 0;
}