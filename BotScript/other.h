#ifndef __OTHER_H_
#define __OTHER_H_

#include "library.h"
#include <time.h>

int SetMaxZoom(lua_State *L);
int SetMinZoom(lua_State *L);
int UseItemSlot(lua_State *L);
int GetTimeTick(lua_State *L);
int GetKeyPress(lua_State *L);

#endif