#pragma once

#include "main.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
struct CAMERA_2D
{
	D3DXVECTOR2 pos;
	D3DXVECTOR2 Oldpos;

	bool move;
	bool moveRight;
	bool moveLeft;
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void DrawCamera(void);

CAMERA_2D* GetCamera(void);
D3DXVECTOR2 GetBase(void);
