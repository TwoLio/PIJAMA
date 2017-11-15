#pragma once

#include <iostream>

#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_opengl.h>

//#include <glm/vec3.hpp> // glm::vec3
//#include <glm/vec4.hpp> // glm::vec4
//#include <glm/mat4x4.hpp> // glm::mat4
//#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

#define DISPLAY	al_get_current_display()

const float PI = ALLEGRO_PI;
const float H_PI = ALLEGRO_PI/2.;
const float OS_PI = ALLEGRO_PI/8.;		//	Offset

enum game_state
{
	MENU,
	PLAY,
	PAUSE,
	CREDIT
};

enum load_state
{
	NAME,
	SIZE,
	MAP
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
