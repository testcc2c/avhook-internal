#include "CLocalPlayer.h"

void CLocalPlayer::AimAt(CBaseEntity*& entity, byte& bone, float speed, bool prediction)
{

	ImVec3 targetpos = entity->GetBonePosition(bone);
	ImVec3 myPos = this->m_vecOrigin;

	myPos.z += this->m_vecViewOffset.z;
	


	ImVec3* angles = this->GetViewAngles();

	float distance = this->CalcDistaceToEntity(entity);
	if (prediction)
	{
		targetpos.x += entity->m_vecVelocity.x * (distance / speed);
		targetpos.y += entity->m_vecVelocity.y * (distance / speed);

		distance = sqrtf(powf(targetpos.x - myPos.x, 2) + powf(targetpos.y - myPos.y, 2) + powf(targetpos.z - myPos.z, 2));
	}

	float pitch = -asinf( (targetpos.z - myPos.z) / distance) * (180 / 3.1415926f);
	float yaw = atan2f(targetpos.y - myPos.y, targetpos.x - myPos.x) * (180 / 3.1415926f);


	if ((-89.f <= pitch) && (pitch <= 89.f) && (-180.f <= yaw) && (yaw <= 180.f))
	{
		angles->x = pitch;
		angles->y = yaw;
	}
}
CBaseEntity* CLocalPlayer::GetClosestTarget(int& fov, byte& bone)
{
	CBaseEntity* entitylist[32];


	IClientEntityList* VClientEntityList = GetInterface<IClientEntityList>("client.dll", "VClientEntityList003");
	byte counter = 0;

	for (byte i = 1; i < 33; i++)
	{

		__try
		{
			CBaseEntity* entity = reinterpret_cast<CBaseEntity*>(VClientEntityList->GetClientEntity(i));

			if (!entity)
				continue;
			ImVec3* localAngles = this->GetViewAngles();
			ImVec3  targetAngles = this->GetAimTargetAngles(entity, bone);
			ImVec2  fov_target = ImVec2(localAngles->x - targetAngles.x, localAngles->y - targetAngles.y);

			if (entity->m_iHealth > 0 and !entity->m_bDormant and this->m_iTeamNum != entity->m_iTeamNum and fov_target.x <= fov and fov_target.y <= fov and fov_target.x >= -fov and fov_target.y >= -fov)
				entitylist[counter++] = entity;
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{

		}
	}

	for (byte i = 0; i < counter; i++)
	{
		for (byte j = 0; j < counter - 1; j++)
		{
			if (this->CalcDistaceToEntity(entitylist[j]) > this->CalcDistaceToEntity(entitylist[j + 1]))
			{
				CBaseEntity* temp = entitylist[j];
				entitylist[j] = entitylist[j + 1];
				entitylist[j + 1] = temp;
			
			}
		}

	}
	return entitylist[0];
}

ImVec3 CLocalPlayer::GetAimTargetAngles(CBaseEntity*& entity, byte bone)
{
	ImVec3 calculated;

	ImVec3 targetpos = entity->GetBonePosition(bone);
	ImVec3 myPos = this->m_vecOrigin;

	myPos.z += this->m_vecViewOffset.z;

	float distance = this->CalcDistaceToEntity(entity);
	calculated.x   = -asinf((targetpos.z - myPos.z) / distance) * (180 / 3.1415926f);
	calculated.y   = atan2f(targetpos.y - myPos.y, targetpos.x - myPos.x) * (180 / 3.1415926f);

	return calculated;
}

ImVec3* CLocalPlayer::GetViewAngles()
{
	DWORD engineModule = reinterpret_cast<DWORD>(GetModuleHandle(xorstr("engine.dll")));
	return (ImVec3*)(*(DWORD*)(engineModule + signatures::dwClientState) + signatures::dwClientState_ViewAngles);
}