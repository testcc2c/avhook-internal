#pragma once
#include <d3d9.h>
#include <d3dx9.h>

#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

class DirectX9Drawer
{
public:
	DirectX9Drawer(LPDIRECT3DDEVICE9 pDevice);
	void DrawLine(int x1, int y1, int x2, int y2, int thickness, D3DCOLOR color);

private:
	LPDIRECT3DDEVICE9 pDevice;
};