#include "DirectX9Drawer.h"

DirectX9Drawer::DirectX9Drawer(LPDIRECT3DDEVICE9 pDevice)
{
    this->pDevice = pDevice;
}

void DirectX9Drawer::DrawLine(int x1, int y1, int x2, int y2, int thickness, D3DCOLOR color)
{
    ID3DXLine* LineL;
    D3DXCreateLine(this->pDevice, &LineL);
    D3DXVECTOR2 Line[2];

    Line[0] = D3DXVECTOR2(x1, y1);
    Line[1] = D3DXVECTOR2(x2, y2);

    LineL->SetWidth(thickness);
    LineL->Draw(Line, 2, color);
    LineL->Release();
}
void DirectX9Drawer::DrawFilledRect(int x, int y, int w, int h, D3DCOLOR color)
{
    D3DRECT rect = { x, y, x + w, y + h };
    this->pDevice->Clear(TRUE, &rect, D3DCLEAR_TARGET, color, 0.f, 0);
}