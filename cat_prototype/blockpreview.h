#ifndef PREVIEW_H
#define PREVIEW_H
#pragma once

#include "main.h"
#include "renderer.h"

#define MOVE_BLOCK_MAX 50
#define PREVIEW_BLOCK_MAX 10

struct MOVE_BLOCK
{
	//�L�����͂قƂ�ǌ��܂��Ă鋤�ʕ��i������
	//�\���̎g�p���t���O
	bool use = false;
	//�\�����W
	D3DXVECTOR2 pos;
	//��]�p�x
	float rot;
	//�e�N�X�`���ԍ�
	int texNo;
	//�F
	D3DXCOLOR col;
	//�X�N���[���p�u���b�N�ړ��x�N�g��
	D3DXVECTOR2 Speed;
	//�u���b�N�̎�ޔ��ʗp�ϐ�
	int type;
	//�u���b�N�p�^�[��
	float Patern;

	//�u���b�N��ݒu����ۂɒl������B
	//���u���b�N��ݒu����Ƃ��͑O�Ƃ͈Ⴄ�l������B�@��x�ɒu���u���b�N���O���[�v�ƂƂ炦�Ĕ��ʂ��邽�߂̕ϐ�
	int group;

};

struct PREVIEW_BLOCK
{
	//�\���̎g�p���t���O
	bool use;
	//�\�����W
	D3DXVECTOR2 pos;
	//��]�p�x
	float rot;
	//�e�N�X�`���ԍ�
	int texNo;
	//�F
	D3DXCOLOR col;
};

//�v���g�^�C�v�錾
HRESULT InitPreview();
void UnInitPreview();
void UpdatePreview();
void DrawPreview();
//�S���̎d�l�t���O��false�ɂ���
void FalsePreviewBlock();
//false�����݂��邩�ǂ����`�F�b�N����	�S��true�̎��͔������u���b�N���g���؂����Ƃ������ƂɂȂ�
bool FalseExistCheck();
//Move�u���b�N���Z�b�g����
void SetMoveBlock();
void BlockPreview(D3DXVECTOR2 pos);
void UpdateBlockPreview(D3DXVECTOR2 pos);
//�|�C���^��Ԃ�
PREVIEW_BLOCK *GetPreviewBlock();
MOVE_BLOCK *GetMoveBlock();
#endif//!PREVIEW_H