#pragma once
#include "hack.h"
#include "offsets.h"
#include "imgui/imgui.h"
#include "CBaseEntity.h"

class InGameGlowEsp : public Hack
{
public:
	InGameGlowEsp(int* mode);

	void HandleGlow(ImColor &enemyColor, ImColor &friendlyColor);
private:
	int* mode;
};
