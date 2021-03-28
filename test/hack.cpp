#include "hack.h"

Hack::Hack()
{
	this->clientbase = (ClientBase*)GetModuleHandle(L"client.dll");
	this->enginebase = (DWORD)GetModuleHandle(L"engine.dll");
}