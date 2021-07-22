#include <Windows.h>

#include <d3d9.h>
#include <d3dx9.h>

#include <d3dx9tex.h>

#include "Hacks/ESPDrawer.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx9.h"

#include "DirctX/DX9ColorFix.h"

#include "Hacks/bhop.h"
#include "Hacks/GlowWhInGame.h"
#include "Hacks/AimBot.h"
#include "Hacks/TriggerBot.h"
#include "SDK/SDK.h"


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <shellapi.h>
#include <time.h>
#include <shlobj_core.h>

#include "resource.h"
#include "Utils/memory.h"
#include "Menu/menu.h"
#include "Utils/offsets.h"
#include "Utils/GetInterface.h"

#define ANTI_DEBUG_PROTECTION 0;

typedef long(__stdcall* EndScene)(LPDIRECT3DDEVICE9);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

EndScene		  oEndScene;
WNDPROC			  oWndProc;
HMODULE			  hmodule;
Menu*             menu = nullptr;

long __stdcall hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{

	if (!menu)
		menu = new Menu(pDevice, hmodule);
	menu->Render();                                 

	return oEndScene(pDevice);
}



LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
	if (menu->isOpen())
	{
		ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
		return TRUE;
	}
	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

DWORD WINAPI EntryPoint(HMODULE hModule)
{
	//void* d3dDevice[119];
	DWORD end_scene_addr = (DWORD)(GetModuleHandle(xorstr("d3d9.dll"))) + 0x63130;
	BYTE end_scene_bytes[7] = { 0 };

	//DirectX9VTableCreator dx9;

	// dx9.GetD3D9Device(d3dDevice, sizeof(d3dDevice), window)
	HWND window = FindWindowA(NULL, WINDOW_NAME);


	if (window)
	{
		Memory mem;
		//DWORD end_scene_addr_sig = mem.FindPattern("client.dll", "\x6A\x00\xB8\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x8B\x7D\x00\x8B\xDF\x8D\x47\x00\xF7\xDB\x1B\xDB\x23\xD8\x89\x5D\x00\x33\xF6\x89\x75\x00\x39\x73\x00\x75", "x?x????x????xx?xxxx?xxxxxxxx?xxxx?xx?x");
		oWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(window, GWL_WNDPROC, reinterpret_cast<LONG_PTR>(WndProc)));
		PlaySound(xorstr("avhook\\sounds\\activated.wav"), NULL, SND_ASYNC);
		memcpy(end_scene_bytes, reinterpret_cast<char*>(end_scene_addr), 7);

		oEndScene = (EndScene)mem.trampHook32(reinterpret_cast<char*>(end_scene_addr), reinterpret_cast<char*>(hkEndScene), 7);
		

		while (!GetAsyncKeyState(VK_END))
		{
#if ANTI_DEBUG_PROTECTION
			if (IsDebuggerPresent())
				TerminateProcess(GetCurrentProcess(), 0);
#endif // ANTI_DEBUG_PROTECTION
			Sleep(500);
		}

		PlaySound(xorstr("avhook\\sounds\\deactivated.wav"), NULL, SND_ASYNC);

		menu->Detach();
		SetWindowLongPtr(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(oWndProc));

		mem.patch(reinterpret_cast<BYTE*>(end_scene_addr), end_scene_bytes, 7);
		Sleep(5000);

	}
	FreeLibraryAndExitThread(hModule, NULL);
}

DWORD WINAPI Bhop(HMODULE hModule)
{
	BunnyHop bhop;
	while (!menu)
		Sleep(100);
	MiscSettings* settings = dynamic_cast<MiscSettings*>(menu->settings[MiscSettingsID]);

	while (menu->isAttached())
	{
		if (!settings->bhop)
			Sleep(500);
		else if (GetAsyncKeyState(VK_SPACE))
			bhop.Work();
	}
	ExitThread(0);
}

DWORD WINAPI InGameGlowWH(HMODULE hModule)
{
	while (!menu)
		Sleep(100);

	InGameGlowEsp esp = InGameGlowEsp(dynamic_cast<GlowWHSettings*>(menu->settings[GlowSettingID]));
	while (menu->isAttached())
	{
		if (esp.settings->active)
			esp.Work();
		else
			Sleep(500);
	}
	ExitThread(0);
}

DWORD WINAPI Trigger(HMODULE hModule)
{
	while (!menu)
		Sleep(100);

	TriggerBot triggerbot(dynamic_cast<TriggerBotSetting*>(menu->settings[TriggerBotSettingsID]));

	while (menu->isAttached())
	{
		if (triggerbot.settings->active and GetAsyncKeyState(VK_XBUTTON1))
			triggerbot.Work();
		else
			Sleep(100);
	}
	ExitThread(0);
}

DWORD WINAPI AimBotThread(HMODULE hModule)
{
	while (!menu)
		Sleep(100);
	
	AimBot aimbot = AimBot(dynamic_cast<AimBotSettings*>(menu->settings[AimbotSettingID]));

	while (menu->isAttached())
	{
		aimbot.Work();
	}

	ExitThread(0);
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	hmodule = hModule;

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)EntryPoint,   hModule, 0, nullptr);
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Bhop,         hModule, 0, nullptr);
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)InGameGlowWH, hModule, 0, nullptr);
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Trigger,	   hModule, 0, nullptr);
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)AimBotThread, hModule, 0, nullptr);
	}
	return TRUE;
}