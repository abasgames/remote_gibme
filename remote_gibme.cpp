#include "remote_gibme.h"
#include <hl_sdk/common/protocol.h>

#include <messagebuffer.h>

CMessageBuffer CvarValueBuffer;
 
sizebuf_t *clc_buffer; // picked at plugin initialization
 
DECLARE_FUNC(void, __cdecl, HOOKED_CL_Send_CvarValue2) 
{
    // Init
    CNetMessageParams *params = Utils()->GetNetMessageParams();
    CvarValueBuffer.Init( params->buffer, params->readcount, params->badread );
 
    // Main body
    CMessageBuffer ClientToServerBuffer;
    ClientToServerBuffer.Init( clc_buffer );
 
    int iRequestID = CvarValueBuffer.ReadLong();
    const char *pszCvarName = CvarValueBuffer.ReadString();
 
    if ( strlen(pszCvarName) >= 0xFF ) // too long cvar name
    {
        // Client-to-server message type
        ClientToServerBuffer.WriteByte( CLC_REQUESTCVARVALUE2 );
        ClientToServerBuffer.WriteLong( iRequestID );
        ClientToServerBuffer.WriteString( pszCvarName );
 
        ClientToServerBuffer.WriteString( "Bad CVAR request" );
    }
    else
    {
        cvar_t *pCvar = CVar()->FindCvar( pszCvarName );
 
        ClientToServerBuffer.WriteByte( CLC_REQUESTCVARVALUE2 );
        ClientToServerBuffer.WriteLong( iRequestID );
        ClientToServerBuffer.WriteString( pszCvarName );
 
        if ( pCvar != NULL )
        {
            ClientToServerBuffer.WriteString( pCvar->string ); // write cvar's value
        }
        else // no such cvar
        {
            ClientToServerBuffer.WriteString( "Bad CVAR request" );
        }
    }
 
    // Apply reading to the network messages buffer
    Utils()->ApplyNetMessageReading( CvarValueBuffer ); // not implemented in current version of svenmod yet
 
    ORIG_CL_Send_CvarValue2();
}

const char* CRemoteGibme::GetAuthor(void)
{
	return "not really";
}

const char* CRemoteGibme::GetVersion(void)
{
	return "1.0.0";
}

const char* CRemoteGibme::GetDescription(void)
{
	return "lol";
}

const char* CRemoteGibme::GetURL(void)
{
	return "https://github.com/abasgames/remote_gibme";
}

const char* CRemoteGibme::GetDate(void)
{
	return SVENMOD_BUILD_TIMESTAMP;
}

const char* CRemoteGibme::GetLogTag(void)
{
	return "REMOTE_GIBME";
}
