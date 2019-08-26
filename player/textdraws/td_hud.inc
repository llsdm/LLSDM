#if defined TD_PLAYER_HUD
	#endinput
#endif
#define TD_PLAYER_HUD

static enum Float:
{
	TD_HUD_SIZE_HEALTH = 74.3300
};

static enum
{
	TD_HUD_TIMER_TIME = 500
};

static enum
	td_hud_weapon
	{
		td_hud_weapon_modelid,
		Float:td_hud_weapon_pos_x,
		Float:td_hud_weapon_pos_y,
		Float:td_hud_weapon_pot_y,
		Float:td_hud_weapon_size
	};

static const
	td_hud_weapon_name[][] =
	{
		"Colt 45",
		"Silenced",
		"Deagle",
		"Shotgun",
		"Sawed-off",
		"Combat",
		"Uzi",
		"MP5",
		"AK-47",
		"M4",
		"Tec-9",
		"Rifle",
		"Sniper"
	},
	td_hud_weapon_ammo[] =
	{
		17, 17, 7, 5, 4, 7, 50, 30, 30, 50, 50, 1, 1
	},
	td_hud_weapon_slots[] =
	{
		2, 2, 2, 3, 3, 3, 4, 4, 5, 5, 4, 6, 6
	},
	td_hud_weapon_model_position[13][td_hud_weapon] =
	{
		{346, 629.3333, -10.9259, 10.0, 2.0},
		{347, 629.3333, -10.9259, 10.0, 2.0},
		{348, 629.3333, -10.9259, 10.0, 2.0},
		{349, 629.3333, -10.9259, 8.0, 2.0},
		{350, 620.7238, -10.9259, 8.0, 2.0},
		{351, 622.8201, -10.8740, 10.0, 2.5},
		{352, 637.9196, -17.9259, 5.0, 2.0},
		{353, 629.3333, -10.9259, 8.0, 2.0},
		{355, 629.3333, -10.9259, 0.0, 2.5},
		{356, 629.3333, -10.9259, 0.0, 2.5},
		{372, 629.3333, -10.9259, 0.0, 2.5},
		{357, 629.3333, -10.9259, 0.0, 2.5},
		{358, 629.3333, -10.9259, 5.0, 2.5}
	};

static
	td_hud_player_timer[MAX_PLAYERS],
	td_hud_player_weaponid[MAX_PLAYERS char] = {255, ...},
	bool:td_hud_player_show[MAX_PLAYERS char],

	Text:td_hud_backgroud[3],
	Text:td_hud_kill_squares[2],
	Text:td_hud_kill_squares_title,
	Text:td_hud_weapon_name_block,
	Text:td_hud_other_squares[3],
	Text:td_hud_health_line,
	Text:td_hud_ex_blocks[2],
	Text:td_hud_ex_icons[2],

	PlayerText:td_hud_player_kills[MAX_PLAYERS],
	PlayerText:td_hud_player_kills_life[MAX_PLAYERS],
	PlayerText:td_hud_player_weapon_model[MAX_PLAYERS] = {PlayerText:-1, ...},
	PlayerText:td_hud_player_weapon_ammo_block[MAX_PLAYERS],
	PlayerText:td_hud_player_weapon_name[MAX_PLAYERS],
	PlayerText:td_hud_player_weapon_ammo[MAX_PLAYERS],
	PlayerText:td_hud_player_health[MAX_PLAYERS],
	PlayerText:td_hud_player_health_line[MAX_PLAYERS],
	PlayerText:td_hud_player_experience[MAX_PLAYERS],
	PlayerText:td_hud_player_money[MAX_PLAYERS];

public OnGameModeInit()
{
	//background
	td_hud_backgroud[0] = TextDrawCreate(561.2539, 76.1604, !"LD_SPAC:white");
	TextDrawTextSize(td_hud_backgroud[0], 78.6600, 27.3798);
	TextDrawAlignment(td_hud_backgroud[0], 1);
	TextDrawColor(td_hud_backgroud[0], 538976511);
	TextDrawBackgroundColor(td_hud_backgroud[0], 255);
	TextDrawFont(td_hud_backgroud[0], 4);
	TextDrawSetProportional(td_hud_backgroud[0], 0);
	TextDrawSetShadow(td_hud_backgroud[0], 0);

	td_hud_backgroud[1] = TextDrawCreate(493.1500, 76.145, !"LD_SPAC:white");
	TextDrawTextSize(td_hud_backgroud[1], 73.3300, 27.3798);
	TextDrawAlignment(td_hud_backgroud[1], 1);
	TextDrawColor(td_hud_backgroud[1], 673720575);
	TextDrawBackgroundColor(td_hud_backgroud[1], 255);
	TextDrawFont(td_hud_backgroud[1], 4);
	TextDrawSetProportional(td_hud_backgroud[1], 0);
	TextDrawSetShadow(td_hud_backgroud[1], 0);

	td_hud_backgroud[2] = TextDrawCreate(493.1762, -4.3442, !"LD_SPAC:white");
	TextDrawTextSize(td_hud_backgroud[2], 150.3300, 87.1100);
	TextDrawAlignment(td_hud_backgroud[2], 1);
	TextDrawColor(td_hud_backgroud[2], 943208703);
	TextDrawBackgroundColor(td_hud_backgroud[2], 255);
	TextDrawFont(td_hud_backgroud[2], 4);
	TextDrawSetProportional(td_hud_backgroud[2], 0);
	TextDrawSetShadow(td_hud_backgroud[2], 0);

	//kills
	td_hud_kill_squares[0] = TextDrawCreate(499.5166, 7.7108, !"LD_SPAC:white");
	TextDrawTextSize(td_hud_kill_squares[0], 54.0000, 67.1900);
	TextDrawAlignment(td_hud_kill_squares[0], 1);
	TextDrawColor(td_hud_kill_squares[0], -1);
	TextDrawBackgroundColor(td_hud_kill_squares[0], 255);
	TextDrawFont(td_hud_kill_squares[0], 4);
	TextDrawSetProportional(td_hud_kill_squares[0], 0);
	TextDrawSetShadow(td_hud_kill_squares[0], 0);

	td_hud_kill_squares[1] = TextDrawCreate(502.5296, 11.4442, !"LD_SPAC:white");
	TextDrawTextSize(td_hud_kill_squares[1], 48.0000, 59.7200);
	TextDrawAlignment(td_hud_kill_squares[1], 1);
	TextDrawColor(td_hud_kill_squares[1], 943208703);
	TextDrawBackgroundColor(td_hud_kill_squares[1], 255);
	TextDrawFont(td_hud_kill_squares[1], 4);
	TextDrawSetProportional(td_hud_kill_squares[1], 0);
	TextDrawSetShadow(td_hud_kill_squares[1], 0);

	td_hud_kill_squares_title = TextDrawCreate(527.0001, 15.3541, !"KILLS");
	TextDrawLetterSize(td_hud_kill_squares_title, 0.2876, 1.0690);
	TextDrawAlignment(td_hud_kill_squares_title, 2);
	TextDrawColor(td_hud_kill_squares_title, -1);
	TextDrawBackgroundColor(td_hud_kill_squares_title, 255);
	TextDrawFont(td_hud_kill_squares_title, 1);
	TextDrawSetProportional(td_hud_kill_squares_title, 1);
	TextDrawSetShadow(td_hud_kill_squares_title, 0);

	//weapon
	td_hud_weapon_name_block = TextDrawCreate(559.5520, 7.6753, !"LD_SPAC:white");
	TextDrawTextSize(td_hud_weapon_name_block, 54.9897, 8.3000);
	TextDrawAlignment(td_hud_weapon_name_block, 1);
	TextDrawColor(td_hud_weapon_name_block, -1);
	TextDrawBackgroundColor(td_hud_weapon_name_block, 255);
	TextDrawFont(td_hud_weapon_name_block, 4);
	TextDrawSetProportional(td_hud_weapon_name_block, 0);
	TextDrawSetShadow(td_hud_weapon_name_block, 0);

	td_hud_other_squares[0] = TextDrawCreate(559.5064, 18.0510, !"LD_SPAC:white");
	TextDrawTextSize(td_hud_other_squares[0], 3.3299, 4.1500);
	TextDrawAlignment(td_hud_other_squares[0], 1);
	TextDrawColor(td_hud_other_squares[0], -1);
	TextDrawBackgroundColor(td_hud_other_squares[0], 255);
	TextDrawFont(td_hud_other_squares[0], 4);
	TextDrawSetProportional(td_hud_other_squares[0], 0);
	TextDrawSetShadow(td_hud_other_squares[0], 0);

	td_hud_other_squares[1] = TextDrawCreate(559.5064, 24.2709, !"LD_SPAC:white");
	TextDrawTextSize(td_hud_other_squares[1], 3.3299, 4.1500);
	TextDrawAlignment(td_hud_other_squares[1], 1);
	TextDrawColor(td_hud_other_squares[1], -1);
	TextDrawBackgroundColor(td_hud_other_squares[1], 255);
	TextDrawFont(td_hud_other_squares[1], 4);
	TextDrawSetProportional(td_hud_other_squares[1], 0);
	TextDrawSetShadow(td_hud_other_squares[1], 0);

	td_hud_other_squares[2] = TextDrawCreate(564.5266, 18.0510, !"LD_SPAC:white");
	TextDrawTextSize(td_hud_other_squares[2], 3.3299, 4.1500);
	TextDrawAlignment(td_hud_other_squares[2], 1);
	TextDrawColor(td_hud_other_squares[2], -1);
	TextDrawBackgroundColor(td_hud_other_squares[2], 255);
	TextDrawFont(td_hud_other_squares[2], 4);
	TextDrawSetProportional(td_hud_other_squares[2], 0);
	TextDrawSetShadow(td_hud_other_squares[2], 0);

	//health
	td_hud_health_line = TextDrawCreate(559.5703, 66.5828, !"LD_SPAC:white");
	TextDrawTextSize(td_hud_health_line, TD_HUD_SIZE_HEALTH, 8.3000);
	TextDrawAlignment(td_hud_health_line, 1);
	TextDrawColor(td_hud_health_line, 606348543);
	TextDrawBackgroundColor(td_hud_health_line, 255);
	TextDrawFont(td_hud_health_line, 4);
	TextDrawSetProportional(td_hud_health_line, 0);
	TextDrawSetShadow(td_hud_health_line, 0);

	//exp & money
	td_hud_ex_blocks[0] = TextDrawCreate(495.8656, 86.0802, !"LD_SPAC:white");
	TextDrawTextSize(td_hud_ex_blocks[0], 11.3297, 14.1000);
	TextDrawAlignment(td_hud_ex_blocks[0], 1);
	TextDrawColor(td_hud_ex_blocks[0], 943208703);
	TextDrawBackgroundColor(td_hud_ex_blocks[0], 255);
	TextDrawFont(td_hud_ex_blocks[0], 4);
	TextDrawSetProportional(td_hud_ex_blocks[0], 0);
	TextDrawSetShadow(td_hud_ex_blocks[0], 0);

	td_hud_ex_blocks[1] = TextDrawCreate(569.1762, 86.0802, !"LD_SPAC:white");
	TextDrawTextSize(td_hud_ex_blocks[1], 11.3297, 14.1000);
	TextDrawAlignment(td_hud_ex_blocks[1], 1);
	TextDrawColor(td_hud_ex_blocks[1], 808464639);
	TextDrawBackgroundColor(td_hud_ex_blocks[1], 255);
	TextDrawFont(td_hud_ex_blocks[1], 4);
	TextDrawSetProportional(td_hud_ex_blocks[1], 0);
	TextDrawSetShadow(td_hud_ex_blocks[1], 0);

	td_hud_ex_icons[0] = TextDrawCreate(496.5133, 88.5711, !"XP");
	TextDrawLetterSize(td_hud_ex_icons[0], 0.2386, 1.0190);
	TextDrawAlignment(td_hud_ex_icons[0], 1);
	TextDrawColor(td_hud_ex_icons[0], -5963521);
	TextDrawBackgroundColor(td_hud_ex_icons[0], 255);
	TextDrawFont(td_hud_ex_icons[0], 1);
	TextDrawSetProportional(td_hud_ex_icons[0], 1);
	TextDrawSetShadow(td_hud_ex_icons[0], 0);

	td_hud_ex_icons[1] = TextDrawCreate(571.8632, 86.8114, !"$");
	TextDrawLetterSize(td_hud_ex_icons[1], 0.3280, 1.2762);
	TextDrawAlignment(td_hud_ex_icons[1], 1);
	TextDrawColor(td_hud_ex_icons[1], 8388863);
	TextDrawBackgroundColor(td_hud_ex_icons[1], 255);
	TextDrawFont(td_hud_ex_icons[1], 3);
	TextDrawSetProportional(td_hud_ex_icons[1], 1);
	TextDrawSetShadow(td_hud_ex_icons[1], 0);

	#if defined td_hud_OnGameModeInit
		td_hud_OnGameModeInit();
	#endif

	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit td_hud_OnGameModeInit
#if  defined td_hud_OnGameModeInit
	forward td_hud_OnGameModeInit();
#endif

public OnPlayerConnect(playerid)
{
	//kills
	td_hud_player_kills[playerid] = CreatePlayerTextDraw(playerid, 526.7868, 54.8642, !"0");
	PlayerTextDrawLetterSize(playerid, td_hud_player_kills[playerid], 0.2966, 1.3882);
	PlayerTextDrawAlignment(playerid, td_hud_player_kills[playerid], 2);
	PlayerTextDrawColor(playerid, td_hud_player_kills[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, td_hud_player_kills[playerid], 255);
	PlayerTextDrawFont(playerid, td_hud_player_kills[playerid], 3);
	PlayerTextDrawSetProportional(playerid, td_hud_player_kills[playerid], 1);
	PlayerTextDrawSetShadow(playerid, td_hud_player_kills[playerid], 0);

	td_hud_player_kills_life[playerid] = CreatePlayerTextDraw(playerid, 526.4204, 23.5492, !"0");
	PlayerTextDrawLetterSize(playerid, td_hud_player_kills_life[playerid], 0.6528, 3.4333);
	PlayerTextDrawAlignment(playerid, td_hud_player_kills_life[playerid], 2);
	PlayerTextDrawColor(playerid, td_hud_player_kills_life[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, td_hud_player_kills_life[playerid], 255);
	PlayerTextDrawFont(playerid, td_hud_player_kills_life[playerid], 3);
	PlayerTextDrawSetProportional(playerid, td_hud_player_kills_life[playerid], 1);
	PlayerTextDrawSetShadow(playerid, td_hud_player_kills_life[playerid], 0);

	//weapon
	td_hud_player_weapon_ammo_block[playerid] = CreatePlayerTextDraw(playerid, 609.8571, 7.6803, !"LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, td_hud_player_weapon_ammo_block[playerid], 24.0000, 1.2400);
	PlayerTextDrawAlignment(playerid, td_hud_player_weapon_ammo_block[playerid], 1);
	PlayerTextDrawColor(playerid, td_hud_player_weapon_ammo_block[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, td_hud_player_weapon_ammo_block[playerid], 255);
	PlayerTextDrawFont(playerid, td_hud_player_weapon_ammo_block[playerid], 4);
	PlayerTextDrawSetProportional(playerid, td_hud_player_weapon_ammo_block[playerid], 0);
	PlayerTextDrawSetShadow(playerid, td_hud_player_weapon_ammo_block[playerid], 0);

	td_hud_player_weapon_name[playerid] = CreatePlayerTextDraw(playerid, 560.1630, 6.6918, !"LLSD");
	PlayerTextDrawLetterSize(playerid, td_hud_player_weapon_name[playerid], 0.2460, 1.0482);
	PlayerTextDrawAlignment(playerid, td_hud_player_weapon_name[playerid], 1);
	PlayerTextDrawColor(playerid, td_hud_player_weapon_name[playerid], 255);
	PlayerTextDrawBackgroundColor(playerid, td_hud_player_weapon_name[playerid], 255);
	PlayerTextDrawFont(playerid, td_hud_player_weapon_name[playerid], 1);
	PlayerTextDrawSetProportional(playerid, td_hud_player_weapon_name[playerid], 1);
	PlayerTextDrawSetShadow(playerid, td_hud_player_weapon_name[playerid], 0);

	td_hud_player_weapon_ammo[playerid] = CreatePlayerTextDraw(playerid, 633.8137, 8.0958, !"00/00");
	PlayerTextDrawLetterSize(playerid, td_hud_player_weapon_ammo[playerid], 0.1876, 0.9071);
	PlayerTextDrawAlignment(playerid, td_hud_player_weapon_ammo[playerid], 3);
	PlayerTextDrawColor(playerid, td_hud_player_weapon_ammo[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, td_hud_player_weapon_ammo[playerid], 255);
	PlayerTextDrawFont(playerid, td_hud_player_weapon_ammo[playerid], 3);
	PlayerTextDrawSetProportional(playerid, td_hud_player_weapon_ammo[playerid], 1);
	PlayerTextDrawSetShadow(playerid, td_hud_player_weapon_ammo[playerid], 0);

	//health
	td_hud_player_health[playerid] = CreatePlayerTextDraw(playerid, 560.1303, 56.6655, !"0HP");
	PlayerTextDrawLetterSize(playerid, td_hud_player_health[playerid], 0.2196, 1.0109);
	PlayerTextDrawAlignment(playerid, td_hud_player_health[playerid], 1);
	PlayerTextDrawColor(playerid, td_hud_player_health[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, td_hud_player_health[playerid], 255);
	PlayerTextDrawFont(playerid, td_hud_player_health[playerid], 1);
	PlayerTextDrawSetProportional(playerid, td_hud_player_health[playerid], 1);
	PlayerTextDrawSetShadow(playerid, td_hud_player_health[playerid], 0);

	td_hud_player_health_line[playerid] = CreatePlayerTextDraw(playerid, 559.5703, 66.5828, !"LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, td_hud_player_health_line[playerid], TD_HUD_SIZE_HEALTH, 8.3000);
	PlayerTextDrawAlignment(playerid, td_hud_player_health_line[playerid], 1);
	PlayerTextDrawColor(playerid, td_hud_player_health_line[playerid], -1458630657);
	PlayerTextDrawBackgroundColor(playerid, td_hud_player_health_line[playerid], 255);
	PlayerTextDrawFont(playerid, td_hud_player_health_line[playerid], 4);
	PlayerTextDrawSetProportional(playerid, td_hud_player_health_line[playerid], 0);
	PlayerTextDrawSetShadow(playerid, td_hud_player_health_line[playerid], 0);

	//exp & money
	td_hud_player_experience[playerid] = CreatePlayerTextDraw(playerid, 511.2236, 86.6564, !"0");
	PlayerTextDrawLetterSize(playerid, td_hud_player_experience[playerid], 0.3165, 1.3092);
	PlayerTextDrawAlignment(playerid, td_hud_player_experience[playerid], 1);
	PlayerTextDrawColor(playerid, td_hud_player_experience[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, td_hud_player_experience[playerid], 255);
	PlayerTextDrawFont(playerid, td_hud_player_experience[playerid], 3);
	PlayerTextDrawSetProportional(playerid, td_hud_player_experience[playerid], 1);
	PlayerTextDrawSetShadow(playerid, td_hud_player_experience[playerid], 0);

	td_hud_player_money[playerid] = CreatePlayerTextDraw(playerid, 584.3333, 86.6564, !"0");
	PlayerTextDrawLetterSize(playerid, td_hud_player_money[playerid], 0.3165, 1.3092);
	PlayerTextDrawAlignment(playerid, td_hud_player_money[playerid], 1);
	PlayerTextDrawColor(playerid, td_hud_player_money[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, td_hud_player_money[playerid], 255);
	PlayerTextDrawFont(playerid, td_hud_player_money[playerid], 3);
	PlayerTextDrawSetProportional(playerid, td_hud_player_money[playerid], 1);
	PlayerTextDrawSetShadow(playerid, td_hud_player_money[playerid], 0);

	#if defined td_hud_OnPlayerConnect
		td_hud_OnPlayerConnect(playerid);
	#endif

	return 1;
}

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect td_hud_OnPlayerConnect
#if defined td_hud_OnPlayerConnect
	forward td_hud_OnPlayerConnect(playerid);
#endif

public OnPlayerSpawn(playerid)
{
	if (td_hud_player_show{playerid} == false)
	{
		td_hud_player_show{playerid} = true;

		TextDrawShowForPlayer(playerid, td_hud_backgroud[0]);
		TextDrawShowForPlayer(playerid, td_hud_backgroud[1]);
		TextDrawShowForPlayer(playerid, td_hud_backgroud[2]);
		TextDrawShowForPlayer(playerid, td_hud_kill_squares[0]);
		TextDrawShowForPlayer(playerid, td_hud_kill_squares[1]);
		TextDrawShowForPlayer(playerid, td_hud_kill_squares_title);
		TextDrawShowForPlayer(playerid, td_hud_weapon_name_block);
		TextDrawShowForPlayer(playerid, td_hud_other_squares[0]);
		TextDrawShowForPlayer(playerid, td_hud_other_squares[1]);
		TextDrawShowForPlayer(playerid, td_hud_other_squares[2]);
		TextDrawShowForPlayer(playerid, td_hud_health_line);
		TextDrawShowForPlayer(playerid, td_hud_ex_blocks[0]);
		TextDrawShowForPlayer(playerid, td_hud_ex_blocks[1]);
		TextDrawShowForPlayer(playerid, td_hud_ex_icons[0]);
		TextDrawShowForPlayer(playerid, td_hud_ex_icons[1]);

		PlayerTextDrawShow(playerid, td_hud_player_kills[playerid]);
		PlayerTextDrawShow(playerid, td_hud_player_kills_life[playerid]);
		UpdateHudKills(playerid);

		PlayerTextDrawShow(playerid, td_hud_player_weapon_name[playerid]);
		PlayerTextDrawShow(playerid, td_hud_player_weapon_ammo[playerid]);

		PlayerTextDrawShow(playerid, td_hud_player_health[playerid]);
		PlayerTextDrawShow(playerid, td_hud_player_health_line[playerid]);

		PlayerTextDrawShow(playerid, td_hud_player_experience[playerid]);
		PlayerTextDrawShow(playerid, td_hud_player_money[playerid]);
		UpdateHudExperience(playerid);

		SetTimerEx(!"PlayerHudTimer", TD_HUD_TIMER_TIME, true, "i", playerid);
	}

	#if defined td_hud_OnPlayerSpawn
		td_hud_OnPlayerSpawn(playerid);
	#endif

	return 1;
}

#if defined _ALS_OnPlayerSpawn
	#undef OnPlayerSpawn
#else
	#define _ALS_OnPlayerSpawn
#endif
#define OnPlayerSpawn td_hud_OnPlayerSpawn
#if defined td_hud_OnPlayerSpawn
	forward td_hud_OnPlayerSpawn(playerid);
#endif

stock UpdateHudWeapon(playerid, weaponid)
{
	new
		slot = td_hud_weapon_slots[weaponid],
		weapon,
		ammo,
		string[6];

	PlayerTextDrawSetString(playerid, td_hud_player_weapon_name[playerid], td_hud_weapon_name[weaponid]);

	GetPlayerWeaponData(playerid, slot, weapon, ammo);
	format(string, sizeof string, "%02i/%02i", ammo, td_hud_weapon_ammo[weaponid]);
	PlayerTextDrawSetString(playerid, td_hud_player_weapon_ammo[playerid], string);

	PlayerTextDrawTextSize(playerid, td_hud_player_weapon_ammo_block[playerid], 24.0000, 1.2400);
	PlayerTextDrawShow(playerid, td_hud_player_weapon_ammo_block[playerid]);

	PlayerTextDrawDestroy(playerid, td_hud_player_weapon_model[playerid]);

	td_hud_player_weapon_model[playerid] = CreatePlayerTextDraw(playerid, td_hud_weapon_model_position[weaponid][td_hud_weapon_pos_x], td_hud_weapon_model_position[weaponid][td_hud_weapon_pos_y], !"");
	PlayerTextDrawTextSize(playerid, td_hud_player_weapon_model[playerid], -88.0000, 108.0000);
	PlayerTextDrawAlignment(playerid, td_hud_player_weapon_model[playerid], 1);
	PlayerTextDrawColor(playerid, td_hud_player_weapon_model[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, td_hud_player_weapon_model[playerid], 0);
	PlayerTextDrawFont(playerid, td_hud_player_weapon_model[playerid], 5);
	PlayerTextDrawSetProportional(playerid, td_hud_player_weapon_model[playerid], 0);
	PlayerTextDrawSetShadow(playerid, td_hud_player_weapon_model[playerid], 0);
	PlayerTextDrawSetPreviewModel(playerid, td_hud_player_weapon_model[playerid], td_hud_weapon_model_position[weaponid][td_hud_weapon_modelid]);
	PlayerTextDrawSetPreviewRot(playerid, td_hud_player_weapon_model[playerid], 0.0000, td_hud_weapon_model_position[weaponid][td_hud_weapon_pot_y], 0.0000, td_hud_weapon_model_position[weaponid][td_hud_weapon_size]);

	PlayerTextDrawShow(playerid, td_hud_player_weapon_model[playerid]);

	return 1;
}

stock UpdateHudWeaponAmmo(playerid, weaponid, ammo)
{
	new
		string[6];

	format(string, sizeof string, "%02i/%02i", ammo, td_hud_weapon_ammo[weaponid-22]);
	PlayerTextDrawSetString(playerid, td_hud_player_weapon_ammo[playerid], string);
	
	return 1;
}

stock UpdateHudKills(playerid)
{
	new
		kills = pInfo[playerid][pKills],
		kills_life = pInfo[playerid][pKillsLife],
		string[5];

	valstr(string, kills_life);
	PlayerTextDrawSetString(playerid, td_hud_player_kills_life[playerid], string);

	valstr(string, kills);
	PlayerTextDrawSetString(playerid, td_hud_player_kills[playerid], string);

	return 1;
}

stock UpdateHudHealth(playerid, Float:health)
{
	new
		Float:size_line,
		string[7];

	format(string, sizeof string, "%.0fHP", health);
	PlayerTextDrawSetString(playerid, td_hud_player_health[playerid], string);

	size_line = TD_HUD_SIZE_HEALTH/100.0*health;
	PlayerTextDrawTextSize(playerid, td_hud_player_health_line[playerid], size_line, 8.3000);
	PlayerTextDrawShow(playerid, td_hud_player_health_line[playerid]);

	return 1;
}

stock UpdateHudExperience(playerid)
{
	new
		experience = pInfo[playerid][pExpLife],
		money = pInfo[playerid][pMoney],
		string[12];

	valstr(string, experience);
	PlayerTextDrawSetString(playerid, td_hud_player_experience[playerid], string);

	valstr(string, money);
	PlayerTextDrawSetString(playerid, td_hud_player_money[playerid], string);

	return 1;
}

forward PlayerHudTimer(playerid);
public PlayerHudTimer(playerid)
{
	new
		Float:health,
		weaponid = GetPlayerWeapon(playerid);

	if (weaponid != td_hud_player_weaponid[playerid])
	{
		if (22 <= weaponid <= 34)
		{
			UpdateHudWeapon(playerid, weaponid-22);
		}
		else if (weaponid == 46)
		{
			PlayerTextDrawSetString(playerid, td_hud_player_weapon_name[playerid], "Parachute");
			PlayerTextDrawSetString(playerid, td_hud_player_weapon_ammo[playerid], " ");

			PlayerTextDrawTextSize(playerid, td_hud_player_weapon_ammo_block[playerid], 24.0000, 8.3000);
			PlayerTextDrawShow(playerid, td_hud_player_weapon_ammo_block[playerid]);
	
			PlayerTextDrawDestroy(playerid, td_hud_player_weapon_model[playerid]);

			td_hud_player_weapon_model[playerid] = CreatePlayerTextDraw(playerid, 641.5831, -10.9888, "");
			PlayerTextDrawTextSize(playerid, td_hud_player_weapon_model[playerid], -88.0000, 108.0000);
			PlayerTextDrawAlignment(playerid, td_hud_player_weapon_model[playerid], 1);
			PlayerTextDrawColor(playerid, td_hud_player_weapon_model[playerid], -1);
			PlayerTextDrawBackgroundColor(playerid, td_hud_player_weapon_model[playerid], 0);
			PlayerTextDrawFont(playerid, td_hud_player_weapon_model[playerid], 5);
			PlayerTextDrawSetProportional(playerid, td_hud_player_weapon_model[playerid], 0);
			PlayerTextDrawSetShadow(playerid, td_hud_player_weapon_model[playerid], 0);
			PlayerTextDrawSetPreviewModel(playerid, td_hud_player_weapon_model[playerid], 371);
			PlayerTextDrawSetPreviewRot(playerid, td_hud_player_weapon_model[playerid], 0.0000, 0.0000, 0.0000, 2.7000);

			PlayerTextDrawShow(playerid, td_hud_player_weapon_model[playerid]);
		}
		else
		{
			PlayerTextDrawSetString(playerid, td_hud_player_weapon_name[playerid], "Fists");
			PlayerTextDrawSetString(playerid, td_hud_player_weapon_ammo[playerid], " ");
			PlayerTextDrawHide(playerid, td_hud_player_weapon_model[playerid]);

			PlayerTextDrawTextSize(playerid, td_hud_player_weapon_ammo_block[playerid], 24.0000, 8.3000);
			PlayerTextDrawShow(playerid, td_hud_player_weapon_ammo_block[playerid]);
		}
	}

	td_hud_player_weaponid[playerid] = weaponid;

	GetPlayerHealth(playerid, health);

	if (health > 0)
	{
		UpdateHudHealth(playerid, health);
	}
	else
	{
		PlayerTextDrawSetString(playerid, td_hud_player_health[playerid], "0HP");
		PlayerTextDrawHide(playerid, td_hud_player_health_line[playerid]);
	}

	return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
	PlayerTextDrawHide(playerid, td_hud_player_health_line[playerid]);

	#if defined td_hud_OnPlayerDeath
		td_hud_OnPlayerDeath(playerid, killerid, reason);
	#endif

	return 1;
}

#if defined _ALS_OnPlayerDeath
	#undef OnPlayerDeath
#else
	#define _ALS_OnPlayerDeath
#endif
#define OnPlayerDeath td_hud_OnPlayerDeath
#if defined td_hud_OnPlayerDeath
	forward td_hud_OnPlayerDeath(playerid, killerid, reason);
#endif

public OnPlayerDisconnect(playerid, reason)
{
	td_hud_player_show{playerid} = false;
	td_hud_player_weaponid{playerid} = 255;

	TextDrawHideForPlayer(playerid, td_hud_backgroud[0]);
	TextDrawHideForPlayer(playerid, td_hud_backgroud[1]);
	TextDrawHideForPlayer(playerid, td_hud_backgroud[2]);
	TextDrawHideForPlayer(playerid, td_hud_kill_squares[0]);
	TextDrawHideForPlayer(playerid, td_hud_kill_squares[1]);
	TextDrawHideForPlayer(playerid, td_hud_kill_squares_title);
	TextDrawHideForPlayer(playerid, td_hud_weapon_name_block);
	TextDrawHideForPlayer(playerid, td_hud_other_squares[0]);
	TextDrawHideForPlayer(playerid, td_hud_other_squares[1]);
	TextDrawHideForPlayer(playerid, td_hud_other_squares[2]);
	TextDrawHideForPlayer(playerid, td_hud_health_line);
	TextDrawHideForPlayer(playerid, td_hud_ex_blocks[0]);
	TextDrawHideForPlayer(playerid, td_hud_ex_blocks[1]);
	TextDrawHideForPlayer(playerid, td_hud_ex_icons[0]);
	TextDrawHideForPlayer(playerid, td_hud_ex_icons[1]);

	PlayerTextDrawDestroy(playerid, td_hud_player_kills[playerid]);
	PlayerTextDrawDestroy(playerid, td_hud_player_kills_life[playerid]);
	PlayerTextDrawDestroy(playerid, td_hud_player_weapon_model[playerid]);
	PlayerTextDrawDestroy(playerid, td_hud_player_weapon_ammo_block[playerid]);
	PlayerTextDrawDestroy(playerid, td_hud_player_weapon_name[playerid]);
	PlayerTextDrawDestroy(playerid, td_hud_player_weapon_ammo[playerid]);
	PlayerTextDrawDestroy(playerid, td_hud_player_health[playerid]);
	PlayerTextDrawDestroy(playerid, td_hud_player_health_line[playerid]);
	PlayerTextDrawDestroy(playerid, td_hud_player_experience[playerid]);
	PlayerTextDrawDestroy(playerid, td_hud_player_money[playerid]);

	KillTimer(td_hud_player_timer[playerid]);
	td_hud_player_timer[playerid] = 0;

	td_hud_player_weapon_model[playerid] = PlayerText:-1;

	#if defined td_hud_OnPlayerDisconnect
		td_hud_OnPlayerDisconnect(playerid, reason);
	#endif

	return 1;
}

#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect td_hud_OnPlayerDisconnect
#if defined td_hud_OnPlayerDisconnect
	forward td_hud_OnPlayerDisconnect(playerid, reason);
#endif
