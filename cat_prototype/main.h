/*==============================================================================

   ���ʃw�b�_�[ [main.h]
                                                         Author : 
                                                         Date   : 
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once


#pragma warning(push)
#pragma warning(disable:4005)

#define _CRT_SECURE_NO_WARNINGS			// scanf ��warning�h�~
#include <stdio.h>

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <d3dx9.h>

#define DIRECTINPUT_VERSION 0x0800		// �x���Ώ�
#include "dinput.h"
#include "mmsystem.h"

#pragma warning(pop)



//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCREEN_WIDTH	(960)				// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(540)				// �E�C���h�E�̍���
//�e�����邩����E���W����낤
//��
#define SCREEN_LIMIT_UP (0)
//��
#define SCREEN_LIMIT_DOWN (540)
//��
#define SCREEN_LIMIT_LEFT (0)
//�E
#define SCREEN_LIMIT_RIGHT (960)
//�d��
#define GRAV 2.5f
//�L�̈ړ����x
#define WALK 0.5f
//�^�C�}�[�֘A
#define WAIT_TIME 10;
#define TIME_MAX 3
#define TIME_POS_X 530
#define TIME_POS_Y 50
#define TIME_SIZE_W 50
#define TIME_SIZE_H 50

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

