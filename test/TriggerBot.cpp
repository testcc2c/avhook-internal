#include "TriggerBot.h"

TriggerBot::TriggerBot(int* delay, bool* rage, bool *predict, int* predict_time)
{
	this->delay = delay;
	this->rage = rage;
	this->predict = predict;
	this->predict_time = predict_time;
}
void TriggerBot::Handle()
{
	__try
	{
		CLocalPlayer* localplayer = this->clientbase->dwLocalPlayer;
		CBaseEntity* entity = *(CBaseEntity**)((DWORD)(this->clientbase) + signatures::dwEntityList + ((localplayer->m_iCrosshairId - 1) * 0x10));

		
		if ( (localplayer->m_iTeamNum == entity->m_iTeamNum  or !entity->m_iHealth) or !localplayer->m_iCrosshairId)
			return;

		Sleep(*delay);
		if (*this->rage)
			localplayer->AimAt(entity, 8, *predict_time, *predict);

		this->clientbase->dwForceAttack = 6;
		Sleep(20);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{

	}
}