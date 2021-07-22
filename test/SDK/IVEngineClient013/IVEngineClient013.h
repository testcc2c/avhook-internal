#include <Windows.h>
#include "../AbstractInterface.h"

#define CLIENT_DLL_INTERFACE_VERSION		"VClient017"

typedef struct player_info_s
{
	unsigned __int64		uiUnk;
	unsigned __int64		uiXuid;
	char                    szName[128];
	int                     iUserID;
	char                    szGuid[32 + 1];
	unsigned int            uiFriendsID;
	char                    szFriendsName[128];
	bool                    bFakePlayer;
	bool                    bIsHltv;
	unsigned long           ulCustomFiles[4];
	unsigned char           uszFilesDownloader;
} player_info_t;

class IVEngineClient013 : AbstractInterface
{
public:
	player_info_s GetPlayerInfo(int ent_num);
};

