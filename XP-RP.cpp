/*
	XP-RP by Speed_Limit75
	This file is based off of multiple sample codes on the X-Plane Developer Website
*/

// Dependencies (almost all from X-Plane SDK)
#include "XPLMDisplay.h"
#include "XPLMGraphics.h"
#include "XPUIGraphics.h"
#include "XPLMMenus.h"
#include "XPLMDataAccess.h"
#include "XPLMPlugin.h"
#include "XPWidgets.h"
#include "XPStandardWidgets.h"
#include <fstream>
#include <string.h>
#include <string>

// OS-specific Dependencies (OpenGL?)
#if IBM
	#include <windows.h>
#endif

#if LIN
	#include <GL/gl.h>
#elif __GNUC__
	#include <OpenGL/gl.h>
#else
	#include <GL/gl.h>
#endif

// Error incase wrong X-Plane SDK version is used
#ifndef XPLM300
	#error This is made to be compiled against the XPLM300 SDK
#endif

// Begin Plugin-Specific Variables
char* version = "v0.9 Developer Beta 1";
// End Plugin-Specific Variables

static XPLMWindowID	g_window;
static XPLMWindowID t_window;
void draw_main_window(XPLMWindowID in_window_id, void* in_refcon);
int dummy_mouse_handler(XPLMWindowID in_window_id, int x, int y, int is_down, void* in_refcon) { return 0; }
XPLMCursorStatus dummy_cursor_status_handler(XPLMWindowID in_window_id, int x, int y, void* in_refcon) { return xplm_CursorDefault; }
int dummy_wheel_handler(XPLMWindowID in_window_id, int x, int y, int wheel, int clicks, void* in_refcon) { return 0; }
void dummy_key_handler(XPLMWindowID in_window_id, char key, XPLMKeyFlags flags, char virtual_key, void* in_refcon, int losing_focus) { }

int g_menu_container_idx;
XPLMMenuID g_menu_id;
void menu_handler(void*, void*);

// String to Bool
bool stringToBool(char* text) {
	if ((text == "false") && (text == "false")) {
		return false;
	} else if((text == "true") && (text == "True")) {
		return true;
	} else {
		return ERROR;
	}
}

// Manages Settings
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
	}
}

void writeSettings(char* filePath, bool settings[4]) {
	// Recieve input from function
	bool displaySpeedDisagree = settings[0];
	bool displayAltDisagree = settings[1];
	bool displayFlightNumber = settings[2];
	bool openOnStart = settings[3];

	// Future: Write settings
	std::fstream settingsFile;
	settingsFile.open("test.txt");
	settingsFile << "test";
	settingsFile.close();
}

// Gets Data
char* getData(char* type) {
	if (type == "Airspeed") {
		return "Program Me kts"; // Placeholder to remind me to make work during testing
	} else if (type == "Altitude") {
		return "Program Me ft"; // Placeholder to remind me to make work during testing
	} else {
		return "Invalid Type";
	}
}

// System to return correct aircraft icon
char* getAircraftIcon() {
	// Get Aircraft ICAO
	byte AircraftICAO[40];
	static XPLMDataRef AircraftICAO_df = XPLMFindDataRef("sim/aircraft/view/acf_ICAO");
	XPLMGetDatab(AircraftICAO_df, AircraftICAO, 0, 40);
	char* acfIcao= (char*)AircraftICAO;
	
	// Debug: Output ICAO to Log.txt
	XPLMDebugString("XP-RP: ");
	XPLMDebugString(acfIcao);

	// Aircraft Icon Logic
	if ((acfIcao == "E170") && (acfIcao == "E175") && (acfIcao == "E190") && (acfIcao == "E195")) {
		return "e-jets";
	} else if (acfIcao == "DR40") {
		return "dr40";
	} else if (acfIcao == "C172") {
		return "c172";
	} else if ((acfIcao == "B733") && (acfIcao == "B734") && (acfIcao == "B735") && (acfIcao == "B736") && (acfIcao == "B737") && (acfIcao == "B738") && (acfIcao == "B739")) {
		return "737ng";
	} else if ((acfIcao == "B741") && (acfIcao == "B742") && (acfIcao == "B743") && (acfIcao == "B744") && (acfIcao == "B748")) {
		return "747";
	} else if ((acfIcao == "A318") && (acfIcao == "A319") && (acfIcao == "A320") && (acfIcao == "A321")) {
		return "a320";
	} else if ((acfIcao == "B752") && (acfIcao == "B753")) {
		return "b757";
	} else if ((acfIcao == "MD82") && (acfIcao == "MD88") && (acfIcao == "b712")) {
		return "md88";
	} else if ((acfIcao == "D328") && (acfIcao == "J328")) {
		return "d328";
	} else if ((acfIcao == "B772") && (acfIcao && "B773") && (acfIcao == "B778") && (acfIcao == "B779") && (acfIcao == "B77L") && (acfIcao == "B77W")) {
		return "773";
	} else if ((acfIcao == "B762") && (acfIcao == "B763") && (acfIcao == "B764")) {
		return "773";
	} else if ((acfIcao == "B788") && (acfIcao == "B789") && (acfIcao == "B78X")) {
		return "787";
	} else if ((acfIcao == "A332") && (acfIcao == "A333") && (acfIcao == "A337") && (acfIcao == "A338") && (acfIcao == "A339")) {
		return "a330";
	} else if ((acfIcao == "A342") && (acfIcao == "A343") && (acfIcao == "A345") && (acfIcao == "A346")) {
		return "a340";
	} else if (acfIcao == "A388") {
		return "a380";
	} else if ((acfIcao == "A359") && (acfIcao == "A35K")) {
		return "a350";
	} else {
		return "xp";
	}
}

// Draw Main Window
void draw_main_window(XPLMWindowID in_window_id, void* in_refcon) {
	// OpenGL State, kind of required
	XPLMSetGraphicsState(0, /* no fog */ 0, /* 0 texture units */ 0, /* no lighting */ 0, /* no alpha testing */ 1, /* do alpha blend */ 1, /* do depth testing */ 0 /* no depth writing */);

	int l, t, r, b;
	XPLMGetWindowGeometry(in_window_id, &l, &t, &r, &b);
	float col_white[] = { 1.0, 1.0, 1.0 };

	XPLMDrawString(col_white, l + 10, t - 20, "This version of the plugin does nothing so far. You can close this window.", NULL, xplmFont_Proportional); // text warning of lack of functionality
}

// Draw Settings Window
void draw_settings(XPLMWindowID in_window_id, void* in_refcon) {
	// OpenGL State, kind of required
	XPLMSetGraphicsState(0, /* no fog */ 0, /* 0 texture units */ 0, /* no lighting */ 0, /* no alpha testing */ 1, /* do alpha blend */ 1, /* do depth testing */ 0 /* no depth writing */);

	int l, t, r, b;
	XPLMGetWindowGeometry(in_window_id, &l, &t, &r, &b);
	float col_white[] = { 1.0, 1.0, 1.0 };

	XPLMDrawString(col_white, l + 10, t - 20, "Settings (non-functional right now)", NULL, xplmFont_Proportional); // text warning of lack of functionality
	//XPDrawElement(1, 1, 1, 1, xpElement_CheckBox, 0);
	XPCreateWidget(l + 30, l + 40, t - 40, t - 50, 0, "Display Speed Disagree", 1, 0, xpRadioButton);
	XPLMDrawString(col_white, l + 50, t - 45, "Display Speed Disagree", NULL, xplmFont_Proportional);
	XPCreateWidget(l + 30, l + 40, t - 60, t - 70, 0, "Display Altitude Disagree", 1, 0, xpRadioButton);
	XPLMDrawString(col_white, l + 50, t - 65, "Display Altitude Disagree", NULL, xplmFont_Proportional);
	XPCreateWidget(l + 30, l + 40, t - 80, t - 90, 0, "Display Flight Number", 1, 0, xpRadioButton);
	XPLMDrawString(col_white, l + 50, t - 85, "Display Flight Number", NULL, xplmFont_Proportional);
	XPCreateWidget(l + 30, l + 40, t - 100, t - 110, 0, "Open Window on Start", 1, 0, xpRadioButton);
	XPLMDrawString(col_white, l + 50, t - 105, "Open Window on Start", NULL, xplmFont_Proportional);
}

// Creation of Main Wndow
int startdraw_main_window() {
	XPLMCreateWindow_t params;
	params.structSize = sizeof(params);
	params.visible = 1;
	params.drawWindowFunc = draw_main_window;
	params.handleMouseClickFunc = dummy_mouse_handler;
	params.handleRightClickFunc = dummy_mouse_handler;
	params.handleMouseWheelFunc = dummy_wheel_handler;
	params.handleKeyFunc = dummy_key_handler;
	params.handleCursorFunc = dummy_cursor_status_handler;
	params.refcon = NULL;
	params.layer = xplm_WindowLayerFloatingWindows;
	params.decorateAsFloatingWindow = xplm_WindowDecorationRoundRectangle;
	int left, bottom, right, top;
	XPLMGetScreenBoundsGlobal(&left, &top, &right, &bottom);
	params.left = left + 50;
	params.bottom = bottom + 150;
	params.right = params.left + 200;
	params.top = params.bottom + 200;

	g_window = XPLMCreateWindowEx(&params);

	XPLMSetWindowPositioningMode(g_window, xplm_WindowPositionFree, -1);
	// Min Width/Height Max Width/Height
	XPLMSetWindowResizingLimits(g_window, 450, 75, 450, 75);
	XPLMSetWindowTitle(g_window, "XP-RichPresence");

	return g_window != NULL;
}

// Creation of Settings Window
int startdraw_settings() {
	XPLMCreateWindow_t params;
	params.structSize = sizeof(params);
	params.visible = 1;
	params.drawWindowFunc = draw_settings;
	params.handleMouseClickFunc = dummy_mouse_handler;
	params.handleRightClickFunc = dummy_mouse_handler;
	params.handleMouseWheelFunc = dummy_wheel_handler;
	params.handleKeyFunc = dummy_key_handler;
	params.handleCursorFunc = dummy_cursor_status_handler;
	params.refcon = NULL;
	params.layer = xplm_WindowLayerFloatingWindows;
	params.decorateAsFloatingWindow = xplm_WindowDecorationRoundRectangle;
	int left, bottom, right, top;
	XPLMGetScreenBoundsGlobal(&left, &top, &right, &bottom);
	params.left = left + 50;
	params.bottom = bottom + 150;
	params.right = params.left + 200;
	params.top = params.bottom + 200;

	t_window = XPLMCreateWindowEx(&params);

	XPLMSetWindowPositioningMode(t_window, xplm_WindowPositionFree, -1);
	// Min Width/Height Max Width/Height
	XPLMSetWindowResizingLimits(t_window, 450, 75, 450, 75);
	XPLMSetWindowTitle(t_window, "XP-RichPresence Settings");

	return t_window != NULL;
}

// Plugin Startup
PLUGIN_API int XPluginStart(char* outName, char* outSig, char* outDesc) {
	// Details
	strcpy(outName, "XP-RichPresence");
	strcpy(outSig, "sl75.xp.richpresence");
	strcpy(outDesc, "Discord Rich Presence for X-Plane 11.");
	XPLMDebugString("XP-RP: Loading..");

	// Menu
	XPLMDebugString("      - Loading Menu.");
	g_menu_container_idx = XPLMAppendMenuItem(XPLMFindPluginsMenu(), "XP-RichPresence", 0, 0);
	g_menu_id = XPLMCreateMenu("XP-RichPresence", XPLMFindPluginsMenu(), g_menu_container_idx, menu_handler, NULL);
	XPLMAppendMenuItem(g_menu_id, "Re-Configure Flight", (void*)"Menu Item 1", 1);
	XPLMAppendMenuItem(g_menu_id, "Toggle Settings", (void*)"Menu Item 2", 1);
	XPLMAppendMenuSeparator(g_menu_id);
	XPLMAppendMenuItem(g_menu_id, "Reload Plugins", (void*)"Menu Item 3", 1);
	XPLMAppendMenuItem(g_menu_id, "Test Aircraft Icon Logic (outputs to Log.txt)", (void*)"Menu Item 4", 1);
	XPLMDebugString("      - Menu Loaded.");

	// Inital Window
	return startdraw_main_window();
	XPLMDebugString("XP-RP: Loaded");
}

// Plugin Stop
PLUGIN_API void	XPluginStop(void) {
	XPLMDebugString("XP-RP: Stopping...");
	XPLMDebugString("      - Destroying Windows");
	XPLMDestroyWindow(g_window); // Destroy Window
	g_window = NULL;
	XPLMDestroyMenu(g_menu_id); // Destroy Menu
	XPLMDebugString("XP-RP: Stopped.");
}

// Plugin Disable
PLUGIN_API void XPluginDisable(void) {
	XPLMDebugString("XP-RP: Plugin Disabled");
}

// Plugin Enable
PLUGIN_API int  XPluginEnable(void) { 
	XPLMDebugString("XP-RP: Plugin Enabled");
	return 1; 
}

// Recieve Message
PLUGIN_API void XPluginReceiveMessage(XPLMPluginID inFrom, int inMsg, void* inParam) { 
	XPLMDebugString("XP-RP: Message Received: Not expecting any messages.");
}

// Function for menu buttons to work
void menu_handler(void* in_menu_ref, void* in_item_ref) {
	if (!strcmp((const char*)in_item_ref, "Menu Item 1")) {
		startdraw_main_window();
	} else if (!strcmp((const char*)in_item_ref, "Menu Item 2")) {
		startdraw_settings();
	} else if (!strcmp((const char*)in_item_ref, "Menu Item 3")) {
		XPLMReloadPlugins();
	} else if (!strcmp((const char*)in_item_ref, "Menu Item 4")) {
		XPLMDebugString(getAircraftIcon());
	}
}