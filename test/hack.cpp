#include "hack.h"

Hack::Hack()
{
	this->clientbase = (ClientBase*)GetModuleHandle("client.dll");
	this->enginebase = (DWORD)GetModuleHandle("engine.dll");
	this->entity_list = GetInterface<IClientEntityList>(xorstr("client.dll"), xorstr("VClientEntityList003"));
}