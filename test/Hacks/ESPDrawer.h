#pragma once
#include "../Utils/Vec3.h"
#include <stdlib.h>
#include "../SDK/CBaseEntity.h"
#include "../SDK/ClientBase.h"
#include "../SDK/IVEngineClient013/IVEngineClient013.h"

#include <stdio.h>
#include <string>

class ESPDrawer : public ImDrawList
{
public:
	void DrawBoxEsp(CBaseEntity* entity, int &thickness, ImColor color, bool drawHp=false);
	void DrawBonesNumbers(CBaseEntity* entity);
	void DrawSkeleton(CBaseEntity* entity, ImColor& color, int& thicknes);
};