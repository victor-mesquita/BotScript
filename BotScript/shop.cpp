#include "shop.h"

// .c totalmente atualizado -> 28/02/2014

int global_offset = 0x029BEFAC; // 28/02/2014	**********************************

int aux_tmp_eax;
int aux_tmp_ecx;

DWORD ShopHandlerLoL;

int SellItem(lua_State *L)
{
	unsigned int Slot = (unsigned int)luaL_checknumber(L, 1);
	int Quantity = (int)luaL_checknumber(L, 2);

	if(ShopHandlerLoL == NULL)
	 ShopHandlerLoL = GetModuleLoL();
	__try
	{
		__asm
		{
			mov eax, ShopHandlerLoL
			add eax, global_offset
			MOV ECX,DWORD PTR DS:[eax]

			mov esi, 2003
			PUSH esi	// ItemID (SEM NECESSIDADE).
			//MOV DWORD PTR SS:[ESP+18], EAX
			mov ebx, ShopHandlerLoL
			add ebx, 0x1FB140						// 28/02/2014 **********************************
			call ebx
			mov aux_tmp_eax, eax
			mov aux_tmp_ecx, ecx
		}

		for(int i = 0; i < Quantity; i++)
		{
			__asm
			{
				mov eax, aux_tmp_eax
				mov ecx, aux_tmp_ecx

				MOV ecx,DWORD PTR DS:[EAX+0x04]

				mov edx, ShopHandlerLoL
				add edx, global_offset
				mov edx, dword ptr ds:[edx]
			 
				push ecx
				push Slot								// Slot (0 ~ 6)
				mov ebx, 0
				LEA ecx,DWORD PTR DS:[edx+0x0FB0]
				mov edx, ShopHandlerLoL
				add edx, 0x2AD0C0		// 28/02/2014	**********************************
				call edx
				}
			}
		}
		__except(EXCEPTION_EXECUTE_HANDLER)
		{
			//MessageBox(0, LPCSTR("SellItem(Slot, Quantity) failed - exception"), LPCSTR("Exception Error"), 0);
		}
		return 0;
}

int BuyItem(lua_State *L)
{
	unsigned int ItemID = (int)luaL_checknumber(L, 1);

	if(ShopHandlerLoL == NULL)
	 ShopHandlerLoL = GetModuleLoL();

	__try
	{
		__asm
		{
			/*
			005540A1   FF15 C018DA00    CALL DWORD PTR DS:[<&MSVCR110.atoi>]     ; msvcr110.atoi
			005540A7   83C4 04          ADD ESP,4
			005540AA   8BF0             MOV ESI,EAX
			005540AC   56               PUSH ESI
			005540AD   E8 FE79D9FF      CALL League_o.002EBAB0
			*/

			mov eax, ShopHandlerLoL
			add eax, 0x1FB140	// 28/02/2014	**********************************
			mov esi, ItemID		// ID Item ...
			push esi
			call eax

			/*
			0055409E   8B00             MOV EAX,DWORD PTR DS:[EAX]
			005540A0   50               PUSH EAX
			005540A1   FF15 C018DA00    CALL DWORD PTR DS:[<&MSVCR110.atoi>]     ; msvcr110.atoi
			005540A7   83C4 04          ADD ESP,4
			005540AA   8BF0             MOV ESI,EAX
			005540AC   56               PUSH ESI			    <-------- Here
			005540AD   E8 FE79D9FF      CALL League_o.002EBAB0  <-------- Here
			005540B2   8BD8             MOV EBX,EAX
			005540B4   85DB             TEST EBX,EBX
			005540B6   75 24            JNZ SHORT League_o.005540DC
			005540B8   A1 70B63401      MOV EAX,DWORD PTR DS:[134B670]
			005540BD   56               PUSH ESI
			005540BE   68 E8EFEE00      PUSH League_o.00EEEFE8                   ; ASCII "GAME_UI: (FoundryItemShop) Item %d is NULL"
			005540C3   FF35 74B63401    PUSH DWORD PTR DS:[134B674]
			005540C9   83C8 01          OR EAX,1
			005540CC   50               PUSH EAX
			005540CD   6A 02            PUSH 2
			005540CF   E8 9CE8DDFF      CALL League_o.00332970
			005540D4   83C4 14          ADD ESP,14
			005540D7   E9 D5010000      JMP League_o.005542B1
			005540DC   8B43 04          MOV EAX,DWORD PTR DS:[EBX+4] <-------- Here
			005540DF   894424 18        MOV DWORD PTR SS:[ESP+18],EAX <-------- Here
			*/


			/*
			00554110   8B4424 18        MOV EAX,DWORD PTR SS:[ESP+18] <-------- Here
			00554114   8078 7B 00       CMP BYTE PTR DS:[EAX+7B],0
			00554118   0F84 A7000000    JE League_o.005541C5
			0055411E   8BC8             MOV ECX,EAX  <-------- Here
			00554120   E8 9BF6FFFF      CALL League_o.005537C0
			*/

			MOV EBX,EAX

			MOV EAX,DWORD PTR DS:[EBX+0x04]
			MOV ECX,EAX
			mov ebx, ShopHandlerLoL
			add ebx, 0x45D910	// 28/02/2014	**********************************
			call ebx

			mov eax, ShopHandlerLoL
			add eax, global_offset
			MOV ECX,DWORD PTR DS:[eax]
			push esi
		    LEA ECX,DWORD PTR DS:[ECX+0xFB0]
			mov ebx, ShopHandlerLoL
			add ebx, 0x2ACEB0	// 28/02/2014	**********************************
			call ebx
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		//MessageBox(0, LPCSTR("BuyItem(ItemID) failed - exception"), LPCSTR("Exception Error"), 0);
	}
	return 0;
}

int GetInventorySlot(lua_State *L)
{
	int tmp;
	if(ShopHandlerLoL == NULL)
	 ShopHandlerLoL = GetModuleLoL();

	unsigned int Slot = (int)luaL_checknumber(L, 1);

	//MessageBox(0, LPCSTR(" "), LPCSTR(" "), 0);

	__asm
	{
		pushad
	}

	tmp = IntermedGetInventorySlot(Slot);

	__asm
	{
		popad
	}

	lua_pushnumber(L, tmp);
	return 1;
}

int IntermedGetInventorySlot(int SlotID)
{
	int tmp;
	__try
	{
		__asm
		{
			// 28/02/2014	**********************************
			mov ecx, ShopHandlerLoL
			add ecx, global_offset
			MOV ECX,DWORD PTR DS:[ecx]
			mov esi, SlotID
			PUSH esi
			ADD ECX,0x0FB0
			mov ebx, ShopHandlerLoL
			add ebx, 0x2AE9F0			// 28/02/2014	**********************************
			call ebx
			mov tmp, eax
		}

		return tmp;
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		//MessageBox(0, LPCSTR("GetInventorySlot(SlotID) failed - exception"), LPCSTR("Exception Error"), 0);
	}

	return 0;
}

int GetItemQuantity(lua_State *L)
{
	if(ShopHandlerLoL == NULL)
	 ShopHandlerLoL = GetModuleLoL();

	int tmp;
	unsigned int Slot = (int)luaL_checknumber(L, 1);

	//MessageBox(0, LPCSTR(" "), LPCSTR(" "), 0);

	__asm
	{
		pushad
	}

	tmp = IntermedGetQuantitySlot(Slot);

	__asm
	{
		popad
	}

	lua_pushnumber(L, tmp);
	return 1;
}

int IntermedGetQuantitySlot(int SlotID)
{
	int tmp;
	__try
	{
		__asm
		{
			// 28/02/2014	**********************************
			mov ecx, ShopHandlerLoL
			add ecx, global_offset
			MOV ECX,DWORD PTR DS:[ecx]
			mov esi, SlotID
			ADD ECX,0x0FB0

			mov edi, ecx

			MOV EAX,DWORD PTR DS:[EDI+ESI*0x04+0x6C]
			MOV EAX,DWORD PTR DS:[EAX+0x04] // Quantity Item
			mov tmp, eax
		}

		return tmp;
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		//MessageBox(0, LPCSTR("GetInventorySlot(SlotID) failed - exception"), LPCSTR("Exception Error"), 0);
	}

	return 0;
}

int ShopStatus(lua_State *L)
{
	if(ShopHandlerLoL == NULL)
	 ShopHandlerLoL = GetModuleLoL();

	int tmp = 0;
	__try
	{
	 __asm
	 {
	  mov eax,  ShopHandlerLoL
	  add eax, 0x029BFA9C		// 28/02/2014	**********************************
	  mov eax, dword ptr ds:[eax]

	  add eax, 0x18
	  mov eax, dword ptr ds:[eax]

	  add eax, 0x10
	  mov eax, dword ptr ds:[eax]

	  add eax, 0x24
	  mov eax, dword ptr ds:[eax]

	  add eax, 0x770
	  mov eax, dword ptr ds:[eax]


	  add eax, 0x48			// ShopActive

	  mov eax, dword ptr ds:[eax]
	  mov tmp, eax
	 }
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		//MessageBox(0, LPCSTR("ShopStatus() failed - exception"), LPCSTR("Exception Error"), 0);
	}

	lua_pushnumber(L, tmp);
	return 1;
}