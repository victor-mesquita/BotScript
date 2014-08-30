#include "target.h"

// .c totalmente atualizado -> 27/02/2014

bool StatAutoCursorTarget = false;
DWORD TargetHandlerLoL;

//target ObjectTarget;

int target_global_offset = 0x029BEFAC;			// 27/02/2014	**********************************

int offset_targetselect = 0x10DD099;	// 27/02/2014	**********************************

/*
static int StructLuaCreateTarget(lua_State *L)
{
	lua_newtable(L); // Cria a tabela

	lua_pushstring(L, "x");
	lua_pushnumber(L, 0);

	lua_pushstring(L, "y");
	lua_pushnumber(L, 0);

	lua_pushstring(L, "z");
	lua_pushnumber(L, 0);

	lua_pushstring(L, "hp");
	lua_pushnumber(L, 0);

	lua_pushstring(L, "max_hp");
	lua_pushnumber(L, 0);

	lua_pushstring(L, "mp");
	lua_pushnumber(L, 0);

	lua_pushstring(L, "max_mp");
	lua_pushnumber(L, 0);

	lua_pushstring(L, "PowerAbility");
	lua_pushnumber(L, 0);

	lua_pushstring(L, "Armor");
	lua_pushnumber(L, 0);

	lua_pushstring(L, "AttackDamage");
	lua_pushnumber(L, 0);

	lua_pushstring(L, "AttackSpeed");
	lua_pushnumber(L, 0);

	lua_pushstring(L, "ResistMagic");
	lua_pushnumber(L, 0);

	lua_pushstring(L, "MovimentSpeed");
	lua_pushnumber(L, 0);

	lua_pushstring(L, "SelectTargetID");
	lua_pushnumber(L, 0);

	lua_settable(L, -3);

	return 1; // Retorna a Tabela
}

// Retorna os Status + ID do Target
static int GetTarget(lua_State *L)
{
	lua_newtable(L);

	if(TargetHandlerLoL != 0x00)
	 TargetHandlerLoL = GetModuleLoL();

	int tmp;

	// Select Target
	__asm
	{
	 mov eax, TargetHandlerLoL
	 add eax, offset_targetselect
	 mov eax, dword ptr ds:[eax]
	 mov tmp, eax
	}

	// Position
	if(tmp != 0x00)
	{
		__try
		{
		 __asm
		 {
		  mov edx, eax
		  
		  push edx
		  mov ebx, TargetHandlerLoL
		  add ebx, 0x063580			// 14/02/2014
		  call ebx

		  mov edx, esi
		  mov eax, dword ptr ds:[edx]
		  mov ObjectTarget.hp, eax
		  mov eax, dword ptr ds:[edx+0x04]
		  mov ObjectTarget.max_hp, eax
		  mov eax, dword ptr ds:[edx+0x08]
		  mov ObjectTarget.mp, eax
		  mov eax, dword ptr ds:[edx+0x0c]
		  mov ObjectTarget.max_mp, eax
		 }

		  if(ObjectTarget.hp >= 1)
		  {
		   __asm
		   {
		    mov eax, dword ptr ds:[edx+0x64]
		    mov ObjectTarget.x, eax
		    mov eax, dword ptr ds:[edx+0x68]
		    mov ObjectTarget.y, eax
		    mov eax, dword ptr ds:[edx+0x6C]
		    mov ObjectTarget.z, eax
		   }
		  }

		 lua_pushinteger(L, ObjectTarget.x);
		 lua_setfield(L, -2, "x");

		 lua_pushinteger(L, ObjectTarget.y);
		 lua_setfield(L, -2, "y");

		 lua_pushinteger(L, ObjectTarget.z);
		 lua_setfield(L, -2, "z");

		 lua_pushinteger(L, ObjectTarget.hp);
		 lua_setfield(L, -2, "hp");

		 lua_pushinteger(L, ObjectTarget.max_hp);
		 lua_setfield(L, -2, "max_hp");

		 lua_pushinteger(L, ObjectTarget.mp);
		 lua_setfield(L, -2, "mp");

		 lua_pushinteger(L, ObjectTarget.max_mp);
		 lua_setfield(L, -2, "max_mp");

		 lua_pushinteger(L, tmp);
		 lua_setfield(L, -2, "SelectTargetID");
		}
		__except(EXCEPTION_EXECUTE_HANDLER)
		{
			MessageBox(0, LPCSTR("GetTarget() failed - exception"), LPCSTR("Exception Error"), 0);
		}
	}

	return 1;
}

// Retorna os Status pelo ID do Target
static int GetTargetID(lua_State *L) // GetTargetID(id_target)
{
	int id_target = (int)luaL_checknumber(L, 1);

	lua_newtable(L);

	if(TargetHandlerLoL != 0x00)
	 TargetHandlerLoL = GetModuleLoL();

	int tmp;

	// Position
	if(tmp != 0x00)
	{
		__try
		{
		 __asm
		 {
		  mov edx, id_target
		  mov eax, dword ptr ds:[edx+0x64]
		  mov ObjectTarget.x, eax
		  mov eax, dword ptr ds:[edx+0x68]
		  mov ObjectTarget.y, eax
		  mov eax, dword ptr ds:[edx+0x6C]
		  mov ObjectTarget.z, eax
		 }

		 lua_pushinteger(L, ObjectTarget.x);
		 lua_setfield(L, -2, "x");

		 lua_pushinteger(L, ObjectTarget.y);
		 lua_setfield(L, -2, "y");

		 lua_pushinteger(L, ObjectTarget.z);
		 lua_setfield(L, -2, "z");
		}
		__except(EXCEPTION_EXECUTE_HANDLER)
		{
		 MessageBox(0, LPCSTR("GetTargetID(id_target) failed - exception"), LPCSTR("Exception Error"), 0);
		}
	 }

	return 1;
}
*/

// Seleciona Auto Select Target
int SetAutoCursorTarget(lua_State *L) // SetAutoCursorTarget(status)
{
	int status = (int)luaL_checknumber(L, 1);
	if(status == 1)
	 StatAutoCursorTarget = true;
	else
	 StatAutoCursorTarget = false;
	return 0;
}

/*
// Seleciona um target
static int SetSelectTarget(lua_State *L) // SetSelectTarget(id_target)
{
	int id_target = (int)luaL_checknumber(L, 1);

	__try
	{
		__asm
		{
		   // Select Target (GetTarget)
		   mov eax, TargetHandlerLoL
		   add eax, offset_targetselect;
		   mov ebx, id_target
		   mov dword ptr ds:[eax], ebx
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		MessageBox(0, LPCSTR("SetSelectTarget() failed - exception"), LPCSTR("Exception Error"), 0);
	}
}

// Captura o ID do Target Selecionado
static int GetSelectIDTarget(lua_State *L)
{
	int tmp;
	__try
	{
		__asm
		{
		   // Select Target (GetTarget)
		   mov eax, TargetHandlerLoL
		   add eax, offset_targetselect;
		   mov ebx, dword ptr ds:[eax]
		   mov tmp, ebx
		}

		if(tmp != 0x00)
		{
			ObjectTarget.SelectTargetID = tmp;
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
	 MessageBox(0, LPCSTR("GetSelectTarget() failed - exception"), LPCSTR("Exception Error"), 0);
	}

	lua_pushnumber(L, tmp);
	return 1;// Returno TMP for LUA ...
}
*/
void AutoCursorTarget()
{
	if(TargetHandlerLoL == 0x00)
	 TargetHandlerLoL = GetModuleLoL();

	int tmp;
	if(StatAutoCursorTarget)
	{
		__try
		{
		 __asm
		 {
			// Mouse Target
			mov eax, TargetHandlerLoL
			add eax, 0x29828A4			// 27/02/2014	**********************************
			mov ebx, dword ptr ds:[eax]
			mov tmp, ebx
		 }
		 if(tmp != 0x00)
		 {
		  __asm
		  {
		    // Select Target
			mov eax, TargetHandlerLoL
		    add eax, offset_targetselect;
			mov dword ptr ds:[eax], ebx
		  }
	     }
		}
		__except(EXCEPTION_EXECUTE_HANDLER)
		{
			MessageBox(0, LPCSTR("SetAutoCursorTarget(true) failed - exception"), LPCSTR("Exception Error"), 0);
		}
	}
}

int PlayerAttackTo(lua_State *L)
{
	move_player mp;
	move_player *pMp;

	pMp = (move_player*)&mp;

	// push 3 -> Atacar
	// push 2 -> Andar

	mp.move_x = (float)luaL_checknumber(L, 1);
	mp.move_y = (float)luaL_checknumber(L, 2);
	mp.move_z = (float)luaL_checknumber(L, 3);

	int object_minion = (int)luaL_checknumber(L, 4);

	if(TargetHandlerLoL == 0x00)
	 TargetHandlerLoL = GetModuleLoL();

	__try
	{
		__asm
		{
			mov ecx, TargetHandlerLoL
			add ecx, target_global_offset
			mov ecx, dword ptr ds:[ecx]

			mov esi, object_minion

			PUSH 1
			push 0
			push 0
			PUSH object_minion
			push pMp
			push 3	// -> Atacar
			mov ebx, TargetHandlerLoL
			add ebx, 0x295E40
			call ebx				// 27/02/2014	**********************************
		}

		lua_pushnumber(L, 1);
		return 1;
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
	}

	lua_pushnumber(L, 0);
	return 0;
}

int CastTargetSpell(lua_State *L)
{
	if(TargetHandlerLoL == 0x00)
	 TargetHandlerLoL = GetModuleLoL();

	int target = (int)luaL_checknumber(L, 1);
	int target_id = target + 0x64;

	__try
	{
		__asm
		{
		 // Spellbook::Client_CastTargettedSpell
		 mov ecx, TargetHandlerLoL
		 add ecx, target_global_offset
		 mov ecx, dword ptr ds:[ecx]
		 add ecx, 0x100C
		 mov ecx, dword ptr ds:[ecx]

		 mov edx, target
		 mov edx, dword ptr ds:[edx+0xF4]

		 push 1
		 push edx
		 push target_id
		 push target_id
		 mov eax, TargetHandlerLoL
		 add eax, 0x3B9020				// 27/02/2014	**********************************
		 call eax
	    }

	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
	}
}

int PlayerMoveTo(lua_State *L)
{
	move_player mp;
	move_player *pMp;

	pMp = (move_player*)&mp;

	// push 3 -> Atacar
	// push 2 -> Andar

	mp.move_x = (float)luaL_checknumber(L, 1);
	mp.move_y = (float)luaL_checknumber(L, 2);
	mp.move_z = (float)luaL_checknumber(L, 3);

	if(TargetHandlerLoL == 0x00)
	 TargetHandlerLoL = GetModuleLoL();

	__try
	{
		__asm
		{
			mov ecx, TargetHandlerLoL
			add ecx, target_global_offset
			mov ecx, dword ptr ds:[ecx]

			PUSH 1
			push 0
			push 0
			PUSH 0
			push pMp
			push 2 // -> Mover
			mov ebx, TargetHandlerLoL
			add ebx, 0x0295E40
			call ebx				// 27/02/2014	**********************************
		}

		lua_pushnumber(L, 1);
		return 1;
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
	}

	lua_pushnumber(L, 0);
	return 0;
}