#include "TriggerBot.h"

TriggerBot::TriggerBot(TriggerBotSetting* settings)
{
	this->settings = settings;

}
void TriggerBot::Work()
{
	
	__try
	{
		CLocalPlayer* localplayer = this->clientbase->dwLocalPlayer;
		CBaseEntity*  entity = this->entity_list->GetClientEntity(localplayer->m_iCrosshairId);


		if ((localplayer->m_iTeamNum == entity->m_iTeamNum or !entity->m_iHealth) or !localplayer->m_iCrosshairId)
			return;

		Sleep(this->settings->delay);
		if (this->settings->rage)
			localplayer->AimAt(entity, this->bone);

		this->clientbase->dwForceAttack = 6;
		Sleep(20);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{

	}
}