/*
	##########################
	# XP-RP by Speed_Limit75 #
	# discordRP.cpp/.h       #
	##########################

	This file manages the Discord Rich Presence.
*/
#include <cstring> 
#include <iostream> 
#include "discord_rpc.h"
#include "XPLMUtilities.h"
#include <string>
#include <string.h>
using namespace std;

static void handleDiscordReady(const DiscordUser* connectedUser) {
    XPLMDebugString("XP-RP [DISCORD]: Discord Read. User: ");
    XPLMDebugString(connectedUser->username);
    XPLMDebugString("\n");
}

static void handleDiscordError(int errcode, const char* message) {
    XPLMDebugString("XP-RP [DISCORD]: Error\n   - Error Code:");
    char* result;
    sprintf(result, "%d", errcode);
    XPLMDebugString(result);
    XPLMDebugString("\n    - Error Text:");
    XPLMDebugString(message);
    XPLMDebugString("/n");
}

static void handleDiscordDisconnected(int errcode, const char* message) {
    XPLMDebugString("XP-RP: Loaded\n");
}

static void handleDiscordJoin(const char* secret) {return;}
static void handleDiscordSpectate(const char* secret) {return;}
static void handleDiscordJoinRequest(const DiscordUser* request) {return;}

static void initRP() {
    DiscordEventHandlers handlers;
    memset(&handlers, 0, sizeof(handlers));
    handlers.ready = handleDiscordReady;
    handlers.errored = handleDiscordError;
    handlers.disconnected = handleDiscordDisconnected;
    handlers.joinGame = handleDiscordJoin;
    handlers.spectateGame = handleDiscordSpectate;
    handlers.joinRequest = handleDiscordJoinRequest;

    // Discord_Initialize(const char* applicationId, DiscordEventHandlers* handlers, int autoRegister, const char* optionalSteamId)
    Discord_Initialize("579668847846752266", &handlers, 0, "269950");
    return;
}

void menuRP() {}
void updateRP() {}
void stopRP() {}