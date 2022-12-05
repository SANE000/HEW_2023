#pragma once

#include "main.h"
#include "renderer.h"

//�}�N����`
#define BLOCK_MAX 126
#define ONTIME 23.0f
//�\���̒�`
struct BLOCK
{
	//�\���̎g�p���t���O
	bool use = true;
	//�{�^���I���t���O
	bool button = false;
	//�{�^���ɏ���Ă��鎞�Ԃ��Ƃ�
	int ontime;
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
	//�f�t�H���g�͑�����n�ʃu���b�N
	float Patern = 0.0f;
};
//�v���g�^�C�v�錾
HRESULT InitBlock();
void UnInitBlock();
void UpdateBlock();
void DrawBlock();
//�\���̂̐擪�|�C���^��Ԃ�
BLOCK *GetBlock();


double GetMapPos();

int GetStage();
