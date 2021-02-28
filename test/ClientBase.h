#pragma once
#include "offsets.h"

class ClientBase
{
public:
	union
	{
		DEFINE_MEMBER_N(int, dwForceJump, signatures::dwForceJump);
		DEFINE_MEMBER_N(int, dwForceAttack, signatures::dwForceAttack);
	};
};