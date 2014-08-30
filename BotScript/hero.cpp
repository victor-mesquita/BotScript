#include "hero.h"

// .c totalmente atualizado -> 28/02/2014

ObjectAI HeroObjectAI;

DWORD HeroHandlerLoL;

int GetMyHero(lua_State *L)
{
	int tmp;

	if(HeroHandlerLoL == 0x00)
	 HeroHandlerLoL = GetModuleLoL();

	lua_newtable(L);

	for(int i = 0; i < 0x3000; i++)
	{
		if(GetObjectAI(i, &HeroObjectAI) == 3) // MyHero
		 break;
	}

	lua_pushnumber(L, (int)HeroObjectAI.HeroName);
	lua_setfield(L, -2, "HeroName");

	lua_pushnumber(L, (int)HeroObjectAI.InitObj);
	lua_setfield(L, -2, "InitObj");

	lua_pushnumber(L, (int)HeroObjectAI.PointObj);
	lua_setfield(L, -2, "PointObj");

	lua_pushnumber(L, (int)HeroObjectAI.hp);
	lua_setfield(L, -2, "hp");

	lua_pushnumber(L, (int)HeroObjectAI.max_hp);
	lua_setfield(L, -2, "max_hp");

	lua_pushnumber(L, (int)HeroObjectAI.mp);
	lua_setfield(L, -2, "mp");

	lua_pushnumber(L, (int)HeroObjectAI.max_mp);
	lua_setfield(L, -2, "max_mp");

	lua_pushnumber(L, (int)HeroObjectAI.level);
	lua_setfield(L, -2, "level");

	lua_pushnumber(L, (int)HeroObjectAI.Attack);
	lua_setfield(L, -2, "Attack");

	lua_pushnumber(L, (int)HeroObjectAI.Armor);
	lua_setfield(L, -2, "Armor");

	lua_pushnumber(L, (int)HeroObjectAI.ResisMagic);
	lua_setfield(L, -2, "ResisMagic");

	lua_pushnumber(L, (int)HeroObjectAI.VelMoviment);
	lua_setfield(L, -2, "VelMoviment");

	lua_pushnumber(L, (int)HeroObjectAI.VelAttack);
	lua_setfield(L, -2, "VelAttack");

	lua_pushnumber(L, (int)HeroObjectAI.team_ally);
	lua_setfield(L, -2, "my_team");

	lua_pushnumber(L, (int)HeroObjectAI.map_x);
	lua_setfield(L, -2, "map_x");

	lua_pushnumber(L, (int)HeroObjectAI.map_y);
	lua_setfield(L, -2, "map_y");

	lua_pushnumber(L, (int)HeroObjectAI.map_z);
	lua_setfield(L, -2, "map_z");

	lua_pushnumber(L, (int)HeroObjectAI.obj_id);
	lua_setfield(L, -2, "obj_id");

	__try
	{
		__asm
		{
			// Skill Status (1 CoolDown - 0 Active)
			mov eax,  HeroHandlerLoL
			add eax, 0x029BFA9C		// 28/02/2014	**********************************
			mov eax, dword ptr ds:[eax]

			add eax, 0x18
			mov eax, dword ptr ds:[eax]

			add eax, 0x10
			mov eax, dword ptr ds:[eax]

			add eax, 0x24
			mov eax, dword ptr ds:[eax]

			add eax, 0x320
			mov eax, dword ptr ds:[eax]

			add eax, 0x0

			add eax, 0x48  // Scan SpellCooldown0

			mov ebx, eax
			mov ebx, dword ptr ds:[ebx]
			mov HeroObjectAI.StatusSkill_Q, ebx

			add eax, 0x954
			mov ebx, eax
			mov ebx, dword ptr ds:[ebx]
			mov HeroObjectAI.StatusSkill_W, ebx

			add eax, 0x954
			mov ebx, eax
			mov ebx, dword ptr ds:[ebx]
			mov HeroObjectAI.StatusSkill_E, ebx

			add eax, 0x954
			mov ebx, eax
			mov ebx, dword ptr ds:[ebx]
			mov HeroObjectAI.StatusSkill_R, ebx
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
	}

	lua_pushnumber(L, HeroObjectAI.StatusSkill_Q);
	lua_setfield(L, -2, "StatusSkill_Q");

	lua_pushnumber(L, HeroObjectAI.StatusSkill_W);
	lua_setfield(L, -2, "StatusSkill_W");

	lua_pushnumber(L, HeroObjectAI.StatusSkill_E);
	lua_setfield(L, -2, "StatusSkill_E");

	lua_pushnumber(L, HeroObjectAI.StatusSkill_R);
	lua_setfield(L, -2, "StatusSkill_R");

	lua_pushnumber(L, HeroObjectAI.LevelSkill_Q);
	lua_setfield(L, -2, "LevelSkill_Q");

	lua_pushnumber(L, HeroObjectAI.LevelSkill_W);
	lua_setfield(L, -2, "LevelSkill_W");

	lua_pushnumber(L, HeroObjectAI.LevelSkill_E);
	lua_setfield(L, -2, "LevelSkill_E");

	lua_pushnumber(L, HeroObjectAI.LevelSkill_R);
	lua_setfield(L, -2, "LevelSkill_R");


	char *skinname;
	char SkinNameType[127];

	__try
	{
		__asm
		{
			// SkinName
			mov eax, HeroHandlerLoL
			add eax, 0x029BEDD0			// Att 28/02/2014	**********************************
			mov eax, dword ptr ds:[eax]

			add eax, 0xC
			mov eax, dword ptr ds:[eax]
			add eax, 0x54
			mov eax, dword ptr ds:[eax]
			add eax, 0x4
			mov eax, dword ptr ds:[eax]
			add eax, 0x3C
			mov eax, dword ptr ds:[eax]
			add eax, 0xa0
			//mov eax, dword ptr ds:[eax]
			mov skinname, eax
		}

		__asm
		{
			// Money
			mov eax, HeroHandlerLoL
			add eax, 0x029BFAA8			// Att 28/02/2014	**********************************
			mov eax, dword ptr ds:[eax]

			add eax, 0x14
			mov eax, dword ptr ds:[eax]
			add eax, 0x124
			mov eax, dword ptr ds:[eax]
			add eax, 0x3C
			mov eax, dword ptr ds:[eax]
			add eax, 0xb8
			mov eax, dword ptr ds:[eax]
			add eax, 0x0C
			mov eax, dword ptr ds:[eax]
			mov tmp, eax
		}

		strcpy_s(SkinNameType, skinname);
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
	}

	lua_pushnumber(L, tmp);
	lua_setfield(L, -2, "money");

	lua_pushstring(L, SkinNameType);
	lua_setfield(L, -2, "SkinName");

	return 1;
}