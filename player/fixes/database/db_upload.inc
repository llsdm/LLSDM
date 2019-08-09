#if defined DB_UPLOAD
	#endinput
#endif
#define DB_UPLOAD

forward UploadPlayerAccount(playerid);
public UploadPlayerAccount(playerid)
{
	new
		buff[100];

	cache_get_value_name_int(0, "pID", pInfo[playerid][pID]);
	cache_get_value_name_int(0, "pAdmin", pInfo[playerid][pAdmin]);
	cache_get_value_name_int(0, "pLife", pInfo[playerid][pLife]);
	cache_get_value_name_float(0, "pHealth", pInfo[playerid][pHealth]);

	cache_get_value_name_int(0, "pExpLife", pInfo[playerid][pExpLife]);
	cache_get_value_name_int(0, "pExp", pInfo[playerid][pExp]);
	cache_get_value_name_int(0, "pMoney", pInfo[playerid][pMoney]);

	cache_get_value_name_int(0, "pKills", pInfo[playerid][pKills]);
	cache_get_value_name_int(0, "pTimeKill", pInfo[playerid][pTimeKill]);
	cache_get_value_name_int(0, "pKillsLife", pInfo[playerid][pKillsLife]);
	cache_get_value_name_int(0, "pDeaths", pInfo[playerid][pDeaths]);

	cache_get_value_name(0, "pWeapons", buff);
	sscanf(buff, !"p<|>a<i>[3]", pInfo[playerid][pWeapons]);
	cache_get_value_name_int(0, "pSecondWeapon", pInfo[playerid][pSecondWeapon]);
	cache_get_value_name(0, "pAmmo", buff);
	sscanf(buff, !"p<|>a<i>[2]", pInfo[playerid][pAmmo]);

	cache_get_value_name_int(0, "pBackpackLvl", pInfo[playerid][pBackpackLvl]);
	cache_get_value_name_int(0, "pBackpackSize", pInfo[playerid][pBackpackSize]);

	cache_get_value_name(0, "pBackpackIndex", buff);
	sscanf(buff, !"p<|>a<i>["#MAX_BACKPACK_SLOTS"]", backpack_index[playerid]);
	cache_get_value_name(0, "pBackpackNumber", buff);
	sscanf(buff, !"p<|>a<i>["#MAX_BACKPACK_SLOTS"]", backpack_number[playerid]);

	if (pInfo[playerid][pLife] != 0)
	{
		new
			Float:pos_x,
			Float:pos_y,
			Float:pos_z,
			Float:angle;

		cache_get_value_name(0, "pPosition", buff);
		sscanf(buff, !"p<|>ffff", pos_x, pos_y, pos_z, angle);

		SetSpawnInfo(playerid, 0, pInfo[playerid][pSkin], pos_x, pos_y, pos_z, angle, pInfo[playerid][pWeapons][0], pInfo[playerid][pAmmo][0], pInfo[playerid][pWeapons][1], pInfo[playerid][pAmmo][1], 0, 0);

		GetKillLeader();
	}
	else
		CreateSpawnInfo(playerid);

	SendClientMessage(playerid, COLOR_LIME, !"Вы успешно авторизировались!");

	TogglePlayerSpectating(playerid, false);
	
	return 1;
}
