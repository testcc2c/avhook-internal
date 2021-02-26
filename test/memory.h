#pragma once
#include <Windows.h>

namespace mem
{
	template <typename T>
	T* ReadVirtualMemory(DWORD addr)
	{
		__try
		{
			return (T*)(addr);
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			return nullptr;
		}
	}

}