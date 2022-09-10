#include "remote_gibme.h"

#include <string>

#include <interface.h>
#include <dbg.h>
#include <convar.h>
#include <messagebuffer.h>

using namespace std;

CRemoteGibme g_RemoteGibme;
EXPOSE_SINGLE_INTERFACE_GLOBALVAR(CRemoteGibme, IClientPlugin, CLIENT_PLUGIN_INTERFACE_VERSION, g_RemoteGibme);

CMessageBuffer SayTextBuffer;

UserMsgHookFn ORIG_UserMsgHook_SayText = NULL;
DetourHandle_t hUserMsgHook_SayText = 0;

int UserMsgHook_SayText(const char* pszName, int iSize, void* pBuffer)
{
	SayTextBuffer.Init(pBuffer, iSize, true);

	int playerIndex = SayTextBuffer.ReadByte();
	string playerMessage(SayTextBuffer.ReadString());
	
	// Chat messages start with 0x2 (STX Start of Text)
	if (playerMessage.length() > 0 && playerMessage.at(0) == 2) {
		player_info_s* playerInfo = g_pEngineStudio->PlayerInfo(playerIndex - 1);
		size_t playerNameLength = strlen(playerInfo->name);
		string message = playerMessage.substr(playerNameLength + 3, playerMessage.length() - playerNameLength - 4); // Parse message by slicing with player name length. Also removing \n at the end of message

		if (message.compare("!remotegib") == 0 || message.compare("|remotegib") == 0) {
			g_pEngineFuncs->ClientCmd("gibme\n");
		}
	}

	return ORIG_UserMsgHook_SayText(pszName, iSize, pBuffer);
}

api_version_s CRemoteGibme::GetAPIVersion()
{
	return SVENMOD_API_VER;
}

bool CRemoteGibme::Load(CreateInterfaceFn pfnSvenModFactory, ISvenModAPI* pSvenModAPI, IPluginHelpers* pPluginHelpers)
{
	BindApiToGlobals(pSvenModAPI);

	hUserMsgHook_SayText = g_pHooks->HookUserMessage("SayText", UserMsgHook_SayText, &ORIG_UserMsgHook_SayText);

	return true;
}

void CRemoteGibme::PostLoad(bool bGlobalLoad)
{
}

void CRemoteGibme::Unload(void)
{
	g_pHooks->UnhookUserMessage(hUserMsgHook_SayText);
}

bool CRemoteGibme::Pause(void)
{
	return true;
}

void CRemoteGibme::Unpause(void)
{
}

void CRemoteGibme::GameFrame(client_state_t state, double frametime, bool bPostRunCmd)
{
}

PLUGIN_RESULT CRemoteGibme::Draw(void)
{
	return PLUGIN_CONTINUE;
}

PLUGIN_RESULT CRemoteGibme::DrawHUD(float time, int intermission)
{
	return PLUGIN_CONTINUE;
}

const char* CRemoteGibme::GetName(void)
{
	return "Remote Gibme";
}

const char* CRemoteGibme::GetAuthor(void)
{
	return "Steve (Noxturnix)";
}

const char* CRemoteGibme::GetVersion(void)
{
	return "1.0.0";
}

const char* CRemoteGibme::GetDescription(void)
{
	return "You gib when someone sends !remotegib or |remotegib in chat";
}

const char* CRemoteGibme::GetURL(void)
{
	return "https://github.com/Noxturnix/remote_gibme";
}

const char* CRemoteGibme::GetDate(void)
{
	return SVENMOD_BUILD_TIMESTAMP;
}

const char* CRemoteGibme::GetLogTag(void)
{
	return "REMOTE_GIBME";
}
