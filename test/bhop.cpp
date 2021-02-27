#include "bhop.h"

void HandleBhop(DWORD baseAddr)
{
    __try
    {
        DWORD LocalPlayer = *(DWORD*)(baseAddr + signatures::dwLocalPlayer);

        if (*(int*)(LocalPlayer + netvars::m_fFlags) > 256 and GetAsyncKeyState(VK_SPACE))
        {
            *(int*)(baseAddr + signatures::dwForceJump) = 5;
            Sleep(10);
            *(int*)(baseAddr + signatures::dwForceJump) = 4;
        }

    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {

    }
}