#if defined ADMIN_CMD_SAY
	#endinput
#endif
#define ADMIN_CMD_SAY

CMD:say(playerid, params[])
{
	if (pInfo[playerid][pAdmin] == 0)
	{
		return SendClientMessage(playerid, COLOR_ERROR, !"Вы не уполномочены использовать данную команду!");
	}

	if (isnull(params))
	{
		return SendClientMessage(playerid, COLOR_ERROR, !"Ошибка: /say [текст]");
	}

	if (strlen(params) > 50)
	{
		return SendClientMessage(playerid, COLOR_ERROR, !"Ошибка: допустимая длина сообщения 50 символов");
	}

	new
		string[25] = !"Администратор ";

	strcat(string, pInfo[playerid][pName]);
	strcat(string, !":{FFFFFF} ");
	strcat(string, params);
	SendClientMessageToAll(COLOR_ADMIN, string);

	return 1;
}