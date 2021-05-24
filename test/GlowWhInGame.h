#pragma once
#include "hack.h"
#include "SDK.h"


class InGameGlowEsp : public Hack
{
public:
	InGameGlowEsp(GlowWHSettings* settings);

	void HandleGlow();
	GlowWHSettings* settings;
	IClientEntityList* entity_list;
};
