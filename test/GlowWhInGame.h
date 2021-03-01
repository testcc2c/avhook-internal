#pragma once
#include "hack.h"
#include "offsets.h"
#include "imgui/imgui.h"
#include "CBaseEntity.h"

class InGameGlowEsp : public Hack
{
public:
	void HandleGlow(ImVec4 &enemyColor, ImVec4 &friendlyColor);

};
