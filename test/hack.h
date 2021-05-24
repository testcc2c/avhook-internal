#pragma once
#include <Windows.h>
#include "ClientBase.h"
#include "MenuSettings.h"
class Hack
{
public:
	Hack();

protected:
	ClientBase* clientbase;
	DWORD       enginebase;
	IClientEntityList* entity_list;
};
