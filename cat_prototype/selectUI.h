#pragma once

#include "main.h"
#include "renderer.h"

#define UI_MAX  30


struct SelUI
{
	//�\���̎g�p���t���O
	bool use = true;
	//�\�����W
	D3DXVECTOR2 pos;
	//�T�C�Y
	D3DXVECTOR2 size;
	//��]�p�x
	float rot = 0;
	//�F
	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//�e�N�X�`���p�^�[��
	int Patern = 0;
	//�N���A�����N
	int rank;
};

//������	HRESULT�͕Ԃ�l�����m�点���郂�m�B�������s�A��
HRESULT InitselUI();
void UnInitselUI();
void UpdateselUI();
void DrawselUI();