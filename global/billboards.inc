#if defined BILLBOARDS
	#endinput
#endif
#define BILLBOARDS


static enum
	billboard_pos_info
	{
		billboard_pos_info_id,
		Float:billboard_pos_info_x,
		Float:billboard_pos_info_y,
		Float:billboard_pos_info_z,
		Float:billboard_pos_info_a
	};

const
	MAX_BILLBOARDS = 200,
	MAX_BILLBOARDS_LOGO = 200,

	BILLBOARD_OBJECTS = 8,
	BILLBOARD_OBJS_LOGO = 3,
	BILLBOARD_SPECIAL_OBJECTS = 2,
	BILLBOARD_BLOCK_OBJECTS = 6,
	BILLBOARD_BLOCK_OBJECTS_LOGO = 4,

	BILLBOARD_BLOCK = 18766,
	BILLBOARD_GROUP_1 = 1260,
	BILLBOARD_GROUP_2 = 1259,
	BILLBOARD_GROUP_3 = 1267,

	Float:BILLBOARD_GROUP_1_DIFFERENCE_Y = 0.64,

	BILLBOARD_COLOR = -1,
	BILLBOARD_BACKGROUND = -4062975,
	BILLBOARD_BACKGROUND_LOGO = 0xFFFF8C00,
	BILLBOARD_BACKGROUND_BLOCK = -16777216;

const
	BILLBOARDS_LEADER = BILLBOARD_OBJECTS+BILLBOARD_SPECIAL_OBJECTS+BILLBOARD_BLOCK_OBJECTS,
	BILLBOARDS_LOGO = BILLBOARD_OBJS_LOGO+(BILLBOARD_SPECIAL_OBJECTS-1)+BILLBOARD_BLOCK_OBJECTS_LOGO;

static const
	billboard_objects[BILLBOARD_OBJECTS][billboard_pos_info] =
	{
		{19480, 0.0400, 0.0000, 0.0000},
		{19480, 0.0600, 0.0000, -0.3500},
		{19477, 0.0600, 0.0000, -1.5000},
		{19477, 0.0600, 0.0000, -2.2400},
		{19482, 0.0600, 0.0000, 1.6000},
		{19476, 0.0800, 0.0000, 2.30000},
		{19477, 0.1000, 0.0000, 2.2900},
		{19477, 0.0600, 0.0000, 1.5500}
	},
	billboard_objects_logo[BILLBOARD_OBJS_LOGO-1][billboard_pos_info] =
	{
		{19483, 0.0400, 0.0000, 1.7700},
		{19479, 0.0400, 0.0000, 0.0000}
	},
	Float:billboard_block_objects_t1[BILLBOARD_BLOCK_OBJECTS][2] =
	{
		{6.05, -0.7},
		{6.05, 0.7},
		{-6.05, -0.7},
		{-6.05, 0.7},
		{0.0, -0.7},
		{0.0, 0.7}
	},
	Float:billboard_block_objects_t2[BILLBOARD_BLOCK_OBJECTS][2] =
	{
		{3.8, -1.2},
		{3.8, 1.2},
		{-3.8, -1.2},
		{-3.8, 1.2},
		{0.0, 0.0},
		{0.0, 0.0}
	},
	Float:billboard_block_objects_t3[BILLBOARD_BLOCK_OBJECTS_LOGO][2] =
	{
		{3.1, -1.45},
		{3.1, 1.45},
		{-3.1, -1.45},
		{-3.1, 1.45}
	};

static enum
	b_info
	{
		bIndex,
		bObject,
		bCity,
		bGroup,
		bBagBord,
		bMainLeader,
		bLeader[BILLBOARDS_LEADER],
		bMainLogo,
		bLogo[BILLBOARDS_LOGO]
	}

new
	billboard_info[MAX_BILLBOARDS][b_info],
	BILLBOARDS_NUMS_LEADER,
	BILLBOARDS_NUMS_LOGO;

public OnGameModeInit()
{
	mysql_tquery(mysql_connect_ID, "SELECT * FROM `billboards` WHERE `status` != '0' AND `group` != '3'", "CreatBillboards", "");
	mysql_tquery(mysql_connect_ID, "SELECT * FROM `billboards` WHERE `status` != '0' AND `group` = '3'", "CreatBillboardsLogo", "");

	#if defined billboard_OnGameModeInit
		billboard_OnGameModeInit();
	#endif

	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit billboard_OnGameModeInit
#if  defined billboard_OnGameModeInit
	forward billboard_OnGameModeInit();
#endif

forward CreatBillboards();
public CreatBillboards()
{
	new
		rows,
		modelid,
		Float:x, Float:y, Float:z, Float:a, Float:x_2, Float:y_2;

	cache_get_row_count(rows);

	BILLBOARDS_NUMS_LEADER = rows;

	if (BILLBOARDS_NUMS_LEADER != 0)
	{
		for (new i = 0; i < BILLBOARDS_NUMS_LEADER; i++)
		{
			cache_get_value_name_int(i, "id", modelid);
			cache_get_value_name_float(i, "pos_x", x);
			x_2 = x;
			cache_get_value_name_float(i, "pos_y", y);
			y_2 = y;
			cache_get_value_name_float(i, "pos_z", z);
			cache_get_value_name_float(i, "angle", a);

			CreateLeaderboard(i, modelid, x, y, z, x_2, y_2, a);
		}
	}

	return 1;
}

forward CreatBillboardsLogo();
public CreatBillboardsLogo()
{
	new
		rows,
		Float:x, Float:y, Float:z, Float:a, Float:a_3;

	cache_get_row_count(rows);

	if (rows != 0)
	{
		for (new i = 0; i < rows; i++)
		{
			cache_get_value_name_float(i, "pos_x", x);
			cache_get_value_name_float(i, "pos_y", y);
			cache_get_value_name_float(i, "pos_z", z);
			cache_get_value_name_float(i, "angle", a);
			a_3 = a;

			CreateLogoboard(x, y, z, a, a_3);
		}
	}

	return 1;
}

stock BillboardVector(&Float:x, &Float:y, Float:angle)
{
	new 
		Float:cx = x,
		Float:cy = y; 

	x = cx*floatcos(angle, degrees)-cy*floatsin(angle, degrees); 
	y = cx*floatsin(angle, degrees)+cy*floatcos(angle, degrees); 
	return 1;
}

stock UpdateBillboard(playerid, kills)
{
	new
		str_kills[3],
		str_title[3],
		string[MAX_PLAYER_NAME];

	if (kills > 0)
	{
		strcat(string, pInfo[playerid][pName]);
		str_title = !"";
		valstr(str_kills, kills);
	}
	else
	{
		strcat(string, !"KILL");
		str_title = !"LEADER";
		str_kills = !"LLSDM";
	}

	for (new i = 0; i < BILLBOARDS_NUMS_LEADER; i++)
	{
		SetDynamicObjectMaterialText(billboard_info[i][bLeader][2], 0, string, 120, !"Arial", 35, 0, BILLBOARD_COLOR, 0, 1);
		SetDynamicObjectMaterialText(billboard_info[i][bLeader][4], 0, str_title, 130, !"Arial", 100, 1, BILLBOARD_COLOR, 0, 1);
		SetDynamicObjectMaterialText(billboard_info[i][bLeader][5], 0, str_kills, 130, !"Arial", 180, 1, BILLBOARD_COLOR, 0, 1);
	}

	return 1;
}

stock CreateLeaderboard(billboardid, modelid, Float:x, Float:y, Float:z, Float:x_2, Float:y_2, Float:a)
{
	new
		info_id, type_1,
		Float:x_1, Float:y_1, Float:z_1, Float:a_1, Float:z_2,
		Float:difference_y;

	if (modelid == BILLBOARD_GROUP_1)
	{
		billboard_info[billboardid][bMainLeader] = CreateDynamicObject(BILLBOARD_GROUP_1, x, y, z, 0.0, 0.0, a, -1, -1, -1, 300.0, 300.0);

		x_1 = -0.85;
		y_1 = 0.0;
		z_1 = 5.8;
		difference_y = 0.0;

		BillboardVector(x_1, y_1, a);

		x += x_1;
		y += y_1;
		z += z_1;
		a -= -180.0;

		billboard_info[billboardid][bLeader][0] = CreateDynamicObject(19480, x, y, z, 0.0, 0.0, a);
	}
	else
	{
		CreateDynamicObject(BILLBOARD_GROUP_2, x, y, z, 0.0, 0.0, a, -1, -1, -1, 300.0, 300.0);

		x_1 = -0.85;
		y_1 = -BILLBOARD_GROUP_1_DIFFERENCE_Y;
		z_1 = 6.456867;
		difference_y = BILLBOARD_GROUP_1_DIFFERENCE_Y*3;

		BillboardVector(x_1, y_1, a);

		x += x_1;
		y += y_1;
		z += z_1;
		a -= -180.0;

		billboard_info[billboardid][bLeader][0] = CreateDynamicObject(19479, x, y, z, 0.0, 0.0, a);

		x_1 = 0.85;
		y_1 = BILLBOARD_GROUP_1_DIFFERENCE_Y*4;

		BillboardVector(x_1, y_1, a);

		billboard_info[billboardid][bLeader][1] = CreateDynamicObject(19479, x_2+x_1, y_2+y_1, z, 0.0, 0.0, a);
	}

	for (new j = 0; j < BILLBOARD_OBJECTS; j++)
	{
		info_id = billboard_objects[j][billboard_pos_info_id],
		x_1 = billboard_objects[j][billboard_pos_info_x];
		y_1 = difference_y/2;
		z_1 = billboard_objects[j][billboard_pos_info_z];

		BillboardVector(x_1, y_1, a);

		billboard_info[billboardid][bLeader][j+BILLBOARD_SPECIAL_OBJECTS] = CreateDynamicObject(info_id, x+x_1, y+y_1, z+z_1, 0.0, 0.0, a);

		x_2 = x+x_1;
		y_2 = y+y_1;
		z_2 = z+z_1;
	}

	for (new b = 0, m = BILLBOARD_OBJECTS+BILLBOARD_SPECIAL_OBJECTS; b < BILLBOARD_BLOCK_OBJECTS; b++)
	{
		if (modelid == BILLBOARD_GROUP_1)
		{
			x_1 = -0.6;
			y_1 = billboard_block_objects_t1[b][0];
			z_1 = billboard_block_objects_t1[b][1];
			a_1 = a;
			type_1 = 1;
		}
		else
		{
			x_1 = -0.6;
			y_1 = billboard_block_objects_t2[b][0];
			z_1 = billboard_block_objects_t2[b][1];
			a_1 = a;

			if (_:z_1 == 0)
				break;
		} 

		BillboardVector(x_1, y_1, a_1);

		billboard_info[billboardid][bLeader][b+m] = CreateDynamicObject(BILLBOARD_BLOCK, x_2+x_1, y_2+y_1, z_2-z_1-1.55, 0.0, 0.0, a_1-90.0, -1, -1, -1, 300.0, 300.0);
	}

	SetDynamicObjectMaterialText(billboard_info[billboardid][bLeader][0], 0, !" ", 120, !"Arial", 35, 0, BILLBOARD_BACKGROUND, BILLBOARD_BACKGROUND, 1);
	if (modelid == BILLBOARD_GROUP_2)
		SetDynamicObjectMaterialText(billboard_info[billboardid][bLeader][1], 0, !" ", 120, !"Arial", 35, 0, BILLBOARD_BACKGROUND, BILLBOARD_BACKGROUND, 1);
	SetDynamicObjectMaterialText(billboard_info[billboardid][bLeader][2], 0, !"ИМЯ ИГРОКА", 120, !"Arial", 35, 0, BILLBOARD_COLOR, 0, 1);
	SetDynamicObjectMaterialText(billboard_info[billboardid][bLeader][3], 0, !"_____________", 130, !"Arial", 60, 0, BILLBOARD_COLOR, 0, 1);
	SetDynamicObjectMaterialText(billboard_info[billboardid][bLeader][4], 0, !"ЗАГОЛОВОК", 130, !"Arial", 100, 1, BILLBOARD_COLOR, 0, 1);
	SetDynamicObjectMaterialText(billboard_info[billboardid][bLeader][5], 0, !"СЧЕТЧИК", 130, !"Arial", 180, 1, BILLBOARD_COLOR, 0, 1);
	SetDynamicObjectMaterialText(billboard_info[billboardid][bLeader][6], 0, !"c", 130, !"Webdings", 140, 0, BILLBOARD_COLOR, 0, 1);
	SetDynamicObjectMaterialText(billboard_info[billboardid][bLeader][7], 0, !" ", 130, !"Arial", 60, 0, 0, BILLBOARD_BACKGROUND, 1);
	SetDynamicObjectMaterialText(billboard_info[billboardid][bLeader][8], 0, !"LLS", 130, !"Arial", 100, 1, BILLBOARD_COLOR, 0, 1);
	SetDynamicObjectMaterialText(billboard_info[billboardid][bLeader][9], 0, !"DM", 130, !"Arial", 160, 1, BILLBOARD_COLOR, 0, 1);

	SetDynamicObjectMaterialText(billboard_info[billboardid][bLeader][10], 0, " ", 10, " ", 0, 0, 0, BILLBOARD_BACKGROUND_BLOCK, 0);
	SetDynamicObjectMaterialText(billboard_info[billboardid][bLeader][11], 0, " ", 10, " ", 0, 0, 0, BILLBOARD_BACKGROUND_BLOCK, 0);
	SetDynamicObjectMaterialText(billboard_info[billboardid][bLeader][12], 0, " ", 10, " ", 0, 0, 0, BILLBOARD_BACKGROUND_BLOCK, 0);
	SetDynamicObjectMaterialText(billboard_info[billboardid][bLeader][13], 0, " ", 10, " ", 0, 0, 0, BILLBOARD_BACKGROUND_BLOCK, 0);
	if (type_1 == 1)
	{
		SetDynamicObjectMaterialText(billboard_info[billboardid][bLeader][14], 0, " ", 10, " ", 0, 0, 0, BILLBOARD_BACKGROUND_BLOCK, 0);
		SetDynamicObjectMaterialText(billboard_info[billboardid][bLeader][15], 0, " ", 10, " ", 0, 0, 0, BILLBOARD_BACKGROUND_BLOCK, 0);
	}

	return 1;
}

stock CreateLogoboard(Float:x, Float:y, Float:z, Float:a, Float:a_3)
{
	new
		info_id,
		Float:x_1, Float:y_1, Float:z_1, Float:a_1,
		Float:x_2, Float:y_2, Float:z_2, Float:a_2;

	billboard_info[BILLBOARDS_NUMS_LOGO][bMainLogo] = CreateDynamicObject(BILLBOARD_GROUP_3, x, y, z, 0.0, 0.0, a, -1, -1, -1, 300.0, 300.0);

	for (new j = 0; j < 2; j++)
	{
		if (j == 0)
		{
			x_1 = -2.8;
			y_1 = 0.15;
			z_1 = 5.4;
			a_1 = 172.619995;

			BillboardVector(x_1, y_1, a);

			x_2 = x+x_1;
			y_2 = y+y_1;
			z_2 = z+z_1;
			a_2 = a-180.0+a_1;

			billboard_info[BILLBOARDS_NUMS_LOGO][bLogo][2] = CreateDynamicObject(19479, x_2, y_2, z_2, 0.0, 0.0, a_2-180.0);
		}
		else
		{
			x_1 = 3.0;
			y_1 = 0.15;
			z_1 = 5.4;
			a_1 = 7.550000;

			BillboardVector(x_1, y_1, a);
					
			x_2 = x+x_1;
			y_2 = y+y_1;
			z_2 = z+z_1;
			a_2 = a-180.0+a_1;

			billboard_info[BILLBOARDS_NUMS_LOGO][bLogo][2] = CreateDynamicObject(19479, x_2, y_2, z_2, 0.0, 0.0, a_2);
		}

		for (new k = 0; k < 2; k++)
		{
			info_id = billboard_objects_logo[k][billboard_pos_info_id],
			x_1 = billboard_objects_logo[k][billboard_pos_info_x];
			y_1 = 0.0;
			z_1 = billboard_objects_logo[k][billboard_pos_info_z];
			a_3 = a_2-180.0;

			BillboardVector(x_1, y_1, a_3);

			billboard_info[BILLBOARDS_NUMS_LOGO][bLogo][k]  = CreateDynamicObject(info_id, x_2+x_1, y_2+y_1, z_2+z_1, 0.0, 0.0, a_3);
		}

		for (new b = 0, m = BILLBOARD_OBJS_LOGO; b < BILLBOARD_BLOCK_OBJECTS_LOGO; b++)
		{
			x_1 = 0.6;
			y_1 = billboard_block_objects_t3[b][0];
			z_1 = billboard_block_objects_t3[b][1];
			a_1 = a_2;

			BillboardVector(x_1, y_1, a_1);

			billboard_info[BILLBOARDS_NUMS_LOGO][bLogo][b+m] = CreateDynamicObject(BILLBOARD_BLOCK, x_2+x_1, y_2+y_1, z_2-z_1, 0.0, 0.0, a_1-90.0, -1, -1, -1, 300.0, 300.0);
		}	

		SetDynamicObjectMaterialText(billboard_info[BILLBOARDS_NUMS_LOGO][bLogo][0], 0, !"LLS", 130, !"Arial", 255, 1, BILLBOARD_COLOR, BILLBOARD_BACKGROUND_LOGO, 1);
		SetDynamicObjectMaterialText(billboard_info[BILLBOARDS_NUMS_LOGO][bLogo][1], 0, !"DM", 130, !"Arial", 85, 1, BILLBOARD_COLOR, 0, 1);
		SetDynamicObjectMaterialText(billboard_info[BILLBOARDS_NUMS_LOGO][bLogo][2], 0, !"c", 130, !"Webdings", 150, 0, BILLBOARD_COLOR, BILLBOARD_BACKGROUND_LOGO, 1);
		SetDynamicObjectMaterialText(billboard_info[BILLBOARDS_NUMS_LOGO][bLogo][3], 0, " ", 10, " ", 0, 0, 0, BILLBOARD_BACKGROUND_BLOCK, 0);
		SetDynamicObjectMaterialText(billboard_info[BILLBOARDS_NUMS_LOGO][bLogo][4], 0, " ", 10, " ", 0, 0, 0, BILLBOARD_BACKGROUND_BLOCK, 0);
		SetDynamicObjectMaterialText(billboard_info[BILLBOARDS_NUMS_LOGO][bLogo][5], 0, " ", 10, " ", 0, 0, 0, BILLBOARD_BACKGROUND_BLOCK, 0);
		SetDynamicObjectMaterialText(billboard_info[BILLBOARDS_NUMS_LOGO][bLogo][6], 0, " ", 10, " ", 0, 0, 0, BILLBOARD_BACKGROUND_BLOCK, 0);

		BILLBOARDS_NUMS_LOGO++;
	}

	return 1;
}
