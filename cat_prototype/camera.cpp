/*==============================================================================

   �J�������� [camera.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "camera.h"
#include "main.h"
#include "input.h"
#include "cat.h"
#include "block.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CAMERA_SPEED 3
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static CAMERA_2D	g_Camera;	// �J�����p�f�[�^
static D3DXVECTOR2  g_Base;		// �}�b�v�S�̂̐e���W

//=============================================================================
// ����������
//=============================================================================
void InitCamera(void)
{
	g_Camera.pos = D3DXVECTOR2(0.0f, 0.0f);
	g_Camera.move = false;
	g_Base = D3DXVECTOR2(0.0f, 0.0f);


}

void UninitCamera(void)
{

}

void UpdateCamera(void)
{
	//�J�����̍��W�𔽓]�������̂��x�[�X���W�ɂȂ�
	g_Base = (g_Camera.pos * -1);
	CAT* pCat = GetCat();
	PREVIEW_BLOCK* pPreviewBlock = GetPreviewBlock();
	PLAYER* pplayer = GetPlayer();


	//���ɓ���
	if (pCat->pos.x >= g_Camera.pos.x + SCREEN_WIDTH - 20) {
		g_Camera.move  = true;
	}
	if (g_Camera.move == true)
	{	 
		g_Camera.pos.x += 10;
	  //pPreviewBlock->pos.x += 10;
	    pplayer->pos.x += 10;
		if (pCat->pos.x - 10 <= g_Camera.pos.x) {
		 pPreviewBlock->pos.x = g_Camera.pos.x;
		  pplayer->pos.x = g_Camera.pos.x;
			g_Camera.move = false;
		}
	}

	if (pCat->pos.x <= g_Camera.pos.x - 20) {
		g_Camera.pos.x = 0;
	}

	////�p�b�Ɛ؂�ւ��
	////if (pCat->pos.x >= g_Camera.pos.x + SCREEN_WIDTH - 20) {
	////	�J�����𓮂���
	////	g_Camera.pos.x += 960;
	////	pPreviewBlock->pos.x += 960;
	////	pplayer->pos.x += 960;
	////}
	 

	if (GetKeyboardPress(DIK_V))
	{
			g_Camera.pos.x++;
	}
	if (GetKeyboardPress(DIK_C))
	{
		g_Camera.pos.x--;
	}
}


void DrawCamera(void)
{

}

CAMERA_2D* GetCamera(void)
{
	return &g_Camera;
}

D3DXVECTOR2 GetBase(void)
{
	return g_Base;
}
