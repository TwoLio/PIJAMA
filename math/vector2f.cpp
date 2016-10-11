#pragma once

class Vector2f
{
	private:
	float x;
	float y;

	public:
	Vector2f(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	Vector2f(const Vector2f &v)
	{
		this->setX(v.getX());
		this->setY(v.getY());
	}

	Vector2f& operator= (const Vector2f &v)
	{
		this->setX(v.getX());
		this->setY(v.getY());

		return *this;
	}

	float getX() const
	{
		return x;
	}

	void setX(float x)
	{
		this->x = x;
	}

	float getY() const
	{
		return y;
	}

	void setY(float y)
	{
		this->y = y;
	}

	float getLength()
	{
		return sqrt(x * x + y * y);
	}

	float dot(Vector2f *v)
	{
		return (x * v->getX()) + (y * v->getY());
	}

	float cross(Vector2f *v)
	{
		return (x * v->getY()) - (y * v->getX());
	}

	bool equals(Vector2f *v)
	{
		return (x == v->getX() && y == v->getY());
	}

	Vector2f* normalize()
	{
		float length = this->getLength();

		return new Vector2f(x / length, y / length);
	}

	Vector2f* interpolate(Vector2f *dest)
	{
		return dest->sub(this)->mul(dest)->add(this);
	}

	Vector2f* rotate(float angle)
	{
		float cs = cos(angle);
		float sn = sin(angle);

		return new Vector2f(x*cs - y*sn, x*sn + y*cs);
	}

	Vector2f* add(Vector2f *v)
	{
		return new Vector2f(x + v->getX(), y + v->getY());
	}

	Vector2f* add(float s)
	{
		return new Vector2f(x + s, y + s);
	}

	Vector2f* sub(Vector2f *v)
	{
		return new Vector2f(x - v->getX(), y - v->getY());
	}

	Vector2f* sub(float s)
	{
		return new Vector2f(x - s, y - s);
	}

	Vector2f* mul(Vector2f *v)
	{
		return new Vector2f(x * v->getX(), y * v->getY());
	}

	Vector2f* mul(float s)
	{
		return new Vector2f(x * s, y * s);
	}

	Vector2f* div(Vector2f *v)
	{
		return new Vector2f(x / v->getX(), y / v->getY());
	}

	Vector2f* div(float s)
	{
		return new Vector2f(x / s, y / s);
	}
};
