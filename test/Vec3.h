#pragma once
#include "Vec2.h"

class Vec3 : public Vec2
{
public:
	float z = 0;

	Vec3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Vec3()
	{
	};


private:

};