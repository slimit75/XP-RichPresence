#pragma once

#include <iostream>

bool stringToBool(char* text);
bool readSettings(char* filePath, char* wanted);
void writeSettings(char* filePath, bool settings[4]);