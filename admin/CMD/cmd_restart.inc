#if defined ADMIN_CMD_RESTART
	#endinput
#endif
#define ADMIN_CMD_RESTART

const
	RESTART_TIME = 3,
	RESTART_5_MIN = 5*1000*60,
	RESTART_1_HOUR = 1*1000*60*60;

static
	restart_timer_now;

CMD:restart(playerid, params[])
{
	if (pInfo[playerid][pAdmin] != MAX_ADMIN_LEVELS)
		return SendClientMessage(playerid, COLOR_ERROR, !"Вы не уполномочены использовать данную команду!");

	SendClientMessageToAll(COLOR_ADMIN, !"Через 5 минут рестарт сервера!");

	restart_timer_now = SetTimer(!"AdminRestart", RESTART_5_MIN, false);

	return 1;
}

CMD:stoprestart(playerid, params[])
{
	if (pInfo[playerid][pAdmin] != MAX_ADMIN_LEVELS)
		return SendClientMessage(playerid, COLOR_ERROR, !"Вы не уполномочены использовать данную команду!");

	if (restart_timer_now == 0)
		return SendClientMessage(playerid, COLOR_ERROR, !"Рестарт сервера не запущен");

	SendClientMessageToAll(COLOR_ADMIN, !"Рестарт сервера отменен!");

	KillTimer(restart_timer_now);
	restart_timer_now = 0;

	return 1;
}

forward AdminRestart();
public AdminRestart()
{
	SendRconCommand("gmx");

	return 1;
}

public OnGameModeInit()
{
	SetTimer(!"RestartServer", RESTART_1_HOUR, true);

	#if defined restart_OnGameModeInit
		restart_OnGameModeInit();
	#endif

	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit restart_OnGameModeInit
#if  defined restart_OnGameModeInit
	forward restart_OnGameModeInit();
#endif

forward RestartServer();
public RestartServer()
{
	new
		hour;

	gettime(hour, _, _);

	if (hour == RESTART_TIME)
	{
		SendClientMessageToAll(COLOR_ADMIN, !"Через 5 минут рестарт сервера!");

		restart_timer_now = SetTimer(!"AdminRestart", RESTART_5_MIN, false);
	}

	return 1;
}
