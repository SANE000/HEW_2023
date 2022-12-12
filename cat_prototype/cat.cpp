#include "cat.h"
#include "main.h"
#include "blockpreview.h"
#include "inputx.h"
#include "texture.h"
#include "sprite.h"
#include "Scene.h"
#include "sound.h"
#include "collision.h"
#include "camera.h"
#include "jumpflag.h"	


//�O���[�o���ϐ�
//int JumpSoundNo = 0;

//�܂Ƃ��̕b����m�邽��	
int tumetogi_count = 0;

//�v���C���[�I�u�W�F�N�g
static CAT g_Cat;
static MOVE_BLOCK *m_block = GetMoveBlock();

HRESULT InitCat()
{
	//�e�N�X�`�����[�h �摜�̖��O�����悤
	g_Cat.texNo = LoadTexture((char*)"data\\texture\\cat.png");
	//�\���̂̏�����
	g_Cat.pos.x = DEFO_SIZE_X;
	g_Cat.pos.y = CAT_INIT_Y;
	g_Cat.dir.x = WALK;
	g_Cat.move_flag = false;
	g_Cat.jump_flag = false;
	g_Cat.tumetogi_flag = false;
	g_Cat.jump_y = 0.0f;
	g_Cat.limit_jump = 0.0f;
	g_Cat.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Cat.patern = 0.0f;
	g_Cat.half_flag = false;
	g_Cat.goal_flag = false;
	//�g�p���t���O���I���ɂ���
	g_Cat.use = true;

	g_Cat.nowjump_flag = 0;

	//�T�E���h�̃��[�h
	//char filename[] = "data\\SE\\boyoyon.wav";
	//JumpSoundNo = LoadSound(filename);
	//HRESULT�ɒl��Ԃ��Đ���I���������Ƃ�A������
	return S_OK;
}
//�I������
void UnInitCat()
{

}
//�X�V����
void UpdateCat()
{
	//�󒆂ɕ����Ă���Ƃ������d�͂̉e��
	if (g_Cat.jump_flag == false)
	{
		g_Cat.pos.y += GRAV;
	}
	//�E�Ɍ������Đi��ł���Ƃ�
	if (g_Cat.move_flag == false)
	{

		//�n�ʂɂ��Ă���Ƃ�
		if (g_Cat.jump_flag == true)
		{
			//�L�A�j���[�V�����p�^�[���Ǘ�
			g_Cat.patern += 0.04f;

			//�܂Ƃ��A�j���[�V���� �E
			if (g_Cat.tumetogi_flag == true)
			{
				if (g_Cat.patern < 4.0f)
				{
					g_Cat.patern = 4.0f;
				}

				tumetogi_count++;


				if (g_Cat.patern > 6.0f)
				{
					g_Cat.patern = 4.0f;
				}
			}
			else
			{

				//�E�Ɍ������ĕ����L�A�j��
				if (g_Cat.patern > 1.9f)
				{
					g_Cat.patern = 0.0f;
				}
				else if (g_Cat.patern > 2.0f)
				{
					g_Cat.patern = 0.0f;
				}

			}

		}
		else
		{
			//�L�A�j���[�V�����p�^�[���Ǘ�
			g_Cat.patern += 0.20f;

			//�W�����v�p���[��0�ȏゾ������@
			if (g_Cat.jump_y > 0.0f)
			{

				//�W�����v�L�A�j���@�E
				if (g_Cat.patern > 10.0f)
				{
					g_Cat.patern = 9.0f;
				}
			}
			else
			{
				//������L�A�j���@�E
				g_Cat.patern = 10.0f;

			}
		}
	}
	//���Ɍ������Đi��ł���Ƃ�
	else
	{
		g_Cat.patern += 0.04f;

		//�n�ʂɂ��Ă���Ƃ�
		if (g_Cat.jump_flag == true)
		{
			//�܂Ƃ��A�j���[�V���� ��
			if (g_Cat.tumetogi_flag == true)
			{
				tumetogi_count++;

				if (g_Cat.patern > 8.0f)
				{
					g_Cat.patern = 6.0f;
				}
			}
			//���Ɍ������ĕ����L�A�j��
			else if (g_Cat.patern > 4.0f)
			{

				g_Cat.patern = 2.0f;
			}
			else if (g_Cat.patern < 2.0f)
			{
				g_Cat.patern = 2.0f;
			}
		}
		else
		{
			//�L�A�j���[�V�����p�^�[���Ǘ�
			g_Cat.patern += 0.20f;

			//�W�����v�p���[��0�ȏゾ������@
			if (g_Cat.jump_y > 0.0f)
			{

				//�W�����v�L�A�j���@��
				if (g_Cat.patern > 13.0f)
				{
					g_Cat.patern = 12.0f;
				}
			}
			else
			{
				//������L�A�j���@��
				g_Cat.patern = 13.0f;

			}


		}

	}

	if (tumetogi_count > 180 && g_Cat.tumetogi_flag == true)
	{
		g_Cat.tumetogi_flag = false;
	}

	//�܂Ƃ����͐i�܂Ȃ�
	if (g_Cat.tumetogi_flag == false)
	{
		if (tumetogi_count > 0)
			tumetogi_count = 0;

		//�����ňړ�(�ǂɂԂ���or�����l�܂Ŗ߂����甽�])
		if (g_Cat.move_flag == false)
		{
			//�����^�C�~���O�ŃW�����v���n�܂邽�߁A��Ԓi���ɉ����Ĕ��ł�Œ���X���ʂ̈ړ���x������
			if (g_Cat.nowjump_flag > 0)
			{
				g_Cat.pos.x += g_Cat.dir.x / g_Cat.nowjump_flag;
			}
			else
			{
				g_Cat.pos.x += g_Cat.dir.x;
			}
		}
		else
		{
			//�����^�C�~���O�ŃW�����v���n�܂邽�߁A��Ԓi���ɉ����Ĕ��ł�Œ���X���ʂ̈ړ���x������
			if (g_Cat.nowjump_flag > 0)
			{
				g_Cat.pos.x += g_Cat.dir.x / g_Cat.nowjump_flag;
			}
			else
			{
				g_Cat.pos.x += g_Cat.dir.x;
			}
		}
	}
	//��ʊO�ւ͂����Ȃ��悤�ɂ���
	if (g_Cat.pos.x < CAT_SIZE_W/2)
	{
		g_Cat.pos.x = CAT_SIZE_W / 2;
		//�����l�܂Ŗ߂��Ă����甽�]����
		ChangeMoveFlag(&g_Cat);
	}
	else if (g_Cat.pos.x >= SCREEN_WIDTH * 6 - CAT_SIZE_W/2)
	{
		g_Cat.pos.x = SCREEN_WIDTH * 6 - CAT_SIZE_W / 2;
		//�I�[�l�܂ōs���Ă��܂����炫���甽�]����
		ChangeMoveFlag(&g_Cat);
	}
	//�W�����v�p���[
	g_Cat.pos.y -= g_Cat.jump_y;

	//�v���C���[�����E���x�𒴂�����
	if (g_Cat.pos.y <= g_Cat.limit_jump)
	{
		//��яオ��͂�0�ɂ���
		g_Cat.jump_y = 0;
	}
	////���ԃ|�C���g
	if (g_Cat.pos.x >= CAT_GOLL/2 && g_Cat.jump_flag == true)
	{
		g_Cat.half_flag = true;//���ԃ|�C���g�t���OON
	}
	////�S�[��//jump_flug�͏��u���b�N�ƐG��Ă��邩�����̂ŋ󒆃S�[���͂��Ȃ�
	if (g_Cat.pos.x >= CAT_GOLL && g_Cat.jump_flag == true)
	{
		g_Cat.goal_flag = true;//�S�[���t���OON

		//�X�R�A�V�[���ɑJ��
		SetScene(SCENE_SCORE);
	}
	//�L�����ɗ����Ă��܂����ꍇ
	if (g_Cat.pos.y >= SCREEN_HEIGHT)
	{
		//�Q�[���I�[�o�[
		SetScene(SCENE_GAMEOVER);
	}
}
void DrawCat()
{	
	D3DXVECTOR2 basePos = GetBase();
	//�e�N�X�`���̃Z�b�g
	GetDeviceContext()->PSSetShaderResources
	(0, 1, GetTexture(g_Cat.texNo));
	g_Cat.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//�X�v���C�g�̕`��
	DrawSpriteColorRotate(
		basePos.x + g_Cat.pos.x,
		basePos.y + g_Cat.pos.y,
		DRAW_SIZE,
		DRAW_SIZE,
		g_Cat.rot,
		g_Cat.col,
		g_Cat.patern,		
		1.0f / 8.0f,//��
		1.0f / 3.0f,//�c
		8//���̃p�^�[������
	);
}
//�\���̂̐擪�|�C���^��Ԃ��@�F���g����悤��
CAT *GetCat()
{
	return &g_Cat;
}

//�W�����v�t���O���擾
bool GetJumpFlag()
{
	return g_Cat.jump_flag;
}

//�W�����v�֐�
void CatJump(float jumpheight)
{
	//�W�����v

	/*	PlaySound(JumpSoundNo, 0);
		SetVolume(JumpSoundNo, 0.1f);*/

	//�L����яオ�鍂��
	//���݂̔L�̈ʒu����@collision�̒��ň����Ŗ�����i���@�~�@�u���b�N�̍����@���
	//���ɗ����Ȃ����яオ��o�O���C��
	//���������ȉ��ɔL���s���Ă��܂�����W�����v�͂��Ȃ�
	if (g_Cat.pos.y <= DEFO_SIZE_Y - DEFO_SIZE_X)
	{
		g_Cat.limit_jump = g_Cat.pos.y - (DRAW_SIZE * jumpheight);


		g_Cat.jump_y = JUMP;

		g_Cat.nowjump_flag = jumpheight;
		g_Cat.jump_flag = false;

		//�E�ɐi��ł�����
		if (g_Cat.move_flag == false)
		{
			g_Cat.patern = 8.0f;
		}
		else
			//���ɐi��ł�����
		{
			g_Cat.patern = 11.0f;
		}
	}
}

void ChangeMoveFlag(CAT* c)
{
	if (c->move_flag == true)
	{
		c->move_flag = false;
		g_Cat.dir *= -1;

	}
	else if (c->move_flag == false)
	{
		c->move_flag = true;
		g_Cat.dir *= -1;
	}
}

bool HalfWayFlag()
{
	return g_Cat.half_flag;
}
