#pragma once

#include "main.h"
#include "renderer.h"

//マクロ定義
#define BLOCK_MAX 8
#define MOVE_BLOCK_MAX 50
#define PREVIEW_BLOCK_MAX 10

//マクロ定義
#define BLOCK_SIZE_W 96
#define BLOCK_SIZE_H 48
//96だとひっかかるかも/////////////////////////////////
#define MOVE_BLOCK_SIZE_W 47.5
#define MOVE_BLOCK_SIZE_H 48


//構造体定義
struct BLOCK
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
	//ブロックサイズ
	float w, h;
	//色
	D3DXCOLOR col;
	//スクロール用ブロック移動ベクトル
	D3DXVECTOR2 Speed;
	//ジャンプ用
	bool Hit;
};

struct MOVE_BLOCK
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
	//ブロックサイズ
	float w, h;
	//色
	D3DXCOLOR col;
	//スクロール用ブロック移動ベクトル
	D3DXVECTOR2 Speed;
	//ジャンプ用
	bool Hit;
	//ブロックの種類判別用変数
	int type;
};

struct PREVIEW_BLOCK
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
	//ブロックサイズ
	float w, h;
	//色
	D3DXCOLOR col;
};


//プロトタイプ宣言
//初期化	HRESULTは返り値をお知らせするモノ。成功失敗連絡
HRESULT InitBlock();
//HRESULT InitPlayer(int a);
void UnInitBlock();
void UpdateBlock();
void DrawBlock();
//構造体の先頭ポインタを返す　皆が使えるように
BLOCK *GetBlock();
MOVE_BLOCK *GetMoveBlock();
PREVIEW_BLOCK *GetPreviewBlock();
void SetMoveBlock();

void BlockPreview(D3DXVECTOR2 pos);
void UpdateBlockPreview(D3DXVECTOR2 pos);

//全部の仕様フラグをfalseにする
void FalsePreviewBlock();

//falseが存在するかどうかチェックする	全部trueの時は買ったブロックを使い切ったということになる
bool FalseExistCheck();