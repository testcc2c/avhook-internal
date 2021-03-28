#include "GlowWhInGame.h"


InGameGlowEsp::InGameGlowEsp(int* mode) : Hack()
{
	this->mode = mode;
}

void InGameGlowEsp::HandleGlow(ImColor &enemyColor, ImColor &friendlyColor)
{
	__try
	{
		DWORD glowObject = this->clientbase->dwGlowObjectManager;

		CBaseEntity* LocalPlayer = this->clientbase->dwLocalPlayer;
		for (short int i = 0; i < 32; i++)
		{
			CBaseEntity* Entity = *(CBaseEntity**)((DWORD)(this->clientbase) + signatures::dwEntityList + i * 0x10);
			__try
			{
				if (!*this->mode)
				{
					if (Entity->m_iTeamNum != LocalPlayer->m_iTeamNum)
					{
						*(float*)(glowObject + ((Entity->m_iGlowIndex * 0x38) + 0x4)) = enemyColor.Value.x;
						*(float*)(glowObject + ((Entity->m_iGlowIndex * 0x38) + 0x8)) = enemyColor.Value.y;
						*(float*)(glowObject + ((Entity->m_iGlowIndex * 0x38) + 0xC)) = enemyColor.Value.z;
						*(float*)(glowObject + ((Entity->m_iGlowIndex * 0x38) + 0x10)) = enemyColor.Value.w;

					}
					else
					{
						*(float*)(glowObject + ((Entity->m_iGlowIndex * 0x38) + 0x4)) = friendlyColor.Value.x;
						*(float*)(glowObject + ((Entity->m_iGlowIndex * 0x38) + 0x8)) = friendlyColor.Value.y;
						*(float*)(glowObject + ((Entity->m_iGlowIndex * 0x38) + 0xC)) = friendlyColor.Value.z;
						*(float*)(glowObject + ((Entity->m_iGlowIndex * 0x38) + 0x10)) = friendlyColor.Value.w;
					}
				}
				else
				{
					if (Entity->m_iTeamNum != LocalPlayer->m_iTeamNum)
					{
						if (45 > Entity->m_iHealth)
						{
							*(float*)(glowObject + ((Entity->m_iGlowIndex * 0x38) + 0x4)) = 1.f;
							*(float*)(glowObject + ((Entity->m_iGlowIndex * 0x38) + 0x8)) = 0.f;
							*(float*)(glowObject + ((Entity->m_iGlowIndex * 0x38) + 0xC)) = 0.f;
							*(float*)(glowObject + ((Entity->m_iGlowIndex * 0x38) + 0x10)) = 1.f;

						}
						else if (60 > Entity->m_iHealth)
						{
							*(float*)(glowObject + ((Entity->m_iGlowIndex * 0x38) + 0x4)) = 1.f;
							*(float*)(glowObject + ((Entity->m_iGlowIndex * 0x38) + 0x8)) = 1.f;
							*(float*)(glowObject + ((Entity->m_iGlowIndex * 0x38) + 0xC)) = 0.f;
							*(float*)(glowObject + ((Entity->m_iGlowIndex * 0x38) + 0x10)) = 1.f;

						}
						else if (Entity->m_iHealth > 60)
						{
							*(float*)(glowObject + ((Entity->m_iGlowIndex * 0x38) + 0x4)) = 0.f;
							*(float*)(glowObject + ((Entity->m_iGlowIndex * 0x38) + 0x8)) = 1.f;
							*(float*)(glowObject + ((Entity->m_iGlowIndex * 0x38) + 0xC)) = 0.f;
							*(float*)(glowObject + ((Entity->m_iGlowIndex * 0x38) + 0x10)) = 1.f;

						}

					}
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