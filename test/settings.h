#pragma once
#include "imgui/imgui.h"


namespace settings
{
	// menu
	static short int menu;
	static bool isOpen;
	static bool init;
	static bool attach = true;

	// aimbot sector
	static bool aimbot;
	static bool silent;
	static const char* hitboxes[] = {"Head", "Body", "Legs"};
	static int selectedhitbox;

	namespace inGameWallHack
	{
		static bool on;
		static ImVec4 EnemyGlowColor = ImVec4(1.f, 0.f, 0.f, 1.f);
		static ImVec4 FriedndlyGlowColor = ImVec4(0.f, 1.f, 0.f, 1.f);
		static const char* glowmode[] = {"Seted Color", "Health"};
		static int selected_glow_mode;
	}
	namespace SnapLinesESP
	{
		static bool on;
		static ImVec4 Color = ImVec4(1.f, 0.f, 0.f, 1.f);
	}

	// trigger bot
	namespace trigger_bot
	{
		static bool on;
	}


	// misc sector
	static bool bhop;
	static bool thirdperson;
	static bool airjump;
	
}