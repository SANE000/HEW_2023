

#include "title.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "scene.h"
#include "sound.h"
#include<stdio.h>
#include <iostream>


//==========================================
//マクロ定義
//==========================================
#define GAMESTART_ARROW	260
#define GAMEEND_ARROW	378

#define ARROWSIZE_W		50
#define ARROWSIZE_H		50


//==========================================
//プロトタイプ宣言
//==========================================
//御金欲しい

//==========================================
//グローバル変数
//==========================================

typedef struct
{
	D3DXVECTOR3 Position;	//表示座標
	D3DXVECTOR2 Size;		//サイズ
	D3DXCOLOR	Color;		//色
	float		Rotate;		//角度

}TITLE;






HRESULT InitTitle()
{

	return S_OK;
}

void UninitTitle()
{
	
}

void UpdateTitle()
{
	
}

void DrawTitle()
{
	
}
