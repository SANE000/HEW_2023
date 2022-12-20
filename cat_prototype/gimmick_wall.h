#pragma once

#include <d3dx9.h>

//==========================================
//�}�N����`
//==========================================
#define WALL_MAX 30

//�\���̒�`
struct G_WALL
{
	//�\���̎g�p���t���O
	bool use = true;
	//�{�^���I���t���O
	bool button = false;
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
	float Patern = 0.0f;
};

//==========================================
//�v���g�^�C�v�錾
//==========================================
HRESULT InitGimmickWall();
void UninitGimmickWall();
void UpdateGimmickWall();
void DrawGimmickWall();

G_WALL* GetGimmickWall();
