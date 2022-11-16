#pragma once

#include "main.h"
#include "renderer.h"

//�}�N����`
#define BLOCK_MAX 22
#define MOVE_BLOCK_MAX 50
#define PREVIEW_BLOCK_MAX 10


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
};

struct PREVIEW_BLOCK
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
	//�F
	D3DXCOLOR col;
};


//�v���g�^�C�v�錾
//������	HRESULT�͕Ԃ�l�����m�点���郂�m�B�������s�A��
HRESULT InitBlock();
//HRESULT InitPlayer(int a);
void UnInitBlock();
void UpdateBlock();
void DrawBlock();
//�\���̂̐擪�|�C���^��Ԃ��@�F���g����悤��
BLOCK *GetBlock();
MOVE_BLOCK *GetMoveBlock();
PREVIEW_BLOCK *GetPreviewBlock();
void SetMoveBlock();

void BlockPreview(D3DXVECTOR2 pos);
void UpdateBlockPreview(D3DXVECTOR2 pos);

//�S���̎d�l�t���O��false�ɂ���
void FalsePreviewBlock();

//false�����݂��邩�ǂ����`�F�b�N����	�S��true�̎��͔������u���b�N���g���؂����Ƃ������ƂɂȂ�
bool FalseExistCheck();