#include "bhop.h"

void BunnyHop::HandleBhop()
{
	__try
	{
		switch (this->clientbase->dwLocalPlayer->m_fFlags)
		{
		case FL_ONGROUND:
		case FL_ONGROUND_DUCK:
			this->clientbase->dwForceJump = 5;
			Sleep(10);
			this->clientbase->dwForceJump = 4;
			break;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{

	}
}