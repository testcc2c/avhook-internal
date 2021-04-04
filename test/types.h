#pragma once
#include <Windows.h>

typedef void* (__cdecl* tCreateInterface)(const char* name, int* returncode);

void* GetInterface(const char* dllname, const char* interfacename)
{
	tCreateInterface CreateInterFace = (tCreateInterface)GetProcAddress(GetModuleHandle(dllname), "CreateInterface");

	int returnCode = 0;
	void* interFace = CreateInterFace(interfacename, &returnCode);

	return interFace;

}
