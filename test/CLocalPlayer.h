#pragma once
#include "CBaseEntity.h"

class CLocalPlayer : public CBaseEntity
{
public:
	void AimAt(CBaseEntity*& entity, int bone, float speed = 999999.0f, bool prediction = false);
	CBaseEntity* GetClosestTarget();
private:

};
