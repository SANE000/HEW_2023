#include "main.h"
#include "renderer.h"
#include "Game.h"
#include "polygon.h"
#include "player.h"
#include "cat.h"
#include "block.h"
#include "blockpreview.h"
#include "timer.h"
#include "etcUI.h"
#include "collision.h"
#include "sound.h"
#include "blocktype.h"
#include "camera.h"
#include "result.h"

//マクロ定義
//あとはタイム表示、

//==========================================
//グローバル変数
//==========================================

//初期化
void InitGame()
{
	////////////////ゲーム関連の初期化
//ポリゴンの初期化
		//サウンドのロード
	//char filename[] = "data\\BGM\\sample000.wav";
	//GameSoundNo = LoadSound(filename);
	//PlaySound(GameSoundNo, -1);
	//SetVolume(GameSoundNo,0.1f);
	//背景の初期化
	InitPolygon();
	InitEtc();
	//タイマーの初期化
	InitTime();
	//ステージの初期化
	InitCamera();
	InitPlayer();
	InitCat();
	InitBlock();
	InitPreview();
	InitCollsion();
	InitResult();


	///////////////////////////////
}
//更新処理
void UninitGame()
{
	////////////////ゲーム関連
	//BGMの終了
	//StopSound(GameSoundNo);
	UnInitBlock();
	UnInitPreview();
	UnInitCat();
	UnInitPlayer();
	UninitCamera();
	UnInitTime();
	UnInitEtc();
	//背景の終了
	UnInitPolygon();
	////////////////ゲーム関連
}
//終了処理
void UpdateGame()
{
	////////////////ゲーム関連
	//背景の更新
	UpdatePolygon();
	UpdateEtc();
	//ステージの更新
	UpdatePlayer();
	UpdateCat();
	UpdateCamera();
	UpdateBlock();
	UpdatePreview();
	UpdateCollision();
	UpdateResult();
	////////////////ゲーム関連
}
//描画処理
void DrawGame()
{
	////////////////ゲーム関連
	//背景描画
	DrawPolygon();
	//ブロックの表示
	DrawBlock();
	DrawPreview();
	//猫の表示
	DrawCat();
	//ゴールその他UI
	DrawEtc();
	DrawTime();
	//プレイヤーの描画//は下の方に！
	DrawPlayer();
	// バックバッファ、フロントバッファ入れ替え
	////////////////ゲーム関連
}
