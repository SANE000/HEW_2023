#include "main.h"
#include "renderer.h"
#include "Game.h"
#include "polygon.h"
#include "timer.h"
#include "etcUI.h"
#include "sound.h"
#include "result.h"
#include "StageSelect.h"
#include "texture.h"
#include "sprite.h"
#include "inputx.h"
#include "keyboard.h"
#include "scene.h"
#include "block.h"

static FIELD g_Field[FIELD_MAX];
static STAGE  g_InStage[STAGE_MAX];
static int	g_TextureNo;		// �e�N�X�`�����ʎq

static int	StageNum = 0;		// �X�e�[�W��
static int  FieldNum = 0;       // ���[���h��

static int	ClearNum = 0;       // �N���A������
static int  ClearStage = 0;
static int  ClearField = 0;

static int time = 0;

static bool World = true;



FIELD  InitData[] = {

	{true,D3DXVECTOR2(170, 290),D3DXVECTOR2(240, 130),0,3,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0},
	{true,D3DXVECTOR2(485, 290),D3DXVECTOR2(240, 130),0,1,D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),1},
	{true,D3DXVECTOR2(800, 290),D3DXVECTOR2(240, 130),0,0,D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),2},
	{true,D3DXVECTOR2(170, 450),D3DXVECTOR2(240, 130),0,0,D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),3},
	{true,D3DXVECTOR2(485, 450),D3DXVECTOR2(240, 130),0,0,D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),4},
	{true,D3DXVECTOR2(800, 450),D3DXVECTOR2(240, 130),0,0,D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),5},
	{true,D3DXVECTOR2(500, 500),D3DXVECTOR2(288, 162),0,0,D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),5}


};

STAGE  InitData1[] = {
	{false,D3DXVECTOR2(170, 250),D3DXVECTOR2(288, 162),0,0,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0},
	{false,D3DXVECTOR2(485, 250),D3DXVECTOR2(288, 162),0,0,D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f),1},
	{false,D3DXVECTOR2(800, 250),D3DXVECTOR2(288, 162),0,0,D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f),2},
	
	//{false,D3DXVECTOR2(170 + SCREEN_WIDTH, 250),D3DXVECTOR2(288, 162),0,0,D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),0},
	//{false,D3DXVECTOR2(485 + SCREEN_WIDTH, 250),D3DXVECTOR2(288, 162),0,0,D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),0},
	//{false,D3DXVECTOR2(800 + SCREEN_WIDTH, 250),D3DXVECTOR2(288, 162),0,0,D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),0},
	//
	//{false,D3DXVECTOR2(170 + (SCREEN_WIDTH * 2), 250),D3DXVECTOR2(288, 162),0,0,D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),0},
	//{false,D3DXVECTOR2(485 + (SCREEN_WIDTH * 2), 250),D3DXVECTOR2(288, 162),0,0,D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),0},
	//{false,D3DXVECTOR2(800 + (SCREEN_WIDTH * 2), 250),D3DXVECTOR2(288, 162),0,0,D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),0} ,
	//
	//{false,D3DXVECTOR2(170 + (SCREEN_WIDTH * 3), 250),D3DXVECTOR2(288, 162),0,0,D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),0},
	//{false,D3DXVECTOR2(485 + (SCREEN_WIDTH * 3), 250),D3DXVECTOR2(288, 162),0,0,D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),0},
	//{false,D3DXVECTOR2(800 + (SCREEN_WIDTH * 3), 250),D3DXVECTOR2(288, 162),0,0,D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),0},

	//{false,D3DXVECTOR2(170 + (SCREEN_WIDTH * 4), 250),D3DXVECTOR2(288, 162),0,0,D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),0},
	//{false,D3DXVECTOR2(485 + (SCREEN_WIDTH * 4), 250),D3DXVECTOR2(288, 162),0,0,D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),0},
	//{false,D3DXVECTOR2(800 + (SCREEN_WIDTH * 4), 250),D3DXVECTOR2(288, 162),0,0,D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),0}
};




HRESULT InitStageSelect()
{
	g_TextureNo = LoadTexture((char*)"data/TEXTURE/field.png");


	for (int i = 0; i < FIELD_MAX; i++) {
		g_Field[i] = InitData[i];
		g_Field[i].texNo = LoadTexture((char*)"data/TEXTURE/field_0.png");
	}

	
	
	for (int i = 0; i < FIELD_MAX * 3; ) {
		for (int n = 0; n < 3; i++, n++) {
			g_InStage[i] = InitData1[n];
			g_InStage[i].texNo = LoadTexture((char*)"data/TEXTURE/stage.png");
		}
	}
	StageNum = 0;
	FieldNum = 0;
	
	
	ClearNum = SetClear() + 1;

	if (ClearNum > 20)
	{
		ClearNum = 20;
	}

	ClearStage = ClearNum;
	ClearField = ClearNum / 3;

	
	for (int i = 0; i < ClearNum + 1; i++)
	{
		g_InStage[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	}
	


	return S_OK;
}

void UnInitStageSelect()
{
	//�X�R�A����߂��Ă����Ƃ��ɕ\������Ȃ��Ȃ邽��
	//���ŃR�����g�A�E�g���Ă����܂���
	//UninitTexture();
}

void UpdateStageSelect()
{

	if (time > 0)
	{
		time -= 1;
	}
	if (World == true) {//1�`6�ʂ̑I��
		//�E���ň�E�Ɉړ�
		//�I�𒆂̃X�e�[�W�𓧖��x��0.5
		//���̃X�e�[�W�̓����x��1.0
		if (Keyboard_IsKeyDown(KK_RIGHT) && time <= 0 || GetThumbLeftX(0) > 0 && time <= 0) {
			g_Field[FieldNum].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			FieldNum++;
			if (FieldNum > (ClearField)) {
				FieldNum = 0;
			}
			g_Field[FieldNum].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			time = 10;
		}
		if (Keyboard_IsKeyDown(KK_LEFT) && time <= 0 || GetThumbLeftX(0) < 0 && time <= 0) {
			//�����ň�E�Ɉړ�
			//�I�𒆂̃X�e�[�W�𓧖��x��0.5
			//���̃X�e�[�W�̓����x��1.0
			g_Field[FieldNum].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			FieldNum--;
			if (FieldNum < 0) {
				FieldNum = (ClearField);
			}
			g_Field[FieldNum].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			time = 10;
		}


		if (Keyboard_IsKeyDown(KK_SPACE) && time <= 0 || IsButtonTriggered(0, XINPUT_GAMEPAD_B) && time <= 0) {
			for (int i = 0; i < FIELD_MAX; i++) {
				g_Field[i].use = false;
			}
			for (int i = 0; i < STAGE_MAX; i++) {
				g_InStage[i].use = true;
			}

			StageNum = FieldNum * 3;
			g_InStage[StageNum].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			World = false;
			time = 20;
		}
	}
	else if (World == false) {
		//�E���ň�E�Ɉړ�
		//�I�𒆂̃X�e�[�W�𓧖��x��0.5
		//���̃X�e�[�W�̓����x��1.0
		if (Keyboard_IsKeyDown(KK_RIGHT) && time <= 0 || GetThumbLeftX(0) > 0 && time <= 0) {
			g_InStage[StageNum].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			StageNum++;
			if (StageNum > ClearStage) 
			{
				StageNum = ClearStage;
			}
			if (StageNum > FieldNum * 3 + 2) {
				StageNum = FieldNum * 3 + 2;
			}
			
			g_InStage[StageNum].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			time = 10;
		}
		if (Keyboard_IsKeyDown(KK_LEFT) && time <= 0 || GetThumbLeftX(0) < 0 && time <= 0) {
			//�����ň���Ɉړ�
			//�I�𒆂̃X�e�[�W�𓧖��x��0.5
			//���̃X�e�[�W�̓����x��1.0
			g_InStage[StageNum].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			StageNum--;
			if (StageNum < FieldNum * 3) {
				StageNum = FieldNum * 3;
			}
			g_InStage[StageNum].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			time = 10;
		}

		if (Keyboard_IsKeyDown(KK_ENTER) && time <= 0 || IsButtonTriggered(0, XINPUT_GAMEPAD_B) && time <= 0) {
			//Enter�ŃV���b�v��	
			SetScene(SCENE_SHOP);
			World = true;
			time = 20;
		}


		if (Keyboard_IsKeyDown(KK_B) && time <= 0 || IsButtonTriggered(0, XINPUT_GAMEPAD_B) && time <= 0) {
			for (int i = 0; i < FIELD_MAX; i++) {
				g_Field[i].use = true;
			}
			for (int i = 0; i < STAGE_MAX; i++) {
				g_InStage[i].use = false;
			}
			time = 20;
			g_InStage[StageNum].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			World = true;
		}
			//�㉺�̖��Ŗʂ�ύX
		if (Keyboard_IsKeyDown(KK_UP) && time <= 0 || GetThumbLeftY(0) > 0 && time <= 0) {
			time = 20;
			g_InStage[StageNum].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			FieldNum--;
			StageNum = FieldNum * 3;
			g_InStage[FieldNum * 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			if (FieldNum < 0) {
				FieldNum = (ClearField);
			}
		}
		else if (Keyboard_IsKeyDown(KK_DOWN) && time <= 0 || GetThumbLeftY(0) < 0 && time <= 0) {
			time = 20;
			g_InStage[StageNum].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			FieldNum++;
			StageNum = FieldNum * 3;
			g_InStage[FieldNum * 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			if (FieldNum > (ClearField)) {
				FieldNum = 0;
			}
		}
		
	}

}

void DrawStageSelect()
{
	GetDeviceContext()->PSSetShaderResources
	(0, 1, GetTexture(g_TextureNo));
	DrawSpriteColorRotate
	(
		SCREEN_WIDTH / 2,
		SCREEN_HEIGHT / 2,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		0,
		D3DXCOLOR(0.7f, 0.7f, 0.7f,0.7f),
		FieldNum,
		1.0f / 6.0f,//��
		1.0f,//�c
		6//������
	);


	for (int i = 0; i < FIELD_MAX; i++) {
		GetDeviceContext()->PSSetShaderResources
		(0, 1, GetTexture(g_Field[i].texNo));

		if (g_Field[i].use == true) {

			DrawSpriteColorRotate
			(
				g_Field[i].pos.x,
				g_Field[i].pos.y,
				g_Field[i].size.x,
				g_Field[i].size.y,
				g_Field[i].rot,
				g_Field[i].col,
				g_Field[i].Patern,
				1.0f / 6.0f,//��
				1.0f,//�c
				6//������
			);
		}
	}




	for (int i = FieldNum * 3; i < FieldNum * 3 + 3; i++) {
		GetDeviceContext()->PSSetShaderResources
		(0, 1, GetTexture(g_InStage[i].texNo));

		if (g_InStage[i].use == true) {

			DrawSpriteColorRotate
			(
				g_InStage[i].pos.x,
				g_InStage[i].pos.y,
				g_InStage[i].size.x,
				g_InStage[i].size.y,
				g_InStage[i].rot,
				g_InStage[i].col,
				g_InStage[i].Patern,
				1.0f / 3.0f,//��
				1.0f,//�c
				3//������
			);
		}
	}

}

//�`�ʂ̃Z�b�g
int SetField()
{
	return FieldNum;
}

//�X�e�[�W�̃Z�b�g
int SetStage()
{
	return StageNum % 3;
}
