#include "CLocalPlayer.h"

void CLocalPlayer::AimAt(CBaseEntity*& entity, int bone, int time, bool prediction)
{
	DWORD engineModule = (DWORD)GetModuleHandle(L"engine.dll");
	ClientBase* client = (ClientBase*)((DWORD)GetModuleHandle(L"client.dll"));
	ImVec3 calculated;

	ImVec3 targetpos = entity->GetBonePosition(bone);
	ImVec3 myPos = this->m_vecOrigin;
	myPos.z += this->m_vecViewOffset.z;



	ImVec3* angles = (ImVec3*)(*(DWORD*)(engineModule + signatures::dwClientState) + signatures::dwClientState_ViewAngles);

	float distance = this->CalcDistaceToEntity(entity);
	if (prediction)
	{
		targetpos.x += entity->m_vecVelocity.x * (time / 1000.f);
		targetpos.y += entity->m_vecVelocity.y * (time / 1000.f);

		distance = sqrtf(powf(targetpos.x - myPos.x, 2) + powf(targetpos.y - myPos.y, 2) + powf(targetpos.z - myPos.z, 2));
	}

	float pitch = -asinf( (targetpos.z - myPos.z) / distance * (180 / 3.1415926f));
	float yaw = atan2f(targetpos.y - myPos.y, targetpos.x - myPos.x) * (180 / 3.1415926f);

	if ((-89.f <= pitch) && (pitch <= 89.f) && (-180.f <= yaw) && (yaw <= 180.f))
	{
		angles->x = pitch;
		angles->y = yaw;
	}
	if (prediction)
		Sleep(time);
}