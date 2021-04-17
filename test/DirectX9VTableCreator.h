#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "D3dx9")
#define WINDOW_NAME "Counter-Strike: Global Offensive"

class DirectX9VTableCreator
{
public:
	static bool GetD3D9Device(void** pTable, size_t size, HWND window);
private:

};

