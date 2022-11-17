#pragma once

#include "main.h"
#include "renderer.h"

//マクロ定義

//構造体定義
struct PLAYER
{
	//キャラはほとんど決まってる共通部品がある
	//構造体使用中フラグ
	bool use;
	//表示座標
	D3DXVECTOR2 pos;
	//ブロック発生座標
	D3DXVECTOR2 SetPos;
	//回転角度
	float rot;
	//テクスチャ番号
	int texNo;
	//アニメ番号
	float patern;
	//色
	D3DXCOLOR col;
	//発射間隔
	int bwait;
};


//プロトタイプ宣言
//初期化	HRESULTは返り値をお知らせするモノ。成功失敗連絡
HRESULT InitPlayer();
//HRESULT InitPlayer(int a);
void UnInitPlayer();
void UpdatePlayer();
void DrawPlayer();
//構造体の先頭ポインタを返す　皆が使えるように
PLAYER *GetPlayer();

int BlockScore();
