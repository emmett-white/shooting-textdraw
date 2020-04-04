/*
  * Include: shooting-textdraw.inc
  * Author: Emmett
  * Date: 3th April
  * Time: 07:08 AM
  * Copyright (C) 2020
  * Credits: Emmet_ - New SA-MP callbacks (callbacks.inc)
*/

#include <a_samp>
#tryinclude <YSI_Coding\y_hooks>
#tryinclude <YSI_Visual\y_commands>
#tryinclude <sscanf2>

static PlayerText:ShootingTextDraw[MAX_PLAYERS];

// ----
// API
// ----

#if !defined _easyDialog_included
	enum { st_DIALOG_COLOR }
#endif

static
	bool:st_WEAPON_ID[MAX_PLAYERS],
	bool:showedShootingTD[MAX_PLAYERS];

// ----
// Hook
// ----

hook OnPlayerConnect(playerid)
{
    showedShootingTD[playerid] = false;
    st_WEAPON_ID[playerid] = false;

    ShootingTextDraw[playerid] = 	CreatePlayerTextDraw(
    	playerid,
    	319.725250,
    	317.686828,
    	"_"
    );

    PlayerTextDrawLetterSize(playerid, 			ShootingTextDraw[playerid], 0.237499, 0.754166);
    PlayerTextDrawAlignment(playerid, 			ShootingTextDraw[playerid], 2);
    PlayerTextDrawColor(playerid,	 			ShootingTextDraw[playerid], -1);
    PlayerTextDrawSetShadow(playerid, 			ShootingTextDraw[playerid], 0);
    PlayerTextDrawSetOutline(playerid, 			ShootingTextDraw[playerid], 1);
    PlayerTextDrawBackgroundColor(playerid, 	ShootingTextDraw[playerid], 255); // white
    PlayerTextDrawFont(playerid, 				ShootingTextDraw[playerid], 1);
    PlayerTextDrawSetProportional(playerid, 	ShootingTextDraw[playerid], 1);
    PlayerTextDrawSetShadow(playerid, 			ShootingTextDraw[playerid], 0);
    return 1;
}

#if !defined _easyDialog_included
	hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
	{
		if (dialogid == st_DIALOG_COLOR) {
			if (!response)
				return 1;

			static __color;
			if (sscanf(inputtext, "x", __color))
				return 0;

			PlayerTextDrawColor(playerid, ShootingTextDraw[playerid], __color);
		}
		return 1;
	}
#else
	Dialog:DialogSTColor (const playerid, response, listitem, const inputtext[])
	{
		if (!response)
			return 1;

		static __color;
		if (sscanf(inputtext, "x", __color))
				return 0;

		PlayerTextDrawColor(playerid, ShootingTextDraw[playerid], __color);
		return 1;
	}
#endif

// ----
// Callbacks
// ----

public OnPlayerHoldingKey(playerid, keys)
{
	// If holding KEY_FIRE (MOUSE1 / Left Mouse / LMB)
    if (keys & KEY_FIRE) {
        if (GetPlayerWeapon(playerid) != 0) {
            if (!showedShootingTD[playerid])
                PlayerTextDrawShow(playerid, ShootingTextDraw[playerid]);

            showedShootingTD[playerid] = true;

            new
           		String[70];

            if (st_WEAPON_ID[playerid]) {
            	format(String, sizeof String, "\
                	Weapon_ID:_%d_-_Ammo:_%d",
                	GetPlayerWeapon(playerid), GetPlayerAmmo(playerid));
            } else {
            	format(String, sizeof String, "\
                	Ammo:_%d", GetPlayerAmmo(playerid));
            }

            PlayerTextDrawSetString(playerid, ShootingTextDraw[playerid], String);
        }
    }
    return 1;
}

public OnPlayerReleaseKey(playerid, keys, time)
{
	// If stop holding KEY_FIRE (MOUSE1 / Left Mouse / LMB)
    if (keys & KEY_FIRE || showedShootingTD[playerid] || GetPlayerWeapon(playerid) != 0) {
        PlayerTextDrawHide(playerid, ShootingTextDraw[playerid]);

        showedShootingTD[playerid] = false;
    }
    return 1;
}

// ----
// Command
// ----

YCMD:showwid(playerid, const params[], help)
{
	if (!st_WEAPON_ID[playerid]) {
		st_WEAPON_ID[playerid] = true;
	} else {
		st_WEAPON_ID[playerid] = false;
	}
	return 1;
}

YCMD:stcolor(playerid, const params[], help)
{
	#if defined _easyDialog_included
		Dialog_Show(playerid, "DialogSTColor", DIALOG_STYLE_INPUT,
			"Shooting-TextDraw Color",
			"Enter color (example: FF0000AA):",
			">", "Cancel"
		);
	#else
		ShowPlayerDialog(playerid, st_DIALOG_COLOR, DIALOG_STYLE_INPUT,
			"Shooting-TextDraw Color",
			"Enter color (example: FF0000AA):",
			">", "Cancel"
		);
	#endif

	return 1;
}
