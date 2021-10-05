/*
===========================================================================
Copyright (C) 1999-2005 Id Software, Inc.

This file is part of Quake III Arena source code.

Quake III Arena source code is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the License,
or (at your option) any later version.

Quake III Arena source code is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Quake III Arena source code; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
===========================================================================
*/
//
/*
=======================================================================

TEAM ORDERS MENU

=======================================================================
*/


#include "ui_local.h"


#define ART_FRAME		"menu/" MENU_ART_DIR "/addbotframe"
#define ART_BACK0		"menu/" MENU_ART_DIR "/back_0"
#define ART_BACK1		"menu/" MENU_ART_DIR "/back_1"

#define ID_LIST_BOTS		10
#define ID_LIST_CTF_ORDERS	11
#define ID_LIST_CTF1F_ORDERS	12
#define ID_LIST_BASE_ORDERS	13
#define ID_LIST_TEAM_ORDERS	14
#define ID_LIST_DD_ORDERS	15


typedef struct {
	menuframework_s	menu;

	menutext_s		banner;
	menubitmap_s	frame;

	menulist_s		list;

	menubitmap_s	back;

	int			gametype;
	int			numBots;
	char			*selectedBot;
	char			*bots[9];
	char			botNames[9][16];
} teamOrdersMenuInfo_t;

static teamOrdersMenuInfo_t	teamOrdersMenuInfo;

#define NUM_CTF_ORDERS		7
static const char *ctfOrders[] = {
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	NULL
};
static const char *ctfMessages[] = {
	"i am the leader",
	"%s defend the base",
	"%s follow me",
	"%s get the enemy flag",
	"%s camp here",
	"%s report",
	"i stop being the leader",
	NULL
};

#define NUM_CTF1F_ORDERS		7
//static const char *ctf1fOrders[] = {
//	"",
//	"",
//	"",
//	"",
//	"",
//	"",
//	"",
//	NULL
//};

static const char *ctf1fMessages[] = {
	"i am the leader",
	"%s defend the base",
	"%s follow me",
	"%s get the flag",
	"%s camp here",
	"%s report",
	"i stop being the leader",
	NULL
};

#define NUM_BASE_ORDERS		7
//static const char *baseOrders[] = {
//	"",
//	"",
//	"",
//	"",
//	"",
//	"",
//	"",
//	NULL
//};

static const char *baseMessages[] = {
	"i am the leader",
	"%s defend the base",
	"%s follow me",
	"%s attack the base",
	"%s camp here",
	"%s report",
	"i stop being the leader",
	NULL
};

#define NUM_TEAM_ORDERS		6
static const char *teamOrders[] = {
	"",
	"",
	"",
	"",
	"",
	"",
	NULL
};
static const char *teamMessages[] = {
	"i am the leader",
	"%s follow me",
	"%s roam",
	"%s camp here",
	"%s report",
	"i stop being the leader",
	NULL
};

#define NUM_DD_ORDERS		8
static const char *ddOrders[] = {
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	NULL
};
static const char *ddMessages[] = {
	"i am the leader",
	"%s follow me",
	"%s roam",
	"%s dominate point A",
	"%s dominate point B",
	"%s camp here",
	"%s report",
	"i stop being the leader",
	NULL
};

/*
===============
UI_TeamOrdersMenu_BackEvent
===============
*/
static void UI_TeamOrdersMenu_BackEvent( void *ptr, int event )
{
	if( event != QM_ACTIVATED ) {
		return;
	}
	UI_PopMenu();
}


/*
===============
UI_TeamOrdersMenu_SetList
===============
*/
static void UI_TeamOrdersMenu_SetList( int id )
{
        ctfOrders[0] = COM_Localize(281);
        ctfOrders[1] = COM_Localize(282);
        ctfOrders[2] = COM_Localize(283);

        ctfOrders[4] = COM_Localize(285);
        ctfOrders[5] = COM_Localize(286);
        ctfOrders[6] = COM_Localize(287);

	switch( id ) {
	default:
	case ID_LIST_BOTS:
		teamOrdersMenuInfo.list.generic.id = id;
		teamOrdersMenuInfo.list.numitems = teamOrdersMenuInfo.numBots;
		teamOrdersMenuInfo.list.itemnames = (const char **)teamOrdersMenuInfo.bots;
		break;

	case ID_LIST_CTF_ORDERS:
		teamOrdersMenuInfo.list.generic.id = id;
		teamOrdersMenuInfo.list.numitems = NUM_CTF_ORDERS;
		teamOrdersMenuInfo.list.itemnames = ctfOrders;
                teamOrdersMenuInfo.list.itemnames[3] = COM_Localize(284);
		break;

	case ID_LIST_CTF1F_ORDERS:
		teamOrdersMenuInfo.list.generic.id = id;
		teamOrdersMenuInfo.list.numitems = NUM_CTF1F_ORDERS;
		teamOrdersMenuInfo.list.itemnames = ctfOrders;
                teamOrdersMenuInfo.list.itemnames[3] = COM_Localize(284);
		break;

	case ID_LIST_BASE_ORDERS:
		teamOrdersMenuInfo.list.generic.id = id;
		teamOrdersMenuInfo.list.numitems = NUM_BASE_ORDERS;
		teamOrdersMenuInfo.list.itemnames = ctfOrders;
                teamOrdersMenuInfo.list.itemnames[3] = COM_Localize(289);
		break;

	case ID_LIST_TEAM_ORDERS:
		teamOrdersMenuInfo.list.generic.id = id;
		teamOrdersMenuInfo.list.numitems = NUM_TEAM_ORDERS;
		teamOrdersMenuInfo.list.itemnames = teamOrders;
                teamOrdersMenuInfo.list.itemnames[0] = ctfOrders[0];
                teamOrdersMenuInfo.list.itemnames[1] = ctfOrders[2];
                teamOrdersMenuInfo.list.itemnames[2] = COM_Localize(288);
                teamOrdersMenuInfo.list.itemnames[3] = ctfOrders[4];
                teamOrdersMenuInfo.list.itemnames[4] = ctfOrders[5];
                teamOrdersMenuInfo.list.itemnames[5] = ctfOrders[6];
		break;

	case ID_LIST_DD_ORDERS:
		teamOrdersMenuInfo.list.generic.id = id;
		teamOrdersMenuInfo.list.numitems = NUM_DD_ORDERS;
		teamOrdersMenuInfo.list.itemnames = ddOrders;
                teamOrdersMenuInfo.list.itemnames[0] = ctfOrders[0];
                teamOrdersMenuInfo.list.itemnames[1] = ctfOrders[2];
                teamOrdersMenuInfo.list.itemnames[2] = COM_Localize(288);
                teamOrdersMenuInfo.list.itemnames[3] = COM_Localize(290);
                teamOrdersMenuInfo.list.itemnames[4] = COM_Localize(291);
                teamOrdersMenuInfo.list.itemnames[5] = ctfOrders[4];
                teamOrdersMenuInfo.list.itemnames[6] = ctfOrders[5];
                teamOrdersMenuInfo.list.itemnames[7] = ctfOrders[6];
		break;
	}

	teamOrdersMenuInfo.list.generic.bottom = teamOrdersMenuInfo.list.generic.top + teamOrdersMenuInfo.list.numitems * PROP_HEIGHT;
}


/*
=================
UI_TeamOrdersMenu_Key
=================
*/
sfxHandle_t UI_TeamOrdersMenu_Key( int key )
{
	menulist_s	*l;
	int	x;
	int	y;
	int	index;

	l = (menulist_s	*)Menu_ItemAtCursor( &teamOrdersMenuInfo.menu );
	if( l != &teamOrdersMenuInfo.list ) {
		return Menu_DefaultKey( &teamOrdersMenuInfo.menu, key );
	}

	switch( key ) {
	case K_MOUSE1:
		x = l->generic.left;
		y = l->generic.top;
		if( UI_CursorInRect( x, y, l->generic.right - x, l->generic.bottom - y ) ) {
			index = (uis.cursory - y) / PROP_HEIGHT;
			l->oldvalue = l->curvalue;
			l->curvalue = index;

			if( l->generic.callback ) {
				l->generic.callback( l, QM_ACTIVATED );
				return menu_move_sound;
			}
		}
		return menu_null_sound;

	case K_KP_UPARROW:
	case K_UPARROW:
		l->oldvalue = l->curvalue;

		if( l->curvalue == 0 ) {
			l->curvalue = l->numitems - 1;
		}
		else {
			l->curvalue--;
		}
		return menu_move_sound;

	case K_KP_DOWNARROW:
	case K_DOWNARROW:
		l->oldvalue = l->curvalue;

		if( l->curvalue == l->numitems - 1 ) {
			l->curvalue = 0;;
		}
		else {
			l->curvalue++;
		}
		return menu_move_sound;
	}

	return Menu_DefaultKey( &teamOrdersMenuInfo.menu, key );
}


/*
=================
UI_TeamOrdersMenu_ListDraw
=================
*/
static void UI_TeamOrdersMenu_ListDraw( void *self )
{
	menulist_s	*l;
	int			x;
	int			y;
	int			i;
	float		*color;
	qboolean	hasfocus;
	int			style;

	l = (menulist_s *)self;

	hasfocus = (l->generic.parent->cursor == l->generic.menuPosition);

	x =	320;//l->generic.x;
	y =	l->generic.y;
	for( i = 0; i < l->numitems; i++ ) {
		style = UI_LEFT|UI_SMALLFONT|UI_CENTER;
		if( i == l->curvalue ) {
			color = color_yellow;
			if( hasfocus ) {
				style |= UI_PULSE;
			}
		}
		else {
			color = color_orange;
		}

		UI_DrawProportionalString( x, y, l->itemnames[i], style, color );
		y += PROP_HEIGHT;
	}
}


/*
===============
UI_TeamOrdersMenu_ListEvent
===============
*/
static void UI_TeamOrdersMenu_ListEvent( void *ptr, int event )
{
	int		id;
	int		selection;
	char	message[256];

	if (event != QM_ACTIVATED || !UI_IsATeamGametype(teamOrdersMenuInfo.gametype))
		return;

	id = ((menulist_s *)ptr)->generic.id;
	selection = ((menulist_s *)ptr)->curvalue;

	if( id == ID_LIST_BOTS ) {
                if (selection > 0) {
		        teamOrdersMenuInfo.selectedBot = teamOrdersMenuInfo.botNames[selection];
                } else {
                        teamOrdersMenuInfo.selectedBot = "Everyone";
                }
		if ( UI_UsesTeamFlags(teamOrdersMenuInfo.gametype) && !UI_UsesTheWhiteFlag(teamOrdersMenuInfo.gametype) ) {
			UI_TeamOrdersMenu_SetList( ID_LIST_CTF_ORDERS );
		} else if ( UI_UsesTeamFlags(teamOrdersMenuInfo.gametype) && UI_UsesTheWhiteFlag(teamOrdersMenuInfo.gametype) ) {
			UI_TeamOrdersMenu_SetList( ID_LIST_CTF1F_ORDERS );
		} else if ( teamOrdersMenuInfo.gametype == GT_HARVESTER || teamOrdersMenuInfo.gametype == GT_OBELISK ) {
			UI_TeamOrdersMenu_SetList( ID_LIST_BASE_ORDERS );
		} else if ( teamOrdersMenuInfo.gametype == GT_DOUBLE_D ) {
			UI_TeamOrdersMenu_SetList( ID_LIST_DD_ORDERS );
		} else {
			UI_TeamOrdersMenu_SetList( ID_LIST_TEAM_ORDERS );
		}
		return;
	}



	if( id == ID_LIST_CTF_ORDERS ) {
		Com_sprintf( message, sizeof(message), ctfMessages[selection], teamOrdersMenuInfo.selectedBot );
	}
	if( id == ID_LIST_CTF1F_ORDERS ) {
		Com_sprintf( message, sizeof(message), ctf1fMessages[selection], teamOrdersMenuInfo.selectedBot );
	}
	if( id == ID_LIST_BASE_ORDERS ) {
		Com_sprintf( message, sizeof(message), baseMessages[selection], teamOrdersMenuInfo.selectedBot );
	}
	if( id == ID_LIST_TEAM_ORDERS ) {
		Com_sprintf( message, sizeof(message), teamMessages[selection], teamOrdersMenuInfo.selectedBot );
	}
	if( id == ID_LIST_DD_ORDERS ) {
		Com_sprintf( message, sizeof(message), ddMessages[selection], teamOrdersMenuInfo.selectedBot );
	}

	trap_Cmd_ExecuteText( EXEC_APPEND, va( "say_team \"%s\"\n", message ) );
	UI_PopMenu();
}


/*
===============
UI_TeamOrdersMenu_BuildBotList
===============
*/
static void UI_TeamOrdersMenu_BuildBotList( void )
{
	uiClientState_t	cs;
	int		numPlayers;
	int		isBot;
	int		n;
	char	playerTeam;
	char	botTeam;
	char	info[MAX_INFO_STRING];

	for( n = 0; n < 9; n++ ) {
		teamOrdersMenuInfo.bots[n] = teamOrdersMenuInfo.botNames[n];
	}

	trap_GetClientState( &cs );

	Q_strncpyz( teamOrdersMenuInfo.botNames[0], COM_Localize(102), 16 );
	teamOrdersMenuInfo.numBots = 1;

	trap_GetConfigString( CS_SERVERINFO, info, sizeof(info) );
	numPlayers = atoi( Info_ValueForKey( info, "sv_maxclients" ) );
	teamOrdersMenuInfo.gametype = atoi( Info_ValueForKey( info, "g_gametype" ) );

	trap_GetConfigString( CS_PLAYERS + cs.clientNum, info, MAX_INFO_STRING );
	playerTeam = *Info_ValueForKey( info, "t" );

	for( n = 0; n < numPlayers && teamOrdersMenuInfo.numBots < 9; n++ ) {
		if( n == cs.clientNum ) {
			continue;
		}

		trap_GetConfigString( CS_PLAYERS + n, info, MAX_INFO_STRING );

		isBot = atoi( Info_ValueForKey( info, "skill" ) );
		if( !isBot ) {
			continue;
		}

		botTeam = *Info_ValueForKey( info, "t" );
		if( botTeam != playerTeam ) {
			continue;
		}

		Q_strncpyz( teamOrdersMenuInfo.botNames[teamOrdersMenuInfo.numBots], Info_ValueForKey( info, "n" ), 16 );
		Q_CleanStr( teamOrdersMenuInfo.botNames[teamOrdersMenuInfo.numBots] );
		teamOrdersMenuInfo.numBots++;
	}
}


/*
===============
UI_TeamOrdersMenu_Init
===============
*/
static void UI_TeamOrdersMenu_Init( void )
{
	UI_TeamOrdersMenu_Cache();

	memset( &teamOrdersMenuInfo, 0, sizeof(teamOrdersMenuInfo) );
	teamOrdersMenuInfo.menu.fullscreen = qfalse;
	teamOrdersMenuInfo.menu.key = UI_TeamOrdersMenu_Key;

	UI_TeamOrdersMenu_BuildBotList();

	teamOrdersMenuInfo.banner.generic.type		= MTYPE_BTEXT;
	teamOrdersMenuInfo.banner.generic.x			= 320;
	teamOrdersMenuInfo.banner.generic.y			= 16;
	teamOrdersMenuInfo.banner.string			= COM_Localize(208);
	teamOrdersMenuInfo.banner.color				= color_white;
	teamOrdersMenuInfo.banner.style				= UI_CENTER;

	teamOrdersMenuInfo.frame.generic.type		= MTYPE_BITMAP;
	teamOrdersMenuInfo.frame.generic.flags		= QMF_INACTIVE;
	teamOrdersMenuInfo.frame.generic.name		= ART_FRAME;
	teamOrdersMenuInfo.frame.generic.x			= 320-233;
	teamOrdersMenuInfo.frame.generic.y			= 240-166;
	teamOrdersMenuInfo.frame.width				= 466;
	teamOrdersMenuInfo.frame.height				= 332;

	teamOrdersMenuInfo.list.generic.type		= MTYPE_SCROLLLIST;
	teamOrdersMenuInfo.list.generic.flags		= QMF_PULSEIFFOCUS;
	teamOrdersMenuInfo.list.generic.ownerdraw	= UI_TeamOrdersMenu_ListDraw;
	teamOrdersMenuInfo.list.generic.callback	= UI_TeamOrdersMenu_ListEvent;
	teamOrdersMenuInfo.list.generic.x			= 320-64;
	teamOrdersMenuInfo.list.generic.y			= 120;

	teamOrdersMenuInfo.back.generic.type		= MTYPE_BITMAP;
	teamOrdersMenuInfo.back.generic.name		= ART_BACK0;
	teamOrdersMenuInfo.back.generic.flags		= QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS;
	teamOrdersMenuInfo.back.generic.callback	= UI_TeamOrdersMenu_BackEvent;
	teamOrdersMenuInfo.back.generic.x			= 0;
	teamOrdersMenuInfo.back.generic.y			= 480-64;
	teamOrdersMenuInfo.back.width				= 128;
	teamOrdersMenuInfo.back.height				= 64;
	teamOrdersMenuInfo.back.focuspic			= ART_BACK1;

	Menu_AddItem( &teamOrdersMenuInfo.menu, &teamOrdersMenuInfo.banner );
	Menu_AddItem( &teamOrdersMenuInfo.menu, &teamOrdersMenuInfo.frame );
	Menu_AddItem( &teamOrdersMenuInfo.menu, &teamOrdersMenuInfo.list );
	Menu_AddItem( &teamOrdersMenuInfo.menu, &teamOrdersMenuInfo.back );

	teamOrdersMenuInfo.list.generic.left = 220;
	teamOrdersMenuInfo.list.generic.top = teamOrdersMenuInfo.list.generic.y;
	teamOrdersMenuInfo.list.generic.right = 420;
	UI_TeamOrdersMenu_SetList( ID_LIST_BOTS );
}


/*
=================
UI_TeamOrdersMenu_Cache
=================
*/
void UI_TeamOrdersMenu_Cache( void )
{
	trap_R_RegisterShaderNoMip( ART_FRAME );
	trap_R_RegisterShaderNoMip( ART_BACK0 );
	trap_R_RegisterShaderNoMip( ART_BACK1 );
}


/*
===============
UI_TeamOrdersMenu
===============
*/
void UI_TeamOrdersMenu( void )
{
	UI_TeamOrdersMenu_Init();
	UI_PushMenu( &teamOrdersMenuInfo.menu );
}


/*
===============
UI_TeamOrdersMenu_f
===============
*/
void UI_TeamOrdersMenu_f( void )
{
	uiClientState_t	cs;
	char	info[MAX_INFO_STRING];
	int		team;

	// make sure it's a team game
	trap_GetConfigString( CS_SERVERINFO, info, sizeof(info) );
	teamOrdersMenuInfo.gametype = atoi( Info_ValueForKey( info, "g_gametype" ) );
	if(!UI_IsATeamGametype(teamOrdersMenuInfo.gametype)) {
		return;
	}

	// not available to spectators
	trap_GetClientState( &cs );
	trap_GetConfigString( CS_PLAYERS + cs.clientNum, info, MAX_INFO_STRING );
	team = atoi( Info_ValueForKey( info, "t" ) );
	if( team == TEAM_SPECTATOR ) {
		return;
	}

	UI_TeamOrdersMenu();
}