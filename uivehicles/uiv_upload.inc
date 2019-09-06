#if defined UIV_UPLOAD
	#endinput
#endif
#define UIV_UPLOAD

public OnGameModeInit()
{
	mysql_tquery(mysql_connect_ID, "SELECT * FROM `vehicles` WHERE `status` = '1'", "UploadVehicles", "");

	#if defined uiv_upload_OnGameModeInit
		uiv_upload_OnGameModeInit();
	#endif

	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit uiv_upload_OnGameModeInit
#if defined uiv_upload_OnGameModeInit
	forward uiv_upload_OnGameModeInit();
#endif

forward UploadVehicles();
public UploadVehicles()
{
	new
		vehicleid, modelid,
		Float:x, Float:y, Float:z, Float:a,
		rows;
		
	cache_get_row_count(rows);

	if (rows > 0)
	{
		for (new i = 0; i < rows; i++)
		{
			cache_get_value_name_int(i, "modelid", modelid);
			cache_get_value_name_float(i, "pos_x", x);
			cache_get_value_name_float(i, "pos_y", y);
			cache_get_value_name_float(i, "pos_z", z);
			cache_get_value_name_float(i, "angle", a);
			vehicleid = CreateUIVehicle(modelid, x, y, z, a);
			cache_get_value_name_int(i, "index", uiv[vehicleid][uiv_index]);

			if (modelid == COLLECTOR)
			{
				MAX_COLLECTOR_VEHICLES++;
			}
		}
	}

	return 1;
}