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
		ImVec3* local_player_fov = localPlayer->GetViewAngles();
		ImVec3 target_angles     = localPlayer->GetAimTargetAngles(ent, aim_bone);
		ImVec2  fov_target       = ImVec2(local_player_fov->x - target_angles.x, local_player_fov->y - target_angles.y);

		if (fov_target.x <= this->settings->fov and fov_target.y <= this->settings->fov and fov_target.x >= -this->settings->fov and fov_target.y >= -this->settings->fov)
			localPlayer->AimAt(ent, aim_bone, 30000, true);
		
		if (this->settings->auto_shoot)
		{
			this->clientbase->dwForceAttack = 6;
			Sleep(10);
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{

	}
}