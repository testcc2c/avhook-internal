#include "IVEngineClient013.h"

player_info_s IVEngineClient013::GetPlayerInfo(int ent_num)
{
	player_info_s info;
	typedef player_info_s* (__thiscall* GetPlayerInfoFunc)(void*,int ent_num, player_info_t* pinfo);
	this->GetVirtualFunction<GetPlayerInfoFunc>(8)(this, ent_num, &info);
	return info;
}