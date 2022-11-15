#include "player.h"
#include "main.h"
#include "block.h"
#include "inputx.h"
#include "keyboard.h"
#include "texture.h"
#include "sprite.h"
#include "Scene.h"
#include "sound.h"
#include "collision.h"
#include "camera.h"
//マクロ定義
#define PLAYER_SIZE_W (48)
#define PLAYER_SIZE_H (48)
#define PLAYER_INIT_X (PLAYER_SIZE_W/2)
#define PLAYER_INIT_Y (PLAYER_SIZE_H/2)
#define MOVE_X (PLAYER_SIZE_W)
#define MOVE_Y (PLAYER_SIZE_H)
#define BULLET_WAIT (38)
//プロトタイプ宣言


///////////////////////グローバル
static int time = 0;
//int JumpSoundNo = 0;
//プレイヤーオブジェクト
static PLAYER g_Player;
///

HRESULT InitPlayer()
{
	//テクスチャロード 画像の名前を入れよう
	g_Player.texNo = LoadTexture((char*)"data\\texture\\player.png");
	//構造体の初期化
	g_Player.pos.x = PLAYER_INIT_X;
	g_Player.pos.y = PLAYER_INIT_Y;
	g_Player.SetPos.x = g_Player.pos.x;
	g_Player.SetPos.y = g_Player.pos.y + PLAYER_SIZE_H;
	g_Player.w = PLAYER_SIZE_W;
	g_Player.h = PLAYER_SIZE_H;
	g_Player.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Player.patern = 0.0f;
	g_Player.bwait = 0;
	//使用中フラグをオンにする
	g_Player.use = true;


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
	if (time > 0)
	{
		time -= 1;
	}
	//初期値から左へはいかないようにする
	if (g_Player.pos.x <= PLAYER_INIT_X)
	{
		g_Player.pos.x = PLAYER_INIT_X;
	}
	//終端値から右へもいかないようにする
	//else if (g_Player.pos.x >= SCREEN_WIDTH - PLAYER_INIT_X)
	//{
	//	g_Player.pos.x = SCREEN_WIDTH - PLAYER_INIT_X;
	//}
	if (g_Player.bwait > 0)
	{
		g_Player.bwait -= 1;
	}
	//初期値から上へはいかないようにする
	if (g_Player.pos.y <= PLAYER_INIT_Y)
	{
		g_Player.pos.y = PLAYER_INIT_Y;
	}
	//終端値から下へもいかないようにする
	else if (g_Player.pos.y >= SCREEN_HEIGHT - PLAYER_INIT_Y)
	{
		g_Player.pos.y = SCREEN_HEIGHT - PLAYER_INIT_Y;
	}

	//操作関係
	//上下左右矢印キーで移動する
	if (Keyboard_IsKeyDown(KK_D) || GetThumbLeftX(0) > 0 && time <= 0)
	{//右
		g_Player.pos.x += MOVE_X;
		time = WAIT_TIME;
	}
	else if (Keyboard_IsKeyDown(KK_A)|| GetThumbLeftX(0) < 0 && time <= 0)
	{//左
		g_Player.pos.x -= MOVE_X;
		time = WAIT_TIME;
	}
	//上下の移動によってバグが生じそうだから今は辞めておく
	else if (Keyboard_IsKeyDown(KK_S) || GetThumbLeftY(0) < 0 && time <= 0)
	{//下
		g_Player.pos.y += MOVE_Y;
		time = WAIT_TIME;
	}
	else if (Keyboard_IsKeyDown(KK_W) || GetThumbLeftY(0) > 0 && time <= 0)
	{//上
		g_Player.pos.y -= MOVE_Y;
		time = WAIT_TIME;
	}

	//プレビューブロックを回転
	if (Keyboard_IsKeyDown(KK_Z) || IsButtonTriggered(0, XINPUT_GAMEPAD_X) && time <= 0)
	{
		GetPreviewBlock()->rot += 90;
		if (GetPreviewBlock()->rot == 360)
		{
			GetPreviewBlock()->rot = 0;
		}
		time = WAIT_TIME;
	}

	//SPACEキーでブロックをプレイヤーの下方向へ射出して
	//猫の足場を形成(授業でやったバレットを参考にする)
	g_Player.SetPos = g_Player.pos;
	if (Keyboard_IsKeyDown(KK_SPACE) || IsButtonTriggered(0, XINPUT_GAMEPAD_B) && g_Player.bwait == 0)
	{
		if(FalseExistCheck() == true)
		SetMoveBlock();
		//要調整
		g_Player.bwait = BULLET_WAIT;
	}

	//リセットキー
	if (Keyboard_IsKeyDown(KK_R)||IsButtonTriggered(0, XINPUT_GAMEPAD_START) &&time<=0)
	{
		SetScene(SCENE_SHOP);
		time = WAIT_TIME;
	}
}
void DrawPlayer()
{
	////テクスチャのセット
	//GetDeviceContext()->PSSetShaderResources
	//(0, 1, GetTexture(g_Player.texNo));
	//g_Player.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	////スプライトの描画
	//DrawSpriteColorRotate(
	//	g_Player.pos.x,
	//	g_Player.pos.y,
	//	g_Player.w,
	//	g_Player.h,
	//	g_Player.rot,
	//	g_Player.col,
	//	g_Player.patern,		
	//	1.0f,//横
	//	1.0f,//縦
	//	1//横のパターン枚数
	//);
}
//構造体の先頭ポインタを返す　皆が使えるように
PLAYER *GetPlayer()
{
	return &g_Player;
}