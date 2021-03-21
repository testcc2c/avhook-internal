#pragma once
#include "offsets.h"
#include "viewmatrix.h"
#include "Windows.h"
#include "CBaseEntity.h"


class ClientBase
{
public:
	union
	{
		DEFINE_MEMBER_N(int, dwForceJump, signatures::dwForceJump);
		DEFINE_MEMBER_N(int, dwForceAttack, signatures::dwForceAttack);
		DEFINE_MEMBER_N(viewmatrix, dwViewmatrix, signatures::dwViewMatrix);

	};
	static ImVec3 WorldToScreen(const ImVec3 pos, viewmatrix matrix);


};