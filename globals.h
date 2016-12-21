#pragma once
#include <allegro5/allegro.h>

#define DISPLAY	al_get_current_display()

const float PI = ALLEGRO_PI;
const float H_PI = ALLEGRO_PI/2.;
const float OS_PI = ALLEGRO_PI/8.;

bool exitGame = false;

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
