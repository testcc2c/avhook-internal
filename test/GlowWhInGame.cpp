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

		for (byte i = 0; i < 32; i++)
		{
			CBaseEntity* entity = reinterpret_cast<CBaseEntity*>(this->entity_list->GetClientEntity(i));
			__try
			{
				if (entity->m_iTeamNum != this->clientbase->dwLocalPlayer->m_iTeamNum)
				{
					if (!settings->draw_mode)
					{
						*(float*)(glowObject + ((entity->m_iGlowIndex * 0x38) + 0x4))  = this->settings->color.Value.x;
						*(float*)(glowObject + ((entity->m_iGlowIndex * 0x38) + 0x8))  = this->settings->color.Value.y;
						*(float*)(glowObject + ((entity->m_iGlowIndex * 0x38) + 0xC))  = this->settings->color.Value.z;
						*(float*)(glowObject + ((entity->m_iGlowIndex * 0x38) + 0x10)) = this->settings->color.Value.w;

					}
					else
					{
						ImColor auto_color = entity->GetColorBasedOnHealth();

						*(float*)(glowObject + ((entity->m_iGlowIndex * 0x38) + 0x4))  = auto_color.Value.x;
						*(float*)(glowObject + ((entity->m_iGlowIndex * 0x38) + 0x8))  = auto_color.Value.y;
						*(float*)(glowObject + ((entity->m_iGlowIndex * 0x38) + 0xC))  = auto_color.Value.z;
						*(float*)(glowObject + ((entity->m_iGlowIndex * 0x38) + 0x10)) = auto_color.Value.w;
					}
				}

				*(bool*)(glowObject + ((entity->m_iGlowIndex * 0x38) + 0x24)) = true;
				*(bool*)(glowObject + ((entity->m_iGlowIndex * 0x38) + 0x25)) = false;

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