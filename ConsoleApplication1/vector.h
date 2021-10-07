#ifndef VECTOR_H__
#define VECTOR_H__
#include <math.h>

struct Vector2f{
	float x;
	float y;
	Vector2f(){}
	Vector2f(float Tx, float Ty)
	{
		x = Tx;
		y =Ty;
	}
	Vector2f operator +(const Vector2f& v) const
	{
		return Vector2f(x+v.x, y+v.y);
	}
	Vector2f operator -(const Vector2f& v) const
	{
		return Vector2f(x-v.x, y-v.y);
	}
	Vector2f operator *(float v) const
	{
		return Vector2f(x*v, y*v);
	}
	Vector2f operator /(float v) const
	{
		return Vector2f(x/v, y/v);
	}

	void operator +=(const Vector2f& v)
	{
		*this=  Vector2f(x+v.x, y+v.y);
	}
	void operator -=(const Vector2f& v)
	{
		*this= Vector2f(x-v.x, y-v.y);
	}
	void operator *=(float v) 	{
		*this= Vector2f(x*v, y*v);
	}
	void operator /=(float v)
	{
		*this= Vector2f(x/v, y/v);
	}
	bool operator ==(const Vector2f& v)const
	{
		return x ==v.x&& y==v.y;
	}
	Vector2f Cross(const Vector2f& v) const
	{
		return Vector2f(x,y);
	}
	Vector2f Normalize()
	{
		float k = sqrt(pow(x, 2)+pow(y, 2));
		if(k==0.0)
			return Vector2f(0.0,0.0);
		else
		{
			x = x/k;
			y = y/k;
			return Vector2f(x, y);
		}
		


	}
	float Length()
	{
		float w =sqrt(pow((float)x, 2)+pow((float)y, 2));
		return w;
	}

};
#endif