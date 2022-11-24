
#include "main.h"
#include "gimmick_wall.h"
#include "block.h"
#include "texture.h"
#include "sprite.h"
#include "etcUI.h"
#include "shop.h"
#include "texture.h"
#include "sprite.h"
#include "camera.h"
#include "gimmick_wall.h"

//==========================================
//
//==========================================

//g_wall�̃R���W�����I�I�I�I�I�I�I�I

//==========================================
//�O���[�o���ϐ�
//==========================================
//�ǂ̔z��ϐ�
BLOCK g_wall[WALL_MAX];


//���݂̃X�e�[�W������
int stage_gw;

double mappos_gw;


//==========================================
//�v���g�^�C�v�錾
//==========================================
void InitWall_12();


HRESULT InitGimmickWall()
{
	stage_gw = GetStage();
	mappos_gw = GetMapPos();

	for (int i = 0; i < WALL_MAX; i++)
	{
		g_wall[i].use = false;
		g_wall[i].texNo = LoadTexture((char*)"data\\texture\\block.png");
		g_wall[i].Patern = 1.0f;

	}

	switch (stage_gw)
	{
		//1-1	
	case 0:

		break;

		//1-2
	case 1:
		InitWall_12();

		break;

	}
	return S_OK;
}

void UninitGimmickWall()
{
	switch (stage_gw)
	{
		//1-1	
	case 0:

		break;

		//1-2
	case 1:
		for (int i = 0; i < WALL_MAX; i++)
		{
			g_wall[i].use = false;

		}

		break;


	}
}

void UpdateGimmickWall()
{
	BLOCK* pb = GetBlock();

	switch (stage_gw)
	{
		//1-1	
	case 0:

		break;

		//1-2
	case 1:
		//�{�^���������ꂽ��S��false�ɂ���
		if (pb[54].button == false)
		{
			g_wall[0].use = false;
			g_wall[1].use = false;
			g_wall[2].use = false;
			g_wall[3].use = false;
			g_wall[4].use = false;
			g_wall[5].use = false;
			g_wall[6].use = false;
			g_wall[7].use = false;

		}

		break;

	}
}

void DrawGimmickWall()
{
	D3DXVECTOR2 basePos_gw = GetBase();

	switch (stage_gw)
	{
		//1-1	
	case 0:

		break;

		//1-2
	case 1:

		for (int i = 0; i < WALL_MAX; i++)
		{
			if (g_wall[i].use == true)
			{
				//�e�N�X�`���̃Z�b�g
				GetDeviceContext()->PSSetShaderResources
				(0, 1, GetTexture(g_wall[i].texNo));
				//�X�v���C�g�̕`��
				DrawSpriteColorRotate
				(
					mappos_gw + basePos_gw.x + g_wall[i].pos.x,
					basePos_gw.y + g_wall[i].pos.y,
					DRAW_SIZE,
					DRAW_SIZE,
					g_wall[i].rot,
					g_wall[i].col,
					g_wall[i].Patern,
					1.0f / 7.0f,//��
					1.0f,//�c
					7//������
				);

			}
			else
			{
				break;
			}

		}



		break;

	}
}

BLOCK* GetGimmickWall()
{
	return g_wall;
}


void InitWall_12()
{
	g_wall[0].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_wall[1].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_wall[2].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_wall[3].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_wall[4].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_wall[5].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 6);
	g_wall[6].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_wall[7].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 8);

	g_wall[0].use = true;
	g_wall[1].use = true;
	g_wall[2].use = true;
	g_wall[3].use = true;
	g_wall[4].use = true;
	g_wall[5].use = true;
	g_wall[6].use = true;
	g_wall[7].use = true;

}