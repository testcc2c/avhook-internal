#pragma once
#include <Windows.h>
#include <Psapi.h>


class Memory
{
private:
	MODULEINFO GetModuleInfo(const char* szModule)
	{
		MODULEINFO modinfo{ 0 };
		HMODULE hModule = GetModuleHandle(szModule);
		if (hModule == 0)
			return modinfo;
		GetModuleInformation(GetCurrentProcess(), hModule, &modinfo, sizeof(MODULEINFO));
		return modinfo;
	}
public:
	void patch(BYTE* dst, BYTE* src, unsigned int size)
	{
		DWORD oproc;
		VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oproc);
		memcpy(dst, src, size);
		VirtualProtect(dst, size, oproc, &oproc);
	}
	bool detour32(char* src, char* dst, const intptr_t len)
	{
		if (len < 5) return false;

		DWORD  curProtection;
		VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &curProtection);

		intptr_t  relativeAddress = (intptr_t)(dst - (intptr_t)src) - 5;

		*src = '\xE9';
		*(intptr_t*)((intptr_t)src + 1) = relativeAddress;

		VirtualProtect(src, len, curProtection, &curProtection);
		return true;
	}

	char* trampHook32(char* src, char* dst, const intptr_t len)
	{
		if (len < 5) return 0;

		void* gateway = VirtualAlloc(0, len + 5, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

		memcpy(gateway, src, len);

		intptr_t  gatewayRelativeAddr = ((intptr_t)src - (intptr_t)gateway) - 5;

		*(char*)((intptr_t)gateway + len) = 0xE9;

		*(intptr_t*)((intptr_t)gateway + len + 1) = gatewayRelativeAddr;
		this->detour32(src, dst, len);

		return (char*)gateway;
	}

	// for finding a signature/pattern in memory of another process
	DWORD FindPattern(const char* module,const char* pattern,const  char* mask)
	{
		MODULEINFO mInfo	= this->GetModuleInfo(module);
		DWORD base          = (DWORD)mInfo.lpBaseOfDll;
		DWORD size			= (DWORD)mInfo.SizeOfImage;
		DWORD patternLength = (DWORD)strlen(mask);

		for (DWORD i = 0; i < size - patternLength; i++)
		{
			bool found = true;
			for (DWORD j = 0; j < patternLength; j++)
			{
				found &= mask[j] == '?' || pattern[j] == *(char*)(base + i + j);
			}
			if (found)
			{
				return base + i;
			}
		}

		return NULL;
	}
	template<typename FuncType>
	__forceinline static FuncType CallVFunction(void* ppClass, int index)
	{
		int* pVTable         = *reinterpret_cast<int**>(ppClass);
		int function_address = pVTable[index];
		return reinterpret_cast<FuncType>(function_address);
	}
};