#pragma once

#include <All2D/All2DEngine/All2D/includes/gameMessages.h>

#define COLUMNS_APP_TITLE							0x0001
#define COLUMNS_APP_GAME							0x0002
#define COLUMNS_APP_HIGH_SCORE						0x0003
#define COLUMNS_APP_BOSS							0x0004
#define COLUMNS_NO_LAYER							0x0000
#define COLUMNS_LAYER_CONFIG						0x0005
#define COLUMNS_LAYER_HIGH_SCORE					0x0006
#define COLUMNS_LAYER_INSTRUCTIONS					0x0007
#define COLUMNS_LAYER_CREDITS						0x0008
#define COLUMNS_LAYER_MENU							0x0009
#define COLUMNS_LAYER_MSGBOX						0x000A
#define COLUMNS_END									0x0666

#define COLUMNS_JOKER							0x0007


#define COLUMNS_STONE_MOVE				0x0010
#define COLUMNS_REMOVE_STONE			0x0020
#define COLUMNS_REMOVE_JOKER			0x0030
#define COLUMNS_REMOVE_GAP				0x0040
#define COLUMNS_GAME_PAUSE				0x0050
#define COLUMNS_GAME_OVER				0x0060
#define COLUMNS_GAME_OUT				0x0070

// Time between explosion and removing stones in Millisec
#define COLUMNS_REACTIONTIME	500

// GAME MESSAGES SENDET VIA MESSAGE-MANAGER


// CONFIGS
#define MM_FULLSCREEN						0x1001
#define MM_SNOW								0x1002
#define MM_PREVIEW							0x1003
#define MM_JOKER							0x1004
// IN-GAME KEYS
#define MM_DROP								MM_FIRE
// NAVIGATION ELEMENTS
#define MM_HELP								0x1201
#define MM_START_REQUEST					0x1202
#define MM_START							0x1203
#define MM_HIGHSCORE						0x1204
#define MM_CONFIG							0x1205
#define MM_CREDITS							0x1206
#define MM_QUIT								0x1207

#define COLUMNS_NAVIGATION_HOVER			0x0001

#define MM_NAME_READY						0x1301
