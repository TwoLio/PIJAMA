#include "object.cpp"
#include "input.h"

/*	TODO
	~ Migliorare IA dei bot friendly;
	~ Aggiornare logica della zona di visione dei bot enemy:
		facendola rimanere sempre intorno al bot (e non allo spawn) e ridurla;
	~ Improve AI for friendly bot;
	~ Update enemy sight logic:
		switching from being fixed to spawnpoint, to following the enemy bot;
 */

class EnemyBot : public GameObject
{
	public:
	EnemyBot(float x, float y, float health,
			obj_state state = IDLE, obj_type type = ENEMY,
			obj_dir direction = NORTH, int size = 32,
			float sight = 100.0f, float speed = 1.f)	:
	GameObject(x, y, health, state, type, direction, size, sight, speed)	{}

	void update(GameObject *target = NULL, GameObject *obj = NULL)
	{
		if (this->state == IDLE)
		{
			if (this->sight > this->getDistance(target))
				this->state = CHASE;
		}
		else if (this->state == CHASE)
		{
			if (this->sight < this->getDistance(this->spawnX, this->spawnY))
				this->state = WALK;
			else
			{
				this->follow(target);

				if (this->sight < this->getDistance(target))
					this->state = WALK;
			}
		}
		else if (this->state == WALK)
		{
			if (4 >= this->getDistance(this->spawnX, this->spawnY))
			{
				this->follow(this->spawnX, this->spawnY);
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
		al_draw_circle(this->spawnX, this->spawnY, this->sight,
					al_map_rgba(255, 255, 255, 128), 1);
		al_draw_circle(this->x, this->y, this->sight,
					al_map_rgba(r, g, b, 128), 1);
		al_draw_bitmap_region(this->texture[this->animation],
							this->textSourceX, this->textSourceY,
							this->sizeW, this->sizeH,
							this->x - this->sizeW/2, this->y - this->sizeH/2, 0);
		al_draw_textf(this->font, al_map_rgb(r, g, b),
					this->x - this->sizeW/2, this->y - this->sizeH/2,
					ALLEGRO_ALIGN_RIGHT, "%i", (int)this->health);
	}

	void input()	{}
	void move()		{}
};

class Bot : public GameObject
{
	public:
	Bot(float x, float y, float health,
		obj_state state = IDLE, obj_type type = FRIEND,
		obj_dir direction = NORTH, int size = 32,
		float sight = 100.0f, float speed = 1.f)	:
	GameObject(x, y, health, state, type, direction, size, sight, speed)	{}

	void update(GameObject *target = NULL, GameObject *obj = NULL)
	{
		if (this->state == IDLE)
		{
			if (this->sight > this->getDistance(obj))
				this->state = WALK;
		}
		else if (this->state == ATTACK)
		{
			if (this->sight < this->getDistance(obj->x, obj->y))
				this->state = WALK;
			else
			{
				this->follow(target);

				if (this->sight < this->getDistance(target))
					this->state = WALK;
			}
		}
		else if (this->state == WALK)
		{	
			if (64 >= this->getDistance(obj->x, obj->y))
			{
				this->state = IDLE;
			}
			else
			{
				this->follow(obj);

				if (this->sight > this->getDistance(target))
					this->state = ATTACK;
			}
		}
	}

	void render(int r = 0, int g = 255, int b = 0)
	{
		al_draw_circle(this->spawnX, this->spawnY, this->sight,
					al_map_rgba(255, 255, 255, 128), 1);
		al_draw_circle(this->x, this->y, this->sight,
					al_map_rgba(r, g, b, 128), 1);
		al_draw_bitmap_region(this->texture[this->animation],
							this->textSourceX, this->textSourceY,
							this->sizeW, this->sizeH,
							this->x - this->sizeW/2, this->y - this->sizeH/2, 0);
		al_draw_textf(this->font, al_map_rgb(r, g, b),
					this->x - this->sizeW/2, this->y - this->sizeH/2,
					ALLEGRO_ALIGN_RIGHT, "%i", (int)this->health);
	}

	void input()	{}
	void move()		{}
};

class Player : public GameObject
{
	protected:
	GameInput	*gameInput;

	public:
	Player(GameInput *gameInput,
			float x, float y, float health,
			obj_state state = WALK, obj_type type = PLAYER,
			obj_dir direction = SOUTH, int size = 32,
			float sight = 200.0f, float speed = 1.f)	:
	GameObject(x, y, health, state, type, direction, size, sight, speed)
	{
		this->gameInput = gameInput;
	}

	GameInput* getGameInput()
	{
		return this->gameInput;
	}

	void move()	{}

	void input(int keyCode, bool keyFlag)
	{
		this->gameInput->setKey(keyCode, keyFlag);
		this->gameInput->updateKeyboard();
		this->gameInput->updateMouse();
	}

	void render(int r = 0, int g = 0, int b = 255)
	{
		al_draw_bitmap_region(this->texture[this->animation],
							this->textSourceX, this->textSourceY,
							this->sizeW, this->sizeH,
							this->x - this->sizeW/2, this->y - this->sizeH/2, 0);
		al_draw_textf(this->font, al_map_rgb(r, g, b),
					this->x - this->sizeW/2, this->y - this->sizeH/2,
					ALLEGRO_ALIGN_RIGHT, "%i", (int)this->health);
	}

	void update(GameObject *obj)
	{
		this->state = WALK;

		if (this->gameInput->getKey(ALLEGRO_KEY_UP) && this->gameInput->getKey(ALLEGRO_KEY_LEFT))
			this->follow(this->x - this->speed, this->y - this->speed, obj);
		else if (this->gameInput->getKey(ALLEGRO_KEY_UP) && this->gameInput->getKey(ALLEGRO_KEY_RIGHT))
			this->follow(this->x + this->speed, this->y - this->speed, obj);
		else if (this->gameInput->getKey(ALLEGRO_KEY_DOWN) && this->gameInput->getKey(ALLEGRO_KEY_LEFT))
			this->follow(this->x - this->speed, this->y + this->speed, obj);
		else if (this->gameInput->getKey(ALLEGRO_KEY_DOWN) && this->gameInput->getKey(ALLEGRO_KEY_RIGHT))
			this->follow(this->x + this->speed, this->y + this->speed, obj);
		else if (this->gameInput->getKey(ALLEGRO_KEY_UP))
			this->follow(this->x, this->y - this->speed, obj);
		else if (this->gameInput->getKey(ALLEGRO_KEY_DOWN))
			this->follow(this->x, this->y + this->speed, obj);
		else if (this->gameInput->getKey(ALLEGRO_KEY_LEFT))
			this->follow(this->x - this->speed, this->y, obj);
		else if (this->gameInput->getKey(ALLEGRO_KEY_RIGHT))
			this->follow(this->x + this->speed, this->y, obj);
		else
			this->state = IDLE;
	}
};