#ifndef __DRAW_OBJECT_H_
#define __DRAW_OBJECT_H_

#include "library.h"

#define D3DFVF_TL (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

struct D3DTLVERTEX
{
    float fX;
    float fY;
    float fZ;
    float fRHW;
    D3DCOLOR Color;
    float fU;
    float fV;
};

/*
struct text_object
{
	char text[1024];
	unsigned int size;
	int x, y;
	struct text_object *pTextObject;	// Next
};

void InitRegisterObject();
void RegisterObjectText(int x, int y, char *);
void DeleteObjectText();
void DrawObjectText();
*/

// *************  Draw Object ************* //

void CreateFont(char *type);
/*void DrawTextD3D(int x, int y, char *text);*/
int DrawTextD3D(lua_State *L);
VOID Clear(INT x, INT y, INT w, INT h, D3DCOLOR color);
VOID DrawBorder(INT x, INT y, INT w, INT h, INT px, D3DCOLOR BorderColor);
VOID DrawBox(INT X, INT Y, INT W, INT H, D3DCOLOR Color, D3DCOLOR BorderColor);
void DrawLine(float x1, float y1, float x2, float y2, DWORD color);
void DrawPoint(float x, float y, DWORD color);
void DrawCircle(float x, float y, float radius, DWORD color);
void Fillrgba(int x, int y, int w, int h, int r, int g, int b, int a);
D3DTLVERTEX CreateD3DTLVERTEX(float X, float Y, float Z, float RHW, D3DCOLOR color, float U, float V);
void Draw2DCircle(POINT pt, float radius, D3DCOLOR color);
void SetDevice(LPDIRECT3DDEVICE9);
LPDIRECT3DDEVICE9 GetDevice();

int LUA_COLOR(lua_State *L);

void DrawCircleD3D(int map_x, int map_y, int radius);

int DrawCircleGameD3D(lua_State *L);
void DrawGameCircleD3D(float map_x, float map_y, float map_z, float radius, float color);

void CreateLine();
void FillR(float x, float y, float w, float h, D3DCOLOR color);

void DrawSelectBox(INT x, INT y, INT w, INT h, D3DCOLOR color);

#endif