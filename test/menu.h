#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx9.h"

#include <d3d9.h>
#include <d3dx9.h>

#include "xorstr.h"
#include "ESPDrawer.h"

#include "memory.h"
#include "DX9ColorFix.h"

#include "MenuSettings.h"

#include "SDK.h"

#include <string>
#include <time.h>
#include "resource.h"

enum Icons : int
{
	PlayerListIcon        = 0,
	SettingsIcon		  = 1,
	AboutIcon			  = 2,
	CounterTerroristIcon  = 3,
	TerroristIcon		  = 4

};

class Menu
{
public:
	Menu(LPDIRECT3DDEVICE9 pDevice, HMODULE hmod, MenuSettings* settings);
	void Render();
	void Detach();
private:
	bool  render			= true;
	short menutab			= 0;
	bool  start_menu		= false;
	bool  about_menu		= false;
	bool  settings_menu		= false;
	bool  player_list		= false;

	const LPCSTR	  window_name = xorstr("Counter-Strike: Global Offensive");
	ImVec4*			  theme;
	ESPDrawer*		  drawlist;
	ImGuiIO			  io;
	HMODULE			  hmodule;
	LPDIRECT3DDEVICE9 pDevice;
	HWND			  window;
	ImVec4*			  theme;
	ImVec2			  window_size;
	IClientEntityList*entitylist;
	ClientBase*	      client;

	AimBotSettings*   aimbot_settings;
	GlowWHSettings*	  glow_esp_settings;
	SnapLinesESP*	  snap_esp_settings;
	BoxESP*			  box_esp_settings;
	PDIRECT3DTEXTURE9 logos[3];
	PDIRECT3DTEXTURE9 icons[5];

	ImVec2	GetWindowSize();
	std::string GetTime();

	void DrawStartMenu();
	void DrawAboutMenu();
	void DrawPlayerList();
	void DrawSettingsMenu();
	void DrawTaskBar();
};