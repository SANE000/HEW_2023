
//==========================================
//���U���g����
//==========================================
#pragma once

#include "main.h"


//==========================================
//�}�N����`
//==========================================

//�V�[���ԍ�
enum SCORE
{
	SCORE_S = 0,
	SCORE_A,
	SCORE_B,
};

//==========================================
//�v���g�^�C�v�錾
//==========================================
HRESULT InitResult();
void UninitResult();
void UpdateResult();
void DrawResult();

void SetTime(int time);

void SetBlock(int block);

//�N���A�̒l�̃Z�b�g
int SetClear();

