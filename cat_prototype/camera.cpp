/*==============================================================================

   �J�������� [camera.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "camera.h"
#include "main.h"
#include "inputx.h"
#include "keyboard.h"
#include "cat.h"
#include "blockpreview.h"
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
static int			Nowpos;

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
	//�L����ʂ̉E���ɂ�������
	if (pCat->pos.x >= g_Camera.pos.x + SCREEN_WIDTH - 20) {
	//���[�u�t���O��turu�ɂ���
		g_Camera.move = true;
	}
	//���[�u�t���O��true�Ȃ�
	if (g_Camera.move == true)
	{//���̑��x�ňړ�
		g_Camera.pos.x += 10;
		//pPreviewBlock->pos.x += 10;
		if (pCat->pos.x - 10 <= g_Camera.pos.x) {
			//�L�����[�ɂ�����ړ����~�߈ʒu�␳
			pPreviewBlock->pos.x = g_Camera.pos.x;
			g_Camera.move = false;
			Nowpos = g_Camera.pos.x;
		}
	}
	//�����ɍs�����珉�����
	if (pCat->pos.x <= g_Camera.pos.x - 20) {
		g_Camera.pos.x = 0;
	}

	//���[�u�t���O��false / pos��9601�̔{���ȊO
	if (g_Camera.move == false && Nowpos % SCREEN_WIDTH != 0)
	{//��ʂɍ��킹�ʒu�␳
		g_Camera.pos.x = g_Camera.Oldpos.x + SCREEN_WIDTH;
		Nowpos = g_Camera.pos.x;
		pplayer->pos.x = g_Camera.Oldpos.x + SCREEN_WIDTH - 30;
	}

	//���[�u�t���O��false / pos��9601�̔{��
	if (g_Camera.move == false && Nowpos % SCREEN_WIDTH == 0)
	{
		//Oldpos�ɍ��̈ʒu������
		g_Camera.Oldpos = g_Camera.pos;
	}


	if (Keyboard_IsKeyDown(KK_V))
	{
		g_Camera.pos.x++;
	}
	if (Keyboard_IsKeyDown(KK_C))
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
