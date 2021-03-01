#include "bhop.h"

void BunnyHop::HandleBhop()
{
    __try
    {
        CBaseEntity* LocalPlayer = *(CBaseEntity**)(this->clientbase + signatures::dwLocalPlayer);
        ClientBase* client = (ClientBase*)(this->clientbase);

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