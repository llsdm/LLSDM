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
	print(!"LLDM Beta");
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
	#if UIV_C_AUTO_SAVE == LLSDM_PARAMS_ON
		SaveExp(playerid);
	#endif
	SaveLife(playerid);

	return 1;
}


public OnPlayerDisconnect(playerid, reason)
{
	PlayerDisconnect;
	GetKillLeader();
	#if LEADER_AUTO_SAVE == LLSDM_PARAMS_OFF
		SaveDeath(playerid);
	#endif
	#if BACKPACK_AUTO_SAVE == LLSDM_PARAMS_OFF
		SaveBackpackLvl(playerid);
		SaveBackpack(playerid);
	#endif
	#if !defined UIV_COLLECTOR
		SaveExp(playerid);
	#endif
	SaveWeapon(playerid);
	SavePosition(playerid);
	SaveLife(playerid);
	SaveHealth(playerid);
	RemovePlayerInfo(playerid);
	return 1;
}
