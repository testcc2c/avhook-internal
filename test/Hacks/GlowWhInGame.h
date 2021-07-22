#pragma once
#include "hack.h"


class InGameGlowEsp : public Hack
{
public:
	InGameGlowEsp(GlowWHSettings* settings);
	GlowWHSettings* settings;
	void Work() override;
};
