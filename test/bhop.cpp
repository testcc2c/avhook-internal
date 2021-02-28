#include "bhop.h"

void HandleBhop(DWORD baseAddr)
{
        DWORD pLocalPlayer = mem::ReadVirtualMemory<DWORD>(baseAddr + signatures::dwLocalPlayer);
        if (!pLocalPlayer)
            return;

        CBaseEntity* LocalPlayer = (CBaseEntity*)pLocalPlayer;
        if (LocalPlayer->m_fFlags > 256 and GetAsyncKeyState(VK_SPACE))
        {
            mem::WriteVirtualMemory<int>(baseAddr + signatures::dwForceJump, 5);
            Sleep(10);
            mem::WriteVirtualMemory<int>(baseAddr + signatures::dwForceJump, 4);
        }
}