#pragma once
#include "imgui/imgui.h"

class ImVec3 : public ImVec2
{
public:
	float z = 0;

	ImVec3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	ImVec3()
	{
	};


private:

};