/*==============================================================================

   ���ʃw�b�_�[ [main.h]
                                                         Author : 
                                                         Date   : 
--------------------------------------------------------------------------------

==============================================================================*/
#ifndef MAIN_H
#define MAIN_H
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
//�u���b�N�`��,�����蔻��p
//����p�T�C�Y
#define SIZE			 (59)
//�`��p�T�C�Y
#define DRAW_SIZE		 (60)
//������
#define DEFO_SIZE_X		 (DRAW_SIZE/2)
//������
#define DEFO_SIZE_Y		 (SCREEN_HEIGHT - DEFO_SIZE_X)
//��3�{��������T�C�Y
#define BASE_SIZE	 (DRAW_SIZE*3-1)
//��3�{��������p�T�C�Y
#define BASE_DRAW_SIZE	 (DRAW_SIZE*3)
//��3�{�������ꏉ���ʒu
#define BASE_DEFO_SIZE_X (BASE_DRAW_SIZE/2)
//�d��
#define GRAV 2.5f
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
#endif // MAIN_H
