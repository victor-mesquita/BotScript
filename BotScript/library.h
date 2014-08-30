#ifndef __LIBRARY_H_
#define __LIBRARY_H_

/*
Code by Firefox (Lucas Campos)
Using Visual C++ 2010 for Compilation the code
Install SDK DirectX9
Install Lua 5.1 for Visual C++ 2010
*/

#include <Windows.h>
#include <psapi.h>
#include <d3d9.h>
#include <d3dx9.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <lua.hpp>
#include <conio.h>

/*
#include <lua.h>
#include <lualib.h>
#include <luaconf.h>
#include <lauxlib.h>

extern "C" {
 #include "lua.h"
 #include "lualib.h"
 #include "lauxlib.h"
}
*/

#include "detours.h"
#include "shop.h"

#pragma comment(lib, "psapi.lib")
#pragma comment (lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "lua5.1.lib")
#pragma comment(lib, "detours.lib")

typedef int (__stdcall* EndScene)(LPDIRECT3DDEVICE9 Device);

DWORD GetModuleLoL();
/*bool ColisionRaio(int x1, int y1, int x2, int y2, int obj_raio);*/
int ColisionRadius(lua_State *L);

#endif