#pragma once
#include <Windows.h>
#include "ClientBase.h"

class Hack
{
public:
	Hack();

protected:
	ClientBase* clientbase;
	DWORD enginebase;

};
