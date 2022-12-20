#include "main.h"
#include "block.h"
#include "shop.h"
#include "texture.h"
#include "sprite.h"
#include "camera.h"
#include "cat.h"
#include "gimmick_wall.h"
#include "stageselect.h"
#include "inputx.h"
#include "keyboard.h"
#include "result.h"

//�v���g�^�C�v�錾
void InitStage11();
void InitStage12();
void InitStage13();
void InitStage21();
void InitStage22();
void InitStage23();
void InitStage31();
void InitStage32();
void InitStage33();
void InitStage41();
void InitStage42();
void InitStage43();
void InitStage51();
void InitStage52();

//==========================================
//�O���[�o���ϐ�
//==========================================
//��@�p
static int time = 0;
static double map_pos = 0;
//�n�ʂ⑫��̔���Ɏg��
static BLOCK g_Block[BLOCK_MAX];
//==========================================
//�X�e�[�W�I�ԕϐ�
//==========================================

//�X�e�[�W�I���e�X�g�p�Ȃ̂Ŏ蓮��Init�őI��ł܂��B
//�X�e�[�W�I����ʂ��ł��������������Ă�������
static int clear;
static int field;
static int stage;
//world = 0�Ȃ��ʂ�
//stage = 0�Ȃ�X�e�[�W1
//���킹��1-1���I�΂��d�g��

HRESULT InitBlock()
{
	/////////////�����ŃX�e�[�W�Z���N�g�̃Z�b�^�[�Q�b�g�����炢���邩��
	field = SetField();
	stage = SetStage();
	clear = SetClear();
	//BLOCK�\���̂̏�����
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		g_Block[i].use = true;
		//�Z���T�[�œ������̃t���O�����Z�b�g
		g_Block[i].moveflug = false;
		//�e�N�X�`�����[�h �摜�̖��O�����悤
		g_Block[i].texNo = LoadTexture((char*)"data\\texture\\block.png");
		//�u���b�N�̃��Z�b�g
		if (field == 0)
		{
			g_Block[i].Patern = 0.0f;
		}
		else if (field == 1 || field == 3)
		{
			g_Block[i].Patern = 12.0f;
		}
		else if (field == 2)
		{
			g_Block[i].Patern = 24.0f;
		}
		else if (field == 4)
		{
			g_Block[i].Patern = 30.0f;
		}
	}
	////////////////////////////////////////////////////////////////////
	//�X�e�[�W�e�X�g
	//�����Ă�����switch�\���ł����Ă���������
	if (field == 0)
	{
		if (stage == 0 && clear >= 0)
		{
			//����u���b�N�̐ݒu.��ԍŌ�ɐݒ�
			InitStage11();
		}
		else if (stage == 1 && clear >= 1)
		{
			InitStage12();
			InitGimmickWall();
		}
		else if (stage == 2 && clear >= 2)
		{
			InitStage13();
			InitGimmickWall();
		}
	}
	else if (field == 1)
	{
		if (stage == 0 && clear >= 3)
		{
			InitStage21();
		}
		else if (stage == 1 && clear >= 4)
		{
			InitStage22();
		}
		else if (stage == 2 && clear >= 5)
		{
			InitStage23();
			InitGimmickWall();
		}
	}
	else if (field == 2)
	{
		if (stage == 0 && clear >= 6)
		{
			InitStage31();
			InitGimmickWall();
		}
		else if (stage == 1 && clear >= 7)
		{
			InitStage32();
			InitGimmickWall();
		}
		else if (stage == 2 && clear >= 8)
		{
			InitStage33();
			InitGimmickWall();
		}
	}
	else if (field == 3)
	{
		if (stage == 0 && clear >= 9)
		{
			InitStage41();
		}
		else if (stage == 1 && clear >= 10)
		{
			InitStage42();
		}
		else if (stage == 2 && clear >= 11)
		{
			InitStage43();
			InitGimmickWall();
		}
	}
	else if (field == 4)
	{
		if (stage == 0 && clear >= 12)
		{
			InitStage51();
			InitGimmickWall();
		}
		else if (stage == 1 && clear >= 13)
		{
			InitStage52();
		}
		//else if (stage == 2 && clear >= 14)
		//{
		//	InitStage53();
		//	InitGimmickWall();
		//}
	}
	else
	{
		//�Ⴄ���[���h�̂Ƃ��p
		exit(1);
	}
	//
	return S_OK;
}
//�I������
void UnInitBlock()
{
	UninitGimmickWall();
}
//�X�V����
void UpdateBlock()
{
	D3DXVECTOR2 basePos = GetBase();
	CAT* pCat = GetCat();
	//�}�b�v�{�^���������ꂽ��
	if (WatchMapFlag() == true)
	{//��ʒ[�ɂȂ�܂ō��W�������Ă���
		if (time > 0)
		{
			time -= 1;
		}
		//�����X�N���[������,������₷���悤�Ɏ����œ�������悤�ɂ���
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
	}
	else
	{
		//�}�b�v�{�^����������ĂȂ��Ȃ�0�ɂ���
		map_pos = 0;
	}
	//�������
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		//�܂��ړ��������`�F�b�N//�c��
		if (g_Block[i].Patern == 20.0f)
		{
			//��ʏ�܂Œ�������X�s�[�h���t�ɂ���
			if (g_Block[i].pos.y < (DRAW_SIZE / 2.0))
			{
				g_Block[i].pos.y = (DRAW_SIZE / 2.0);
				g_Block[i].Speed.y = 1.0f;
			}
			//��ʉ��܂Œ�������X�s�[�h���t�ɂ���
			if (g_Block[i].pos.y > (SCREEN_HEIGHT - DRAW_SIZE / 2.0))
			{
				g_Block[i].pos.y = (SCREEN_HEIGHT - DRAW_SIZE / 2.0);
				g_Block[i].Speed.y = -1.0f;
			}
			//�����̂ō��W�̍X�V
			g_Block[i].pos += g_Block[i].Speed;
		}
		//�܂��ړ��������`�F�b�N//����
		if (g_Block[i].Patern == 21.0f)
		{
			//�E��5�܂Œ�������X�s�[�h���t�ɂ���
			if (g_Block[i].pos.x > g_Block[i].limitmax)
			{
				g_Block[i].pos.x = g_Block[i].limitmax;
				g_Block[i].Speed.x = -1.0f;
			}
			//����5�܂Œ�������X�s�[�h���t�ɂ���
			if (g_Block[i].pos.x < g_Block[i].limitmin)
			{
				g_Block[i].pos.x = g_Block[i].limitmin;
				g_Block[i].Speed.x = 1.0f;
			}
			//�����̂ō��W�̍X�V
			g_Block[i].pos += g_Block[i].Speed;
		}
		//�L���߂��ɗ����瓮�����
		if (g_Block[i].Patern == 25.0f || g_Block[i].Patern == 32.0f)
		{
			//�L���߂��ɂ��ē����ĂȂ����`�F�b�N
			if (pCat->pos.x > g_Block[i].pos.x - (DRAW_SIZE * 3) && g_Block[i].moveflug == false)
			{
				//��񂾂��Ă�
				g_Block[i].Speed.y = GRAV*2;
				g_Block[i].moveflug = true;
			}
			//���E�l�܂Œ�������~�߂�
			if (g_Block[i].pos.y > g_Block[i].limitmax)
			{
				g_Block[i].pos.y = g_Block[i].limitmax;
				g_Block[i].Speed.y = 0;
			}
			//�����̂ō��W�̍X�V
			g_Block[i].pos += g_Block[i].Speed;
		}
		//���E�l�ɂȂ�����߂��Ă�����
		if (g_Block[i].Patern == 28.0f)
		{
			//��ʊO�̌��E�l�܂ł�������(�e�Őݒ肷��)
			if (g_Block[i].pos.y < g_Block[i].limitmax)
			{
				//�����̌��E�l�܂Ŗ߂�
				g_Block[i].pos.y = g_Block[i].limitmin;
			}
			//�����̂ō��W�̍X�V
			g_Block[i].pos += g_Block[i].Speed;
		}
	}
	//�{�^������������̏���
	UpdateGimmickWall();
}
//�`�揈��
void DrawBlock()
{
	D3DXVECTOR2 basePos = GetBase();
	CAT* c = GetCat();

	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (field == 0)
		{
			if (stage == 1)
			{
				if (i == 50)
				{
					//�{�^���u���b�N
					if (g_Block[i].button == true)
					{

						g_Block[i].Patern = 3.0f;
					}
					else
					{
						g_Block[i].Patern = 4.0f;
					}
				}
			}
			else if (stage == 2)
			{
				if (i == 52)
				{
					//�{�^���u���b�N
					if (g_Block[i].button == true)
					{

						g_Block[i].Patern = 3.0f;
					}
					else
					{
						g_Block[i].Patern = 4.0f;
					}
				}
			}
		}
		else if (field == 1)
		{
			//�w�i�̃T�{�e���ƃu���b�N�̃T�{�e���𕪂���₷�����邽�߂̔��]����
			if (g_Block[i].Patern >= 15.0f && g_Block[i].Patern <= 16.9f)
			{
				g_Block[i].Patern += 0.05f;
			}
			else if (g_Block[i].Patern >= 16.9f && g_Block[i].Patern < 17.0f)
			{
				g_Block[i].Patern = 15.0f;
			}
			//�{�^��
			if (stage == 2)
			{
				//��
				if (i == 7)
				{
					//�{�^���u���b�N
					if (g_Block[i].button == true)
					{

						g_Block[i].Patern = 5.0f;
					}
					else
					{
						g_Block[i].Patern = 6.0f;
					}
				}
				else if (i == 9)//��
				{
					//�{�^���u���b�N
					if (g_Block[i].button == true)
					{

						g_Block[i].Patern = 3.0f;
					}
					else
					{
						g_Block[i].Patern = 4.0f;
					}
				}
			}
		}
		else if (field == 2)
		{
			//�{�^��
			if (stage == 0)
			{
				if (i == 66)//��
				{
					//�{�^���u���b�N
					if (g_Block[i].button == true)
					{

						g_Block[i].Patern = 3.0f;
					}
					else
					{
						g_Block[i].Patern = 4.0f;
					}
				}
			}
			else if (stage == 1)
			{
				if (i == 25)//��
				{
					//�{�^���u���b�N
					if (g_Block[i].button == true)
					{

						g_Block[i].Patern = 3.0f;
					}
					else
					{
						g_Block[i].Patern = 4.0f;
					}
				}
				else if (i == 62)//��
				{
					//�{�^���u���b�N
					if (g_Block[i].button == true)
					{

						g_Block[i].Patern = 3.0f;
					}
					else
					{
						g_Block[i].Patern = 4.0f;
					}
				}
			}
			else if (stage == 2)
			{
				//��
				if (i == 28)
				{
					//�{�^���u���b�N
					if (g_Block[i].button == true)
					{

						g_Block[i].Patern = 5.0f;
					}
					else
					{
						g_Block[i].Patern = 6.0f;
					}
				}
				else if (i == 30)//��
				{
					//�{�^���u���b�N
					if (g_Block[i].button == true)
					{

						g_Block[i].Patern = 3.0f;
					}
					else
					{
						g_Block[i].Patern = 4.0f;
					}
				}
			}
		}
		else if (field == 3)
		{
			//�{�^��
			if (stage == 2)
			{
				if (i == 68)//��
				{
					//�{�^���u���b�N
					if (g_Block[i].button == true)
					{

						g_Block[i].Patern = 5.0f;
					}
					else
					{
						g_Block[i].Patern = 6.0f;
					}
				}
			}
		}
		else if (field == 4)
		{
			//�{�^��
			if (stage == 0)
			{
				if (i == 83)//��
				{
					//�{�^���u���b�N
					if (g_Block[i].button == true)
					{

						g_Block[i].Patern = 3.0f;
					}
					else
					{
						g_Block[i].Patern = 4.0f;
					}
				}
			}
		}
		if (WatchMapFlag() == false)
		{
			//�v���C���͔L���牓�����͕̂`�悵�Ȃ�
			if (g_Block[i].pos.x < (c->pos.x - SCREEN_WIDTH) || g_Block[i].pos.x >(c->pos.x + SCREEN_WIDTH))
			{
				continue;
			}
		}
		if (g_Block[i].draw_use == true)
		{
			//�e�N�X�`���̃Z�b�g
			GetDeviceContext()->PSSetShaderResources
			(0, 1, GetTexture(g_Block[i].texNo));
			//�X�v���C�g�̕`��
			DrawSpriteColorRotate
			(
				map_pos + basePos.x + g_Block[i].pos.x,
				basePos.y + g_Block[i].pos.y,
				DRAW_SIZE,
				DRAW_SIZE,
				g_Block[i].rot,
				g_Block[i].col,
				g_Block[i].Patern,
				1.0f / 12.0f,//��
				1.0f / 3.0f,//�c
				12//���̑�����
			);
		}
		DrawGimmickWall();
	}
}
//�\���̂̐擪�|�C���^��Ԃ��@�F���g����悤��
BLOCK *GetBlock()
{
	return &g_Block[0];
}

double GetMapPos()
{
	return map_pos;
}

int GetStage()
{
	return stage;
}

void InitStage52()
{
	//����Ɋւ��Ă�,�U�[�b�ƕ��ׂ銴���ɂ��Ă݂܂���
	//���� �� 16 �}�X * �c 9 �}�X�@�Ł@����Ă܂�
	// X�����@��ʍ��[����E�� * ����(�}�X)
	// Y�����@��ʉ��[������ * ����(�}�X)
	//�傫�Ȍ`���Ƃɕ�����Ƃ킩��₷������

	for (int i = 0; i < BLOCK_MAX; i++)
	{
		//覐�
		if (i >= 6 && i <= 8 || i >= 35 && i <= 37)
		{
			g_Block[i].Patern = 32.0f;
			g_Block[i].Speed.y = 0;
			//���̍ő�l������
			g_Block[i].limitmax = (SCREEN_HEIGHT - (DRAW_SIZE / 2.0));
		}
		//�㉺�ɓ������
		if (i >= 52 && i <= 54 || i >= 65 && i <= 67)
		{
			g_Block[i].Patern = 20.0f;
			g_Block[i].Speed.y = 1.0f;
		}
		//�]��̃u���b�N
		if (i >= 84 && i < BLOCK_MAX)
		{
			//�g��Ȃ��u���b�N�͓����蔻��͎��Ȃ�
			g_Block[i].use = false;
			g_Block[i].draw_use = false;
		}
	}
	g_Block[0].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 0, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[1].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 1, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[2].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 2, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[3].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 3, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[4].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 4, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[5].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 5, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//覐�
	g_Block[6].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 9);
	g_Block[7].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 10, DEFO_SIZE_Y - DRAW_SIZE * 9);
	g_Block[8].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 11, DEFO_SIZE_Y - DRAW_SIZE * 9);
	//�������畁��
	g_Block[9].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 12, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[10].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[11].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 14, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[12].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[13].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[14].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 6);
	g_Block[15].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[16].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 8);

	g_Block[17].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 16, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[18].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 17, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[19].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 16, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[20].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 17, DEFO_SIZE_Y - DRAW_SIZE * 5);

	g_Block[21].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 18, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[22].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 19, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[23].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 20, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[24].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 18, DEFO_SIZE_Y - DRAW_SIZE * 5);
	//���̏�ɓG
	g_Block[25].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 19, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[26].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 20, DEFO_SIZE_Y - DRAW_SIZE * 5);

	g_Block[27].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 21, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[28].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[29].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 25, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[30].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 27, DEFO_SIZE_Y - DRAW_SIZE * 5);

	g_Block[31].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 28, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[32].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 29, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[33].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 30, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[34].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 31, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//覐�
	g_Block[35].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 22, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[36].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 24, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[37].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 26, DEFO_SIZE_Y - DRAW_SIZE * 5);
	//�������畁��
	g_Block[38].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 32, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[39].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 33, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[40].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 34, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[41].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 35, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[42].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 36, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[43].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 37, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[44].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 38, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[45].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 38, DEFO_SIZE_Y - DRAW_SIZE * 1);

	g_Block[46].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 39, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[47].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 39, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[48].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 39, DEFO_SIZE_Y - DRAW_SIZE * 2);

	g_Block[49].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 40, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[50].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 40, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[51].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 41, DEFO_SIZE_Y - DRAW_SIZE * 2);
	//�㉺�ɓ������
	g_Block[52].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 42, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[53].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 43, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[54].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 44, DEFO_SIZE_Y - DRAW_SIZE * 1);
	//�������畁��
	g_Block[55].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[56].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 46, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_Block[57].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[58].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 46, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[59].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[60].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 46, DEFO_SIZE_Y - DRAW_SIZE * 2);

	g_Block[61].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[62].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 46, DEFO_SIZE_Y - DRAW_SIZE * 1);

	g_Block[63].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[64].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 46, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//�㉺�ɓ������
	g_Block[65].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 47, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[66].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 48, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[67].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 49, DEFO_SIZE_Y - DRAW_SIZE * 7);
	//�������畁��
	g_Block[68].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 50, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[69].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 51, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[70].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 52, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//���̏�ɓG
	g_Block[71].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 53, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[72].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 50, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[73].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 51, DEFO_SIZE_Y - DRAW_SIZE * 3);
	//���[�v�@�B
	g_Block[74].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 52, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[74].Patern = 31.0f;
	g_Block[74].warpos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 57, DEFO_SIZE_Y - DRAW_SIZE * 9);

	g_Block[75].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 53, DEFO_SIZE_Y - DRAW_SIZE * 3);
	//����
	g_Block[76].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 50, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[77].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 51, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[78].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 52, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[79].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 53, DEFO_SIZE_Y - DRAW_SIZE * 7);

	g_Block[80].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 61, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[81].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 62, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[82].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 63, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//���[�v�@�B
	g_Block[83].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 57, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[83].Patern = 31.0f;
	g_Block[83].warpos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 52, DEFO_SIZE_Y - DRAW_SIZE * 5);
}

void InitStage51()
{
	//����Ɋւ��Ă�,�U�[�b�ƕ��ׂ銴���ɂ��Ă݂܂���
	//���� �� 16 �}�X * �c 9 �}�X�@�Ł@����Ă܂�
	// X�����@��ʍ��[����E�� * ����(�}�X)
	// Y�����@��ʉ��[������ * ����(�}�X)
	//�傫�Ȍ`���Ƃɕ�����Ƃ킩��₷������

	for (int i = 0; i < BLOCK_MAX; i++)
	{
		//�]��̃u���b�N
		if (i >= 86 && i < BLOCK_MAX)
		{
			//�g��Ȃ��u���b�N�͓����蔻��͎��Ȃ�
			g_Block[i].use = false;
			g_Block[i].draw_use = false;
		}
	}
	g_Block[0].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 0, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[1].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 1, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[2].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 2, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[3].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 3, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[4].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 4, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[5].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 5, DEFO_SIZE_Y - DRAW_SIZE * 0);
	
	g_Block[6].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 6, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[7].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 7, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[8].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[9].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 6, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[10].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 7, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[11].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 1);

	g_Block[12].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 9, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[13].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 10, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[14].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 11, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[15].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 9, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[16].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 10, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[17].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 11, DEFO_SIZE_Y - DRAW_SIZE * 1);

	g_Block[18].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 9, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[19].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 10, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[20].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 11, DEFO_SIZE_Y - DRAW_SIZE * 2);

	g_Block[21].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 12, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[22].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[23].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 14, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[24].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 12, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[25].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[26].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 14, DEFO_SIZE_Y - DRAW_SIZE * 1);

	g_Block[27].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 12, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[28].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[29].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 14, DEFO_SIZE_Y - DRAW_SIZE * 2);

	g_Block[30].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 12, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[31].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[32].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 14, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[33].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 12, DEFO_SIZE_Y - DRAW_SIZE * 4);
	//���������[�v�@�B
	g_Block[34].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[34].Patern = 31.0f;
	//���[�v����W��ݒ�
	g_Block[34].warpos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 17, DEFO_SIZE_Y - DRAW_SIZE * 2);

	g_Block[35].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 14, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_Block[36].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[37].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[38].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 2);

	g_Block[39].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[40].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[41].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 5);

	g_Block[42].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 6);
	g_Block[43].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[44].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 8);
	//����������
	g_Block[45].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 16, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//���[�v�@�B
	g_Block[46].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 17, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[46].Patern = 31.0f;
	//���[�v����W��ݒ�
	g_Block[46].warpos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 6);

	g_Block[47].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 18, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[48].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 16, DEFO_SIZE_Y - DRAW_SIZE * 3);
	//���̏�ɓG
	g_Block[49].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 17, DEFO_SIZE_Y - DRAW_SIZE * 3);
	//�������畁��
	g_Block[50].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 19, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[51].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 20, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//�o�l
	g_Block[52].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 21, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[52].Patern = 9.0f;
	//�o�l
	g_Block[53].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 26, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[53].Patern = 9.0f;
	//�������畁��
	g_Block[54].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 31, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//��������O��
	g_Block[55].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 32, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[56].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 33, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[57].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 34, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[58].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 35, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[59].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 36, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[60].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 37, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[61].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 37, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[62].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 37, DEFO_SIZE_Y - DRAW_SIZE * 2);

	g_Block[63].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 38, DEFO_SIZE_Y - DRAW_SIZE * 2);
	//���̏�ɓG
	g_Block[64].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 39, DEFO_SIZE_Y - DRAW_SIZE * 2);

	g_Block[65].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 40, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[66].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 41, DEFO_SIZE_Y - DRAW_SIZE * 2);
	
	g_Block[67].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 42, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[68].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 43, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[69].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 44, DEFO_SIZE_Y - DRAW_SIZE * 2);

	g_Block[70].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 42, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[71].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 43, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[72].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 44, DEFO_SIZE_Y - DRAW_SIZE * 5);

	g_Block[73].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[74].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[75].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 4);
	//���[�v�@�B
	g_Block[76].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[76].Patern = 31.0f;
	//���[�v����W��ݒ�
	g_Block[76].warpos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 51, DEFO_SIZE_Y - DRAW_SIZE * 7);
	//�������畁��
	g_Block[77].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 46, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[78].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 47, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[79].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 47, DEFO_SIZE_Y - DRAW_SIZE * 6);
	g_Block[80].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 47, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[81].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 47, DEFO_SIZE_Y - DRAW_SIZE * 8);
	//���[�v�@�B
	g_Block[82].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 51, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[82].Patern = 31.0f;
	//���[�v����W��ݒ�
	g_Block[82].warpos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 7);
	//�{�^��
	g_Block[83].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 56, DEFO_SIZE_Y - DRAW_SIZE * 6);
	g_Block[83].button = true;
	g_Block[84].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 62, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[85].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 63, DEFO_SIZE_Y - DRAW_SIZE * 0);
}

void InitStage43()
{
	//����Ɋւ��Ă�,�U�[�b�ƕ��ׂ銴���ɂ��Ă݂܂���
	//���� �� 16 �}�X * �c 9 �}�X�@�Ł@����Ă܂�
	// X�����@��ʍ��[����E�� * ����(�}�X)
	// Y�����@��ʉ��[������ * ����(�}�X)
	//�傫�Ȍ`���Ƃɕ�����Ƃ킩��₷������

	for (int i = 0; i < BLOCK_MAX; i++)
	{
		//�T���S
		if (i >= 6 && i <= 23)
		{
			g_Block[i].Patern = 26.0f;
		}

		if (i >= 73 && i <= 74 || i >= 80 && i <= 85)
		{
			//�C�A�������u���b�N
			g_Block[i].Patern = 27.0f;
		}

		//�C�Alimitmin,max���炵�Ĕz�u�Ń����_�������o
		if (i >= 42 && i <= 50 || i >= 75 && i <= 76 || i >= 86 && i <= 88)
		{
			g_Block[i].Patern = 28.0f;
			//min
			if (i >= 42 && i <= 44)
			{
				g_Block[i].limitmin = SCREEN_HEIGHT + (DRAW_SIZE / 2);
			}
			else if (i >= 45 && i <= 47)
			{
				g_Block[i].limitmin = SCREEN_HEIGHT + ((DRAW_SIZE / 2) * 3);
			}
			else if (i >= 48 && i <= 50)
			{
				g_Block[i].limitmin = SCREEN_HEIGHT + ((DRAW_SIZE / 2) * 5);
			}
			else
			{
				g_Block[i].limitmin = SCREEN_HEIGHT - (DRAW_SIZE / 2.0);
			}
			//max
			if (i >= 75 && i <= 76)
			{
				g_Block[i].limitmax = DEFO_SIZE_Y - DRAW_SIZE * 3;
			}
			else
			{
				g_Block[i].limitmax = -(DRAW_SIZE / 2);
			}
			//�X�s�[�h�͈ꗥ����
			g_Block[i].Speed.y = -(GRAV / 4);
		}

		if (i >= 54 && i <= 56)
		{
			//�C��
			g_Block[i].Patern = 29.0f;
		}

		//�]��̃u���b�N
		if (i >= 89 && i < BLOCK_MAX)
		{
			//�g��Ȃ��u���b�N�͓����蔻��͎��Ȃ�
			g_Block[i].use = false;
			g_Block[i].draw_use = false;
		}
	}
	g_Block[0].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 0, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[1].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 1, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[2].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 2, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[3].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 3, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[4].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 4, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[5].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 5, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//�T���S
	g_Block[6].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 0, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[7].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 1, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[8].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 2, DEFO_SIZE_Y - DRAW_SIZE * 1);

	g_Block[9].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 3, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[10].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 4, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[11].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 5, DEFO_SIZE_Y - DRAW_SIZE * 1);

	g_Block[12].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 0, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[13].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 1, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[14].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 2, DEFO_SIZE_Y - DRAW_SIZE * 2);

	g_Block[15].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 3, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[16].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 4, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[17].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 5, DEFO_SIZE_Y - DRAW_SIZE * 2);

	g_Block[18].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 3, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[19].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 4, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[20].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 5, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[21].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 6, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[22].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 7, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[23].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 4);
	//�������畁��
	g_Block[24].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 6, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[25].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 7, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//���̏�ɃT��
	g_Block[26].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[27].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 9, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[28].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 10, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[29].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 11, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[30].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 12, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[31].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[32].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 14, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[33].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 12, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[34].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[35].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 14, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_Block[36].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[37].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 16, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[38].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 17, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[39].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[40].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 16, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[41].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 17, DEFO_SIZE_Y - DRAW_SIZE * 4);
	//�C�A
	g_Block[42].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 18, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[43].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 19, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[44].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 20, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[45].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 21, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[46].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 22, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[47].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[48].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 24, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[49].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 25, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[50].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 26, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//�������畁��
	g_Block[51].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 27, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[52].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 28, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[53].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 29, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//���C��
	g_Block[54].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 27, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[55].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 28, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[56].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 29, DEFO_SIZE_Y - DRAW_SIZE * 1);
	//�������畁��
	g_Block[57].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 30, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[58].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 31, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//��������O��
	g_Block[59].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 32, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[60].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 33, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[61].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 34, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[62].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 35, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[63].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 36, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[64].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 37, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[65].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 38, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[66].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 36, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[67].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 37, DEFO_SIZE_Y - DRAW_SIZE * 3);
	//�ԃ{�^��
	g_Block[68].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 37, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[68].button = true;

	g_Block[69].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 39, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[70].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 40, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[71].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 41, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[72].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 42, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//�C�A������
	g_Block[73].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 43, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[74].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 44, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//�C�Amax�Z�߂������񔭐��G���x�[�^�[�̑���
	g_Block[75].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 43, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[76].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 44, DEFO_SIZE_Y - DRAW_SIZE * 1);
	//�C��
	g_Block[77].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 42, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[78].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 41, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[79].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 40, DEFO_SIZE_Y - DRAW_SIZE * 3);
	//�C�A������
	g_Block[80].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 49, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[81].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 53, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[82].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 57, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[83].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 61, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[84].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 62, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[85].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 63, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//�C�A
	g_Block[86].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 49, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[87].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 53, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[88].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 57, DEFO_SIZE_Y - DRAW_SIZE * 1);
}

void InitStage42()
{
	//����Ɋւ��Ă�,�U�[�b�ƕ��ׂ銴���ɂ��Ă݂܂���
	//���� �� 16 �}�X * �c 9 �}�X�@�Ł@����Ă܂�
	// X�����@��ʍ��[����E�� * ����(�}�X)
	// Y�����@��ʉ��[������ * ����(�}�X)
	//�傫�Ȍ`���Ƃɕ�����Ƃ킩��₷������

	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (i >= 10 && i <= 11 || i >= 16 && i <= 17 || 
			i >= 58 && i <= 60 || i == 63)
		{
			//�������̊C���u���b�N(�A�j���������̂Œ��S�_�C�ɂ��Ȃ��Ă悵)
			g_Block[i].Patern = 29.0f;
		}
		//�T���S
		if (i >= 54 && i <= 57)
		{
			g_Block[i].Patern = 26.0f;
		}
		//�]��̃u���b�N
		if (i >= 69 && i < BLOCK_MAX)
		{
			//�g��Ȃ��u���b�N�͓����蔻��͎��Ȃ�
			g_Block[i].use = false;
			g_Block[i].draw_use = false;
		}
	}
	g_Block[0].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 0, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[1].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 1, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[2].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 2, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[3].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 3, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[4].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 4, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[5].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 5, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[6].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 6, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[7].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 7, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_Block[8].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[9].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 9, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//�C��
	g_Block[10].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[11].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 9, DEFO_SIZE_Y - DRAW_SIZE * 1);
	//�������畁��
	g_Block[12].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 10, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[13].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 11, DEFO_SIZE_Y - DRAW_SIZE * 2);

	g_Block[14].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 12, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[15].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//�C��
	g_Block[16].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 12, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[17].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 1);
	//�������畁��
	g_Block[18].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 14, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[19].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 2);

	g_Block[20].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 16, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[21].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 17, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[22].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 18, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[23].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 19, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[24].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 20, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[25].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 20, DEFO_SIZE_Y - DRAW_SIZE * 6);
	//���̏�ɓG
	g_Block[26].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 21, DEFO_SIZE_Y - DRAW_SIZE * 6);

	g_Block[27].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 24, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[28].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 25, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[29].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 26, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[30].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 27, DEFO_SIZE_Y - DRAW_SIZE * 5);

	g_Block[31].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 29, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[32].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 30, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[33].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 31, DEFO_SIZE_Y - DRAW_SIZE * 2);

	g_Block[34].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 32, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[35].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 33, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[36].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 34, DEFO_SIZE_Y - DRAW_SIZE * 2);

	g_Block[37].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 35, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[38].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 36, DEFO_SIZE_Y - DRAW_SIZE * 2);

	g_Block[39].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 39, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_Block[40].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 40, DEFO_SIZE_Y - DRAW_SIZE * 4);
	//���̏�ɓG
	g_Block[41].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 40, DEFO_SIZE_Y - DRAW_SIZE * 7);

	g_Block[42].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 41, DEFO_SIZE_Y - DRAW_SIZE * 2);

	g_Block[43].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 44, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[44].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[45].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 46, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[46].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 47, DEFO_SIZE_Y - DRAW_SIZE * 1);

	g_Block[47].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 48, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[48].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 49, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[49].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 50, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[50].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 51, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[51].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 52, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[52].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 53, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[53].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 54, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//�T���S
	g_Block[54].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 48, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[55].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 49, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[56].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 50, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[57].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 51, DEFO_SIZE_Y - DRAW_SIZE * 1);
	//�C��
	g_Block[58].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 52, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[59].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 53, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[60].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 54, DEFO_SIZE_Y - DRAW_SIZE * 1);

	g_Block[61].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 55, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[62].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 56, DEFO_SIZE_Y - DRAW_SIZE * 2);
	//�C��
	g_Block[63].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 56, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[64].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 57, DEFO_SIZE_Y - DRAW_SIZE * 5);

	g_Block[65].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 60, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[66].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 61, DEFO_SIZE_Y - DRAW_SIZE * 2);

	g_Block[67].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 62, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[68].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 63, DEFO_SIZE_Y - DRAW_SIZE * 0);
}

void InitStage41()
{
	//����Ɋւ��Ă�,�U�[�b�ƕ��ׂ銴���ɂ��Ă݂܂���
	//���� �� 16 �}�X * �c 9 �}�X�@�Ł@����Ă܂�
	// X�����@��ʍ��[����E�� * ����(�}�X)
	// Y�����@��ʉ��[������ * ����(�}�X)
	//�傫�Ȍ`���Ƃɕ�����Ƃ킩��₷������

	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (i == 5 || i >= 62 && i <= 64)
		{
			//�C�A�������u���b�N
			g_Block[i].Patern = 27.0f;
		}

		//�C�A
		if (i == 6 || i >= 94 && i <= 96)
		{
			g_Block[i].Patern = 28.0f;
			g_Block[i].limitmax = -(DRAW_SIZE * 2);
			g_Block[i].limitmin = SCREEN_HEIGHT - (DRAW_SIZE / 2.0);
			g_Block[i].Speed.y = -(GRAV / 4);
		}

		//�T���S
		if (i >= 12 && i <= 26)
		{
			g_Block[i].Patern = 26.0f;
		}

		//�Ƃ���
		if (i >= 36 && i <= 41)
		{
			g_Block[i].Patern = 13.0f;
			g_Block[i].ontime = ONTIME;
		}

		//�]��̃u���b�N
		if (i >= 98 && i < BLOCK_MAX)
		{
			//�g��Ȃ��u���b�N�͓����蔻��͎��Ȃ�
			g_Block[i].use = false;
			g_Block[i].draw_use = false;
		}
	}
	g_Block[0].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 0, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[1].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 1, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[2].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 2, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[3].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 3, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[4].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 4, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//�C�A������
	g_Block[5].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 5, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//�C�A
	g_Block[6].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 5, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//�������畁��
	g_Block[7].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 7, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[8].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[9].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 9, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[10].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 10, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[11].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 11, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//�T���S
	g_Block[12].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 9, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[13].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 10, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[14].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 11, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[15].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 9, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[16].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 10, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[17].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 11, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[18].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 9, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[19].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 10, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[20].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 11, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[21].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 9, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[22].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 10, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[23].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 11, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[24].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 9, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[25].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 10, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[26].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 11, DEFO_SIZE_Y - DRAW_SIZE * 5);
	//�������畁��
	g_Block[27].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 12, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[28].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[29].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 14, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[30].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//����������
	g_Block[31].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 16, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[32].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 17, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[33].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 18, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[34].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 19, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[35].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 20, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//�Ƃ���
	g_Block[36].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 21, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[37].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 22, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[38].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[39].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 24, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[40].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 25, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[41].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 26, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//�������畁��
	g_Block[42].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 21, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[43].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 22, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[44].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[45].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 24, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[46].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 25, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[47].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 26, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[48].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 27, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[49].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 28, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[50].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 29, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[51].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 30, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//���̏�ɓG
	g_Block[52].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 31, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//��������O��
	g_Block[53].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 32, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[54].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 33, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[55].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 34, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[56].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 35, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[57].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 36, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[58].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 37, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[59].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 38, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[60].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 39, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[61].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 40, DEFO_SIZE_Y - DRAW_SIZE * 3);
	//�C�A������
	g_Block[62].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 41, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[63].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 42, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[64].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 43, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//�������畁��
	g_Block[65].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 44, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[66].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[67].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 46, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[68].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 47, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//��������l��
	g_Block[69].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 48, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[70].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 49, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[71].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 50, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[72].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 48, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[73].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 49, DEFO_SIZE_Y - DRAW_SIZE * 7);
	//���̏�ɓG
	g_Block[74].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 50, DEFO_SIZE_Y - DRAW_SIZE * 7);

	g_Block[75].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 51, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[76].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 52, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[77].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 53, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[78].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 54, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[79].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 55, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[80].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 56, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[81].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 54, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[82].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 55, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[83].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 56, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_Block[84].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 57, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[85].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 58, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[86].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 59, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[87].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 60, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[88].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 61, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[89].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 62, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[90].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 63, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//���̏�ɓG
	g_Block[91].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 61, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[92].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 62, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[93].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 63, DEFO_SIZE_Y - DRAW_SIZE * 7);
	//�C�A
	g_Block[94].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 41, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[95].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 42, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[96].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 43, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[97].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 57, DEFO_SIZE_Y - DRAW_SIZE * 4);
}

void InitStage33()
{
	//����Ɋւ��Ă�,�U�[�b�ƕ��ׂ銴���ɂ��Ă݂܂���
	//���� �� 16 �}�X * �c 9 �}�X�@�Ł@����Ă܂�
	// X�����@��ʍ��[����E�� * ����(�}�X)
	// Y�����@��ʉ��[������ * ����(�}�X)
	//�傫�Ȍ`���Ƃɕ�����Ƃ킩��₷������

	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (i >= 0 && i <= 5)
		{
			//-�x���g�R���x�A�u���b�N1,4 �A�j�����S�_�͂���
			//+��22.0f
			g_Block[i].Patern = 22.0f;
		}

		if (i >= 9 && i <= 14)
		{
			//-�x���g�R���x�A�u���b�N10,13 �A�j�����S�_�͂���
			//+��22.0f
			g_Block[i].Patern = 23.0f;
		}

		//�㉺�ɓ������
		if (i >= 6 && i <= 8)
		{
			g_Block[i].Patern = 20.0f;
			g_Block[i].Speed.y = (GRAV / 4);
		}

		//�]��̃u���b�N
		if (i >= 72 && i < BLOCK_MAX)
		{
			//�g��Ȃ��u���b�N�͓����蔻��͎��Ȃ�
			g_Block[i].use = false;
			g_Block[i].draw_use = false;
		}
	}
	//+�x���g�R���x�A
	g_Block[0].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 0, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[1].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 1, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[2].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 2, DEFO_SIZE_Y - DRAW_SIZE * 1);

	g_Block[3].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 3, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[4].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 4, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[5].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 5, DEFO_SIZE_Y - DRAW_SIZE * 1);
	//�㉺�ɓ������
	g_Block[6].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 6, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[7].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 7, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[8].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 1);
	//-�x���g�R���x�A
	g_Block[9].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 9, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[10].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 10, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[11].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 11, DEFO_SIZE_Y - DRAW_SIZE * 1);

	g_Block[12].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 12, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[13].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[14].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 14, DEFO_SIZE_Y - DRAW_SIZE * 1);
	//�������畁��
	g_Block[15].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[16].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 16, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[17].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 17, DEFO_SIZE_Y - DRAW_SIZE * 1);

	g_Block[18].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[19].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 16, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[20].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 17, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_Block[21].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 18, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[22].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 19, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[23].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 20, DEFO_SIZE_Y - DRAW_SIZE * 1);

	g_Block[24].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 18, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[25].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 19, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[26].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 20, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_Block[27].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 21, DEFO_SIZE_Y - DRAW_SIZE * 1);
	//�ԃ{�^��
	g_Block[28].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 21, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[28].button = true;

	g_Block[29].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 21, DEFO_SIZE_Y - DRAW_SIZE * 4);
	//�{�^��
	g_Block[30].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 21, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[30].button = true;
	//�������畁��
	g_Block[31].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 27, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[32].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 28, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[33].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 29, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[34].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 30, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[35].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 31, DEFO_SIZE_Y - DRAW_SIZE * 1);
	//���̏�ɓG
	g_Block[36].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 27, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[37].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 28, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[38].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 29, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[39].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 30, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[40].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 31, DEFO_SIZE_Y - DRAW_SIZE * 4);
	//��������O��
	g_Block[41].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 32, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[42].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 33, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[43].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 34, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[44].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 35, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[45].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 36, DEFO_SIZE_Y - DRAW_SIZE * 1);
	//�i�{�[��
	g_Block[46].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 37, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[47].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 38, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[48].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 39, DEFO_SIZE_Y - DRAW_SIZE * 4);
	//�i�{�[��
	g_Block[49].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 41, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[50].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 42, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[51].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 43, DEFO_SIZE_Y - DRAW_SIZE * 4);
	//�i�{�[��
	g_Block[52].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[53].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 47, DEFO_SIZE_Y - DRAW_SIZE * 4);
	//�������畁��
	g_Block[54].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 48, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[55].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 49, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[56].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 50, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[57].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 51, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[58].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 52, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[59].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 52, DEFO_SIZE_Y - DRAW_SIZE * 8);
	//���̏�ɓG
	g_Block[60].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 53, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[61].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 54, DEFO_SIZE_Y - DRAW_SIZE * 7);
	//���E�ɓ������
	g_Block[62].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 55, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[63].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 56, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[64].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 57, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//�������畁��
	g_Block[65].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 57, DEFO_SIZE_Y - DRAW_SIZE * 7);
	//���̏�ɓG
	g_Block[66].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 58, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[67].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 59, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[68].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 59, DEFO_SIZE_Y - DRAW_SIZE * 8);

	g_Block[69].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 61, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[70].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 62, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[71].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 63, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//�ړ�����u���b�N�ɂ��Ă�
	//�����ʒu��ݒ��ɏڂ������Ƃ͐ݒ�
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		//�i
		if (i >= 46 && i <= 53)
		{
			g_Block[i].Patern = 25.0f;
			g_Block[i].Speed.y = 0;
			//���̍ő�l������
			g_Block[i].limitmax = g_Block[i].pos.y + (DRAW_SIZE * 4);
		}
		//���ɓ������
		if (i >= 62 && i <= 64)
		{
			g_Block[i].Patern = 21.0f;
			g_Block[i].Speed.x = 1.0f;
			//���E�̍ő�l������
			g_Block[i].limitmax = g_Block[i].pos.x + DRAW_SIZE * 3;
			g_Block[i].limitmin = g_Block[i].pos.x - DRAW_SIZE * 3;
		}
	}
}

void InitStage32()
{
	//����Ɋւ��Ă�,�U�[�b�ƕ��ׂ銴���ɂ��Ă݂܂���
	//���� �� 16 �}�X * �c 9 �}�X�@�Ł@����Ă܂�
	// X�����@��ʍ��[����E�� * ����(�}�X)
	// Y�����@��ʉ��[������ * ����(�}�X)
	//�傫�Ȍ`���Ƃɕ�����Ƃ킩��₷������

	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (i >= 31 && i <= 36)
		{
			//-�x���g�R���x�A�u���b�N32,35 �A�j�����S�_�͂���
			g_Block[i].Patern = 23.0f;
		}

		//�]��̃u���b�N
		if (i >= 79 && i < BLOCK_MAX)
		{
			//�g��Ȃ��u���b�N�͓����蔻��͎��Ȃ�
			g_Block[i].use = false;
			g_Block[i].draw_use = false;
		}
	}
	g_Block[0].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 0, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[1].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 1, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[2].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 2, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[3].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 3, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[4].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 4, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[5].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 5, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[6].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 0, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[7].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 1, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[8].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 2, DEFO_SIZE_Y - DRAW_SIZE * 5);

	g_Block[9].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 3, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[10].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 4, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[11].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 5, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_Block[12].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 6, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[13].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 7, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[14].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[15].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 6, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[16].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 9, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[17].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 10, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//���]�u���b�N
	g_Block[18].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 11, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[18].Patern = 2.0f;
	//�i�{�[���u���b�N
	g_Block[19].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 12, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[20].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[21].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 14, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[22].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 12, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[23].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[24].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 14, DEFO_SIZE_Y - DRAW_SIZE * 5);
	//�{�^��
	g_Block[25].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 4, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[25].button = true;
	//�������畁��
	g_Block[26].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 16, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[27].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 17, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[28].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 18, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[29].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 19, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[30].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 20, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//-�x���g�R���x�A//etc�Œǉ�����32.35
	g_Block[31].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 21, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[32].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 22, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[33].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[34].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 24, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[35].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 25, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[36].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 26, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//�������畁��
	g_Block[37].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 27, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[38].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 28, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[39].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 29, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[40].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 27, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[41].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 28, DEFO_SIZE_Y - DRAW_SIZE * 4);
	//���̏�ɓG
	g_Block[42].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 29, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_Block[43].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 30, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[44].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 31, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//��������O��
	g_Block[45].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 32, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[46].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 30, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[47].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 31, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[48].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 32, DEFO_SIZE_Y - DRAW_SIZE * 4);
	//�i�{�[��
	g_Block[49].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 26, DEFO_SIZE_Y - DRAW_SIZE * 5);
	//�������畁��
	g_Block[50].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 33, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[51].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 34, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[52].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 35, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[53].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 36, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[54].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 37, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[55].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 38, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//�i�{�[��
	g_Block[56].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 39, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[57].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 39, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[58].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 39, DEFO_SIZE_Y - DRAW_SIZE * 6);
	g_Block[59].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 39, DEFO_SIZE_Y - DRAW_SIZE * 7);
	//koko
	g_Block[60].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 40, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[61].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 41, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//�{�^��
	g_Block[62].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 41, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[62].button = true;
	//�������畁��
	g_Block[63].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 42, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[64].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 40, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[65].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 41, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[66].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 42, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_Block[67].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 43, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[68].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 44, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[69].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 44, DEFO_SIZE_Y - DRAW_SIZE * 1);

	g_Block[70].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 50, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[71].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 51, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[72].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 52, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[73].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 53, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[74].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 54, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[75].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 55, DEFO_SIZE_Y - DRAW_SIZE * 1);

	g_Block[76].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 61, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[77].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 62, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[78].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 63, DEFO_SIZE_Y - DRAW_SIZE * 1);

	//�ړ�����u���b�N�ɂ��Ă�
	//�����ʒu��ݒ��ɏڂ������Ƃ͐ݒ�
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		//�i
		if (i >= 19 && i <= 24 || i == 49 || i >= 56 && i <= 59)
		{
			g_Block[i].Patern = 25.0f;
			g_Block[i].Speed.y = 0;
			//���̍ő�l������
			g_Block[i].limitmax = g_Block[i].pos.y + (DRAW_SIZE * 4);
		}
		//���ɓ������
		if (i >= 70 && i <= 75)
		{
			g_Block[i].Patern = 21.0f;
			g_Block[i].Speed.x = (GRAV / 4);
			//���E�̍ő�l������
			g_Block[i].limitmax = g_Block[i].pos.x + DRAW_SIZE * 5;
			g_Block[i].limitmin = g_Block[i].pos.x - DRAW_SIZE * 5;
		}
	}
}

void InitStage31()
{
	//����Ɋւ��Ă�,�U�[�b�ƕ��ׂ銴���ɂ��Ă݂܂���
	//���� �� 16 �}�X * �c 9 �}�X�@�Ł@����Ă܂�
	// X�����@��ʍ��[����E�� * ����(�}�X)
	// Y�����@��ʉ��[������ * ����(�}�X)
	//�傫�Ȍ`���Ƃɕ�����Ƃ킩��₷������

	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (i >= 15 && i <= 23 || i >= 38 && i <= 40 || i >= 60 && i <= 62)
		{
			//+�x���g�R���x�A�u���b�N16,19,22,39,61�@�A�j�����S�_�͂���
			g_Block[i].Patern = 22.0f;
		}

		if (i >= 51 && i <= 59)
		{
			//-�x���g�R���x�A�u���b�N52,55,58 �A�j�����S�_�͂���
			g_Block[i].Patern = 23.0f;
		}

		//�]��̃u���b�N
		if (i >= 91 && i < BLOCK_MAX)
		{
			//�g��Ȃ��u���b�N�͓����蔻��͎��Ȃ�
			g_Block[i].use = false;
			g_Block[i].draw_use = false;
		}
	}
	g_Block[0].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 0, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[1].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 1, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[2].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 2, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[3].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 3, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[4].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 4, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[5].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 5, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[6].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 6, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[7].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 7, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[8].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[9].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 9, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[10].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 10, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[11].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 11, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[12].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 12, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[13].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[14].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 14, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//+�x���g�R���x�A
	g_Block[15].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 6, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[16].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 7, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[17].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 1);

	g_Block[18].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 9, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[19].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 10, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[20].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 11, DEFO_SIZE_Y - DRAW_SIZE * 1);

	g_Block[21].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 12, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[22].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[23].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 14, DEFO_SIZE_Y - DRAW_SIZE * 1);
	//�������畁��
	g_Block[24].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 21, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[25].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 22, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[26].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[27].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[28].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[29].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 6);
	g_Block[30].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[31].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 8);

	g_Block[32].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 24, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[33].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 25, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[34].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 26, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[35].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 27, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[36].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 28, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[37].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 29, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//+�x���g�R���x�A
	g_Block[38].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 24, DEFO_SIZE_Y - DRAW_SIZE * 4);
	//���̏�ɓG
	g_Block[39].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 25, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[40].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 26, DEFO_SIZE_Y - DRAW_SIZE * 4);
	//����
	g_Block[41].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 31, DEFO_SIZE_Y - DRAW_SIZE * 3);
	//��������O��
	g_Block[42].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 32, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[43].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 33, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[44].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 34, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[45].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 35, DEFO_SIZE_Y - DRAW_SIZE * 3);
	//���]
	g_Block[46].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 36, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[46].Patern = 2.0f;
	g_Block[47].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 37, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[48].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 38, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[49].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 39, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[50].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 40, DEFO_SIZE_Y - DRAW_SIZE * 3);
	//-�x���g�R���x�A
	g_Block[51].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 32, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[52].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 33, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[53].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 34, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[54].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 35, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[55].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 36, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[56].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 37, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[57].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 38, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[58].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 39, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[59].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 40, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//+�x���g�R���x�A
	g_Block[60].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 44, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[61].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[62].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 46, DEFO_SIZE_Y - DRAW_SIZE * 4);
	//�������畁��
	g_Block[63].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 44, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[64].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[65].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 46, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//�{�^��
	g_Block[66].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 46, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[66].button = true;
	//�������畁��
	g_Block[67].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 47, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[68].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 47, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[69].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 47, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[70].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 47, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[71].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 47, DEFO_SIZE_Y - DRAW_SIZE * 4);
	//���̏�ɓG
	g_Block[72].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 48, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[73].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 49, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[74].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 50, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[75].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 48, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[76].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 49, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[77].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 50, DEFO_SIZE_Y - DRAW_SIZE * 4);
	//���̏�ɓG
	g_Block[78].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 48, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[79].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 49, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[80].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 50, DEFO_SIZE_Y - DRAW_SIZE * 7);

	g_Block[81].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 51, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[82].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 52, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[83].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 53, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[84].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 54, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[85].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 55, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[86].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 56, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[87].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 61, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[88].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 62, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[89].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 63, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[90].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 16, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[90].Patern = 9.0f;
}

void InitStage23()
{
	//����Ɋւ��Ă�,�U�[�b�ƕ��ׂ銴���ɂ��Ă݂܂���
	//���� �� 16 �}�X * �c 9 �}�X�@�Ł@����Ă܂�
	// X�����@��ʍ��[����E�� * ����(�}�X)
	// Y�����@��ʉ��[������ * ����(�}�X)
	//�傫�Ȍ`���Ƃɕ�����Ƃ킩��₷������

	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (i >= 13 && i <= 14 || i == 20)
		{
			//�T�{�e���u���b�N
			g_Block[i].Patern = 15.0f;
		}
		//�Ƃ���
		if (i >= 22 && i <= 34)
		{
			g_Block[i].Patern = 13.0f;
			g_Block[i].ontime = ONTIME;
		}
		//�㉺�ɓ������
		if (i >= 52 && i <= 55)
		{
			g_Block[i].Patern = 20.0f;
			g_Block[i].Speed.y = (GRAV / 4);
		}

		//�]��̃u���b�N
		if (i >= 56 && i < BLOCK_MAX)
		{
			//�g��Ȃ��u���b�N�͓����蔻��͎��Ȃ�
			g_Block[i].use = false;
			g_Block[i].draw_use = false;
		}
	}
	g_Block[0].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 0, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[1].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 1, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[2].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 2, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[3].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 3, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[4].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 4, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[5].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 5, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[6].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 6, DEFO_SIZE_Y - DRAW_SIZE * 3);
	//�ԃ{�^��
	g_Block[7].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 6, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[7].button = true;
	//�Ԃ̒n�`
	g_Block[8].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 11, DEFO_SIZE_Y - DRAW_SIZE * 3);
	//�{�^��
	g_Block[9].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 11, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[9].button = true;
	//�������畁�ʓ��
	g_Block[10].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 16, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[11].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 17, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[12].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 18, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[13].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 27, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[14].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 31, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[15].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 21, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[16].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 22, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[17].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//�����u���b�N
	g_Block[18].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 24, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[18].Patern = 17.0f;
	g_Block[19].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 29, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[19].Patern = 17.0f;
	//�T�{�e��
	//���̏�ɓG
	g_Block[20].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 26, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[21].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 34, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//�Ƃ���
	g_Block[22].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 35, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[23].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 36, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[24].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 37, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[25].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 38, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[26].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 39, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[27].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 40, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[28].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 41, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[29].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 42, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[30].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 43, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[31].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 44, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[32].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[33].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 46, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//���̏�ɓG
	g_Block[34].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 47, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[35].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 48, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//�������畁��
	g_Block[36].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 46, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[37].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 47, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[38].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 48, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_Block[39].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 49, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[40].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 50, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[41].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 51, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_Block[42].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 49, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[43].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 50, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[44].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 51, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[45].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 52, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[46].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 52, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[47].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 59, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[48].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 60, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[49].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 61, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[50].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 62, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[51].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 63, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//��������
	g_Block[52].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 54, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[53].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 55, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[54].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 56, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[55].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 57, DEFO_SIZE_Y - DRAW_SIZE * 1);

}

void InitStage22()
{
	//����Ɋւ��Ă�,�U�[�b�ƕ��ׂ銴���ɂ��Ă݂܂���
	//���� �� 16 �}�X * �c 9 �}�X�@�Ł@����Ă܂�
	// X�����@��ʍ��[����E�� * ����(�}�X)
	// Y�����@��ʉ��[������ * ����(�}�X)
	//�傫�Ȍ`���Ƃɕ�����Ƃ킩��₷������
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (i >= 21 && i <= 26 || i >= 49 && i <= 51)
		{
			g_Block[i].Patern = 13.0f;
			g_Block[i].ontime = ONTIME;
		}
		//�]��̃u���b�N
		if (i >= 88 && i < BLOCK_MAX)
		{
			//�g��Ȃ��u���b�N�͓����蔻��͎��Ȃ�
			g_Block[i].use = false;
			g_Block[i].draw_use = false;
		}
	}
	g_Block[0].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 0, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[1].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 1, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[2].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 2, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[3].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 3, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[4].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 4, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[5].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 5, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[6].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 6, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[7].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 7, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[8].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[9].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 3, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//���̏�ɓG
	g_Block[10].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 4, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[11].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 5, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[12].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 6, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[13].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 7, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[14].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[15].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 9, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[16].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 10, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[17].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 11, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[18].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 12, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//���]�u���b�N
	g_Block[19].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[19].Patern = 2.0f;
	g_Block[20].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 14, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//���������
	g_Block[21].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 9, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[22].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 10, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[23].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 11, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[24].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 12, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[25].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[26].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 14, DEFO_SIZE_Y - DRAW_SIZE * 3);
	//�������畁��
	g_Block[27].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 16, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[28].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 17, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[29].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 18, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[30].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 19, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[31].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 20, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[32].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 20, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[32].Patern = 15.0f;
	g_Block[33].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[34].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 16, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[35].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 17, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[36].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 18, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[37].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 19, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[38].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 2, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[39].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 3, DEFO_SIZE_Y - DRAW_SIZE * 0);

	//�T�{�e��
	g_Block[40].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 20, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[41].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 20, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[40].Patern = 15.0f;
	g_Block[41].Patern = 15.0f;
	//�������畁��
	g_Block[42].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[43].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 24, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[44].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 25, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[45].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 26, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[46].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 27, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[47].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 28, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[48].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 29, DEFO_SIZE_Y - DRAW_SIZE * 3);
	//���������
	g_Block[49].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 30, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[50].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 31, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[51].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 32, DEFO_SIZE_Y - DRAW_SIZE * 3);
	//�������獻��
	g_Block[52].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 34, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[53].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 35, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[52].Patern = 17.0f;
	g_Block[53].Patern = 17.0f;
	//�������]
	g_Block[54].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 38, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[54].Patern = 2.0f;

	g_Block[55].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 39, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[56].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 40, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[57].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 41, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[58].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 42, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[59].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 43, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[60].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 44, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[61].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[62].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[63].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[64].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[65].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_Block[66].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[67].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 46, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[68].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 47, DEFO_SIZE_Y - DRAW_SIZE * 5);

	g_Block[69].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 48, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[70].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 49, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[71].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 50, DEFO_SIZE_Y - DRAW_SIZE * 5);

	g_Block[72].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 51, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[73].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 52, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[74].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 53, DEFO_SIZE_Y - DRAW_SIZE * 5);
	//��������T�{�e��
	//���̏�ɓG
	g_Block[75].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 47, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[76].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 49, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[77].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 51, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[78].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 53, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[75].Patern = 15.0f;
	g_Block[76].Patern = 15.0f;
	g_Block[77].Patern = 15.0f;
	g_Block[78].Patern = 15.0f;
	//�������畁��
	g_Block[79].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 55, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[80].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 56, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[81].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 57, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[82].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 58, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[83].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 59, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[84].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 60, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[85].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 61, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[86].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 62, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[87].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 63, DEFO_SIZE_Y - DRAW_SIZE * 0);
}

void InitStage21()
{
	//����Ɋւ��Ă�,�U�[�b�ƕ��ׂ銴���ɂ��Ă݂܂���
	//���� �� 16 �}�X * �c 9 �}�X�@�Ł@����Ă܂�
	// X�����@��ʍ��[����E�� * ����(�}�X)
	// Y�����@��ʉ��[������ * ����(�}�X)
	//�傫�Ȍ`���Ƃɕ�����Ƃ킩��₷������
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (i >= 15 && i <= 23 || i >= 80 && i <= 81)
		{
			//�T�{�e���u���b�N
			g_Block[i].Patern = 15.0f;
		}
		//�]��̃u���b�N
		if (i >= 91 && i < BLOCK_MAX)
		{
			//�g��Ȃ��u���b�N�͓����蔻��͎��Ȃ�
			g_Block[i].use = false;
			g_Block[i].draw_use = false;
		}

	}
	g_Block[0].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 0, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[1].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 1, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[2].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 2, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[3].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 3, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[4].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 4, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[5].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 5, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[5].Patern = 13.0f;
	g_Block[5].ontime = ONTIME;

	g_Block[6].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 6, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[7].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 7, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[8].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[9].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 9, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[10].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 10, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[11].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 11, DEFO_SIZE_Y - DRAW_SIZE * 1);

	g_Block[12].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 9, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[13].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 10, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[14].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 11, DEFO_SIZE_Y - DRAW_SIZE * 2);
	//�T�{�e��
	g_Block[15].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[16].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[17].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 17, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[18].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 19, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[19].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 21, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[20].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[21].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 25, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[22].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 27, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[23].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 29, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//�����܂�
	g_Block[24].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[25].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 16, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[26].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 17, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[27].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 18, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[28].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 19, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[29].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 20, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[30].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 21, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[31].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 22, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[32].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[33].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[34].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 16, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[35].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 17, DEFO_SIZE_Y - DRAW_SIZE * 7);

	g_Block[36].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 18, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[37].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 19, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[38].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 20, DEFO_SIZE_Y - DRAW_SIZE * 7);

	g_Block[39].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 21, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[40].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 22, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[41].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 7);

	g_Block[42].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 30, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[43].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 31, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[44].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 32, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[45].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 33, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[46].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 34, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[47].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 35, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[48].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 21, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[49].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 22, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[50].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 7);

	g_Block[51].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 24, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[52].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 25, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[53].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 26, DEFO_SIZE_Y - DRAW_SIZE * 7);

	g_Block[54].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 30, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[55].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 31, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[56].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 32, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//��������O��
	g_Block[57].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 33, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[58].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 34, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[59].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 35, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[60].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 36, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[61].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 37, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//���]�u���b�N
	g_Block[62].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 37, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[62].Patern = 2.0f;
	g_Block[63].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 38, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[64].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 39, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[65].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 40, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[66].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 41, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[67].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 42, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[68].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 43, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[69].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 44, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//�����u���b�N
	g_Block[70].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[70].Patern = 17.0f;

	g_Block[71].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 48, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[72].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 48, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[73].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 48, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[74].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 48, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[75].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 51, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[76].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 52, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//����鍻
	g_Block[77].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 49, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[78].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 50, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[79].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 51, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[77].Patern = 13.0f;
	g_Block[78].Patern = 13.0f;
	g_Block[79].Patern = 13.0f;
	g_Block[77].ontime = ONTIME;
	g_Block[78].ontime = ONTIME;
	g_Block[79].ontime = ONTIME;
	//�T�{�e��
	g_Block[80].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 51, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[81].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 52, DEFO_SIZE_Y - DRAW_SIZE * 1);
	//����
	g_Block[82].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 55, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[83].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 56, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[84].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 57, DEFO_SIZE_Y - DRAW_SIZE * 2);

	g_Block[85].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 58, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[86].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 59, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[87].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 60, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[88].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 61, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[89].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 62, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[90].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 63, DEFO_SIZE_Y - DRAW_SIZE * 4);
}

void InitStage13()
{
	//����Ɋւ��Ă�,�U�[�b�ƕ��ׂ銴���ɂ��Ă݂܂���
	//���� �� 16 �}�X * �c 9 �}�X�@�Ł@����Ă܂�
	// X�����@��ʍ��[����E�� * ����(�}�X)
	// Y�����@��ʉ��[������ * ����(�}�X)
	//�傫�Ȍ`���Ƃɕ�����Ƃ킩��₷������
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		//�]��̃u���b�N
		if (i >= 56 && i < BLOCK_MAX)
		{
			//�g��Ȃ��u���b�N�͓����蔻��͎��Ȃ�
			g_Block[i].use = false;
			g_Block[i].draw_use = false;
		}
	}
	//���̏�Ɍ�
	g_Block[0].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 0, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[1].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 1, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[2].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 2, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[3].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 3, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[4].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 4, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[5].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 5, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[6].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 6, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[7].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 7, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[8].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//�o�l
	g_Block[9].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[9].Patern = 9.0f;

	g_Block[10].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 12, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[11].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[12].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 14, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[13].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[14].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 16, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[15].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 17, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[16].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 18, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[17].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 16, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[18].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 17, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[19].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 18, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_Block[20].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 19, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[21].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 20, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[22].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 21, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//���̏�Ɍ�
	g_Block[23].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 19, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[24].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 20, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[25].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 21, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_Block[26].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 22, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[27].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[28].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 24, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[29].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 22, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[30].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[31].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 24, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_Block[32].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 25, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[33].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 26, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[34].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 27, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[35].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 28, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[36].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 29, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[37].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 30, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[38].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 31, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[39].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 32, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[40].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 33, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[41].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 34, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[42].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 35, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[43].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 36, DEFO_SIZE_Y - DRAW_SIZE * 6);
	g_Block[44].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 37, DEFO_SIZE_Y - DRAW_SIZE * 6);
	g_Block[45].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 38, DEFO_SIZE_Y - DRAW_SIZE * 6);
	//���̏�Ɍ�
	g_Block[46].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 39, DEFO_SIZE_Y - DRAW_SIZE * 6);
	g_Block[47].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 40, DEFO_SIZE_Y - DRAW_SIZE * 6);
	g_Block[48].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 41, DEFO_SIZE_Y - DRAW_SIZE * 6);

	g_Block[49].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 42, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[50].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 43, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[51].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 44, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//�{�^��
	g_Block[52].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 57, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[52].button = true;
	//�������畁��
	g_Block[53].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 61, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[54].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 62, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[55].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 63, DEFO_SIZE_Y - DRAW_SIZE * 0);
}

void InitStage12()
{
	//����Ɋւ��Ă�,�U�[�b�ƕ��ׂ銴���ɂ��Ă݂܂���
	//���� �� 16 �}�X * �c 9 �}�X�@�Ł@����Ă܂�
	// X�����@��ʍ��[����E�� * ����(�}�X)
	// Y�����@��ʉ��[������ * ����(�}�X)
	//�傫�Ȍ`���Ƃɕ�����Ƃ킩��₷������
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (i >= 10 && i <= 14 || i >= 79 && i <= 83)
		{
			//�����Ȃ��^�C�v�̏��u���b�N
			g_Block[i].Patern = 1.0f;
		}
		//�]��͂Ȃ��B�ő�����₵���畜������
		if (i >= 96 && i < BLOCK_MAX)
		{
			//�g��Ȃ��u���b�N�͓����蔻��͎��Ȃ�
			g_Block[i].use = false;
			g_Block[i].draw_use = false;
		}
	}

	g_Block[0].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 0, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[1].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 1, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[2].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 2, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[3].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 3, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[4].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 4, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//���]�u���b�N
	g_Block[5].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 5, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[5].Patern = 2.0f;

	g_Block[6].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 6, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[7].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 7, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[8].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[9].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//�y
	g_Block[10].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[11].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[12].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 6);
	g_Block[13].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[14].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 8);
	//�������畁��
	g_Block[15].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 9, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[16].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 10, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[17].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 11, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[18].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 9, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[19].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 10, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[20].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 11, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_Block[21].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 12, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[22].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[23].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 14, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[24].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 12, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[25].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[26].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 14, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_Block[27].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[28].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 16, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[29].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 17, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[30].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[31].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 16, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[32].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 17, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_Block[33].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 18, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[34].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 19, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[35].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 20, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[36].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 18, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[37].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 19, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[38].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 20, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_Block[39].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 21, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[40].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 22, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[41].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[42].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 21, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[43].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 22, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[44].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[45].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 24, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[46].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 25, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[47].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 26, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[48].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 24, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[49].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 25, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[50].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 25, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[50].button = true;
	g_Block[51].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 26, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[52].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 30, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[53].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 31, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[54].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 32, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[55].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 33, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[56].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 34, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[57].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 35, DEFO_SIZE_Y - DRAW_SIZE * 1);

	g_Block[58].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 36, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[59].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 37, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[60].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 38, DEFO_SIZE_Y - DRAW_SIZE * 2);

	g_Block[61].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 39, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[62].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 40, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[63].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 41, DEFO_SIZE_Y - DRAW_SIZE * 2);

	g_Block[64].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 42, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[65].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 43, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[66].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 44, DEFO_SIZE_Y - DRAW_SIZE * 2);

	g_Block[67].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[68].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 46, DEFO_SIZE_Y - DRAW_SIZE * 2);
	//���]�u���b�N
	g_Block[69].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 47, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[69].Patern = 2.0f;
	//�������畁��
	g_Block[70].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[71].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 46, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[72].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 47, DEFO_SIZE_Y - DRAW_SIZE * 7);

	g_Block[73].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 48, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[74].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 49, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[75].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 50, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[76].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 51, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[77].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 52, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[78].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 53, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//�y
	g_Block[79].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 53, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[80].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 53, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[81].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 53, DEFO_SIZE_Y - DRAW_SIZE * 6);
	g_Block[82].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 53, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[83].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 53, DEFO_SIZE_Y - DRAW_SIZE * 8);
	//�������畁��
	g_Block[84].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 54, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[85].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 55, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[86].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 56, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//���̏�Ɍ�
	g_Block[87].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 54, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[88].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 57, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[89].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 58, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[90].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 59, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[91].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 60, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[92].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 61, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[93].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 62, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[94].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 63, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[95].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 55, DEFO_SIZE_Y - DRAW_SIZE * 4);
}

void InitStage11()
{
	//����Ɋւ��Ă�,�U�[�b�ƕ��ׂ銴���ɂ��Ă݂܂���
	//���� �� 16 �}�X * �c 9 �}�X�@�Ł@����Ă܂�
	// X�����@��ʍ��[����E�� * ����(�}�X)
	// Y�����@��ʉ��[������ * ����(�}�X)
	//�傫�Ȍ`���Ƃɕ�����Ƃ킩��₷������
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (i >= 21 && i <= 29 || i >= 33 && i <= 44 || i >= 74 && i <= 76)
		{
			//�����Ȃ��^�C�v�̏��u���b�N
			g_Block[i].Patern = 1.0f;
		}

		if (i >= 92 && i < BLOCK_MAX)
		{
			//�g��Ȃ��u���b�N�͓����蔻��ƕ`��͎��Ȃ�
			g_Block[i].use = false;
			g_Block[i].draw_use = false;
		}
	}
	g_Block[0].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 0, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[1].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 1, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[2].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 2, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[3].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 3, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[4].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 4, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[5].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 5, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[6].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 6, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[7].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 7, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[8].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[9].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 9, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[10].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 10, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[11].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 11, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[12].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 12, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[13].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[14].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 14, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[15].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//����������
	g_Block[16].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 16, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[17].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 17, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[18].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 18, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[19].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 19, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[20].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 20, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[21].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[22].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 24, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[23].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 25, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[24].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[25].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 24, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[26].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 25, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[27].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[28].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 24, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[29].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 25, DEFO_SIZE_Y - DRAW_SIZE * 2);

	g_Block[30].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[31].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 24, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[32].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 25, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[33].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 26, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[34].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 27, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[35].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 28, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[36].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 26, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[37].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 27, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[38].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 28, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[39].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 26, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[40].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 27, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[41].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 28, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[42].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 26, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[43].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 27, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[44].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 28, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[45].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 26, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[46].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 27, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[47].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 28, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_Block[48].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 21, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[49].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 22, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[50].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 29, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[51].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 30, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[52].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 31, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//1-1�O�ʓ�������̂Œ������܂���
	g_Block[53].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 32, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[54].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 33, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[55].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 34, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[56].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 35, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[57].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 36, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[58].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 37, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[59].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 38, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[60].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 39, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[61].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 40, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[62].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 41, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[63].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 42, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[64].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 43, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_Block[65].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 44, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[66].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[67].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 46, DEFO_SIZE_Y - DRAW_SIZE * 5);

	g_Block[68].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 49, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[69].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 50, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[70].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 51, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[71].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 49, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[72].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 50, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[73].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 51, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[74].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 52, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[75].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 53, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[76].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 54, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//�y
	g_Block[77].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 52, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[78].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 53, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[79].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 54, DEFO_SIZE_Y - DRAW_SIZE * 1);

	g_Block[80].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 52, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[81].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 53, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[82].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 54, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[83].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 55, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[84].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 56, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[85].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 57, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[86].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 58, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[87].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 59, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[88].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 60, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[89].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 61, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[90].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 62, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[91].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 63, DEFO_SIZE_Y - DRAW_SIZE * 0);
}