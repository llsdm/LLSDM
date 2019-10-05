#if defined ADMIN_CMD_AHELP
	#endinput
#endif
#define ADMIN_CMD_AHELP

static const
	ahelp_str[][] =
	{
		"{D83333}/say{FFFFFF} - сообщение от администрации\n",
		"{D83333}/ban{FFFFFF} - заблокировать игрока\n",
		"{D83333}/kick{FFFFFF} - кикнуть игрока\n",
		"{D83333}/goto{FFFFFF} - телепортироваться к игроку\n",
		"{D83333}/gome{FFFFFF} - телепортировать игрока к себе\n",
		"{D83333}/restart{FFFFFF} - рестарт сервера\n",
		"{D83333}/stoprestart{FFFFFF} - отменить рестарт сервера\n"
	},
	ahelp_str_uiv_editor[][] =
	{
		"{C8B02C}/create{FFFFFF} - создать транспорт\n",
		"{C8B02C}/saveh{FFFFFF} - сохранить позицию транспорта\n",
		"{C8B02C}/delveh{FFFFFF} - удалить транспорт\n"
	};

CMD:ahelp(playerid)
{
	if (pInfo[playerid][pAdmin] == 0)
	{
		return SendClientMessage(playerid, COLOR_ERROR, !"Вы не уполномочены использовать данную команду!");
	}

	static
		string[600];

	format(string, sizeof string, "%s%s%s%s%s%s%s%s%s%s%s%s",
		"{D83333}Главные:\n",
		ahelp_str[0],
		ahelp_str[1],
		ahelp_str[2],
		ahelp_str[3],
		ahelp_str[4],
		ahelp_str[5],
		ahelp_str[6],
		"\n{C8B02C}uiv_editor:\n",
		ahelp_str_uiv_editor[0],
		ahelp_str_uiv_editor[1],
		ahelp_str_uiv_editor[2]
	);

	return ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, !"Админ команды", string, !"Закрыть", "");
}