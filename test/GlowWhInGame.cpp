#include "GlowWhInGame.h"


InGameGlowEsp::InGameGlowEsp(GlowWHSettings* settings) : Hack()
{
	this->settings = settings;
}

void InGameGlowEsp::HandleGlow()
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
				if (Entity->m_iTeamNum != LocalPlayer->m_iTeamNum)
				{
					if (!settings->draw_mode)
					{
						*(float*)(glowObject + ((Entity->m_iGlowIndex * 0x38) + 0x4))  = this->settings->color.Value.x;
						*(float*)(glowObject + ((Entity->m_iGlowIndex * 0x38) + 0x8))  = this->settings->color.Value.y;
						*(float*)(glowObject + ((Entity->m_iGlowIndex * 0x38) + 0xC))  = this->settings->color.Value.z;
						*(float*)(glowObject + ((Entity->m_iGlowIndex * 0x38) + 0x10)) = this->settings->color.Value.w;

					}
					else
					{
						ImColor auto_color = Entity->GetColorBasedOnHealth();

						*(float*)(glowObject + ((Entity->m_iGlowIndex * 0x38) + 0x4))  = auto_color.Value.x;
						*(float*)(glowObject + ((Entity->m_iGlowIndex * 0x38) + 0x8))  = auto_color.Value.y;
						*(float*)(glowObject + ((Entity->m_iGlowIndex * 0x38) + 0xC))  = auto_color.Value.z;
						*(float*)(glowObject + ((Entity->m_iGlowIndex * 0x38) + 0x10)) = auto_color.Value.w;
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