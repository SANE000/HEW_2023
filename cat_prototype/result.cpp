
#include "texture.h"
#include "sprite.h"
#include "cat.h"
#include "player.h"
#include "timer.h"
#include "result.h"
#include "main.h"
#include "inputx.h"
#include "keyboard.h"
#include "scene.h"
#include "stageselect.h"


//==========================================
//グローバル変数
//==========================================
static int g_TextureNo = 0;	// テクスチャ識別子
static int TextureBGNo = 0;	// テクスチャ識別子
static int TextureSNo = 0;	// テクスチャ識別子
static int TextureANo = 0;	// テクスチャ識別子
static int TextureBNo = 0;	// テクスチャ識別子
static int g_Time = 0;
static int time = 0;
static int g_Block = 0;
//Clear←この値をいじれば好きなステージを選べるようになる
//初期値を0に設定して順番通りにプレイすればバグは起きない
//デバック用は99に設定すればどこでもプレイできます
static int clear = 99;
//
int Score = 0;
int rank[21];

HRESULT InitResult()
{
	//タイトル画面用テクスチャの読み込み
	g_TextureNo = LoadTexture((char*)"data/TEXTURE/time.png");
	TextureBGNo = LoadTexture((char*)"data/TEXTURE/Result_alpha_bg.png");
	TextureSNo = LoadTexture((char*)"data/TEXTURE/Result_alpha_s.png");
	TextureANo = LoadTexture((char*)"data/TEXTURE/Result_alpha_a.png");
	TextureBNo = LoadTexture((char*)"data/TEXTURE/Result_alpha_b.png");

	return S_OK;
}

void UninitResult()
{
	////

}

void UpdateResult()
{
	if (time > 0)
	{
		time -= 1;
	}
	//スコア計算//ココプランナーに決めてもらうの忘れてた
	if (BlockScore() <= 6 && ResultTimer() <= 80)
	{//Sランク
		Score = SCORE::SCORE_S;
	}
	else if (BlockScore() <= 8 && ResultTimer() <= 100)
	{//Aランク
		Score = SCORE::SCORE_A;
	}
	else
	{//Bランク
		Score = SCORE::SCORE_B;
	}
	if (Keyboard_IsKeyDown(KK_ENTER) && time <= 0 || IsButtonTriggered(0, XINPUT_GAMEPAD_B) && time <= 0)//ENTERキー押したら
	{
		rank[(SetField() * 3) + SetStage()] = Score;

		//例　2面の2ステージ  1*3 + 1 = 4 (0,1,2,3,4)の5番目のステージである 2-2(中の数字的に0から始まるので1-1をクリアした時だけクリアが1足される)
		if (clear == (SetField() * 3) + SetStage() - 1)
		{
			clear += 1;
		}
		time = WAIT_TIME;
		//ショップシーンに遷移//ステージ選択が反映したらそっちにシーン遷移
		SetScene(SCENE_SELECT);
	}
}

void DrawResult()
{
	{
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(TextureBGNo));//&Result_alpha_bg);
		//サイズを気を付けよう。
		static float patern = 0;
		DrawSpriteColorRotate(
			SCREEN_WIDTH / 2,
			SCREEN_HEIGHT / 2,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			0,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			0,//アニメーション番号背景だから変わらない
			1.0f,//横サイズ背景もスト2みたいに変えたかったらやれ
			1.0f,//縦サイズ
			1//横のパターン数
		);

		int time = g_Time;

		for (int i = 0; i < TIME_MAX; i++)
		{
			//1の位の数値を取り出す
			int suuji = time % 10;;

			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_TextureNo));//&time.png);
			DrawSpriteColorRotate(560.0f - (50.0f*i), 220.0f, 50.0f, 50.0f, 0, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f),
				suuji, 0.1f, 1.0f, 10);

			//数値全体を10で割る
			time /= 10;
		}

		int block = g_Block;

		for (int i = 0; i < 2; i++)
		{
			//1の位の数値を取り出す
			int num = block % 10;;

			DrawSpriteColorRotate(560.0f - (50.0f*i), 355.0f, 50.0f, 50.0f, 0, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f),
				num, 0.1f, 1.0f, 10);

			//数値全体を10で割る
			block /= 10;
		}
		SetTime(ResultTimer());
		SetBlock(BlockScore());

		if (Score == SCORE::SCORE_S)
		{
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(TextureSNo));//&Result_alpha_s);
		//サイズを気を付けよう。
			static float patern = 0;
			DrawSpriteColorRotate(
				SCREEN_WIDTH / 2,
				SCREEN_HEIGHT / 2,
				SCREEN_WIDTH,
				SCREEN_HEIGHT,
				0,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				0,//アニメーション番号背景だから変わらない
				1.0f,//横サイズ背景もスト2みたいに変えたかったらやれ
				1.0f,//縦サイズ
				1//横のパターン数
			);
		}
		else if (Score == SCORE::SCORE_A)
		{
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(TextureANo));//&Result_alpha_a);
		//サイズを気を付けよう。
			static float patern = 0;
			DrawSpriteColorRotate(
				SCREEN_WIDTH / 2,
				SCREEN_HEIGHT / 2,
				SCREEN_WIDTH,
				SCREEN_HEIGHT,
				0,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				0,//アニメーション番号背景だから変わらない
				1.0f,//横サイズ背景もスト2みたいに変えたかったらやれ
				1.0f,//縦サイズ
				1//横のパターン数
			);
		}
		else if (Score == SCORE::SCORE_B)
		{
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(TextureBNo));//&Result_alpha_b);
		//サイズを気を付けよう。
			static float patern = 0;
			DrawSpriteColorRotate(
				SCREEN_WIDTH / 2,
				SCREEN_HEIGHT / 2,
				SCREEN_WIDTH,
				SCREEN_HEIGHT,
				0,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				0,//アニメーション番号背景だから変わらない
				1.0f,//横サイズ背景もスト2みたいに変えたかったらやれ
				1.0f,//縦サイズ
				1//横のパターン数
			);
		}
	}


}

void SetTime(int time)
{
	g_Time = time;
}
void SetBlock(int block)
{
	g_Block = block;
}

int SetClear()
{
	return clear + 1;
}

int GetScore(int i)
{
	return rank[i];
}