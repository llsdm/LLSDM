#if defined LLSDM_EDITOR
	#endinput
#endif
#define LLSDM_EDITOR

#define UIV_EDITOR_TITLE						"LLSDM > Создать транспорт"
#define UIV_EDITOR_DIALOGID_CREATE_VEHICLE		11000

static const
	uiv_editor_vehicleid[] =
	{
		416,
		428,
		433,
		427,
		596,
		597,
		598,
		599
	},
	uiv_editor_vehiclegroup[] =
	{
		1,
		2,
		3,
		4,
		4,
		4,
		4,
		4
	};

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if (dialogid == UIV_EDITOR_DIALOGID_CREATE_VEHICLE)
	{
		if (response == 0)
		{
			return 0;
		}

		static const
			str[] = "INSERT INTO `vehicles` (`modelid`, `status`, `group`, `pos_x`, `pos_y`, `pos_z`, `angle`) VALUES ('%i', '1', '%i', '%.4f', '%.4f', '%.4f', '%.4f')";

		new
			Float:x, Float:y, Float:z, Float:a,
			vehicleid,
			group = uiv_editor_vehiclegroup[listitem],
			modelid = uiv_editor_vehicleid[listitem],
			string[sizeof str + 11 + 9*4 - (2 + 4*4)];

		GetPlayerPos(playerid, x, y, z);
		GetPlayerFacingAngle(playerid, a);

		vehicleid = CreateUIVehicle(modelid, x, y, z, a);

		if (modelid == COLLECTOR)
		{
			MAX_COLLECTOR_VEHICLES++;
		}


		PutPlayerInVehicle(playerid, vehicleid, 0);

		format(string, sizeof string, str, 
			modelid, 
			group, 
			x, y, z, a
		);
			
		mysql_tquery(mysql_connect_ID, string, !"UploadVehicleNumber", "i", vehicleid);

		SendClientMessage(playerid, COLOR_LIME, !"Транспорт создан");
	}

	#if defined uiv_editor_OnDialogResponse
		uiv_editor_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#endif

	return 0;
}

#if defined _ALS_OnDialogResponse
	#undef OnDialogResponse
#else
	#define _ALS_OnDialogResponse
#endif
#define OnDialogResponse uiv_editor_OnDialogResponse
#if defined uiv_editor_OnDialogResponse
	forward uiv_editor_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif

forward UploadVehicleNumber(vehicleid);
public UploadVehicleNumber(vehicleid) uiv[vehicleid][uiv_index] = cache_insert_id();

CMD:create(playerid)
{
	if (pInfo[playerid][pAdmin] != 10)
	{
		return SendClientMessage(playerid, COLOR_ERROR, !"Вы не уполномочены использовать данную команду!");
	}

	return ShowPlayerDialog(playerid, UIV_EDITOR_DIALOGID_CREATE_VEHICLE, DIALOG_STYLE_LIST, !"#UIV_EDITOR_TITLE", !"AMBULANCE\nCOLLECTOR\nTRUCK\nPOLICE_VAN\nPOLICE_LS\nPOLICE_SF\nPOLICE_LV\nPOLICE_JEEP", !"Выбрать", !"Закрыть");	
}

CMD:saveh(playerid)
{
	if (pInfo[playerid][pAdmin] != 10)
	{
		return SendClientMessage(playerid, COLOR_ERROR, !"Вы не уполномочены использовать данную команду!");
	}

	static const
		str[] = "UPDATE `vehicles` SET `pos_x` = '%.4f', `pos_y` = '%.4f', `pos_z` = '%.4f', `angle` = '%.4f' WHERE `index` = '%i'";

	new
		Float:x, Float:y, Float:z, Float:a,
		vehicleid = GetPlayerVehicleID(playerid),
		string[sizeof str + (4+1+4)*4 + 11 - (2 + 4*4)];

	if (vehicleid == 0)
	{
		return SendClientMessage(playerid, COLOR_ERROR, !"Вы не в транспортном средстве!");
	}

	GetVehiclePos(vehicleid, x, y, z);
	GetVehicleZAngle(vehicleid, a);
 
	format(string, sizeof string, str,
		x,
		y,
		z,
		a,
		uiv[vehicleid][uiv_index]
	);

	mysql_tquery(mysql_connect_ID, string, "", "");

	return SendClientMessage(playerid, COLOR_LIME, !"Транспорт сохранен");
}

CMD:delveh(playerid)
{
	if (pInfo[playerid][pAdmin] != 10)
	{
		return SendClientMessage(playerid, COLOR_ERROR, !"Вы не уполномочены использовать данную команду!");
	}

	static const
		str[] = "DELETE FROM `vehicles` WHERE `index` = '%i'";

	new
		vehicleid = GetPlayerVehicleID(playerid),
		modelid = GetVehicleModel(vehicleid),
		string[sizeof str + 4 - 2];

	if (vehicleid == 0)
	{
		return SendClientMessage(playerid, COLOR_ERROR, !"Вы не в транспортном средстве!");
	}

	format(string, sizeof string, str, uiv[vehicleid][uiv_index]);
		
	mysql_tquery(mysql_connect_ID, string, "", "");

	DestroyDynamicObject(uiv[vehicleid][uiv_object1]);
	DestroyDynamicObject(uiv[vehicleid][uiv_object2]);
	DestroyVehicle(vehicleid);

	foreach(Player, i)
	{
		if (uiv_vehicleid[i] == vehicleid)
		{
			if (modelid == COLLECTOR)
			{
				DeathPlayerWithBagMoney(i);
				RestoreCollectorVehicleTimer(i, vehicleid);
				ClearPlayerIDFromArrayCollector(i);
			}

			TrunkOrRearDoorsOfVehicle(i);
			ClosePlayerDialog(i);

			break;
		}	
	}

	switch (modelid)
	{
		case AMBULANCE: uiv[vehicleid][uiv_kits] = 0;
		case COLLECTOR:
		{
			uiv[vehicleid][uiv_time] =
			uiv[vehicleid][uiv_timer] =
			uiv[vehicleid][uiv_pickup] = 0;

			uiv[vehicleid][uiv_hack] =
			uiv[vehicleid][uiv_death] = false;

			MAX_COLLECTOR_VEHICLES--;
		}
		case TRUCK:
		{
			for (new i = 0; i < UIV_MAX_AMMO; i++)
			{
				uiv[vehicleid][uiv_ammo][i] =
				uiv[vehicleid][uiv_ammoID][i] = 0;
			}
		}
		case POLICE_VAN:
		{
			for (new i = 0; i < UIV_MAX_WEAPONS; i++)
			{
				uiv[vehicleid][uiv_weapons][i] = 0;
			}

			uiv[vehicleid][uiv_backpacks] = 0;
		}
		case POLICE_LS, POLICE_SF, POLICE_LV, POLICE_JEEP: uiv[vehicleid][uiv_weapon] = 0;
	}

	uiv[vehicleid][uiv_size] =
	uiv[vehicleid][uiv_object1] =
	uiv[vehicleid][uiv_object2] = 0;

	uiv[vehicleid][uiv_dist] = 0.0;

	uiv[vehicleid][uiv_anim] =
	uiv[vehicleid][uiv_drop] =
	uiv[vehicleid][uiv_loot] = false;

	return SendClientMessage(playerid, COLOR_LIME, !"Транспорт удален");
}