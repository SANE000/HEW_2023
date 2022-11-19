#pragma once

#include "main.h"
#include "renderer.h"

//�\���̒�`//�G�̏��͂��ׂč\���̂ɓ����I
struct ETC
{
	//�L�����͂قƂ�ǌ��܂��Ă鋤�ʕ��i������
	//�\���̎g�p���t���O
	bool use;
	//�\�����W
	D3DXVECTOR2 pos;
	//��]�p�x
	float rot;
	//�e�N�X�`���ԍ�
	int texNo;
	//���̑��̃T�C�Y
	float w, h;
	//�F
	D3DXCOLOR col;
};

//�v���g�^�C�v�錾
//������	HRESULT�͕Ԃ�l�����m�点���郂�m�B�������s�A��
HRESULT InitEtc();
void UnInitEtc();
void UpdateEtc();
void DrawEtc();
//�\���̂̐擪�|�C���^��Ԃ��@�F���g����悤��
ETC *GetEtc();