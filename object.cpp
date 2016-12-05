#include <cmath>

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
	float x;
	float y;

	float spawnX;
	float spawnY;

	float speed;
	float sight;
	float radius;

	int sizeW;
	int sizeH;

	obj_state state;
	obj_type type;

	ALLEGRO_BITMAP	*texture = NULL;
//	ALLEGRO_SAMPLE	*sound = NULL;
//	ALLEGRO_TIMER	*timer = NULL;

	GameObject(obj_state state, obj_type type,
				int size,
				float offsetX = 0.0f, float offsetY = 0.0f,
				float sight = 0.0f, float speed = 2.5f)
	{
		this->x = this->spawnX = (SCREEN_WIDTH / 2 - size / 2) + offsetX;
		this->y = this->spawnY = (SCREEN_HEIGHT / 2 - size / 2) + offsetY;
		this->sizeH = size;
		this->sizeW = size;

		this->state = state;
		this->type = type;

		this->sight = sight;
		this->speed = speed;

		this->radius = size / 2;
	}

	~GameObject()	
	{
		//al_destroy_bitmap(texture);
		//al_destroy_timer(timer);
		//al_destroy_sample(sound);
	}

	virtual void input()	{}
	virtual void update(GameObject *target = NULL, GameObject *obj = NULL)	{}
	virtual void render(int r = 0, int g = 0, int b = 0)	{}

	ALLEGRO_BITMAP* loadBitmap(const char *path)
	{
		return al_load_bitmap(path);
	}

	void setTexture(const char *path)
	{
		texture = loadBitmap(path);
	}

	ALLEGRO_BITMAP*	getTexture()
	{
		return texture;
	}

	void move(int dir)
	{
		switch (dir)
		{
			case UP:
				this->y -= this->speed;
				break;
			case DOWN:
				this->y += this->speed;
				break;
			case LEFT:
				this->x -= this->speed;
				break;
			case RIGHT:
				this->x += this->speed;
				break;
		};
	}

	void follow(GameObject *obj)
	{
		float angle = this->getAngle(obj);
		this->x += (2 * cos(angle));
		this->y += (2 * sin(angle));
	}

	void follow(float x, float y)
	{
		float angle = this->getAngle(x, y);
		this->x += (2 * cos(angle));
		this->y += (2 * sin(angle));
	}

	float getX()
	{
		return x;
	}
	void setX(float x)	
	{
		this->x = x;
	}

	float getY()
	{
		return y;
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
		return spawnX;
	}
	void setSpawnX(float spawnX)
	{
		this->spawnX = spawnX;
	}

	float getSpawnY()
	{
		return spawnY;
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
		return sight;
	}
	void setSightDistance(float sight)
	{
		this->sight = sight;
	}

	int getWidthSize()
	{
		return sizeW;
	}

	void setWidthSize(int sizeW)
	{
		this->sizeW = sizeW;
	}

	int getHeightSize()
	{
		return sizeW;
	}

	void setHeightSize(int sizeH)
	{
		this->sizeH = sizeH;
	}

	float getSpeed()
	{
		return speed;
	}

	void setSpeed(float speed)
	{
		this->speed = speed;
	}

	float getRadius()
	{
		return radius;
	}

	void setRadius(float radius)
	{
		this->radius = radius;
	}

	obj_state getState()
	{
		return state;
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
