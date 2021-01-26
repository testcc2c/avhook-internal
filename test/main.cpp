#include "includes.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

EndScene oEndScene = NULL;
WNDPROC oWndProc;
static HWND window = NULL;
ImVec4* theme;
DWORD baseAddr;

BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam)
{
	DWORD wndProcId;
	GetWindowThreadProcessId(handle, &wndProcId);

	if (GetCurrentProcessId() != wndProcId)
		return TRUE; // skip to next window

	window = handle;
	return FALSE; // window found abort search
}

inline HWND GetProcessWindow()
{
	window = NULL;
	EnumWindows(EnumWindowsCallback, NULL);
	return window;
}

inline void InitImGui(LPDIRECT3DDEVICE9 pDevice)
{

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 15.0f, 0);

	ImGui_ImplWin32_Init(window);
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
}

bool init = false;
long __stdcall hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{

	if (!init)
	{
		InitImGui(pDevice);
		init = true;
		baseAddr = (DWORD)GetModuleHandle(NULL);

	}
	if (GetAsyncKeyState(VK_INSERT) & 1)
	{
		
		settings::isOpen = !settings::isOpen;
		if (settings::isOpen)
			PlaySound(L"C:\\Program Files (x86)\\AssaultCube\\packages\\audio\\hev\\activated.wav", NULL, SND_ASYNC);
		else
		{
			PlaySound(L"C:\\Program Files (x86)\\AssaultCube\\packages\\audio\\hev\\deactivated.wav", NULL, SND_ASYNC);
		}
	}
	
	if (settings::isOpen)
	{

		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("AVhook", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar);
		ImGui::SetWindowSize(ImVec2(440, 250));

		ImGui::SameLine();
		ImGui::Text("AVhook");
		if (ImGui::Button("AIMBOT", ImVec2(100, 30)))
		{
			settings::menu = 1;

		}

		ImGui::SameLine();
		if (ImGui::Button("ESP", ImVec2(100, 30)))
		{
			settings::menu = 2;
		}

		ImGui::SameLine();
		if (ImGui::Button("MISC", ImVec2(100, 30)))
		{
			settings::menu = 3;
		}

		ImGui::SameLine();
		if (ImGui::Button("MENU", ImVec2(100, 30)))
		{
			settings::menu = 4;
		}
		if (settings::menu == 1) // aimbot sector
		{
			
		}
		else if (settings::menu == 2) // esp sector
		{
			
			
		}
		else if (settings::menu == 3) //misc sector
		{
			ImGui::Text("Misc configuration");
			DWORD phealth = memory::GetPointer(baseAddr + 0x9D5858, { 0xE0, 0x48, 0x488 });

			if (phealth != NULL)
			{
				//ImGui::SliderInt("Health", (int*)phealth, 1, 999);
				ImGui::InputInt("Health", (int*)phealth);
			}
			else 
			{
				ImGui::Text("Start game for edit heatlh.");
			}
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
			ImGui::Text("Welcome back AV!\nAlpha build: v0.0.1");

		}
		ImGui::End();

		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	}
	return oEndScene(pDevice);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}


DWORD WINAPI MainThread(LPVOID lpReserved)
{
	bool attached = false;
	do
	{
		if (kiero::init(kiero::RenderType::D3D9) == kiero::Status::Success)
		{
			kiero::bind(42, (void**)&oEndScene, hkEndScene);
			do
				window = GetProcessWindow();
			while (window == NULL);
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWL_WNDPROC, (LONG_PTR)WndProc);
			attached = true;
		}
	} while (!attached);
	return TRUE;
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hMod);
		CreateThread(nullptr, 0, MainThread, hMod, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		kiero::shutdown();

		break;
	}
	return TRUE;
}