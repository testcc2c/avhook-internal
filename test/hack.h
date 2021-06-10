#pragma once
#include <Windows.h>
#include "ClientBase.h"
#include "MenuSettings.h"

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
