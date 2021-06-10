#pragma once
#include "hack.h"
#include "CBaseEntity.h"
#include "ClientBase.h"
#include "CLocalPlayer.h"
class TriggerBot : public Hack
{

public:
	TriggerBot(TriggerBotSetting* settings);
	void Work() override;
	TriggerBotSetting* settings;
private:
	byte bone = 8;
};

