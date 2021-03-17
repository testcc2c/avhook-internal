#include "DirectX9Drawer.h"

DirectX9Drawer::DirectX9Drawer(LPDIRECT3DDEVICE9 pDevice)
{
    this->pDevice = pDevice;
}

void DirectX9Drawer::DrawLine(Vec2 &pos1, Vec2& pos2, int thickness, D3DCOLOR color)
{
    ID3DXLine* LineL;
    D3DXCreateLine(this->pDevice, &LineL);
    D3DXVECTOR2 Line[2];

    Line[0] = D3DXVECTOR2(pos1.x, pos1.y);
    Line[1] = D3DXVECTOR2(pos2.x, pos2.y);

    LineL->SetWidth(thickness);
    LineL->Draw(Line, 2, color);
    LineL->Release();
}
void DirectX9Drawer::DrawFilledRect(int x, int y, int w, int h, D3DCOLOR color)
{
    D3DRECT rect = { x, y, x + w, y + h };
    this->pDevice->Clear(TRUE, &rect, D3DCLEAR_TARGET, color, 0.f, 0);
}
void DirectX9Drawer::DrawEmptyRect(Vec2 top, Vec2 bottom, int thickness, D3DCOLOR color)
{
    int height = ABS(top.y - bottom.y);

    Vec2 topleft, topright;
    Vec2 bottomLeft, bottomRight;

    topleft.x = top.x - height / 4;
    topright.x = top.x + height / 4;
    topleft.y = topright.y = top.y;

    bottomLeft.x = bottom.x - height / 4;
    bottomRight.x = bottom.x + height / 4;
    bottomLeft.y = bottomRight.y = bottom.y;

    this->DrawLine(topleft, topright, thickness, color);
    this->DrawLine(bottomLeft, bottomRight, thickness, color);
    this->DrawLine(topleft, bottomLeft, thickness, color);
    this->DrawLine(topright, bottomRight, thickness, color);
}