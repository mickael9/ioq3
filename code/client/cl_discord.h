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

#include "../../external/discord-rpc/include/discord-rpc.h"

#ifndef DISCORD_APPLICATION_ID
#define DISCORD_APPLICATION_ID "413053829500764180"
#endif

void CL_DiscordInit(void);
void CL_DiscordClearPresence(void);
void CL_DiscordRespond(const char *userid, int reply);
void CL_DiscordShutdown(void);
void CL_DiscordThink(void);
void CL_DiscordUpdateConnection(void);
void CL_DiscordUpdatePresence(const char *state, const char *details, int64_t startTimestamp, int64_t endTimestamp,
							  const char *largeImageKey, const char *largeImageText, const char *smallImageKey,
							  const char *smallImageText, const char *partyId, int partySize, int partyMax,
							  const char *matchSecret, const char *joinSecret, const char *spectateSecret,
							  int8_t instance);

// ----------------------------------------------------------------------------
// Discord Event Handlers
// ----------------------------------------------------------------------------

void CL_DiscordReady(void);
void CL_DiscordDisconnected(int errorCode, const char *message);
void CL_DiscordErrored(int errorCode, const char *message);
void CL_DiscordJoinGame(const char *joinSecret);
void CL_DiscordSpectateGame(const char *spectateSecret);
void CL_DiscordJoinRequest(const DiscordJoinRequest *request);

#endif