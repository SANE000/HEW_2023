
//==========================================
//リザルト処理
//==========================================
#pragma once

#include "main.h"


//==========================================
//マクロ定義
//==========================================

//シーン番号
enum SCORE
{
	SCORE_NULL = 0,
	SCORE_S,
	SCORE_A,
	SCORE_B,
};

//==========================================
//プロトタイプ宣言
//==========================================
HRESULT InitResult();
void UninitResult();
void UpdateResult();
void DrawResult();

void SetTime(int time);

void SetBlock(int block);

//クリアの値のセット
int SetClear();

//ステージのクリアランク
int GetScore(int i);
