#include "main.h"
#include "renderer.h"
#include "gameover.h"
#include "texture.h"
#include "scene.h"
#include "keyboard.h"
#include "sprite.h"

//====================
//ƒOƒ[ƒoƒ‹
//====================
static    GAMEOVER  g_GameOver;

HRESULT InitGameOver()
{
	g_GameOver.texNo = LoadTexture((char*)"data/TEXTURE/gameover.png");

	return S_OK;
}

void UninitGameOver()
{

}

void UpdateGameOver()
{
	if (Keyboard_IsKeyDown(KK_A))
	{
		SetScene(SCENE_SELECT);
	}
}

void DrawGameOver()
{
	GetDeviceContext()->PSSetShaderResources
	(0, 1, GetTexture(g_GameOver.texNo));
	DrawSpriteColorRotate
	(
		SCREEN_WIDTH / 2,
		SCREEN_HEIGHT / 2,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		0,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		0,
		1.0f /1.0f,
		1.0f,
		1
	);

}