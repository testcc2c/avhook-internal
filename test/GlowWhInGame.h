#pragma once
#include "hack.h"
#include "offsets.h"
#include "imgui/imgui.h"
#include "CBaseEntity.h"
#include "settings.h"

class InGameGlowEsp : public Hack
{
public:
	InGameGlowEsp(int* mode);

	void HandleGlow(ImVec4 &enemyColor, ImVec4 &friendlyColor);
private:
	int* mode;
};
