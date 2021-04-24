#pragma once
#include "CBaseEntity.h"
#include "types.h"
#include "IClientEntityList.h"

class CLocalPlayer : public CBaseEntity
{
public:
	ImVec3* GetViewAngles();
	// Aim on target entity
	void AimAt(CBaseEntity*& entity, int bone, float speed = 999999.0f, bool prediction = false);
	// Get closest valid target
	CBaseEntity* GetClosestTarget();
	// Return angles to target
	ImVec3 GetAimTargetAngles(CBaseEntity*& entity, int bone);
private:

};
