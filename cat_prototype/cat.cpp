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
#include "timer.h"
//�O���[�o���ϐ�
//int JumpSoundNo = 0;
//���Ԑ؂�ɂȂ����Ƃ��̃��Z�b�g�����p�ϐ�
bool Reset = false;
//�v���C���[�I�u�W�F�N�g
static CAT g_Cat;
static MOVE_BLOCK *m_block = GetMoveBlock();

HRESULT InitCat()
{
	//�e�N�X�`�����[�h �摜�̖��O�����悤
	g_Cat.texNo = LoadTexture((char*)"data\\texture\\neko.png");
	//�\���̂̏�����
	g_Cat.pos.x = DEFO_SIZE_X;
	g_Cat.pos.y = CAT_INIT_Y;
	g_Cat.move_flag = false;
	g_Cat.jump_flag = false;
	g_Cat.jump_y = 0.0f;
	g_Cat.limit_jump = 0.0f;
	g_Cat.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Cat.patern = 0.0f;
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
	g_Cat.patern += 0.03;
	if (g_Cat.patern >= 2.0f)
	{
		g_Cat.patern -= 2.0f;
	}
	Reset = GetReset();
	//�󒆂ɕ����Ă���Ƃ������d�͂̉e��
	if (g_Cat.jump_flag == false)
	{
		g_Cat.pos.y += GRAV;
	}
	//�����ňړ�(�ǂɂԂ���or�����l�܂Ŗ߂����甽�])
	if (g_Cat.move_flag == false)
	{
		//�����^�C�~���O�ŃW�����v���n�܂邽�߁A��Ԓi���ɉ����Ĕ��ł�Œ���X���ʂ̈ړ���x������
		if (g_Cat.nowjump_flag > 0)
		{
			g_Cat.pos.x += WALK / g_Cat.nowjump_flag;
		}
		else
		{
			g_Cat.pos.x += WALK;
		}
	}
	else
	{
		//�����^�C�~���O�ŃW�����v���n�܂邽�߁A��Ԓi���ɉ����Ĕ��ł�Œ���X���ʂ̈ړ���x������
		if (g_Cat.nowjump_flag > 0)
		{
			g_Cat.pos.x -= WALK / g_Cat.nowjump_flag;
		}
		else
		{
			g_Cat.pos.x -= WALK;
		}
	}
	//��ʊO�ւ͂����Ȃ��悤�ɂ���
	if (g_Cat.pos.x < CAT_SIZE_W/2)
	{
		g_Cat.pos.x = CAT_SIZE_W / 2;
		//�����l�܂Ŗ߂��Ă����甽�]����
		ChangeMoveFlag(&g_Cat);
	}
	//////////�L�̃W�����v�͍�������\��/////////////////////////////////////////////////////
	//�W�����v�p���[
	g_Cat.pos.y -= g_Cat.jump_y;

	//�v���C���[�����E���x�𒴂�����
	if (g_Cat.pos.y <= g_Cat.limit_jump)
	{
		//��яオ��͂�0�ɂ���
		g_Cat.jump_y = 0;
	}
	
	////�S�[��//jump_flug�͏��u���b�N�ƐG��Ă��邩�����̂ŋ󒆃S�[���͂��Ȃ�
	if (g_Cat.pos.x >= CAT_GOLL && g_Cat.jump_flag == true)
	{
		////�e�X�g�����珉���ʒu�ɖ߂�
		//g_Cat.pos.x = CAT_INIT_X;
		//g_Cat.pos.y = CAT_INIT_Y;
		g_Cat.goal_flag = true;//�S�[���t���OON

		//�X�R�A�V�[���ɑJ��
		SetScene(SCENE_SCORE);
	}
	//�L�����ɗ����Ă��܂����ꍇ
	if (g_Cat.pos.y >= SCREEN_HEIGHT)
	{
		//�e�X�g�����珉���ʒu�ɖ߂�
		g_Cat.pos.x = CAT_INIT_X;
		g_Cat.pos.y = CAT_INIT_Y;
	}
	//==============================================================================================================================
	//		//���Ԑ؂ꏈ��              ///////////////////////////////////////////////////////////////////////////////////////////
	//==============================================================================================================================
	if (GetLimitFrame() < 0)
	{
		//�e�X�g�����珉���ʒu�ɖ߂�,jump_flug�������ݒ�ɖ߂�
		g_Cat.pos.x = CAT_INIT_X;
		g_Cat.pos.y = CAT_INIT_Y;
		g_Cat.jump_flag = false;
		//���Ԃ��e�X�g�Ȃ̂Ŗ߂��B�Q�[���I�[�o�[�������V���b�v�ɖ߂鏈���Ƃ����߂���
		//���Z�b�g����ƃu���b�N�͏����邪�g���Ă��܂������͖߂��Ă��Ȃ��̂ł��������������ł�
		//11/18��
		Reset = true;
		//MOVE�u���b�N���S����������
		for (int i = 0; i < MOVE_BLOCK_MAX; i++)
		{
			if (m_block[i].use == true)
			{
				m_block[i].use = false;
				//�S�Ă�false�ɂ��邽��break�͂��Ȃ�
			}
		}
		
	}
}
void DrawCat()
{	
	D3DXVECTOR2 basePos = GetBase();
	//�e�N�X�`���̃Z�b�g
	GetDeviceContext()->PSSetShaderResources
	(0, 1, GetTexture(g_Cat.texNo));
	g_Cat.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//�X�v��s�C�g�̕`��
	DrawSpriteColorRotate(
		basePos.x + g_Cat.pos.x,
		basePos.y + g_Cat.pos.y,
		DRAW_SIZE,
		DRAW_SIZE,
		g_Cat.rot,
		g_Cat.col,
		g_Cat.patern,		
		1.0f / 2.0f,//��
		1.0f,//�c
		2//���̃p�^�[������
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
	g_Cat.limit_jump = g_Cat.pos.y - ( SIZE * jumpheight);


	g_Cat.jump_y = JUMP;

	g_Cat.nowjump_flag = jumpheight;
	g_Cat.jump_flag = false;
}

void ChangeMoveFlag(CAT* c)
{
	if (c->move_flag == true)
	{
		c->move_flag = false;
	}
	else if (c->move_flag == false)
	{
		c->move_flag = true;
	}
}
//���Ԃ����Ƃɖ߂��t���O
bool ResetTime()
{
	return Reset;
}
