#include <cmath>
#include <sstream>

#include "globals.h"

//	TODO	Migliorare movimenti e direzioni

class GameObject
{
	protected:
	static const int OBJ_TEXTURES = 2;

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

	float			textSourceX;		//Variables for spritesheet animation
	float			textSourceY;
	int				rowFrame;
	int				columnFrame;

	GameObject(float x, float y, float health,
				obj_state state, obj_type type,
				obj_dir direction, int size = 32,
				float sight = 0.0f, float speed = 1.f)
	{
		this->health = health;
		this->font = NULL;

		this->state = state;
		this->type = type;
		this->direction = direction;
		this->animation = ROW_COL;

		this->sight = sight;
		this->speed = speed;

		this->radius = size/2.;
		this->sizeH = this->sizeW = size;

		this->x = this->spawnX = x;
		this->y = this->spawnY = y;

		this->setTexture("gfx/sheet/");
		this->textSourceX = size;
		this->textSourceY = 0;
		this->rowFrame = 3;
		this->columnFrame = 4;
	}

	~GameObject()	
	{
		for (int i = 0; i < OBJ_TEXTURES; i++)
			al_destroy_bitmap(texture[i]);
		//al_destroy_timer(timer);
		//al_destroy_sample(sound);
	}

	virtual void input()	{}
	virtual void update()	{}
	virtual void render()	{}
	virtual void move()		{}

	ALLEGRO_BITMAP* loadBitmap(const char *path)
	{
		return al_load_bitmap(path);
	}

	void setTexture(const char *folder)
	{
		for (int i = 0; i < OBJ_TEXTURES; i++)
		{
			std::stringstream path;
			path << folder << "sprite" << i << ".png";
			this->texture[i] = loadBitmap(path.str().c_str());
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
		if (this->state == CHASE || this->state == WALK)
			this->textSourceX += this->sizeW;
		else if (this->state == IDLE)
			this->textSourceX = this->sizeW;

		if (this->textSourceX >= 3 * this->sizeW)
			this->textSourceX = 0;

		this->textSourceY = (this->direction - 4*this->animation) * this->sizeH;
	}

	void follow(float x, float y)
	{
		float angle = this->getAngle(x, y);
		this->setDirection(angle);
		this->x += this->speed * cos(angle);
		this->y += this->speed * sin(angle);
	}

	void follow(GameObject *obj)
	{
		float angle = this->getAngle(obj);
		this->setDirection(angle);

		float dir;
		if (this->getCollisionBB(obj))
			dir = -5.*(this->speed);
		else
			dir = this->speed;

		this->x += dir * cos(angle);
		this->y += dir * sin(angle);
	}

	void follow(float x, float y, GameObject *obj)
	{
		float dirAngle = this->getAngle(x, y);

		if (this->getDistance(obj) < this->sight)
		{
			float objAngle = this->getAngle(obj);
			this->setDirection(objAngle);
		}
		else
			this->setDirection(dirAngle);

		float dir;
		if (this->getCollisionBB(obj))
			dir = -5.*(this->speed);
		else
			dir = this->speed;

		this->x += dir * cos(dirAngle);
		this->y += dir * sin(dirAngle);
	}

	void follow(GameObject *obj, GameObject *target)
	{
		float objAngle = this->getAngle(obj);
		float tarAngle = this->getAngle(target);
		this->setDirection(tarAngle);

		float dir;
		if (this->getCollisionBB(obj) || this->getCollisionBB(target))
			dir = -5.*(this->speed);
		else
			dir = this->speed;

		this->x += dir * cos(objAngle);
		this->y += dir * sin(objAngle);
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

	ALLEGRO_FONT* getFont()
	{
		return this->font;
	}
	void setFont(ALLEGRO_FONT *font)
	{
		this->font = font;
	}

	float getAngle(GameObject *obj)
	{
		float dx = obj->x - this->x;
		float dy = obj->y - this->y;
		return atan2(dy, dx);
	}

	float getAngle(float x, float y)
	{
		float dx = x - this->x;
		float dy = y - this->y;
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

	float getRadius()
	{
		return this->radius;
	}
	void setRadius(float radius)
	{
		this->radius = radius;
	}

	float getDistance(float x, float y)
	{
		return sqrt(pow(x - this->x, 2) + pow(y - this->y, 2));
	}

	float getDistance(GameObject *obj)
	{
		return sqrt(pow(obj->x - this->x, 2) + pow(obj->y - this->y, 2));
	}

	float getSightDistance()
	{
		return this->sight;
	}
	void setSightDistance(float sight)
	{
		this->sight = sight;
	}

	float getSpeed()
	{
		return this->speed;
	}
	void setSpeed(float speed)
	{
		this->speed = speed;
	}

	obj_state getState()
	{
		return this->state;
	}
	void setState(obj_state state)
	{
		this->state = state;
	}

	bool getCollisionBB(GameObject *obj)	//Bounding Box Collision
	{
		if (this->x > obj->x + obj->sizeW || this->y > obj->y + obj->sizeH ||
			obj->x > this->x + this->sizeW || obj->y > this->y + this->sizeH)
			return false;

		return true;
	}

	bool getCollisionDB(GameObject *obj)	//Distance Based Collision
	{
		if (sqrt(pow(this->x - obj->x, 2) + pow(this->y - obj->y, 2)) < this->radius + obj->radius)
			return true;

		return false;
	}

	bool getCollisionPP(GameObject *obj)	//Pixel Perfect Collision
	{
		int ppBoxTop, ppBoxBottom, ppBoxLeft, ppBoxRight;

		if (!getCollisionBB(obj))
			return false;

		ppBoxTop = std::max(this->y, obj->y);
		ppBoxBottom = std::min(this->y + this->sizeH, obj->y + obj->sizeH);
		ppBoxLeft = std::max(this->x, obj->x);
		ppBoxRight = std::min(this->x + this->sizeW, obj->x + obj->sizeW);

		for (int i = ppBoxTop; i < ppBoxBottom; i++)
		{
			for (int j = ppBoxLeft; j < ppBoxRight; j++)
			{
				al_lock_bitmap(this->texture[this->animation], al_get_bitmap_format(this->texture[this->animation]), ALLEGRO_LOCK_READONLY);
				al_lock_bitmap(obj->texture[obj->animation], al_get_bitmap_format(obj->texture[obj->animation]), ALLEGRO_LOCK_READONLY);
				ALLEGRO_COLOR color1 = al_get_pixel(this->texture[this->animation], j - this->x, i - this->y);
				ALLEGRO_COLOR color2 = al_get_pixel(obj->texture[obj->animation], j - obj->x, i - obj->y);

				if (color1.a != 0 && color2.a != 0)
					return true;
			}
		}
		return false;
	}
};
