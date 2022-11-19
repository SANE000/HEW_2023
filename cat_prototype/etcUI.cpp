#include "etcUI.h"
#include "texture.h"
#include "sprite.h"
#include "shop.h"
#include "camera.h"
#include "cat.h"

//その他のUI関係のマクロやこれから追加するかも用
#define ETC_MAX 3
#define ETC_SIZE_W 100
#define ETC_SIZE_H 50
//プロトタイプ宣言
///////////////////////グローバル宣言
//偵察用
static double map_pos = 0;
static ETC g_etc[ETC_MAX];

ETC InitDate[] =
{
	{true,D3DXVECTOR2(SCREEN_WIDTH/2,100),0,0,ETC_SIZE_W,ETC_SIZE_H,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)},//タイムUI
	{true,D3DXVECTOR2((CAT_GOLL + DRAW_SIZE)/2,SCREEN_HEIGHT / 2 + 150),0,0,ETC_SIZE_W,ETC_SIZE_H * 2,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)},//中間ポイント
	{true,D3DXVECTOR2(CAT_GOLL + DRAW_SIZE,SCREEN_HEIGHT / 2 + 150),0,0,ETC_SIZE_W,ETC_SIZE_H*2,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)},//ゴール表示
};

HRESULT InitEtc()
{
	//構造体の初期化
	for (int i = 0; i < ETC_MAX; i++)
	{
		g_etc[i] = InitDate[i];
		if (i == 0)
		{
			g_etc[i].texNo = LoadTexture((char*)"data\\texture\\timeUI.png");
		}
		else
		{
			g_etc[i].texNo = LoadTexture((char*)"data\\texture\\goal_flag.png");
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
	if (WatchMapFlag() == true)
	{
		if (map_pos <= -SCREEN_WIDTH * 5)
		{
			map_pos += 0;
		}
		else
		{
			map_pos -= WATCH;
		}
	}
	else
	{
		map_pos = 0;
	}
}
//描画処理
void DrawEtc()
{
	D3DXVECTOR2 basePos = GetBase();

	for (int i = 0; i < ETC_MAX; i++)
	{
		//画面上を動かないUI描画
		if (g_etc[i].use == true)
		{
			if (i == 0)
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
					0,//動かないから0
					1.0f,//横
					1.0f,//縦
					1
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
					0,
					1.0f,//横
					1.0f,//縦
					1
				);
			}
		}
	}
}
//構造体の先頭ポインタを返す　皆が使えるように
ETC *GetEtc()
{
	return &g_etc[0];
}
