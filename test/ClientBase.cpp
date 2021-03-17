#include "ClientBase.h"


Vec3 ClientBase::WorldToScreen(int width, int height, const Vec3 pos, viewmatrix matrix)
{
    float _x = matrix[0][0] * pos.x + matrix[0][1] * pos.y + matrix[0][2] * pos.z + matrix[0][3];
    float _y = matrix[1][0] * pos.x + matrix[1][1] * pos.y + matrix[1][2] * pos.z + matrix[1][3];
    float _z = matrix[2][0] * pos.x + matrix[2][1] * pos.y + matrix[2][2] * pos.z + matrix[2][3];
    float w = matrix[3][0] * pos.x + matrix[3][1] * pos.y + matrix[3][2] * pos.z + matrix[3][3];


    float x = (width / 2 * (_x / w)) + ((_x / w) + width / 2);

    float y = -(height / 2 * (_y / w)) + ((_y / w) + height / 2);

    return Vec3(x, y, w);
}