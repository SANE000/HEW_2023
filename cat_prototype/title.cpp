

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
//�}�N����`
//==========================================
#define GAMESTART_ARROW	260
#define GAMEEND_ARROW	378

#define ARROWSIZE_W		50
#define ARROWSIZE_H		50


//==========================================
//�v���g�^�C�v�錾
//==========================================
//����~����

//==========================================
//�O���[�o���ϐ�
//==========================================

typedef struct
{
	D3DXVECTOR2 Position;	//�\�����W
	D3DXVECTOR2 Size;		//�T�C�Y
	D3DXCOLOR	Color;		//�F
	float		Rotate;		//�p�x

}TITLE;

static int g_TextureNo = 0;	// �e�N�X�`�����ʎq
static int logotime = 300;
static float patern = 0.0f;

HRESULT InitTitle()
{
	g_TextureNo = LoadTexture((char*)"data/TEXTURE/title.png");
	//�^�C�g���A�j��������
	logotime = 300;
	patern = 0.0f;

	return S_OK;
}

void UninitTitle()
{
	
}

void UpdateTitle()
{
	if (logotime > 0)
	{
		logotime -= 1;
	}
	else
	{
		patern = 1.0f;
	}

	if (Keyboard_IsKeyDown(KK_ENTER) && patern == 1.0f || IsButtonTriggered(0, XINPUT_GAMEPAD_B) && patern == 1.0f) {
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
		patern,
		1.0f/2,//��
		1.0f,//�c
		2//������
	);
}
