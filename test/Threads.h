#pragma once
#include "settings.h"
#include "pointers.h"
#include <Windows.h>
#include "memory.h"

namespace threads
{
	DWORD WINAPI FreezeThread(LPVOID lpReserved);
}