#pragma once
#include "CBaseEntity.h"
#include "types.h"
#include "IClientEntityList.h"

class CLocalPlayer : public CBaseEntity
{
public:
	ImVec3* GetViewAngles();
	// Aim on target entity
	void AimAt(CBaseEntity*& entity, byte& bone, float speed = 999999.0f, bool prediction = false);
	// Get closest valid target
	CBaseEntity* GetClosestTarget(int& fov, byte& bone);
	// Return angles to target
	ImVec3 GetAimTargetAngles(CBaseEntity*& entity, byte bone);
private:

};
