#if defined PLAYER_LEADER
	#endinput
#endif
#define PLAYER_LEADER

const
	LEADER_AUTO_SAVE = LLSDM_PARAMS_ON;

static
	leader_id = -1;

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

	if (leader_id != playerid)
	{
		leader_id = playerid;
		format(string, sizeof string, str, pInfo[playerid][pName]);
		SendClientMessageToAll(COLOR_LIME, string);
	}

	#if defined BILLBOARDS
		UpdateBillboard(playerid, kills);

		foreach (Player, i)
		{
			Streamer_Update(i, STREAMER_TYPE_OBJECT);
		}
	#endif

	return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
	pInfo[playerid][pMoney] =
	pInfo[playerid][pExpLife] =
	pInfo[playerid][pKillsLife] =
	pInfo[playerid][pTimeKill] = 0;
	pInfo[playerid][pDeaths]++;
	
	#if LEADER_AUTO_SAVE == LLSDM_PARAMS_ON
		SaveDeath(playerid);
	#endif

	if (killerid != INVALID_PLAYER_ID)
	{
		if (playerid == leader_id && playerid != killerid)
		{
			pInfo[killerid][pExp] += 200;
			pInfo[killerid][pExpLife] += 200;
			pInfo[killerid][pMoney] += 100;
			SendClientMessage(killerid, COLOR_LIME, !"Вы убили лидера");
		}

		pInfo[killerid][pKillsLife]++;
		pInfo[killerid][pKills]++;
		pInfo[killerid][pTimeKill] = gettime();
		pInfo[killerid][pExp] += 100;
		pInfo[killerid][pExpLife] += 100;
		pInfo[killerid][pMoney] += 20;

		#if LEADER_AUTO_SAVE == LLSDM_PARAMS_ON
			SaveDeath(killerid);
		#endif
	}

	GetKillLeader();

	#if defined leader_OnPlayerDeath
		leader_OnPlayerDeath(playerid, killerid, reason);
	#endif

	return 1;
}

#if defined _ALS_OnPlayerDeath
	#undef OnPlayerDeath
#else
	#define _ALS_OnPlayerDeath
#endif
#define  OnPlayerDeath leader_OnPlayerDeath
#if defined leader_OnPlayerDeath
	forward leader_OnPlayerDeath(playerid, killerid, reason);
#endif
