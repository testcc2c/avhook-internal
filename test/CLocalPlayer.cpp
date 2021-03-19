#include "CLocalPlayer.h"

void CLocalPlayer::AimAt(CBaseEntity*& entity, int bone)
{
	DWORD engineModule = (DWORD)GetModuleHandle(L"engine.dll");
	ClientBase* client = (ClientBase*)((DWORD)GetModuleHandle(L"client.dll"));
	ImVec3 calculated;

	ImVec3 targetpos = entity->GetBonePosition(bone);
	ImVec3 myPos = this->m_vecOrigin;
	myPos.z += this->m_vecViewOffset.z;
	ImVec3* angles = (ImVec3*)(*(DWORD*)(engineModule + signatures::dwClientState) + signatures::dwClientState_ViewAngles);

	ImVec3 delta = ImVec3(targetpos.x - myPos.x, targetpos.y - myPos.y, targetpos.z - myPos.z);
	float legth = delta.x * delta.x + delta.y * delta.y + delta.z * delta.z;

	angles->x = -asinf(delta.z / legth) * (180 / 3.1415926f);
	angles->y = atan2f(delta.y, delta.x) * (180 / 3.1415926f);

}