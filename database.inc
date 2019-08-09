#if defined DATABASE
	#endinput
#endif
#define DATABASE

#define MYSQL_HOST				"localhost"
#define MYSQL_USER				"root"
#define MYSQL_DATABASE				"llsdm"
#define MYSQL_PASSWORD				""

new
	MySQL:mysql_connect_ID;

public OnGameModeInit()
{
	mysql_connect_ID = mysql_connect(MYSQL_HOST, MYSQL_USER, MYSQL_PASSWORD, MYSQL_DATABASE);

	mysql_tquery(mysql_connect_ID, !"SET CHARACTER SET 'utf8'", "", "");
	mysql_tquery(mysql_connect_ID, !"SET NAMES 'utf8'", "", "");
	mysql_tquery(mysql_connect_ID, !"SET character_set_client = 'cp1251'", "", "");
	mysql_tquery(mysql_connect_ID, !"SET character_set_connection = 'cp1251'", "", "");
	mysql_tquery(mysql_connect_ID, !"SET character_set_results = 'cp1251'", "", "");
	mysql_tquery(mysql_connect_ID, !"SET SESSION collation_connection = 'utf8_general_ci'", "", "");

	switch (mysql_errno())
	{
		case 0: print(!"Подключение к базе данных удалось");
		case 1044: print(!"Подключение к базе данных не удалось [Указано неизвестное имя пользователя]");
		case 1045: print(!"Подключение к базе данных не удалось [Указан неизвестный пароль]");
		case 1049: print(!"Подключение к базе данных не удалось [Указана неизвестная база данных]");
		case 2003: print(!"Подключение к базе данных не удалось [Хостинг с базой данных недоступен]");
		case 2005: print(!"Подключение к базе данных не удалось [Указан неизвестный адрес хостинга]");
		default: printf("Подключение к базе данных не удалось [Неизвестная ошибка. Код ошибки: %d]", mysql_errno());
	}

	#if defined database_OnGameModeInit
		database_OnGameModeInit();
	#endif

	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit database_OnGameModeInit
#if  defined database_OnGameModeInit
	forward database_OnGameModeInit();
#endif

#include "../LLSDM/player/database/db_dialogs.inc"
#include "../LLSDM/player/database/db_ban.inc"
#include "../LLSDM/player/database/db_skin.inc"
#include "../LLSDM/player/database/db_connect.inc"
#include "../LLSDM/player/database/db_create.inc"
#include "../LLSDM/player/database/db_save.inc"
#include "../LLSDM/player/database/db_upload.inc"
#include "../LLSDM/player/database/db_remove.inc"
