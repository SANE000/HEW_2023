#pragma once

#include "main.h"
#include "renderer.h"

//マクロ定義
#define CAT_GOLL 1870*2//1870*2
#define CAT_SIZE_W 52
#define CAT_SIZE_H 57
#define CAT_INIT_X (CAT_SIZE_W)
#define CAT_INIT_Y 240
//猫の移動速度
#define WALK (1.00f)
//ジャンプ力
#define JUMP (7.0f)
//ジャンプセンサーの横サイズ
#define SENSOR_SIZE	(15.0f)		


//構造体定義
struct CAT
{
	//キャラはほとんど決まってる共通部品がある
	//構造体使用中フラグ
	bool use;
	//表示座標
	D3DXVECTOR2 pos;
	//回転角度
	float rot;
	//進行方向
	D3DXVECTOR2 dir;
	//テクスチャ番号
	int texNo;
	//アニメ番号
	float patern;
	//色
	D3DXCOLOR col;
	//左右反転するフラグ
	bool move_flag;
	//ジャンプフラグ
	bool jump_flag;
	//今ジャンプしているかどうかのフラグ
	int nowjump_flag;
	//爪とぎブロックに乗っているかどうかのフラグ
	bool tumetogi_flag;
	//ジャンプ力
	float jump_y;
	//ジャンプ限界高度
	float limit_jump;
	//中間ポイントフラグ
	bool half_flag;
	//ゴールフラグ
	bool goal_flag;
};

//プロトタイプ宣言
//初期化	HRESULTは返り値をお知らせするモノ。成功失敗連絡
HRESULT InitCat();
void UnInitCat();
void UpdateCat();
void DrawCat();
//構造体の先頭ポインタを返す　皆が使えるように
CAT *GetCat();

//ジャンプフラグ取得関数
bool GetJumpFlag();


//猫がジャンプする処理が入った関数 collisionでブロックとぶつかった際呼び出す
void CatJump(float jumpheight);

//
void ChangeMoveFlag(CAT* c);

//中間ポイントフラグを返す
bool HalfWayFlag();