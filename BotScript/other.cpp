#include "other.h"

// .c totalmente atualizado -> 28/02/2014

int global_offset_other = 0x029BEFAC; // 28/02/2014	**********************************

DWORD OtherHandlerLoL;
DWORD lpflOldProtect;
unsigned char *pVirtualProtect;

int SetMaxZoom(lua_State *L) // SetMaxZoom(ValueZoom)
{
	if(OtherHandlerLoL == 0x00)
	 OtherHandlerLoL = GetModuleLoL();

	float zoom = (float)luaL_checknumber(L, 1);
	__try
	{
		pVirtualProtect = (unsigned char*)OtherHandlerLoL+0x0CD11FC;
		VirtualProtect(pVirtualProtect, 4, PAGE_EXECUTE_READWRITE, &lpflOldProtect);
		__asm
		{
			mov eax, OtherHandlerLoL
			add eax, 0x0CD11FC 			// 28/02/2014	**********************************
			mov ebx, zoom
			mov dword ptr ds:[eax], ebx
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		 MessageBox(0, LPCSTR("SetMaxZoom(ValueZoom) failed - exception"), LPCSTR("Exception Error"), 0);
	}

	return 0;
}

int SetMinZoom(lua_State *L) // SetMinZoom(ValueZoom) - Não atualizar
{
	if(OtherHandlerLoL == 0x00)
	 OtherHandlerLoL = GetModuleLoL();

	float zoom = (float)luaL_checknumber(L, 1);
	__try
	{
		__asm
		{
			mov eax, OtherHandlerLoL
			add eax, 0x0CACB0C				// ??/??/????
			mov ebx, zoom
			mov dword ptr ds:[eax], ebx
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		 MessageBox(0, LPCSTR("SetMinZoom(ValueZoom) failed - exception"), LPCSTR("Exception Error"), 0);
	}

	return 0;
}

int UseItemSlot(lua_State *L)
{
	if(OtherHandlerLoL == 0x00)
	 OtherHandlerLoL = GetModuleLoL();

	 unsigned int UseIdItem = (int)luaL_checknumber(L, 1);

	__try
	{
	 __asm
	 {
	  mov ecx, OtherHandlerLoL
	  add ecx, global_offset_other
	  mov ecx, dword ptr ds:[ecx]
	  mov esi, UseIdItem
	  push 1
	  PUSH ESI
	  LEA ECX,DWORD PTR DS:[ECX+0xFB0]
	  mov ebx, OtherHandlerLoL
	  add ebx, 0x002AD1D0				// 28/02/2014 ************************
	  call ebx
	 }

	 lua_pushnumber(L, 1);
	 return 1;
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
	}

	 lua_pushnumber(L, 0);
	 return 1;
}

int GetTimeTick(lua_State *L)
{
	int tmp;
	time_t rawtime;
	struct tm * timeinfo;

	time (&rawtime);
	timeinfo = localtime (&rawtime);

	tmp = timeinfo->tm_hour*3600+timeinfo->tm_min*60+timeinfo->tm_sec;

	lua_pushnumber(L, tmp);
	return 1;
}

int GetKeyPress(lua_State *L)
{
	unsigned int key_press = (int)luaL_checknumber(L, 1);
	if(GetAsyncKeyState(key_press) & 0x8000)
	 lua_pushnumber(L, 1);
	else
	 lua_pushnumber(L, 0);

	return 1;
}