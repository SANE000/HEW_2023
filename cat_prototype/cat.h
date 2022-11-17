#pragma once

#include "main.h"
#include "renderer.h"

//マクロ定義
#define CAT_GOLL 180
#define CAT_SIZE_W 60
#define CAT_SIZE_H 60
#define CAT_INIT_X (CAT_SIZE_W)
#define CAT_INIT_Y 240


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
	//テクスチャ番号
	int texNo;
	//アニメ番号
	float patern;
	//猫サイズ
	float w, h;
	//色
	D3DXCOLOR col;
	//左右反転するフラグ
	bool move_flag;
	//ジャンプフラグ
	bool jump_flag;
	//今ジャンプしているかどうかのフラグ
	int nowjump_flag;
	//ジャンプ力
	float jump_y;
	//ジャンプ限界高度
	float limit_jump;
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
