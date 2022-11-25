#pragma once

#include "main.h"
#include "renderer.h"

//------------------------
//�}�N����`
//------------------------
#define DOG_MAX	  (3)
#define DOG_SPEED (2.0f)

#define DOG_SIZE_W (60)
#define DOG_SIZE_H (60)
//#define DOG_INIT_X (60)
//#define DOG_INIT_Y (240)

//------------------------
//�\���̒�`
//------------------------
struct DOG
{
	bool		  use;			//�g�p���t���O
	bool          move_flag;	//�L�߂Â��Ă����t���O
	bool          jump_flag;
	D3DXVECTOR2   pos;			//�\�����W
	float		  rot;			//��]�p�x
	D3DXVECTOR2   dir;          //�i�s����
	int			  texNo;		//�e�N�X�`���ԍ�
	float		  w, h;			//dog�T�C�Y
	D3DXVECTOR2   move;			//�ړ��X�s�[�h
	D3DXCOLOR	  col;			//�F
	float         framewait;
	int           ugoki;
	float         anime;
};

//------------------------
//�v���g�^�C�v�錾
//------------------------
HRESULT InitDog();
void UnInitDog();
void UpdateDog();
void DrawDog();

DOG* GetDog();

void ChangeDogMoveFlag(DOG* d);