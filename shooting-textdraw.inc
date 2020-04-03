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


static
    PlayerText:ShootingTextDraw[MAX_PLAYERS],
    bool:showedShootingTD[MAX_PLAYERS];


// ----
// Hook
// ----

hook OnPlayerConnect(playerid)
{
	// Setting variable to false (0)
    showedShootingTD[playerid] = false;

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
    PlayerTextDrawBackgroundColor(playerid, 	ShootingTextDraw[playerid], 255);
    PlayerTextDrawFont(playerid, 				ShootingTextDraw[playerid], 1);
    PlayerTextDrawSetProportional(playerid, 	ShootingTextDraw[playerid], 1);
    PlayerTextDrawSetShadow(playerid, 			ShootingTextDraw[playerid], 0);
    return 1;
}

// From callbacks.inc
public OnPlayerHoldingKey(playerid, keys)
{
	// If holding KEY_FIRE (MOUSE1 / Left Mouse / LMB)
    if (keys & KEY_FIRE) {
        if (GetPlayerWeapon(playerid) != 0) { // If a player has any weapon/s
            if (!showedShootingTD[playerid])
                PlayerTextDrawShow(playerid, ShootingTextDraw[playerid]);

            // Setting variable to true (1)
            showedShootingTD[playerid] = true;

            new String[70];
            format(String, sizeof String, "\
                ~w~Weapon_ID:_~y~%d_~w~|_Ammo:_~y~%d",
                GetPlayerWeapon(playerid), GetPlayerAmmo(playerid));

            PlayerTextDrawSetString(playerid, ShootingTextDraw[playerid], String);
        }
    }
    return 1;
}

// ----
// Callbacks
// ----

// From callbacks.inc
public OnPlayerReleaseKey(playerid, keys, time)
{
	// If stop holding KEY_FIRE (MOUSE1 / Left Mouse / LMB)
	// If a player has any weapon/s and if textdraw showed
    if (keys & KEY_FIRE || showedShootingTD[playerid] || GetPlayerWeapon(playerid) != 0) {
        PlayerTextDrawHide(playerid, ShootingTextDraw[playerid]);

        // Setting variable to false (0)
        showedShootingTD[playerid] = false;
    }
    return 1;
}
