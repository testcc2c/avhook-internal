#include "GlowWhInGame.h"

void HandleGlow(DWORD baseAddr, ImVec4 color)
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
					*(float*)(glowObject + ((Entity->m_iGlowIndex * 0x38) + 0x4)) = color.x;
					*(float*)(glowObject + ((Entity->m_iGlowIndex * 0x38) + 0x8)) = color.y;
					*(float*)(glowObject + ((Entity->m_iGlowIndex * 0x38) + 0xC)) = color.z;
					*(float*)(glowObject + ((Entity->m_iGlowIndex * 0x38) + 0x10)) = color.w;

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