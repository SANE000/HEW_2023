#include "player.h"
#include "main.h"
#include "block.h"
#include "inputx.h"
#include "keyboard.h"
#include "texture.h"
#include "sprite.h"
#include "Scene.h"
#include "sound.h"
#include "collision.h"
#include "camera.h"
//�}�N����`
#define PLAYER_SIZE_W (48)
#define PLAYER_SIZE_H (48)
#define PLAYER_INIT_X (PLAYER_SIZE_W/2)
#define PLAYER_INIT_Y (PLAYER_SIZE_H/2)
#define MOVE_X (PLAYER_SIZE_W)
#define MOVE_Y (PLAYER_SIZE_H)
#define BULLET_WAIT (38)
//�v���g�^�C�v�錾


///////////////////////�O���[�o��
static int time = 0;
//int JumpSoundNo = 0;
//�v���C���[�I�u�W�F�N�g
static PLAYER g_Player;
///

HRESULT InitPlayer()
{
	//�e�N�X�`�����[�h �摜�̖��O�����悤
	g_Player.texNo = LoadTexture((char*)"data\\texture\\player.png");
	//�\���̂̏�����
	g_Player.pos.x = PLAYER_INIT_X;
	g_Player.pos.y = PLAYER_INIT_Y;
	g_Player.SetPos.x = g_Player.pos.x;
	g_Player.SetPos.y = g_Player.pos.y + PLAYER_SIZE_H;
	g_Player.w = PLAYER_SIZE_W;
	g_Player.h = PLAYER_SIZE_H;
	g_Player.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Player.patern = 0.0f;
	g_Player.bwait = 0;
	//�g�p���t���O���I���ɂ���
	g_Player.use = true;


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
	if (time > 0)
	{
		time -= 1;
	}
	//�����l���獶�ւ͂����Ȃ��悤�ɂ���
	if (g_Player.pos.x <= PLAYER_INIT_X)
	{
		g_Player.pos.x = PLAYER_INIT_X;
	}
	//�I�[�l����E�ւ������Ȃ��悤�ɂ���
	//else if (g_Player.pos.x >= SCREEN_WIDTH - PLAYER_INIT_X)
	//{
	//	g_Player.pos.x = SCREEN_WIDTH - PLAYER_INIT_X;
	//}
	if (g_Player.bwait > 0)
	{
		g_Player.bwait -= 1;
	}
	//�����l�����ւ͂����Ȃ��悤�ɂ���
	if (g_Player.pos.y <= PLAYER_INIT_Y)
	{
		g_Player.pos.y = PLAYER_INIT_Y;
	}
	//�I�[�l���牺�ւ������Ȃ��悤�ɂ���
	else if (g_Player.pos.y >= SCREEN_HEIGHT - PLAYER_INIT_Y)
	{
		g_Player.pos.y = SCREEN_HEIGHT - PLAYER_INIT_Y;
	}

	//����֌W
	//�㉺���E���L�[�ňړ�����
	if (Keyboard_IsKeyDown(KK_D) || GetThumbLeftX(0) > 0 && time <= 0)
	{//�E
		g_Player.pos.x += MOVE_X;
		time = WAIT_TIME;
	}
	else if (Keyboard_IsKeyDown(KK_A)|| GetThumbLeftX(0) < 0 && time <= 0)
	{//��
		g_Player.pos.x -= MOVE_X;
		time = WAIT_TIME;
	}
	//�㉺�̈ړ��ɂ���ăo�O���������������獡�͎��߂Ă���
	else if (Keyboard_IsKeyDown(KK_S) || GetThumbLeftY(0) < 0 && time <= 0)
	{//��
		g_Player.pos.y += MOVE_Y;
		time = WAIT_TIME;
	}
	else if (Keyboard_IsKeyDown(KK_W) || GetThumbLeftY(0) > 0 && time <= 0)
	{//��
		g_Player.pos.y -= MOVE_Y;
		time = WAIT_TIME;
	}

	//�v���r���[�u���b�N����]
	if (Keyboard_IsKeyDown(KK_Z) || IsButtonTriggered(0, XINPUT_GAMEPAD_X) && time <= 0)
	{
		GetPreviewBlock()->rot += 90;
		if (GetPreviewBlock()->rot == 360)
		{
			GetPreviewBlock()->rot = 0;
		}
		time = WAIT_TIME;
	}

	//SPACE�L�[�Ńu���b�N���v���C���[�̉������֎ˏo����
	//�L�̑�����`��(���Ƃł�����o���b�g���Q�l�ɂ���)
	g_Player.SetPos = g_Player.pos;
	if (Keyboard_IsKeyDown(KK_SPACE) || IsButtonTriggered(0, XINPUT_GAMEPAD_B) && g_Player.bwait == 0)
	{
		if(FalseExistCheck() == true)
		SetMoveBlock();
		//�v����
		g_Player.bwait = BULLET_WAIT;
	}

	//���Z�b�g�L�[
	if (Keyboard_IsKeyDown(KK_R)||IsButtonTriggered(0, XINPUT_GAMEPAD_START) &&time<=0)
	{
		SetScene(SCENE_SHOP);
		time = WAIT_TIME;
	}
}
void DrawPlayer()
{
	////�e�N�X�`���̃Z�b�g
	//GetDeviceContext()->PSSetShaderResources
	//(0, 1, GetTexture(g_Player.texNo));
	//g_Player.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	////�X�v���C�g�̕`��
	//DrawSpriteColorRotate(
	//	g_Player.pos.x,
	//	g_Player.pos.y,
	//	g_Player.w,
	//	g_Player.h,
	//	g_Player.rot,
	//	g_Player.col,
	//	g_Player.patern,		
	//	1.0f,//��
	//	1.0f,//�c
	//	1//���̃p�^�[������
	//);
}
//�\���̂̐擪�|�C���^��Ԃ��@�F���g����悤��
PLAYER *GetPlayer()
{
	return &g_Player;
}