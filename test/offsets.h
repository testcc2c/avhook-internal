#pragma once
#include <Windows.h>

#define STR_MERGE_IMPL(a, b) a##b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)
#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]
#define DEFINE_MEMBER_N(type, name, offset) struct {unsigned char MAKE_PAD(offset); type name;}


#define BONE_HEAD 8
#define BONE_BODY 6


namespace netvars {
	constexpr DWORD cs_gamerules_data = 0x0;
	constexpr DWORD m_ArmorValue = 0xB378;
	constexpr DWORD m_Collision = 0x320;
	constexpr DWORD m_CollisionGroup = 0x474;
	constexpr DWORD m_Local = 0x2FBC;
	constexpr DWORD m_MoveType = 0x25C;
	constexpr DWORD m_OriginalOwnerXuidHigh = 0x31C4;
	constexpr DWORD m_OriginalOwnerXuidLow = 0x31C0;
	constexpr DWORD m_SurvivalGameRuleDecisionTypes = 0x1328;
	constexpr DWORD m_SurvivalRules = 0xD00;
	constexpr DWORD m_aimPunchAngle = 0x302C;
	constexpr DWORD m_aimPunchAngleVel = 0x3038;
	constexpr DWORD m_angEyeAnglesX = 0xB37C;
	constexpr DWORD m_angEyeAnglesY = 0xB380;
	constexpr DWORD m_bBombDefused = 0x29B0;
	constexpr DWORD m_bBombPlanted = 0x9A5;
	constexpr DWORD m_bBombTicking = 0x2980;
	constexpr DWORD m_bFreezePeriod = 0x20;
	constexpr DWORD m_bGunGameImmunity = 0x3944;
	constexpr DWORD m_bHasDefuser = 0xB388;
	constexpr DWORD m_bHasHelmet = 0xB36C;
	constexpr DWORD m_bInReload = 0x32A5;
	constexpr DWORD m_bIsDefusing = 0x3930;
	constexpr DWORD m_bIsQueuedMatchmaking = 0x74;
	constexpr DWORD m_bIsScoped = 0x3928;
	constexpr DWORD m_bIsValveDS = 0x7C;
	constexpr DWORD m_bSpotted = 0x93D;
	constexpr DWORD m_bSpottedByMask = 0x980;
	constexpr DWORD m_bStartedArming = 0x33F0;
	constexpr DWORD m_bUseCustomAutoExposureMax = 0x9D9;
	constexpr DWORD m_bUseCustomAutoExposureMin = 0x9D8;
	constexpr DWORD m_bUseCustomBloomScale = 0x9DA;
	constexpr DWORD m_clrRender = 0x70;
	constexpr DWORD m_dwBoneMatrix = 0x26A8;
	constexpr DWORD m_fAccuracyPenalty = 0x3330;
	constexpr DWORD m_fFlags = 0x104;
	constexpr DWORD m_flC4Blow = 0x2990;
	constexpr DWORD m_flCustomAutoExposureMax = 0x9E0;
	constexpr DWORD m_flCustomAutoExposureMin = 0x9DC;
	constexpr DWORD m_flCustomBloomScale = 0x9E4;
	constexpr DWORD m_flDefuseCountDown = 0x29AC;
	constexpr DWORD m_flDefuseLength = 0x29A8;
	constexpr DWORD m_flFallbackWear = 0x31D0;
	constexpr DWORD m_flFlashDuration = 0xA420;
	constexpr DWORD m_flFlashMaxAlpha = 0xA41C;
	constexpr DWORD m_flLastBoneSetupTime = 0x2924;
	constexpr DWORD m_flLowerBodyYawTarget = 0x3A90;
	constexpr DWORD m_flNextAttack = 0x2D70;
	constexpr DWORD m_flNextPrimaryAttack = 0x3238;
	constexpr DWORD m_flSimulationTime = 0x268;
	constexpr DWORD m_flTimerLength = 0x2994;
	constexpr DWORD m_hActiveWeapon = 0x2EF8;
	constexpr DWORD m_hBombDefuser = 0x29B4;
	constexpr DWORD m_hMyWeapons = 0x2DF8;
	constexpr DWORD m_hObserverTarget = 0x338C;
	constexpr DWORD m_hOwner = 0x29CC;
	constexpr DWORD m_hOwnerEntity = 0x14C;
	constexpr DWORD m_hViewModel = 0x32F8;
	constexpr DWORD m_iAccountID = 0x2FC8;
	constexpr DWORD m_iClip1 = 0x3264;
	constexpr DWORD m_iCompetitiveRanking = 0x1A84;
	constexpr DWORD m_iCompetitiveWins = 0x1B88;
	constexpr DWORD m_iCrosshairId = 0xB3E4;
	constexpr DWORD m_iDefaultFOV = 0x332C;
	constexpr DWORD m_iEntityQuality = 0x2FAC;
	constexpr DWORD m_iFOVStart = 0x31E8;
	constexpr DWORD m_iGlowIndex = 0xA438;
	constexpr DWORD m_iHealth = 0x100;
	constexpr DWORD m_iItemDefinitionIndex = 0x2FAA;
	constexpr DWORD m_iItemIDHigh = 0x2FC0;
	constexpr DWORD m_iMostRecentModelBoneCounter = 0x2690;
	constexpr DWORD m_iObserverMode = 0x3378;
	constexpr DWORD m_iShotsFired = 0xA390;
	constexpr DWORD m_iState = 0x3258;
	constexpr DWORD m_iTeamNum = 0xF4;
	constexpr DWORD m_lifeState = 0x25F;
	constexpr DWORD m_nBombSite = 0x2984;
	constexpr DWORD m_nFallbackPaintKit = 0x31C8;
	constexpr DWORD m_nFallbackSeed = 0x31CC;
	constexpr DWORD m_nFallbackStatTrak = 0x31D4;
	constexpr DWORD m_nForceBone = 0x268C;
	constexpr DWORD m_nTickBase = 0x3430;
	constexpr DWORD m_nViewModelIndex = 0x29C0;
	constexpr DWORD m_rgflCoordinateFrame = 0x444;
	constexpr DWORD m_szCustomName = 0x303C;
	constexpr DWORD m_szLastPlaceName = 0x35B4;
	constexpr DWORD m_thirdPersonViewAngles = 0x31D8;
	constexpr DWORD m_vecOrigin = 0x138;
	constexpr DWORD m_vecVelocity = 0x114;
	constexpr DWORD m_vecViewOffset = 0x108;
	constexpr DWORD m_viewPunchAngle = 0x3020;
	constexpr DWORD m_zoomLevel = 0x33D0;
} // namespace netvars
namespace signatures {
	constexpr DWORD anim_overlays = 0x2980;
	constexpr DWORD clientstate_choked_commands = 0x4D30;
	constexpr DWORD clientstate_delta_ticks = 0x174;
	constexpr DWORD clientstate_last_outgoing_command = 0x4D2C;
	constexpr DWORD clientstate_net_channel = 0x9C;
	constexpr DWORD convar_name_hash_table = 0x2F0F8;
	constexpr DWORD dwClientState = 0x58EFE4;
	constexpr DWORD dwClientState_GetLocalPlayer = 0x180;
	constexpr DWORD dwClientState_IsHLTV = 0x4D48;
	constexpr DWORD dwClientState_Map = 0x28C;
	constexpr DWORD dwClientState_MapDirectory = 0x188;
	constexpr DWORD dwClientState_MaxPlayer = 0x388;
	constexpr DWORD dwClientState_PlayerInfo = 0x52C0;
	constexpr DWORD dwClientState_State = 0x108;
	constexpr DWORD dwClientState_ViewAngles = 0x4D90;
	constexpr DWORD dwEntityList = 0x4DA2F24;
	constexpr DWORD dwForceAttack = 0x31D446C;
	constexpr DWORD dwForceAttack2 = 0x31D4478;
	constexpr DWORD dwForceBackward = 0x31D44C0;
	constexpr DWORD dwForceForward = 0x31D44CC;
	constexpr DWORD dwForceJump = 0x524CE84;
	constexpr DWORD dwForceLeft = 0x31D44E4;
	constexpr DWORD dwForceRight = 0x31D44D8;
	constexpr DWORD dwGameDir = 0x62D7F8;
	constexpr DWORD dwGameRulesProxy = 0x52C016C;
	constexpr DWORD dwGetAllClasses = 0xDB2F9C;
	constexpr DWORD dwGlobalVars = 0x58ECE8;
	constexpr DWORD dwGlowObjectManager = 0x52EB520;
	constexpr DWORD dwInput = 0x51F4508;
	constexpr DWORD dwInterfaceLinkList = 0x946254;
	constexpr DWORD dwLocalPlayer = 0xD8B2CC;
	constexpr DWORD dwMouseEnable = 0xD90E70;
	constexpr DWORD dwMouseEnablePtr = 0xD90E40;
	constexpr DWORD dwPlayerResource = 0x31D27E0;
	constexpr DWORD dwRadarBase = 0x51D7C9C;
	constexpr DWORD dwSensitivity = 0xD90D0C;
	constexpr DWORD dwSensitivityPtr = 0xD90CE0;
	constexpr DWORD dwSetClanTag = 0x8A1A0;
	constexpr DWORD dwViewMatrix = 0x4D94824;
	constexpr DWORD dwWeaponTable = 0x51F4FC8;
	constexpr DWORD dwWeaponTableIndex = 0x325C;
	constexpr DWORD dwYawPtr = 0xD90AD0;
	constexpr DWORD dwZoomSensitivityRatioPtr = 0xD95D70;
	constexpr DWORD dwbSendPackets = 0xD745A;
	constexpr DWORD dwppDirect3DDevice9 = 0xA7050;
	constexpr DWORD find_hud_element = 0x26D7E320;
	constexpr DWORD force_update_spectator_glow = 0x3AD962;
	constexpr DWORD interface_engine_cvar = 0x3E9EC;
	constexpr DWORD is_c4_owner = 0x3BA430;
	constexpr DWORD m_bDormant = 0xED;
	constexpr DWORD m_flSpawnTime = 0xA370;
	constexpr DWORD m_pStudioHdr = 0x294C;
	constexpr DWORD m_pitchClassPtr = 0x51D7F38;
	constexpr DWORD m_yawClassPtr = 0xD90AD0;
	constexpr DWORD model_ambient_min = 0x59205C;
	constexpr DWORD set_abs_angles = 0x1DF9C0;
	constexpr DWORD set_abs_origin = 0x1DF800;
} // namespace signatures