#if  defined DB_BAN
	#endinput
#endif
#define DB_BAN

forward PlayerBan(playerid);
public PlayerBan(playerid)
{
	new
		ban_date,
		rows;

	cache_get_row_count(rows);

	if (rows)
	{
		static const
			str_del[] = "DELETE FROM `ban-list` WHERE `PlayerName` = '%s'";

		new
			string[sizeof str_del + MAX_PLAYER_NAME - 2];

		cache_get_value_name_int(0, "DateOfUnBan", ban_date);

		if (gettime() > ban_date)
		{
			format(string, sizeof string, str_del, pInfo[playerid][pName]);
			mysql_tquery(mysql_connect_ID, string, "", "");
		}
		else
		{
			new
				str[30] = !"{FF0000}Ваш аккаунт заблокирован!\nДата вашей разблокировки: {FFFF00}";

			strcat(str, date("%dd/%mm/%yyyy", ban_date));

			ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, !"{FF0000}Вы забанены!", str, !"Ок", "");
			return PlayerKick(playerid);
		}
	}
	else
		ShowPlayerDialog(playerid, dLogin, DIALOG_STYLE_INPUT, !"Авторизация", !"Введите пароль от аккаунта для того, чтоб продолжить игру:", !"Вход", !"Выход");

	return 1;
}
