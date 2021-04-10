#include "hack.h"

Hack::Hack()
{
	this->clientbase = (ClientBase*)GetModuleHandle("client.dll");
	this->enginebase = (DWORD)GetModuleHandle("engine.dll");
}