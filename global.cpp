#pragma once
#include <allegro5/allegro.h>
#include <cmath>

bool keys[] = {	false,
				false,
				false,
				false,
				false,
				false,
				false,
				false,
				false,
				false	};

enum game_keys
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	W,
	A,
	S,
	D,
	SPACE,
	ENTER
};

enum game_states
{
	MENU,
	PLAY,
	PAUSE,
	CREDIT
};

enum obj_states
{
	IDLE,
	WALK,
	CHASE,
	RETREAT,
	ATTACK,
	DEFENSE
};

class GameObject
{
	protected:
	float x;
	float y;

	float spawnX;
	float spawnY;

	float sight;
	int size;

	int state;
	bool NPC;

	public:
	ALLEGRO_BITMAP	*texture = nullptr;
//	ALLEGRO_TIMER	*timer = nullptr;
//	ALLEGRO_SAMPLE	*sound = nullptr;

	GameObject(float dWidth, float dHeight, int size, bool NPC, float offsetX = 0.0f, float offsetY = 0.0f, float sight = 0.0f)
	{
		this->x = this->spawnX = (dWidth / 2 - size / 2) + offsetX;
		this->y = this->spawnY = (dHeight / 2 - size / 2) + offsetY;
		this->size = size;

		this->NPC = NPC;
		this->sight = sight;
		this->state = IDLE;
	}

	~GameObject()
	{
		//al_destroy_bitmap(texture);
		//al_destroy_timer(timer);
		//al_destroy_sample(sound);
	}

	void update(GameObject *target)
	{
		if (this->state == IDLE)
		{
			if (this->sight > this->getDistance(target))
				this->setState(CHASE);
		}
		else if (this->state == CHASE)
		{
			if (this->sight < this->getDistance(this->spawnX, this->spawnY))
				this->state = RETREAT;
			else
			{
				this->follow(target);

				if (this->sight < this->getDistance(target))
					this->state = RETREAT;
			}
		}
		else if (this->state == RETREAT)
		{
			if (5 >= this->getDistance(this->spawnX, this->spawnY))
			{
				this->x = this->spawnX;
				this->y = this->spawnY;
				this->state = IDLE;
			}
			else
			{
				this->follow(this->spawnX, this->spawnY);

				if (this->sight > this->getDistance(target))
					this->state = CHASE;
			}
		}
	}

	void render(int r = 255, int g = 0, int b = 0)
	{
		if (this->NPC)
		{
			al_draw_circle(this->spawnX, this->spawnY, this->sight,
							al_map_rgba(255, 255, 255, 128), 1);
			al_draw_circle(this->x, this->y, this->sight,
							al_map_rgba(r, g, b, 128), 1);
			al_draw_filled_rectangle(this->x - 10, this->y - 10,
									this->x + 10, this->y + 10,
									al_map_rgb(r, g, b));
		}
		else
		{
			al_draw_filled_rectangle(this->x - 10, this->y - 10,
									this->x + 10, this->y + 10,
									al_map_rgb(r, g, b));
		}
	}

	void move(int dir)
	{
		switch (dir)
		{
		case UP:
			this->y -= 5.0;
			break;
		case DOWN:
			this->y += 5.0;
			break;
		case LEFT:
			this->x -= 5.0;
			break;
		case RIGHT:
			this->x += 5.0;
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

	float getSightDistance()
	{
		return sight;
	}
	void setSightDistance(float sight)
	{
		this->sight = sight;
	}

	int getSize()
	{
		return size;
	}

	void setSize(int size)
	{
		this->size = size;
	}

	int getState()
	{
		return state;
	}

	void setState(int state)
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
};

/*	bad.bmp = al_create_bitmap(bad.size, bad.size);
	al_set_target_bitmap(bad.bmp);
	al_clear_to_color(al_map_rgb(255, 0, 255));
	al_set_target_bitmap(al_get_backbuffer(display));	*/
