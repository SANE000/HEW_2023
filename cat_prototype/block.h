#pragma once

#include "main.h"

//マクロ定義
#define BLOCK_MAX 100
#define ONTIME 69.0f
//構造体定義
struct BLOCK
{
	//構造体使用中フラグ
	bool use = true;
	//描画フラグ
	bool draw_use = true;
	//ボタンオンフラグ
	bool button = false;
	//ボタンに乗っている時間をとる
	float ontime;
	//表示座標
	D3DXVECTOR2 pos;
	//ワープ先座標
	D3DXVECTOR2 warpos;
	//回転角度
	float rot = 0;
	//テクスチャ番号
	int texNo;
	//色
	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//スクロール用ブロック移動ベクトル
	D3DXVECTOR2 Speed = D3DXVECTOR2(0, 0);
	//種類用のアニメ番号
	//デフォルトはステージ別に用意しよう
	float Patern = 0.0f;
	//移動する奴用+-limit
	float limitmax = 0.0f;
	float limitmin = 0.0f;
	//起動フラグ
	bool moveflug;
};
//プロトタイプ宣言
HRESULT InitBlock();
void UnInitBlock();
void UpdateBlock();
void DrawBlock();
//構造体の先頭ポインタを返す
BLOCK *GetBlock();


double GetMapPos();

int GetStage();
