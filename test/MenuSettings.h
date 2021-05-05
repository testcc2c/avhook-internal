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
	bool	    active          = false;
	ImColor		color           = ImColor(255, 0, 0, 255);
	int			draw_mode       = 0;
	const char* draw_options[2] = { "Custom", "Health" };
	int			thickness       = 1;

	void Restore() override {};
};

class MenuSettings : public Settings
{
public:
	short menutab       = 0;
	bool  start_menu    = false;
	bool  about_menu	= false;
	bool  settings_menu = false;
	bool  player_list   = false;
	ImColor background = ImColor(0, 0, 0, 90);

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
	void Restore() override {};
};
class GlowWHSettings : public ESP
{
	void Restore() override {};
};
class SnapLinesESP : public ESP
{
public:
	int selected_bone = 0;
	const char* bones[3] = { "Head", "Body", "Legs" };
	void Restore() override {};
};
class BoxESP : public ESP
{
public:
	bool draw_hp_value;
	void Restore() override {};
};
class MiscSettings : public Settings
{
public:
	bool bhop;
	bool wallpaper;
	void Restore() override {};
};
class TriggerBotSetting : public Settings
{
public:
	bool active;
	bool rage;
	int delay;
	void Restore() override {};
};