#include "object.cpp"

class EnemyBot : public GameObject
{
	public:
	EnemyBot(obj_state state = IDLE, obj_type type = ENEMY,
			int size = 20,
			float offsetX = 250.0f, float offsetY = 0.0f,
			float sight = 200.0f, float speed = 2.5f)	:
	GameObject(state, type, size, offsetX, offsetY, sight, speed)	{}

	void render(int r = 255, int g = 0, int b = 0)
	{
		al_draw_circle(this->spawnX, this->spawnY, this->sight,
						al_map_rgba(255, 255, 255, 128), 1);
		al_draw_circle(this->x, this->y, this->sight,
						al_map_rgba(r, g, b, 128), 1);
		al_draw_filled_rectangle(this->x - 10, this->y - 10,
								this->x + 10, this->y + 10,
								al_map_rgb(r, g, b));
	}

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

	void input()	{}
};

class Bot : public GameObject
{
	public:
	Bot(obj_state state = IDLE, obj_type type = FRIEND,
		int size = 20,
		float offsetX = -250.0f, float offsetY = 20.0f,
		float sight = 200.0f, float speed = 2.5f)	:
	GameObject(state, type, size, offsetX, offsetY, sight, speed)	{}

	void render(int r = 0, int g = 255, int b = 0)
	{
		al_draw_circle(this->spawnX, this->spawnY, this->sight,
						al_map_rgba(255, 255, 255, 128), 1);
		al_draw_circle(this->x, this->y, this->sight,
						al_map_rgba(r, g, b, 128), 1);
		al_draw_filled_rectangle(this->x - 10, this->y - 10,
								this->x + 10, this->y + 10,
								al_map_rgb(r, g, b));
	}

	void update(GameObject *target = NULL, GameObject *obj = NULL)
	{
		if (this->state == IDLE)
		{
			if (this->sight > this->getDistance(target))
				this->state = ATTACK;
			else if (this->sight > this->getDistance(obj))
				this->state = DEFEND;
		}
		else if (this->state == ATTACK)
		{
			if (this->sight < this->getDistance(obj->x, obj->y))
				this->state = DEFEND;
			else
			{
				this->follow(target);

				if (this->sight < this->getDistance(target))
					this->state = DEFEND;
			}
		}
		else if (this->state == DEFEND)
		{
			if (30 >= this->getDistance(obj->x, obj->y))
			{
				this->state = IDLE;
			}
			else
			{
				this->follow(obj->x, obj->y);

				if (this->sight > this->getDistance(target))
					this->state = ATTACK;
			}
		}
	}

	void input()	{}
};

class Player : public GameObject
{
	public:
	Player(obj_state state = WALK, obj_type type = PLAYER,
			int size = 20,
			float offsetX = -250.0f, float offsetY = -20.0f,
			float sight = 0.0f, float speed = 2.5f)	:
	GameObject(state, type, size, offsetX, offsetY, sight, speed)	{}

	void render(int r = 0, int g = 0, int b = 255)
	{
		al_draw_filled_rectangle(this->x - 10, this->y - 10,
								this->x + 10, this->y + 10,
								al_map_rgb(r, g, b));
	}

	void update()
	{
		if (keys[UP] && this->y >= 5.0)
			this->move(UP);
		if (keys[DOWN] && this->y <= SCREEN_HEIGHT - this->sizeH - 5.0)
			this->move(DOWN);
		if (keys[LEFT] && this->x >= 5.0)
			this->move(LEFT);
		if (keys[RIGHT] && this->x <= SCREEN_WIDTH - this->sizeW - 5.0)
			this->move(RIGHT);
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
};
