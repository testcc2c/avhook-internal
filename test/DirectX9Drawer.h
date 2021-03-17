#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "Vec2.h"

#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

#define ABS(x) ((x < 0) ? (-x): (x))
class DirectX9Drawer
{
public:
	DirectX9Drawer(LPDIRECT3DDEVICE9 pDevice);
	void DrawLine(Vec2& pos1, Vec2& pos2, int thickness, D3DCOLOR color);
	void DrawFilledRect(int x, int y, int w, int h, D3DCOLOR color);
	void DrawEmptyRect(Vec2 up, Vec2 bottom, int thickness, D3DCOLOR color);

private:
	LPDIRECT3DDEVICE9 pDevice;
};