/*
===========================================================================
Copyright (C) 2018 Daniele Pantaleone <danielepantaleone@me.com>

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

 1. The origin of this software must not be misrepresented; you must not
    claim that you wrote the original software. If you use this software
    in a product, an acknowledgment in the product documentation would be
    appreciated but is not required.

 2. Altered source versions must be plainly marked as such, and must not be
    misrepresented as being the original software.

 3. This notice may not be removed or altered from any source distribution.
===========================================================================
*/

#ifdef USE_DISCORD

#include "client.h"
#include "cl_discord.h"

void CL_DiscordInit(void) {
	Com_Printf("CL_DiscordInit\n");
	DiscordEventHandlers handlers;
	memset(&handlers, 0, sizeof(handlers));
	handlers.ready = CL_DiscordReady;
	handlers.errored = CL_DiscordErrored;
	handlers.disconnected = CL_DiscordDisconnected;
	handlers.joinGame = CL_DiscordJoinGame;
	handlers.spectateGame = CL_DiscordSpectateGame;
	handlers.joinRequest = CL_DiscordJoinRequest;
	Discord_Initialize(DISCORD_APPLICATION_ID, &handlers, 1, NULL);
}

void CL_DiscordClearPresence(void) {
	Com_DPrintf("CL_DiscordClearPresence\n");
	Discord_ClearPresence();
}

void CL_DiscordUpdatePresence(const char *state, const char *details, int64_t startTimestamp, int64_t endTimestamp,
							  const char *largeImageKey, const char *largeImageText, const char *smallImageKey,
							  const char *smallImageText, const char *partyId, int partySize, int partyMax,
							  const char *matchSecret, const char *joinSecret, const char *spectateSecret,
							  int8_t instance) {
	Com_DPrintf("CL_DiscordUpdatePresence\n");
	DiscordRichPresence presence;
	memset(&presence, 0, sizeof(presence));
	presence.state = state;
	presence.details = details;
	presence.startTimestamp = startTimestamp;
	presence.endTimestamp = endTimestamp;
	presence.largeImageKey = largeImageKey;
	presence.largeImageText = largeImageText;
	presence.smallImageKey = smallImageKey;
	presence.smallImageText = smallImageText;
	presence.partyId = partyId;
	presence.partySize = partySize;
	presence.partyMax = partyMax;
	presence.matchSecret = matchSecret;
	presence.joinSecret = joinSecret;
	presence.spectateSecret = spectateSecret;
	presence.instance = instance;
	Discord_UpdatePresence(&presence);
}

void CL_DiscordRespond(const char *userid, int reply) {
	Com_DPrintf("CL_DiscordRespond: %s (%d)\n", userid, reply);
	Discord_Respond(userid, reply);
}

void CL_DiscordShutdown(void) {
	Com_DPrintf("CL_DiscordShutdown\n");
	Discord_Shutdown();
}

void CL_DiscordThink(void) {
	Com_DPrintf("CL_DiscordThink\n");
	Discord_RunCallbacks();
}

void CL_DiscordUpdateConnection(void) {
#ifdef DISCORD_DISABLE_IO_THREAD
	Com_DPrintf("CL_DiscordUpdateConnection\n");
	Discord_UpdateConnection();
#endif
}

// ----------------------------------------------------------------------------
// Discord Event Handlers
// ----------------------------------------------------------------------------

void CL_DiscordReady(void) {
	Com_DPrintf("CL_DiscordReady\n");
	VM_Call(cgvm, CG_DISCORD_READY);
}

void CL_DiscordDisconnected(int errorCode, const char *message) {
	Com_DPrintf("CL_DiscordDisconnected %s (%d)\n", message, errorCode);
	VM_Call(cgvm, CG_DISCORD_DISCONNECTED, errorCode, message);
}

void CL_DiscordErrored(int errorCode, const char *message) {
	Com_DPrintf("CL_DiscordErrored: %s (%d)\n", message, errorCode);
	VM_Call(cgvm, CG_DISCORD_ERRORED, errorCode, message);
}

void CL_DiscordJoinGame(const char *joinSecret) {
	Com_DPrintf("CL_DiscordJoinGame: %s\n", joinSecret);
	VM_Call(cgvm, CG_DISCORD_JOIN_GAME, joinSecret);
}

void CL_DiscordSpectateGame(const char *spectateSecret) {
	Com_DPrintf("CL_DiscordSpectateGame: %s\n", spectateSecret);
	VM_Call(cgvm, CG_DISCORD_SPECTATE_GAME, spectateSecret);
}

void CL_DiscordJoinRequest(const DiscordJoinRequest *request) {
	Com_DPrintf("CL_DiscordJoinRequest: %s (%s)\n", request->username, request->userId);
	VM_Call(cgvm, CG_DISCORD_JOIN_REQUEST, request->userId, request->username, request->discriminator, request->avatar);
}

#endif