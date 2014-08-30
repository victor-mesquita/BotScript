#include "skill.h"

// .c totalmente atualizado -> 28/02/2014

int spell_global_offset = 0x029BEFAC;			// 27/02/2014	**********************************

DWORD HandlerSkillLoL;
RECT rect;

bool SkillActive = false;
int count_skill = 0;

float map_spell_x = 118;
float map_spell_y = 395;
float map_spell_z = 1334;

unsigned char opcode_hook[] = {0xE8, 0x00, 0x00, 0x00, 0x00};
unsigned char nop_opcode[] = {0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90};

int ActionSpell(lua_State *L)
{
	int push1, push2;
	if(HandlerSkillLoL == NULL)
	 HandlerSkillLoL = GetModuleLoL();

	HWND hwnd_foreground = GetForegroundWindow();
	HWND hwnd_compared = FindWindow(NULL, "League of Legends (TM) Client");

	int spell_type = (int)luaL_checknumber(L, 1);

	float x = (float)luaL_checknumber(L, 2);
	float y = (float)luaL_checknumber(L, 3);
	float z = (float)luaL_checknumber(L, 4);

	map_spell_x = x;
	map_spell_y = y;
	map_spell_z = z;

	if(spell_type == 0) // Q
	{
		push1 = 0;
		push2 = 0;
	}

	if(spell_type == 1) // W
	{
		push1 = 0;
		push2 = 1;
	}

	if(spell_type == 2) // E
	{
		push1 = 0;
		push2 = 2;
	}

	if(spell_type == 3) // R
	{
		push1 = 0;
		push2 = 3;
	}

	if(spell_type == 4) // D
	{
		push1 = 1;
		push2 = 0;
	}

	if(spell_type == 5) // F
	{
		push1 = 1;
		push2 = 1;
	}

	if(spell_type == 6) // B
	{
		push1 = 0x0B;
		push2 = 1;
	}

	__asm
	{
		pushad
	}

	if(hwnd_compared == hwnd_foreground)
	{
	 __try
	 {
	  __asm
	  {
 	   MOV ESI, HandlerSkillLoL
	   add esi, spell_global_offset
	   mov esi, dword ptr ds:[esi]
	   LEA EDI,DWORD PTR DS:[ESI+0x1408]
	   MOV ECX, EDI

	   push push1
	   push push2

	   // 00CADCB6   68 E0236E01      PUSH League_o.016E23E0                   ; ASCII "Spellbook::SetSelectedSpellSlot"
	   mov eax, HandlerSkillLoL
	   add eax, 0x03B8CA0			// *********************** Atualizado 27/02/2014
	   call eax
	  }

	  mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	  mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

	  //HWND w = FindWindow(NULL, "League of Legends (TM) Client");

	  //SendMessage(w, WM_RBUTTONDOWN, 0, 0);
 	  //SendMessage(w, WM_RBUTTONUP, 0, 0);

	  // Adicionar X Y Z ao map_skill_x ...
	  // Dar SetSkill ... na função SetSelectedSpellSlot
	  // Adiconar SkillActive = true e regular o count_skill para a Skill ir direto onde eu quero e depois retomar o controle ao player.
	  // Clique SendInput dentro da tela ...

	  SkillActive = true;
	  count_skill += 2;
	 }
	 __except(EXCEPTION_EXECUTE_HANDLER)
	 {
	 }
	}

	__asm
	{
		popad
	}

	return 0;
}

/*
int UseTargetSpell(lua_State *L)
{
	if(HandlerSkillLoL == NULL)
	 HandlerSkillLoL = GetModuleLoL();

	int skill = (int)luaL_checknumber(L, 1);

	int x = (int)luaL_checknumber(L, 2);
	int y = (int)luaL_checknumber(L, 3);

	__try
	{
		__asm
		{

			//mov eax, HandlerSkillLoL
			//add eax, 0x010A5074			// 19/02/2014	**********************************
			//MOV EAX,DWORD PTR DS:[eax]

			//mov edi, HandlerSkillLoL
			//add edi, 0x050DC4			// 19/02/2014	**********************************
			//mov edi, dword ptr ds:[edi]

			mov ebx, HandlerSkillLoL
			add ebx, 0x029644E8

			//mov ecx, y
			//mov dword ptr ds:[ebx], ecx
			//mov ecx, z
			//mov dword ptr ds:[ebx+4], ecx
			//mov ecx, x
			//mov dword ptr ds:[ebx+8], ecx

			//mov ecx, edi

			//PUSH 0
			//PUSH 0
			//PUSH 0
			//mov ebx, HandlerSkillLoL
			//add ebx, 0x029E870			// 19/02/2014	**********************************
			//call ebx

			mov ebx, HandlerSkillLoL
			add ebx, 0x0211518				// 19/02/2014	**********************************
			MOV ebx,DWORD PTR DS:[ebx]
			mov ecx, ebx

			push 0
			push x		// X
			push y		// Y
			mov eax, HandlerSkillLoL
			add eax, 0x299300
			call eax


		}

		lua_pushnumber(L, 1);
		return 1;
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
	}

	lua_pushnumber(L, 0);
	return 0;
}*/

/*
011B3A86   F3:0F104D E8                                   MOVSS XMM1,DWORD PTR SS:[EBP-18]
011B3A8B   F3:0F1055 EC                                   MOVSS XMM2,DWORD PTR SS:[EBP-14]
011B3A90   F3:0F101D 5812A501                             MOVSS XMM3,DWORD PTR DS:[1A51258]
011B3A98   C700 00000000                                  MOV DWORD PTR DS:[EAX],0
011B3A9E   F3:0F1105 88287003                             MOVSS DWORD PTR DS:[3702888],XMM0
011B3AA6   F3:0F1105 94287003                             MOVSS DWORD PTR DS:[3702894],XMM0
011B3AAE   F3:0F1005 D013A501                             MOVSS XMM0,DWORD PTR DS:[1A513D0]
011B3AB6   F3:0F110D 80287003                             MOVSS DWORD PTR DS:[3702880],XMM1
011B3ABE   F3:0F110D 8C287003                             MOVSS DWORD PTR DS:[370288C],XMM1
011B3AC6   0F54C8                                         ANDPS XMM1,XMM0
011B3AC9   0F2FD9                                         COMISS XMM3,XMM1
011B3ACC   C705 A4287003 00000000                         MOV DWORD PTR DS:[37028A4],0
011B3AD6   F3:0F1115 84287003                             MOVSS DWORD PTR DS:[3702884],XMM2
011B3ADE   F3:0F1115 90287003                             MOVSS DWORD PTR DS:[3702890],XMM2 <-<<<<<<<<<<<<<<<<<<<<<<< HERE
011B3AE6   77 31                                          JA SHORT League_o.011B3B19
011B3AE8   68 50219901                                    PUSH League_o.01992150                   ; ASCII "Assert occurred, game may crash."
011B3AED   68 5CE19C01                                    PUSH League_o.019CE15C                   ; ASCII "pwHUD::GetTargetLocation"
011B3AF2   68 720B0000                                    PUSH 0B72
011B3AF7   68 C0DE9C01                                    PUSH League_o.019CDEC0                   ; ASCII "C:/jenkins/workspace/Code-CI-Releases-Public-Win32/code/Game/LoL/UX/Hud/Client/HudManager.cpp"
011B3AFC   BA 78E19C01                                    MOV EDX,League_o.019CE178                ; ASCII "Riot::std_abs(UI_TargetPos2.x) < 100000.0f"
011B3B01   E8 BA45DCFF                                    CALL League_o.00F780C0


*/

void InitHooked()
{
	if(HandlerSkillLoL == NULL)
	 HandlerSkillLoL = GetModuleLoL();

	unsigned char *pInt = opcode_hook;

	LPVOID pProtect;

	int offset_localhook = 0x433ADE;	// *********************** Atualizado 28/02/2014

	__asm
	{
		mov eax, HandlerSkillLoL
		add eax, offset_localhook
		mov ebx, eax

		mov ecx, HookMoveSkill
		sub ecx, ebx

		sub ecx, 5

		mov eax, ecx

		mov ecx, pInt
		add ecx, 1
		mov [ecx], eax

		mov eax, HandlerSkillLoL
		add eax, offset_localhook

		mov pProtect, eax
	}

	VirtualProtect((LPVOID)pProtect, 0x1024, PAGE_EXECUTE_READWRITE, 0);

	WriteProcessMemory((HANDLE)-1, pProtect, nop_opcode, 8, 0);
	WriteProcessMemory((HANDLE)-1, pProtect, opcode_hook, 5, 0);
}

void HookMoveSkill()
{
	if(HandlerSkillLoL == NULL)
	 HandlerSkillLoL = GetModuleLoL();

	__asm
	{
		pushad
	}

	__try
	{
		if(SkillActive) // Lanca a skill na coordenada que quero
		{
			__asm
			{
			 // Mouse Coordenadas
			 mov eax, HandlerSkillLoL
			 add eax, 0x298288C				// *********************** Atualizado 28/02/2014
			 mov ebx, map_spell_x
			 mov dword ptr ds:[eax], ebx
			 //mov dword ptr ds:[edi+0x12C], ebx
			 mov ebx, map_spell_z
			 mov dword ptr ds:[eax+4], ebx
			 //mov dword ptr ds:[edi+0x130], ebx
			 mov ebx, map_spell_y
			 mov dword ptr ds:[eax+8], ebx
			 //mov dword ptr ds:[edi+0x134], ebx
		    }

			if(count_skill <= 0x00)
			 SkillActive = false;
			else
		     count_skill--;
		}
		else
		{
			__asm
			{
			 mov eax, HandlerSkillLoL
			 add eax, 0x298288C					// *********************** Atualizado 28/02/2014
			 //MOVSS DWORD PTR DS:[eax], XMM2
			 MOVSS DWORD PTR DS:[eax+4], XMM2
			 //MOVSS DWORD PTR DS:[eax+8], XMM0
			}
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
	}

	__asm
	{
	 popad
	}
}