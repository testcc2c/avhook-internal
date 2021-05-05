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
#include <shlobj_core.h>
enum Icons : int
{
	PlayerListIcon        = 0,
	SettingsIcon		  = 1,
	AboutIcon			  = 2,
	CounterTerroristIcon  = 3,
	TerroristIcon		  = 4

};
enum MenuTabs : int
{
	StartMenuTab = 0,
	AboutMenuTab = 1,
	SettingsMenuTab = 2,
	PlayerListTab = 3
};
enum SettingsIds : int
{
	AimbotSettingID = 0,
	GlowSettingID = 1,
	SnapLinesSettingsID = 2,
	BoxESPSettingsID = 3,
	MiscSettingsID = 4,
	TriggerBotSettingsID = 5,
	MenuSettingsID = 6
};
class Menu
{
public:
	Menu(LPDIRECT3DDEVICE9 pDevice, HMODULE hmod);
	void Render();
	void Detach();
	bool isOpen();
	bool isAttached();
	Settings* settings[7] = { new AimBotSettings(), new GlowWHSettings(), new SnapLinesESP(),
							  new BoxESP(),         new MiscSettings(),   new TriggerBotSetting(),
							  new MenuSettings()};
private:
	bool              render      = true;
	short             menutab     = 0;
	bool		      tabs[4]     = { false, false, false, false };
	bool			  active      = false;
	const LPCSTR	  window_name = xorstr("Counter-Strike: Global Offensive");
	ImVec4*			  theme;
	
	ESPDrawer*		  drawlist;
	ImGuiIO			  io;
	HMODULE			  hmodule;
	LPDIRECT3DDEVICE9 pDevice;
	HWND			  window;
	ImVec2			  window_size;
	IClientEntityList*entitylist;
	ClientBase*	      client;

	PDIRECT3DTEXTURE9 wallpaper_texture;

	PDIRECT3DTEXTURE9 logos[3], icons[5];

	ImVec2	GetWindowSize();
	std::string GetTime();

	void DrawStartMenu();
	void DrawAboutMenu();
	void DrawPlayerList();
	void DrawSettingsMenu();
	void DrawTaskBar();
	void DrawESP();
	std::string GetDesktopWallpaper();
};