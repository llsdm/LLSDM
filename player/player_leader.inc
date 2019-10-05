#if defined PLAYER_LEADER
	#endinput
#endif
#define PLAYER_LEADER

static enum
{
	PLAYER_LEADER_MONEY = 100,
	PLAYER_LEADER_KILL_BONUS = 2
};

const
	PLAYER_LEADER_AUTO_SAVE = LLSDM_PARAMS_ON;

static
	leaderid = -1;

stock GetKillLeader()
{
	static const
		str[] = "%s - новый лидер";

	new
		string[sizeof str + MAX_PLAYER_NAME - 2],
		playerid,
		leader_time,
		kills;

	foreach (Player, i)
	{
		if (pInfo[i][pKillsLife] == kills)
		{
			if (pInfo[i][pTimeKill] > leader_time)
			{
				leader_time = pInfo[i][pTimeKill];
				kills = pInfo[i][pKillsLife];
				playerid = i;
			}
		}
		else if (pInfo[i][pKillsLife] > kills)
		{
			leader_time = pInfo[i][pTimeKill];
			kills = pInfo[i][pKillsLife];
			playerid = i;
		}
	}

	if (leaderid != playerid && kills > 0)
	{
		leaderid = playerid;
		pInfo[leaderid][pLeader] = true;
		format(string, sizeof string, str, pInfo[leaderid][pName]);
		SendClientMessageToAll(COLOR_LIME, string);
	}

	#if defined BILLBOARDS
		UpdateBillboard(leaderid, kills);

		foreach (Player, i)
		{
			Streamer_Update(i, STREAMER_TYPE_OBJECT);
		}
	#endif

	return 1;
}

static stock GivePlayerExperience(playerid, reason, kill_bonus)
{

	new
		weaponid = GetWeaponIndex(reason),
		kills_life = pInfo[playerid][pKillsLife],
		experience = pInfo[playerid][pWeaponExp][weaponid],
		money = (kills_life*PLAYER_LEADER_MONEY)*kill_bonus;
	
	#if LLSDM_RESPAWN_WITH_SAVED == 0
		pInfo[playerid][pExpLife] += experience;
	#endif
	pInfo[playerid][pExp] += experience;
	pInfo[playerid][pMoney] += money;
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

	return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
	new
		leader_update,
		kill_bonus = 1;

	#if LLSDM_RESPAWN_WITH_SAVED == 0
		pInfo[playerid][pMoney] =
		pInfo[playerid][pExpLife] =
	#endif
	pInfo[playerid][pKillsLife] =
	pInfo[playerid][pTimeKill] = 0;
	pInfo[playerid][pDeaths]++;

	#if defined TD_PLAYER_HUD
		UpdateHudKills(playerid);
		UpdateHudExperience(playerid);
	#endif
	
	#if PLAYER_LEADER_AUTO_SAVE == LLSDM_PARAMS_ON
		SaveDeath(playerid);
		SaveExp(playerid);
	#endif

	if (killerid != INVALID_PLAYER_ID)
	{
		if (playerid == leaderid && playerid != killerid)
		{
			kill_bonus = PLAYER_LEADER_KILL_BONUS;
			pInfo[playerid][pLeader] = false;
			GiveWeaponExpCardsPro(killerid, 1);
			leader_update = 1;
			SendClientMessage(killerid, COLOR_LIME, !"Вы убили лидера");
			GetKillLeader();
		}
		else if (killerid != leaderid && playerid != killerid)
		{
			leader_update = 1;
			GiveWeaponExpCards(killerid, 1);
			GetKillLeader();
		}

		if (killerid == leaderid && leader_update == 0 && playerid != killerid)
		{
			kill_bonus = PLAYER_LEADER_KILL_BONUS;
			GiveWeaponExpCardsPro(killerid, 1);
		}

		pInfo[killerid][pKillsLife]++;
		pInfo[killerid][pKills]++;
		pInfo[killerid][pTimeKill] = gettime();
		
		GivePlayerExperience(killerid, reason, kill_bonus);

		#if defined TD_PLAYER_HUD
			UpdateHudKills(killerid);
			UpdateHudExperience(killerid);
		#endif

		#if PLAYER_LEADER_AUTO_SAVE == LLSDM_PARAMS_ON
			SaveDeath(killerid);
			SaveExp(killerid);
		#endif
	}

	#if PLAYER_LEADER_AUTO_SAVE == LLSDM_PARAMS_ON
		SaveDeath(playerid);
		SaveExp(playerid);
	#endif

	#if defined player_leader_OnPlayerDeath
		player_leader_OnPlayerDeath(playerid, killerid, reason);
	#endif

	return 1;
}

#if defined _ALS_OnPlayerDeath
	#undef OnPlayerDeath
#else
	#define _ALS_OnPlayerDeath
#endif
#define OnPlayerDeath player_leader_OnPlayerDeath
#if defined player_leader_OnPlayerDeath
	forward player_leader_OnPlayerDeath(playerid, killerid, reason);
#endif