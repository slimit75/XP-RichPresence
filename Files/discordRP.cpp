/*
	##########################
	# XP-RP by Speed_Limit75 #
	# discordRP.cpp/.h       #
	##########################

	This file manages the Discord Rich Presence.

	TODO: Fix entire file
*/

#include "discordRP.h"
#include "discord.h"
#include "XPLMUtilities.h"
#include <array>

struct DiscordState {
	discord::User currentUser;
	std::unique_ptr<discord::Core> core;
};

namespace {
	volatile bool interrupted{ false };
}

DiscordState state{};
discord::Core* core{}; // LNK2001/2019?
char* str;

void initRP() {
	const auto result = discord::Core::Create(579668847846752266, DiscordCreateFlags_NoRequireDiscord, &core); // LNK 2001/2019
	state.core.reset(core);
	if (!state.core) {
		XPLMDebugString("Failed to instantiate discord core! (err");

		sprintf(str, "%d", static_cast<int>(result));
		XPLMDebugString(str);
		
		XPLMDebugString(")\n");
		std::exit(-1);
	}

	discord::Activity activity{};
	activity.SetState("Testing"); // LNK2001/2019
	activity.SetDetails("Testing, but another line");  // LNK2001/2019
	activity.GetAssets().SetLargeImage("xp"); // LNK2001/2019
	activity.SetType(discord::ActivityType::Playing); // LNK2001/2019
	state.core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {}); // LNK2001/2019
	state.core->ActivityManager().RegisterSteam(1938123); // LNK2001/2019
}

void runCallback() {
	::core->RunCallbacks(); // LNK2001/2019
}