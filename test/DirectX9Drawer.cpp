#include "DirectX9Drawer.h"

DirectX9Drawer::DirectX9Drawer(LPDIRECT3DDEVICE9 pDevice)
{
    this->pDevice = pDevice;
}

void DirectX9Drawer::DrawLine(int x1, int y1, int x2, int y2, int thickness, D3DCOLOR color)
{
    ID3DXLine* LineL;
    D3DXCreateLine(pDevice, &LineL);
    D3DXVECTOR2 Line[2];

    Line[0] = D3DXVECTOR2(x1, y1);
    Line[1] = D3DXVECTOR2(x2, y2);

    LineL->SetWidth(thickness);
    LineL->Draw(Line, 2, color);
    LineL->Release();
}