#include "bhop.h"

void BunnyHop::HandleBhop()
{
    __try
    {
        CBaseEntity* LocalPlayer = *(CBaseEntity**)(this->clientbase + signatures::dwLocalPlayer);
        ClientBase* client = (ClientBase*)(this->clientbase);

        if (GetAsyncKeyState(VK_SPACE))
            switch (LocalPlayer->m_fFlags)
            {
            case FL_ONGROUND:
            case FL_ONGROUND_DUCK:
                client->dwForceJump = 5;
                Sleep(10);
                client->dwForceJump = 4;
                break;
            }
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {

    }
}