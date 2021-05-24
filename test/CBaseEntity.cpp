#include "CBaseEntity.h"
ImVec3 CBaseEntity::GetBonePosition(int bone)
{
	DWORD  pBone = this->boneMatrix;
	ImVec3 position;

	position.x = *(float*)(pBone + 0x30 * bone + 0x0C);
	position.y = *(float*)(pBone + 0x30 * bone + 0x1C);
	position.z = *(float*)(pBone + 0x30 * bone + 0x2C);

	return position;
}

float CBaseEntity::CalcDistaceToEntity(CBaseEntity* entity)
{
	ImVec3 myPos = this->m_vecOrigin;
	ImVec3 enPos = entity->m_vecOrigin;

	return sqrtf(powf(enPos.x - myPos.x, 2) + powf(enPos.y - myPos.y, 2) + powf(enPos.z - myPos.z, 2));
}

ImColor CBaseEntity::GetColorBasedOnHealth()
{
	if (45 >= this->m_iHealth)
		return ImColor(255, 0, 0);

	else if (60 >= this->m_iHealth)
		return ImColor(255, 255, 0);

	else if (this->m_iHealth >= 60)
		return ImColor(0, 255, 0);

	else
		return ImColor(221, 0, 255);
}

ImVec3 CBaseEntity::GetCameraPosition()
{
	return this->m_vecOrigin + this->m_vecViewOffset;
}

CBaseEntity* CBaseEntity::GetClosestEntity()
{
	CBaseEntity* entitylist[32] = {0};

	DWORD clientBase = (DWORD)GetModuleHandle("client.dll");

	IClientEntityList* VClientEntityList = GetInterface<IClientEntityList>("client.dll", "VClientEntityList003");
	byte counter = 0;

	for (byte i = 2; i < 33; i++)
	{
		CBaseEntity* entity = reinterpret_cast<CBaseEntity*>(VClientEntityList->GetClientEntity(i));

		if (reinterpret_cast<DWORD>(entity) != this->invalid_entity and entity)
			entitylist[counter++] = entity;
	}

	for (byte i = 0; i < counter; i++)
	{
		for (byte j = 0; j < counter - 1; j++)
		{
			if (this->CalcDistaceToEntity(entitylist[j]) > this->CalcDistaceToEntity(entitylist[j + 1]))
			{
				CBaseEntity* temp = entitylist[j];
				entitylist[j]     = entitylist[j + 1];
				entitylist[j + 1] = temp;
			}
		}
	}
	return entitylist[0];
}