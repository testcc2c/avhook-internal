#pragma once
#include "hack.h"
#include "CBaseEntity.h"
#include "ClientBase.h"

class TriggerBot : public Hack
{

public:
	TriggerBot(int* delay);
	void Handle();
private:
	int* delay;
};

