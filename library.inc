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
#include "../LLSDM/global/maps/lost_venturas.inc"
#include "../LLSDM/global/billboards.inc"
#include "../LLSDM/global/containers.inc"

//player
	//textdraws
	#include "../LLSDM/player/textdraws/td_gamemode_version.inc"
	#include "../LLSDM/player/textdraws/td_map.inc"
	#include "../LLSDM/player/textdraws/td_hud.inc"
	//database
	#include "../LLSDM/player/database/db_dialogs.inc"
	#include "../LLSDM/player/database/db_ban.inc"
	#include "../LLSDM/player/database/db_skin.inc"
	#include "../LLSDM/player/database/db_connect.inc"
	#include "../LLSDM/player/database/db_create.inc"
	#include "../LLSDM/player/database/db_save.inc"
	#include "../LLSDM/player/database/db_upload.inc"
	#include "../LLSDM/player/database/db_remove.inc"
	//fixes
	#include "../LLSDM/player/fixes/fix_loading_anims.inc"
#include "../LLSDM/player/player_afk_checker.inc"
#include "../LLSDM/player/player_attached_weapon.inc"
#include "../LLSDM/player/player_backpack.inc"
#include "../LLSDM/player/player_kit.inc"
#include "../LLSDM/player/player_spawn.inc"
#include "../LLSDM/player/player_leader.inc"

//admin
	//CMD
	#include "../LLSDM/admin/CMD/cmd_ahelp.inc"
	#include "../LLSDM/admin/CMD/cmd_disconnect.inc"
	#include "../LLSDM/admin/CMD/cmd_go.inc"
	#include "../LLSDM/admin/CMD/cmd_say.inc"
	#include "../LLSDM/admin/CMD/cmd_restart.inc"
#include "../LLSDM/admin/admin_click_map.inc"

//systems
#include "../LLSDM/uivehicles/uiv.inc"