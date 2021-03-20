#pragma once
#include "CBaseEntity.h"

class CLocalPlayer : public CBaseEntity
{
public:
	void AimAt(CBaseEntity*& entity, int bone,int time = 1, bool prediction = false);

private:

};
