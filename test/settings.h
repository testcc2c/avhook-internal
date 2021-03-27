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
	namespace aimbot
	{
		static bool on;
		static bool silent;
		static const char* hitboxes[] = { "Head", "Body", "Legs" };
		static int selectedhitbox;
	}

	namespace inGameWallHack
	{
		static bool on;
		static ImColor EnemyGlowColor = ImColor(1.f, 0.f, 0.f, 1.f);
		static ImColor FriedndlyGlowColor = ImColor(0.f, 1.f, 0.f, 1.f);
		static const char* glowmode[] = {"Custom", "Health"};
		static int selected_glow_mode;
	}
	namespace SnapLinesESP
	{
		static bool on;
		static ImColor Color = ImColor(1.f, 0.f, 0.f, 1.f);
		static const char* Bones[] = { "Head", "Body", "Legs" };
		static int thicnes = 1;
		static int selectedBoneId;
		static const char* colormode[] = { "Custom", "Health" };
		static int selected_colormode;
	}
	namespace BoxEsp
	{
		static bool on;
		static ImColor Color = ImColor(1.f, 0.f, 0.f, 1.f);
		static int thicnes = 2;

		static const char* colormode[] = { "Custom", "Health" };
		static int selected_colormode;
		static bool drawHpValue;
	}
	namespace SkeletonESP
	{
		static bool on;
		bool showbones;

		static ImColor Color = ImColor(1.f, 0.f, 0.f, 1.f);
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

	namespace misc
	{
		static bool nullcorelogo;
		static ImColor backgrooundcolor = ImColor(0, 0, 0, 90);
	}
	// misc sector
	static bool bhop;
	static bool thirdperson;
	
}