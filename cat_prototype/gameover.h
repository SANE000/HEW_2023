#pragma once

#include "main.h"
#include "renderer.h"

struct  GAMEOVER
{
	D3DXVECTOR3 pos;
	D3DXVECTOR2 size;
	D3DXCOLOR   col;
	int         texNo;
};

HRESULT InitGameOver();
void UninitGameOver();
void UpdateGameOver();
void DrawGameOver();

