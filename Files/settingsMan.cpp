#include "settingsMan.h"
#include <fstream>
#include <iostream>
using namespace std;

// String to Bool
bool stringToBool(char* text) {
	if ((text == "false") && (text == "False")) {
		return false;
	}
	else if ((text == "true") && (text == "True")) {
		return true;
	}
	else {
		return 0;
	}
}

// Read Settings
bool readSettings(char* filePath, char* wanted) {
	// Future: Read Settings
	char* text;

	// String to Bool
	bool displaySpeedDisagree = stringToBool("true");
	bool displayAltDisagree = stringToBool("true");
	bool displayFlightNumber = stringToBool("true");
	bool openOnStart = stringToBool("true");

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
void writeSettings(char* filePath, bool settings[4]) {
	// Recieve input from function
	bool displaySpeedDisagree = settings[0];
	bool displayAltDisagree = settings[1];
	bool displayFlightNumber = settings[2];
	bool openOnStart = settings[3];

	// Future: Write settings
	fstream settingsFile;
	settingsFile.open("test.txt");
	settingsFile << "test";
	settingsFile.close();
}