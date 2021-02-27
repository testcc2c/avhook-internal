#include "bhop.h"

class LocalPlayer
{
public:
    char pad_0000[244]; //0x0000
    int m_Team; //0x00F4
    char pad_00F6[14]; //0x00F6
    int m_Flags; //0x0104
    char pad_0108[3896]; //0x0108
}; //Size: 0x1040

void HandleBhop(DWORD baseAddr)
{
        DWORD LocalPlayer = mem::ReadVirtualMemory<DWORD>(baseAddr + signatures::dwLocalPlayer);

        if (mem::ReadVirtualMemory<DWORD>(LocalPlayer + netvars::m_fFlags) > 256 and GetAsyncKeyState(VK_SPACE))
        {
            mem::WriteVirtualMemory<int>(baseAddr + signatures::dwForceJump, 5);
            Sleep(10);
            mem::WriteVirtualMemory<int>(baseAddr + signatures::dwForceJump, 4);
        }
}