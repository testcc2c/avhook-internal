#pragma once
#include "imgui/imgui.h"
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
	bool GlowWh = false;

	// esp glow sector

	ImVec4 EnemyGlowColor = ImVec4(1.f, 0.f, 0.f, 1.f);
	ImVec4 FriedndlyGlowColor = ImVec4(0.f, 1.f, 0.f, 1.f);

	// misc sector
	bool bhop;
	bool thirdperson;
	bool airjump;
	
}