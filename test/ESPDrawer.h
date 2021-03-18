#pragma once
#include "Vec3.h"

#define ABS(x) ((x < 0) ? (-x): (x))

class ESPDrawer : public ImDrawList
{
public:
	void DrawBoxEsp(ImVec2 &up, ImVec2&bottom, int &thickness, ImColor color);

};