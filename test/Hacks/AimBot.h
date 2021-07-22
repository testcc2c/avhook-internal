#pragma once
#include "hack.h"

class AimBot : public Hack
{
public:
	AimBot(AimBotSettings* settings);
	void Work() override;
private:
	AimBotSettings* settings;
	byte GetBoneIDBySelectedTab();
	
};