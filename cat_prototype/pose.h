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
// プロトタイプ宣言
//*****************************************************************************
void InitPose(void);
void UninitPose(void);
void UpdatePose(void);
void DrawPose(void);

POSE* GetPose();