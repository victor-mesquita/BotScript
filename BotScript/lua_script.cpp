#include "lua_script.h"
#include "other.h"
#include "skill.h"
#include "draw_menu.h"

void LoadingFunction(lua_State *L)
{
	// Function

	lua_pushcfunction(L, CreateObjectAI);
	lua_setfield(L, -2, "CreateObjectAI");

	lua_pushcfunction(L, GetTurrentAI);
	lua_setfield(L, -2, "GetTurrentAI");

	lua_pushcfunction(L, GetMinionsAI);
	lua_setfield(L, -2, "GetMinionAI");

	lua_pushcfunction(L, GetHeroAI);
	lua_setfield(L, -2, "GetHeroAI");

	lua_pushcfunction(L, SellItem);
	lua_setfield(L, -2, "SellItem");

	lua_pushcfunction(L, BuyItem);
	lua_setfield(L, -2, "BuyItem");

	lua_pushcfunction(L, lua_print);
	lua_setfield(L, -2, "lua_print");

	lua_pushcfunction(L, DrawTextD3D);
	lua_setfield(L, -2, "DrawTextD3D");

	lua_pushcfunction(L, ColisionRadius);
	lua_setfield(L, -2, "ColisionRadius");

	lua_pushcfunction(L, LUA_COLOR);
	lua_setfield(L, -2, "LUA_COLOR");

	lua_pushcfunction(L, SetAutoCursorTarget);
	lua_setfield(L, -2, "SetAutoCursorTarget");

	lua_pushcfunction(L, GetMyHero);
	lua_setfield(L, -2, "GetMyHero");

	lua_pushcfunction(L, SetMaxZoom);
	lua_setfield(L, -2, "SetMaxZoom");

	lua_pushcfunction(L, SetMinZoom);
	lua_setfield(L, -2, "SetMinZoom");

	lua_pushcfunction(L, ColisionRadius);
	lua_setfield(L, -2, "ColisionRadius");

	lua_pushcfunction(L, DrawCircleGameD3D);
	lua_setfield(L, -2, "DrawGameCircleD3D");

	lua_pushcfunction(L, GetInventorySlot);
	lua_setfield(L, -2, "GetInventorySlot");

	lua_pushcfunction(L, GetItemQuantity);
	lua_setfield(L, -2, "GetItemQuantity");

	lua_pushcfunction(L, ShopStatus);
	lua_setfield(L, -2, "ShopStatus");

	lua_pushcfunction(L, UseItemSlot);
	lua_setfield(L, -2, "UseItemSlot");

	lua_pushcfunction(L, GetTimeTick);
	lua_setfield(L, -2, "GetTimeTick");

	lua_pushcfunction(L, PlayerMoveTo);
	lua_setfield(L, -2, "PlayerMoveTo");

	lua_pushcfunction(L, PlayerAttackTo);
	lua_setfield(L, -2, "PlayerAttackTo");

	lua_pushcfunction(L, GetKeyPress);
	lua_setfield(L, -2, "GetKeyPress");

	/*
	lua_pushcfunction(L, CreateMenu);
	lua_setfield(L, -2, "CreateMenu");

	lua_pushcfunction(L, CreateButton);
	lua_setfield(L, -2, "CreateButton");

	lua_pushcfunction(L, CreateText);
	lua_setfield(L, -2, "CreateText");

	lua_pushcfunction(L, CreateCheckBox);
	lua_setfield(L, -2, "CreateCheckBox");

	lua_pushcfunction(L, DrawMenu);
	lua_setfield(L, -2, "DrawMenu");
	*/

	lua_pushcfunction(L, LUA_ARGB);
	lua_setfield(L, -2, "LUA_ARGB");

	/*
	lua_pushcfunction(L, UseTargetSpell);
	lua_setfield(L, -2, "UseTargetSpell");
	*/

	lua_pushcfunction(L, CastTargetSpell);
	lua_setfield(L, -2, "CastTargetSpell");

	lua_pushcfunction(L, ActionSpell);
	lua_setfield(L, -2, "ActionSpell");

	// Global Variable

	lua_pushnumber(L, -1);
	lua_setfield(L, -2, "FAILED");

	lua_pushnumber(L, 3);
	lua_setfield(L, -2, "ATTACK");

	lua_pushnumber(L, 2);
	lua_setfield(L, -2, "MOVE");

	lua_pushnumber(L, 0);
	lua_setfield(L, -2, "_Q");

	lua_pushnumber(L, 1);
	lua_setfield(L, -2, "_W");

	lua_pushnumber(L, 2);
	lua_setfield(L, -2, "_E");

	lua_pushnumber(L, 3);
	lua_setfield(L, -2, "_R");

	lua_pushnumber(L, 4);
	lua_setfield(L, -2, "_D");

	lua_pushnumber(L, 5);
	lua_setfield(L, -2, "_F");

	lua_pushnumber(L, 6);
	lua_setfield(L, -2, "_B");

	lua_pushnumber(L, 0);
	lua_setfield(L, -2, "FINITE");
 
	lua_pushnumber(L, 1);
	lua_setfield(L, -2, "INFINITE");
}

void loadscript(lua_State *L, const char *filename)
{
	char err_msg[1024];
    /* load the lua script into memory */
    if(luaL_loadfile(L, filename))
	{
	 sprintf_s(err_msg, "[%s] Impossivel executar script [%s]", filename, lua_tostring(L, -1));
     MessageBox(0, err_msg, "Script Error", 0);
     exit(1);
	}

    /* create a new function environment and store it in the registry */
    lua_createtable(L, 0, 1);
    lua_getglobal(L, "print");
    lua_setfield(L, -2, "print");
    lua_pushvalue(L, -1);

	LoadingFunction(L);

    lua_setfield(L, LUA_REGISTRYINDEX, filename);

    /* set the environment for the loaded script and execute it */
    lua_setfenv(L, -2);
    
    lua_call(L, 0, 0);

    /* run the script initialization function */
    executescript(L, filename, "OnLoad");
}

void executescript(lua_State *L, const char *filename, const char *function)
{
    /* retrieve the environment from the resgistry */
    lua_getfield(L, LUA_REGISTRYINDEX, filename);

    /* get the desired function from the environment */
    lua_getfield(L, -1, function);

    return lua_call(L, 0, 0);
}

int lua_print(lua_State *L)
{
	const char *s = lua_tostring(L, 1);
	printf(s);
	return 0;
}