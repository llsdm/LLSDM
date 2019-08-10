#if defined LIBRARY
	#endinput
#endif
#define LIBRARY

//server
#include "../LLSDM/colors.inc"
#include "../LLSDM/settings.inc"
#include "../LLSDM/info.inc"
#include "../LLSDM/functions.inc"
#include "../LLSDM/database.inc"

//global
	//maps-remove
	#include "../LLSDM/global/maps/remove_billboards.inc"
#include "../LLSDM/global/billboards.inc"

//player
	//fixes
	#include "../LLSDM/player/fixes/fix_loading_anims.inc"
#include "../LLSDM/player/player_attach_weapon.inc"
#include "../LLSDM/player/player_backpack.inc"
#include "../LLSDM/player/player_kit.inc"
#include "../LLSDM/player/player_spawn.inc"
#include "../LLSDM/player/player_leader.inc"

//systems
#include "../LLSDM/uivehicles/uiv.inc"

//admin
	//CMD
	#include "../LLSDM/admin/CMD/cmd_disconnect.inc"
	#include "../LLSDM/admin/CMD/cmd_go.inc"
	#include "../LLSDM/admin/CMD/cmd_say.inc"
	#include "../LLSDM/admin/CMD/cmd_restart.inc"
#include "../LLSDM/admin/click_map.inc"
