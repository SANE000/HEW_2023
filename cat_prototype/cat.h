#pragma once

#include "main.h"
#include "renderer.h"

//�}�N����`
#define CAT_GOLL 180
#define CAT_SIZE_W 60
#define CAT_SIZE_H 60
#define CAT_INIT_X (CAT_SIZE_W)
#define CAT_INIT_Y 240


//�\���̒�`
struct CAT
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
	//�A�j���ԍ�
	float patern;
	//�L�T�C�Y
	float w, h;
	//�F
	D3DXCOLOR col;
	//���E���]����t���O
	bool move_flag;
	//�W�����v�t���O
	bool jump_flag;
	//���W�����v���Ă��邩�ǂ����̃t���O
	int nowjump_flag;
	//�W�����v��
	float jump_y;
	//�W�����v���E���x
	float limit_jump;
	//�S�[���t���O
	bool goal_flag;
};

//�v���g�^�C�v�錾
//������	HRESULT�͕Ԃ�l�����m�点���郂�m�B�������s�A��
HRESULT InitCat();
void UnInitCat();
void UpdateCat();
void DrawCat();
//�\���̂̐擪�|�C���^��Ԃ��@�F���g����悤��
CAT *GetCat();

//�W�����v�t���O�擾�֐�
bool GetJumpFlag();


//�L���W�����v���鏈�����������֐� collision�Ńu���b�N�ƂԂ������یĂяo��
void CatJump(float jumpheight);

//
void ChangeMoveFlag(CAT* c);
