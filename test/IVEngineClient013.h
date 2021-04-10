#define PRINTF_FORMAT_STRING _Printf_format_string_
#define SCANF_FORMAT_STRING _Scanf_format_string_impl_

class IVEngineClient013
{

public:
	// Find the model's surfaces that intersect the given sphere.
	// Returns the number of surfaces filled in.
	virtual int					GetIntersectingSurfaces(
		const int* model,
		const int& vCenter,
		const float radius,
		const bool bOnlyVisibleSurfaces,	// Only return surfaces visible to vCenter.
		int* pInfos,
		const int nMaxInfos) = 0;

	// Get the lighting intensivty for a specified point
	// If bClamp is specified, the resulting Vector is restricted to the 0.0 to 1.0 for each element
	virtual int				GetLightForPoint(const int& pos, bool bClamp) = 0;

	// Traces the line and reports the material impacted as well as the lighting information for the impact point
	virtual int* TraceLineMaterialAndLighting(const int& start, const int& end,
		int& diffuseLightColor, int& baseColor) = 0;

	// Given an input text buffer data pointer, parses a single token into the variable token and returns the new
	//  reading position
	virtual const char* ParseFile(const char* data, char* token, int maxlen) = 0;
	virtual bool				CopyLocalFile(const char* source, const char* destination) = 0;

	// Gets the dimensions of the game window
	virtual void				GetScreenSize(int& width, int& height) = 0;

	// Forwards szCmdString to the server, sent reliably if bReliable is set
	virtual void				ServerCmd(const char* szCmdString, bool bReliable = true) = 0;
	// Inserts szCmdString into the command buffer as if it was typed by the client to his/her console.
	// Note: Calls to this are checked against FCVAR_CLIENTCMD_CAN_EXECUTE (if that bit is not set, then this function can't change it).
	//       Call ClientCmd_Unrestricted to have access to FCVAR_CLIENTCMD_CAN_EXECUTE vars.
	virtual void				ClientCmd(const char* szCmdString) = 0;

	// Fill in the player info structure for the specified player index (name, model, etc.)
	virtual bool				GetPlayerInfo(int ent_num, int* pinfo) = 0;

	// Retrieve the player entity number for a specified userID
	virtual int					GetPlayerForUserID(int userID) = 0;

	// Retrieves text message system information for the specified message by name
	virtual int* TextMessageGet(const char* pName) = 0;

	// Returns true if the console is visible
	virtual bool				Con_IsVisible(void) = 0;

	// Get the entity index of the local player
	virtual int					GetLocalPlayer(void) = 0;

	// Client DLL is hooking a model, loads the model into memory and returns  pointer to the model_t
	virtual const int* LoadModel(const char* pName, bool bProp = false) = 0;

	// Get accurate, sub-frame clock ( profiling use )
	virtual float				Time(void) = 0;

	// Get the exact server timesstamp ( server time ) from the last message received from the server
	virtual float				GetLastTimeStamp(void) = 0;

	// Given a CAudioSource (opaque pointer), retrieve the underlying CSentence object ( stores the words, phonemes, and close
	//  captioning data )
	virtual int* GetSentence(int* pAudioSource) = 0;
	// Given a CAudioSource, determines the length of the underlying audio file (.wav, .mp3, etc.)
	virtual float				GetSentenceLength(int* pAudioSource) = 0;
	// Returns true if the sound is streaming off of the hard disk (instead of being memory resident)
	virtual bool				IsStreaming(int* pAudioSource) const = 0;

	// Copy current view orientation into va
	virtual void				GetViewAngles(int& va) = 0;
	// Set current view orientation from va
	virtual void				SetViewAngles(int& va) = 0;

	// Retrieve the current game's maxclients setting
	virtual int					GetMaxClients(void) = 0;

	// Given the string pBinding which may be bound to a key, 
	//  returns the string name of the key to which this string is bound. Returns NULL if no such binding exists
	virtual	const char* Key_LookupBinding(const char* pBinding) = 0;

	// Given the name of the key "mouse1", "e", "tab", etc., return the string it is bound to "+jump", "impulse 50", etc.
	virtual const char* Key_BindingForKey(int code) = 0;

	// key trapping (for binding keys)
	virtual void				StartKeyTrapMode(void) = 0;
	virtual bool				CheckDoneKeyTrapping(int& code) = 0;

	// Returns true if the player is fully connected and active in game (i.e, not still loading)
	virtual bool				IsInGame(void) = 0;
	// Returns true if the player is connected, but not necessarily active in game (could still be loading)
	virtual bool				IsConnected(void) = 0;
	// Returns true if the loading plaque should be drawn
	virtual bool				IsDrawingLoadingImage(void) = 0;

	// Prints the formatted string to the notification area of the screen ( down the right hand edge
	//  numbered lines starting at position 0
	virtual void				Con_NPrintf(int pos, PRINTF_FORMAT_STRING const char* fmt, ...) = 0;
	// Similar to Con_NPrintf, but allows specifying custom text color and duration information
	virtual void				Con_NXPrintf(const struct con_nprint_s* info, const char* fmt, ...) = 0;

	// Is the specified world-space bounding box inside the view frustum?
	virtual int					IsBoxVisible(const int& mins, const int& maxs) = 0;

	// Is the specified world-space boudning box in the same PVS cluster as the view origin?
	virtual int					IsBoxInViewCluster(const int& mins, const int& maxs) = 0;
	
		// Returns true if the specified box is outside of the view frustum and should be culled
	_Printf_format_string_ virtual bool				CullBox(const int& mins, const int& maxs) = 0;

	// Allow the sound system to paint additional data (during lengthy rendering operations) to prevent stuttering sound.
	virtual void				Sound_ExtraUpdate(void) = 0;

	// Get the current game directory ( e.g., hl2, tf2, cstrike, hl1 )
	virtual const char* GetGameDirectory(void) = 0;

	// Get access to the world to screen transformation matrix
	virtual const int& WorldToScreenMatrix() = 0;

	// Get the matrix to move a point from world space into view space
	// (translate and rotate so the camera is at the origin looking down X).
	virtual const int& WorldToViewMatrix() = 0;

	// The .bsp file can have mod-specified data lumps. These APIs are for working with such game lumps.

	// Get mod-specified lump version id for the specified game data lump
	virtual int					GameLumpVersion(int lumpId) const = 0;
	// Get the raw size of the specified game data lump.
	virtual int					GameLumpSize(int lumpId) const = 0;
	// Loads a game lump off disk, writing the data into the buffer pointed to bye pBuffer
	// Returns false if the data can't be read or the destination buffer is too small
	virtual bool				LoadGameLump(int lumpId, void* pBuffer, int size) = 0;

	// Returns the number of leaves in the level
	virtual int					LevelLeafCount() const = 0;

	// Gets a way to perform spatial queries on the BSP tree
	virtual int* GetBSPTreeQuery() = 0;

	// Convert texlight to gamma...
	virtual void		LinearToGamma(float* linear, float* gamma) = 0;

	// Get the lightstyle value
	virtual float		LightStyleValue(int style) = 0;

	// Computes light due to dynamic lighting at a point
	// If the normal isn't specified, then it'll return the maximum lighting
	virtual void		ComputeDynamicLighting(const int& pt, const int* pNormal, int& color) = 0;

	// Returns the color of the ambient light
	virtual void		GetAmbientLightColor(int& color) = 0;

	// Returns the dx support level
	virtual int			GetDXSupportLevel() = 0;

	// GR - returns the HDR support status
	virtual bool        SupportsHDR() = 0;

	// Replace the engine's material system pointer.
	virtual void		Mat_Stub(int* pMatSys) = 0;

	// Get the name of the current map
	virtual void GetChapterName(char* pchBuff, int iMaxLength) = 0;
	virtual char const* GetLevelName(void) = 0;
	virtual int	GetLevelVersion(void) = 0;
#if !defined( NO_VOICE )
	// Obtain access to the voice tweaking API
	virtual struct IVoiceTweak_s* GetVoiceTweakAPI(void) = 0;
#endif
	// Tell engine stats gathering system that the rendering frame is beginning/ending
	virtual void		EngineStats_BeginFrame(void) = 0;
	virtual void		EngineStats_EndFrame(void) = 0;

	// This tells the engine to fire any events (temp entity messages) that it has queued up this frame. 
	// It should only be called once per frame.
	virtual void		FireEvents() = 0;

	// Returns an area index if all the leaves are in the same area. If they span multple areas, then it returns -1.
	virtual int			GetLeavesArea(int* pLeaves, int nLeaves) = 0;

	// Returns true if the box touches the specified area's frustum.
	virtual bool		DoesBoxTouchAreaFrustum(const int& mins, const int& maxs, int iArea) = 0;

	// Sets the hearing origin (i.e., the origin and orientation of the listener so that the sound system can spatialize 
	//  sound appropriately ).
	virtual void		SetAudioState(const int& state) = 0;

	// Sentences / sentence groups
	virtual int			SentenceGroupPick(int groupIndex, char* name, int nameBufLen) = 0;
	virtual int			SentenceGroupPickSequential(int groupIndex, char* name, int nameBufLen, int sentenceIndex, int reset) = 0;
	virtual int			SentenceIndexFromName(const char* pSentenceName) = 0;
	virtual const char* SentenceNameFromIndex(int sentenceIndex) = 0;
	virtual int			SentenceGroupIndexFromName(const char* pGroupName) = 0;
	virtual const char* SentenceGroupNameFromIndex(int groupIndex) = 0;
	virtual float		SentenceLength(int sentenceIndex) = 0;

	// Computes light due to dynamic lighting at a point
	// If the normal isn't specified, then it'll return the maximum lighting
	// If pBoxColors is specified (it's an array of 6), then it'll copy the light contribution at each box side.
	virtual void		ComputeLighting(const int& pt, const int* pNormal, bool bClamp, int& color, int* pBoxColors = NULL) = 0;

	// Activates/deactivates an occluder...
	virtual void		ActivateOccluder(int nOccluderIndex, bool bActive) = 0;
	virtual bool		IsOccluded(const int& vecAbsMins, const int& vecAbsMaxs) = 0;

	// The save restore system allocates memory from a shared memory pool, use this allocator to allocate/free saverestore 
	//  memory.
	virtual void* SaveAllocMemory(size_t num, size_t size) = 0;
	virtual void		SaveFreeMemory(void* pSaveMem) = 0;

	// returns info interface for client netchannel
	virtual int* GetNetChannelInfo(void) = 0;

	// Debugging functionality:
	// Very slow routine to draw a physics model
	virtual void		DebugDrawPhysCollide(const int* pCollide, int* pMaterial, int& transform, const int& color) = 0;
	// This can be used to notify test scripts that we're at a particular spot in the code.
	virtual void		CheckPoint(const char* pName) = 0;
	// Draw portals if r_DrawPortals is set (Debugging only)
	virtual void		DrawPortals() = 0;
	// Determine whether the client is playing back or recording a demo
	virtual bool		IsPlayingDemo(void) = 0;
	virtual bool		IsRecordingDemo(void) = 0;
	virtual bool		IsPlayingTimeDemo(void) = 0;
	virtual int			GetDemoRecordingTick(void) = 0;
	virtual int			GetDemoPlaybackTick(void) = 0;
	virtual int			GetDemoPlaybackStartTick(void) = 0;
	virtual float		GetDemoPlaybackTimeScale(void) = 0;
	virtual int			GetDemoPlaybackTotalTicks(void) = 0;
	// Is the game paused?
	virtual bool		IsPaused(void) = 0;
	// Is the game currently taking a screenshot?
	virtual bool		IsTakingScreenshot(void) = 0;
	// Is this a HLTV broadcast ?
	virtual bool		IsHLTV(void) = 0;
	// is this level loaded as just the background to the main menu? (active, but unplayable)
	virtual bool		IsLevelMainMenuBackground(void) = 0;
	// returns the name of the background level
	virtual void		GetMainMenuBackgroundName(char* dest, int destlen) = 0;

	// Get video modes
	virtual void		GetVideoModes(int& nCount, int*& pModes) = 0;

	// Occlusion system control
	virtual void		SetOcclusionParameters(const int& params) = 0;

	// What language is the user expecting to hear .wavs in, "english" or another...
	virtual void		GetUILanguage(char* dest, int destlen) = 0;

	// Can skybox be seen from a particular point?
	virtual int IsSkyboxVisibleFromPoint(const int& vecPoint) = 0;

	// Get the pristine map entity lump string.  (e.g., used by CS to reload the map entities when restarting a round.)
	virtual const char* GetMapEntitiesString() = 0;

	// Is the engine in map edit mode ?
	virtual bool		IsInEditMode(void) = 0;

	// current screen aspect ratio (eg. 4.0f/3.0f, 16.0f/9.0f)
	virtual float		GetScreenAspectRatio() = 0;

	// allow the game UI to login a user
	virtual bool		REMOVED_SteamRefreshLogin(const char* password, bool isSecure) = 0;
	virtual bool		REMOVED_SteamProcessCall(bool& finished) = 0;

	// allow other modules to know about engine versioning (one use is a proxy for network compatability)
	virtual unsigned int	GetEngineBuildNumber() = 0; // engines build
	virtual const char* GetProductVersionString() = 0; // mods version number (steam.inf)

	// Communicates to the color correction editor that it's time to grab the pre-color corrected frame
	// Passes in the actual size of the viewport
	virtual void			GrabPreColorCorrectedFrame(int x, int y, int width, int height) = 0;

	virtual bool			IsHammerRunning() const = 0;

	// Inserts szCmdString into the command buffer as if it was typed by the client to his/her console.
	// And then executes the command string immediately (vs ClientCmd() which executes in the next frame)
	//
	// Note: this is NOT checked against the FCVAR_CLIENTCMD_CAN_EXECUTE vars.
	virtual void			ExecuteClientCmd(const char* szCmdString) = 0;

	// returns if the loaded map was processed with HDR info. This will be set regardless
	// of what HDR mode the player is in.
	virtual bool MapHasHDRLighting(void) = 0;

	virtual int	GetAppID() = 0;

	// Just get the leaf ambient light - no caching, no samples
	virtual int			GetLightForPointFast(const int& pos, bool bClamp) = 0;

	// This version does NOT check against FCVAR_CLIENTCMD_CAN_EXECUTE.
	virtual void			ClientCmd_Unrestricted(const char* szCmdString) = 0;
};