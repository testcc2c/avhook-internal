#pragma once
#include "hack.h"
#include "offsets.h"
#include "imgui/imgui.h"
#include "CBaseEntity.h"
class InGameGlowEsp : public Hack
{
public:
	InGameGlowEsp(GlowWHSettings* settings);

	void HandleGlow();
	GlowWHSettings* settings;
};
