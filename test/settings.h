#pragma once

namespace settings
{
	// menu
	short int menu;
	bool isOpen;
	bool init;

	// aimbot sector
	bool aimbot;
	bool silent;
	static const char* hitboxes[] = {"Head", "Body", "Legs"};
	static int selectedhitbox;

	// misc sector
	static bool bhop;
	static bool thirdperson;
	static bool airjump;
}