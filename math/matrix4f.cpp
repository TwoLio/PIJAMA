#pragma once

class Matrix4f
{
	private:
	float **m;

	public:
	Matrix4f()
	{
		*m = new float[4];
		
	}

	~Matrix4f()
	{
	}

	/*Matrix4f(const Matrix4f	&m)
	{

	}

	Matrix4f& operator= (const Matrix4f &m)
	{

	}*/

	Matrix4f* initIdentity()
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; i++)
				if (i == j)
					m[i][j] = 1;
				else
					m[i][j] = 0;

		return this;
	}

	Matrix4f* initRotation(Vector3f *forward, Vector3f *up)
	{
		Vector3f *f = forward;
		f->normalize();

		Vector3f *r = up;
		r->normalize();
		r = r->cross(f);

		Vector3f *u = f->cross(r);

		m[0][0] = r->getX();	m[0][1] = r->getY();	m[0][2] = r->getZ();	m[0][3] = 0;
		m[1][0] = u->getX();	m[1][1] = u->getY();	m[1][2] = u->getZ();	m[1][3] = 0;
		m[2][0] = f->getX();	m[2][1] = f->getY();	m[2][2] = f->getZ();	m[2][3] = 0;
		m[3][0] = 0;			m[3][1] = 0;			m[3][2] = 0;			m[3][3] = 1;

		return this;
	}

	Matrix4f* initPerspective(float fov, float ratio, float zNear, float zFar)
	{
		float tanHalfFOV = tan(fov / 2);
		float zRange = zNear - zFar;

		m[0][0] = 1.0f / (tanHalfFOV * ratio);	m[0][1] = 0;					m[0][2] = 0;							m[0][3] = 0;
		m[1][0] = 0;							m[1][1] = 1.0f / tanHalfFOV;	m[1][2] = 0;							m[1][3] = 0;
		m[2][0] = 0;							m[2][1] = 0;					m[2][2] = (- zNear - zFar) / zRange;	m[2][3] = 2 * zFar * zNear / zRange;
		m[3][0] = 0;							m[3][1] = 0;					m[3][2] = 1;							m[3][3] = 0;

		return this;
	}

	Matrix4f* initOrthographic(float left, float right, float bottom, float top, float near, float far)
	{
		float width = right - left;
		float height = top - bottom;
		float depth = far - near;

		m[0][0] = 2 / width;	m[0][1] = 0;			m[0][2] = 0;			m[0][3] = -(right + left) / width;
		m[1][0] = 0;			m[1][1] = 2 / height;	m[1][2] = 0;			m[1][3] = -(top + bottom) / height;
		m[2][0] = 0;			m[2][1] = 0;			m[2][2] = -2 / depth;	m[2][3] = -(far + near) / depth;
		m[3][0] = 0; 			m[3][1] = 0;			m[3][2] = 0;			m[3][3] = 1;

		return this;
	}

	Matrix4f* initTranslation(float x, float y, float z)
	{
        m[0][0] = 1;   m[0][1] = 0;   m[0][2] = 0;   m[0][3] = x;
        m[1][0] = 0;   m[1][1] = 1;   m[1][2] = 0;   m[1][3] = y;
        m[2][0] = 0;   m[2][1] = 0;   m[2][2] = 1;   m[2][3] = z;
        m[3][0] = 0;   m[3][1] = 0;   m[3][2] = 0;   m[3][3] = 1;

		return this;
	}

	void initRotation(float x, float y, float z)
	{
		Matrix4f *rx = new Matrix4f();
		Matrix4f *ry = new Matrix4f();
		Matrix4f *rz = new Matrix4f();

		rx->m[0][0] = 1;		rx->m[0][1] = 0;		rx->m[0][2] = 0;		rx->m[0][3] = 0;
		rx->m[1][0] = 0;		rx->m[1][1] = cos(x);	rx->m[1][2] = -sin(x);	rx->m[1][3] = 0;
		rx->m[2][0] = 0;		rx->m[2][1] = sin(x);	rx->m[2][2] = cos(x);	rx->m[2][3] = 0;
		rx->m[3][0] = 0;		rx->m[3][1] = 0;		rx->m[3][2] = 0;		rx->m[3][3] = 1;
        
		ry->m[0][0] = cos(y);	ry->m[0][1] = 0;		ry->m[0][2] = -sin(y);	ry->m[0][3] = 0;
		ry->m[1][0] = 0;		ry->m[1][1] = 1;		ry->m[1][2] = 0;		ry->m[1][3] = 0;
		ry->m[2][0] = sin(y);	ry->m[2][1] = 0;		ry->m[2][2] = cos(y);	ry->m[2][3] = 0;
		ry->m[3][0] = 0;		ry->m[3][1] = 0;		ry->m[3][2] = 0;		ry->m[3][3] = 1;

		rz->m[0][0] = cos(z);	rz->m[0][1] = -sin(z);	rz->m[0][2] = 0;		rz->m[0][3] = 0;
		rz->m[1][0] = sin(z);	rz->m[1][1] = cos(z);	rz->m[1][2] = 0;		rz->m[1][3] = 0;
		rz->m[2][0] = 0;		rz->m[2][1] = 0;		rz->m[2][2] = 1;		rz->m[2][3] = 0;
		rz->m[3][0] = 0;		rz->m[3][1] = 0;		rz->m[3][2] = 0;		rz->m[3][3] = 1;

		//TODO m = rz->mul(ry->mul(rx)).getMatrix();

		
	}

	Matrix4f* initScale(float x, float y, float z)
	{
		m[0][0] = x;	m[0][1] = 0;	m[0][2] = 0;	m[0][3] = 0;
		m[1][0] = 0;	m[1][1] = y;	m[1][2] = 0;	m[1][3] = 0;
		m[2][0] = 0;	m[2][1] = 0;	m[2][2] = z;	m[2][3] = 0;
		m[3][0] = 0;	m[3][1] = 0;	m[3][2] = 0;	m[3][3] = 1;

		return this;
	}

	float getValue(int i, int j)
	{
		return m[i][j];
	}

	void setValue(int i, int j, int value)
	{
		m[i][j] = value;
	}



/*	float** getMatrix()
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				r[i][j] = m[i][j];

		return r;
	}
*/
};
