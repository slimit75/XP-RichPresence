/*
	##########################
	# XP-RP by Speed_Limit75 #
	# settingsMan.cpp/.h     #
	##########################

	This file manages reading and writing the settings.
*/

#include "settingsMan.h"
#include <fstream>
#include <iostream>
using namespace std;

// String to Bool
bool stringToBool(const char* text) {
	if ((strcmp(text, "false") == 0) && (strcmp(text, "False") == 0)) {
		return false;
	}
	else if ((strcmp(text, "true") == 0) && (strcmp(text, "True") == 0)) {
		return true;
	}
	else {
		return 0;
	}
}

// Read Settings
bool readSettings(const char* filePath, const char* wanted) {
	// Future: Read Settings
	char* text{};

	// String to Bool
	const bool displaySpeedDisagree = stringToBool("true");
	const bool displayAltDisagree = stringToBool("true");
	const bool displayFlightNumber = stringToBool("true");
	const bool openOnStart = stringToBool("true");

	// Return
	if (wanted == "displaySpeedDisagree") {
		return displaySpeedDisagree;
	} else if (wanted == "displayAltDisagree") {
		return displayAltDisagree;
	} else if (wanted == "displayFlightNumber") {
		return displayFlightNumber;
	} else if (wanted == "openOnStart") {
		return openOnStart;
	} else {
		return 0;
	}
}

// Write Settings
void writeSettings(char* filePath, const bool settings[4]) {
	// Recieve input from function
	const bool displaySpeedDisagree = settings[0];
	const bool displayAltDisagree = settings[1];
	const bool displayFlightNumber = settings[2];
	const bool openOnStart = settings[3];

	// Future: Write settings
	fstream settingsFile;
	settingsFile.open("test.txt"); // to be changed to path of settings file
	settingsFile << "displaySpeedDisagree=";
	settingsFile << displaySpeedDisagree;
	settingsFile << "\ndisplayAltDisagree=";
	settingsFile << displayAltDisagree;
	settingsFile << "\ndisplayFlightNumber=";
	settingsFile << displayFlightNumber;
	settingsFile << "\nopenOnStart=";
	settingsFile << openOnStart;
	settingsFile.close();
}