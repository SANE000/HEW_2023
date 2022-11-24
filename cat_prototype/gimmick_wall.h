#pragma once


#pragma once

#include <d3dx9.h>
#include "block.h"

//==========================================
//マクロ定義
//==========================================
#define WALL_MAX 128



//==========================================
//プロトタイプ宣言
//==========================================
HRESULT InitGimmickWall();
void UninitGimmickWall();
void UpdateGimmickWall();
void DrawGimmickWall();

BLOCK* GetGimmickWall();
