#if defined ADMIN_CMD_DISCONNECT
	#endinput
#endif
#define ADMIN_CMD_DISCONNECT

CMD:ban(playerid, params[])
{
	if (pInfo[playerid][pAdmin] < 8)
	{
		return SendClientMessage(playerid, COLOR_ERROR, !"Вы не уполномочены использовать данную команду!");
	}

	extract params -> new id, days, string:reason[30]; else
	{
		return SendClientMessage(playerid, COLOR_ERROR, !"Ошибка: /ban [id] [Дни] [Причина]");
	}

	if (strlen(reason) > 30)
	{
		return SendClientMessage(playerid, COLOR_ERROR, !"Ошибка: допустимая длина сообщения 30 символов");
	}

	if (!IsPlayerConnected(id))
	{
		return SendClientMessage(playerid, COLOR_ERROR, !"Ошибка: игрока нет в сети");
	}

	if (!(1 <= days <= 30))
	{
		return SendClientMessage(playerid, COLOR_ERROR, !"Ошибка: количество дней должно быть от 1-го до 30-ти");
	}

	static const
		str[] = "Администратор %s забанил %s на %i дней. Причина: %s",
		str_ban[] = "INSERT INTO `ban-list` (`PlayerName`, `AdminName`, `Days`, `Message`, `DateOfBan`, `DateOfUnBan`, `IP`) VALUES ('%s', '%s', '%i', '%s', '%i', '%i', '%s')";

	new
		unban_time = gettime()+86400*days,
		ban_time = gettime(),
		ban_ip[16],
		string[sizeof str_ban + MAX_PLAYER_NAME*2 + 3 + 30 + 11*2 + 16 - 2*7];

	GetPlayerIp(playerid, ban_ip, 16);

	format(string, sizeof string, str, pInfo[playerid][pName], pInfo[id][pName], days, reason);
	SendClientMessageToAll(COLOR_ADMIN, string);

	format(string, sizeof string, str_ban,
		pInfo[id][pName],
		pInfo[playerid][pName],
		days,
		reason,
		ban_time,
		unban_time,
		ban_ip
	);
	mysql_tquery(mysql_connect_ID, string, "", "");

	return PlayerKick(id);
}

CMD:kick(playerid, params[])
{
	if (pInfo[playerid][pAdmin] < 5)
	{
		return SendClientMessage(playerid, COLOR_ERROR, !"Вы не уполномочены использовать данную команду!");
	}

	extract params -> new id, string:reason[32]; else
	{
		return SendClientMessage(playerid, COLOR_ERROR, !"Ошибка: /kick [id] [Причина]");
	}

	if (strlen(reason) > 30)
	{
		return SendClientMessage(playerid, COLOR_ERROR, !"Ошибка: допустимая длина сообщения в 30 символов");
	}

	if (!IsPlayerConnected(id))
	{
		return SendClientMessage(playerid, COLOR_ERROR, !"Ошибка: игрока нет в сети");
	}

	static const
		str[] = "Администратор %s кикнул %s. Причина: %s";

	new
		string[sizeof str + MAX_PLAYER_NAME*2 + 30 - 2*3];

	format(string, sizeof string, str, pInfo[playerid][pName], pInfo[id][pName], reason);
	SendClientMessageToAll(COLOR_ADMIN, string);

	return PlayerKick(id);
}