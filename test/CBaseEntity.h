#pragma once
#include "offsets.h"
#include "Vec3.h"
#include <Windows.h>
#include "imgui/imgui.h"
#include "TraceLine.h"
#include "types.h"
#include "xorstr.h"
#include "IClientEntityList.h"

class CBaseEntity
{
public:

	union 
	{
		DEFINE_MEMBER_N(int, m_iTeamNum, netvars::m_iTeamNum);
		DEFINE_MEMBER_N(int, m_iHealth, netvars::m_iHealth);
		DEFINE_MEMBER_N(int, m_iTeamNum, netvars::m_iTeamNum);
		DEFINE_MEMBER_N(int, m_fFlags, netvars::m_fFlags);
		DEFINE_MEMBER_N(int, m_iDefaultFOV, netvars::m_iDefaultFOV);
		DEFINE_MEMBER_N(int, m_iGlowIndex, netvars::m_iGlowIndex);
		DEFINE_MEMBER_N(int, m_ArmorValue, netvars::m_ArmorValue);
		DEFINE_MEMBER_N(int, m_iCrosshairId, netvars::m_iCrosshairId);
		DEFINE_MEMBER_N(ImVec3, m_vecViewOffset, netvars::m_vecViewOffset);
		DEFINE_MEMBER_N(ImVec3, m_vecOrigin, netvars::m_vecOrigin);
		DEFINE_MEMBER_N(DWORD, boneMatrix, netvars::m_dwBoneMatrix);
		DEFINE_MEMBER_N(ImVec3, m_vecVelocity, netvars::m_vecVelocity);
		DEFINE_MEMBER_N(bool, m_bDormant, signatures::m_bDormant);
	};
	// Get position of bone like head, pelvis and etc...
	ImVec3 GetBonePosition(int bone);
	// Calc distance to entity
	float CalcDistaceToEntity(CBaseEntity* entity);
	CBaseEntity* GetClosestEntity();
	//Get color based on entity health
	ImColor GetColorBasedOnHealth();
	// Get entity camera position
	ImVec3 GetCameraPosition();
	
private:
	const DWORD invalid_entity = 0xCCCCCCCC;
};