#include "draw_menu.h"

ID3DXFont* menu_dx_Font;

void CreateFontMenu()
{
	D3DXCreateFontA(GetDevice(), 16, 0, 4, 0, false, 1, 0, 0, 0, "Comic Sans", &menu_dx_Font);
}

int CreateMenu(lua_State *L)
{
	int w = (int)luaL_checknumber(L, 1);
	int h = (int)luaL_checknumber(L, 2);
	int color_alpha_transp = (int)luaL_checknumber(L, 3);

	MenuObject *menu_object = (MenuObject*)malloc(sizeof(MenuObject));

	for(int i = 0; i < MAX_OBJECT_MENU; i++)
	{
		menu_object->s_draw_checkbox[i].active_type = false;
		menu_object->s_draw_text[i].active_type = false;
		menu_object->s_draw_button[i].active_type = false;
	}

	menu_object->x = 127;
	menu_object->y = 0;
	menu_object->w = w;
	menu_object->h = h;
	menu_object->color = color_alpha_transp;
	menu_object->active_type = true;

	int address = (int)menu_object;
	//printf("menu_object: %x\n", menu_object);
	//printf("MENU CRIADO COM SUCESSO\n");

	lua_pushinteger(L, address);
	return 1;
}

int CreateButton(lua_State *L)
{
	int address = (int)luaL_checknumber(L, 1);
	MenuObject *menu_object;
	__asm
	{
		mov eax, address
		mov menu_object, eax
	}

	int x = (int)luaL_checknumber(L, 2);
	int y = (int)luaL_checknumber(L, 3);
	char *text = (char*)luaL_checkstring(L, 4);
	char *call_function = (char*)luaL_checkstring(L, 5);
	int color = (int)luaL_checknumber(L, 6);

	for(int i = 0; i < MAX_OBJECT_MENU; i++)
	{
		if(menu_object->s_draw_button[i].active_type == false)
		{
			strcpy_s(menu_object->s_draw_button[i].call_function, call_function);
			strcpy_s(menu_object->s_draw_button[i].text, text);
			menu_object->s_draw_button[i].x = x;
			menu_object->s_draw_button[i].y = y;
			menu_object->s_draw_button[i].w = 0;
			menu_object->s_draw_button[i].h = 20;
			menu_object->s_draw_button[i].text_color = color;
			menu_object->s_draw_button[i].press = false;
			menu_object->s_draw_button[i].active_type = true;
			//printf("BUTTON CRIADO COM SUCESSO - OnButton [%s]\n", call_function);
			//printf("menu_object: %x\n", menu_object);
			lua_pushnumber(L, i);
			return 1;
		}
	}

	lua_pushnumber(L, -1);
	return 1;
}

int CreateText(lua_State *L)
{
	int address = (int)luaL_checknumber(L, 1);
	MenuObject *menu_object;
	__asm
	{
		mov eax, address
		mov menu_object, eax
	}

	int x = (int)luaL_checknumber(L, 2);
	int y = (int)luaL_checknumber(L, 3);
	char *text = (char*)luaL_checkstring(L, 4);
	int color = (int)luaL_checknumber(L, 5);

	for(int i = 0; i < MAX_OBJECT_MENU; i++)
	{
		if(menu_object->s_draw_text[i].active_type == false)
		{
			strcpy_s(menu_object->s_draw_text[i].text, text);
			menu_object->s_draw_text[i].x = x;
			menu_object->s_draw_text[i].y = y;
			menu_object->s_draw_text[i].text_color = color;
			menu_object->s_draw_text[i].active_type = true;
			//printf("TEXT CRIADO COM SUCESSO\n");
			//printf("menu_object: %x\n", menu_object);
			lua_pushnumber(L, i);
			return 1;
		}
	}

	lua_pushnumber(L, -1);
	return 1;
}

int CreateCheckBox(lua_State *L)
{
	int address = (int)luaL_checknumber(L, 1);
	MenuObject *menu_object;
	__asm
	{
		mov eax, address
		mov menu_object, eax
	}

	int x = (int)luaL_checknumber(L, 2);
	int y = (int)luaL_checknumber(L, 3);
	char *text = (char*)luaL_checkstring(L, 4);
	char *call_function = (char*)luaL_checkstring(L, 5);
	int color = (int)luaL_checknumber(L, 6);

	for(int i = 0; i < MAX_OBJECT_MENU; i++)
	{
		if(menu_object->s_draw_text[i].active_type == false)
		{
			strcpy_s(menu_object->s_draw_checkbox[i].text, text);
			menu_object->s_draw_checkbox[i].x = x;
			menu_object->s_draw_checkbox[i].y = y;
			strcpy_s(menu_object->s_draw_checkbox[i].call_function, call_function);
			strcpy_s(menu_object->s_draw_checkbox[i].text, text);
			menu_object->s_draw_checkbox[i].text_color = color;
			menu_object->s_draw_checkbox[i].active_box = false;
			menu_object->s_draw_checkbox[i].active_type = true;
			//printf("CHECKBOX CRIADO COM SUCESSO - OnCheckBox [%s]\n", call_function);
			//printf("menu_object: %x\n", menu_object);
			lua_pushnumber(L, i);
			return 1;
		}
	}

	lua_pushnumber(L, -1);
	return 1;
}

int CloseMenu(lua_State *L)
{
	int address = (int)luaL_checknumber(L, 1);
	MenuObject *menu_object;
	__asm
	{
		mov eax, address
		mov menu_object, eax
	}

	menu_object->active_type = false;

	return 1;
}

int OpenMenu(lua_State *L)
{
	int address = (int)luaL_checknumber(L, 1);
	MenuObject *menu_object;
	__asm
	{
		mov eax, address
		mov menu_object, eax
	}

	menu_object->active_type = true;

	return 1;
}

int x, y;

int DrawMenu(lua_State *L)
{
	int address = (int)luaL_checknumber(L, 1);
	MenuObject *menu_object;
	__asm
	{
		mov eax, address
		mov menu_object, eax
	}

	x = (int)luaL_checknumber(L, 2);
	y = (int)luaL_checknumber(L, 3);

	menu_object->x = x;
	menu_object->y = y;

	FillR((float)menu_object->x, (float)menu_object->y, (float)menu_object->w, (float)menu_object->h, menu_object->color);

	int button_size;
	HDC hdc = GetDC(NULL);

	for(int i = 0; i < MAX_OBJECT_MENU; i++)
	{
		// DRAW TEXT
		if(menu_object->s_draw_text[i].active_type == true)
			FunctionDrawText(menu_object->s_draw_text[i].text, x+menu_object->s_draw_text[i].x, y+menu_object->s_draw_text[i].y, menu_object->s_draw_text[i].text_color);

		if(menu_object->s_draw_checkbox[i].active_type == true)
		{
		 FillR((float)x+menu_object->s_draw_checkbox[i].x-3, (float)y+menu_object->s_draw_checkbox[i].y-3, (float)18, (float)18, D3DCOLOR_ARGB(255, 255, 0, 0));
		 if(menu_object->s_draw_checkbox[i].active_box == true)
			 FillR((float)x+menu_object->s_draw_checkbox[i].x, (float)y+menu_object->s_draw_checkbox[i].y, (float)12, (float)12, D3DCOLOR_ARGB(255, 0, 255, 0));
		 else
			 FillR((float)x+menu_object->s_draw_checkbox[i].x, (float)y+menu_object->s_draw_checkbox[i].y, (float)12, (float)12, D3DCOLOR_ARGB(255, 0, 0, 0));

		 FunctionDrawText(menu_object->s_draw_checkbox[i].text, x+menu_object->s_draw_checkbox[i].x+19, y+menu_object->s_draw_checkbox[i].y-4, menu_object->s_draw_checkbox[i].text_color);
		}

		/*
		menu_object->s_draw_button[i].w = strlen(menu_object->s_draw_button[i].text);
		menu_object->s_draw_button[i].w *= 8;
		*/
		if(menu_object->s_draw_button[i].active_type == true)
		{
			SelectObject(hdc, menu_dx_Font);
			GetTextExtentPoint32A(hdc, menu_object->s_draw_button[i].text, strlen(menu_object->s_draw_button[i].text), (LPSIZE)&button_size);
			ReleaseDC(NULL, hdc);

			button_size += 9;

			FillR((float)x+menu_object->s_draw_button[i].x-3, (float)y+menu_object->s_draw_button[i].y-3, (float)button_size+6, (float)menu_object->s_draw_button[i].h+6, D3DCOLOR_ARGB(255, 255, 0, 0));

			if(menu_object->s_draw_button[i].press != true)
			 FillR((float)x+menu_object->s_draw_button[i].x, (float)y+menu_object->s_draw_button[i].y, (float)button_size, (float)menu_object->s_draw_button[i].h, D3DCOLOR_ARGB(255, 35, 35, 35));
			else
			 FillR((float)x+menu_object->s_draw_button[i].x, (float)y+menu_object->s_draw_button[i].y, (float)button_size, (float)menu_object->s_draw_button[i].h, D3DCOLOR_ARGB(255, 0, 0, 0));

			FunctionDrawText(menu_object->s_draw_button[i].text, x+menu_object->s_draw_button[i].x+5, y+menu_object->s_draw_button[i].y+2, menu_object->s_draw_button[i].text_color);
		}
	}

	return 1;
}

int MenuEvent(lua_State *L)
{
	return 1;
}

int LUA_ARGB(lua_State *L)
{
	int r = (int)luaL_checknumber(L, 1);
	int b = (int)luaL_checknumber(L, 2);
	int g = (int)luaL_checknumber(L, 3);
	int alpha = (int)luaL_checknumber(L, 4);

	int color = D3DCOLOR_ARGB(alpha, r, b, g);

	lua_pushnumber(L, color);
	return 1;
}

void FunctionDrawText(char *text, int x, int y, int color)
{
	RECT pos;
	pos.bottom = 0;
	pos.left = x;
	pos.right = 0;
	pos.top = y;

	menu_dx_Font->DrawTextA(NULL, text, strlen(text), &pos, DT_NOCLIP, color);
}
