#pragma once

#include "main.h"
#include "renderer.h"

//�}�N����`
#define CAT_GOLL 1870*2//1870*2
#define CAT_SIZE_W 52
#define CAT_SIZE_H 57
#define CAT_INIT_X (CAT_SIZE_W)
#define CAT_INIT_Y 240
//�L�̈ړ����x
#define WALK (1.00f)
//�W�����v��
#define JUMP (7.0f)
//�W�����v�Z���T�[�̉��T�C�Y
#define SENSOR_SIZE	(15.0f)		


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
	//�i�s����
	D3DXVECTOR2 dir;
	//�e�N�X�`���ԍ�
	int texNo;
	//�A�j���ԍ�
	float patern;
	//�F
	D3DXCOLOR col;
	//���E���]����t���O
	bool move_flag;
	//�W�����v�t���O
	bool jump_flag;
	//���W�����v���Ă��邩�ǂ����̃t���O
	int nowjump_flag;
	//�܂Ƃ��u���b�N�ɏ���Ă��邩�ǂ����̃t���O
	bool tumetogi_flag;
	//�W�����v��
	float jump_y;
	//�W�����v���E���x
	float limit_jump;
	//���ԃ|�C���g�t���O
	bool half_flag;
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

//���ԃ|�C���g�t���O��Ԃ�
bool HalfWayFlag();