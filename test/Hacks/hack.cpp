#include "hack.h"

Hack::Hack()
{
	this->clientbase  = reinterpret_cast<ClientBase*>(GetModuleHandle(xorstr("client.dll")));
	this->enginebase  = reinterpret_cast<DWORD>(GetModuleHandle(xorstr("engine.dll")));
	this->entity_list = GetInterface<IClientEntityList>(xorstr("client.dll"), xorstr("VClientEntityList003"));
}