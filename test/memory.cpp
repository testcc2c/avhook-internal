#include "memory.h"

DWORD memory::GetPointer(DWORD base, std::vector<DWORD> offsets)
{
	DWORD addr = base;
	HANDLE proc = GetCurrentProcess();
	DWORD temp = NULL;
	for (short int i = 0; i < offsets.size(); i++)
	{
		ReadProcessMemory(proc, (void*)addr, &addr, sizeof(addr), 0);
		addr += offsets[i];

	}
	ReadProcessMemory(proc, (void*)addr, &temp, sizeof(temp), 0);
	if (temp == NULL)
		return NULL;
	return addr;
	
}