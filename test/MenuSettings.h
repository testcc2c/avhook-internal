#pragma once
#include "imgui/imgui.h"

class Settings
{
public:
	virtual void Restore() = 0;

};
class ESP : public Settings
{
public:
	bool active = false;
	ImColor color = ImColor(255, 0, 0, 255);
	int draw_mode = 0;
	const char* draw_options[2] = { "Custom", "Health" };
	int thickness;
};

class MenuSettings : public Settings
{
public:
	short menutab       = 0;
	bool  start_menu    = false;
	bool  about_menu	= false;
	bool  settings_menu = false;
	bool  player_list   = false;

	void Restore() override;
};
class AimBotSettings : public Settings
{
public:
	bool			   active	       = false;
	bool			   auto_shoot	   = false;
	bool			   silent		   = false;
	int				   fov			   = 10; 
	int selected_hitbox				   = 8;
	const char* hitboxes[3]			   = { "Head", "Body", "Legs" };
	
};
class GlowWHSettings : public ESP
{

};
class SnapLinesESP : public ESP
{
public:
	int selected_bone = 0;
	const char* bones[3] = { "Head", "Body", "Legs" };
};
class BoxESP : public ESP
{
public:
	bool draw_hp_value;
};