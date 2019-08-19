#if defined DB_CREATE
	#endinput
#endif
#define DB_CREATE

stock CreateNewAccount(playerid, password[], email[], skinid)
{
	static const
		str_y[] = "Аккаунт %s успешно зарегистрирован. Администрация желает Вам приятной игры!",
		str[] = "INSERT INTO `accounts` (`pName`, `pPassword`, `pEmail`, `pSkin`) VALUES ('%s', '%s', '%s', '%i')";
		
	static
		string[sizeof str + MAX_PLAYER_NAME + 32 + 64 + 3 - 2*3];

	format(string, sizeof string, str, pInfo[playerid][pName], password, email, skinid);
	mysql_tquery(mysql_connect_ID, string, "UploadPlayerAccountNumber", "i", playerid);
 
	format(string, sizeof string, str_y, pInfo[playerid][pName]);
	SendClientMessage(playerid, 0xFFFFFF00, string);
	CreateSpawnInfo(playerid);
	SetPlayerVirtualWorld(playerid, 0);
	SetPlayerInterior(playerid, 0);

	return 1;
}

forward UploadPlayerAccountNumber(playerid);
public UploadPlayerAccountNumber(playerid) pInfo[playerid][pID] = cache_insert_id();