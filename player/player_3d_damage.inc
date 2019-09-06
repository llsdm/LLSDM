#if defined PLAYER_3D_DAMAGE
	#endinput
#endif
#define PLAYER_3D_DAMAGE

static enum
{
	MAX_3D_DAMAGE_OBJECTS = 300
}

static enum Float:
{
	DIS_3D_DAMAGE = -0.5
}

static
	Float:player_3d_damage_x[MAX_PLAYERS],
	Float:player_3d_damage_y[MAX_PLAYERS],
	Float:player_3d_damage_z[MAX_PLAYERS],

	player_3d_damage_index,
	player_3d_damage_objs[MAX_3D_DAMAGE_OBJECTS];

public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{
	if (hittype == BULLET_HIT_TYPE_PLAYER)
	{
		GetPlayerPos(hitid, player_3d_damage_x[playerid], player_3d_damage_y[playerid], player_3d_damage_z[playerid]);
		player_3d_damage_x[playerid] += fX;
		player_3d_damage_y[playerid] += fY;
		player_3d_damage_z[playerid] += fZ;
	}

	#if defined player_3d_damage_OnPlayerWeapon
		player_3d_damage_OnPlayerWeapon(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ);
	#endif

	return 1;
}

#if defined _ALS_OnPlayerWeaponShot
	#undef OnPlayerWeaponShot
#else
	#define _ALS_OnPlayerWeaponShot
#endif
#define OnPlayerWeaponShot player_3d_damage_OnPlayerWeapon
#if defined player_3d_damage_OnPlayerWeapon
	forward player_3d_damage_OnPlayerWeapon(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ);
#endif

public OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart)
{
	new
		str[4],
		Float:px, Float:py, Float:pz,
		Float:x, Float:y, Float:z,
		Float:a;

	GetPlayerPos(issuerid, px, py, pz);

	if (issuerid != INVALID_PLAYER_ID)
	{
		x = player_3d_damage_x[issuerid];
		y = player_3d_damage_y[issuerid];
		z = player_3d_damage_z[issuerid];
	}
	
	a = atan2(y-py, x-px)-90.0;
	if (a < 0.0) a += 360.0;
	else if (a >= 360.0) a -= 360.0;
	x += (DIS_3D_DAMAGE * floatsin(-a, degrees));
	y += (DIS_3D_DAMAGE * floatcos(-a, degrees));

	player_3d_damage_index++;
	player_3d_damage_index %= MAX_3D_DAMAGE_OBJECTS;

	format(str, sizeof str, "%.0f", amount);
	player_3d_damage_objs[player_3d_damage_index-1] = CreateDynamicObject(19476, x, y, z, 0.0, 0.0, a-90.0, .playerid = issuerid);
	SetDynamicObjectMaterialText(player_3d_damage_objs[player_3d_damage_index-1], 0, str, 120, "Arial", 90,  1, 0xFFFFFFFF, 0, 1);
	Streamer_Update(issuerid, STREAMER_TYPE_OBJECT);
	MoveDynamicObject(player_3d_damage_objs[player_3d_damage_index-1], x, y, z+0.05, 0.1);

	#if defined player_3d_damage_OnPlayerTDam
		player_3d_damage_OnPlayerTDam(playerid, issuerid, Float:amount, weaponid, bodypart);
	#endif

	return 1;
}

#if defined _ALS_OnPlayerTakeDamage
	#undef OnPlayerTakeDamage
#else
	#define _ALS_OnPlayerTakeDamage
#endif
#define OnPlayerTakeDamage player_3d_damage_OnPlayerTDam
#if defined player_3d_damage_OnPlayerTDam
	forward player_3d_damage_OnPlayerTDam(playerid, issuerid, Float:amount, weaponid, bodypart);
#endif

public OnDynamicObjectMoved(objectid)
{
	for (new i = 0; i < MAX_3D_DAMAGE_OBJECTS; i++)
	{
		if (objectid == player_3d_damage_objs[i])
		{
			DestroyDynamicObject(player_3d_damage_objs[i]);
			player_3d_damage_objs[i] = 0;
		}
	}

	#if defined player_3d_damage_OnDynObjMoved
		player_3d_damage_OnDynObjMoved(objectid);
	#endif

	return 1;
}

#if defined _ALS_OnDynamicObjectMoved
	#undef OnDynamicObjectMoved
#else
	#define _ALS_OnDynamicObjectMoved
#endif
#define OnDynamicObjectMoved player_3d_damage_OnDynObjMoved
#if defined player_3d_damage_OnDynObjMoved
	forward player_3d_damage_OnDynObjMoved(objectid);
#endif