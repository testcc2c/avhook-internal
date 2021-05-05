#pragma once
#include "hack.h"
#include "CBaseEntity.h"
#include "ClientBase.h"
#include "CLocalPlayer.h"
class TriggerBot : public Hack
{

public:
	TriggerBot(TriggerBotSetting* settings);
	void Handle();
	TriggerBotSetting* settings;
private:
	int bone = 8;
};

