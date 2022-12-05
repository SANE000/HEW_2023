#pragma once

#include "main.h"
#include "renderer.h"

//マクロ定義
#define BLOCK_MAX 126
#define ONTIME 23.0f
//構造体定義
struct BLOCK
{
	//構造体使用中フラグ
	bool use = true;
	//ボタンオンフラグ
	bool button = false;
	//ボタンに乗っている時間をとる
	int ontime;
	//表示座標
	D3DXVECTOR2 pos;
	//回転角度
	float rot = 0;
	//テクスチャ番号
	int texNo;
	//色
	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//スクロール用ブロック移動ベクトル
	D3DXVECTOR2 Speed = D3DXVECTOR2(0, 0);
	//種類用のアニメ番号
	//デフォルトは草あり地面ブロック
	float Patern = 0.0f;
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
