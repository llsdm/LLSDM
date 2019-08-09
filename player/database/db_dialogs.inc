#if defined DB_DIALOGS
	#endinput
#endif
#define DB_DIALOGS

enum
{
	dKickMessage = 1,
	dRegister,
	dEmail,
	dLogin
};

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch (dialogid)
	{
		case dRegister:
		{
			if (response == 0)
			{
				ShowPlayerDialog(playerid, dKickMessage, DIALOG_STYLE_MSGBOX, !"Оповещение", !"{FFFFFF}Вы были кикнуты с сервера.\n{FF0000}Причина: Отказ от регистрации.\n{FFFFFF}Для выхода с сервера введите \"/q\" в чат", !"Выход", "");
				return Kick(playerid);
			}

			new
				len = strlen(inputtext),
				bool:war,
				i = -1, 
				s;

			if (!(4 <= len <= MAX_PLAYER_PASSWORD))
				war = true;

			while ((s = inputtext[i++]) != '\0')
			{
				switch (s)
				{
					case '0'..'9', 'a'..'z', 'A'..'Z':
						continue;
					default:
					{
						war = true;
						break;
					}
				}
			}

			if (war)
				return ShowPlayerDialog(playerid, dRegister, DIALOG_STYLE_INPUT, !"{FF0000}Ошибка: {FFFFFF}Вы не можете продолжить регистрацию не введя пароль!", 
					!"{C0C0C0}Примечание:\n\
					{666666}- Пароль чувствителен к регистру;\n\
					- Пароль должен содержать от 4 до 12 символов;\n\
					- Пароль может содержать латинские символы и цифры (aA-zZ, 0-9).\n\n\
					{FFFFFF}Введите пароль для регистрации нового аккаунта:", 
					!"Продолжить", !"Выход");

			strcat((pInfo[playerid][pPassword][0] = EOS, pInfo[playerid][pPassword]), inputtext);
			ShowPlayerDialog(playerid, dEmail, DIALOG_STYLE_INPUT, !"Регистрация нового пользователя", !"Введите адрес эдектронной почты для регистрации нового аккаунта:", !"Регистрация", !"Выход");
			return 1;
		}
		case dEmail:
		{
			if (response == 0)
			{
				ShowPlayerDialog(playerid, dKickMessage, DIALOG_STYLE_MSGBOX, !"Оповещение", !"{FFFFFF}Вы были кикнуты с сервера.\n{FF0000}Причина: Отказ от регистрации.\n{FFFFFF}Для выхода с сервера введите \"/q\" в чат", !"Выход", "");
				return Kick(playerid);
			}

			new
				len = strlen(inputtext),
				at = strfind(inputtext, "@"),
				bool:war,
				i, 
				s;

			if (at == -1)
				war = true;

			if (!(4 <= len <= MAX_PLAYER_EMAIL))
				war = true;

			while ((s = inputtext[i++]) != '\0')
			{
				switch (s)
				{
					case '0'..'9', 'a'..'z', 'A'..'Z', '.', '@', '-', '_':
						continue;
					default:
					{
						war = true;
						break;
					}
				}
			}

			if (war)
				return ShowPlayerDialog(playerid, dRegister, DIALOG_STYLE_INPUT, !"{FF0000}Ошибка: {FFFFFF}Вы не можете продолжить регистрацию не введя адрес почты!", 
					!"{FFFFFF}Введите адрес электронной почты для регистрации нового аккаунта:", 
					!"Продолжить", !"Выход");

			strcat((pInfo[playerid][pEmail][0] = EOS, pInfo[playerid][pEmail]), inputtext);
			PlayerSelection(playerid);
			return 1;
		}
		case dLogin:
		{
			if (response == 0)
			{
				ShowPlayerDialog(playerid, dKickMessage, DIALOG_STYLE_MSGBOX, "Оповещение", "{FFFFFF}Вы были кикнуты с сервера.\n{FF0000}Причина: Отказ от авторизации.\n{FFFFFF}Для выхода с сервера введите \"/q\" в чат", "Выход", "");
				return Kick(playerid);
			}

			new
				len = strlen(inputtext),
				i, 
				s;

			if (len == 0)
				return ShowPlayerDialog(playerid, dLogin, DIALOG_STYLE_INPUT, "Авторизация", "{FF0000}Ошибка: {FFFFFF}Вы не можете продолжить авторизацию не введя пароль!\nВведите пароль от аккаунта для входа на сервер:", "Вход", "Выход");

			while ((s = inputtext[i++]) != '\0')
			{
				switch (s)
				{
					case '0'..'9', 'a'..'z', 'A'..'Z':
						continue;
					default:
						return ShowPlayerDialog(playerid, dLogin, DIALOG_STYLE_INPUT, "Авторизация", "{FF0000}Ошибка: {FFFFFF}Введённый пароль содержит запрещённые символы!\nВведите пароль от аккаунта для входа на сервер:", "Вход", "Выход");
				}
			}

			if (!strcmp(pInfo[playerid][pPassword], inputtext))
			{
				static const
					str[] = "SELECT * FROM `accounts` WHERE `pName` = '%s'";

				static
					query_string[sizeof str + MAX_PLAYER_NAME - 2];

				format(query_string, sizeof(query_string), str, pInfo[playerid][pName]);
				mysql_tquery(mysql_connect_ID, query_string, "UploadPlayerAccount","i", playerid);
			}
			else
			{
				switch (GetPVarInt(playerid, "WrongPassword"))
				{
					case 0: ShowPlayerDialog(playerid, dLogin, DIALOG_STYLE_INPUT, "Авторизация", "{FF0000}Ошибка: {FFFFFF}Вы ввели неверный пароль! У Вас осталось 3 попытки.\nВведите пароль от аккаунта для входа на сервер:", "Вход", "Выход");
					case 1: ShowPlayerDialog(playerid, dLogin, DIALOG_STYLE_INPUT, "Авторизация", "{FF0000}Ошибка: {FFFFFF}Вы ввели неверный пароль! У Вас осталось 2 попытки.\nВведите пароль от аккаунта для входа на сервер:", "Вход", "Выход");
					case 2: ShowPlayerDialog(playerid, dLogin, DIALOG_STYLE_INPUT, "Авторизация", "{FF0000}Ошибка: {FFFFFF}Вы ввели неверный пароль! У Вас осталось 1 попытка.\nВведите пароль от аккаунта для входа на сервер:", "Вход", "Выход");
					case 3: ShowPlayerDialog(playerid, dLogin, DIALOG_STYLE_INPUT, "Авторизация", "{FF0000}Ошибка: {FFFFFF}Вы ввели неверный пароль! У Вас осталась последняя попытка, после чего Вас кикнет.\nВведите пароль от аккаунта для входа на сервер:", "Вход", "Выход");
					default:
					{
						DeletePVar(playerid, "WrongPassword");
						ShowPlayerDialog(playerid, dKickMessage, DIALOG_STYLE_MSGBOX, "Оповещение", "{FFFFFF}Вы были кикнуты с сервера.\n{FF0000}Причина: Превышен лимит попыток на ввод пароля.\n{FFFFFF}Для выхода с сервера введите \"/q\" в чат", "Выход", "");
						return Kick(playerid);
					}
				}
				SetPVarInt(playerid, "WrongPassword", GetPVarInt(playerid, "WrongPassword")+1);
			}
			return 1;
		}
	}
	
	#if defined db_dialogs_OnDialogResponse
		db_dialogs_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#endif

	return 0;
}

#if defined _ALS_OnDialogResponse
	#undef OnDialogResponse
#else
	#define _ALS_OnDialogResponse
#endif
#define OnDialogResponse db_dialogs_OnDialogResponse
#if defined db_dialogs_OnDialogResponse
	forward db_dialogs_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif
