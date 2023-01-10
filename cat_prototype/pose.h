#pragma once

struct POSE
{
	D3DXVECTOR3 pos;
	D3DXVECTOR2 size;
	D3DXCOLOR   col;
	int         texNo;

	bool use;
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPose(void);
void UninitPose(void);
void UpdatePose(void);
void DrawPose(void);

POSE* GetPose();