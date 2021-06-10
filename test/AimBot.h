#pragma once
#include "hack.h"
#include "MenuSettings.h"

class AimBot : public Hack
{
public:
	AimBot(AimBotSettings* settings);
	void Work() override;
private:
	AimBotSettings* settings;
	byte GetBoneIDBySelectedTab();
	
};