#pragma once

#include "main.h"
#include "renderer.h"

//構造体定義//敵の情報はすべて構造体に入れる！
struct TIMER
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
	//タイムサイズ
	float w, h;
	//色
	D3DXCOLOR col;

	float result;
};

//プロトタイプ宣言
//初期化	HRESULTは返り値をお知らせするモノ。成功失敗連絡
HRESULT InitTime();
void UnInitTime();
void DrawTime();
//構造体の先頭ポインタを返す　皆が使えるように
TIMER *GetTime();
int GetLimitFrame();
int GetTimer();
//bool GetReset();
int ResultTimer();