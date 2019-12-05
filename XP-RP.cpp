// XP-RP by Speed_Limit75
// This document is based off of the "Hello World!" tutorial on the X-Plane Developer Website

#include "XPLMDisplay.h"
#include "XPLMGraphics.h"
#include "XPLMMenus.h"
#include <string.h>
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

#ifndef XPLM300
#error This is made to be compiled against the XPLM300 SDK
#endif

static XPLMWindowID	g_window;
void				draw_hello_world(XPLMWindowID in_window_id, void* in_refcon);
int					dummy_mouse_handler(XPLMWindowID in_window_id, int x, int y, int is_down, void* in_refcon) { return 0; }
XPLMCursorStatus	dummy_cursor_status_handler(XPLMWindowID in_window_id, int x, int y, void* in_refcon) { return xplm_CursorDefault; }
int					dummy_wheel_handler(XPLMWindowID in_window_id, int x, int y, int wheel, int clicks, void* in_refcon) { return 0; }
void				dummy_key_handler(XPLMWindowID in_window_id, char key, XPLMKeyFlags flags, char virtual_key, void* in_refcon, int losing_focus) { }

int g_menu_container_idx;
XPLMMenuID g_menu_id;
void menu_handler(void*, void*);

PLUGIN_API int XPluginStart(
	char* outName,
	char* outSig,
	char* outDesc)
{
	strcpy(outName, "XP-RichPresence");
	strcpy(outSig, "sl75.xp.richpresence");
	strcpy(outDesc, "Discord Rich Presence for X-Plane 11.");

	// Menu
	g_menu_container_idx = XPLMAppendMenuItem(XPLMFindPluginsMenu(), "XP-RichPresence", 0, 0);
	g_menu_id = XPLMCreateMenu("XP-RichPresence", XPLMFindPluginsMenu(), g_menu_container_idx, menu_handler, NULL);
	XPLMAppendMenuItem(g_menu_id, "Re-Configure Flight", (void*)"Menu Item 1", 1);
	XPLMAppendMenuSeparator(g_menu_id);
	XPLMAppendMenuItem(g_menu_id, "Toggle Settings", (void*)"Menu Item 2", 1);
	
	// Inital Window
	XPLMCreateWindow_t params;
	params.structSize = sizeof(params);
	params.visible = 1;
	params.drawWindowFunc = draw_hello_world;
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

PLUGIN_API void	XPluginStop(void)
{
	XPLMDestroyWindow(g_window);
	g_window = NULL;

	XPLMDestroyMenu(g_menu_id);
}

PLUGIN_API void XPluginDisable(void) { }
PLUGIN_API int  XPluginEnable(void) { return 1; }
PLUGIN_API void XPluginReceiveMessage(XPLMPluginID inFrom, int inMsg, void* inParam) { }

void	draw_hello_world(XPLMWindowID in_window_id, void* in_refcon)
{
	// Required: OpenGL State
	XPLMSetGraphicsState(
		0 /* no fog */,
		0 /* 0 texture units */,
		0 /* no lighting */,
		0 /* no alpha testing */,
		1 /* do alpha blend */,
		1 /* do depth testing */,
		0 /* no depth writing */
	);

	int l, t, r, b;
	XPLMGetWindowGeometry(in_window_id, &l, &t, &r, &b);

	float col_white[] = { 1.0, 1.0, 1.0 };

	XPLMDrawString(col_white, l + 10, t - 20, "This version of the plugin does nothing so far. You can close this window.", NULL, xplmFont_Proportional); // text warning of lack of functionality
}

void menu_handler(void* in_menu_ref, void* in_item_ref)
{
	if (!strcmp((const char*)in_item_ref, "Menu Item 1"))
	{
		return; // draw_hello_world(XPLMWindowID in_window_id, void* in_refcon); MAY WORK, comment initally read: XPLMCommandOnce(XPLMFindCommand("sim/operation/toggle_settings_window"));
	}
	else if (!strcmp((const char*)in_item_ref, "Menu Item 2"))
	{
		return; //XPLMCommandOnce(XPLMFindCommand("sim/operation/toggle_key_shortcuts_window"));
	}
}