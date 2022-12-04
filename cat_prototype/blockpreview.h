#ifndef PREVIEW_H
#define PREVIEW_H
#pragma once

#include "main.h"
#include "renderer.h"

#define MOVE_BLOCK_MAX 50
#define PREVIEW_BLOCK_MAX 10

struct MOVE_BLOCK
{
	//キャラはほとんど決まってる共通部品がある
	//構造体使用中フラグ
	bool use = false;
	//表示座標
	D3DXVECTOR2 pos;
	//回転角度
	float rot;
	//テクスチャ番号
	int texNo;
	//色
	D3DXCOLOR col;
	//スクロール用ブロック移動ベクトル
	D3DXVECTOR2 Speed;
	//ブロックの種類判別用変数
	int type;
	//ブロックパターン
	float Patern;

	//ブロックを設置する際に値を入れる。
	//次ブロックを設置するときは前とは違う値が入る。　一度に置くブロックをグループととらえて判別するための変数
	int group;

};

struct PREVIEW_BLOCK
{
	//構造体使用中フラグ
	bool use;
	//表示座標
	D3DXVECTOR2 pos;
	//回転角度
	float rot;
	//テクスチャ番号
	int texNo;
	//色
	D3DXCOLOR col;
};

//プロトタイプ宣言
HRESULT InitPreview();
void UnInitPreview();
void UpdatePreview();
void DrawPreview();
//全部の仕様フラグをfalseにする
void FalsePreviewBlock();
//falseが存在するかどうかチェックする	全部trueの時は買ったブロックを使い切ったということになる
bool FalseExistCheck();
//Moveブロックをセットする
void SetMoveBlock();
void BlockPreview(D3DXVECTOR2 pos);
void UpdateBlockPreview(D3DXVECTOR2 pos);
//ポインタを返す
PREVIEW_BLOCK *GetPreviewBlock();
MOVE_BLOCK *GetMoveBlock();
#endif//!PREVIEW_H