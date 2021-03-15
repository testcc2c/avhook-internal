#pragma once
#include <Windows.h>

#include <d3d9.h>
#include <d3dx9.h>
#include "DirectX9Drawer.h"
#include "kiero/kiero.h"
#include "kiero/minhook/include/MinHook.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx9.h"

#include "settings.h"
#include "DX9ColorFix.h"

#include "bhop.h"
#include "GlowWhInGame.h"
#include "bhop.h"
#include "CBaseEntity.h"
#include "TriggerBot.h"

#include "CBaseEntity.h"
#include <iostream>

typedef long(__stdcall* EndScene)(LPDIRECT3DDEVICE9);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);