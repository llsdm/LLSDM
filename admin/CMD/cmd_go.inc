#if defined ADMIN_CMD_GO
	#endinput
#endif
#define ADMIN_CMD_GO

CMD:goto(playerid, params[])
{
	if (pInfo[playerid][pAdmin] < 5)
		return SendClientMessage(playerid, COLOR_ERROR, !"Вы не уполномочены использовать данную команду!");

	if (isnull(params))
		return SendClientMessage(playerid, COLOR_ERROR, !"Ошибка: /goto [id]");

	static const
		str_p[] = "Вы телепортировались к {FFFFFF}%s [%i]",
		str_i[] = "Администратор %s телепортировался к Вам";

	new
		id = strval(params),
		string[sizeof str_p + 11 + MAX_PLAYER_NAME - 2*2],
		Float:x,
		Float:y,
		Float:z;

	if (id == playerid)
		return SendClientMessage(playerid, COLOR_ERROR, !"Ошибка: вы указали свой ID");

	if (!IsPlayerConnected(id))
		return SendClientMessage(playerid, COLOR_ERROR, !"Ошибка: игрока с этим ID не найдено");

	GetPlayerPos(id, x, y, z);
	SetPlayerPos(playerid, x+5, y, z);

	format(string, sizeof string, str_p, pInfo[id][pName], id);
	SendClientMessage(playerid, COLOR_ADMIN, string);

	format(string, sizeof string, str_i, pInfo[playerid][pName]);
	SendClientMessage(id, COLOR_ADMIN, string);

	return 1;
}

CMD:gome(playerid, params[])
{
	if (pInfo[playerid][pAdmin] < 5)
		return SendClientMessage(playerid, COLOR_ERROR, !"Вы не уполномочены использовать данную команду!");

	if (isnull(params))
		return SendClientMessage(playerid, COLOR_ERROR, !"Ошибка: /gome [id]");

	static const
		str_p[] = "Вы телепортировали к себе {FFFFFF}%s [%i]",
		str_i[] = "Администратор %s телепортировал Вас в себе";

	new
		id = strval(params),
		string[sizeof str_p + 11 + MAX_PLAYER_NAME - 2*2],
		Float:x,
		Float:y,
		Float:z;

	if (id == playerid)
		return SendClientMessage(playerid, COLOR_ERROR, !"Ошибка: вы указали свой ID");

	if (!IsPlayerConnected(id))
		return SendClientMessage(playerid, COLOR_ERROR, !"Ошибка: игрока с этим ID не найдено");

	GetPlayerPos(playerid, x, y, z);
	SetPlayerPos(id, x+5, y, z);

	format(string, sizeof string, str_p, pInfo[id][pName], id);
	SendClientMessage(playerid, COLOR_ADMIN, string);

	format(string, sizeof string, str_i, pInfo[playerid][pName]);
	SendClientMessage(id, COLOR_ADMIN, string);
	
	return 1;
}