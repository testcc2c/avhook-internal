#pragma once
#include <Windows.h>
#include "../SDK/SDK.h"
#include "../Menu/MenuSettings.h"
#include "../Utils/xorstr.h"

class Hack
{
public:
	Hack();
	virtual void Work() = 0;
protected:
	ClientBase*		   clientbase;
	DWORD			   enginebase;
	IClientEntityList* entity_list;
	
};
