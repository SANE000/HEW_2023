/*==============================================================================

   カメラ制御 [camera.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "camera.h"
#include "main.h"
#include "inputx.h"
#include "keyboard.h"
#include "cat.h"
#include "blockpreview.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CAMERA_SPEED 3
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static CAMERA_2D	g_Camera;	// カメラ用データ
static D3DXVECTOR2  g_Base;		// マップ全体の親座標
static int			Nowpos;

//=============================================================================
// 初期化処理
//=============================================================================
void InitCamera(void)
{
	g_Camera.pos = D3DXVECTOR2(0.0f, 0.0f);
	g_Camera.move = false;
	g_Base = D3DXVECTOR2(0.0f, 0.0f);


}

void UninitCamera(void)
{

}

void UpdateCamera(void)
{
	//カメラの座標を反転したものがベース座標になる
	g_Base = (g_Camera.pos * -1);
	CAT* pCat = GetCat();
	PREVIEW_BLOCK* pPreviewBlock = GetPreviewBlock();
	PLAYER* pplayer = GetPlayer();


	//横に動く
	//猫が画面の右側にいったら
	if (pCat->pos.x >= g_Camera.pos.x + SCREEN_WIDTH - 20) {
	//ムーブフラグをturuにする
		g_Camera.move = true;
	}
	//ムーブフラグがtrueなら
	if (g_Camera.move == true)
	{//一定の速度で移動
		g_Camera.pos.x += 10;
		//pPreviewBlock->pos.x += 10;
		if (pCat->pos.x - 10 <= g_Camera.pos.x) {
			//猫が左端についたら移動を止め位置補正
			pPreviewBlock->pos.x = g_Camera.pos.x;
			g_Camera.move = false;
			Nowpos = g_Camera.pos.x;
		}
	}
	//左側に行ったら初期画面
	if (pCat->pos.x <= g_Camera.pos.x - 20) {
		g_Camera.pos.x = 0;
	}

	//ムーブフラグがfalse / posが9601の倍数以外
	if (g_Camera.move == false && Nowpos % SCREEN_WIDTH != 0)
	{//画面に合わせ位置補正
		g_Camera.pos.x = g_Camera.Oldpos.x + SCREEN_WIDTH;
		Nowpos = g_Camera.pos.x;
		pplayer->pos.x = g_Camera.Oldpos.x + SCREEN_WIDTH - 30;
	}

	//ムーブフラグがfalse / posが9601の倍数
	if (g_Camera.move == false && Nowpos % SCREEN_WIDTH == 0)
	{
		//Oldposに今の位置を入れる
		g_Camera.Oldpos = g_Camera.pos;
	}


	if (Keyboard_IsKeyDown(KK_V))
	{
		g_Camera.pos.x++;
	}
	if (Keyboard_IsKeyDown(KK_C))
	{
		g_Camera.pos.x--;
	}

}


void DrawCamera(void)
{

}

CAMERA_2D* GetCamera(void)
{
	return &g_Camera;
}

D3DXVECTOR2 GetBase(void)
{
	return g_Base;
}
