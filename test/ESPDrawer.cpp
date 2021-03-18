#include "ESPDrawer.h"


void ESPDrawer::DrawBoxEsp(ImVec2& up, ImVec2& bottom, int& thickness, ImColor color)
{
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
}