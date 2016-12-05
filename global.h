#pragma once

int	SCREEN_WIDTH = 0, SCREEN_HEIGHT = 0;

bool exitGame = false;

const int MAX_KEYS = 60;

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
