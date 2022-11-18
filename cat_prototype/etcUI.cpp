#include "etcUI.h"
#include "texture.h"
#include "sprite.h"
#include "camera.h"
#include "cat.h"

//その他のUI関係のマクロやこれから追加するかも用
#define ETC_MAX 2
#define ETC_SIZE_W 100
#define ETC_SIZE_H 50
//プロトタイプ宣言
///////////////////////グローバル宣言
static ETC g_etc[ETC_MAX];

ETC InitDate[] =
{
	{true,D3DXVECTOR2(SCREEN_WIDTH/2,100),0,0,ETC_SIZE_W,ETC_SIZE_H,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)},//タイムUI
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
//描画処理
void DrawEtc()
{
	D3DXVECTOR2 basePos = GetBase();

	for (int i = 0; i < ETC_MAX; i++)
	{
		//画面上を動かないUI描画
		if (g_etc[0].use == true)
		{
				//テクスチャのセット
				GetDeviceContext()->PSSetShaderResources
				(0, 1, GetTexture(g_etc[0].texNo));
				//スプライトの描画
				DrawSpriteColorRotate(
					g_etc[0].pos.x,
					g_etc[0].pos.y,
					g_etc[0].w,
					g_etc[0].h,
					g_etc[0].rot,
					g_etc[0].col,
					0,//動かないから0
					1.0f,//横
					1.0f,//縦
					1
				);
		}
		//動くUI描画
		if(g_etc[1].use == true)
		{
			//テクスチャのセット
			GetDeviceContext()->PSSetShaderResources
			(0, 1, GetTexture(g_etc[1].texNo));
			//スプライトの描画
			DrawSpriteColorRotate(
				basePos.x + g_etc[1].pos.x,
				basePos.y + g_etc[1].pos.y,
				g_etc[1].w,
				g_etc[1].h,
				g_etc[1].rot,
				g_etc[1].col,
				0,
				1.0f,//横
				1.0f,//縦
				1
			);
		}
	}
}
//構造体の先頭ポインタを返す　皆が使えるように
ETC *GetEtc()
{
	return &g_etc[0];
}
