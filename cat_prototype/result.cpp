
#include "texture.h"
#include "sprite.h"
#include "cat.h"
#include "player.h"
#include "timer.h"
#include "result.h"
#include "main.h"


//==========================================
//グローバル変数
//==========================================
static int g_TextureNo = 0;	// テクスチャ識別子
static int TextureBGNo = 0;	// テクスチャ識別子
static int TextureSNo = 0;	// テクスチャ識別子
static int TextureANo = 0;	// テクスチャ識別子
static int TextureBNo = 0;	// テクスチャ識別子
static int g_Time = 0;
static int g_Block = 0;
int Score = 0;



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
	//スコア計算//ココプランナーに決めてもらうの忘れてた
	if (BlockScore() <= 4 && ResultTimer() <= 20)
	{
		Score = SCORE::SCORE_S;
	}
	else if (BlockScore() <= 5 && ResultTimer() <= 35)
	{
		Score = SCORE::SCORE_A;
	}
	else
	{
		Score = SCORE::SCORE_B;
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

		for (int i = 0; i < TIME_MAX - 1; i++)
		{
			//1の位の数値を取り出す
			int suuji = time % 10;;

			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_TextureNo));//&time.png);
			DrawSpriteColorRotate(480.0f - (32.0f*i), 220.0f, 32.0f, 32.0f, 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				suuji, 0.1f, 1.0f, 10);

			//数値全体を10で割る
			time /= 10;
		}

		int block = g_Block;

		for (int i = 0; i < 2; i++)
		{
			//1の位の数値を取り出す
			int num = block % 10;;

			DrawSpriteColorRotate(480.0f - (32.0f*i), 355.0f, 32.0f, 32.0f, 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
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
