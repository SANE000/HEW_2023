#pragma once


#pragma once

#include <d3dx9.h>
#include "block.h"

//==========================================
//�}�N����`
//==========================================
#define WALL_MAX 128



//==========================================
//�v���g�^�C�v�錾
//==========================================
HRESULT InitGimmickWall();
void UninitGimmickWall();
void UpdateGimmickWall();
void DrawGimmickWall();

BLOCK* GetGimmickWall();
