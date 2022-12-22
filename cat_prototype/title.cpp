

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
		1.0f,//��
		1.0f,//�c
		1//������
	);
}
