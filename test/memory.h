#pragma once
#include <Windows.h>

#define NOP 0x90
#define JUMP 0x9E

void patch(BYTE* dst, BYTE* src, unsigned int size)
{
	DWORD oProc;

	VirtualProtect(src, size, PAGE_EXECUTE_READWRITE, &oProc);
	memcpy(dst, src, size);
	VirtualProtect(src, size, oProc, &oProc);
}
bool hook(char* dst, char* src, int len)
{
	if (len < 5) return false;
	DWORD oProc;

	VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &oProc);
	memset(src, NOP, len);

	DWORD relative_addres = (DWORD)(dst - src - 5);
	*src = (char)JUMP;
	*(DWORD*)(src + 1) = (DWORD)relative_addres;

	VirtualProtect(src, len, oProc, &oProc);
}
char* trampolinehook(char* dst, char* src, int len)
{
	if (len < 5) return false;
	char* gateway = (char*)VirtualAlloc(NULL, len + 5, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	memcpy(gateway, src, len);
	DWORD jumpAddr = (DWORD)(src - gateway - 5);
	*(gateway + len) = (char)JUMP;
	*(DWORD*)(gateway + len + 1) = jumpAddr;

	if (hook(src, dst, len))
		return gateway;

	else return nullptr;

}