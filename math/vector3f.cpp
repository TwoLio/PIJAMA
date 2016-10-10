#pragma once

class Vector3f
{
	private:
	float x;
	float y;
	float z;

	public:
	Vector3f(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	/*Vector3f(const Vector3f &v)
	{

	}

	Vector3f& operator= (const Vector3f &v)
	{

	}*/

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

	float getZ()
	{
		return z;
	}

	void setZ(float z)
	{
		this->z = z;
	}

	float getLength()
	{
		return sqrt(x * x + y * y + z * z);
	}

	float dot(Vector3f *v)
	{
		return x * v->getX() + y * v->getY() + z * v->getZ();
	}

	bool equals(Vector3f *v)
	{
		return (x == v->getX() && y == v->getY() && z == v->getZ());
	}

	Vector3f* cross(Vector3f *v)
	{
		float x_ = y * v->getZ() - z * v->getY();
		float y_ = z * v->getX() - x * v->getZ();
		float z_ = x * v->getY() - y * v->getX();

		return new Vector3f(x_, y_, z_);
	}

	Vector3f* normalize()
	{
		float length = getLength();

		return new Vector3f(x / length, y / length, z / length);
	}

	Vector3f* interpolate(Vector3f *dest)
	{
		return dest->sub(this)->mul(dest)->add(this);
	}

	void rotate(float angle, Vector3f *axis)
	{
		/*float cosHalf = cos(angle / 2);
		float sinHalf = sin(angle / 2);

		float rX = axis.getX() * sinHalf;
		float rY = axis.getY() * sinHalf;
		float rZ = axis.getZ() * sinHalf;
		float rW = cosHalf;*/

		//TODO		
	}

	Vector3f* add(Vector3f *v)
	{
		return new Vector3f(x + v->getX(), y + v->getY(), z + v->getZ());
	}

	Vector3f* add(float s)
	{
		return new Vector3f(x + s, y + s, z + s);
	}

	Vector3f* sub(Vector3f *v)
	{
		return new Vector3f(x - v->getX(), y - v->getY(), z - v->getZ());
	}

	Vector3f* sub(float s)
	{
		return new Vector3f(x - s, y - s, z - s);
	}

	Vector3f* mul(Vector3f *v)
	{
		return new Vector3f(x * v->getX(), y * v->getY(), z * v->getZ());
	}

	Vector3f* mul(float s)
	{
		return new Vector3f(x * s, y * s, z * s);
	}

	Vector3f* div(Vector3f *v)
	{
		return new Vector3f(x / v->getX(), y / v->getY(), z / v->getZ());
	}

	Vector3f* div(float s)
	{
		return new Vector3f(x / s, y / s, z / s);
	}

	Vector3f* absolute()
	{
		return new Vector3f(abs(x), abs(y), abs(z));
	}
};
