#include "TriggerBot.h"

TriggerBot::TriggerBot(int* delay, bool* rage)
{
	this->delay = delay;
	this->rage = rage;
}
void TriggerBot::Handle()
{
	__try
	{
		CLocalPlayer* localplayer = *(CLocalPlayer**)(this->clientbase + signatures::dwLocalPlayer);
		CBaseEntity* entity = *(CBaseEntity**)(this->clientbase + signatures::dwEntityList + ((localplayer->m_iCrosshairId - 1) * 0x10));


		if ( (localplayer->m_iTeamNum == entity->m_iTeamNum  or !entity->m_iHealth) or !localplayer->m_iCrosshairId)
			return;

		ClientBase* client = (ClientBase*)clientbase;

		Sleep(*delay);
		if (*this->rage)
			localplayer->AimAt(entity, 8);

		client->dwForceAttack = 6;
		Sleep(20);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{

	}
}