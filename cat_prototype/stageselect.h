#pragma once

#include "main.h"
#include "renderer.h"

#define FIELD_MAX   6
#define STAGE_MAX   3

struct FIELD
{
	//�\���̎g�p���t���O
	bool use = true;
	//�\�����W
	D3DXVECTOR2 pos;
	//�T�C�Y
	D3DXVECTOR2 size;
	//��]�p�x
	float rot = 0;
	//�e�N�X�`���ԍ�
	int texNo;
	//�F
	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//��ޗp�̃A�j���ԍ�
	float Patern = 0;
};

struct STAGE
{
	//�\���̎g�p���t���O
	bool use = true;
	//�\�����W
	D3DXVECTOR2 pos;
	//�T�C�Y
	D3DXVECTOR2 size;
	//��]�p�x
	float rot = 0;
	//�e�N�X�`���ԍ�
	int texNo;
	//�F
	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//��ޗp�̃A�j���ԍ�
	float Patern = 0;

};

//�v���g�^�C�v�錾
HRESULT InitStageSelect();
void UnInitStageSelect();
void UpdateStageSelect();
void DrawStageSelect();

int SetStage();
int SetField();
