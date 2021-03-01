#include "GlowWhInGame.h"

void HandleGlow(DWORD baseAddr, ImVec4 enemyColor, ImVec4 friendlyColor)
{
	__try
	{
		DWORD glowObject = *(DWORD*)(baseAddr + signatures::dwGlowObjectManager);

		CBaseEntity* LocalPlayer = *(CBaseEntity**)(baseAddr + signatures::dwLocalPlayer);
		for (short int i = 0; i < 64; i++)
		{
			CBaseEntity* Entity = *(CBaseEntity**)(baseAddr + signatures::dwEntityList + i * 0x10);
			__try
			{
				if (Entity->m_iTeamNum != LocalPlayer->m_iTeamNum)
				{
					*(float*)(glowObject + ((Entity->m_iGlowIndex * 0x38) + 0x4)) = enemyColor.x;
					*(float*)(glowObject + ((Entity->m_iGlowIndex * 0x38) + 0x8)) = enemyColor.y;
					*(float*)(glowObject + ((Entity->m_iGlowIndex * 0x38) + 0xC)) = enemyColor.z;
					*(float*)(glowObject + ((Entity->m_iGlowIndex * 0x38) + 0x10)) = enemyColor.w;

				}
				else
				{
					*(float*)(glowObject + ((Entity->m_iGlowIndex * 0x38) + 0x4)) = friendlyColor.x;
					*(float*)(glowObject + ((Entity->m_iGlowIndex * 0x38) + 0x8)) = friendlyColor.y;
					*(float*)(glowObject + ((Entity->m_iGlowIndex * 0x38) + 0xC)) = friendlyColor.z;
					*(float*)(glowObject + ((Entity->m_iGlowIndex * 0x38) + 0x10)) = friendlyColor.w;
				}

				*(bool*)(glowObject + ((Entity->m_iGlowIndex * 0x38) + 0x24)) = true;
				*(bool*)(glowObject + ((Entity->m_iGlowIndex * 0x38) + 0x25)) = false;

			}
			__except (EXCEPTION_EXECUTE_HANDLER)
			{

			}
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{

	}
}