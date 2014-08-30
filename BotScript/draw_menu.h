#ifndef __DRAW_MENU_H_
#define __DRAW_MENU_H_

#include "library.h"
#include "draw_object.h"

#define MAX_OBJECT_MENU 255

struct StructDrawText
{
	char text[127];
	int x;
	int y;
	int text_color;
	bool active_type;
};

struct StructDrawCheckBox
{
	char text[127];
	int text_color;
	int x;
	int y;
	bool active_type;
	char call_function[127];
	bool active_box;
};

struct StructDrawButton
{
 char text[127];
 int text_color;
 int x;
 int y;
 int w;
 int h;
 bool active_type;
 char call_function[127];
 bool press;
};

struct MenuObject
{
	int x;
	int y;
	int w;
	int h;
	int color;
	bool active_type;
	int alpha;
	StructDrawText s_draw_text[MAX_OBJECT_MENU];
	StructDrawCheckBox s_draw_checkbox[MAX_OBJECT_MENU];
	StructDrawButton s_draw_button[MAX_OBJECT_MENU];

	int number_category;
};

void CreateFontMenu();
int CreateMenu(lua_State *L);
int CreateButton(lua_State *L);
int CreateText(lua_State *L);
int CreateCheckBox(lua_State *L);
int CloseMenu(lua_State *L);
int OpenMenu(lua_State *L);

int DrawMenu(lua_State *L);
int MenuEvent(lua_State *L);

int LUA_ARGB(lua_State *L);
void FunctionDrawText(char *text, int x, int y, int color);

#endif