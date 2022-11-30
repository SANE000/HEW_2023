//////////////////////////当たり判定を作る
#pragma once

#include "cat.h"
#include "block.h"
#include "blockpreview.h"
#include "gimmick_wall.h"



//==============================
//プロトタイプ宣言
//==============================
HRESULT InitCollsion();
void UpdateCollision();//当たり判定を一気に行う

bool CollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2,
	D3DXVECTOR2 size1, D3DXVECTOR2 size2);

float SearchJumpHeight(MOVE_BLOCK* mb, CAT* c, int i);
float SearchJumpHeightB(BLOCK* b, CAT* c, int i);
float SearchJumpHeightG(G_WALL* b, CAT* c, int i);

int GetBlockNum();

