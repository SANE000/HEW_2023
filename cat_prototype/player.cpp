#include "player.h"
#include "main.h"
#include "block.h"
#include "blockpreview.h"
#include "inputx.h"
#include "keyboard.h"
#include "texture.h"
#include "sprite.h"
#include "Scene.h"
#include "sound.h"
#include "timer.h"
#include "collision.h"
#include "camera.h"
#include "preview_collision.h"

//�}�N����`
#define BULLET_WAIT (28)
#define ROT_WAIT (10)
//�v���g�^�C�v�錾

///////////////////////�O���[�o��
static int time = 0;
//int JumpSoundNo = 0;
//�v���C���[�I�u�W�F�N�g
static PLAYER g_Player;
//�X�N���[�����͓������Ȃ��΍�
static CAMERA_2D *g_Camera = GetCamera();
//1�X�e�[�W�ɉ��u���b�N���g������
static int blockscore = 0;
///

HRESULT InitPlayer()
{
	//�e�N�X�`�����[�h �摜�̖��O�����悤
	g_Player.texNo = LoadTexture((char*)"data\\texture\\shop_cursor.png");
	//�\���̂̏�����
	g_Player.pos.x = DEFO_SIZE_X;
	g_Player.pos.y = DEFO_SIZE_X;
	g_Player.SetPos.x = g_Player.pos.x;
	g_Player.SetPos.y = g_Player.pos.y + DRAW_SIZE;
	g_Player.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Player.patern = 0.0f;
	g_Player.bwait = 0;
	//�g�p���t���O���I���ɂ���
	g_Player.use = true;

	blockscore = 0;


	//�T�E���h�̃��[�h
	//char filename[] = "data\\SE\\boyoyon.wav";
	//JumpSoundNo = LoadSound(filename);
	//HRESULT�ɒl��Ԃ��Đ���I���������Ƃ�A������
	return S_OK;
}
//�I������
void UnInitPlayer()
{

}
//�X�V����
void UpdatePlayer()
{
	//�����݂̃v���C���[�̍��W���L�����Ă���
	D3DXVECTOR2 now_playerpos = g_Player.pos;

	if (time > 0)
	{
		time -= 1;
	}
	//�����l���獶�ւ͂����Ȃ��悤�ɂ���
	if (g_Player.pos.x <= DEFO_SIZE_X)
	{
		g_Player.pos.x = DEFO_SIZE_X;
	}
	else if (g_Player.pos.x >= SCREEN_WIDTH * 6 - DEFO_SIZE_X)
	{
		g_Player.pos.x = SCREEN_WIDTH * 6 - DEFO_SIZE_X;
	}

	if (g_Player.bwait > 0)
	{
		g_Player.bwait -= 1;
	}
	//�����l�����ւ͂����Ȃ��悤�ɂ���
	if (g_Player.pos.y <= DEFO_SIZE_X)
	{
		g_Player.pos.y = DEFO_SIZE_X;
	}
	//�I�[�l���牺�ւ������Ȃ��悤�ɂ���
	else if (g_Player.pos.y >= SCREEN_HEIGHT - DEFO_SIZE_X)
	{
		g_Player.pos.y = SCREEN_HEIGHT - DEFO_SIZE_X;
	}

	//����֌W
	//��ʃX�N���[�����̓v���C���[�̑���͍s���Ȃ��悤�ɂ���
	if (g_Camera->moveLeft == false && g_Camera->moveRight == false)
	{
		//�㉺���E���L�[�ňړ�����
		if (Keyboard_IsKeyDown(KK_D) && time <= 0 || GetThumbLeftX(0) > 0 && time <= 0)
		{//�E
			g_Player.pos.x += DRAW_SIZE;
			time = WAIT_TIME;
		}
		else if (Keyboard_IsKeyDown(KK_A) && time <= 0 || GetThumbLeftX(0) < 0 && time <= 0)
		{//��
			g_Player.pos.x -= DRAW_SIZE;
			time = WAIT_TIME;
		}
		//�㉺�̈ړ�
		else if (Keyboard_IsKeyDown(KK_S) && time <= 0 || GetThumbLeftY(0) < 0 && time <= 0)
		{//��
			g_Player.pos.y += DRAW_SIZE;
			time = WAIT_TIME;
		}
		else if (Keyboard_IsKeyDown(KK_W) && time <= 0 || GetThumbLeftY(0) > 0 && time <= 0)
		{//��
			g_Player.pos.y -= DRAW_SIZE;
			time = WAIT_TIME;
		}

		//�v���r���[�u���b�N����]
		if (Keyboard_IsKeyDown(KK_Z) && g_Player.bwait == 0 || IsButtonTriggered(0, XINPUT_GAMEPAD_X) && g_Player.bwait == 0)
		{
			GetPreviewBlock()->rot += 90;
			if (GetPreviewBlock()->rot == 360)
			{
				GetPreviewBlock()->rot = 0;
			}
			g_Player.bwait = ROT_WAIT;
		}

		//SPACE�L�[�Ńu���b�N���v���C���[�̉������֎ˏo����
		//�L�̑�����`��(���Ƃł�����o���b�g���Q�l�ɂ���)
		g_Player.SetPos = g_Player.pos;
		if (Keyboard_IsKeyDown(KK_SPACE) && g_Player.bwait == 0 || IsButtonTriggered(0, XINPUT_GAMEPAD_B) && g_Player.bwait == 0)
		{
			if (FalseExistCheck() == true)
			{
				blockscore++;//�u���b�N�����g������

				SetMoveBlock();

			}
			//�v����
			g_Player.bwait = BULLET_WAIT;

		}

		//�܂Ƃ��I��
		if (GetCat()->tumetogi_flag == true && Keyboard_IsKeyDown(KK_X) || IsButtonPressed(0, XINPUT_GAMEPAD_X))
		{
			GetCat()->tumetogi_flag = false;
		}

		//���Z�b�g�L�[
		if (Keyboard_IsKeyDown(KK_R) && time <= 0 || IsButtonTriggered(0, XINPUT_GAMEPAD_START) && time <= 0)
		{
			SetScene(SCENE_SHOP);
			time = WAIT_TIME;
		}
		//���Ԑ؂�Q�[���I�[�o�[
		if (GetLimitFrame() < 0)
		{
			SetScene(SCENE_GAMEOVER);
		}

		//�u���b�N�v���r���[�X�V
		UpdateBlockPreview(g_Player.pos);

		//�v���r���[�u���b�N���u���b�N�ɂ߂肱��ł�����
		if (PreviewCollisionCheck() == true)
		{
			//�v���C���[�̍��W���ŏ��̏�Ԃɖ߂���
			g_Player.pos = now_playerpos;

			//�u���b�N�v���r���[�X�V
			UpdateBlockPreview(g_Player.pos);
		}


	}
}
void DrawPlayer()
{
	//�e�N�X�`���̃Z�b�g
	D3DXVECTOR2 basePos = GetBase();
	GetDeviceContext()->PSSetShaderResources
	(0, 1, GetTexture(g_Player.texNo));
	g_Player.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//�X�v���C�g�̕`��
	DrawSpriteColorRotate(
		g_Player.pos.x + basePos.x,
		g_Player.pos.y,
		DRAW_SIZE,
		DRAW_SIZE,
		g_Player.rot,
		g_Player.col,
		g_Player.patern,		
		1.0f,//��
		1.0f,//�c
		1//���̃p�^�[������
	);
}
//�\���̂̐擪�|�C���^��Ԃ��@�F���g����悤��
PLAYER *GetPlayer()
{
	return &g_Player;
}

//�g�����u���b�N�̐��𒲂ׂ邽�߂Ɏg��
int BlockScore()
{
	return blockscore;
}

