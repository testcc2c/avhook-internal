#include "includes.h"
#include "CBaseEntity.h"
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

EndScene oEndScene;
WNDPROC oWndProc;

ImVec4* theme;

DWORD baseAddr;

#define WINDOW_NAME "Counter-Strike: Global Offensive"


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
    DX9ColorFix colorfix(pDevice);

    if (!init)
    {
        InitImGui(pDevice);
        init = true;
    }
    if (GetAsyncKeyState(VK_INSERT) & 1)
    {

        settings::isOpen = !settings::isOpen;
    }

    if (settings::isOpen)
    {
        CBaseEntity* localPlayer = *(CBaseEntity**)(baseAddr + signatures::dwLocalPlayer);

        colorfix.RemoveColorFilter();

        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("AVhook", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);
        ImGui::SetWindowSize(ImVec2(440, 250));

        ImGui::SameLine();
        ImGui::Text("AVhook");

        if (ImGui::Button("ATAS", ImVec2(100, 30)))
            settings::menu = 1;

        ImGui::SameLine();
        if (ImGui::Button("VISUALS", ImVec2(100, 30)))
            settings::menu = 2;

        ImGui::SameLine();
        if (ImGui::Button("MISC", ImVec2(100, 30)))
            settings::menu = 3;

        ImGui::SameLine();
        if (ImGui::Button("MENU", ImVec2(100, 30)))
            settings::menu = 4;

        if (settings::menu == 1) // aimbot sector
        {
            ImGui::Text("Automatic Target Acquisition System");

            ImGui::Checkbox("Status", &settings::aimbot);
            ImGui::SameLine();
            ImGui::Combo("HitBox", &settings::selectedhitbox, settings::hitboxes, IM_ARRAYSIZE(settings::hitboxes));
            ImGui::Checkbox("Silent", &settings::silent);

        }
        else if (settings::menu == 2) // esp sector
        {
            ImGui::Text("Extra Sensory Perception");

            ImGui::Checkbox("Glow whall hack", &settings::GlowWh);
            ImGui::ColorEdit4("Enemy color", (float*)&settings::EnemyGlowColor, ImGuiColorEditFlags_NoInputs);
        }
        else if (settings::menu == 3) //misc sector
        {
            ImGui::Text("Misc configuration");
            ImGui::Checkbox("Bunny hop", &settings::bhop);

            if (localPlayer != nullptr)
                ImGui::SliderInt("FOV", &localPlayer->m_iDefaultFOV, 0, 150);
        }
        else if (settings::menu == 4) // menu settings
        {
            ImGui::SetWindowSize(ImVec2(440, 350));

            ImGui::Text("Menu configuration");
            ImGui::ColorEdit4("Border", (float*)&theme[ImGuiCol_Border], ImGuiColorEditFlags_NoInputs);
            ImGui::ColorEdit4("Background", (float*)&theme[ImGuiCol_WindowBg], ImGuiColorEditFlags_NoInputs);
            ImGui::ColorEdit4("Button", (float*)&theme[ImGuiCol_Button], ImGuiColorEditFlags_NoInputs);
            ImGui::ColorEdit4("Button active", (float*)&theme[ImGuiCol_ButtonActive], ImGuiColorEditFlags_NoInputs);
            ImGui::ColorEdit4("Text", (float*)&theme[ImGuiCol_Text], ImGuiColorEditFlags_NoInputs);
            ImGui::ColorEdit4("Frame", (float*)&theme[ImGuiCol_FrameBg], ImGuiColorEditFlags_NoInputs);
            ImGui::ColorEdit4("Frame active", (float*)&theme[ImGuiCol_FrameBgActive], ImGuiColorEditFlags_NoInputs);
            ImGui::ColorEdit4("Frame hovered", (float*)&theme[ImGuiCol_FrameBgHovered], ImGuiColorEditFlags_NoInputs);
            ImGui::ColorEdit4("Text selected", (float*)&theme[ImGuiCol_TextSelectedBg], ImGuiColorEditFlags_NoInputs);
        }
        else
        {
            HW_PROFILE_INFO hwProfileInfo;
            GetCurrentHwProfile(&hwProfileInfo);

            ImGui::Text("Welcome back!\nHWID: %s\nAlpha build: v0.0.5", hwProfileInfo.szHwProfileGuid);
        }
        ImGui::End();
        ImGui::EndFrame();

        colorfix.RestoreRenderState();

        ImGui::Render();
        ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

        colorfix.RestoreColorFilter();

    }
    return oEndScene(pDevice);
}



LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}


DWORD WINAPI MainThread(HMODULE hModule)
{
	HWND window = FindWindowA(NULL, WINDOW_NAME);
	if (window)
	{

        kiero::init(kiero::RenderType::D3D9);
		kiero::bind(42, (void**)&oEndScene, hkEndScene);

        baseAddr = (DWORD)GetModuleHandle(L"client.dll");

		oWndProc = (WNDPROC)SetWindowLongPtr(window, GWL_WNDPROC, (LONG_PTR)WndProc);
        settings::attach = true;

        while ( !GetAsyncKeyState(VK_END))
        {
            Sleep(1);
        }

        //remove imgui
        settings::isOpen = false;
        ImGui_ImplWin32_Shutdown();
        ImGui_ImplDX9_Shutdown();
        ImGui::DestroyContext();

        //unhook wndproc
        SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)oWndProc);

        //unhook kiero
        kiero::unbind(41);
        kiero::shutdown();

        settings::attach = false;
        Sleep(1000);
        
	}
    FreeLibraryAndExitThread(hModule, NULL);

    return NULL;
}

DWORD WINAPI Bhop(HMODULE hModule)
{
    while (settings::attach)
    {
        
        if (settings::bhop)
            HandleBhop(baseAddr);

    }
    return 0;
}

DWORD WINAPI InGameGlowWH(HMODULE hModule)
{
    while (settings::attach)
    {

        if (settings::GlowWh)
            HandleGlow(baseAddr, settings::EnemyGlowColor);
            
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
		break;
	case DLL_PROCESS_DETACH:
        break;
	}
	return TRUE;
}