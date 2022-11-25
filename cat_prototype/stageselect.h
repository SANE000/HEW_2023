#pragma once

#include "main.h"
#include "renderer.h"

#define FIELD_MAX   6
#define STAGE_MAX   3

struct FIELD
{
	//構造体使用中フラグ
	bool use = true;
	//表示座標
	D3DXVECTOR2 pos;
	//サイズ
	D3DXVECTOR2 size;
	//回転角度
	float rot = 0;
	//テクスチャ番号
	int texNo;
	//色
	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//種類用のアニメ番号
	float Patern = 0;
};

struct STAGE
{
	//構造体使用中フラグ
	bool use = true;
	//表示座標
	D3DXVECTOR2 pos;
	//サイズ
	D3DXVECTOR2 size;
	//回転角度
	float rot = 0;
	//テクスチャ番号
	int texNo;
	//色
	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//種類用のアニメ番号
	float Patern = 0;

};

//プロトタイプ宣言
HRESULT InitStageSelect();
void UnInitStageSelect();
void UpdateStageSelect();
void DrawStageSelect();

int SetStage();
int SetField();
