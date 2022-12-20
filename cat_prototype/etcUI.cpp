#include "etcUI.h"
#include "texture.h"
#include "sprite.h"
#include "shop.h"
#include "player.h"
#include "camera.h"
#include "cat.h"
#include "inputx.h"
#include "keyboard.h"
#include "stageselect.h"

//その他のUI関係のマクロやこれから追加するかも用
#define ETC_MAX 28
#define ETC_SIZE_W 100
#define ETC_SIZE_H 50
//プロトタイプ宣言
///////////////////////グローバル宣言
//偵察用
static int time = 0;
static double map_pos = 0;
static double ofset = 1.0;
static int field;
static int stage;
static ETC g_etc[ETC_MAX];

ETC InitDate[] =
{
	//タイムUI
	{true,D3DXVECTOR2(SCREEN_WIDTH/2,90),0,0,ETC_SIZE_W,ETC_SIZE_H,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f/2.0f,1.0f,2},
	//発射したブロックUI
	{true,D3DXVECTOR2(SCREEN_WIDTH - 200,50),0,0,ETC_SIZE_W,ETC_SIZE_H,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f/2.0f,1.0f,2},
	//発射したブロック数1の位UI
	{true,D3DXVECTOR2(SCREEN_WIDTH - 50,50),0,0,TIME_SIZE_W,TIME_SIZE_H,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f/10.0f,1.0f,10},
	//発射したブロック数10の位UI
	{true,D3DXVECTOR2(SCREEN_WIDTH - 100,50),0,0,TIME_SIZE_W,TIME_SIZE_H,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f / 10.0f,1.0f,10},
	//偵察猫
	{false,D3DXVECTOR2(SCREEN_WIDTH / 2,40),0,0,60,60,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f / 6.0f,1.0f,6},
	//プレイ中操作説明UI
	{true,D3DXVECTOR2(150,60),0,0,300,100,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),1.0f,1.0f / 4.0f,1.0f,4},
	////
	//ここより下はスクロールするもの
	////
	//中間ポイント
	{true,D3DXVECTOR2((CAT_GOLL + DRAW_SIZE)/2,SCREEN_HEIGHT / 2 + 150),0,0,ETC_SIZE_W,ETC_SIZE_H * 2,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f / 2.0f,1.0f,2 },
	//ゴール表示
	{true,D3DXVECTOR2(CAT_GOLL + DRAW_SIZE,SCREEN_HEIGHT / 2 + 150),0,0,ETC_SIZE_W,ETC_SIZE_H*2,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),1.0f,1.0f / 2.0f,1.0f,2},
	//ベルトコンベア31-8-15
	{false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 7, DEFO_SIZE_Y - DRAW_SIZE * 1),0,0,180,60,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f / 10.0f,1.0f / 3.0f,10},
	{false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 10, DEFO_SIZE_Y - DRAW_SIZE * 1),0,0,180,60,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f / 10.0f,1.0f / 3.0f,10},
	{false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 1),0,0,180,60,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f / 10.0f,1.0f / 3.0f,10},
	{false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 25, DEFO_SIZE_Y - DRAW_SIZE * 4),0,0,180,60,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f / 10.0f,1.0f / 3.0f,10},
	{false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 33, DEFO_SIZE_Y - DRAW_SIZE * 0),0,0,180,60,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f / 10.0f,1.0f / 3.0f,10},
	{false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 36, DEFO_SIZE_Y - DRAW_SIZE * 0),0,0,180,60,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f / 10.0f,1.0f / 3.0f,10},
	{false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 39, DEFO_SIZE_Y - DRAW_SIZE * 0),0,0,180,60,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f / 10.0f,1.0f / 3.0f,10},
	{false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 4),0,0,180,60,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f / 10.0f,1.0f / 3.0f,10},
	//ベルトコンベア32-16-17
	{false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 22, DEFO_SIZE_Y - DRAW_SIZE * 0),0,0,180,60,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f / 10.0f,1.0f / 3.0f,10},
	{false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 25, DEFO_SIZE_Y - DRAW_SIZE * 0),0,0,180,60,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f / 10.0f,1.0f / 3.0f,10},
	//ベルトコンベア33-18-21
	{false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 10, DEFO_SIZE_Y - DRAW_SIZE * 1),0,0,180,60,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f / 10.0f,1.0f / 3.0f,10},
	{false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 1),0,0,180,60,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f / 10.0f,1.0f / 3.0f,10},
	{false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 1, DEFO_SIZE_Y - DRAW_SIZE * 1),0,0,180,60,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f / 10.0f,1.0f / 3.0f,10},
	{false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 4, DEFO_SIZE_Y - DRAW_SIZE * 1),0,0,180,60,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f / 10.0f,1.0f / 3.0f,10},
	//ワープ51-22-25
	{false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 5),0,0,DRAW_SIZE,DRAW_SIZE,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f / 2.0f,1.0f,2},
	{false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 17, DEFO_SIZE_Y - DRAW_SIZE * 1),0,0,DRAW_SIZE,DRAW_SIZE,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f / 2.0f,1.0f,2},
	{false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 6),0,0,DRAW_SIZE,DRAW_SIZE,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f / 2.0f,1.0f,2},
	{false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 51, DEFO_SIZE_Y - DRAW_SIZE * 6),0,0,DRAW_SIZE,DRAW_SIZE,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f / 2.0f,1.0f,2},
	//ワープ52-26-27
	{false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 52, DEFO_SIZE_Y - DRAW_SIZE * 4),0,0,DRAW_SIZE,DRAW_SIZE,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f / 2.0f,1.0f,2},
	{false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 57, DEFO_SIZE_Y - DRAW_SIZE * 8),0,0,DRAW_SIZE,DRAW_SIZE,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0.0f,1.0f / 2.0f,1.0f,2},
};

HRESULT InitEtc()
{
	field = SetField();
	stage = SetStage();

	//構造体の初期化
	for (int i = 0; i < ETC_MAX; i++)
	{
		//上で設定したモノがここに入る
		g_etc[i] = InitDate[i];

		//テクスチャは個別に設定する
		if (i == 0)
		{
			g_etc[i].texNo = LoadTexture((char*)"data\\texture\\timeUI.png");
		}
		else if (i == 1)
		{
			g_etc[i].texNo = LoadTexture((char*)"data\\texture\\blockscoreUI.png");
		}
		else if (i == 2 || i == 3)
		{
			g_etc[i].texNo = LoadTexture((char*)"data\\texture\\time.png");
		}
		else if (i == 4)
		{
			g_etc[i].texNo = LoadTexture((char*)"data\\texture\\night_cat.png");
		}
		else if (i == 5)
		{
			g_etc[i].texNo = LoadTexture((char*)"data\\texture\\sousaUI.png");
		}
		else if (i == 6 || i == 7)
		{
			g_etc[i].texNo = LoadTexture((char*)"data\\texture\\goal.png");
		}
		else if (i >= 12 && i <= 14 || i >= 16 && i <= 19)
		{
			g_etc[i].texNo = LoadTexture((char*)"data\\texture\\-belt_con.png");
		}
		else if (i >= 22 && i <= 27)
		{
			g_etc[i].texNo = LoadTexture((char*)"data\\texture\\warp.png");
		}
		else
		{
			g_etc[i].texNo = LoadTexture((char*)"data\\texture\\+belt_con.png");
		}
	}
	//
	if (field == 2)
	{
		if (stage == 0)
		{
			for (int i = 8; i < 16; i++)
			{
				g_etc[i].use = true;
			}
		}
		else if (stage == 1)
		{
			for (int i = 16; i < 18; i++)
			{
				g_etc[i].use = true;
			}
		}
		else if (stage == 2)
		{
			for (int i = 18; i < 22; i++)
			{
				g_etc[i].use = true;
			}
		}
	}
	else if (field == 4)
	{
		if (stage == 0)
		{
			for (int i = 22; i < 26; i++)
			{
				g_etc[i].use = true;
			}
		}
		else if (stage == 1)
		{
			for (int i = 26; i < 28; i++)
			{
				g_etc[i].use = true;
			}
		}
	}
	else
	{
		for (int i = 8; i < 28; i++)
		{
			g_etc[i].use = false;
		}
	}

	return S_OK;
}
//終了処理
void UnInitEtc()
{

}
void UpdateEtc()
{
	D3DXVECTOR2 basePos = GetBase();
	//マップボタンが押されたら
	if (WatchMapFlag() == true)
	{//画面端になるまで座標を引いていく
		if (time > 0)
		{
			time -= 1;
		}

		if (Keyboard_IsKeyDown(KK_D) && time <= 0 || GetThumbLeftX(0) > 0 && time <= 0)
		{
			if (map_pos > -SCREEN_WIDTH * 3 + (-basePos.x))
			{
				//画面端になったら止める
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
		//偵察用のUIへ変更
		//タイムをテイサツへ
		g_etc[0].patern = 1.0f;
		//SHOTをPUSH STARTへ変更
		g_etc[1].patern = 1.0f;
		//偵察用操作説明
		g_etc[5].patern = 0.0f;
		//ブロック数UIは表示しない
		g_etc[2].use = false;
		g_etc[3].use = false;
		//テイサツ猫を出現させる
		g_etc[4].use = true;
		//UI点滅
		
			if (ofset >= 0.25f)
			{
				ofset -= 0.01f;
			}
			else
			{
				ofset += 1.5f;
			}
		//偵察猫アニメーション
		if (g_etc[4].patern <= 10.0f)
		{
			g_etc[4].patern += 0.04f;
		}
		else
		{
			g_etc[4].patern -= 10.0f;
		}

	}
	else
	{
		//マップボタンが押されてないなら0にする
		map_pos = 0;
		ofset = 1.0;
		//普通の表示に戻す
		g_etc[0].patern = 0.0f;
		g_etc[1].patern = 0.0f;
		g_etc[4].patern = 0.0f;
		g_etc[5].patern += 0.002;
		if (g_etc[5].patern > 4.0f || g_etc[5].patern < 1.0f)
		{
			g_etc[5].patern = 1.0f;
		}
		g_etc[2].use = true;
		g_etc[3].use = true;
		g_etc[4].use = false;
	}
	g_etc[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, ofset);
}
//描画処理
void DrawEtc()
{
	D3DXVECTOR2 basePos = GetBase();
	g_etc[2].patern = BlockScore() % 10;
	g_etc[3].patern = (BlockScore()/10) % 10;
	for (int i = 0; i < ETC_MAX; i++)
	{
		if (g_etc[i].use == true)
		{		//画面上を動かないUI描画
			if (i >= 0 && i <= 5)
			{
				//テクスチャのセット
				GetDeviceContext()->PSSetShaderResources
				(0, 1, GetTexture(g_etc[i].texNo));
				//スプライトの描画
				DrawSpriteColorRotate(
					g_etc[i].pos.x,
					g_etc[i].pos.y,
					g_etc[i].w,
					g_etc[i].h,
					g_etc[i].rot,
					g_etc[i].col,
					g_etc[i].patern,
					g_etc[i].uv_w,//横
					g_etc[i].uv_h,//縦
					g_etc[i].uv_num//総枚数
				);
			}
			else
			{//動くUI描画
				//テクスチャのセット
				GetDeviceContext()->PSSetShaderResources
				(0, 1, GetTexture(g_etc[i].texNo));
				//スプライトの描画
				DrawSpriteColorRotate(
					basePos.x + g_etc[i].pos.x + map_pos,
					basePos.y + g_etc[i].pos.y,
					g_etc[i].w,
					g_etc[i].h,
					g_etc[i].rot,
					g_etc[i].col,
					g_etc[i].patern,
					g_etc[i].uv_w,//横
					g_etc[i].uv_h,//縦
					g_etc[i].uv_num//総枚数
				);
			}
			if (i >= 8 && i <= 21)
			{
				g_etc[i].patern += 0.5f;
				if (g_etc[i].patern >= 30.0f)
				{
					g_etc[i].patern -= 30.0f;
				}
			}
			else if (i >= 22 && i <= 27)
			{
				g_etc[i].patern += 0.02f;
				if (g_etc[i].patern >= 2.0f)
				{
					g_etc[i].patern -= 2.0f;
				}
			}
		}
	}
}
//構造体の先頭ポインタを返す　皆が使えるように
ETC *GetEtc()
{
	return &g_etc[0];
}
