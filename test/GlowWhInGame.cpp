#include "GlowWhInGame.h"

void HandleGlow(DWORD baseAddr, ImVec4 color)
{
	
	DWORD glowObject = mem::ReadVirtualMemory<DWORD>(baseAddr + signatures::dwGlowObjectManager);
	DWORD pLocalPlayer = mem::ReadVirtualMemory<DWORD>(baseAddr + signatures::dwLocalPlayer);

	for (short int i = 0; i < 64; i++)
	{
		DWORD pEntity = mem::ReadVirtualMemory<DWORD>(baseAddr + signatures::dwEntityList + i * 0x10);

		if (pEntity and pLocalPlayer)
		{
			CBaseEntity* LocalPlayer = (CBaseEntity*)pLocalPlayer;
			CBaseEntity* Entity = (CBaseEntity*)pEntity;
			int glowindex = mem::ReadVirtualMemory<int>(pEntity + netvars::m_iGlowIndex);

			if (Entity->m_iTeamNum != LocalPlayer->m_iTeamNum)
			{
				mem::WriteVirtualMemory<float>(glowObject + ((Entity->m_iGlowIndex * 0x38)  + 0x4), color.x);
				mem::WriteVirtualMemory<float>(glowObject + ((Entity->m_iGlowIndex * 0x38) + 0x8), color.y);
				mem::WriteVirtualMemory<float>(glowObject + ((Entity->m_iGlowIndex * 0x38) + 0xC), color.z);
				mem::WriteVirtualMemory<float>(glowObject + ((Entity->m_iGlowIndex * 0x38) + 0x10), color.w);
			}
			mem::WriteVirtualMemory<bool>(glowObject + ((Entity->m_iGlowIndex * 0x38) + 0x24), true);
			mem::WriteVirtualMemory<bool>(glowObject + ((Entity->m_iGlowIndex * 0x38) + 0x25), false);
		}
	}
}