#pragma once

namespace settings
{
	// menu
	short int menu = 0;
	bool isOpen = false;

	// aimbot sector
	bool aimbot;
	bool silent;
	static const char* hitboxes[]{ "Head", "Chest", "Legs" };
	static int selectedhitbox;

	// misc sector
	bool bhop;
	bool thirdperson;

}