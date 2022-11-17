#pragma once

#include "main.h"
#include "renderer.h"

//�}�N����`
#define BLOCK_MAX 22

//�\���̒�`
struct BLOCK
{
	//�\���̎g�p���t���O
	bool use = true;
	//�\�����W
	D3DXVECTOR2 pos;
	//��]�p�x
	float rot = 0;
	//�e�N�X�`���ԍ�
	int texNo;
	//�F
	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//�X�N���[���p�u���b�N�ړ��x�N�g��
	D3DXVECTOR2 Speed = D3DXVECTOR2(0, 0);
	//��ޗp�̃A�j���ԍ�
	float Patern = 0;
};
//�v���g�^�C�v�錾
HRESULT InitBlock();
void UnInitBlock();
void UpdateBlock();
void DrawBlock();
//�\���̂̐擪�|�C���^��Ԃ�
BLOCK *GetBlock();
