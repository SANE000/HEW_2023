//�X�v���C�g�`�揈��
#pragma once
#include "main.h"
//�}�N��

//�v���g�^�C�v�錾
//����������������ɂ��邼�I
//static float PaternNo = 0;
//float uv_w = 0.5f;//�L�����N�^�[�̉��T�C�Y
//float uv_h = 0.5f;//�L�����N�^�[�̏c�T�C�Y�@�@�c�݂����Ȋ���
//int NumPatern = 2;//�L�����N�^�[�̉��̖���
void DrawSpriteColorRotate(float posx, float posy, int size_w,
	int size_h, float kakudo, D3DXCOLOR col,
	float PaternNo,
	float uv_w,float uv_h,
	int NumPatern);
void InitSptite();
void UnInitSptite();