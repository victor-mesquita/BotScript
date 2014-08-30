#include "ai_object.h"

// .c totalmente atualizado -> 27/02/2014

/*
ObjectAI ObjectAITurrent;
ObjectAI ObjectAIMinion;
ObjectAI ObjectAIHero;
*/

DWORD ObjectHandlerLoL;

DWORD GetObjectAI(unsigned int obj_id, ObjectAI *_ObjectAI)
{
	ObjectAI LocalObjectAI;

	int tmp;
	float float_tmp;
	char *object_type;
	char *name_hero;
	char *object;

	if(ObjectHandlerLoL == 0x00)
	 ObjectHandlerLoL = GetModuleLoL();

	__try
	{
	 __asm
	 {
	 	mov ecx, ObjectHandlerLoL
 		MOV ECX, dword ptr ds:[ecx+0x0297BEB8] // 27/02/2014 **********************************
		MOV EDX, obj_id
		MOV ECX,DWORD PTR DS:[ECX+EDX*4]
		mov obj_id, ecx
	 }

	 if(obj_id != 0x00)
	 {
		__asm
		{
			mov edx, obj_id
			mov LocalObjectAI.InitObj, edx

			mov eax, edx
			add eax, 0x28
			mov name_hero, eax

			add eax, 0x04
			mov object, eax

			mov eax, edx
			add eax, 0x64
			mov eax, dword ptr ds:[eax]
			mov LocalObjectAI.map_x, eax // x

			mov eax, edx
			add eax, 0x68
			mov eax, dword ptr ds:[eax]
			mov LocalObjectAI.map_z, eax // z

			mov eax, edx
			add eax, 0x6C
			mov eax, dword ptr ds:[eax]
			mov LocalObjectAI.map_y, eax // y

			mov eax, edx
			add eax, 0x1C
			mov eax, dword ptr ds:[eax]
			mov LocalObjectAI.team_ally, eax

			add edx, 4
			mov edx, dword ptr ds:[edx]
			//mov edx, dword ptr ds:[edx]
			mov LocalObjectAI.PointObj, edx
			add edx, 4
			mov object_type, edx // Object Name
		}

		if(!strcmp(object_type, "obj_AI_Turret") || !strcmp(object_type, "obj_AI_Minion") || !strcmp(object_type, "obj_AI_Hero"))
		{
		 __asm
		 {
			mov eax, LocalObjectAI.InitObj

			mov ebx, dword ptr ds:[eax+0x118] // HP
			mov LocalObjectAI.hp, ebx

			mov ebx, dword ptr ds:[eax+0x128] // MAX HP
			mov LocalObjectAI.max_hp, ebx

			mov ebx, dword ptr ds:[eax+0x184] // MP
			mov LocalObjectAI.mp, ebx

			mov ebx, dword ptr ds:[eax+0x194] // MAX MP
			mov LocalObjectAI.max_mp, ebx

			mov ebx, dword ptr ds:[eax+0x688] // Add Ataque
			mov float_tmp, ebx

			mov ebx, dword ptr ds:[eax+0x6F0] // Ataque
			mov LocalObjectAI.Attack, ebx
		 }

		 LocalObjectAI.Attack += float_tmp;

		 __asm
		 {
			mov ebx, dword ptr ds:[eax+0x70C] // Armadura
			mov LocalObjectAI.Armor, ebx

			mov ebx, dword ptr ds:[eax+0x710] // Resistencia Mágica
			mov LocalObjectAI.ResisMagic, ebx

			mov ebx, dword ptr ds:[eax+0x720] // Velocidade de Movimento  
			mov LocalObjectAI.VelMoviment, ebx

			mov ebx, dword ptr ds:[eax+0x6EC] // Velocidade de Ataque
			mov LocalObjectAI.VelAttack, ebx

			//mov ebx, dword ptr ds:[eax+0x4744] // Level
			mov ebx, dword ptr ds:[eax+0x474C] // Level
			mov LocalObjectAI.level, ebx

			mov ebx, dword ptr ds:[eax+0x9E8] // Poder de Habilidade
			mov LocalObjectAI.PowerAbility, ebx

			mov ebx, dword ptr ds:[eax+0x1550] // Level Skill 0
			mov LocalObjectAI.LevelSkill_Q, ebx

			mov ebx, dword ptr ds:[eax+0x1550+0xA0] // Level Skill 1
			mov LocalObjectAI.LevelSkill_W, ebx

			mov ebx, dword ptr ds:[eax+0x1550+0x140] // Level Skill 2
			mov LocalObjectAI.LevelSkill_E, ebx

			mov ebx, dword ptr ds:[eax+0x1550+0x1E0] // Level Skill 3
			mov LocalObjectAI.LevelSkill_R, ebx
		 }

		_ObjectAI->LevelSkill_Q = LocalObjectAI.LevelSkill_Q;
		_ObjectAI->LevelSkill_W = LocalObjectAI.LevelSkill_W;
		_ObjectAI->LevelSkill_E = LocalObjectAI.LevelSkill_E;
		_ObjectAI->LevelSkill_R = LocalObjectAI.LevelSkill_R;

		_ObjectAI->hp = LocalObjectAI.hp;
		_ObjectAI->max_hp = LocalObjectAI.max_hp;

		_ObjectAI->mp = LocalObjectAI.mp;
		_ObjectAI->max_mp = LocalObjectAI.max_mp;

		_ObjectAI->Attack = LocalObjectAI.Attack;
		_ObjectAI->Armor = LocalObjectAI.Armor;
		_ObjectAI->ResisMagic = LocalObjectAI.ResisMagic;
		_ObjectAI->VelMoviment = LocalObjectAI.VelMoviment;
		_ObjectAI->VelAttack = LocalObjectAI.VelAttack;

		_ObjectAI->PowerAbility = LocalObjectAI.PowerAbility;

		_ObjectAI->PointObj = LocalObjectAI.PointObj;
		_ObjectAI->InitObj = LocalObjectAI.InitObj;


		_ObjectAI->map_x = LocalObjectAI.map_x;
		_ObjectAI->map_y = LocalObjectAI.map_y;
		_ObjectAI->map_z = LocalObjectAI.map_z;

		_ObjectAI->team_ally = LocalObjectAI.team_ally;

		_ObjectAI->level = LocalObjectAI.level;

		/*
		if(LocalObjectAI.team_ally == 0x64)
		 _ObjectAI->team_ally = 1; // RED
		else
	     _ObjectAI->team_ally = 0; // BLUE
		 */
	   }

		if(!strcmp(object_type, "obj_AI_Turret"))
			return 1; // Object Turrent
		else if(!strcmp(object_type, "obj_AI_Minion"))
			return 2; // Object Minion
		else if(!strcmp(object_type, "obj_AI_Hero"))
		{
			__asm
			{
				mov eax, LocalObjectAI.InitObj
				add eax, 0x28
				add eax, 0x03
				xor ebx, ebx
				mov bl, byte ptr ds:[eax]
				mov tmp, ebx
			}
			if(strcmp(object, "Object") && tmp != 0x00)
			 strcpy_s(_ObjectAI->HeroName, name_hero);
			else
			{
				__asm
				{
					mov eax, LocalObjectAI.InitObj
					add eax, 0x28
					mov eax, dword ptr ds:[eax]
					mov name_hero, eax
				}

				strcpy_s(_ObjectAI->HeroName, name_hero);
			}
			return 3; // Object Minion
		}
		else
			return 0xFF; // Other
	 }
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		return 0;
	}

	return obj_id;
}

int CreateObjectAI(lua_State *L)
{
	lua_newtable(L);

	lua_pushstring(L, "NULL");
	lua_setfield(L, -2, "ObjectType");

	lua_pushnumber(L, 0);
	lua_setfield(L, -2, "HeroName");

	lua_pushnumber(L, 0);
	lua_setfield(L, -2, "InitObj");

	lua_pushnumber(L, 0);
	lua_setfield(L, -2, "PointObj");

	lua_pushnumber(L, 0);
	lua_setfield(L, -2, "hp");

	lua_pushnumber(L, 0);
	lua_setfield(L, -2, "mp");

	lua_pushnumber(L, 0);
	lua_setfield(L, -2, "max_hp");

	lua_pushnumber(L, 0);
	lua_setfield(L, -2, "max_mp");

	lua_pushnumber(L, 0);
	lua_setfield(L, -2, "Attack");

	lua_pushnumber(L, 0);
	lua_setfield(L, -2, "Armor");

	lua_pushnumber(L, 0);
	lua_setfield(L, -2, "ResisMagic");

	lua_pushnumber(L, 0);
	lua_setfield(L, -2, "VelMoviment;");

	lua_pushnumber(L, 0);
	lua_setfield(L, -2, "VelAttack;");

	lua_pushnumber(L, 0);
	lua_setfield(L, -2, "team_ally");

	lua_pushnumber(L, 0);
	lua_setfield(L, -2, "map_x");

	lua_pushnumber(L, 0);
	lua_setfield(L, -2, "map_y");

	lua_pushnumber(L, 0);
	lua_setfield(L, -2, "map_z");

	lua_pushnumber(L, 0);
	lua_setfield(L, -2, "count_obj");

	lua_pushnumber(L, 0);
	lua_setfield(L, -2, "obj_id");

	lua_pushstring(L, "NULL");
	lua_setfield(L, -2, "HeroName");

	lua_pushnumber(L, 1);
	lua_setfield(L, -2, "level");

	lua_pushnumber(L, 1);
	lua_setfield(L, -2, "type");

	return 1;
}

int GetTurrentAI(lua_State *L)
{
	ObjectAI LocalObjectAI;
	LocalObjectAI.obj_id = 0x00;

	int found = 0;

	int count_object = (int)luaL_checknumber(L, 1);

	if(count_object >= 0x3000)
	 count_object = 0x0;

	lua_newtable(L);

	for(int i = count_object; i < 0x3000; i++)
	{
	 if(GetObjectAI(i, &LocalObjectAI) == 1)
	 {
	  count_object = i;
	  found = 1;
	  break;
	 }
	}

	if(found)
	{
	 lua_pushnumber(L, 1);
	 lua_setfield(L, -2, "type");
	}
	else
	{
	 lua_pushnumber(L, 0);
	 lua_setfield(L, -2, "type");
	 count_object = 0;
	}

	LocalObjectAI.obj_id = count_object;

	lua_pushinteger(L, LocalObjectAI.InitObj);
	lua_setfield(L, -2, "InitObj");

	lua_pushinteger(L, LocalObjectAI.PointObj);
	lua_setfield(L, -2, "PointObj");

	lua_pushnumber(L, LocalObjectAI.map_x);
	lua_setfield(L, -2, "map_x");

	lua_pushnumber(L, LocalObjectAI.map_y);
	lua_setfield(L, -2, "map_y");

	lua_pushnumber(L, LocalObjectAI.map_z);
	lua_setfield(L, -2, "map_z");

	lua_pushnumber(L, LocalObjectAI.hp);
	lua_setfield(L, -2, "hp");

	lua_pushnumber(L, LocalObjectAI.max_hp);
	lua_setfield(L, -2, "max_hp");

	if(count_object >= 0x2999)
	 count_object = 0x00;
	else
	 count_object++;

	lua_pushnumber(L, count_object);
	lua_setfield(L, -2, "count_obj");

	lua_pushnumber(L, LocalObjectAI.Attack);
	lua_setfield(L, -2, "Attack");

	lua_pushnumber(L, LocalObjectAI.Armor);
	lua_setfield(L, -2, "Armor");

	lua_pushnumber(L, LocalObjectAI.ResisMagic);
	lua_setfield(L, -2, "ResisMagic");

	lua_pushnumber(L, LocalObjectAI.VelMoviment);
	lua_setfield(L, -2, "VelMoviment");

	lua_pushnumber(L, LocalObjectAI.VelAttack);
	lua_setfield(L, -2, "VelAttack");

	/*
	lua_pushnumber(L, LocalObjectAI.PowerAbility);
	lua_setfield(L, -2, "PowerAbility");
	*/

	lua_pushnumber(L, LocalObjectAI.team_ally);
	lua_setfield(L, -2, "team_ally");

	return 1;
}

int GetMinionsAI(lua_State *L)
{
	ObjectAI LocalObjectAI;
	LocalObjectAI.obj_id = 0x00;

	int found = 0;

	int count_object = (int)luaL_checknumber(L, 1);

	if(count_object >= 0x3000)
	 count_object = 0x0;

	lua_newtable(L);

	for(int i = count_object; i < 0x3000; i++)
	{
	 if(GetObjectAI(i, &LocalObjectAI) == 2)
	 {
	  count_object = i;
	  found = 1;
	  break;
	 }
	}

	if(found)
	{
	 lua_pushnumber(L, 1);
	 lua_setfield(L, -2, "type");
	}
	else
	{
	 lua_pushnumber(L, 0);
	 lua_setfield(L, -2, "type");
	 count_object = 0;
	}

	LocalObjectAI.obj_id = count_object;

	lua_pushinteger(L, LocalObjectAI.InitObj);
	lua_setfield(L, -2, "InitObj");

	lua_pushinteger(L, LocalObjectAI.PointObj);
	lua_setfield(L, -2, "PointObj");

	lua_pushnumber(L, LocalObjectAI.map_x);
	lua_setfield(L, -2, "map_x");

	lua_pushnumber(L, LocalObjectAI.map_y);
	lua_setfield(L, -2, "map_y");

	lua_pushnumber(L, LocalObjectAI.map_z);
	lua_setfield(L, -2, "map_z");

	lua_pushnumber(L, LocalObjectAI.hp);
	lua_setfield(L, -2, "hp");

	lua_pushnumber(L, LocalObjectAI.max_hp);
	lua_setfield(L, -2, "max_hp");

	if(count_object >= 0x2999)
	 count_object = 0x00;
	else
	 count_object++;

	lua_pushnumber(L, count_object);
	lua_setfield(L, -2, "count_obj");

	lua_pushnumber(L, LocalObjectAI.Attack);
	lua_setfield(L, -2, "Attack");

	lua_pushnumber(L, LocalObjectAI.Armor);
	lua_setfield(L, -2, "Armor");

	lua_pushnumber(L, LocalObjectAI.ResisMagic);
	lua_setfield(L, -2, "ResisMagic");

	lua_pushnumber(L, LocalObjectAI.VelMoviment);
	lua_setfield(L, -2, "VelMoviment");

	lua_pushnumber(L, LocalObjectAI.VelAttack);
	lua_setfield(L, -2, "VelAttack");

	lua_pushnumber(L, LocalObjectAI.team_ally);
	lua_setfield(L, -2, "team_ally");

  return 1;
}

int GetHeroAI(lua_State *L)
{
	ObjectAI LocalObjectAI;
	LocalObjectAI.obj_id = 0x00;

	int found = 0;

	int count_object = (int)luaL_checknumber(L, 1);

	if(count_object >= 0x3000)
	 count_object = 0x0;

	lua_newtable(L);

	for(int i = count_object; i < 0x3000; i++)
	{
	 if(GetObjectAI(i, &LocalObjectAI) == 3)
	 {
	  count_object = i;
	  found = 1;
	  break;
	 }
	}

	if(found)
	{
	 lua_pushnumber(L, 1);
	 lua_setfield(L, -2, "type");
	}
	else
	{
	 lua_pushnumber(L, 0);
	 lua_setfield(L, -2, "type");
	 count_object = 0;
	}

	LocalObjectAI.obj_id = count_object;

	lua_pushnumber(L, LocalObjectAI.InitObj);
	lua_setfield(L, -2, "InitObj");

	lua_pushstring(L, LocalObjectAI.HeroName);
	lua_setfield(L, -2, "HeroName");

	lua_pushinteger(L, LocalObjectAI.PointObj);
	lua_setfield(L, -2, "PointObj");

	lua_pushnumber(L, (int)LocalObjectAI.map_x);
	lua_setfield(L, -2, "map_x");

	lua_pushnumber(L, (int)LocalObjectAI.map_y);
	lua_setfield(L, -2, "map_y");

	lua_pushnumber(L, (int)LocalObjectAI.map_z);
	lua_setfield(L, -2, "map_z");

	lua_pushnumber(L, (int)LocalObjectAI.hp);
	lua_setfield(L, -2, "hp");

	lua_pushnumber(L, (int)LocalObjectAI.max_hp);
	lua_setfield(L, -2, "max_hp");

	lua_pushnumber(L, (int)LocalObjectAI.mp);
	lua_setfield(L, -2, "mp");

	lua_pushnumber(L, (int)LocalObjectAI.max_mp);
	lua_setfield(L, -2, "max_mp");

	if(count_object >= 0x2999)
	 count_object = 0x00;
	else
	 count_object++;

	lua_pushnumber(L, count_object);
	lua_setfield(L, -2, "count_obj");

	lua_pushnumber(L, (int)LocalObjectAI.Attack);
	lua_setfield(L, -2, "Attack");

	lua_pushnumber(L, (int)LocalObjectAI.Armor);
	lua_setfield(L, -2, "Armor");

	lua_pushnumber(L, (int)LocalObjectAI.ResisMagic);
	lua_setfield(L, -2, "ResisMagic");

	lua_pushnumber(L, (int)LocalObjectAI.VelMoviment);
	lua_setfield(L, -2, "VelMoviment");

	lua_pushnumber(L, (int)LocalObjectAI.VelAttack);
	lua_setfield(L, -2, "VelAttack");

	lua_pushnumber(L, LocalObjectAI.PowerAbility);
	lua_setfield(L, -2, "PowerAbility");

	lua_pushnumber(L, (int)LocalObjectAI.team_ally);
	lua_setfield(L, -2, "team_ally");

	lua_pushnumber(L, (int)LocalObjectAI.level);
	lua_setfield(L, -2, "level");

	return 1;
}

/*
int GetHeroName(lua_State *L)
{
}
*/

int ObjectTeste()
{
	int turrent = 0;
	int hero = 0;
	int minions = 0;
	ObjectAI TestObjectAI;
	for(int i = 0; i < 0x3000; i++)
	{
		if(GetObjectAI(i, &TestObjectAI) == 1)
		 /*printf("obj_AI_Turret [%d]\n", i);*/ turrent++;
		if(GetObjectAI(i, &TestObjectAI) == 2)
		 /*printf("obj_AI_Turret [%d]\n", i);*/ minions++;

		if(GetObjectAI(i, &TestObjectAI) == 3)
		{
		 /*printf("obj_AI_Turret [%d]\n", i);*/ hero++;
		 /*
		 printf_s("HP [%f/%f] MP [%f/%f] [%f] [%f] [%f] [%f] [%f]\n", TestObjectAI.hp, TestObjectAI.max_hp, TestObjectAI.mp, TestObjectAI.Attack, TestObjectAI.max_mp, TestObjectAI.Armor, TestObjectAI.ResisMagic, TestObjectAI.VelMoviment, TestObjectAI.VelAttack);*/
		 printf("NAME [%s] [%f][%f][%f]\n", TestObjectAI.HeroName, TestObjectAI.map_x, TestObjectAI.map_y, TestObjectAI.map_z);
		}
	}

	/*
	if(turrent > 1)
		printf("obj_AI_Turret Found [%d]\n", turrent);
	if(minions > 1)
		printf("obj_AI_Minion Found [%d]\n", minions);
	if(hero > 1)
		printf("obj_AI_Hero Found [%d]\n", hero);
	*/

	return 0;
}
