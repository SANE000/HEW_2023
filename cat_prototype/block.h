#pragma once

#include "main.h"

//�}�N����`
#define BLOCK_MAX 100
#define ONTIME 69.0f
//�\���̒�`
struct BLOCK
{
	//�\���̎g�p���t���O
	bool use = true;
	//�`��t���O
	bool draw_use = true;
	//�{�^���I���t���O
	bool button = false;
	//�{�^���ɏ���Ă��鎞�Ԃ��Ƃ�
	float ontime;
	//�\�����W
	D3DXVECTOR2 pos;
	//���[�v����W
	D3DXVECTOR2 warpos;
	//��]�p�x
	float rot = 0;
	//�e�N�X�`���ԍ�
	int texNo;
	//�F
	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//�X�N���[���p�u���b�N�ړ��x�N�g��
	D3DXVECTOR2 Speed = D3DXVECTOR2(0, 0);
	//��ޗp�̃A�j���ԍ�
	//�f�t�H���g�̓X�e�[�W�ʂɗp�ӂ��悤
	float Patern = 0.0f;
	//�ړ�����z�p+-limit
	float limitmax = 0.0f;
	float limitmin = 0.0f;
	//�N���t���O
	bool moveflug;
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
