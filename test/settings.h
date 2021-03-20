#pragma once
#include "imgui/imgui.h"


namespace settings
{
	// menu
	static short int menu;
	static bool isOpen;
	static bool init;
	static bool attach = true;
	static bool render = true;
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
		static const char* glowmode[] = {"Custom", "Health"};
		static int selected_glow_mode;
	}
	namespace SnapLinesESP
	{
		static bool on;
		static ImVec4 Color = ImVec4(1.f, 0.f, 0.f, 1.f);
		static const char* Bones[] = { "Head", "Body", "Legs" };
		static int thicnes = 1;
		static int selectedBoneId;
		static const char* colormode[] = { "Custom", "Health" };
		static int selected_colormode;
	}
	namespace BoxEsp
	{
		static bool on;
		static ImVec4 Color = ImVec4(1.f, 0.f, 0.f, 1.f);
		static int thicnes = 1;

		static const char* colormode[] = { "Custom", "Health" };
		static int selected_colormode;
	}
	namespace SkeletonESP
	{
		static bool on;
		static ImVec4 Color = ImVec4(1.f, 0.f, 0.f, 1.f);
		static int thicnes = 1;

	}

	// trigger bot
	namespace trigger_bot
	{
		static bool on;
		static bool rage;
		static bool predict;

		static int delay = 0;
		static int predtime = 0;
	}


	// misc sector
	static bool bhop;
	static bool thirdperson;
	
}