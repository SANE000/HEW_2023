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
//��@���x
#define WATCH 2.0f
//�d��
#define GRAV 2.5f
//�A�����͖h�~�p�ҋ@����
#define WAIT_TIME 10;
//�^�C�}�[�֘A
#define TIME_MAX 3
#define TIME_POS_X 530
#define TIME_POS_Y 50
#define TIME_SIZE_W 50
#define TIME_SIZE_H 50
//��������
#define TIME_LIMIT 60


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
#endif // MAIN_H
