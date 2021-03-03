#pragma once
#include "offsets.h"
#include "Vec3.h"

class CBaseEntity
{
public:
	union 
	{
		DEFINE_MEMBER_N(int, m_iTeamNum, netvars::m_iTeamNum);
		DEFINE_MEMBER_N(int, m_iHealth, netvars::m_iHealth);
		DEFINE_MEMBER_N(int, m_fFlags, netvars::m_fFlags);
		DEFINE_MEMBER_N(int, m_iDefaultFOV, netvars::m_iDefaultFOV);
		DEFINE_MEMBER_N(int, m_iGlowIndex, netvars::m_iGlowIndex);
		DEFINE_MEMBER_N(int, m_ArmorValue, netvars::m_ArmorValue);
		DEFINE_MEMBER_N(int, m_iCrosshairId, netvars::m_iCrosshairId);

	};
	Vector3 getOrigin()
	{
		DWORD player = *(DWORD*)((DWORD)GetModuleHandle(L"client.dll") + signatures::dwLocalPlayer);

		Vector3 pos = *(Vector3*)(player + 0x138);

		return pos;
	}
private:
	DWORD baseAddr;

};
