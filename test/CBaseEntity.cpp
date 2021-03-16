#include "CBaseEntity.h"
#include "ClientBase.h"

Vec3 CBaseEntity::GetBonePosition(int bone)
{
	DWORD pBone = this->boneMatrix;
	Vec3 position;
	position.x = *(float*)(pBone + 0x30 * bone + 0x0C);
	position.y = *(float*)(pBone + 0x30 * bone + 0x1C);
	position.z = *(float*)(pBone + 0x30 * bone + 0x2C);

	return position;
}

float CBaseEntity::CalcDistaceToEntity(CBaseEntity* entity)
{
	Vec3 myPos = this->m_vecOrigin;
	Vec3 enPos = entity->m_vecOrigin;

	return sqrtf(powf(enPos.x - myPos.x, 2) + powf(enPos.y - myPos.y, 2) + powf(enPos.z - myPos.z, 2));
}

void CBaseEntity::AimAt(CBaseEntity* &entity, int bone)
{
	DWORD engineModule = (DWORD)GetModuleHandle(L"engine.dll");
	ClientBase* client = (ClientBase*)((DWORD)GetModuleHandle(L"client.dll"));
	Vec3 calculated;

	Vec3 targetpos = entity->GetBonePosition(bone);
	Vec3 myPos = this->m_vecOrigin;
	myPos.z += this->m_vecViewOffset.z;
	Vec3* angles = (Vec3*)(*(DWORD*)(engineModule + signatures::dwClientState) + signatures::dwClientState_ViewAngles);
	Vec3 olda = *angles;

	Vec3 delta = Vec3(targetpos.x - myPos.x, targetpos.y - myPos.y, targetpos.z - myPos.z);
	float legth = delta.x * delta.x + delta.y * delta.y + delta.z * delta.z;

	angles->x = -asin(delta.z / legth) * (180/ 3.1415926f);
	angles->y = atan2f(delta.y , delta.x) * (180 / 3.1415926f);

	client->dwForceAttack = 6;
	Sleep(8);
	angles->x = olda.x;
	angles->y = olda.y;
	
}