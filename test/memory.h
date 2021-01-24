#pragma once
#include <Windows.h>
#include <vector>

namespace memory
{
	DWORD GetPointer(DWORD base, std::vector<DWORD> offsets);
}