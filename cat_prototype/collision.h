//////////////////////////�����蔻������
#pragma once

#include "cat.h"
#include "block.h"
//�}�N����`
#define SENSOR_SIZE	(10.0f)		//�W�����v�Z���T�[�̉��T�C�Y



//==============================
//�v���g�^�C�v�錾
//==============================
HRESULT InitCollsion();
void UpdateCollision();//�����蔻�����C�ɍs��

bool CollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2,
	D3DXVECTOR2 size1, D3DXVECTOR2 size2);

float SearchJumpHeight(MOVE_BLOCK* mb, CAT* c, int i);
int GetBlockNum();

