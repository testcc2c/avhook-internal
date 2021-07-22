#pragma once
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_win32.h"
#include "../imgui/imgui_impl_dx9.h"

#include <d3d9.h>
#include <d3dx9.h>

#include "../Utils/xorstr.h"
#include "../Hacks/ESPDrawer.h"

#include "../Utils/memory.h"
#include "../DirctX/DX9ColorFix.h"

#include "../Menu/MenuSettings.h"

#include "../SDK/SDK.h"

#include <string>
#include <time.h>
#include "../resource.h"
#include <shlobj_core.h>

enum Icons : int
{
	PlayerListIcon        = 0,
	SettingsIcon		  = 1,
	AboutIcon			  = 2,
	CounterTerroristIcon  = 3,
	TerroristIcon		  = 4,
	RadarIcon			  = 5
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
	AimbotSettingID,
	GlowSettingID,
	SnapLinesSettingsID,
	BoxESPSettingsID,
	MiscSettingsID,
	TriggerBotSettingsID,
	MenuSettingsID,
	RadarSettingsID
};
class Menu
{
public:
	Menu(LPDIRECT3DDEVICE9& pDevice, HMODULE& hmod);
	void Render();
	void Detach();
	bool isOpen();
	bool isAttached();
	Settings* settings[8] = { new AimBotSettings(), new GlowWHSettings(), new SnapLinesESP(),
							  new BoxESP(),         new MiscSettings(),   new TriggerBotSetting(),
							  new MenuSettings(),   new RadarSettings()};

private:
	bool               render      = true;
	short              menutab     = 0;
	bool		       tabs[4]     = { false, false, false, false };
	bool			   active	   = false;

	const LPCSTR	   window_name = xorstr("Counter-Strike: Global Offensive");

	ImVec4*			   theme;
	ESPDrawer*		   drawlist;
	ImGuiIO			   io;
	HMODULE			   hmodule;
	LPDIRECT3DDEVICE9  pDevice;
	HWND			   window;
	ImVec2			   window_size;
	IClientEntityList* entitylist;
	ClientBase*	       client;
	DX9ColorFix*	   colorfix;
	PDIRECT3DTEXTURE9  wallpaper_texture;

	ImColor		       active_radar_color   = ImColor(255, 0, 0);
	ImColor		       inactive_radar_color = ImColor(255, 255, 255);
	PDIRECT3DTEXTURE9 icons[6];

	ImVec2	     GetWindowSize();
	std::string  GetTime();

	void	     DrawStartMenu();
	void		 DrawAboutMenu();
	void		 DrawPlayerList();
	void		 DrawSettingsMenu();
	void	     DrawTaskBar();
	void		 DrawESP();
	void		 DrawRadar();

	std::string GetDesktopWallpaper();
};