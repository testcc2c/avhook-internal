#include "CBaseEntity.h"

Vec3 CBaseEntity::GetBonePosition(int bone)
{
	DWORD pBone = this->boneMatrix;
	Vec3 position;
	position.x = *(float*)(pBone + 0x30 * bone + 0x0C);
	position.y = *(float*)(pBone + 0x30 * bone + 0x1C);
	position.z = *(float*)(pBone + 0x30 * bone + 0x2C);

	return position;
}