/*
	##########################
	# XP-RP by Speed_Limit75 #
	# XP-RP.cpp              #
	##########################

	This is the main file for the XP-RP Plugin
	NOTE: Some parts of this file are based off of multiple sample codes on the X-Plane Developer Website
*/

// Headers
#include "XPLMDisplay.h" // XP SDK: Basic UI (modern window)
#include "XPLMGraphics.h" // XP SDK: More UI
#include "XPUIGraphics.h" // XP SDK: Even More UI
#include "XPLMMenus.h" // XP SDK: Menu Functionality
#include "XPLMDataAccess.h" // XP SDK: Datarefs
#include "XPLMPlugin.h" // XP SDK: Reload All Plugins
#include "settingsMan.h" // XP-RP: Read/Write Settings File
#include "discordRP.h" // XP-RP: Discord Management
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
#ifndef XPLM301
	#error This is made to be compiled against the XPLM301 SDK
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

	XPLMDrawString(col_white, l + 10, t - 20, "Settings (non-functional right now):", NULL, xplmFont_Proportional); // text warning of lack of functionality
	
	XPLMDrawString(col_white, l + 30, t - 45, "Display Speed Disagree", NULL, xplmFont_Proportional);
	XPDrawElement(l + 10, t - 47, l + 20, t - 37, xpElement_CheckBox, 0);
	
	XPLMDrawString(col_white, l + 30, t - 65, "Display Altitude Disagree", NULL, xplmFont_Proportional);
	XPDrawElement(l + 10, t - 67, l + 20, t - 57, xpElement_CheckBox, 0);
	
	XPLMDrawString(col_white, l + 30, t - 85, "Display Flight Number", NULL, xplmFont_Proportional);
	XPDrawElement(l + 10, t - 87, l + 20, t - 77, xpElement_CheckBox, 0);
	
	XPLMDrawString(col_white, l + 30, t - 105, "Open Window on Start", NULL, xplmFont_Proportional);
	XPDrawElement(l + 10, t - 107, l + 20, t - 97, xpElement_CheckBox, 0);

	XPLMDrawString(col_white, l + 20, b + 20, "Save & Exit", NULL, xplmFont_Proportional);
	XPDrawElement(l + 10, b + 10, r - 10, b + 30, xpElement_PushButton, 0);

	runCallback();
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
	XPLMSetWindowResizingLimits(t_window, 225, 150, 225, 150);
	XPLMSetWindowTitle(t_window, "XP-RichPresence Settings");

	return t_window != NULL;
}

// Function for menu buttons to work
void menu_handler(void* in_menu_ref, void* in_item_ref) {
	if (!strcmp((const char*)in_item_ref, "Menu Item 1")) {
		startdraw_main_window();
	}
	else if (!strcmp((const char*)in_item_ref, "Menu Item 2")) {
		startdraw_settings();
	}
	else if (!strcmp((const char*)in_item_ref, "Menu Item 3")) {
		XPLMReloadPlugins();
	}
	else if (!strcmp((const char*)in_item_ref, "Menu Item 4")) {
		XPLMDebugString(getAircraftIcon());
	}
}

// Plugin Startup
PLUGIN_API int XPluginStart(char* outName, char* outSig, char* outDesc) {
	// Details
	strcpy(outName, "XP-RichPresence");
	strcpy(outSig, "sl75.xp.richpresence");
	strcpy(outDesc, "Discord Rich Presence for X-Plane 11.");
	XPLMDebugString("XP-RP: Loading..\n");

	// Menu
	XPLMDebugString("      - Loading Menu.\n");
	g_menu_container_idx = XPLMAppendMenuItem(XPLMFindPluginsMenu(), "XP-RichPresence", 0, 0);
	g_menu_id = XPLMCreateMenu("XP-RichPresence", XPLMFindPluginsMenu(), g_menu_container_idx, menu_handler, NULL);
	XPLMAppendMenuItem(g_menu_id, "Re-Configure Flight", (void*)"Menu Item 1", 1);
	XPLMAppendMenuItem(g_menu_id, "Toggle Settings", (void*)"Menu Item 2", 1);
	XPLMAppendMenuSeparator(g_menu_id);
	XPLMAppendMenuItem(g_menu_id, "Reload Plugins", (void*)"Menu Item 3", 1);
	XPLMAppendMenuItem(g_menu_id, "Test Aircraft Icon Logic (outputs to Log.txt)", (void*)"Menu Item 4", 1);
	XPLMDebugString("      - Menu Loaded.\n");

	// Inital Window
	return startdraw_main_window();

	// Discord RP
	initRP();
	XPLMDebugString("XP-RP: Loaded\n");
}

// Plugin Stop
PLUGIN_API void	XPluginStop(void) {
	XPLMDebugString("XP-RP: Stopping...\n");
	XPLMDebugString("      - Destroying Windows");
	XPLMDestroyWindow(g_window); // Destroy Window
	g_window = NULL;
	XPLMDestroyMenu(g_menu_id); // Destroy Menu
	XPLMDebugString("XP-RP: Stopped.\n");
}

// Plugin Disable
PLUGIN_API void XPluginDisable(void) { XPLMDebugString("XP-RP: Plugin Disabled\n");  }

// Plugin Enable
PLUGIN_API int  XPluginEnable(void) { 
	XPLMDebugString("XP-RP: Plugin Enabled\n");
	return 1; 
}

// Recieve Message
PLUGIN_API void XPluginReceiveMessage(XPLMPluginID inFrom, int inMsg, void* inParam) { XPLMDebugString("XP-RP: Message Received: Not expecting any messages.\n");  }