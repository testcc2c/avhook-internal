#pragma once
#include "Vec3.h"
#include <stdlib.h>
#include "CBaseEntity.h"
#include "ClientBase.h"
#include <stdio.h>

#define ABS(x) ((x < 0) ? (-x): (x))

class ESPDrawer : public ImDrawList
{
public:
	void DrawBoxEsp(CBaseEntity* entity, int &thickness, ImColor color, bool drawHp=false);
	void DrawBonesNumbers(CBaseEntity* entity);
};