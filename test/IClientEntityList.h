#pragma once
#include "CBaseEntity.h"
#include "AbstractInterface.h"
#include "memory.h"

class IClientEntityList : public AbstractInterface
{
public:
	CBaseEntity* GetClientEntity(int entnum)
	{
		typedef CBaseEntity*(__thiscall* GetEntityFunc)(void*, int);
		return this->GetVirtualFunction<GetEntityFunc>(3)(this, entnum);
	}
};
