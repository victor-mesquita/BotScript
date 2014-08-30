#ifndef __SKILL_H_
#define __SKILL_H_

#include "library.h"
#include "draw_object.h"

int ActionSpell(lua_State *L);

int UseTargetSpell(lua_State *L);
void HookMoveSkill();

void InitHooked();

#endif