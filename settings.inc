#if defined SETTINGS
	#endinput
#endif
#define SETTINGS

#define LLSDM_PARAMS_ON					1
#define LLSDM_PARAMS_OFF				0

#define SETTING_HOSTNAME				!"hostname LLSDM"
#define SETTING_MODE					!"gamemodetext LLSDM"
#define SETTING_LANGUAGE				!"language Russia"
#define SETTING_VERSION					"LLSDM v0.4 Beta"
#define SETTING_TIME				        19
#define SETTING_WEATHER					07
#define SETTING_SHOW_NAME_TAGS	                        1
#define SETTING_NAME_DISTANCE			        (20.0)
#define SETTING_MARKER_RADIUS			        (20.0)
#define SETTING_CHAT_RADIUS		                (200.0)
#define SETTING_USE_PED_ANIMS			        1
#define SETTING_ENTER_EXITS				1
#define SETTING_BONUSES					0

#undef MAX_PLAYERS
#define MAX_PLAYERS 					100
#undef MAX_VEHICLES
#define MAX_VEHICLES					1000
#define MAX_WEAPONS				        2

#define MAX_WEAPON_NAME					20
#define MAX_PLAYER_PASSWORD				12
#define MAX_PLAYER_EMAIL				32

//SetPlayerAttachedObject
#define AMMU_SLOT_BACKPACK                              0
#define AMMU_SLOT_MONEY_BAG                             1
#define AMMU_SLOT_KIT             		        2
#define AMMU_SLOT_WEAPON_1 				3
#define AMMU_SLOT_WEAPON_2 				4
#define AMMU_SLOT_WEAPON_3 				5
#define AMMU_SLOT_PROTOCOL				6

#define LLSDM_MAX_BACKPACK_SLOTS			19
#define LLSDM_MAX_ADMIN_LEVELS				10
#define LLSDM_MAX_PLAYERS_WITH_BAG			20
#define LLSDM_RESPAWN_WITH_SAVED			0
#if LLSDM_RESPAWN_WITH_SAVED == 1
	#define LLSDM_MAX_VALUER_MONEY_EXP		999999999
#endif
