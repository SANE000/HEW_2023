#pragma once

#include "main.h"
#include "renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
struct CAMERA_2D
{
	D3DXVECTOR2 pos;

	bool move;
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void DrawCamera(void);

CAMERA_2D* GetCamera(void);
D3DXVECTOR2 GetBase(void);
