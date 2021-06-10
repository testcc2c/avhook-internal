#include "AimBot.h"

AimBot::AimBot(AimBotSettings* settings) : Hack()
{
	this->settings = settings;
}
byte AimBot::GetBoneIDBySelectedTab()
{
	if (this->settings->selected_hitbox == 0)
		return CBaseEntiyBones::HEAD;

	else if (this->settings->selected_hitbox == 1)
		return CBaseEntiyBones::BODY;
	else if (this->settings->selected_hitbox == 2)
		return CBaseEntiyBones::LEGS;
	else
		return CBaseEntiyBones::HEAD;
}
void AimBot::Work()
{
	if (!this->settings->active or (this->settings->on_key and !GetAsyncKeyState(VK_LBUTTON)))
	{
		Sleep(10);
		this->settings->is_working = false;
		return;
	}
	CLocalPlayer* localPlayer = this->clientbase->dwLocalPlayer;
	CBaseEntity* ent		  = nullptr;
	this->settings->is_working = true;
	byte aim_bone = this->GetBoneIDBySelectedTab();

	if (!localPlayer)
		return;

	ent = localPlayer->GetClosestTarget(this->settings->fov, aim_bone);

	if (!ent)
		return;
	__try
	{
		localPlayer->AimAt(ent, aim_bone, 30000, true);
		if (this->settings->auto_shoot and this->entity_list->GetClientEntity(localPlayer->m_iCrosshairId) == ent)
		{
			this->clientbase->dwForceAttack = 6;
			Sleep(10);
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{

	}
}