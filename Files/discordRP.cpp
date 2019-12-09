/*
	##########################
	# XP-RP by Speed_Limit75 #
	# discordRP.cpp/.h       #
	##########################

	This file manages the Discord Rich Presence.
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
discord::Core* core{};

void initRP() {
	auto result = discord::Core::Create(579668847846752266, DiscordCreateFlags_NoRequireDiscord, &core);
	state.core.reset(core);
	if (!state.core) {
		XPLMDebugString("Failed to instantiate discord core! (err");
		XPLMDebugString(static_cast<int>(result));
		XPLMDebugString(")\n");
		std::exit(-1);
	}

	discord::Activity activity{};
	activity.SetState("Testing");
	activity.SetDetails("Testing, but another line");
	activity.GetAssets().SetLargeImage("xp");
	activity.SetType(discord::ActivityType::Playing);
	state.core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {});
	state.core->ActivityManager().RegisterSteam(1938123);
}

void runCallback() {
	::core->RunCallbacks();
}