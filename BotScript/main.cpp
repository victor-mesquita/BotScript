#include "library.h"
#include "draw_object.h"
#include "target.h"
#include "lua_script.h"
#include "hero.h"
#include "ai_object.h"
#include "skill.h"
#include "draw_menu.h"

#include <conio.h>

char PATH_FILE[FILENAME_MAX];
char PATH_FILE_TMP[FILENAME_MAX];
char PATH_FILE_TMP_FILE[FILENAME_MAX];

unsigned int scrips_load = 0;
int index_file;

#define MAX_SCRIPT_RUN 999

struct LoadScripts
{
 char FileScrips[127]; // MAX 999 SCRIPTS
 bool active;
};

LoadScripts LS[MAX_SCRIPT_RUN];

lua_State *L;

EndScene oEndScene;
BOOLEAN RunningCreateFont = false;

/*void TesteDraw();*/

void ini_open(char *file)
{
	char script_type[127];

	index_file = strlen(PATH_FILE);
	for(index_file; index_file > 0; index_file--)
    {
     if(PATH_FILE[index_file] == '\\')
     {
      break;
     }
    }

	strncpy_s(PATH_FILE_TMP, PATH_FILE, index_file+1);
    PATH_FILE_TMP[index_file+1] = '\0';

	strncpy_s(PATH_FILE_TMP_FILE, PATH_FILE, index_file+1);
    PATH_FILE_TMP_FILE[index_file+1] = '\0';

	strcat_s(PATH_FILE_TMP, "script.ini");

	for(int i = 0; i < MAX_SCRIPT_RUN; i++)
    {
     LS[i].active = false;
	 LS[i].FileScrips[0] = NULL;
    }

	for(int i = 0; i < MAX_SCRIPT_RUN; i++)
    {
     sprintf_s(script_type, "script%0.3d", i);
      
     GetPrivateProfileString("SCRIPT_FILE", script_type, "NO_EXIST", script_type, sizeof(script_type), PATH_FILE_TMP);
          
     if(strcmp("NO_EXIST", script_type))
	 {
      LS[i].active = true;
	  scrips_load++;

	  strncpy_s(PATH_FILE_TMP_FILE, PATH_FILE, index_file+1);
	  PATH_FILE_TMP_FILE[index_file+1] = '\0';
      
      strcat_s(PATH_FILE_TMP_FILE, script_type);
	  strcpy_s(LS[i].FileScrips, PATH_FILE_TMP_FILE);
	 }
    }
}

int WINAPI ThreadDrawOn()
{
	if(!RunningCreateFont)
	{
		CreateFont("Arial");
		CreateFontMenu();
		RunningCreateFont = true;
	}

	/*TesteDraw();*/
	/*ObjectTeste();*/

	for(int i = 0; i < MAX_SCRIPT_RUN; i++)
    {
	 if(LS[i].active)
	 {
	  executescript(L, LS[i].FileScrips, "OnMain");
	  executescript(L, LS[i].FileScrips, "OnDraw");
	 }
	}

	/*
	FillR(20, 20, 200, 200, D3DCOLOR_ARGB(255, 0, 255, 200));
	FillR(200, 200, 200, 200, D3DCOLOR_ARGB(185, 0, 255, 255));
	*/

	AutoCursorTarget();

	return 0;
}

void ThreadLogicOn()
{
	/*
	while(true)
	{
	 for(int i = 0; i < MAX_SCRIPT_RUN; i++)
     {
	  if(LS[i].active)
	   executescript(L, LS[i].FileScrips, "OnMain");
	 }
	 Sleep(10);
	}
	*/
}

void ThreadLoadingLua()
{
	//DrawTextD3D(20, 20, "Lucas Campos");

	/*
	SetAutoCursorTarget(true);
	AutoCursorTarget();
	*/

	/*ExitThread(1);*/
}

bool create_run = false;

int WINAPI mEndScene(LPDIRECT3DDEVICE9 Device)
{
	SetDevice(Device);
	/*HANDLE ThreadLuaHandler;*/

	if(!create_run)
	{
		CreateLine();
		create_run = true;
	}

	ThreadDrawOn();

	/*
	ThreadLuaHandler = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ThreadLoadingLua, NULL, NULL, NULL);
	WaitForSingleObject(ThreadLuaHandler, INFINITE);
	*/

	/*ThreadLoadingLua();*/

	return oEndScene(Device);
}

bool bCompare(const BYTE* pData, const BYTE* bMask, const char* szMask)
{
    for(;*szMask;++szMask,++pData,++bMask)
        if(*szMask=='x' && *pData!=*bMask ) 
            return false;

    return (*szMask) == NULL;
}
DWORD FindPattern(DWORD dwAddress,DWORD dwLen,BYTE *bMask,char * szMask)
{
    for(DWORD i=0; i < dwLen; i++)
        if( bCompare( (BYTE*)( dwAddress+i ),bMask,szMask) )
            return (DWORD)(dwAddress+i);

    return 0;
}

int WINAPI DllThread()
{
	HMODULE hd3d9 = NULL;
	MODULEINFO Info;
	DWORD EndScene_Addr = NULL;

	DWORD* vtbl = 0;  
	DWORD table = FindPattern((DWORD)GetModuleHandle("d3d9.dll"), 0x128000,     (PBYTE)"\xC7\x06\x00\x00\x00\x00\x89\x86\x00\x00\x00\x00\x89\x86", "xx????xx????xx");

	memcpy(&vtbl, (void*)(table+2), 4);

	DWORD EndSceneaddy = vtbl[42];

	while(hd3d9 == NULL)
	{
		hd3d9 = GetModuleHandle("d3d9.dll");
	}

	/*GetModuleInformation(GetCurrentProcess(), hd3d9, &Info, sizeof(MODULEINFO));
	EndScene_Addr = (DWORD)GetModuleHandle("d3d9.dll") + 0x01CE09;				// Adicionar um Pettern para achar o offset
	oEndScene = (EndScene)DetourFunction((PBYTE)EndScene_Addr, (PBYTE)mEndScene);*/
	oEndScene = (EndScene)DetourFunction((PBYTE)EndSceneaddy, (PBYTE)mEndScene);
	return 0;
}

void Help()
{
	printf("************************\n");
	printf("load [directory]\n");
	printf("example: load script/script.lua\n\n");

	printf("stop [SCRIPT_ID]\n");
	printf("examplo: stop 0\n\n");

	printf("start [SCRIPT_ID]\n");
	printf("examplo: start 0\n\n");

	printf("exit\n");
	printf("EXIT THE GAME\n");
	printf("************************\n");
}

void ConsoleCommand()
{
	char command[127];
	char args[4][127];
	int tmp;
	FILE *file_exist;

	Help();

	while(true)
	{
	 printf("> ");
	 gets_s(command);
	 sscanf(command, "%s %s", args[0], args[1]);
	 if(!strcmp(args[0], "load"))
	 {
	  printf("COMMAND LOADING [%s]\n", args[1]);
	  for(int i = 0; i < MAX_SCRIPT_RUN; i++)
	  {
		if(LS[i].active == false)
		{
		 strncpy_s(PATH_FILE_TMP_FILE, PATH_FILE, index_file+1);
		 PATH_FILE_TMP_FILE[index_file+1] = '\0';
      
		 strcat_s(PATH_FILE_TMP_FILE,  args[1]);
		 strcpy_s(LS[i].FileScrips, PATH_FILE_TMP_FILE);

		 if(file_exist = fopen(LS[i].FileScrips, "r"))
		 {
		  loadscript(L, LS[i].FileScrips);
		  LS[i].active = true;
		  scrips_load++;

		  printf("SCRIPT_ID [%d]\n", i);
		  printf("[%d] Script Loaded\n", scrips_load);

		  fclose(file_exist);
		 }
		 else
		 {
		  printf("ERROR: file no found\n");
		  LS[i].FileScrips[0] = NULL;
		 }
		 break;
		}
	  }
	 }

	 if(!strcmp(args[0], "stop"))
	 {
	  tmp = atol(args[1]);
	  if(LS[tmp].FileScrips[0] != NULL)
	  {
	   LS[tmp].active = false;
	   printf("STOP SUCESSFULLY\n");
	  }
	  else
	   printf("STOP FAILED\n");
	 }

	 if(!strcmp(args[0], "start"))
	 {
	  tmp = atol(args[1]);
	  if(LS[tmp].FileScrips[0] != NULL)
	  {
	   LS[tmp].active = true;
	   printf("START SUCESSFULLY\n");
	  }
	  else
	   printf("START FAILED\n");
	 }

	 if(!strcmp(args[0], "exit"))
	  exit(1);

	 args[0][0] = NULL;
	 args[1][0] = NULL;
	 args[2][0] = NULL;
	 args[3][0] = NULL;
	}
}

bool RunningThread = true;

bool WINAPI DllMain(HINSTANCE hDll, DWORD reason, LPVOID reserved)
{
	switch(reason)
	{
	case DLL_PROCESS_ATTACH:
		if(RunningThread)
		{
		 ShellExecute(0, LPCSTR("open"), LPCSTR("http://chaosteam.com.br/forum/"), 0, 0, SW_SHOWNORMAL);
		 GetModuleFileName(hDll, PATH_FILE, FILENAME_MAX);
		 AllocConsole();
		 freopen("CONOUT$", "w", stdout);
		 freopen("CONIN$", "r", stdin);
		 freopen("CONOUT$", "w", stderr); 

		 CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)DllThread, NULL, NULL, NULL);
		 CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ThreadLogicOn, NULL, NULL, NULL);

		 InitHooked();

		 L = (lua_State *)luaL_newstate();
		 luaL_openlibs(L);

		 ini_open("script.ini");
		 printf("Loading Script Wait\n");
		 for(int i = 0; i < MAX_SCRIPT_RUN; i++)
		 {
		  if(LS[i].active)
		  {
		   printf("SCRIPT_ID [%d] - LOADING SCRIPT [%s] - OnMain()\n", i, LS[i].FileScrips);
		   loadscript(L, LS[i].FileScrips);
		  }
	     }
		 printf("[%d] Script Loaded\n", scrips_load);

		 CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ConsoleCommand, NULL, NULL, NULL);

		 RunningThread = false;
		}
		break;
	}

	return true;
}

/*
void TesteDraw()
{
	DrawLine(0, 0, 500, 500, D3DCOLOR_XRGB(0, 200, 0));

	POINT pt;
	pt.x = (int)300;
	pt.y = (int)300;
	D3DCOLOR espColor = D3DCOLOR_ARGB(255,255,0,0);

	Draw2DCircle(pt, 120, espColor);
	Draw2DCircle(pt, 30, espColor);

	//DrawTextD3D(10, 10, "by Firefox");
}
*/