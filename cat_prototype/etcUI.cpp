#include "etcUI.h"
#include "texture.h"
#include "sprite.h"
#include "shop.h"
#include "player.h"
#include "camera.h"
#include "cat.h"
#include "inputx.h"
#include "keyboard.h"
#include "stageselect.h"

//���̑���UI�֌W�̃}�N���₱�ꂩ��ǉ����邩���p
#define ETC_MAX 28
#define ETC_SIZE_W 100
#define ETC_SIZE_H 50
//�v���g�^�C�v�錾
///////////////////////�O���[�o���錾
//��@�p
static int time = 0;
static double map_pos = 0;
static double ofset = 1.0;
static int field;
static int stage;
static ETC g_etc[ETC_MAX];

ETC InitDate[] =
{
	//�^�C��UI
	{true,D3DXVECTOR2(SCREEN_WIDTH/2,90),0,0,ETC_SIZE_W,ETC_SIZE_H,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f/2.0f,1.0f,2},
	//���˂����u���b�NUI
	{true,D3DXVECTOR2(SCREEN_WIDTH - 200,50),0,0,ETC_SIZE_W,ETC_SIZE_H,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f/2.0f,1.0f,2},
	//���˂����u���b�N��1�̈�UI
	{true,D3DXVECTOR2(SCREEN_WIDTH - 50,50),0,0,TIME_SIZE_W,TIME_SIZE_H,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f/10.0f,1.0f,10},
	//���˂����u���b�N��10�̈�UI
	{true,D3DXVECTOR2(SCREEN_WIDTH - 100,50),0,0,TIME_SIZE_W,TIME_SIZE_H,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f / 10.0f,1.0f,10},
	//��@�L
	{false,D3DXVECTOR2(SCREEN_WIDTH / 2,40),0,0,60,60,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f / 6.0f,1.0f,6},
	//�v���C���������UI
	{true,D3DXVECTOR2(150,60),0,0,300,100,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),1.0f,1.0f / 4.0f,1.0f,4},
	////
	//������艺�̓X�N���[���������
	////
	//���ԃ|�C���g
	{true,D3DXVECTOR2((CAT_GOLL + DRAW_SIZE)/2,SCREEN_HEIGHT / 2 + 150),0,0,ETC_SIZE_W,ETC_SIZE_H * 2,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f / 2.0f,1.0f,2 },
	//�S�[���\��
	{true,D3DXVECTOR2(CAT_GOLL + DRAW_SIZE,SCREEN_HEIGHT / 2 + 150),0,0,ETC_SIZE_W,ETC_SIZE_H*2,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),1.0f,1.0f / 2.0f,1.0f,2},
	//�x���g�R���x�A31-8-15
	{false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 7, DEFO_SIZE_Y - DRAW_SIZE * 1),0,0,180,60,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f / 10.0f,1.0f / 3.0f,10},
	{false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 10, DEFO_SIZE_Y - DRAW_SIZE * 1),0,0,180,60,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f / 10.0f,1.0f / 3.0f,10},
	{false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 1),0,0,180,60,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f / 10.0f,1.0f / 3.0f,10},
	{false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 25, DEFO_SIZE_Y - DRAW_SIZE * 4),0,0,180,60,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f / 10.0f,1.0f / 3.0f,10},
	{false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 33, DEFO_SIZE_Y - DRAW_SIZE * 0),0,0,180,60,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f / 10.0f,1.0f / 3.0f,10},
	{false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 36, DEFO_SIZE_Y - DRAW_SIZE * 0),0,0,180,60,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f / 10.0f,1.0f / 3.0f,10},
	{false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 39, DEFO_SIZE_Y - DRAW_SIZE * 0),0,0,180,60,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f / 10.0f,1.0f / 3.0f,10},
	{false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 4),0,0,180,60,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f / 10.0f,1.0f / 3.0f,10},
	//�x���g�R���x�A32-16-17
	{false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 22, DEFO_SIZE_Y - DRAW_SIZE * 0),0,0,180,60,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f / 10.0f,1.0f / 3.0f,10},
	{false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 25, DEFO_SIZE_Y - DRAW_SIZE * 0),0,0,180,60,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f / 10.0f,1.0f / 3.0f,10},
	//�x���g�R���x�A33-18-21
	{false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 10, DEFO_SIZE_Y - DRAW_SIZE * 1),0,0,180,60,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f / 10.0f,1.0f / 3.0f,10},
	{false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 1),0,0,180,60,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f / 10.0f,1.0f / 3.0f,10},
	{false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 1, DEFO_SIZE_Y - DRAW_SIZE * 1),0,0,180,60,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f / 10.0f,1.0f / 3.0f,10},
	{false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 4, DEFO_SIZE_Y - DRAW_SIZE * 1),0,0,180,60,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f / 10.0f,1.0f / 3.0f,10},
	//���[�v51-22-25
	{false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 5),0,0,DRAW_SIZE,DRAW_SIZE,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f / 2.0f,1.0f,2},
	{false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 17, DEFO_SIZE_Y - DRAW_SIZE * 1),0,0,DRAW_SIZE,DRAW_SIZE,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f / 2.0f,1.0f,2},
	{false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 6),0,0,DRAW_SIZE,DRAW_SIZE,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f / 2.0f,1.0f,2},
	{false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 51, DEFO_SIZE_Y - DRAW_SIZE * 6),0,0,DRAW_SIZE,DRAW_SIZE,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f / 2.0f,1.0f,2},
	//���[�v52-26-27
	{false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 52, DEFO_SIZE_Y - DRAW_SIZE * 4),0,0,DRAW_SIZE,DRAW_SIZE,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f / 2.0f,1.0f,2},
	{false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 57, DEFO_SIZE_Y - DRAW_SIZE * 8),0,0,DRAW_SIZE,DRAW_SIZE,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f / 2.0f,1.0f,2},
};

HRESULT InitEtc()
{
	field = SetField();
	stage = SetStage();

	//�\���̂̏�����
	for (int i = 0; i < ETC_MAX; i++)
	{
		//��Őݒ肵�����m�������ɓ���
		g_etc[i] = InitDate[i];

		//�e�N�X�`���͌ʂɐݒ肷��
		if (i == 0)
		{
			g_etc[i].texNo = LoadTexture((char*)"data\\texture\\timeUI.png");
		}
		else if (i == 1)
		{
			g_etc[i].texNo = LoadTexture((char*)"data\\texture\\blockscoreUI.png");
		}
		else if (i == 2 || i == 3)
		{
			g_etc[i].texNo = LoadTexture((char*)"data\\texture\\time.png");
		}
		else if (i == 4)
		{
			g_etc[i].texNo = LoadTexture((char*)"data\\texture\\night_cat.png");
		}
		else if (i == 5)
		{
			g_etc[i].texNo = LoadTexture((char*)"data\\texture\\sousaUI.png");
		}
		else if (i == 6 || i == 7)
		{
			g_etc[i].texNo = LoadTexture((char*)"data\\texture\\goal.png");
		}
		else if (i >= 12 && i <= 14 || i >= 16 && i <= 19)
		{
			g_etc[i].texNo = LoadTexture((char*)"data\\texture\\-belt_con.png");
		}
		else if (i >= 22 && i <= 27)
		{
			g_etc[i].texNo = LoadTexture((char*)"data\\texture\\warp.png");
		}
		else
		{
			g_etc[i].texNo = LoadTexture((char*)"data\\texture\\+belt_con.png");
		}
	}
	//
	if (field == 2)
	{
		if (stage == 0)
		{
			for (int i = 8; i < 16; i++)
			{
				g_etc[i].use = true;
			}
		}
		else if (stage == 1)
		{
			for (int i = 16; i < 18; i++)
			{
				g_etc[i].use = true;
			}
		}
		else if (stage == 2)
		{
			for (int i = 18; i < 22; i++)
			{
				g_etc[i].use = true;
			}
		}
	}
	else if (field == 4)
	{
		if (stage == 0)
		{
			for (int i = 22; i < 26; i++)
			{
				g_etc[i].use = true;
			}
		}
		else if (stage == 1)
		{
			for (int i = 26; i < 28; i++)
			{
				g_etc[i].use = true;
			}
		}
	}
	else
	{
		for (int i = 8; i < 28; i++)
		{
			g_etc[i].use = false;
		}
	}

	return S_OK;
}
//�I������
void UnInitEtc()
{

}
void UpdateEtc()
{
	D3DXVECTOR2 basePos = GetBase();
	//�}�b�v�{�^���������ꂽ��
	if (WatchMapFlag() == true)
	{//��ʒ[�ɂȂ�܂ō��W�������Ă���
		if (time > 0)
		{
			time -= 1;
		}

		if (Keyboard_IsKeyDown(KK_D) && time <= 0 || GetThumbLeftX(0) > 0 && time <= 0)
		{
			if (map_pos > -SCREEN_WIDTH * 3 + (-basePos.x))
			{
				//��ʒ[�ɂȂ�����~�߂�
				map_pos -= SCREEN_WIDTH;
				time = 20;
			}
		}
		else if (Keyboard_IsKeyDown(KK_A) && time <= 0 || GetThumbLeftX(0) < 0 && time <= 0)
		{
			if (map_pos < 0 - (basePos.x))
			{
				map_pos += SCREEN_WIDTH;
				time = 20;
			}
		}
		//��@�p��UI�֕ύX
		//�^�C�����e�C�T�c��
		g_etc[0].patern = 1.0f;
		//SHOT��PUSH START�֕ύX
		g_etc[1].patern = 1.0f;
		//��@�p�������
		g_etc[5].patern = 0.0f;
		//�u���b�N��UI�͕\�����Ȃ�
		g_etc[2].use = false;
		g_etc[3].use = false;
		//�e�C�T�c�L���o��������
		g_etc[4].use = true;
		//UI�_��
		
			if (ofset >= 0.25f)
			{
				ofset -= 0.01f;
			}
			else
			{
				ofset += 1.5f;
			}
		//��@�L�A�j���[�V����
		if (g_etc[4].patern <= 10.0f)
		{
			g_etc[4].patern += 0.04f;
		}
		else
		{
			g_etc[4].patern -= 10.0f;
		}

	}
	else
	{
		//�}�b�v�{�^����������ĂȂ��Ȃ�0�ɂ���
		map_pos = 0;
		ofset = 1.0;
		//���ʂ̕\���ɖ߂�
		g_etc[0].patern = 0.0f;
		g_etc[1].patern = 0.0f;
		g_etc[4].patern = 0.0f;
		g_etc[5].patern += 0.002;
		if (g_etc[5].patern > 4.0f || g_etc[5].patern < 1.0f)
		{
			g_etc[5].patern = 1.0f;
		}
		g_etc[2].use = true;
		g_etc[3].use = true;
		g_etc[4].use = false;
	}
	g_etc[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, ofset);
}
//�`�揈��
void DrawEtc()
{
	D3DXVECTOR2 basePos = GetBase();
	g_etc[2].patern = BlockScore() % 10;
	g_etc[3].patern = (BlockScore()/10) % 10;
	for (int i = 0; i < ETC_MAX; i++)
	{
		if (g_etc[i].use == true)
		{		//��ʏ�𓮂��Ȃ�UI�`��
			if (i >= 0 && i <= 5)
			{
				//�e�N�X�`���̃Z�b�g
				GetDeviceContext()->PSSetShaderResources
				(0, 1, GetTexture(g_etc[i].texNo));
				//�X�v���C�g�̕`��
				DrawSpriteColorRotate(
					g_etc[i].pos.x,
					g_etc[i].pos.y,
					g_etc[i].w,
					g_etc[i].h,
					g_etc[i].rot,
					g_etc[i].col,
					g_etc[i].patern,
					g_etc[i].uv_w,//��
					g_etc[i].uv_h,//�c
					g_etc[i].uv_num//������
				);
			}
			else
			{//����UI�`��
				//�e�N�X�`���̃Z�b�g
				GetDeviceContext()->PSSetShaderResources
				(0, 1, GetTexture(g_etc[i].texNo));
				//�X�v���C�g�̕`��
				DrawSpriteColorRotate(
					basePos.x + g_etc[i].pos.x + map_pos,
					basePos.y + g_etc[i].pos.y,
					g_etc[i].w,
					g_etc[i].h,
					g_etc[i].rot,
					g_etc[i].col,
					g_etc[i].patern,
					g_etc[i].uv_w,//��
					g_etc[i].uv_h,//�c
					g_etc[i].uv_num//������
				);
			}
			if (i >= 8 && i <= 21)
			{
				g_etc[i].patern += 0.5f;
				if (g_etc[i].patern >= 30.0f)
				{
					g_etc[i].patern -= 30.0f;
				}
			}
			else if (i >= 22 && i <= 27)
			{
				g_etc[i].patern += 0.02f;
				if (g_etc[i].patern >= 2.0f)
				{
					g_etc[i].patern -= 2.0f;
				}
			}
		}
	}
}
//�\���̂̐擪�|�C���^��Ԃ��@�F���g����悤��
ETC *GetEtc()
{
	return &g_etc[0];
}
