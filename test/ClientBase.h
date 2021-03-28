#pragma once
#include "offsets.h"
#include "viewmatrix.h"
#include "Windows.h"
#include "CBaseEntity.h"
#include "CLocalPlayer.h"


class ClientBase
{
public:
	union
	{
		DEFINE_MEMBER_N(int, dwForceJump, signatures::dwForceJump);
		DEFINE_MEMBER_N(int, dwForceAttack, signatures::dwForceAttack);
		DEFINE_MEMBER_N(viewmatrix, dwViewmatrix, signatures::dwViewMatrix);
		DEFINE_MEMBER_N(CLocalPlayer*, dwLocalPlayer, signatures::dwLocalPlayer);
		DEFINE_MEMBER_N(DWORD, dwGlowObjectManager, signatures::dwGlowObjectManager);
	};
	ImVec3 WorldToScreen(const ImVec3 pos);


};