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
//�O���[�o���ϐ�
//int JumpSoundNo = 0;

//�v���C���[�I�u�W�F�N�g
static CAT g_Cat;
static MOVE_BLOCK *m_block = GetMoveBlock();

HRESULT InitCat()
{
	//�e�N�X�`�����[�h �摜�̖��O�����悤
	g_Cat.texNo = LoadTexture((char*)"data\\texture\\neko2.png");
	//�\���̂̏�����
	g_Cat.pos.x = DEFO_SIZE_X;
	g_Cat.pos.y = CAT_INIT_Y;
	g_Cat.move_flag = false;
	g_Cat.jump_flag = false;
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
	//�����ňړ�(�ǂɂԂ���or�����l�܂Ŗ߂����甽�])
	if (g_Cat.move_flag == false)
	{
		//�E�Ɍ������ĕ����L�A�j��
		g_Cat.patern += 0.04;
		if (g_Cat.patern > 2.0f)
		{
			g_Cat.patern = 0.0f;
		}
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
		//���Ɍ������ĕ����L�A�j��
		g_Cat.patern += 0.04;
		if (g_Cat.patern > 4.0f || g_Cat.patern < 2.0f)
		{
			g_Cat.patern = 2.0f;
		}
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
		//�Q�[���I�[�o�[�̑���
		SetScene(SCENE_SHOP);
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
		1.0f / 4.0f,//��
		1.0f,//�c
		4//���̃p�^�[������
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
		g_Cat.limit_jump = g_Cat.pos.y - (SIZE * jumpheight);


		g_Cat.jump_y = JUMP;

		g_Cat.nowjump_flag = jumpheight;
		g_Cat.jump_flag = false;
	}
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

bool HalfWayFlag()
{
	return g_Cat.half_flag;
}
