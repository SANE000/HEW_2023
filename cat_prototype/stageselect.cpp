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
static int	g_TextureNo;		// テクスチャ識別子
static int	StageNum = 0;		// テクスチャ識別子
static int  FieldNum = 0;
static int time = 0;

static float num;


FIELD  InitData[] = {

	{true,D3DXVECTOR2(170, 155),D3DXVECTOR2(288, 162),0,3,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0},
	{true,D3DXVECTOR2(485, 155),D3DXVECTOR2(288, 162),0,1,D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),1},
	{true,D3DXVECTOR2(800, 155),D3DXVECTOR2(288, 162),0,0,D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),2},
	{true,D3DXVECTOR2(170, 400),D3DXVECTOR2(288, 162),0,0,D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),3},
	{true,D3DXVECTOR2(485, 400),D3DXVECTOR2(288, 162),0,0,D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),4},
	{true,D3DXVECTOR2(800, 400),D3DXVECTOR2(288, 162),0,0,D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),5}

};

STAGE  InitData1[] = {
	{false,D3DXVECTOR2(170, 250),D3DXVECTOR2(288, 162),0,0,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0},
	{false,D3DXVECTOR2(485, 250),D3DXVECTOR2(288, 162),0,0,D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),1},
	{false,D3DXVECTOR2(800, 250),D3DXVECTOR2(288, 162),0,0,D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),2},
	
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
		g_Field[i].texNo = LoadTexture((char*)"data/TEXTURE/field.png");
	}


	
	for (int i = 0; i < STAGE_MAX; i++) {
		g_InStage[i] = InitData1[i];
		g_InStage[i].texNo = LoadTexture((char*)"data/TEXTURE/stage.png");
	}


	return S_OK;
}

void UnInitStageSelect()
{
	UninitTexture();
}

void UpdateStageSelect()
{
	if (time > 0)
	{
		time -= 1;
	}
	if (g_Field[0].use == true) {//1～6面の選択
		//右矢印で一つ右に移動
		//選択中のステージを透明度を0.5
		//次のステージの透明度を1.0
		if (Keyboard_IsKeyDown(KK_RIGHT) && time <= 0 || GetThumbLeftX(0) > 0 && time <= 0) {
			g_Field[FieldNum].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			FieldNum++;
			if (FieldNum > 5) {
				FieldNum = 0;
			}
			g_Field[FieldNum].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			time = 10;
		}
		if (Keyboard_IsKeyDown(KK_LEFT) && time <= 0 || GetThumbLeftX(0) < 0 && time <= 0) {
			//←矢印で一つ右に移動
			//選択中のステージを透明度を0.5
			//次のステージの透明度を1.0
			g_Field[FieldNum].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			FieldNum--;
			if (FieldNum < 0) {
				FieldNum = 5;
			}
			g_Field[FieldNum].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			time = 10;
		}


		if (Keyboard_IsKeyDown(KK_SPACE) && time <= 0 || IsButtonTriggered(0, XINPUT_GAMEPAD_B) && time <= 0) {
			for (int i = 0; i < FIELD_MAX; i++) {
				g_Field[i].use = false;
			}
			for (int i = 0; i < 3; i++) {
				g_InStage[i].use = true;
			}
			time = 20;
		}
	}
	else if (g_InStage[0].use == true) {
		//右矢印で一つ右に移動
		//選択中のステージを透明度を0.5
		//次のステージの透明度を1.0
		if (Keyboard_IsKeyDown(KK_RIGHT) && time <= 0 || GetThumbLeftX(0) > 0 && time <= 0) {
			g_InStage[StageNum].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			StageNum++;
			if (StageNum > 2) {
				StageNum = 0;
			}
			g_InStage[StageNum].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			time = 10;
		}
		if (Keyboard_IsKeyDown(KK_LEFT) && time <= 0 || GetThumbLeftX(0) < 0 && time <= 0) {
			//←矢印で一つ右に移動
			//選択中のステージを透明度を0.5
			//次のステージの透明度を1.0
			g_InStage[StageNum].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			StageNum--;
			if (StageNum < 0) {
				StageNum = 2;
			}
			g_InStage[StageNum].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			time = 10;
		}

		if (Keyboard_IsKeyDown(KK_ENTER) && time <= 0 || IsButtonTriggered(0, XINPUT_GAMEPAD_B) && time <= 0) {
			//Enterでショップへ	
			SetScene(SCENE_SHOP);
			time = 20;
		}
		
		//上下の矢印で面を変更
		if (Keyboard_IsKeyDown(KK_UP) && time <= 0 || GetThumbLeftY(0) > 0 && time <= 0) {
			time = 20;
			FieldNum--;
			if (FieldNum < 0) {
				FieldNum = 5;
			}
		}
		else if (Keyboard_IsKeyDown(KK_DOWN) && time <= 0 || GetThumbLeftY(0) < 0 && time <= 0) {
			time = 20;
			FieldNum++;
			if (FieldNum > 5) {
				FieldNum = 0;
			}
		}

	}

	num += 0.1f;
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
		D3DXCOLOR(1.0f,1.0f,1.0f,0.5f),
		FieldNum,
		1.0f / 6.0f,//横
		1.0f,//縦
		6//総枚数
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
				1.0f / 6.0f,//横
				1.0f,//縦
				6//総枚数
			);
		}
	}

	for (int i = 0; i < STAGE_MAX; i++) {
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
				1.0f / 3.0f,//横
				1.0f,//縦
				3//総枚数
			);
		}
	}

}

//～面のセット
int SetField()
{
	return FieldNum;
}

//ステージのセット
int SetStage()
{
	return StageNum;
}