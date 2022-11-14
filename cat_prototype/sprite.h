//スプライト描画処理
#pragma once
#include "main.h"
//マクロ

//プロトタイプ宣言
//↓こいつらを引き数にするぞ！
//static float PaternNo = 0;
//float uv_w = 0.5f;//キャラクターの横サイズ
//float uv_h = 0.5f;//キャラクターの縦サイズ　　田みたいな感じ
//int NumPatern = 2;//キャラクターの横の枚数
void DrawSpriteColorRotate(float posx, float posy, int size_w,
	int size_h, float kakudo, D3DXCOLOR col,
	float PaternNo,
	float uv_w,float uv_h,
	int NumPatern);
void InitSptite();
void UnInitSptite();