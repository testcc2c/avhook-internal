#include <Windows.h>

#include <d3d9.h>
#include <d3dx9.h>

#include <D3dx9tex.h>

#include "ESPDrawer.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx9.h"

#include "settings.h"
#include "DX9ColorFix.h"

#include "bhop.h"
#include "GlowWhInGame.h"
#include "CBaseEntity.h"
#include "CLocalPlayer.h"
#include "TriggerBot.h"


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <shellapi.h>
#include <time.h>
#include <shlobj_core.h>

#include "DirectX9VTableCreator.h"
#include "memory.h"
#include "SDK.h"
#include "resource.h"
#include "xorstr.h"
#include "menu.h"


typedef long(__stdcall* EndScene)(LPDIRECT3DDEVICE9);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

EndScene		  oEndScene;
WNDPROC			  oWndProc;
HMODULE			  hmodule;

Menu* menu = nullptr;

long __stdcall hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{

	if (!menu)
		menu = new Menu(pDevice, hmodule, new MenuSettings());
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
	DWORD end_scene_addr = (DWORD)(GetModuleHandle("d3d9.dll")) + 0x63130;
	BYTE end_scene_bytes[7] = { 0 };

	//DirectX9VTableCreator dx9;

	// dx9.GetD3D9Device(d3dDevice, sizeof(d3dDevice), window)
	HWND window = FindWindowA(NULL, WINDOW_NAME);

	if (window)
	{
		Memory mem;
		//DWORD end_scene_addr_sig = mem.FindPattern("client.dll", "\x6A\x00\xB8\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x8B\x7D\x00\x8B\xDF\x8D\x47\x00\xF7\xDB\x1B\xDB\x23\xD8\x89\x5D\x00\x33\xF6\x89\x75\x00\x39\x73\x00\x75", "x?x????x????xx?xxxx?xxxxxxxx?xxxx?xx?x");
		oWndProc = (WNDPROC)SetWindowLongPtr(window, GWL_WNDPROC, (LONG_PTR)WndProc);
		settings::attach = true;
		PlaySound(xorstr("avhook\\sounds\\activated.wav"), NULL, SND_ASYNC);
		memcpy(end_scene_bytes, (char*)end_scene_addr, 7);

		oEndScene = (EndScene)mem.trampHook32((char*)end_scene_addr, (char*)hkEndScene, 7);
		

		while (!GetAsyncKeyState(VK_END))
		{
			Sleep(500);
		}

		PlaySound(xorstr("avhook\\sounds\\deactivated.wav"), NULL, SND_ASYNC);

		menu->Detach();

		SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)oWndProc);

		mem.patch((BYTE*)(end_scene_addr), end_scene_bytes, 7);
		Sleep(5000);

	}
	FreeLibraryAndExitThread(hModule, NULL);
}

DWORD WINAPI Bhop(HMODULE hModule)
{
	BunnyHop bhop;
	while (settings::attach)
	{
		if (!settings::bhop)
			Sleep(500);
		else if (GetAsyncKeyState(VK_SPACE))
			bhop.HandleBhop();
	}
	ExitThread(0);
}

DWORD WINAPI InGameGlowWH(HMODULE hModule)
{
	InGameGlowEsp esp = InGameGlowEsp(&settings::inGameWallHack::selected_glow_mode);

	while (settings::attach)
	{
		if (settings::inGameWallHack::on)
			esp.HandleGlow(settings::inGameWallHack::EnemyGlowColor, settings::inGameWallHack::FriedndlyGlowColor);
		else
			Sleep(500);
	}
	ExitThread(0);
}

DWORD WINAPI Trigger(HMODULE hModule)
{
	using namespace settings::trigger_bot;
	TriggerBot triggerbot(&delay, &rage);

	while (settings::attach)
	{
		if (on and GetAsyncKeyState(VK_XBUTTON1))
			triggerbot.Handle();
		else
			Sleep(100);
	}
	ExitThread(0);
}

DWORD WINAPI AimBot(HMODULE hModule)
{
	int bone = 8;
	CBaseEntity* ent;
	IClientEntityList* entitylist = (IClientEntityList*)GetInterface(xorstr("client.dll"), xorstr("VClientEntityList003"));
	ClientBase* client = (ClientBase*)GetModuleHandle(xorstr("client.dll"));

	while (settings::attach)
	{
		__try
		{

			if (!settings::aimbot::on)
			{
				Sleep(500);
				continue;
			}
			CLocalPlayer* localPlayer = *(CLocalPlayer**)((DWORD)client + signatures::dwLocalPlayer);
			switch (settings::aimbot::selectedhitbox)
			{
			case 0:
				bone = BONE_HEAD;
				break;
			case 1:
				bone = BONE_BODY;
				break;
			case 2:
				bone = BONE_LEGS;
				break;
			}

			ent = localPlayer->GetClosestTarget(settings::aimbot::fov, bone);
			// 17000.f - збс
			localPlayer->AimAt(ent, bone);
			if (settings::aimbot::autoshoot and entitylist->GetClientEntity(localPlayer->m_iCrosshairId) == ent)
			{
				client->dwForceAttack = 6;
				Sleep(10);
			
			}
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{

		}

	}
	ExitThread(0);
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{

	case DLL_PROCESS_ATTACH:
		hmodule = hModule;
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)EntryPoint,   hModule, 0, nullptr);
		//CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Bhop,		   hModule, 0, nullptr);
		//CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)InGameGlowWH,   hModule, 0, nullptr);
		//CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Trigger,	       hModule, 0, nullptr);
		//CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)AimBot,         hModule, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}