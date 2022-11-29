#include "main.h"
#include "renderer.h"
#include "gameover.h"
#include "texture.h"
#include "scene.h"
#include "inputx.h"
#include "keyboard.h"
#include "sprite.h"

//====================
//ƒOƒ[ƒoƒ‹
//====================
static    GAMEOVER  g_GameOver;
static int time = 0;
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
	if (time > 0)
	{
		time -= 1;
	}

	if (Keyboard_IsKeyDown(KK_A) && time <= 0 || IsButtonTriggered(0, XINPUT_GAMEPAD_B) && time <= 0)
	{
		SetScene(SCENE_SELECT);
		time = WAIT_TIME;
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