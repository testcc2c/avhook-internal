#include "hack.h"

Hack::Hack()
{
	this->clientbase = (DWORD)GetModuleHandle(L"client.dll");
	this->enginebase = (DWORD)GetModuleHandle(L"engine.dll");
}