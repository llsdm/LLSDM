#include <a_samp>
#include <crashdetect>
#include <a_mysql>
#include <foreach>
#include <sscanf2>
#include <streamer>
#include <mxdate>
#include <DC_CMD>
#include "../LLSDM/library.inc"

main() {
	#if defined SETTINGS
		print(!""#SETTING_VERSION"");
	#endif
}

public OnGameModeInit()
{
	#if defined SETTINGS
		SendRconCommand(SETTING_HOSTNAME);
		SendRconCommand(SETTING_MODE);
		SendRconCommand(SETTING_LANGUAGE);
		SetWorldTime(SETTING_TIME);
		SetWeather(SETTING_WEATHER);
		ShowNameTags(SETTING_SHOW_NAME_TAGS);
		SetNameTagDrawDistance(SETTING_NAME_DISTANCE);
		LimitPlayerMarkerRadius(SETTING_MARKER_RADIUS);
		LimitGlobalChatRadius(SETTING_CHAT_RADIUS);
		#if SETTING_USE_PED_ANIMS == 1
			UsePlayerPedAnims();
		#endif
		#if SETTING_ENTER_EXITS == 1
			DisableInteriorEnterExits();
		#endif
		#if SETTING_BONUSES == 0
			EnableStuntBonusForAll(0);
		#endif
	#endif

	return 1;
}

public OnPlayerConnect(playerid)
{
	PlayerConnect;
	TogglePlayerSpectating(playerid, true);
	
	return 1;
}

	
public OnPlayerDeath(playerid, killerid, reason)
{
	SaveExp(playerid);
	SaveLife(playerid);

	return 1;
}


public OnPlayerDisconnect(playerid, reason)
{
	PlayerDisconnect;
	GetKillLeader();
	#if PLAYER_LEADER_AUTO_SAVE == LLSDM_PARAMS_OFF
		SaveDeath(playerid);
	#endif
	#if PLAYER_BACKPACK_AUTO_SAVE == LLSDM_PARAMS_OFF
		SaveBackpackLvl(playerid);
		SaveBackpack(playerid);
	#endif
	SaveExp(playerid);
	SaveWeapon(playerid);
	SavePosition(playerid);
	SaveLife(playerid);
	SaveHealth(playerid);
	RemovePlayerInfo(playerid);
	#if defined BILLBOARDS
		GetKillLeader();
	#endif
	
	return 1;
}
