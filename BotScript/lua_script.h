#ifndef __LUA_SCRIPT_H_
#define __LUA_SCRIPT_H_

#include "library.h"

#include "draw_object.h"
#include "target.h"
#include "hero.h"
#include "ai_object.h"
#include "shop.h"

void LoadingFunction(lua_State *L);
void loadscript(lua_State *L, const char *filename);
void executescript(lua_State *L, const char *filename, const char *function);
int lua_print(lua_State *L);

#endif