#pragma once
#include <Windows.h>

#define STR_MERGE_IMPL(a, b) a##b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)
#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]
#define DEFINE_MEMBER_N(type, name, offset) struct {unsigned char MAKE_PAD(offset); type name;}

#define WINDOW_NAME "Counter-Strike: Global Offensive"

#define BONE_HEAD 8
#define BONE_BODY 6
#define BONE_LEGS 0
#define FL_ONGROUND 257
#define FL_ONGROUND_DUCK 263

namespace netvars {
	const DWORD cs_gamerules_data = 0x0;
	const DWORD m_ArmorValue = 0xB378;
	const DWORD m_Collision = 0x320;
	const DWORD m_CollisionGroup = 0x474;
	const DWORD m_Local = 0x2FBC;
	const DWORD m_MoveType = 0x25C;
	const DWORD m_OriginalOwnerXuidHigh = 0x31C4;
	const DWORD m_OriginalOwnerXuidLow = 0x31C0;
	const DWORD m_SurvivalGameRuleDecisionTypes = 0x1328;
	const DWORD m_SurvivalRules = 0xD00;
	const DWORD m_aimPunchAngle = 0x302C;
	const DWORD m_aimPunchAngleVel = 0x3038;
	const DWORD m_angEyeAnglesX = 0xB37C;
	const DWORD m_angEyeAnglesY = 0xB380;
	const DWORD m_bBombDefused = 0x29B0;
	const DWORD m_bBombPlanted = 0x9A5;
	const DWORD m_bBombTicking = 0x2980;
	const DWORD m_bFreezePeriod = 0x20;
	const DWORD m_bGunGameImmunity = 0x3944;
	const DWORD m_bHasDefuser = 0xB388;
	const DWORD m_bHasHelmet = 0xB36C;
	const DWORD m_bInReload = 0x32A5;
	const DWORD m_bIsDefusing = 0x3930;
	const DWORD m_bIsQueuedMatchmaking = 0x74;
	const DWORD m_bIsScoped = 0x3928;
	const DWORD m_bIsValveDS = 0x7C;
	const DWORD m_bSpotted = 0x93D;
	const DWORD m_bSpottedByMask = 0x980;
	const DWORD m_bStartedArming = 0x33F0;
	const DWORD m_bUseCustomAutoExposureMax = 0x9D9;
	const DWORD m_bUseCustomAutoExposureMin = 0x9D8;
	const DWORD m_bUseCustomBloomScale = 0x9DA;
	const DWORD m_clrRender = 0x70;
	const DWORD m_dwBoneMatrix = 0x26A8;
	const DWORD m_fAccuracyPenalty = 0x3330;
	const DWORD m_fFlags = 0x104;
	const DWORD m_flC4Blow = 0x2990;
	const DWORD m_flCustomAutoExposureMax = 0x9E0;
	const DWORD m_flCustomAutoExposureMin = 0x9DC;
	const DWORD m_flCustomBloomScale = 0x9E4;
	const DWORD m_flDefuseCountDown = 0x29AC;
	const DWORD m_flDefuseLength = 0x29A8;
	const DWORD m_flFallbackWear = 0x31D0;
	const DWORD m_flFlashDuration = 0xA420;
	const DWORD m_flFlashMaxAlpha = 0xA41C;
	const DWORD m_flLastBoneSetupTime = 0x2924;
	const DWORD m_flLowerBodyYawTarget = 0x3A90;
	const DWORD m_flNextAttack = 0x2D70;
	const DWORD m_flNextPrimaryAttack = 0x3238;
	const DWORD m_flSimulationTime = 0x268;
	const DWORD m_flTimerLength = 0x2994;
	const DWORD m_hActiveWeapon = 0x2EF8;
	const DWORD m_hBombDefuser = 0x29B4;
	const DWORD m_hMyWeapons = 0x2DF8;
	const DWORD m_hObserverTarget = 0x338C;
	const DWORD m_hOwner = 0x29CC;
	const DWORD m_hOwnerEntity = 0x14C;
	const DWORD m_hViewModel = 0x32F8;
	const DWORD m_iAccountID = 0x2FC8;
	const DWORD m_iClip1 = 0x3264;
	const DWORD m_iCompetitiveRanking = 0x1A84;
	const DWORD m_iCompetitiveWins = 0x1B88;
	const DWORD m_iCrosshairId = 0xB3E4;
	const DWORD m_iDefaultFOV = 0x332C;
	const DWORD m_iEntityQuality = 0x2FAC;
	const DWORD m_iFOVStart = 0x31E8;
	const DWORD m_iGlowIndex = 0xA438;
	const DWORD m_iHealth = 0x100;
	const DWORD m_iItemDefinitionIndex = 0x2FAA;
	const DWORD m_iItemIDHigh = 0x2FC0;
	const DWORD m_iMostRecentModelBoneCounter = 0x2690;
	const DWORD m_iObserverMode = 0x3378;
	const DWORD m_iShotsFired = 0xA390;
	const DWORD m_iState = 0x3258;
	const DWORD m_iTeamNum = 0xF4;
	const DWORD m_lifeState = 0x25F;
	const DWORD m_nBombSite = 0x2984;
	const DWORD m_nFallbackPaintKit = 0x31C8;
	const DWORD m_nFallbackSeed = 0x31CC;
	const DWORD m_nFallbackStatTrak = 0x31D4;
	const DWORD m_nForceBone = 0x268C;
	const DWORD m_nTickBase = 0x3430;
	const DWORD m_nViewModelIndex = 0x29C0;
	const DWORD m_rgflCoordinateFrame = 0x444;
	const DWORD m_szCustomName = 0x303C;
	const DWORD m_szLastPlaceName = 0x35B4;
	const DWORD m_thirdPersonViewAngles = 0x31D8;
	const DWORD m_vecOrigin = 0x138;
	const DWORD m_vecVelocity = 0x114;
	const DWORD m_vecViewOffset = 0x108;
	const DWORD m_viewPunchAngle = 0x3020;
	const DWORD m_zoomLevel = 0x33D0;
} // namespace netvars
namespace signatures {
	const DWORD anim_overlays = 0x2980;
	const DWORD clientstate_choked_commands = 0x4D30;
	const DWORD clientstate_delta_ticks = 0x174;
	const DWORD clientstate_last_outgoing_command = 0x4D2C;
	const DWORD clientstate_net_channel = 0x9C;
	const DWORD convar_name_hash_table = 0x2F0F8;
	const DWORD dwClientState = 0x588FE4;
	const DWORD dwClientState_GetLocalPlayer = 0x180;
	const DWORD dwClientState_IsHLTV = 0x4D48;
	const DWORD dwClientState_Map = 0x28C;
	const DWORD dwClientState_MapDirectory = 0x188;
	const DWORD dwClientState_MaxPlayer = 0x388;
	const DWORD dwClientState_PlayerInfo = 0x52C0;
	const DWORD dwClientState_State = 0x108;
	const DWORD dwClientState_ViewAngles = 0x4D90;
	const DWORD dwEntityList = 0x4DA3F9C;
	const DWORD dwForceAttack = 0x31D54DC;
	const DWORD dwForceAttack2 = 0x31D54E8;
	const DWORD dwForceBackward = 0x31D5530;
	const DWORD dwForceForward = 0x31D553C;
	const DWORD dwForceJump = 0x524DEDC;
	const DWORD dwForceLeft = 0x31D5554;
	const DWORD dwForceRight = 0x31D5548;
	const DWORD dwGameDir = 0x6277F8;
	const DWORD dwGameRulesProxy = 0x52C11BC;
	const DWORD dwGetAllClasses = 0xDB3F8C;
	const DWORD dwGlobalVars = 0x588CE8;
	const DWORD dwGlowObjectManager = 0x52EC580;
	const DWORD dwInput = 0x51F5560;
	const DWORD dwInterfaceLinkList = 0x946F44;
	const DWORD dwLocalPlayer = 0xD8C2BC;
	const DWORD dwMouseEnable = 0xD91E60;
	const DWORD dwMouseEnablePtr = 0xD91E30;
	const DWORD dwPlayerResource = 0x31D3850;
	const DWORD dwRadarBase = 0x51D8D14;
	const DWORD dwSensitivity = 0xD91CFC;
	const DWORD dwSensitivityPtr = 0xD91CD0;
	const DWORD dwSetClanTag = 0x8A1B0;
	const DWORD dwViewMatrix = 0x4D958B4;
	const DWORD dwWeaponTable = 0x51F6020;
	const DWORD dwWeaponTableIndex = 0x325C;
	const DWORD dwYawPtr = 0xD91AC0;
	const DWORD dwZoomSensitivityRatioPtr = 0xD96D60;
	const DWORD dwbSendPackets = 0xD749A;
	const DWORD dwppDirect3DDevice9 = 0xA7050;
	const DWORD find_hud_element = 0x2D4FE320;
	const DWORD force_update_spectator_glow = 0x3AE412;
	const DWORD interface_engine_cvar = 0x3E9EC;
	const DWORD is_c4_owner = 0x3BAF00;
	const DWORD m_bDormant = 0xED;
	const DWORD m_flSpawnTime = 0xA370;
	const DWORD m_pStudioHdr = 0x294C;
	const DWORD m_pitchClassPtr = 0x51D8FB0;
	const DWORD m_yawClassPtr = 0xD91AC0;
	const DWORD model_ambient_min = 0x58C05C;
	const DWORD set_abs_angles = 0x1DF9C0;
	const DWORD set_abs_origin = 0x1DF800;
} // namespace signatures