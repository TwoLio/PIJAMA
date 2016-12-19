#include <cmath>
#include <iostream>
#include <sstream>

#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_opengl.h>
#include <allegro5/allegro_native_dialog.h>

//#include <glm/vec3.hpp> // glm::vec3
//#include <glm/vec4.hpp> // glm::vec4
//#include <glm/mat4x4.hpp> // glm::mat4
//#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

#include "global.h"

class GameObject
{
	public:
	float			health;
	float			speed;
	float			sight;

	obj_state		state;
	obj_type		type;
	obj_dir			direction;
	anim_state		animation;

	float			radius;
	int				sizeW;
	int				sizeH;

	float			x;
	float			y;

	float			spawnX;
	float			spawnY;

	ALLEGRO_BITMAP	*texture[OBJ_TEXTURES];
	ALLEGRO_FONT	*font;
//	ALLEGRO_SAMPLE	*sound;
//	ALLEGRO_TIMER	*timer;

	float			textSourceX;		//Variables for sprite sheet animation
	float			textSourceY;
	int				rowFrame;
	int				colFrame;

	GameObject(float health, ALLEGRO_FONT *font,
				obj_state state, obj_type type,
				float sight = 0.0f, float speed = 1.f,
				int size = 32,
				float offsetX = 0.0f, float offsetY = 0.0f)
	{
		this->health = health;
		this->font = font;

		this->state = state;
		this->type = type;
		this->direction = SOUTH;
		this->animation = ROW_COL;

		this->sight = sight;
		this->speed = speed;

		this->radius = size / 2;
		this->sizeH = size;
		this->sizeW = size;

		this->x = this->spawnX = (SCREEN_WIDTH/2 - this->sizeW/2) + offsetX;
		this->y = this->spawnY = (SCREEN_HEIGHT/2 - this->sizeH/2) + offsetY;

		this->setTexture("gfx/sheet/");
		this->textSourceX = size;
		this->textSourceY = 0;
		this->rowFrame = 3;
		this->colFrame = 4;
	}

	~GameObject()	
	{
		for (int i = 0; i < OBJ_TEXTURES; i++)
			al_destroy_bitmap(texture[i]);
		//al_destroy_timer(timer);
		//al_destroy_sample(sound);
	}

	virtual void input()	{}
	virtual void update(GameObject *target = NULL, GameObject *obj = NULL)	{}
	virtual void render(int r = 0, int g = 0, int b = 0)	{}
	virtual void move()	{}

	ALLEGRO_BITMAP* loadBitmap(const char *path)
	{
		return al_load_bitmap(path);
	}

	void setTexture(const char *path)
	{
		for (int i = 0; i < OBJ_TEXTURES; i++)
		{
			std::stringstream str;
			str << path << "sprite" << i << ".png";
			this->texture[i] = loadBitmap(str.str().c_str());
		}
	}

	ALLEGRO_BITMAP*	getTexture(int i)
	{
		return this->texture[i];
	}

	float getTextureWidth(int i)
	{
		return al_get_bitmap_width(this->texture[i]);
	}

	float getTextureHeight(int i)
	{
		return al_get_bitmap_height(this->texture[i]);
	}

	void updateAnimation()
	{
		if (this->state == WALK || this->state == CHASE || this->state == DEFEND)
			this->textSourceX += this->sizeW;
		else if (this->state == IDLE)
			this->textSourceX = this->sizeW;

		if (this->textSourceX >= 3 * this->sizeW)
			this->textSourceX = 0;

		this->textSourceY = (this->direction - 4*this->animation) * this->sizeH;
	}

	void follow(GameObject *obj)
	{
		float angle = this->getAngle(obj);
		this->setDirection(angle);
		this->x += this->speed * cos(angle);
		this->y += this->speed * sin(angle);
	}

	void follow(float x, float y)
	{
		float angle = this->getAngle(x, y);
		this->setDirection(angle);
		this->x += this->speed * cos(angle);
		this->y += this->speed * sin(angle);
	}

	void setDirection(float angle)
	{
		if (abs(angle) >= PI - OS_PI && abs(angle) <= PI)
		{
			this->direction = WEST;
			this->animation = ROW_COL;
		}
		else if (angle > H_PI + OS_PI && angle < PI - OS_PI)
		{
			this->direction = SOUTH_WEST;
			this->animation = CROSS;
		}
		else if (angle >= H_PI - OS_PI && angle <= H_PI + OS_PI)
		{
			this->direction = SOUTH;
			this->animation = ROW_COL;
		}
		else if (angle > OS_PI && angle < H_PI - OS_PI)
		{
			this->direction = SOUTH_EAST;
			this->animation = CROSS;
		}
		else if (angle >= -OS_PI && angle <= OS_PI)
		{
			this->direction = EAST;
			this->animation = ROW_COL;
		}
		else if (angle > -H_PI + OS_PI && angle < -OS_PI)
		{
			this->direction = NORTH_EAST;
			this->animation = CROSS;
		}
		else if (angle >= -H_PI - OS_PI && angle <= -H_PI + OS_PI)
		{
			this->direction = NORTH;
			this->animation = ROW_COL;
		}
		else if (angle > -PI + OS_PI && angle < -H_PI - OS_PI)
		{
			this->direction = NORTH_WEST;
			this->animation = CROSS;
		}
	}

	float getAngle(float x, float y)
	{
		float dx = x - this->x;
		float dy = y - this->y;
		return atan2(dy, dx);
	}

	float getAngle(GameObject *obj)
	{
		float dx = obj->x - this->x;
		float dy = obj->y - this->y;
		return atan2(dy, dx);
	}

	float getX()
	{
		return this->x;
	}
	void setX(float x)	
	{
		this->x = x;
	}

	float getY()
	{
		return this->y;
	}
	void setY(float y)
	{
		this->y = y;
	}

	void setPos(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	float getSpawnX()
	{
		return this->spawnX;
	}
	void setSpawnX(float spawnX)
	{
		this->spawnX = spawnX;
	}

	float getSpawnY()
	{
		return this->spawnY;
	}
	void setSpawnY(float spawnY)
	{
		this->spawnY = spawnY;
	}

	void setSpawn(float spawnX, float spawnY)
	{
		this->spawnX = spawnX;
		this->spawnY = spawnY;
	}

	float getSightDistance()
	{
		return this->sight;
	}
	void setSightDistance(float sight)
	{
		this->sight = sight;
	}

	int getWidthSize()
	{
		return this->sizeW;
	}

	void setWidthSize(int sizeW)
	{
		this->sizeW = sizeW;
	}

	int getHeightSize()
	{
		return this->sizeW;
	}

	void setHeightSize(int sizeH)
	{
		this->sizeH = sizeH;
	}

	float getSpeed()
	{
		return this->speed;
	}

	void setSpeed(float speed)
	{
		this->speed = speed;
	}

	float getRadius()
	{
		return this->radius;
	}

	void setRadius(float radius)
	{
		this->radius = radius;
	}

	obj_state getState()
	{
		return this->state;
	}

	void setState(obj_state state)
	{
		this->state = state;
	}

	float getDistance(float x, float y)
	{
		return sqrt(pow(x - this->x, 2) + pow(y - this->y, 2));
	}

	float getDistance(GameObject *obj)
	{
		return sqrt(pow(obj->x - this->x, 2) + pow(obj->y - this->y, 2));
	}

	bool getCollisionDB(GameObject *obj)	//Distance Based Collision
	{
		if (sqrt(pow(this->x - obj->x, 2) + pow(this->y - obj->y, 2)) < this->radius + obj->radius)
			return true;

		return false;
	}

	bool getCollisionBB(GameObject *obj)	//Bounding Box Collision
	{
		if ((this->x > obj->x + obj->sizeW) || (this->y > obj->y + obj->sizeH) ||
			(obj->x > this->x + this->sizeW) || (obj->y > this->y + this->sizeH))
			return false;

		return true;
	}

	bool getCollisionPP(ALLEGRO_BITMAP *texture, ALLEGRO_BITMAP *objTexture, GameObject *obj)	//Pixel Perfect Collision
	{
		int ppBoxTop, ppBoxBottom, ppBoxLeft, ppBoxRight;

		if (!getCollisionBB(obj))
			return false;
		else
		{
			ppBoxTop = std::max(this->y, obj->y);
			ppBoxBottom = std::min(this->y + this->sizeH, obj->y + obj->sizeH);
			ppBoxLeft = std::max(this->x, obj->x);
			ppBoxRight = std::min(this->x + this->sizeW, obj->x + obj->sizeW);
		}

		for (int i = ppBoxTop; i < ppBoxBottom; i++)
		{
			for (int j = ppBoxLeft; j < ppBoxRight; j++)
			{
				al_lock_bitmap(texture, al_get_bitmap_format(texture), ALLEGRO_LOCK_READONLY);
				al_lock_bitmap(objTexture, al_get_bitmap_format(objTexture), ALLEGRO_LOCK_READONLY);
				ALLEGRO_COLOR color1 = al_get_pixel(texture, j - this->x, i - this->y);
				ALLEGRO_COLOR color2 = al_get_pixel(objTexture, j - obj->x, i - obj->y);

				if (color1.a != 0 && color2.a != 0)
					return true;
			}
		}
		return false;
	}
};
