#pragma once

#include <d3dx9.h>

//==========================================
//マクロ定義
//==========================================
#define WALL_MAX 30

//構造体定義
struct G_WALL
{
	//構造体使用中フラグ
	bool use = true;
	//ボタンオンフラグ
	bool button = false;
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
	float Patern = 0.0f;
};

//==========================================
//プロトタイプ宣言
//==========================================
HRESULT InitGimmickWall();
void UninitGimmickWall();
void UpdateGimmickWall();
void DrawGimmickWall();

G_WALL* GetGimmickWall();
