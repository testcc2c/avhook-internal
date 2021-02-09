#pragma once
#include "includes.h"


long __stdcall hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{

	if (settings::init)
	{
		InitImGui(pDevice);
		settings::init = true;
		baseAddr = (DWORD)GetModuleHandle(NULL);

	}
	if (GetAsyncKeyState(VK_INSERT) & 1)
	{

		settings::isOpen = !settings::isOpen;
		if (settings::isOpen)
			PlaySound(L"sounds\\activated.wav", NULL, SND_ASYNC);
		else
			PlaySound(L"sounds\\deactivated.wav", NULL, SND_ASYNC);
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
			ImGui::Checkbox("Aimbot", &settings::aimbot);
			ImGui::SameLine();
			ImGui::Combo("HitBox", &settings::selectedhitbox, settings::hitboxes, IM_ARRAYSIZE(settings::hitboxes));
			ImGui::Checkbox("Silent", &settings::silent);

		}
		else if (settings::menu == 2) // esp sector
		{
			ImGui::Text("Coming soon....");
		}
		else if (settings::menu == 3) //misc sector
		{
			ImGui::Text("Misc configuration");

			pointers::pPoints = NULL;

			ImGui::Checkbox("Air jump", &settings::airjump);

			// Points block
			if (pointers::pPoints)
				ImGui::InputInt("Points", pointers::pPoints);
			else
			{
				ImGui::Text("Start game to edit points.");
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
			ImGui::Text("Welcome back AV!\nAlpha build: v0.0.5");
		}

		ImGui::End();
		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	}
	return oEndScene(pDevice);
}