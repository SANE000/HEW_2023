#include "main.h"
#include "renderer.h"
#include "gameover.h"
#include "texture.h"
#include "scene.h"
#include "inputx.h"
#include "keyboard.h"
#include "sprite.h"

//====================
//グローバル
//====================
static    GAMEOVER  g_GameOver;
static int time = 0;
static float patern = 0.0f;
HRESULT InitGameOver()
{
	g_GameOver.texNo = LoadTexture((char*)"data/TEXTURE/gameover.png");
	patern = 0.0f;
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

	if (Keyboard_IsKeyDown(KK_SPACE) && time <= 0 && patern == 0.0f || IsButtonTriggered(0, XINPUT_GAMEPAD_B) && patern == 0.0f)
	{
		SetScene(SCENE_SELECT);
		time = WAIT_TIME;
	}
	if (Keyboard_IsKeyDown(KK_SPACE) && time <= 0 && patern == 1.0f || IsButtonTriggered(0, XINPUT_GAMEPAD_B) && patern == 1.0f)
	{
		SetScene(SCENE_SHOP);
		time = WAIT_TIME;
	}
	if (Keyboard_IsKeyDown(KK_SPACE) && time <= 0 && patern == 2.0f || IsButtonTriggered(0, XINPUT_GAMEPAD_B) && patern == 2.0f)
	{
		SetScene(SCENE_GAME);
		time = WAIT_TIME;
	}

	if (patern < 2.0f)
	{
		if (Keyboard_IsKeyDown(KK_RIGHT) && time <= 0 || GetThumbLeftX(0) > 0 && time <= 0)
		{//右
			patern += 1.0f;
			time = WAIT_TIME;
		}
	}
	if (patern > 0.0f)
	{
		if (Keyboard_IsKeyDown(KK_LEFT) && time <= 0 || GetThumbLeftX(0) < 0 && time <= 0)
		{//左
			patern -= 1.0f;
			time = WAIT_TIME;
		}
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
		patern,
		1.0f /3.0f,
		1.0f,
		3
	);

}