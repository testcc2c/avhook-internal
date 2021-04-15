#include "ESPDrawer.h"


void ESPDrawer::DrawBoxEsp(CBaseEntity* entity, int& thickness, ImColor color, bool drawHp)
{
    ClientBase* client = (ClientBase*)GetModuleHandle("client.dll");

    ImVec3 up = client->WorldToScreen(entity->m_vecOrigin);
    ImVec3 headpos = entity->GetBonePosition(BONE_HEAD); 
    headpos.z += 7.9;
    ImVec3 bottom = client->WorldToScreen(headpos);

    int height = ABS(up.y - bottom.y);

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

    if (drawHp)
    {
        bottomRight.x += 5;
        char buffer[256];
        _itoa_s(entity->m_iHealth, buffer, 10);
        this->AddText(bottomRight, entity->GetColorBasedOnHealth(), buffer);
    }
}

void ESPDrawer::DrawBonesNumbers(CBaseEntity* entity)
{
    ClientBase* client = (ClientBase*)GetModuleHandle("client.dll");
    
    char bon_id_char[20];
    for (int bone_id = 0; bone_id < 80; bone_id++)
    {

        sprintf_s(bon_id_char, "%d", bone_id);
        this->AddText(client->WorldToScreen(entity->GetBonePosition(bone_id)), ImColor(255, 255, 255), bon_id_char);

    }
}