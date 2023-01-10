
#include "main.h"
#include "inputx.h"
#include "keyboard.h"
#include "pose.h"
#include "scene.h"
#include "timer.h"
#include "texture.h"
#include "sprite.h"

POSE g_Pose;
static int time = 0;
static float patern = 0.0f;

void InitPose(void)
{
	g_Pose.texNo = LoadTexture((char*)"data/TEXTURE/pose.png");
	g_Pose.use = false;

	patern = 0.0f;
}
void UninitPose(void) 
{
	g_Pose.use = false;
}
void UpdatePose(void)
{
	if (time > 0)
	{
		time -= 1;
	}



	if (Keyboard_IsKeyDown(KK_SPACE) && time <= 0 && patern == 0.0f || IsButtonTriggered(0, XINPUT_GAMEPAD_B) && patern == 0.0f)
	{
		g_Pose.use = false;
	}
	if (Keyboard_IsKeyDown(KK_SPACE) && time <= 0 && patern == 1.0f || IsButtonTriggered(0, XINPUT_GAMEPAD_B) && patern == 1.0f)
	{
		g_Pose.use = false;
		SetScene(SCENE_SHOP);
		time = WAIT_TIME;
		

	}
	if (Keyboard_IsKeyDown(KK_SPACE) && time <= 0 && patern == 2.0f || IsButtonTriggered(0, XINPUT_GAMEPAD_B) && patern == 2.0f)
	{
		g_Pose.use = false;
		SetScene(SCENE_SELECT);
		time = WAIT_TIME;

	}

	if (patern < 2.0f)
	{
		if (Keyboard_IsKeyDown(KK_DOWN) && time <= 0 || GetThumbLeftY(0) < 0 && time <= 0)
		{//‰º
			patern += 1.0f;
			time = WAIT_TIME;
		}
	}
	if (patern > 0.0f)
	{
		if (Keyboard_IsKeyDown(KK_UP) && time <= 0 || GetThumbLeftY(0) > 0 && time <= 0)
		{//ã
			patern -= 1.0f;
			time = WAIT_TIME;
		}
	}

}
void DrawPose(void) 
{
	GetDeviceContext()->PSSetShaderResources
	(0, 1, GetTexture(g_Pose.texNo));
	DrawSpriteColorRotate
	(
		SCREEN_WIDTH / 2,
		SCREEN_HEIGHT / 2,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		0,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f),
		patern,
		1.0f / 3.0f,
		1.0f,
		3
	);
}

POSE* GetPose(void)
{
	return &g_Pose;
}
