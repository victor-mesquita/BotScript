#ifndef __TARGET_H_
#define __TARGET_H_

#include "library.h"

/*
struct target
{
	int x;
	int y;
	int z;

	int hp;
	int max_hp;
	int mp;
	int max_mp;

	//unsigned char name_target[127];

	int PowerAbility;
	int Armor;
	int AttackDamage;
	int AttackSpeed;
	int ResistMagic;
	int MovimentSpeed;

	int SelectTargetID;
};*/

struct move_player
{
	float move_x;
	float move_z;
	float move_y;
	int a,b,c,d,e;
};

/*
static int StructLuaCreateTarget(lua_State *L);
static int GetTarget(lua_State *L);
static int GetTargetID(lua_State *L);
*/
int SetAutoCursorTarget(lua_State *L);
/*
static int SetSelectTarget(lua_State *L);
static int GetSelectIDTarget(lua_State *L);
*/
void AutoCursorTarget();
int PlayerMoveTo(lua_State *L);
int PlayerAttackTo(lua_State *L);
int CastTargetSpell(lua_State *L);

#endif