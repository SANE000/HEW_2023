//////////////////////////当たり判定を作る
#pragma once

#include "cat.h"
#include "block.h"
//マクロ定義
#define SENSOR_SIZE	(10.0f)		//ジャンプセンサーの横サイズ



//==============================
//プロトタイプ宣言
//==============================
HRESULT InitCollsion();
void UpdateCollision();//当たり判定を一気に行う

bool CollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2,
	D3DXVECTOR2 size1, D3DXVECTOR2 size2);

float SearchJumpHeight(MOVE_BLOCK* mb, CAT* c, int i);
int GetBlockNum();

