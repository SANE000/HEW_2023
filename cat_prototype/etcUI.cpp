#include "etcUI.h"
#include "texture.h"
#include "sprite.h"

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
	{true,D3DXVECTOR2(910,SCREEN_HEIGHT / 2-50),0,0,ETC_SIZE_W,ETC_SIZE_H*2,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)},//ゴール表示
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
	for (int i = 0; i < ETC_MAX; i++)
	{
		//描画
		if (g_etc[i].use == true)
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
	}
}
//構造体の先頭ポインタを返す　皆が使えるように
ETC *GetEtc()
{
	return &g_etc[0];
}
