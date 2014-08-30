#ifndef __AI_OBJECT_H_
#define __AI_OBJECT_H_

#include "library.h"

struct ObjectAI
{
	char ObjectType[127];
	char HeroName[127];

	int InitObj;
	int PointObj;

	float hp;
	float max_hp;
	float mp;
	float max_mp;

	int level;

	float Attack;
	float Armor;
	float PowerAbility;
	float ResisMagic;
	float VelMoviment;
	float VelAttack;

	int LevelSkill_Q;
	int StatusSkill_Q;

	int LevelSkill_W;
	int StatusSkill_W;

	int LevelSkill_E;
	int StatusSkill_E;

	int LevelSkill_R;
	int StatusSkill_R;

	int team_ally;

	float map_x;
	float map_y;
	float map_z;

	int count_obj;
	int obj_id;
};

DWORD GetObjectAI(unsigned int obj_id, ObjectAI *);

int CreateObjectAI(lua_State *);

int GetTurrentAI(lua_State *L);
int GetMinionsAI(lua_State *L);
int GetHeroAI(lua_State *L);

/*
int GetHeroName(lua_State *L);
*/

int ObjectTeste();

#endif