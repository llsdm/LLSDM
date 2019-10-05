#if defined DB_CONNECT
	#endinput
#endif
#define DB_CONNECT

public OnPlayerConnect(playerid)
{
	static const
		str[] = "SELECT * FROM `accounts` WHERE `pName` = '%s'";

	static
		string[sizeof str + MAX_PLAYER_NAME - 2];

	GetPlayerName(playerid, pInfo[playerid][pName], MAX_PLAYER_NAME);
	format(string, sizeof string, str, pInfo[playerid][pName]);
	mysql_tquery(mysql_connect_ID, string, "FindPlayerInTable", "i", playerid);

	#if defined db_connect_OnPlayerConnect
		db_connect_OnPlayerConnect(playerid);
	#endif

	return 1;
}

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect db_connect_OnPlayerConnect
#if defined db_connect_OnPlayerConnect
	forward db_connect_OnPlayerConnect(playerid);
#endif

forward FindPlayerInTable(playerid);
public FindPlayerInTable(playerid)
{
	new
		rows;
		
	cache_get_row_count(rows);
 
	if(!rows)
	{
		ShowPlayerDialog(playerid, dRegister, DIALOG_STYLE_INPUT, !"Регистрация нового пользователя", !"Введите пароль для регистрации нового аккаунта:", !"Продолжить", !"Выход");
	}
	else
	{
		static const
			str[] = "SELECT * FROM `ban-list` WHERE `PlayerName` = '%s'";

		static
			string[sizeof str + MAX_PLAYER_NAME - 2];

		cache_get_value_name(0, "pPassword", pInfo[playerid][pPassword], MAX_PLAYER_PASSWORD);
		cache_get_value_name_int(0, "pSkin", pInfo[playerid][pSkin]);

		format(string, sizeof string, str, pInfo[playerid][pName]);
		mysql_tquery(mysql_connect_ID, string, "PlayerBan", "i", playerid);
	}

	return 1;
}