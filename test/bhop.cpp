#include "bhop.h"

void HandleBhop(DWORD baseAddr)
{
    __try
    {
        CBaseEntity* LocalPlayer = *(CBaseEntity**)(baseAddr + signatures::dwLocalPlayer);
        ClientBase* client = (ClientBase*)(baseAddr);

        if (LocalPlayer->m_fFlags > 256 and GetAsyncKeyState(VK_SPACE))
        {
            client->dwForceJump = 5;
            Sleep(10);
            client->dwForceJump = 4;
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {

    }
}