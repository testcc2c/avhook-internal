#pragma once

namespace settings
{
	// menu
	short int menu;
	bool isOpen;
	bool init;
	bool attach = true;
	// aimbot sector
	bool aimbot;
	bool silent;
	const char* hitboxes[] = {"Head", "Body", "Legs"};
	int selectedhitbox;
	
	// misc sector
	bool bhop;
	bool thirdperson;
	bool airjump;
	
}