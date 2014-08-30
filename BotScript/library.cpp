#include "library.h"

DWORD GetModuleLoL()
{
	return (DWORD)GetModuleHandle("League of Legends.exe");
}

int ColisionRadius(lua_State *L)
{
	int x1, y1, x2, y2, obj_raio;

	x1 = (int)lua_tonumber(L, 1);
	y1 = (int)lua_tonumber(L, 2);

	x2 = (int)lua_tonumber(L, 3);
	y2 = (int)lua_tonumber(L, 4);

	obj_raio = (int)lua_tonumber(L, 5);

	int x, y;

	x = ((x1-x2));
	x = x*x;

	y = ((y1-y2));
	y = y*y;

	int d = (int)sqrt((double)x+y);

	/*printf("(%d %d - %d %d) SQRT(%d + %d) = %d\n", x1, y1, x2, y2, x, y, d);*/

	if(d < obj_raio)
	{
	 lua_pushnumber(L, 1);
	 return 1;	// Está dentro do raio
	}
	else
	{
	 lua_pushnumber(L, 0);
	 return 1;	// Está fora do raio
	}
}