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

#pragma comment(lib, "D3dx9")
#pragma comment(lib, "winmm")


typedef long(__stdcall* EndScene)(LPDIRECT3DDEVICE9);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

EndScene		  oEndScene;
WNDPROC			  oWndProc;
ClientBase*		  client;
HMODULE			  hmodule;
PDIRECT3DTEXTURE9 logos[3];
PDIRECT3DTEXTURE9 icons[5];


inline void InitImGui(LPDIRECT3DDEVICE9 pDevice)
{

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;

	io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Impact.ttf", 17.0f, 0);

	ImGui_ImplWin32_Init(FindWindowA(NULL, WINDOW_NAME));
	ImGui_ImplDX9_Init(pDevice);

	ImVec4* theme = ImGui::GetStyle().Colors;
	theme[ImGuiCol_WindowBg] = ImVec4(0.137f, 0.152f, 0.164f, 1.f);
	theme[ImGuiCol_Button] = ImVec4(1.f, 0.372f, 0.372f, 1.f);
	theme[ImGuiCol_Tab] = ImVec4(1.f, 0.372f, 0.372f, 1.f);
	theme[ImGuiCol_SeparatorActive] = ImVec4(1.f, 0.372f, 0.372f, 1.f);
	theme[ImGuiCol_Border] = ImVec4(1.f, 0.372f, 0.372f, 1.f);
	theme[ImGuiCol_Text] = ImVec4(1.f, 1.f, 1.f, 1.f);
	theme[ImGuiCol_ButtonActive] = ImVec4(1.f, 0.57f, 0.57f, 1.f);
	theme[ImGuiCol_ButtonHovered] = ImVec4(1.f, 0.4f, 0.4f, 1.f);
	theme[ImGuiCol_CheckMark] = ImVec4(1.f, 0.372f, 0.372f, 1.f);
	theme[ImGuiCol_TextSelectedBg] = ImVec4(1.f, 0.372f, 0.372f, 1.f);
	theme[ImGuiCol_FrameBg] = ImVec4(0.31f, 0.31f, 0.31f, 1.f);
	theme[ImGuiCol_FrameBgActive] = ImVec4(1.f, 0.57f, 0.57f, 1.f);
	theme[ImGuiCol_FrameBgHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.f);
	theme[ImGuiCol_PopupBg] = ImVec4(0.137f, 0.152f, 0.164f, 1.f);
	theme[ImGuiCol_ScrollbarBg] = ImVec4(1.f, 0.372f, 0.372f, 0.f);
	theme[ImGuiCol_ScrollbarGrab] = ImVec4(1.f, 0.372f, 0.372f, 1.f);
	theme[ImGuiCol_SliderGrab] = ImVec4(1.f, 0.372f, 0.372f, 1.f);
	theme[ImGuiCol_SliderGrabActive] = ImVec4(1.f, 0.372f, 0.372f, 1.f);
	theme[ImGuiCol_TabHovered] = ImVec4(1.f, 0.57f, 0.57f, 1.f);
	theme[ImGuiCol_TabActive] = ImVec4(1.f, 0.372f, 0.372f, 1.f);
}

long __stdcall hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{
	if (!settings::attach)
		return oEndScene(pDevice);

	IClientEntityList* entitylist = (IClientEntityList*)GetInterface(xorstr("client.dll"), xorstr("VClientEntityList003"));
	
	if (!settings::menu::init)
	{
		TCHAR path[256];
		SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, NULL, path);

		std::string path_to_wp = std::string(path);
		path_to_wp += "\\Microsoft\\Windows\\Themes\\TranscodedWallpaper";

		InitImGui(pDevice);
		D3DXCreateTextureFromResourceA(pDevice, hmodule, MAKEINTRESOURCE(AV_LOGO), &logos[0]);

		D3DXCreateTextureFromFileA(pDevice, path_to_wp.c_str(), &logos[2]);

		D3DXCreateTextureFromResourceA(pDevice, hmodule, MAKEINTRESOURCE(PLAYER_LIST_ICON), &icons[0]);
		D3DXCreateTextureFromResourceA(pDevice, hmodule, MAKEINTRESOURCE(SETTINGS_ICON), &icons[1]);
		D3DXCreateTextureFromResourceA(pDevice, hmodule, MAKEINTRESOURCE(ABOUT_ICON), &icons[2]);
		D3DXCreateTextureFromResourceA(pDevice, hmodule, MAKEINTRESOURCE(CT_ICON), &icons[3]);
		D3DXCreateTextureFromResourceA(pDevice, hmodule, MAKEINTRESOURCE(T_ICON), &icons[4]);

		settings::menu::init = true;
	}

	if (GetAsyncKeyState(VK_INSERT) & 1)
		settings::menu::isOpen = !settings::menu::isOpen;

	ESPDrawer* drawlist = (ESPDrawer*)ImGui::GetBackgroundDrawList();

	DX9ColorFix colorfix(pDevice);
	colorfix.RemoveColorFilter();

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	RECT rect;
	GetWindowRect(FindWindowA(NULL, WINDOW_NAME), &rect);

	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;


	// отрисовка esp

	for (byte i = 1; i < 32; i++)
	{
		CBaseEntity* Entity = (CBaseEntity*)entitylist->GetClientEntity(i);

		CLocalPlayer* localPlayer = client->dwLocalPlayer;

		viewmatrix matrix = client->dwViewmatrix;

		if (!Entity or !localPlayer or client->WorldToScreen(Entity->m_vecOrigin).z < 0.01f or Entity->m_iHealth <= 0 or Entity->m_iTeamNum == localPlayer->m_iTeamNum or Entity->m_bDormant)
			continue;

		if (settings::BoxEsp::on)
		{
			ImVec3 origin = client->WorldToScreen(Entity->m_vecOrigin);
			ImVec3 playerhead = Entity->GetBonePosition(8);

			playerhead.z += 7.9f;
			playerhead = client->WorldToScreen(playerhead);

			if (playerhead.z > 0.01f)
			{
				if (!settings::BoxEsp::selected_colormode)
					drawlist->DrawBoxEsp(Entity, settings::BoxEsp::thicnes,
						settings::BoxEsp::Color, settings::BoxEsp::drawHpValue);
				else
					drawlist->DrawBoxEsp(Entity, settings::BoxEsp::thicnes, Entity->GetColorBasedOnHealth(), settings::BoxEsp::drawHpValue);

			}
		}

		if (settings::SnapLinesESP::on)
		{
			ImVec3 pos;
			switch (settings::SnapLinesESP::selectedBoneId)
			{
			case 0:
				pos = Entity->GetBonePosition(BONE_HEAD);
				break;
			case 1:
				pos = Entity->GetBonePosition(BONE_BODY);
				break;
			case 2:
				pos = Entity->m_vecOrigin;
				break;
			}
			ImVec3 screen = client->WorldToScreen(pos);
			ImVec2 start = ImVec2(width / 2, height);

			if (!settings::SnapLinesESP::selected_colormode)
				drawlist->AddLine(start, screen, settings::SnapLinesESP::Color, settings::SnapLinesESP::thicnes);
			else
				drawlist->AddLine(start, screen, Entity->GetColorBasedOnHealth(), settings::SnapLinesESP::thicnes);
		}


		if (settings::SkeletonESP::on)
		{
			drawlist->DrawSkeleton(Entity, settings::SkeletonESP::Color, settings::SkeletonESP::thicnes);
		}
	}

	if (settings::menu::isOpen)
	{

		CBaseEntity* localPlayer = client->dwLocalPlayer;

		if (!settings::misc::wallpaper)
			drawlist->AddRectFilled(ImVec2(0, 0), ImVec2(width, height), settings::misc::backgrooundcolor);
		else
			drawlist->AddImage(logos[2], ImVec2(0, 0), ImVec2(width, height));

		// таск бар
		ImGui::Begin("taskbar", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove);
		ImGui::SetWindowPos(ImVec2(0, height - 33));
		ImGui::SetWindowSize(ImVec2(width, 2));

		ImGui::SetCursorPos(ImVec2(3, 5));
		if (ImGui::Button(xorstr("START")))
			settings::menu::start_menu = !settings::menu::start_menu;

		time_t now = time(NULL);
		tm  tstruct;
		char buf[80]; localtime_s(&tstruct, &now); strftime(buf, sizeof(buf), "%X", &tstruct);

		ImGui::SetCursorPos(ImVec2(width - 57, 7));
		ImGui::Text(buf);

		ImGui::End();

		if (settings::menu::settings_menu)
		{
			ImGui::Begin("Settings", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar );
			ImGui::SetWindowSize(ImVec2(555, 252));

			ImGui::Image(icons[1], ImVec2(16, 16));
			ImGui::SameLine();
			
			ImGui::Text(xorstr("AVhook"));

			ImGui::SetCursorPos(ImVec2(555 - 25, 5));
			if (ImGui::Button(" ", ImVec2(20, 20)))
				settings::menu::settings_menu = false;

			if (ImGui::Button(xorstr("AIMBOT"), ImVec2(102, 30)))
				settings::menu::menutab = 1;

			ImGui::SameLine();
			if (ImGui::Button(xorstr("TRIGGER"), ImVec2(102, 30)))
				settings::menu::menutab = 5;

			ImGui::SameLine();
			if (ImGui::Button(xorstr("VISUALS"), ImVec2(102, 30)))
				settings::menu::menutab = 2;

			ImGui::SameLine();
			if (ImGui::Button(xorstr("MISC"), ImVec2(102, 30)))
				settings::menu::menutab = 3;

			ImGui::SameLine();
			if (ImGui::Button(xorstr("MENU"), ImVec2(102, 30)))
				settings::menu::menutab = 4;


			if (settings::menu::menutab == 1) // aimbot sector
			{
				ImGui::Text(xorstr("Automatic Target Acquisition System"));

				ImGui::Checkbox(xorstr("Active"), &settings::aimbot::on);
				ImGui::SameLine();
				ImGui::Combo(xorstr("HitBox"),    &settings::aimbot::selectedhitbox, settings::aimbot::hitboxes, IM_ARRAYSIZE(settings::aimbot::hitboxes));
				ImGui::Checkbox(xorstr("Silent"), &settings::aimbot::silent);
				ImGui::SameLine();
				ImGui::InputInt(xorstr("FOV"),    &settings::aimbot::fov);
				ImGui::Checkbox(xorstr("Auto shoot"), &settings::aimbot::autoshoot);
				
			}
			else if (settings::menu::menutab == 2) // esp sector
			{

				ImGui::SetWindowSize(ImVec2(555, 500));

				ImGui::Text(xorstr("Extra Sensory Perception"));

				ImGui::Text(xorstr("Glow ESP"));
				ImGui::Checkbox(xorstr("Active###Glow"),			&settings::inGameWallHack::on);
				ImGui::SameLine();
				ImGui::ColorEdit4(xorstr("Enemy color"),			(float*)&settings::inGameWallHack::EnemyGlowColor, ImGuiColorEditFlags_NoInputs);
				ImGui::SameLine();

				ImGui::ColorEdit4(xorstr("Friendly color"),			(float*)&settings::inGameWallHack::FriedndlyGlowColor, ImGuiColorEditFlags_NoInputs);

				ImGui::Combo(xorstr("###GlowEspDrawMode"),			&settings::inGameWallHack::selected_glow_mode, settings::inGameWallHack::glowmode, IM_ARRAYSIZE(settings::inGameWallHack::glowmode));

				ImGui::Text(xorstr("Snap Lines"));
				ImGui::Checkbox(xorstr("Active###Draw lines"),		&settings::SnapLinesESP::on);
				ImGui::SameLine();
				ImGui::ColorEdit4(xorstr("Color###lineColor"),		(float*)&settings::SnapLinesESP::Color, ImGuiColorEditFlags_NoInputs);

				ImGui::InputInt(xorstr("###lineThickness"),			&settings::SnapLinesESP::thicnes);
				ImGui::Combo(xorstr("###LinePoint"),				&settings::SnapLinesESP::selectedBoneId, settings::SnapLinesESP::Bones, IM_ARRAYSIZE(settings::SnapLinesESP::Bones));
				ImGui::Combo(xorstr("###LineEspDrawMode"),			&settings::SnapLinesESP::selected_colormode, settings::SnapLinesESP::colormode, IM_ARRAYSIZE(settings::SnapLinesESP::colormode));

				ImGui::Text(xorstr("Boxes"));
				ImGui::Checkbox(xorstr("Active###Draw boxes"),		&settings::BoxEsp::on);
				ImGui::SameLine();
				ImGui::Checkbox(xorstr("HP value"),					&settings::BoxEsp::drawHpValue);
				ImGui::SameLine();
				ImGui::ColorEdit4(xorstr("Color###boxcolor"),	    (float*)&settings::BoxEsp::Color, ImGuiColorEditFlags_NoInputs);
				ImGui::InputInt(xorstr("###boxThickness"),			&settings::BoxEsp::thicnes);
				ImGui::Combo(xorstr("###BoxEspDrawMode"),		    &settings::BoxEsp::selected_colormode, settings::BoxEsp::colormode, IM_ARRAYSIZE(settings::BoxEsp::colormode));

				ImGui::Text(xorstr("Skeleton"));
				ImGui::Checkbox(xorstr("Active###Draw skeletones"), &settings::SkeletonESP::on);
				ImGui::SameLine();
				ImGui::ColorEdit4(xorstr("Color###SkeletColor"),    (float*)&settings::SkeletonESP::Color, ImGuiColorEditFlags_NoInputs);
				ImGui::InputInt(xorstr("###SkeletThickness"),	    &settings::SkeletonESP::thicnes);
			}
			else if (settings::menu::menutab == 3) //misc sector
			{
				ImGui::Text(xorstr("Misc configuration"));
				ImGui::Checkbox(xorstr("Bunny hop"),		 &settings::bhop);
				ImGui::Checkbox(xorstr("Desktop wallpaper"), &settings::misc::wallpaper);

				if (client->dwLocalPlayer)
					ImGui::SliderInt(xorstr("FOV"), &client->dwLocalPlayer->m_iDefaultFOV, 1, 120);
			}
			else if (settings::menu::menutab == 4) // menu settings
			{
				ImGui::SetWindowSize(ImVec2(555, 352));
				ImVec4* theme = ImGui::GetStyle().Colors;

				ImGui::Text(xorstr("Menu configuration"));
				ImGui::ColorEdit4(xorstr("Border"),		   (float*)&theme[ImGuiCol_Border], ImGuiColorEditFlags_NoInputs);
				ImGui::SameLine();
				ImGui::ColorEdit4(xorstr("Background"),    (float*)&theme[ImGuiCol_WindowBg], ImGuiColorEditFlags_NoInputs);
				ImGui::ColorEdit4(xorstr("Button"),        (float*)&theme[ImGuiCol_Button], ImGuiColorEditFlags_NoInputs);
				ImGui::SameLine();
				ImGui::ColorEdit4(xorstr("Button active"), (float*)&theme[ImGuiCol_ButtonActive], ImGuiColorEditFlags_NoInputs);
				ImGui::ColorEdit4(xorstr("Text"),          (float*)&theme[ImGuiCol_Text], ImGuiColorEditFlags_NoInputs);
				ImGui::SameLine();
				ImGui::ColorEdit4(xorstr("Frame"),         (float*)&theme[ImGuiCol_FrameBg], ImGuiColorEditFlags_NoInputs);
				ImGui::ColorEdit4(xorstr("Frame active"),  (float*)&theme[ImGuiCol_FrameBgActive], ImGuiColorEditFlags_NoInputs);
				ImGui::SameLine();
				ImGui::ColorEdit4(xorstr("Frame hovered"), (float*)&theme[ImGuiCol_FrameBgHovered], ImGuiColorEditFlags_NoInputs);
				ImGui::ColorEdit4(xorstr("Text selected"), (float*)&theme[ImGuiCol_TextSelectedBg], ImGuiColorEditFlags_NoInputs);
				ImGui::ColorEdit4(xorstr("Check mark"),    (float*)&theme[ImGuiCol_CheckMark], ImGuiColorEditFlags_NoInputs);
				ImGui::SameLine();
				ImGui::ColorEdit4(xorstr("Overlay"),	   (float*)(&settings::misc::backgrooundcolor), ImGuiColorEditFlags_NoInputs);
			}
			else if (settings::menu::menutab == 5) // trigger
			{
				ImGui::Text(xorstr("Trigger bot."));
				ImGui::Checkbox(xorstr("Active"), &settings::trigger_bot::on);
				ImGui::SameLine();
				ImGui::Checkbox(xorstr("Rage"),	  &settings::trigger_bot::rage);
				ImGui::SliderInt(xorstr("Delay"), &settings::trigger_bot::delay, 0, 1000);
			}
			else
			{
				ImGui::Text(xorstr("Welcome!"));
			}

			ImGui::End();
		}
		if (settings::menu::start_menu)
		{
			ImGui::Begin("start", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove);
			ImGui::SetWindowPos(ImVec2(0, height - 374));
			ImGui::SetWindowSize(ImVec2(300, 342));

			if (ImGui::Button(xorstr("PLAYER LIST"), ImVec2(100, 25)))
			{
				settings::menu::player_list = !settings::menu::player_list;
			}

			if (ImGui::Button(xorstr("SETTINGS"), ImVec2(100, 25)))
				settings::menu::settings_menu = !settings::menu::settings_menu;

			if (ImGui::Button(xorstr("ABOUT"), ImVec2(100, 25)))
				settings::menu::about_menu = !settings::menu::about_menu;


			ImGui::End();
		}
		if (settings::menu::about_menu)
		{
			ImGui::Begin(xorstr("About"), NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);
			ImGui::SetWindowSize(ImVec2(500, 150));
			ImGui::Image(icons[2], ImVec2(16, 16));
			ImGui::SameLine();
			ImGui::Text(xorstr("ABOUT"));

			ImGui::SetCursorPos(ImVec2(500 - 25, 5));
			if (ImGui::Button(" ", ImVec2(20, 20)))
				settings::menu::about_menu = false;

			ImGui::Image((void*)logos[0], ImVec2(100, 100));
			ImGui::SameLine();
			ImGui::Text(xorstr("COMPILATION DATE: %s\nCOMPILATION TIME: %s"), xorstr(__DATE__), xorstr(__TIME__));
			ImGui::SetCursorPos(ImVec2(115, 70));
			if (ImGui::Button(xorstr("SITE/SUPPORT"), ImVec2(100, 25)))
				ShellExecute(0, 0, xorstr("https://avhook.ru/"), 0, 0, SW_SHOW);
			ImGui::End();
		}
		if (settings::menu::player_list)
		{
			ImGui::Begin(xorstr("player_list"), NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);
			ImGui::SetWindowSize(ImVec2(800, 500));

			ImGui::Image(icons[0], ImVec2(16, 16));
			ImGui::SameLine();

			ImGui::Text(xorstr("PLAYER LIST"));
			ImGui::SetCursorPos(ImVec2(800 - 25, 5));
			if (ImGui::Button(" ", ImVec2(20, 20)))
				settings::menu::player_list = false;

			for (byte i = 1; i < 33; i++)
			{
				CBaseEntity* ent = (CBaseEntity*)entitylist->GetClientEntity(i);

				if (!ent)
					continue;

				if (ent->m_iTeamNum == 3)
					ImGui::Image(icons[3], ImVec2(16, 16));
				else
					ImGui::Image(icons[4], ImVec2(16, 16));

				ImGui::SameLine();
				ImGui::Text(xorstr("ID-%d   TEAM-ID:   %d   HEALTH:  "), i, ent->m_iTeamNum);
				ImGui::SameLine();
				ImGui::TextColored(ent->GetColorBasedOnHealth(), "%d", ent->m_iHealth);

			}

			ImGui::End();
		}
	}
	drawlist->AddText(ImVec2(1, 1), ImColor(255, 94, 94), xorstr("AVhook by LSS"));
	
	ImGui::EndFrame();
	colorfix.RestoreRenderState();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	colorfix.RestoreColorFilter();
	return oEndScene(pDevice);
}



LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (settings::menu::isOpen) 
	{

		ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
		return true;
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
		//end_scene_addr = (DWORD)d3dDevice[42];
		client   = (ClientBase*)GetModuleHandle("client.dll");
		oWndProc = (WNDPROC)SetWindowLongPtr(window, GWL_WNDPROC, (LONG_PTR)WndProc);
		settings::attach = true;
		PlaySound(xorstr("avhook\\sounds\\activated.wav"), NULL, SND_ASYNC);
		memcpy(end_scene_bytes, (char*)end_scene_addr, 7);

		oEndScene = (EndScene)mem.trampHook32((char*)end_scene_addr, (char*)hkEndScene, 7);
		

		while (!GetAsyncKeyState(VK_END))
		{
			Sleep(500);
		}


		settings::attach = false;
		PlaySound(xorstr("avhook\\sounds\\deactivated.wav"), NULL, SND_ASYNC);

		ImGui_ImplWin32_Shutdown();
		ImGui_ImplDX9_Shutdown();
		ImGui::DestroyContext();

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
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Bhop,		   hModule, 0, nullptr);
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)InGameGlowWH, hModule, 0, nullptr);
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Trigger,	   hModule, 0, nullptr);
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)AimBot,       hModule, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}