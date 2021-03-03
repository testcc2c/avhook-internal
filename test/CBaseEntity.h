#pragma once
#include "offsets.h"
#include "Vec3.h"

class CBaseEntity
{
public:

	Vector3& get_origin()
	{
		return *reinterpret_cast<Vector3*>(reinterpret_cast<uintptr_t>(this) + 0x138);
	}

	union 
	{
		DEFINE_MEMBER_N(int, m_iHealth, netvars::m_iHealth);
		DEFINE_MEMBER_N(int, m_iTeamNum, netvars::m_iTeamNum);
		DEFINE_MEMBER_N(int, m_fFlags, netvars::m_fFlags);
		DEFINE_MEMBER_N(Vector3, m_vecOrigin, netvars::m_vecOrigin);
		DEFINE_MEMBER_N(int, m_iDefaultFOV, netvars::m_iDefaultFOV);
		DEFINE_MEMBER_N(int, m_iGlowIndex, netvars::m_iGlowIndex);
		DEFINE_MEMBER_N(int, m_ArmorValue, netvars::m_ArmorValue);

	};
};
