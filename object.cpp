#include <cmath>

#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>

class GameObject
{
	protected:
	float x;
	float y;

	float spawnX;
	float spawnY;

	float speed;
	float sight;
	float radius;

	int sizeW;
	int sizeH;

	int state;
	bool NPC;

	public:
	ALLEGRO_BITMAP	**texture = NULL;
//	ALLEGRO_SAMPLE	**sound = NULL;
//	ALLEGRO_TIMER	*timer = NULL;

	GameObject(int size, bool NPC, float offsetX = 0.0f, float offsetY = 0.0f, float sight = 0.0f)
	{
		this->x = this->spawnX = (SCREEN_WIDTH / 2 - size / 2) + offsetX;
		this->y = this->spawnY = (SCREEN_HEIGHT / 2 - size / 2) + offsetY;
		this->sizeH = size;
		this->sizeW = size;

		this->NPC = NPC;
		this->state = IDLE;

		this->sight = sight;

		this->speed = 5.0;
		this->radius = size / 2;
	}

	~GameObject()	
	{
		//al_destroy_bitmap(texture);
		//al_destroy_timer(timer);
		//al_destroy_sample(sound);
	}

	void input(int &keycode, bool keyFlag)
	{
		switch (keycode)
		{
			case ALLEGRO_KEY_UP:
				keys[UP] = keyFlag;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = keyFlag;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = keyFlag;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = keyFlag;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = keyFlag;
				break;
			case ALLEGRO_KEY_ENTER:
				keys[ENTER] = keyFlag;
				break;
			case ALLEGRO_KEY_ALT:
				keys[ALT] = keyFlag;
				break;
			case ALLEGRO_KEY_ALTGR:
				keys[ALTGR] = keyFlag;
				break;
			case ALLEGRO_KEY_ESCAPE:
				keys[ESCAPE] = keyFlag;
				break;
			case ALLEGRO_KEY_BACKSPACE:
				keys[BACKSPACE] = keyFlag;
				break;
			case ALLEGRO_KEY_LSHIFT:
				keys[LSHIFT] = keyFlag;
				break;
			case ALLEGRO_KEY_RSHIFT:
				keys[RSHIFT] = keyFlag;
				break;
			case ALLEGRO_KEY_LCTRL:
				keys[LCTRL] = keyFlag;
				break;
			case ALLEGRO_KEY_RCTRL:
				keys[RCTRL] = keyFlag;
				break;
			case ALLEGRO_KEY_TAB:
				keys[TAB] = keyFlag;
				break;
			case ALLEGRO_KEY_DELETE:
				keys[DEL] = keyFlag;
				break;
			case ALLEGRO_KEY_HOME:
				keys[HOME] = keyFlag;
				break;
			case ALLEGRO_KEY_END:
				keys[END] = keyFlag;
				break;
			case ALLEGRO_KEY_PGUP:
				keys[PGUP] = keyFlag;
				break;
			case ALLEGRO_KEY_PGDN:
				keys[PGDN] = keyFlag;
				break;
			case ALLEGRO_KEY_A:
				keys[A] = keyFlag;
				break;
			case ALLEGRO_KEY_B:
				keys[B] = keyFlag;
				break;
			case ALLEGRO_KEY_C:
				keys[C] = keyFlag;
				break;
			case ALLEGRO_KEY_D:
				keys[D] = keyFlag;
				break;
			case ALLEGRO_KEY_E:
				keys[E] = keyFlag;
				break;
			case ALLEGRO_KEY_F:
				keys[F] = keyFlag;
				break;
			case ALLEGRO_KEY_G:
				keys[G] = keyFlag;
				break;
			case ALLEGRO_KEY_H:
				keys[H] = keyFlag;
				break;
			case ALLEGRO_KEY_I:
				keys[I] = keyFlag;
				break;
			case ALLEGRO_KEY_J:
				keys[J] = keyFlag;
				break;
			case ALLEGRO_KEY_K:
				keys[K] = keyFlag;
				break;
			case ALLEGRO_KEY_L:
				keys[L] = keyFlag;
				break;
			case ALLEGRO_KEY_M:
				keys[M] = keyFlag;
				break;
			case ALLEGRO_KEY_N:
				keys[N] = keyFlag;
				break;
			case ALLEGRO_KEY_O:
				keys[O] = keyFlag;
				break;
			case ALLEGRO_KEY_P:
				keys[P] = keyFlag;
				break;
			case ALLEGRO_KEY_Q:
				keys[Q] = keyFlag;
				break;
			case ALLEGRO_KEY_R:
				keys[R] = keyFlag;
				break;
			case ALLEGRO_KEY_S:
				keys[S] = keyFlag;
				break;
			case ALLEGRO_KEY_T:
				keys[T] = keyFlag;
				break;
			case ALLEGRO_KEY_U:
				keys[U] = keyFlag;
				break;
			case ALLEGRO_KEY_V:
				keys[V] = keyFlag;
				break;
			case ALLEGRO_KEY_W:
				keys[W] = keyFlag;
				break;
			case ALLEGRO_KEY_X:
				keys[X] = keyFlag;
				break;
			case ALLEGRO_KEY_Y:
				keys[Y] = keyFlag;
				break;
			case ALLEGRO_KEY_Z:
				keys[Z] = keyFlag;
				break;
			case ALLEGRO_KEY_PAD_0:
				keys[PAD_0] = keyFlag;
				break;
			case ALLEGRO_KEY_PAD_1:
				keys[PAD_1] = keyFlag;
				break;
			case ALLEGRO_KEY_PAD_2:
				keys[PAD_2] = keyFlag;
				break;
			case ALLEGRO_KEY_PAD_3:
				keys[PAD_3] = keyFlag;
				break;
			case ALLEGRO_KEY_PAD_4:
				keys[PAD_4] = keyFlag;
				break;
			case ALLEGRO_KEY_PAD_5:
				keys[PAD_5] = keyFlag;
				break;
			case ALLEGRO_KEY_PAD_6:
				keys[PAD_6] = keyFlag;
				break;
			case ALLEGRO_KEY_PAD_7:
				keys[PAD_7] = keyFlag;
				break;
			case ALLEGRO_KEY_PAD_8:
				keys[PAD_8] = keyFlag;
				break;
			case ALLEGRO_KEY_PAD_9:
				keys[PAD_9] = keyFlag;
				break;
			case ALLEGRO_KEY_PAD_ENTER:
				keys[PAD_ENTER] = keyFlag;
				break;
			case ALLEGRO_KEY_PAD_DELETE:
				keys[PAD_DEL] = keyFlag;
				break;
			case ALLEGRO_KEY_PAD_PLUS:
				keys[PAD_PLUS] = keyFlag;
				break;
			case ALLEGRO_KEY_PAD_MINUS:
				keys[PAD_MINUS] = keyFlag;
				break;
		}			
	}

	void update(GameObject *target = NULL)
	{
		if (this->NPC)
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
		else
		{
			if (keys[UP] && this->y >= 5.0)
				this->move(UP);
			if (keys[DOWN] && this->y <= SCREEN_HEIGHT - this->sizeH - 5.0)
				this->move(DOWN);
			if (keys[LEFT] && this->x >= 5.0)
				this->move(LEFT);
			if (keys[RIGHT] && this->x <= SCREEN_WIDTH - this->sizeW - 5.0)
				this->move(RIGHT);
			if (keys[ESCAPE])
				exitGame = true;

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

	float getRadius()
	{
		return radius;
	}

	void setRadius(float radius)
	{
		this->radius = radius;
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

	bool getCollisionDB(GameObject *obj)	//Distance Based Collision
	{
		if (sqrt(pow(this->x - obj->x, 2) + pow(this->y - obj->y, 2)) < this->radius + obj->radius)
			return true;

		return false;
	}

	bool getCollisionBB(GameObject *obj)	//Bounding Box Collision
	{
		if ((this->x > obj->x + obj->sizeW)	||
			(this->y > obj->y + obj->sizeH)	||
			(obj->x > this->x + this->sizeW)||
			(obj->y > this->y + this->sizeH))
			return false;

		return true;
	}

	bool getCollisionPP(ALLEGRO_BITMAP *texture, ALLEGRO_BITMAP *objTexture, GameObject *obj)	//Pixel Perfect Collision
	{
		int ppBoxTop, ppBoxBottom,
			ppBoxLeft, ppBoxRight;

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
