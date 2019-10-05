#if defined PLAYER_WEAPON_EXP_CARDS
	#endinput
#endif
#define PLAYER_WEAPON_EXP_CARDS

static enum
{
	PLAYER_WEAPON_DIALOG_EXP_CARDS = 145,
	PLAYER_WEAPON_DIALOG_EXP_WARN = PLAYER_WEAPON_DIALOG_EXP_CARDS+1,
	PLAYER_WEAPON_EXP_CARD_SIMPLE = 100,
	PLAYER_WEAPON_EXP_CARD_PRO = 500
};


static
	player_weapon_exp_cardid[MAX_PLAYERS char];

stock ApplyWeaponExpCard(playerid, cardid)
{
	new
		weapon_name_1[MAX_WEAPON_NAME],
		weapon_name_2[MAX_WEAPON_NAME],
		weapon_name_3[MAX_WEAPON_NAME],
		weaponid_1 = pInfo[playerid][pWeapons][0],
		weaponid_2 = pInfo[playerid][pWeapons][1],
		weaponid_3 = pInfo[playerid][pWeapons][2],
		string[MAX_WEAPON_NAME*3];

	player_weapon_exp_cardid{playerid} = cardid;

	GetWeaponName(weaponid_1, weapon_name_1, MAX_WEAPON_NAME);
	GetWeaponName(weaponid_2, weapon_name_2, MAX_WEAPON_NAME);
	GetWeaponName(weaponid_3, weapon_name_3, MAX_WEAPON_NAME);

	format(string, sizeof string, "%s\n%s\n%s",
		weaponid_1 == 0 ? "Пусто" : weapon_name_1,
		weaponid_2 == 0 ? "Пусто" : weapon_name_2,
		weaponid_3 == 0 ? "Пусто" : weapon_name_3
	);

	return ShowPlayerDialog(playerid, PLAYER_WEAPON_DIALOG_EXP_CARDS, DIALOG_STYLE_LIST, !"Выберите оружие:", string, !"Улучшить", !"Закрыть");
}


public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if (dialogid == PLAYER_WEAPON_DIALOG_EXP_CARDS)
	{
		if (response == 0)
		{
			return 0;
		}

		if (pInfo[playerid][pWeapons][listitem] == 0)
		{
			return ShowPlayerReminder(playerid, "Слот с оружием пуст", PLAYER_WEAPON_DIALOG_EXP_WARN);
		}

		new
			weapon_exp = player_weapon_exp_cardid{playerid} == 1 ? PLAYER_WEAPON_EXP_CARD_SIMPLE : PLAYER_WEAPON_EXP_CARD_PRO;

		pInfo[playerid][pWeaponExp][listitem] += weapon_exp;

		if (player_weapon_exp_cardid{playerid} == 1)
		{
			GiveWeaponExpCards(playerid, -1);
		}
		else
		{
			GiveWeaponExpCardsPro(playerid, -1);
		}

		return UpdateWeaponExp(playerid, listitem);
	}
	else if (dialogid == PLAYER_WEAPON_DIALOG_EXP_WARN)
	{
		return ApplyWeaponExpCard(playerid, player_weapon_exp_cardid{playerid});
	}
	
	#if defined weapon_cards_OnDialog
		weapon_cards_OnDialog(playerid, dialogid, response, listitem, inputtext);
	#endif

	return 0;
}

#if defined _ALS_OnDialogResponse
	#undef OnDialogResponse
#else
	#define _ALS_OnDialogResponse
#endif
#define OnDialogResponse weapon_cards_OnDialog
#if defined weapon_cards_OnDialog
	forward weapon_cards_OnDialog(playerid, dialogid, response, listitem, inputtext[]);
#endif

public OnPlayerDeath(playerid, killerid, reason)
{
	player_weapon_exp_cardid{playerid} = 0;

	#if LLSDM_RESPAWN_WITH_SAVED == 0
		pInfo[playerid][pWeaponExp][0] =
		pInfo[playerid][pWeaponExp][1] =
		pInfo[playerid][pWeaponExp][2] = 0;

		SaveWeapon(playerid);
	#endif

	#if defined weapon_cards_OnPlayerDeath
		weapon_cards_OnPlayerDeath(playerid, killerid, reason);
	#endif

	return 1;
}

#if defined _ALS_OnPlayerDeath
	#undef OnPlayerDeath
#else
	#define _ALS_OnPlayerDeath
#endif
#define OnPlayerDeath weapon_cards_OnPlayerDeath
#if defined weapon_cards_OnPlayerDeath
	forward weapon_cards_OnPlayerDeath(playerid, killerid, reason);
#endif

public OnPlayerDisconnect(playerid, reason)
{
	player_weapon_exp_cardid{playerid} = 0;
	
	#if defined weapon_cards_OnPlayerDisconnect
		weapon_cards_OnPlayerDisconnect(playerid, reason);
	#endif

	return 1;
}

#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect weapon_cards_OnPlayerDisconnect
#if defined weapon_cards_OnPlayerDisconnect
	forward weapon_cards_OnPlayerDisconnect(playerid, reason);
#endif