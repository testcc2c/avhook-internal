#include "CBaseEntity.h"

ImVec3 CBaseEntity::GetBonePosition(int bone)
{
	DWORD pBone = this->boneMatrix;
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

CBaseEntity* CBaseEntity::GetClosestEnity()
{
	CBaseEntity* entitylist[32];

	DWORD clientBase = (DWORD)GetModuleHandle(L"client.dll");
	int counter = 0;

	for (short int i = 1; i < 33; i++)
	{
		__try
		{
			CBaseEntity* entity = *(CBaseEntity**)(clientBase + signatures::dwEntityList + i * 0x10);
			if (entity->m_iHealth <= 0 or entity->m_bDormant )
				continue;
			entitylist[counter++] = entity;
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{

		}
	}

	for (short int i = 0; i < counter; i++)
	{
		for (short int j = 0; j < counter - 1; j++)
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