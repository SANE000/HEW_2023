#pragma once

#include "main.h"
#include "renderer.h"

#define UI_MAX  30


struct SelUI
{
	//構造体使用中フラグ
	bool use = true;
	//表示座標
	D3DXVECTOR2 pos;
	//サイズ
	D3DXVECTOR2 size;
	//回転角度
	float rot = 0;
	//色
	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//テクスチャパターン
	int Patern = 0;
	//クリアランク
	int rank;
};

//初期化	HRESULTは返り値をお知らせするモノ。成功失敗連絡
HRESULT InitselUI();
void UnInitselUI();
void UpdateselUI();
void DrawselUI();