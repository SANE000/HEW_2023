#pragma once

#include "main.h"
#include "renderer.h"

//�}�N����`

//�\���̒�`
struct PLAYER
{
	//�L�����͂قƂ�ǌ��܂��Ă鋤�ʕ��i������
	//�\���̎g�p���t���O
	bool use;
	//�\�����W
	D3DXVECTOR2 pos;
	//�u���b�N�������W
	D3DXVECTOR2 SetPos;
	//��]�p�x
	float rot;
	//�e�N�X�`���ԍ�
	int texNo;
	//�A�j���ԍ�
	float patern;
	//�F
	D3DXCOLOR col;
	//���ˊԊu
	int bwait;
};


//�v���g�^�C�v�錾
//������	HRESULT�͕Ԃ�l�����m�点���郂�m�B�������s�A��
HRESULT InitPlayer();
//HRESULT InitPlayer(int a);
void UnInitPlayer();
void UpdatePlayer();
void DrawPlayer();
//�\���̂̐擪�|�C���^��Ԃ��@�F���g����悤��
PLAYER *GetPlayer();

int BlockScore();
