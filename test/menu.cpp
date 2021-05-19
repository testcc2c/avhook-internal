#include "menu.h"

Menu::Menu(LPDIRECT3DDEVICE9 pDevice, HMODULE hmod)
{
	this->pDevice    = pDevice;
	this->hmodule    = hmod;
	this->window     = FindWindowA(NULL, this->window_name);
	this->entitylist = GetInterface<IClientEntityList>(xorstr("client.dll"), xorstr("VClientEntityList003"));
	this->client     = (ClientBase*)GetModuleHandle("client.dll");
	this->window_size = this->GetWindowSize();
	this->colorfix = new DX9ColorFix(this->pDevice);

	ImGui::CreateContext();
	ImGui_ImplWin32_Init(this->window);
	ImGui_ImplDX9_Init(pDevice);

	this->io = ImGui::GetIO();
	this->io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	this->io.Fonts->AddFontFromFileTTF(xorstr("C:\\Windows\\Fonts\\Impact.ttf"), 17.0f, 0);
	this->drawlist = (ESPDrawer*)ImGui::GetBackgroundDrawList();

	this->theme = ImGui::GetStyle().Colors;

	this->theme[ImGuiCol_WindowBg]		  = ImColor(24, 31, 35, 255);
	this->theme[ImGuiCol_Button]		  = ImVec4(1.f, 0.372f, 0.372f, 1.f);
	this->theme[ImGuiCol_Tab]			  = ImVec4(1.f, 0.372f, 0.372f, 1.f);
	this->theme[ImGuiCol_SeparatorActive] = ImVec4(1.f, 0.372f, 0.372f, 1.f);
	this->theme[ImGuiCol_Border]		  = ImVec4(1.f, 0.372f, 0.372f, 1.f);
	this->theme[ImGuiCol_Text]			  = ImVec4(1.f, 1.f, 1.f, 1.f);
	this->theme[ImGuiCol_ButtonActive]	  = ImVec4(1.f, 0.57f, 0.57f, 1.f);
	this->theme[ImGuiCol_ButtonHovered]	  = ImVec4(1.f, 0.4f, 0.4f, 1.f);
	this->theme[ImGuiCol_CheckMark]		  = ImVec4(1.f, 0.372f, 0.372f, 1.f);
	this->theme[ImGuiCol_TextSelectedBg]  = ImVec4(1.f, 0.372f, 0.372f, 1.f);
	this->theme[ImGuiCol_FrameBg]		  = ImVec4(0.31f, 0.31f, 0.31f, 1.f);
	this->theme[ImGuiCol_FrameBgActive]	  = ImVec4(1.f, 0.57f, 0.57f, 1.f);
	this->theme[ImGuiCol_FrameBgHovered]  = ImVec4(0.41f, 0.41f, 0.41f, 1.f);
	this->theme[ImGuiCol_PopupBg]		  = ImColor(24, 31, 35, 255);
	this->theme[ImGuiCol_ScrollbarBg]	  = ImVec4(1.f, 0.372f, 0.372f, 0.f);
	this->theme[ImGuiCol_ScrollbarGrab]	  = ImVec4(1.f, 0.372f, 0.372f, 1.f);
	this->theme[ImGuiCol_SliderGrab]	  = ImVec4(1.f, 0.372f, 0.372f, 1.f);
	this->theme[ImGuiCol_SliderGrabActive]= ImVec4(1.f, 0.372f, 0.372f, 1.f);
	this->theme[ImGuiCol_TabHovered]	  = ImVec4(1.f, 0.57f,  0.57f,  1.f);
	this->theme[ImGuiCol_TabActive]		  = ImVec4(1.f, 0.372f, 0.372f, 1.f);

	D3DXCreateTextureFromResourceA(pDevice, hmodule, MAKEINTRESOURCE(IDB_BITMAP4), &icons[PlayerListIcon]);
	D3DXCreateTextureFromResourceA(pDevice, hmodule, MAKEINTRESOURCE(IDB_BITMAP5), &icons[SettingsIcon]);
	D3DXCreateTextureFromResourceA(pDevice, hmodule, MAKEINTRESOURCE(IDB_BITMAP1), &icons[AboutIcon]);
	D3DXCreateTextureFromResourceA(pDevice, hmodule, MAKEINTRESOURCE(IDB_BITMAP3), &icons[CounterTerroristIcon]);
	D3DXCreateTextureFromResourceA(pDevice, hmodule, MAKEINTRESOURCE(IDB_BITMAP6), &icons[TerroristIcon]);
	D3DXCreateTextureFromResourceA(pDevice, hmodule, MAKEINTRESOURCE(IDB_BITMAP7), &icons[RadarIcon]);
	D3DXCreateTextureFromFileA(pDevice, this->GetDesktopWallpaper().c_str(), &this->wallpaper_texture);

	this->render = true;
}

ImVec2 Menu::GetWindowSize()
{
	RECT rect;
	GetWindowRect(this->window, &rect);

	return ImVec2(rect.right - rect.left, rect.bottom - rect.top);
}
// возврат времени в формате "час:минута:секунда"
std::string Menu::GetTime()
{
	time_t now = time(NULL);
	tm  tstruct;
	char buf[80]; localtime_s(&tstruct, &now); strftime(buf, sizeof(buf), "%X", &tstruct);
	return std::string(buf);
}

void Menu::Detach()
{
	this->active = false;
	this->render = false;

	ImGui_ImplWin32_Shutdown();
	ImGui_ImplDX9_Shutdown();
	ImGui::DestroyContext();
	delete this->colorfix;

}

bool Menu::isOpen()
{
	if (this)
		return this->active;
	else
		return false;
}

bool Menu::isAttached()
{
	return this->render;
}

// Отрисовывает меню "пуск", вызвается в ТОЛЬКО методе "Render".
void Menu::DrawStartMenu()
{
	ImGui::Begin(xorstr("start"), NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove);
	ImGui::SetWindowPos(ImVec2(0, this->window_size.y - 374));
	ImGui::SetWindowSize(ImVec2(300, 342));

	if (ImGui::Button(xorstr("PLAYER LIST"), ImVec2(100, 25)))
		this->tabs[PlayerListTab] = !this->tabs[PlayerListTab];

	if (ImGui::Button(xorstr("SETTINGS"), ImVec2(100, 25)))
		this->tabs[SettingsMenuTab] = !this->tabs[SettingsMenuTab];

	if (ImGui::Button(xorstr("ABOUT"), ImVec2(100, 25)))
		this->tabs[AboutMenuTab] = !this->tabs[AboutMenuTab];


	ImGui::End();
}
// Отрисовывает меню "ABOUT", вызвается в ТОЛЬКО методе "Render".
void Menu::DrawAboutMenu()
{
	ImGui::Begin(xorstr("About"), NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);
	ImGui::SetWindowSize(ImVec2(500, 150));
	ImGui::Image(this->icons[AboutIcon], ImVec2(16, 16));
	ImGui::SameLine();
	ImGui::Text(xorstr("ABOUT"));

	ImGui::SetCursorPos(ImVec2(500 - 25, 5));
	if (ImGui::Button(" ", ImVec2(20, 20)))
		this->tabs[AboutMenuTab] = false;

	PDIRECT3DTEXTURE9 logo;
	D3DXCreateTextureFromResourceA(pDevice, hmodule, MAKEINTRESOURCE(IDB_BITMAP2), &logo);

	ImGui::Image((void*)logo, ImVec2(100, 100));
	ImGui::SameLine();
	ImGui::Text(xorstr("COMPILATION DATE: %s\nCOMPILATION TIME: %s"), xorstr(__DATE__), xorstr(__TIME__));
	ImGui::SetCursorPos(ImVec2(115, 70));
	if (ImGui::Button(xorstr("SITE/SUPPORT"), ImVec2(100, 25)))
		ShellExecute(0, 0, xorstr("https://avhook.ru/"), 0, 0, SW_SHOW);
	ImGui::End();
}
// Отрисовывает список игроков, вызвается в ТОЛЬКО методе "Render".
void Menu::DrawPlayerList()
{
	ImGui::Begin(xorstr("player_list"), NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);
	ImGui::SetWindowSize(ImVec2(800, 340));

	ImGui::Image(icons[0], ImVec2(16, 16));
	ImGui::SameLine();

	ImGui::Text(xorstr("PLAYER LIST"));
	ImGui::SetCursorPos(ImVec2(800 - 25, 5));

	if (ImGui::Button(" ", ImVec2(20, 20)))
		this->tabs[PlayerListTab] = false;

	ImGui::BeginChild("Child###xd", ImVec2(785, 300), true, ImGuiWindowFlags_NoScrollbar);

	for (byte i = 1; i < 33; i++)
	{
		CBaseEntity* ent = (CBaseEntity*)this->entitylist->GetClientEntity(i);

		if (!ent)
			continue;

		if (ent->m_iTeamNum == 3)
			ImGui::Image(this->icons[3], ImVec2(16, 16));
		else
			ImGui::Image(this->icons[4], ImVec2(16, 16));

		ImGui::SameLine();
		ImGui::Text(xorstr("ID-%d   TEAM-ID:   %d   HEALTH:  "), i, ent->m_iTeamNum);
		ImGui::SameLine();
		ImGui::TextColored(ent->GetColorBasedOnHealth(), "%d", ent->m_iHealth);
	}
	ImGui::EndChild();
	ImGui::End();
}
// Отрисовывает меню "SETTINGs", вызвается в ТОЛЬКО методе "Render".
void Menu::DrawSettingsMenu()
{
	ImGui::Begin("Settings", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);
	ImGui::SetWindowSize(ImVec2(555, 252));

	ImGui::Image(this->icons[1], ImVec2(16, 16));
	ImGui::SameLine();

	ImGui::Text(xorstr("AVhook"));

	ImGui::SetCursorPos(ImVec2(555 - 25, 5));
	if (ImGui::Button(" ", ImVec2(20, 20)))
		this->tabs[SettingsMenuTab] = false;

	if (ImGui::Button(xorstr("AIMBOT"), ImVec2(102, 30)))
		this->menutab = 1;

	ImGui::SameLine();
	if (ImGui::Button(xorstr("TRIGGER"), ImVec2(102, 30)))
		this->menutab = 5;

	ImGui::SameLine();
	if (ImGui::Button(xorstr("VISUALS"), ImVec2(102, 30)))
		this->menutab = 2;

	ImGui::SameLine();
	if (ImGui::Button(xorstr("MISC"), ImVec2(102, 30)))
		this->menutab = 3;

	ImGui::SameLine();
	if (ImGui::Button(xorstr("MENU"), ImVec2(102, 30)))
		this->menutab = 4;


	if (this->menutab == 1) // aimbot sector
	{
		AimBotSettings* aimbot_settings = (AimBotSettings*)this->settings[AimbotSettingID];

		ImGui::Text(xorstr("Automatic Target Acquisition System"));

		ImGui::Checkbox(xorstr("Active"),	  &aimbot_settings->active);
		ImGui::SameLine();
		ImGui::Combo(xorstr("HitBox"),		  &aimbot_settings->selected_hitbox, aimbot_settings->hitboxes, IM_ARRAYSIZE(aimbot_settings->hitboxes));
		ImGui::Checkbox(xorstr("Silent"),	  &aimbot_settings->silent);
		ImGui::SameLine();
		ImGui::InputInt(xorstr("FOV"),		  &aimbot_settings->fov);
		ImGui::Checkbox(xorstr("Auto shoot"), &aimbot_settings->auto_shoot);
		ImGui::Checkbox(xorstr("Activate on mouse1"), &aimbot_settings->on_key);

	}
	else if (this->menutab == 2) // esp sector
	{
		GlowWHSettings* glow_esp_settings = (GlowWHSettings*)this->settings[GlowSettingID];
		SnapLinesESP*   snap_esp_settings = (SnapLinesESP*)this->settings[SnapLinesSettingsID];
		BoxESP*         box_esp_settings  = (BoxESP*)this->settings[BoxESPSettingsID];

		ImGui::SetWindowSize(ImVec2(555, 500));

		ImGui::Text(xorstr("Extra Sensory Perception"));

		ImGui::Text(xorstr("Glow ESP"));
		ImGui::Checkbox(xorstr("Active###Glow"),       &glow_esp_settings->active);
		ImGui::SameLine();
		ImGui::ColorEdit4(xorstr("Color###GlowColor"), (float*)&glow_esp_settings->color, ImGuiColorEditFlags_NoInputs);
		ImGui::Combo(xorstr("###GlowEspDrawMode"),     &glow_esp_settings->draw_mode, glow_esp_settings->draw_options, IM_ARRAYSIZE(glow_esp_settings->draw_options));

		ImGui::Text(xorstr("Snap Lines"));
		ImGui::Checkbox(xorstr("Active###Draw lines"), &snap_esp_settings->active);
		ImGui::SameLine();
		ImGui::ColorEdit4(xorstr("Color###lineColor"), (float*)&snap_esp_settings->color, ImGuiColorEditFlags_NoInputs);

		ImGui::InputInt(xorstr("###lineThickness"),    &snap_esp_settings->thickness);
		ImGui::Combo(xorstr("###LinePoint"),	       &snap_esp_settings->selected_bone, snap_esp_settings->bones,        IM_ARRAYSIZE(snap_esp_settings->bones));
		ImGui::Combo(xorstr("###LineEspDrawMode"),	   &snap_esp_settings->draw_mode,     snap_esp_settings->draw_options, IM_ARRAYSIZE(snap_esp_settings->draw_options));

		ImGui::Text(xorstr("Boxes"));
		ImGui::Checkbox(xorstr("Active###Draw boxes"), &box_esp_settings->active);
		ImGui::SameLine();
		ImGui::Checkbox(xorstr("HP value"),			   &box_esp_settings->draw_hp_value);
		ImGui::SameLine();
		ImGui::ColorEdit4(xorstr("Color###boxcolor"),  (float*)&box_esp_settings->color, ImGuiColorEditFlags_NoInputs);
		ImGui::InputInt(xorstr("###boxThickness"),     &box_esp_settings->thickness);
		ImGui::Combo(xorstr("###BoxEspDrawMode"),      &box_esp_settings->draw_mode, box_esp_settings->draw_options, IM_ARRAYSIZE(box_esp_settings->draw_options));

		/*ImGui::Text(xorstr("Skeleton"));
		ImGui::Checkbox(xorstr("Active###Draw skeletones"), &settings::SkeletonESP::on);
		ImGui::SameLine();
		ImGui::ColorEdit4(xorstr("Color###SkeletColor"), (float*)&settings::SkeletonESP::Color, ImGuiColorEditFlags_NoInputs);
		ImGui::InputInt(xorstr("###SkeletThickness"), &settings::SkeletonESP::thicnes);*/
	}
	else if (this->menutab == 3) //misc sector
	{
		MiscSettings* misc_settings = (MiscSettings*)this->settings[MiscSettingsID];

		ImGui::Text(xorstr("Misc configuration"));
		ImGui::Checkbox(xorstr("Bunny hop"),		 &misc_settings->bhop);
		ImGui::Checkbox(xorstr("Desktop wallpaper"), &misc_settings->wallpaper);
		ImGui::Checkbox(xorstr("Show local time"),   &misc_settings->show_time);
		ImGui::Checkbox(xorstr("Show radar"),   &misc_settings->radar);
		if (client->dwLocalPlayer)
			ImGui::SliderInt(xorstr("FOV"), &client->dwLocalPlayer->m_iDefaultFOV, 1, 120);
	}
	else if (this->menutab == 4) // menu settings
	{
		ImGui::SetWindowSize(ImVec2(555, 352));

		ImGui::Text(xorstr("Menu configuration"));
		ImGui::ColorEdit4(xorstr("Border"),        (float*)&this->theme[ImGuiCol_Border],         ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::ColorEdit4(xorstr("Background"),    (float*)&this->theme[ImGuiCol_WindowBg],       ImGuiColorEditFlags_NoInputs);
		ImGui::ColorEdit4(xorstr("Button"),        (float*)&this->theme[ImGuiCol_Button],         ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::ColorEdit4(xorstr("Button active"), (float*)&this->theme[ImGuiCol_ButtonActive],   ImGuiColorEditFlags_NoInputs);
		ImGui::ColorEdit4(xorstr("Text"),          (float*)&this->theme[ImGuiCol_Text],           ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::ColorEdit4(xorstr("Frame"),         (float*)&this->theme[ImGuiCol_FrameBg],        ImGuiColorEditFlags_NoInputs);
		ImGui::ColorEdit4(xorstr("Frame active"),  (float*)&this->theme[ImGuiCol_FrameBgActive],  ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::ColorEdit4(xorstr("Frame hovered"), (float*)&this->theme[ImGuiCol_FrameBgHovered], ImGuiColorEditFlags_NoInputs);
		ImGui::ColorEdit4(xorstr("Text selected"), (float*)&this->theme[ImGuiCol_TextSelectedBg], ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::ColorEdit4(xorstr("Check mark"),    (float*)&this->theme[ImGuiCol_CheckMark],      ImGuiColorEditFlags_NoInputs);
		ImGui::ColorEdit4(xorstr("Radar feature active"),   (float*)&dynamic_cast<RadarSettings*>(this->settings[RadarSettingsID])->active_radar_color,   ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::ColorEdit4(xorstr("Radar feature inactive"), (float*)&dynamic_cast<RadarSettings*>(this->settings[RadarSettingsID])->inactive_radar_color, ImGuiColorEditFlags_NoInputs);
		//ImGui::ColorEdit4(xorstr("Overlay"),       (float*)(&this->misc_settings->), ImGuiColorEditFlags_NoInputs);
	}
	else if (this->menutab == 5) // trigger
	{
		TriggerBotSetting* trigger_bot_settings = dynamic_cast<TriggerBotSetting*>(this->settings[TriggerBotSettingsID]);

		ImGui::Text(xorstr("Trigger bot."));
		ImGui::Checkbox(xorstr("Active"), &trigger_bot_settings->active);
		ImGui::SameLine();
		ImGui::Checkbox(xorstr("Rage"),   &trigger_bot_settings->rage);
		ImGui::SliderInt(xorstr("Delay"), &trigger_bot_settings->delay, 0, 1000);
	}
	else
	{
		ImGui::Text(xorstr("Welcome!"));
	}
	ImGui::End();
}
// Отрисовывает меню "таск бар", вызвается в ТОЛЬКО методе "Render".
void Menu::DrawTaskBar()
{
	ImGui::Begin(xorstr("taskbar"), NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove);

	ImGui::SetWindowPos(ImVec2(0, this->window_size.y - 33));
	ImGui::SetWindowSize(ImVec2(this->window_size.x, 20));

	ImGui::SetCursorPos(ImVec2(3, 5));
	if (ImGui::Button(xorstr("START")))
		this->tabs[StartMenuTab] = !this->tabs[StartMenuTab];

	if (dynamic_cast<MiscSettings*>(this->settings[MiscSettingsID])->show_time)
	{
		ImGui::SetCursorPos(ImVec2(this->window_size.x - 57, 7));
		ImGui::Text(GetTime().c_str());
	}

	ImGui::End();
}
// Запускает отрисовку всего меню
void Menu::Render()
{
	if (!this->render)
		return;

	this->colorfix->RemoveColorFilter();

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (GetAsyncKeyState(VK_INSERT) & 1)
		this->active = !this->active;

	MiscSettings* misc_settings = dynamic_cast<MiscSettings*>(this->settings[MiscSettingsID]);


	this->DrawESP();

	if (misc_settings->radar)
		this->DrawRadar();

	if (this->active)
	{
		if (!misc_settings->wallpaper)
			this->drawlist->AddRectFilled(ImVec2(0, 0), this->window_size, dynamic_cast<MenuSettings*>(this->settings[MenuSettingsID])->background);
		else
			drawlist->AddImage(this->wallpaper_texture, ImVec2(0, 0), this->window_size);

		this->DrawTaskBar();
		if (this->tabs[SettingsMenuTab])
			this->DrawSettingsMenu();
		if (this->tabs[StartMenuTab])
			this->DrawStartMenu();
		if (this->tabs[AboutMenuTab])
			this->DrawAboutMenu();
		if (this->tabs[PlayerListTab])
			this->DrawPlayerList();

	}

	ImGui::EndFrame();
	this->colorfix->RestoreRenderState();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	this->colorfix->RestoreColorFilter();
}

void Menu::DrawESP()
{
	BoxESP* box_settings = (BoxESP*)this->settings[BoxESPSettingsID];
	SnapLinesESP* snap_lines_settings = (SnapLinesESP*)this->settings[SnapLinesSettingsID];

	for (byte i = 1; i < 33; i++)
	{
		CBaseEntity* entity = (CBaseEntity*)this->entitylist->GetClientEntity(i);
		CLocalPlayer* localPlayer = client->dwLocalPlayer;
		
		if (!entity or !localPlayer or client->WorldToScreen(entity->m_vecOrigin).z < 0.01f or entity->m_iHealth <= 0 or entity->m_iTeamNum == localPlayer->m_iTeamNum or entity->m_bDormant)
			continue;

		if (box_settings->active)
		{
			ImVec3 origin = client->WorldToScreen(entity->m_vecOrigin);
			ImVec3 playerhead = entity->GetBonePosition(8);

			playerhead.z += 7.9f;
			playerhead = client->WorldToScreen(playerhead);

			if (playerhead.z > 0.01f)
			{
				if (!box_settings->draw_mode)
					drawlist->DrawBoxEsp(entity, box_settings->thickness,
						box_settings->color, box_settings->draw_hp_value);
				else
					drawlist->DrawBoxEsp(entity, box_settings->thickness, entity->GetColorBasedOnHealth(), box_settings->draw_hp_value);

			}
		}
		if (snap_lines_settings->active)
		{
			ImVec3 pos;

			if (snap_lines_settings->selected_bone == 0)
				pos = entity->GetBonePosition(BONE_HEAD);

			else if (snap_lines_settings->selected_bone == 1)
				pos = entity->GetBonePosition(BONE_BODY);

			else if (snap_lines_settings->selected_bone == 2)
				pos = entity->m_vecOrigin;

			ImVec3 screen = client->WorldToScreen(pos);
			ImVec2 start = ImVec2(this->window_size.x / 2, this->window_size.y);
			
			if (!snap_lines_settings->draw_mode)
				drawlist->AddLine(start, screen, snap_lines_settings->color, snap_lines_settings->thickness);
			else
				drawlist->AddLine(start, screen, entity->GetColorBasedOnHealth(), snap_lines_settings->thickness);
		}
	}
}

std::string Menu::GetDesktopWallpaper()
{

	TCHAR path[260];
	SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, NULL, path);

	std::string path_to_wp = std::string(path);
	return path_to_wp + "\\Microsoft\\Windows\\Themes\\TranscodedWallpaper";
}

void Menu::DrawRadar()
{
	ImGui::Begin(xorstr("radar"), NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);
	ImGui::SetWindowSize(ImVec2(250, 220));
	RadarSettings* rad_settings = dynamic_cast<RadarSettings*>(this->settings[RadarSettingsID]);

	if (this->active)
	{
		ImGui::SetWindowSize(ImVec2(250, 240));

		ImGui::Image(this->icons[RadarIcon], ImVec2(16, 16));
		ImGui::SameLine();
		ImGui::Text(xorstr("RADAR"));
	}
	else
		ImGui::SetWindowSize(ImVec2(250, 220));

	if (dynamic_cast<AimBotSettings*>(settings[AimbotSettingID])->is_working)
		ImGui::TextColored(rad_settings->active_radar_color, xorstr("AIM"));
	else
		ImGui::TextColored(rad_settings->inactive_radar_color, xorstr("AIM"));

	if (dynamic_cast<TriggerBotSetting*>(settings[TriggerBotSettingsID])->active)
		ImGui::TextColored(rad_settings->active_radar_color, xorstr("TRG"));
	else
		ImGui::TextColored(rad_settings->inactive_radar_color, xorstr("TRG"));

	if (dynamic_cast<MiscSettings*>(settings[MiscSettingsID])->bhop)
		ImGui::TextColored(rad_settings->active_radar_color, xorstr("BHP"));
	else
		ImGui::TextColored(rad_settings->inactive_radar_color, xorstr("BHP"));

	if (this->active)
		ImGui::SetCursorPos(ImVec2(40, 30));
	else
		ImGui::SetCursorPos(ImVec2(40, 10));

	ImGui::BeginChild("Child!",ImVec2(200, 200), true, ImGuiWindowFlags_NoScrollbar);
	for (byte i = 2; i < 33; i++)
	{
		auto entity = reinterpret_cast<CBaseEntity*>(this->entitylist->GetClientEntity(i));

		if (!entity)
			continue;

		int x_radar_cord = 100.f + (entity->m_vecOrigin.x - this->client->dwLocalPlayer->m_vecOrigin.x) / 22;
		int y_radar_cord = 100.f - (entity->m_vecOrigin.y - this->client->dwLocalPlayer->m_vecOrigin.y) / 22;

		ImGui::SetCursorPos(ImVec2(x_radar_cord - 8, y_radar_cord + 8));
		if (entity->m_iHealth > 0)
			ImGui::Image(this->icons[TerroristIcon], ImVec2(16, 16));
		
	}
	ImGui::SetCursorPos(ImVec2(100 - 8, 100 + 8));
	ImGui::Image(this->icons[CounterTerroristIcon], ImVec2(16, 16));

	ImGui::EndChild();

	ImGui::End();
}