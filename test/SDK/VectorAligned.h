#pragma once
#include "../Utils/Vec3.h"

#define DECL_ALIGN(x) __declspec(align(x))
#define ALIGN16 DECL_ALIGN(16)
#define ALIGN16_POST DECL_ALIGN(16)

class ALIGN16 VectorAligned : public ImVec3
{
public:
    inline VectorAligned(void) {};

    inline VectorAligned(ImVec3 X, ImVec3 Y, ImVec3 Z)
    {
        //Init(X, Y, Z);
    }

    explicit VectorAligned(const ImVec3& vOther)
    {
        this->Init(vOther.x, vOther.y, vOther.z);
    }

    VectorAligned& operator=(const ImVec3& vOther)
    {
        Init(vOther.x, vOther.y, vOther.z);
        return *this;
    }

    float w = 0;	// this space is used anyway
} ALIGN16_POST;