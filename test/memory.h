#pragma once
#include <Windows.h>
#include <Psapi.h>

#define NOP 0x90
#define JUMP 0x9E

 // \x8d\x47\x00\xf7\xdb\x1b\xdb\x23\xd8\x89\x5d\x00\x33\xf6\x89\x75\x00\x39\x73\x00\x75 xx ? xxxxxxxx ? xxxx ? xx ? x

class Memory
{
public:
	static void patch(BYTE* dst, BYTE* src, unsigned int size)
	{
		DWORD oProc;

		VirtualProtect(src, size, PAGE_EXECUTE_READWRITE, &oProc);
		memcpy(dst, src, size);
		VirtualProtect(src, size, oProc, &oProc);
	}

	MODULEINFO GetModuleInfo(const char* szModule)
	{
		MODULEINFO modinfo = { 0 };
		HMODULE hModule = GetModuleHandle(szModule);
		if (hModule == 0)
			return modinfo;
		GetModuleInformation(GetCurrentProcess(), hModule, &modinfo, sizeof(MODULEINFO));
		return modinfo;
	}

	// for finding a signature/pattern in memory of another process
	DWORD FindPattern(const char* module,const char* pattern,const  char* mask)
	{
		MODULEINFO mInfo = this->GetModuleInfo(module);
		DWORD base = (DWORD)mInfo.lpBaseOfDll;
		DWORD size = (DWORD)mInfo.SizeOfImage;
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
};