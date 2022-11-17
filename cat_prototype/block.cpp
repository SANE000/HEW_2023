#include "main.h"
#include "block.h"
#include "texture.h"
#include "sprite.h"
#include "camera.h"

//�v���g�^�C�v�錾
void InitStage11();
//==========================================
//�O���[�o���ϐ�
//==========================================

//�n�ʂ⑫��̔���Ɏg��
static BLOCK g_Block[BLOCK_MAX];

HRESULT InitBlock()
{
	//BLOCK�\���̂̏�����
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		//�e�N�X�`�����[�h �摜�̖��O�����悤
		//�u���b�N�ɂ���ăe�N�X�`���̕ύX
		//9,8,7
		//14,13,12,11�͕\�ʂł͖������֕ύX
		if (i >= 7 && i <= 9)
		{
			g_Block[i].texNo = LoadTexture((char*)"data\\texture\\under_soil_block.png");
		}
		else if (i >= 11 && i <= 14)
		{
			g_Block[i].texNo = LoadTexture((char*)"data\\texture\\under_soil_block.png");
		}
		else
		{
			g_Block[i].texNo = LoadTexture((char*)"data\\texture\\grass_block.png");
		}
	}
	//����u���b�N�̐ݒu.��ԍŌ�ɐݒ�
	InitStage11();
	//
	return S_OK;
}
//�I������
void UnInitBlock()
{

}
//�X�V����
void UpdateBlock()
{

}
//�`�揈��
void DrawBlock()
{
	D3DXVECTOR2 basePos = GetBase();

	//�����Ȃ��X�e�[�W�u���b�N
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (g_Block[i].use == true)
		{
			//�e�N�X�`���̃Z�b�g
			GetDeviceContext()->PSSetShaderResources
			(0, 1, GetTexture(g_Block[i].texNo));
			//�X�v���C�g�̕`��
			DrawSpriteColorRotate
			(
			basePos.x + g_Block[i].pos.x,
			basePos.y + g_Block[i].pos.y,
			BASE_DRAW_SIZE,
			DRAW_SIZE,
			g_Block[i].rot,
			g_Block[i].col,
			g_Block[i].Patern,
			3.0f,
			1.0f,
			1
			);
		}
	}	
}
//�\���̂̐擪�|�C���^��Ԃ��@�F���g����悤��
BLOCK *GetBlock()
{
	return &g_Block[0];
}

void InitStage11()
{
	//����Ɋւ��Ă�,�U�[�b�ƕ��ׂ銴���ɂ���
	//DRAW_SIZE������������}�X������Ă���
	//�傫�Ȍ`���Ƃɕ�����Ƃ킩��₷������
	g_Block[0].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 0, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[1].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 1, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[2].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 2, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[3].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 3, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[4].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 4, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[5].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 5, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[6].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 6, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[7].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 7, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[8].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 7, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[9].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 7, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[10].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 7, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[11].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[12].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[13].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[14].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[15].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_Block[16].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 9, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[17].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 10, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[18].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 11, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[19].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[20].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 14, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[21].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 0);
}
