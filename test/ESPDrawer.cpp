#include "ESPDrawer.h"


void ESPDrawer::DrawBoxEsp(CBaseEntity* entity, int& thickness, ImColor color, bool drawHp)
{
    ClientBase* client = reinterpret_cast<ClientBase*>(GetModuleHandle("client.dll"));

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

    this->AddRect(topleft, bottomRight, color, 0, 0, thickness);

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
    ClientBase* client = reinterpret_cast<ClientBase*>(GetModuleHandle("client.dll"));
    
    char bon_id_char[20];
    for (int bone_id = 0; bone_id < 80; bone_id++)
    {

        sprintf_s(bon_id_char, "%d", bone_id);
        this->AddText(client->WorldToScreen(entity->GetBonePosition(bone_id)), ImColor(255, 255, 255), bon_id_char);

    }
}

void ESPDrawer::DrawSkeleton(CBaseEntity* entity, ImColor &color, int &thicknes)
{
    ClientBase* client = reinterpret_cast<ClientBase*>(GetModuleHandle("client.dll"));
    ImVec3 bones[]{
    client->WorldToScreen(entity->GetBonePosition(8)),
    client->WorldToScreen(entity->GetBonePosition(7)),
    client->WorldToScreen(entity->GetBonePosition(11)),
    client->WorldToScreen(entity->GetBonePosition(12)),
    client->WorldToScreen(entity->GetBonePosition(3)),
    client->WorldToScreen(entity->GetBonePosition(39)),
    client->WorldToScreen(entity->GetBonePosition(73)),
    client->WorldToScreen(entity->GetBonePosition(66)),
    client->WorldToScreen(entity->GetBonePosition(40)),
    client->WorldToScreen(entity->GetBonePosition(74)),
    client->WorldToScreen(entity->GetBonePosition(67)) 
    };

    this->AddLine(bones[0], bones[1],  color, thicknes);
    this->AddLine(bones[1], bones[2],  color, thicknes);
    this->AddLine(bones[1], bones[5],  color, thicknes);
    this->AddLine(bones[2], bones[3],  color, thicknes);
    this->AddLine(bones[5], bones[8],  color, thicknes);

    this->AddLine(bones[1],  bones[4],  color, thicknes);
    this->AddLine(bones[4],  bones[6],  color, thicknes);
    this->AddLine(bones[4],  bones[7],  color, thicknes);
    this->AddLine(bones[6],  bones[9],  color, thicknes);
    this->AddLine(bones[7],  bones[10], color, thicknes);

    this->AddLine(bones[9],  client->WorldToScreen(entity->GetBonePosition(75)), color, thicknes);
    this->AddLine(bones[10], client->WorldToScreen(entity->GetBonePosition(68)), color, thicknes);
    this->AddLine(bones[3],  client->WorldToScreen(entity->GetBonePosition(13)), color, thicknes);
    this->AddLine(bones[8],  client->WorldToScreen(entity->GetBonePosition(41)), color, thicknes);
}