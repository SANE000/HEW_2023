#include "player.h"
#include "main.h"
#include "block.h"
#include "blockpreview.h"
#include "inputx.h"
#include "keyboard.h"
#include "texture.h"
#include "sprite.h"
#include "Scene.h"
#include "sound.h"
#include "timer.h"
#include "collision.h"
#include "camera.h"
#include "preview_collision.h"

//マクロ定義
#define BULLET_WAIT (28)
#define ROT_WAIT (10)
//プロトタイプ宣言

///////////////////////グローバル
static int time = 0;
//int JumpSoundNo = 0;
//プレイヤーオブジェクト
static PLAYER g_Player;
//スクロール中は動かさない対策
static CAMERA_2D *g_Camera = GetCamera();
//1ステージに何個ブロックを使ったか
static int blockscore = 0;
///

HRESULT InitPlayer()
{
	//テクスチャロード 画像の名前を入れよう
	g_Player.texNo = LoadTexture((char*)"data\\texture\\shop_cursor.png");
	//構造体の初期化
	g_Player.pos.x = DEFO_SIZE_X;
	g_Player.pos.y = DEFO_SIZE_X;
	g_Player.SetPos.x = g_Player.pos.x;
	g_Player.SetPos.y = g_Player.pos.y + DRAW_SIZE;
	g_Player.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Player.patern = 0.0f;
	g_Player.bwait = 0;
	//使用中フラグをオンにする
	g_Player.use = true;

	blockscore = 0;


	//サウンドのロード
	//char filename[] = "data\\SE\\boyoyon.wav";
	//JumpSoundNo = LoadSound(filename);
	//HRESULTに値を返して正常終了したことを連絡する
	return S_OK;
}
//終了処理
void UnInitPlayer()
{

}
//更新処理
void UpdatePlayer()
{
	//今現在のプレイヤーの座標を記憶しておく
	D3DXVECTOR2 now_playerpos = g_Player.pos;

	if (time > 0)
	{
		time -= 1;
	}
	//初期値から左へはいかないようにする
	if (g_Player.pos.x <= DEFO_SIZE_X)
	{
		g_Player.pos.x = DEFO_SIZE_X;
	}
	else if (g_Player.pos.x >= SCREEN_WIDTH * 6 - DEFO_SIZE_X)
	{
		g_Player.pos.x = SCREEN_WIDTH * 6 - DEFO_SIZE_X;
	}

	if (g_Player.bwait > 0)
	{
		g_Player.bwait -= 1;
	}
	//初期値から上へはいかないようにする
	if (g_Player.pos.y <= DEFO_SIZE_X)
	{
		g_Player.pos.y = DEFO_SIZE_X;
	}
	//終端値から下へもいかないようにする
	else if (g_Player.pos.y >= SCREEN_HEIGHT - DEFO_SIZE_X)
	{
		g_Player.pos.y = SCREEN_HEIGHT - DEFO_SIZE_X;
	}

	//操作関係
	//画面スクロール中はプレイヤーの操作は行えないようにする
	if (g_Camera->moveLeft == false && g_Camera->moveRight == false)
	{
		//上下左右矢印キーで移動する
		if (Keyboard_IsKeyDown(KK_D) && time <= 0 || GetThumbLeftX(0) > 0 && time <= 0)
		{//右
			g_Player.pos.x += DRAW_SIZE;
			time = WAIT_TIME;
		}
		else if (Keyboard_IsKeyDown(KK_A) && time <= 0 || GetThumbLeftX(0) < 0 && time <= 0)
		{//左
			g_Player.pos.x -= DRAW_SIZE;
			time = WAIT_TIME;
		}
		//上下の移動
		else if (Keyboard_IsKeyDown(KK_S) && time <= 0 || GetThumbLeftY(0) < 0 && time <= 0)
		{//下
			g_Player.pos.y += DRAW_SIZE;
			time = WAIT_TIME;
		}
		else if (Keyboard_IsKeyDown(KK_W) && time <= 0 || GetThumbLeftY(0) > 0 && time <= 0)
		{//上
			g_Player.pos.y -= DRAW_SIZE;
			time = WAIT_TIME;
		}

		//プレビューブロックを回転
		if (Keyboard_IsKeyDown(KK_Z) && g_Player.bwait == 0 || IsButtonTriggered(0, XINPUT_GAMEPAD_X) && g_Player.bwait == 0)
		{
			GetPreviewBlock()->rot += 90;
			if (GetPreviewBlock()->rot == 360)
			{
				GetPreviewBlock()->rot = 0;
			}
			g_Player.bwait = ROT_WAIT;
		}

		//SPACEキーでブロックをプレイヤーの下方向へ射出して
		//猫の足場を形成(授業でやったバレットを参考にする)
		g_Player.SetPos = g_Player.pos;
		if (Keyboard_IsKeyDown(KK_SPACE) && g_Player.bwait == 0 || IsButtonTriggered(0, XINPUT_GAMEPAD_B) && g_Player.bwait == 0)
		{
			if (FalseExistCheck() == true)
			{
				blockscore++;//ブロックを何個使ったか

				SetMoveBlock();

			}
			//要調整
			g_Player.bwait = BULLET_WAIT;

		}

		//爪とぎ終了
		if (GetCat()->tumetogi_flag == true && Keyboard_IsKeyDown(KK_X) || IsButtonPressed(0, XINPUT_GAMEPAD_X))
		{
			GetCat()->tumetogi_flag = false;
		}

		//リセットキー
		if (Keyboard_IsKeyDown(KK_R) && time <= 0 || IsButtonTriggered(0, XINPUT_GAMEPAD_START) && time <= 0)
		{
			SetScene(SCENE_SHOP);
			time = WAIT_TIME;
		}
		//時間切れゲームオーバー
		if (GetLimitFrame() < 0)
		{
			SetScene(SCENE_GAMEOVER);
		}

		//ブロックプレビュー更新
		UpdateBlockPreview(g_Player.pos);

		//プレビューブロックがブロックにめりこんでいたら
		if (PreviewCollisionCheck() == true)
		{
			//プレイヤーの座標を最初の状態に戻して
			g_Player.pos = now_playerpos;

			//ブロックプレビュー更新
			UpdateBlockPreview(g_Player.pos);
		}


	}
}
void DrawPlayer()
{
	//テクスチャのセット
	D3DXVECTOR2 basePos = GetBase();
	GetDeviceContext()->PSSetShaderResources
	(0, 1, GetTexture(g_Player.texNo));
	g_Player.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//スプライトの描画
	DrawSpriteColorRotate(
		g_Player.pos.x + basePos.x,
		g_Player.pos.y,
		DRAW_SIZE,
		DRAW_SIZE,
		g_Player.rot,
		g_Player.col,
		g_Player.patern,		
		1.0f,//横
		1.0f,//縦
		1//横のパターン枚数
	);
}
//構造体の先頭ポインタを返す　皆が使えるように
PLAYER *GetPlayer()
{
	return &g_Player;
}

//使ったブロックの数を調べるために使う
int BlockScore()
{
	return blockscore;
}

