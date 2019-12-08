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

discord::Core* core{};

void initRP() {
	auto result = discord::Core::Create(579668847846752266, DiscordCreateFlags_Default, &core);
	discord::Activity activity{};
	activity.SetState("Testing");
	activity.SetDetails("Testing, but another line");
	core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {});
	core->ActivityManager().RegisterSteam(1938123);
}

void runCallback() {
	::core->RunCallbacks();
}