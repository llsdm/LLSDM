#if defined ADMIN_CLICK_MAP
	#endinput
#endif
#define ADMIN_CLICK_MAP

static
	bool:click_map;

public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
	if (click_map)
		SetPlayerPosFindZ(playerid, fX, fY, fZ);

    return 1;
}

CMD:maptp(playerid)
{
    if (pInfo[playerid][pAdmin] < 6)
        return SendClientMessage(playerid, COLOR_ERROR, !"Вы не уполномочены использовать данную команду!");

    click_map = !click_map;

    return SendClientMessage(playerid, COLOR_LIME, click_map ? !"Телепорт по метке включен" : !"Телепорт по метке выключен");
}
