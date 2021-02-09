#include "Threads.h"


DWORD WINAPI threads::FreezeThread(LPVOID lpReserved)
{
	DWORD baseAddr = (DWORD)GetModuleHandle(NULL);
	while (true)
	{
		bool airjump = settings::airjump;
		if (airjump)
		{
			pointers::pAirJump = (float*)(memory::GetPointer(baseAddr + 0x9D56A8, { 0x888, 0x48, 0x418 }));
			if (pointers::pAirJump)
				*pointers::pAirJump = -1.f;

		}
		Sleep(100);

	}
	return 0;
}