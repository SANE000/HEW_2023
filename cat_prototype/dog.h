#pragma once

#include "main.h"
#include "renderer.h"

//------------------------
//マクロ定義
//------------------------
#define DOG_MAX	  (3)
#define DOG_SPEED (2.0f)

#define DOG_SIZE_W (60)
#define DOG_SIZE_H (60)
//#define DOG_INIT_X (60)
//#define DOG_INIT_Y (240)

//------------------------
//構造体定義
//------------------------
struct DOG
{
	bool		  use;			//使用中フラグ
	bool          move_flag;	//猫近づいてきたフラグ
	bool          jump_flag;
	D3DXVECTOR2   pos;			//表示座標
	float		  rot;			//回転角度
	D3DXVECTOR2   dir;          //進行方向
	int			  texNo;		//テクスチャ番号
	float		  w, h;			//dogサイズ
	D3DXVECTOR2   move;			//移動スピード
	D3DXCOLOR	  col;			//色
	float         framewait;
	int           ugoki;
	float         anime;
};

//------------------------
//プロトタイプ宣言
//------------------------
HRESULT InitDog();
void UnInitDog();
void UpdateDog();
void DrawDog();

DOG* GetDog();

void ChangeDogMoveFlag(DOG* d);