#include <Windows.h>

#include <d3d9.h>
#include <d3dx9.h>

#include <D3dx9tex.h>

#include "ESPDrawer.h"
#include "kiero/kiero.h"
#include "kiero/minhook/include/MinHook.h"

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
#include "viewmatrix.h"

#include "CBaseEntity.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <time.h>


#pragma comment(lib, "D3dx9")
#pragma comment(lib, "winmm")


typedef long(__stdcall* EndScene)(LPDIRECT3DDEVICE9);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

EndScene oEndScene;
WNDPROC oWndProc;

ImVec4* theme;
ClientBase* client;
DWORD clientBase;
HWND window;

PDIRECT3DTEXTURE9 textures[3];
ESPDrawer* drawlist;

inline void InitImGui(LPDIRECT3DDEVICE9 pDevice)
{

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;

	io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 15.0f, 0);
    
	ImGui_ImplWin32_Init(FindWindowA(NULL, WINDOW_NAME));
	ImGui_ImplDX9_Init(pDevice);

	theme = ImGui::GetStyle().Colors;
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
bool init = false;

long __stdcall hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{
    if (!settings::attach)
        return oEndScene(pDevice);
   

    if (!init)
    {
        InitImGui(pDevice);
        D3DXCreateTextureFromFileA(pDevice, "avhook\\photos\\AV.jpg", &textures[0]);
        D3DXCreateTextureFromFileA(pDevice, "avhook\\photos\\ncc_logo.png", &textures[1]);
        drawlist = (ESPDrawer*)ImGui::GetBackgroundDrawList();

        init = true;
    }

    if (GetAsyncKeyState(VK_INSERT) & 1)
        settings::isOpen = !settings::isOpen;

    DX9ColorFix colorfix(pDevice);
    colorfix.RemoveColorFilter();

    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    RECT rect;

    GetWindowRect(window, &rect);

    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;
    viewmatrix matrix = client->dwViewmatrix;

    // отрисовка esp
    for (short int i = 1; i < 32; i++)
    {
        __try
        {
            if (!settings::SnapLinesESP::on && !settings::BoxEsp::on && !settings::SkeletonESP::on)
                break;

            CBaseEntity* Entity = *(CBaseEntity**)(clientBase + signatures::dwEntityList + i * 0x10);
            CLocalPlayer* localPlayer = *(CLocalPlayer**)(clientBase + signatures::dwLocalPlayer);

            if (client->WorldToScreen(Entity->m_vecOrigin).z < 0.01f or Entity->m_iHealth <= 0 or Entity->m_iTeamNum == localPlayer->m_iTeamNum or Entity->m_bDormant)
                continue;

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

            if (settings::SkeletonESP::showbones)
            {
                drawlist->DrawBonesNumbers(Entity);
            }
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
        
        }

    }

    if (settings::isOpen)
    {
        // затемнение когда меню открыто
        drawlist->AddRectFilled(ImVec2(0, 0), ImVec2(width, height), settings::misc::backgrooundcolor);

        // выводим время
        time_t now = time(NULL);
        tm  tstruct;
        char buf[80];

        localtime_s(&tstruct, &now);
        strftime(buf, sizeof(buf), "%X", &tstruct);
        drawlist->AddText(ImVec2(1, 15), ImColor(255, 255, 255), buf);

        // основное окно
        CBaseEntity* localPlayer = *(CLocalPlayer**)(clientBase + signatures::dwLocalPlayer);
        ImGui::Begin("AVhook", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);
        ImGui::SetWindowSize(ImVec2(555, 252));
        ImGui::Text("AVhook");

        if (ImGui::Button("AIMBOT", ImVec2(102, 30)))
            settings::menu = 1;

        ImGui::SameLine();
        if (ImGui::Button("TRIGGER", ImVec2(102, 30)))
            settings::menu = 5;
        
        ImGui::SameLine();
        if (ImGui::Button("VISUALS", ImVec2(102, 30)))
            settings::menu = 2;

        ImGui::SameLine();
        if (ImGui::Button("MISC", ImVec2(102, 30)))
            settings::menu = 3;

        ImGui::SameLine();
        if (ImGui::Button("MENU", ImVec2(102, 30)))
            settings::menu = 4;

        if (settings::menu == 1) // aimbot sector
        {
            ImGui::Text("Automatic Target Acquisition System");

            ImGui::Checkbox("Active", &settings::aimbot::on);
            ImGui::SameLine();
            ImGui::Combo("HitBox", &settings::aimbot::selectedhitbox, settings::aimbot::hitboxes, IM_ARRAYSIZE(settings::aimbot::hitboxes));
            ImGui::Checkbox("Silent", &settings::aimbot::silent);

        }
        else if (settings::menu == 2) // esp sector
        {

            ImGui::SetWindowSize(ImVec2(555, 500));

            ImGui::Text("Extra Sensory Perception");

            ImGui::Text("Glow ESP");
            ImGui::Checkbox("Active###Glow", &settings::inGameWallHack::on);
            ImGui::SameLine();
            ImGui::ColorEdit4("Enemy color", (float*)&settings::inGameWallHack::EnemyGlowColor, ImGuiColorEditFlags_NoInputs);
            ImGui::SameLine();

            ImGui::ColorEdit4("Friendly color", (float*)&settings::inGameWallHack::FriedndlyGlowColor, ImGuiColorEditFlags_NoInputs);

            ImGui::Combo("###GlowEspDrawMode", &settings::inGameWallHack::selected_glow_mode, settings::inGameWallHack::glowmode, IM_ARRAYSIZE(settings::inGameWallHack::glowmode));

            ImGui::Text("Snap Lines");
            ImGui::Checkbox("Active###Draw lines", &settings::SnapLinesESP::on);
            ImGui::SameLine();
            ImGui::ColorEdit4("Color###lineColor", (float*)&settings::SnapLinesESP::Color, ImGuiColorEditFlags_NoInputs);

            ImGui::InputInt("###lineThickness", &settings::SnapLinesESP::thicnes);
            ImGui::Combo("###LinePoint", &settings::SnapLinesESP::selectedBoneId, settings::SnapLinesESP::Bones, IM_ARRAYSIZE(settings::SnapLinesESP::Bones));
            ImGui::Combo("###LineEspDrawMode", &settings::SnapLinesESP::selected_colormode, settings::SnapLinesESP::colormode, IM_ARRAYSIZE(settings::SnapLinesESP::colormode));

            ImGui::Text("Boxes");
            ImGui::Checkbox("Active###Draw boxes", &settings::BoxEsp::on);
            ImGui::SameLine();
            ImGui::Checkbox("HP value", &settings::BoxEsp::drawHpValue);
            ImGui::SameLine();
            ImGui::ColorEdit4("Color###boxcolor", (float*)&settings::BoxEsp::Color, ImGuiColorEditFlags_NoInputs);
            ImGui::InputInt("###boxThickness", &settings::BoxEsp::thicnes);
            ImGui::Combo("###BoxEspDrawMode", &settings::BoxEsp::selected_colormode, settings::BoxEsp::colormode, IM_ARRAYSIZE(settings::BoxEsp::colormode));

            ImGui::Text("Skeleton");
            ImGui::Checkbox("Active###Draw skeletones", &settings::SkeletonESP::on);
            ImGui::Checkbox("Show bones", &settings::SkeletonESP::showbones);
        }
        else if (settings::menu == 3) //misc sector
        {
            ImGui::Text("Misc configuration");
            ImGui::Checkbox("Bunny hop", &settings::bhop);
            ImGui::Checkbox("NullCore joke logo", &settings::misc::nullcorelogo);
            __try
            {
                ImGui::SliderInt("FOV", &client->dwLocalPlayer->m_iDefaultFOV, 1, 120);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {

            }
        }
        else if (settings::menu == 4) // menu settings
        {
            ImGui::SetWindowSize(ImVec2(555, 352));

            ImGui::Text("Menu configuration");
            ImGui::ColorEdit4("Border", (float*)&theme[ImGuiCol_Border], ImGuiColorEditFlags_NoInputs);
            ImGui::SameLine();
            ImGui::ColorEdit4("Background", (float*)&theme[ImGuiCol_WindowBg], ImGuiColorEditFlags_NoInputs);
            ImGui::ColorEdit4("Button", (float*)&theme[ImGuiCol_Button], ImGuiColorEditFlags_NoInputs);
            ImGui::SameLine();
            ImGui::ColorEdit4("Button active", (float*)&theme[ImGuiCol_ButtonActive], ImGuiColorEditFlags_NoInputs);
            ImGui::ColorEdit4("Text", (float*)&theme[ImGuiCol_Text], ImGuiColorEditFlags_NoInputs);
            ImGui::SameLine();
            ImGui::ColorEdit4("Frame", (float*)&theme[ImGuiCol_FrameBg], ImGuiColorEditFlags_NoInputs);
            ImGui::ColorEdit4("Frame active", (float*)&theme[ImGuiCol_FrameBgActive], ImGuiColorEditFlags_NoInputs);
            ImGui::SameLine();
            ImGui::ColorEdit4("Frame hovered", (float*)&theme[ImGuiCol_FrameBgHovered], ImGuiColorEditFlags_NoInputs);
            ImGui::ColorEdit4("Text selected", (float*)&theme[ImGuiCol_TextSelectedBg], ImGuiColorEditFlags_NoInputs);
            ImGui::SameLine();
            ImGui::ColorEdit4("Overlay", (float*)(&settings::misc::backgrooundcolor), ImGuiColorEditFlags_NoInputs);
        }

        else if (settings::menu == 5) // trigger
        {
            ImGui::Text("Trigger bot.");
            ImGui::Checkbox("Active", &settings::trigger_bot::on);
            ImGui::SameLine();
            ImGui::Checkbox("Rage", &settings::trigger_bot::rage);
            ImGui::SameLine();
            ImGui::Checkbox("Prediction", &settings::trigger_bot::predict);
            ImGui::SliderInt("Delay", &settings::trigger_bot::delay, 0, 1000);
            ImGui::SliderInt("Prediction time", &settings::trigger_bot::predtime, 0, 1000);
        }

        else
        {
            ImGui::Text("Welcome!");
        }

        ImGui::End();


        if (settings::misc::nullcorelogo)
        {
            drawlist->AddImage((void*)textures[1], ImVec2((width / 2) - 150, 20), ImVec2(300 + (width / 2) - 150, 180));
        }
        else
        {
            drawlist->AddImage((void*)textures[0], ImVec2((width / 2) - 50, 20), ImVec2(100 + (width / 2) - 50, 120));
            drawlist->AddText(ImVec2((width / 2) - 50, 125), ImColor(255, 94, 94), "MAKE IT SIMPLE");
        }
        
    }
    drawlist->AddText(ImVec2(1, 1), ImColor(255, 94, 94), "AVhook by LSS");

    ImGui::EndFrame();
    colorfix.RestoreRenderState();
    ImGui::Render();
    ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

    colorfix.RestoreColorFilter();
    return oEndScene(pDevice);
}



LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}


DWORD WINAPI MainThread(HMODULE hModule)
{
	window = FindWindowA(NULL, WINDOW_NAME);
	if (window)
	{

        kiero::init(kiero::RenderType::D3D9);
		kiero::bind(42, (void**)&oEndScene, hkEndScene);

        client = (ClientBase*)GetModuleHandle(L"client.dll");
        clientBase = (DWORD)GetModuleHandle(L"client.dll");
		oWndProc = (WNDPROC)SetWindowLongPtr(window, GWL_WNDPROC, (LONG_PTR)WndProc);
        settings::attach = true;

        PlaySound(L"avhook\\sounds\\activated.wav", NULL, SND_ASYNC);

        while ( !GetAsyncKeyState(VK_END))
        {
            Sleep(500);
        }

        //remove imgui
        settings::attach = false;
        PlaySound(L"avhook\\sounds\\deactivated.wav", NULL, SND_ASYNC);
        ImGui_ImplWin32_Shutdown();
        ImGui_ImplDX9_Shutdown();
        ImGui::DestroyContext();

        //unhook wndproc
        SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)oWndProc);

        //unhook kiero
        kiero::unbind(41);
        kiero::shutdown();

        Sleep(2000);
        
	}
    FreeLibraryAndExitThread(hModule, NULL);
}

DWORD WINAPI Bhop(HMODULE hModule)
{
    BunnyHop bhop = BunnyHop();
    while (settings::attach)
    {
        
        if (settings::bhop)
            bhop.HandleBhop();
        else
            Sleep(500);
        

    }
    return 0;
}

DWORD WINAPI InGameGlowWH(HMODULE hModule)
{
    InGameGlowEsp esp = InGameGlowEsp(&settings::inGameWallHack::selected_glow_mode);

    while (settings::attach)
    {

        if (settings::inGameWallHack::on)
        {
            esp.HandleGlow(settings::inGameWallHack::EnemyGlowColor, settings::inGameWallHack::FriedndlyGlowColor);
            Sleep(1);
        }
    }
    return 0;
}

DWORD WINAPI Trigger(HMODULE hModule)
{
    using namespace settings::trigger_bot;
    TriggerBot triggerbot(&delay, &rage, &predict, &predtime);

    while (settings::attach)
    {
        if (settings::trigger_bot::on and GetAsyncKeyState(VK_XBUTTON1))
            triggerbot.Handle();
        else
            Sleep(100);
    }
    return 0;
}

DWORD WINAPI AimBot(HMODULE hModule)
{
    int bone = 8;
    while (settings::attach)
    {
        __try
        {
            if (!settings::aimbot::on)
            {
                Sleep(500);
                continue;
            }

            switch (settings::aimbot::selectedhitbox)
            {
            case 0:
                bone = BONE_HEAD;
                break;
            case 1:
                bone =  BONE_BODY;
                break;
            case 2:
                bone = BONE_LEGS;
                break;
            }

            CLocalPlayer* localPlayer = *(CLocalPlayer**)(clientBase + signatures::dwLocalPlayer);
            CBaseEntity* entity = localPlayer->GetClosestEnity();

            if (localPlayer->m_iTeamNum != entity->m_iTeamNum)
                localPlayer->AimAt(entity, bone, 10, true);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            
        }

    }
    return 0;
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{

	case DLL_PROCESS_ATTACH:
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, nullptr);
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Bhop, hModule, 0, nullptr);
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)InGameGlowWH, hModule, 0, nullptr);
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Trigger, hModule, 0, nullptr);
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)AimBot, hModule, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:
        break;
	}
	return TRUE;
}