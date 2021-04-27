#pragma once
#include "hack.h"
#include "CBaseEntity.h"
#include "ClientBase.h"
#include "CLocalPlayer.h"
class TriggerBot : public Hack
{

public:
	TriggerBot(int* delay, bool* rage);
	void Handle();
private:
	int* delay;
	bool* rage;
	bool* predict;
	int* predict_time;
	int bone = 8;
};

