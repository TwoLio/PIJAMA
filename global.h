#pragma once
#include <allegro5/allegro.h>

const float PI = ALLEGRO_PI;
const float H_PI = ALLEGRO_PI/2.;
const float OS_PI = ALLEGRO_PI/8.;

const int MAX_KEYS = 60;
const int OBJ_TEXTURES = 2;
const int DSP_FONTS = 2;

int	SCREEN_WIDTH = 0, SCREEN_HEIGHT = 0;

bool exitGame = false;

bool keys[MAX_KEYS] = {	false, false, false, false, false,
						false, false, false, false, false,
						false, false, false, false, false,
						false, false, false, false, false,
						false, false, false, false,	false,
						false, false, false, false, false,
						false, false, false, false, false,
						false, false, false, false, false,
						false, false, false, false,	false,
						false, false, false, false, false,
						false, false, false, false,	false,
						false, false, false, false, false	};

enum game_keys
{
	UP, DOWN,
	LEFT, RIGHT,
	SPACE, ENTER,
	ALT, ALTGR,
	ESCAPE,	BACKSPACE,
	LSHIFT, RSHIFT,
	LCTRL, RCTRL,
	TAB, DEL,
	HOME, END,
	PGUP, PGDN,
	
	A, B, C, D, E, F, G, H, I, J, K, L, M,
	N, O, P, Q, R, S, T, U,	V, W, X, Y, Z, 

	PAD_0, PAD_1,
	PAD_2, PAD_3,
	PAD_4, PAD_5,
	PAD_6, PAD_7,
	PAD_8, PAD_9,
	PAD_ENTER, PAD_DEL,
	PAD_PLUS, PAD_MINUS
};

enum game_states
{
	MENU,
	PLAY,
	PAUSE,
	CREDIT
};

enum obj_type
{
	PLAYER,
	FRIEND,
	ENEMY,
	ITEM,
	BULLET,
	WORLD_OBJ
};

enum obj_state
{
	IDLE,
	WALK,
	CHASE,
	RETREAT,
	ATTACK,
	DEFEND
};

enum obj_dir
{
	SOUTH,
	WEST,
	EAST,
	NORTH,
	SOUTH_WEST,
	NORTH_WEST,
	SOUTH_EAST,
	NORTH_EAST
};

enum anim_state
{
	ROW_COL,
	CROSS,
	ANIM_1,
	ANIM_2,
	ANIM_3
	
};
