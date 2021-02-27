#include "GlowWhInGame.h"


void HandleGlow(DWORD baseAddr, ImVec4 color)
{
	
	DWORD glowObject = mem::ReadVirtualMemory<DWORD>(baseAddr + signatures::dwGlowObjectManager);
	DWORD LocalPlayer = mem::ReadVirtualMemory<DWORD>(baseAddr + signatures::dwLocalPlayer);

	for (short int i = 0; i < 64; i++)
	{
		DWORD entity = mem::ReadVirtualMemory<DWORD>(baseAddr + signatures::dwEntityList + i * 0x10);

		if (entity)
		{
			int glowindex = mem::ReadVirtualMemory<int>(entity + netvars::m_iGlowIndex);
			int enemyteam = mem::ReadVirtualMemory<int>(entity + netvars::m_iTeamNum);

			int localPlayerTeam = mem::ReadVirtualMemory<int>(LocalPlayer + netvars::m_iTeamNum);

			if (enemyteam != localPlayerTeam)
			{
				mem::WriteVirtualMemory<float>(glowObject + ((glowindex * 0x38)  + 0x4), color.x);
				mem::WriteVirtualMemory<float>(glowObject + ((glowindex * 0x38) + 0x8), color.y);
				mem::WriteVirtualMemory<float>(glowObject + ((glowindex * 0x38) + 0xC), color.z);
				mem::WriteVirtualMemory<float>(glowObject + ((glowindex * 0x38) + 0x10), color.w);
			}
			mem::WriteVirtualMemory<bool>(glowObject + ((glowindex * 0x38) + 0x24), true);
			mem::WriteVirtualMemory<bool>(glowObject + ((glowindex * 0x38) + 0x25), false);
		}
	}
}