

#include "title.h"
#include "texture.h"
#include "sprite.h"
#include "inputx.h"
#include"keyboard.h"
#include "scene.h"
#include "sound.h"
#include <stdio.h>
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
	D3DXVECTOR2 Position;	//表示座標
	D3DXVECTOR2 Size;		//サイズ
	D3DXCOLOR	Color;		//色
	float		Rotate;		//角度

}TITLE;

static int g_TextureNo = 0;	// テクスチャ識別子

HRESULT InitTitle()
{
	g_TextureNo = LoadTexture((char*)"data/TEXTURE/title.png");


	return S_OK;
}

void UninitTitle()
{
	
}

void UpdateTitle()
{
	if (Keyboard_IsKeyDown(KK_ENTER) || IsButtonTriggered(0, XINPUT_GAMEPAD_B)) {
		SetScene(SCENE_SELECT);
	}
}

void DrawTitle()
{
	GetDeviceContext()->PSSetShaderResources
	(0, 1, GetTexture(g_TextureNo));

	DrawSpriteColorRotate
	(
		SCREEN_WIDTH / 2,
		SCREEN_HEIGHT / 2,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		0,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		0,
		1.0f,//横
		1.0f,//縦
		1//総枚数
	);
}
