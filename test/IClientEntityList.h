#pragma once
#include "CBaseEntity.h"
#include "memory.h"
class IClientEntityList
{
public:
	CBaseEntity* GetClientEntity(int entnum)
	{
		typedef CBaseEntity*(__thiscall* GetEntityFunc)(void*, int);
		return Memory::CallVFunction<GetEntityFunc>(this, 3)(this, entnum);
	}
};
