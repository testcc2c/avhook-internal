#include "ClientBase.h"


ImVec3 ClientBase::WorldToScreen(const ImVec3 pos)
{
    RECT rect;

    GetWindowRect(FindWindowA(NULL, WINDOW_NAME), &rect);

    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;
    
    float _x = this->dwViewmatrix[0][0] * pos.x + this->dwViewmatrix[0][1] * pos.y + this->dwViewmatrix[0][2] * pos.z + this->dwViewmatrix[0][3];
    float _y = this->dwViewmatrix[1][0] * pos.x + this->dwViewmatrix[1][1] * pos.y + this->dwViewmatrix[1][2] * pos.z + this->dwViewmatrix[1][3];
    float _z = this->dwViewmatrix[2][0] * pos.x + this->dwViewmatrix[2][1] * pos.y + this->dwViewmatrix[2][2] * pos.z + this->dwViewmatrix[2][3];
    float w =  this->dwViewmatrix[3][0] * pos.x + this->dwViewmatrix[3][1] * pos.y + this->dwViewmatrix[3][2] * pos.z + this->dwViewmatrix[3][3];


    float x = (width / 2 * (_x / w)) + ((_x / w) + width / 2);

    float y = -(height / 2 * (_y / w)) + ((_y / w) + height / 2);

    return ImVec3(x, y, w);
}

bool ClientBase::IsEntityVisible(CBaseEntity* entity)
{

    IEngineTrace* EngineTrace = GetInterface<IEngineTrace>(xorstr("engine.dll"), xorstr("EngineTraceClient004"));
    CGameTrace	  trace;
    Ray_t		  ray;
    CTraceFilter  tracefilter;

    tracefilter.pSkip = reinterpret_cast<void*>(this->dwLocalPlayer);

    ray.Init(this->dwLocalPlayer->GetCameraPosition(), entity->GetCameraPosition());

    EngineTrace->TraceRay(ray, MASK_SHOT | CONTENTS_GRATE, &tracefilter, &trace);

    if (this == trace.hit_entity)
        return true;
    return false;
}
