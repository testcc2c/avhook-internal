#include "ESPDrawer.h"
#include "ClientBase.h"


// Simple helper function to load an image into a DX9 texture with common settings

void ESPDrawer::DrawBoxEsp(CBaseEntity* entity, int& thickness, ImColor color)
{
    ClientBase* client = (ClientBase*)GetModuleHandle(L"client.dll");

    ImVec3 up = client->WorldToScreen(entity->m_vecOrigin, client->dwViewmatrix);
    ImVec3 headpos = entity->GetBonePosition(BONE_HEAD); 
    headpos.z += 7.9;
    ImVec3 bottom = client->WorldToScreen(headpos, client->dwViewmatrix);

    int height = ABS(up.y - bottom.y);

    char buffer[256];
    _itoa_s(entity->m_iHealth, buffer, 10);


    ImVec2 topleft, topright;
    ImVec2 bottomLeft, bottomRight;

    topleft.x = up.x - height / 4;
    topright.x = up.x + height / 4;
    topleft.y = topright.y = up.y;

    bottomLeft.x = bottom.x - height / 4;
    bottomRight.x = bottom.x + height / 4;
    bottomLeft.y = bottomRight.y = bottom.y;

    this->AddLine(topleft, topright, color, thickness);
    this->AddLine(bottomLeft, bottomRight, color, thickness);
    this->AddLine(topleft, bottomLeft, color, thickness);
    this->AddLine(topright, bottomRight, color, thickness);

    bottomRight.x += 5;
    this->AddText(bottomRight, entity->GetColorBasedOnHealth(), buffer);
}