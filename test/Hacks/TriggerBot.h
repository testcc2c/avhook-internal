#pragma once
#include "hack.h"

class TriggerBot : public Hack
{

public:
	TriggerBot(TriggerBotSetting* settings);
	void Work() override;
	TriggerBotSetting* settings;
private:
	byte bone = 8;
};

