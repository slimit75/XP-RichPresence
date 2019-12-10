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
#include <string>
using namespace std;

// String to Bool
bool stringToBool(string stext) {
	const char* text = stext.c_str();

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
bool readSettings() {
	// Future: Read Settings
	string line;
	string output[4];
	ifstream settingsFile;
	int x = 0;
	settingsFile.open("test.txt"); // to be changed to path of settings file
	if (settingsFile.is_open()) {
		while (getline(settingsFile, line)) {
			output[x] = line;
			x = x + 1;
		}
		settingsFile.close();
	}
	settingsFile.close();

	// Split data from string
	output[0] = output[0].substr(output[0].find("="));
	output[1] = output[1].substr(output[1].find("="));
	output[2] = output[2].substr(output[2].find("="));
	output[3] = output[3].substr(output[3].find("="));

	// String to Bool
	const bool displaySpeedDisagree = stringToBool(output[0]);
	const bool displayAltDisagree = stringToBool(output[1]);
	const bool displayFlightNumber = stringToBool(output[2]);
	const bool openOnStart = stringToBool(output[3]);
	
	// Return
	const bool toReturn[4] = {displaySpeedDisagree, displayAltDisagree, displayFlightNumber, openOnStart};
	return toReturn;
}

// Write Settings
void writeSettings(bool settings[4]) {
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