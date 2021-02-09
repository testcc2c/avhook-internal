#include "memory.h"

DWORD memory::GetPointer(DWORD base, std::vector<DWORD> offsets)
{
	DWORD addr = base;
	MEMORY_BASIC_INFORMATION mbi;

	for (short int i = 0; i < offsets.size(); i++)
	{
		VirtualQuery((LPCVOID)(addr), &mbi, sizeof(MEMORY_BASIC_INFORMATION));

		if (mbi.Protect & (PAGE_GUARD | PAGE_NOCACHE | PAGE_NOACCESS | MEM_PRIVATE) || !(mbi.State & MEM_COMMIT))
			return NULL;

		addr = *(DWORD*)addr;
		addr += offsets[i];

	}
	return addr;
}