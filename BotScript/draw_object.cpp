#include "draw_object.h"

// .c totalmente atualizado -> 27/02/2014

LPDIRECT3DDEVICE9 GlobalDevice;
ID3DXFont* dx_Font = NULL;
LPD3DXLINE line;

const double PI = 3.14159265358979323846264338327950288419;
/*
text_object InitTextObject;

void InitRegisterObject()
{
	InitTextObject.text[0] = NULL;
	InitTextObject.size = NULL;
	InitTextObject.pTextObject = NULL;
}
*/

/*
void RegisterObjectText(int x, int y, char *text)
{
	text_object *pTextObject = InitTextObject.pTextObject;
	for(;;)
	{
		if(pTextObject->pTextObject == NULL)
		 break;
		pTextObject = pTextObject->pTextObject;
	}

	pTextObject->pTextObject = (text_object *)malloc(sizeof(text_object));
	pTextObject = pTextObject->pTextObject;
	pTextObject->pTextObject = NULL;
	pTextObject->x = x;
	pTextObject->y = y;

	for(;;)
	{
		strcpy(pTextObject->text, text);
		pTextObject->size = sizeof(text);
	}
}*/

/*
void DeleteObjectText()
{
	text_object *pTextObject = InitTextObject.pTextObject;
	text_object *pTextObjectAux;
	if(pTextObject != NULL)
	{
	 for(;;)
	 {
		if(pTextObject->pTextObject == NULL)
		{
		 free(pTextObject);
		 break;
		}

	   pTextObjectAux = pTextObject->pTextObject;
	   free(pTextObject);
	   pTextObject = pTextObjectAux;
	 }
	}

	InitTextObject.pTextObject = NULL;
}*/

/*
void DrawObjectText()
{
	text_object *pTextObject = InitTextObject.pTextObject;
	text_object *pTextObjectAux;
	if(pTextObject != NULL)
	{
	 for(;;)
	 {
		DrawTextD3D(pTextObject->x, pTextObject->y, pTextObject->text);

		pTextObjectAux = pTextObject->pTextObject;
		free(pTextObject);
		pTextObject = pTextObjectAux;

		if(pTextObject == NULL)
		 break;
	 }
	}
}
*/

void CreateFont(char *type)
{
	free(dx_Font);
	//D3DXCreateFontA(GlobalDevice, 14, 0, 4, 0, false, 1, 0, 0, 0, type, &dx_Font);
	D3DXCreateFontA(GlobalDevice, 22, 0, 4, 0, false, 1, 0, 0, 0, type, &dx_Font);
}

int DrawTextD3D(lua_State *L)
{
	const char *text = (const char *)lua_tostring(L, 3);
	int x = (int)lua_tonumber(L, 1);
	int y = (int)lua_tonumber(L, 2);
	int color = (int)lua_tonumber(L, 4);

	RECT pos;
	pos.bottom = 0;
	pos.left = x;
	pos.right = 0;
	pos.top = y;

	dx_Font->DrawTextA(NULL, text, strlen(text), &pos, DT_NOCLIP, color);

	return 0;
}

VOID Clear(INT x, INT y, INT w, INT h, D3DCOLOR color, LPDIRECT3DDEVICE9 pDevice)
{
	D3DRECT rec = {x, y, x + w, y + h};
	pDevice->Clear(1, &rec, D3DCLEAR_TARGET, color, 0, 0);
}

VOID DrawBorder(INT x, INT y, INT w, INT h, INT px, D3DCOLOR BorderColor)
{
	Clear(x, (y + h - px), w, px, BorderColor, GlobalDevice);
	Clear(x, y, px, h, BorderColor, GlobalDevice);
	Clear(x, y, w, px, BorderColor, GlobalDevice);
	Clear((x + w - px), y, px, h, BorderColor, GlobalDevice);
}

VOID DrawBox(INT X, INT Y, INT W, INT H, D3DCOLOR Color, D3DCOLOR BorderColor)
{
	
	DrawBorder(X, Y, W, H, 2, BorderColor);
	
	CONST DWORD D3D_FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;
	struct Vertex 
	{
		FLOAT X, Y, W, H;
		D3DCOLOR Color;
	} V[4] = {
		{(FLOAT)X, (FLOAT)(Y + H), 0.0F, 0.0F, Color}, 
		{(FLOAT)X, (FLOAT)Y, 0.0F, 0.0F, Color}, 
		{(FLOAT)(X + W), (FLOAT)(Y + H), 0.0F, 0.0F, Color}, 
		{(FLOAT)(X + W), (FLOAT)Y, 0.0F, 0.0F, Color}
	};

	GlobalDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, D3DZB_TRUE);
	GlobalDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	GlobalDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	GlobalDevice->SetRenderState(D3DRS_FOGENABLE, D3DZB_FALSE);

	//FillR(20, 20, 200, 350, D3DCOLOR_ARGB(185, 0, 255, 255));

	GlobalDevice->SetFVF(D3D_FVF);
	GlobalDevice->SetTexture(0, NULL);
	GlobalDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, V, sizeof(Vertex));
}

void DrawLine(float x1, float y1, float x2, float y2, DWORD color)
{
        /*LPD3DXLINE line;
        D3DXCreateLine(GlobalDevice, &line);*/
        D3DXVECTOR2 lines[] = {D3DXVECTOR2(x1, y1), D3DXVECTOR2(x2, y2)};
        line->Begin();
        line->Draw(lines, 2, color);
        line->End();
        line->Release();
}

void DrawPoint(float x, float y, DWORD color)
{
    DrawLine(x, y, x + 1, y + 1, color);
}

void DrawCircle(float x, float y, float radius, DWORD color)
{
     double t;
     for (t = 0.000; t <= PI*2; t += 0.01)
		 DrawPoint((float)((radius+(radius))*cos(t) + x), (float)((radius)*sin(t) + y), color);
}


void Fillrgba(int x, int y, int w, int h, int r, int g, int b, int a)
{
    D3DXVECTOR2 vLine[2];
    
    vLine[0].x = (float)x + w/2;
    vLine[0].y = (float)y;
    vLine[1].x = (float)x + w/2;
    vLine[1].y = (float)y + h;

    //prepare for drawing. draw. stop drawing
	DrawLine(vLine[0].x, vLine[0].y, vLine[1].x, vLine[1].y, D3DCOLOR_XRGB(0, 255, 0));
}

D3DTLVERTEX CreateD3DTLVERTEX(float X, float Y, float Z, float RHW, D3DCOLOR color, float U, float V)
{
    D3DTLVERTEX v;

    v.fX = X;
    v.fY = Y;
    v.fZ = Z;
    v.fRHW = RHW;
    v.Color = color;
    v.fU = U;
    v.fV = V;

    return v;
}

void Draw2DCircle(POINT pt, float radius, D3DCOLOR color)
{
	const int NUMPOINTS = 50;
	D3DTLVERTEX Circle[NUMPOINTS + 1];
	int i;
	float X;
	float Y;
	float Theta;
	float WedgeAngle; //Size of angle between two points on the circle (single wedge)
	//Precompute WedgeAngle
	WedgeAngle = (float)((2*PI) / NUMPOINTS);
	//Set up vertices for a circle
	//Used <= in the for statement to ensure last point meets first point (closed circle)
	for(i=0; i<=NUMPOINTS; i++)
	{
	 //Calculate theta for this vertex
	 Theta = i * WedgeAngle;
 
	 //Compute X and Y locations
	 X = (float)(pt.x + (radius+radius) * cos(Theta));
	 Y = (float)(pt.y - radius * sin(Theta));
	 Circle[i] = CreateD3DTLVERTEX(X, Y, 0.0f, 1.0f, color, 0.0f, 0.0f);
	}
	//Now draw the circle
	GlobalDevice->SetFVF(D3DFVF_TL);
	GlobalDevice->SetTexture(0, NULL);
	//dev->SetVertexShader (D3DFVF_MIRUSVERTEX);
	GlobalDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, NUMPOINTS, &Circle[0], sizeof(Circle[0]));
}

void SetDevice(LPDIRECT3DDEVICE9 LocalDevice)
{
	GlobalDevice = LocalDevice;
}

LPDIRECT3DDEVICE9 GetDevice()
{
	return GlobalDevice;
}

int LUA_COLOR(lua_State *L)
{
	int r = (int)lua_tonumber(L, 1);
	int b = (int)lua_tonumber(L, 2);
	int g = (int)lua_tonumber(L, 3);

	lua_pushinteger(L, D3DCOLOR_XRGB(r, b, g));
	return 1;
}


DWORD DrawHandlerLoL;

/*
int VECTOR_DIVISION = 40;

void DrawCircleD3D(int map_x, int map_y, int radius)
{
	if(DrawHandlerLoL == 0x00)
	 DrawHandlerLoL = GetModuleLoL();

	float view_x;
	float view_y;

	__try
	{
	 __asm
	 {
	  mov eax, DrawHandlerLoL
	  add eax, 0x0DEF9C8						// 14/02/2014
	  mov eax, dword ptr ds:[eax]
	  mov view_x, eax
	 }

	 __asm
	 {
	  mov eax, DrawHandlerLoL
	  add eax, 0x010BEBF0					// 14/02/2014
	  mov eax, dword ptr ds:[eax]
	  add eax, 0x244
	  mov eax, dword ptr ds:[eax]
	  add eax, 0x608
	  mov eax, dword ptr ds:[eax]
	  add eax, 0xf4
	  mov eax, dword ptr ds:[eax]
	  add eax, 0x44
	  mov eax, dword ptr ds:[eax]
	  add eax, 0x78
	  mov eax, dword ptr ds:[eax]
	  mov view_y, eax
	 }
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
	}

	POINT pt;

	if(GetAsyncKeyState(VK_F11))
	{
	 VECTOR_DIVISION++;
	}

	if(GetAsyncKeyState(VK_F12))
	{
	 VECTOR_DIVISION--;
	}

	if(VECTOR_DIVISION >= 100)
	 VECTOR_DIVISION = 100;

	if(VECTOR_DIVISION <= 0)
	 VECTOR_DIVISION = 0;

	view_y -= 300.0;
	view_x -= 300.0;

	view_x = (-1)*(view_x*VECTOR_DIVISION)/100;
	view_y = (view_y*VECTOR_DIVISION)/100;

	//map_x = (map_x*VECTOR_DIVISION)/100;
	//map_y = (map_y*VECTOR_DIVISION)/100;

	map_x = -300;
	map_y = -300;
	*/
/*
	pt.x = (int)(view_x-map_x)/*-((300*VECTOR_DIVISION)/100)*/;
	/*pt.y = (int)(view_y-map_y)/*+((300*VECTOR_DIVISION)/100)*/;
	/*Draw2DCircle(pt, radius, D3DCOLOR_XRGB(255, 0, 0));

	RECT pos;
	pos.bottom = 0;
	pos.left = 20;
	pos.right = 0;
	pos.top = 20;

	char vactor[1024];

	sprintf_s(vactor, "VECTOR -> %d x %d y %d mapx %d mapy %d (%d - %d)", VECTOR_DIVISION, (int)map_x, (int)map_y, (int)view_x, (int)view_y, pt.x, pt.y);

	dx_Font->DrawTextA(NULL, vactor, strlen(vactor), &pos, DT_NOCLIP, D3DCOLOR_XRGB(255, 0, 0));
}*/

char buffer[1024*10];

int DrawCircleGameD3D(lua_State *L)
{
	float map_x, map_y, map_z, radius;

	map_x = (float)luaL_checknumber(L, 1);
	map_y = (float)luaL_checknumber(L, 2);
	map_z = (float)luaL_checknumber(L, 3);
	radius = (float)luaL_checknumber(L, 4);

	__asm
	{
		pushad
	}

	DrawGameCircleD3D(map_x, map_y, map_z, radius, 0);

	__asm
	{
		popad
	}

	return 1;
}

void DrawGameCircleD3D(float map_x, float map_y, float map_z, float radius, float color)
{
	if(DrawHandlerLoL == 0x00)
	 DrawHandlerLoL = GetModuleLoL();

	color = color;

	__try
	{
		__asm
		{
			push 0x3F800000 // COLOR ?
			push 0x00000000
			push 0x00000000

			//push 0x4388C6A5 // (1227.000000) X
			//push 0x43389DAF // (108.464211) Z
			//push 0x420F9C78 // (2351.000000) Y

			push map_y
			push map_z
			push map_x

			mov ecx, esp

			push ebp // COLOR ?

			/*
			mov eax, DrawHandlerLoL
			add eax, 0x010C95D0
			mov eax, dword ptr ds:[eax]

			add eax, 0x60
			mov eax, dword ptr ds:[eax]

			add eax, 0x44
			mov eax, dword ptr ds:[eax]

			add eax, 0x28
			mov eax, dword ptr ds:[eax]

			add eax, 0x0c
			mov eax, dword ptr ds:[eax]

			add eax, 0x28
			mov eax, dword ptr ds:[eax]*/

			lea eax, buffer

			push eax // (736259.000000) -> Especial
			add eax, 0x04
			push eax //(736259.500000) -> Especial


			push 0x3F800000 // (1.0000)
			push 0x00000000
			push 0x00000000

			//mov ecx, ebp
			mov eax, ecx

			push 0x00000000

			//push 0x442F0000 // (Radius) 700.00
			
			push radius
			
			//mov edx, DrawHandlerLoL
			//add edx, 0x0DF4DC8				// 

			mov edx, DrawHandlerLoL
			add edx, 0x01BB804				// 27/02/2014 **********************************

			//LEA ECX,DWORD PTR SS:[EBP-0x18]

			mov ebx, DrawHandlerLoL
			add ebx, 0x03C2E90				// 27/02/2014 **********************************
			call ebx
			ADD ESP, 0x14
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
	}
}

void FillR(float x, float y, float w, float h, D3DCOLOR color)
{
	D3DXVECTOR2 vLine[2];

	line->SetAntialias(true);
	line->SetWidth(w);
	line->SetGLLines(true);

	vLine[0].x = x + w/2;
    vLine[0].y = y;
    vLine[1].x = x + w/2;
    vLine[1].y = y + h;

	line->Begin();
	line->Draw(vLine, 2, color);
	line->End();
}

void CreateLine()
{
	D3DXCreateLine(GlobalDevice, &line);
}

void DrawSelectBox(INT x, INT y, INT w, INT h, D3DCOLOR color)
{
	D3DRECT rec = {x, y, x + w, y + h};
	GlobalDevice->Clear(1, &rec, D3DCLEAR_TARGET, color, 0, 0);
}
