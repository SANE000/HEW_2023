//�����蔻��̏���
#include "main.h"
#include "collision.h"
#include "player.h"
#include "cat.h"
#include "block.h"
#include "blockpreview.h"
#include "Scene.h"
#include "sound.h"
#include "gimmick_wall.h"
#include "Scene.h"

#include "cat_collision.h"
#include "dogCollision.h"
#include "jumpsensor_collision.h"
#include "block_collision.h"

//==========================================
//�O���[�o���ϐ�
//==========================================

//�L�̃W�����v�t���O�p
int temp = 0;
int m_temp = 0;
int g_temp = 0;
CAT *cat = GetCat();
PLAYER* player = GetPlayer();
BLOCK *block = GetBlock();
MOVE_BLOCK *m_block = GetMoveBlock();
G_WALL* gimmickwall = GetGimmickWall();


//�u���b�N�ƃl�R���Ԃ������ہA
//���̃u���b�N�̂P��A�Q��̃u���b�N�����݂��邩�ǂ����������ϐ�
bool blockexist1;

bool enablejump;

float catjump_height;

int blocknum;

//==============================================================================================================================
//		//�v���g�^�C�v�錾                //////////////////////////////////////////////////////////////////////////////////////
//==============================================================================================================================


//������
HRESULT InitCollsion()
{
	blockexist1 = false;

	enablejump = false;

	catjump_height = 0;

	return S_OK;
}

//�X�V�����@�����蔻�����C�ɍs��
void UpdateCollision()
{
	UpdateCatCollision();
	UpdateDogCollision();
	UpdateJumpSensorCollision();
	UpdateBlockCollision();

}

//==============================================================================================================================
//		//�W�����v�֘A�̊֐��B�@�@�@�@�@�@//////////////////////////////////////////////////////////////////////////////////////
//==============================================================================================================================

//�u���b�N�ƂԂ������Ƃ���ׂ鍂�������ׂ�֐�
//����:�Ԃ������u���b�N��x���W, y���W,�L�|�C���^
float SearchJumpHeight(float x, float y, CAT* c)
{
	//�W�����v�t���O��true��������
					//���ɂ��Ă�����
	if (GetJumpFlag() == true)
	{

		//�S�u���b�N��T�m
		//�Ԃ������u���b�N�Ɠ���x���W�ň��̍����̃u���b�N��T��
		//���ꂪ����������̍����̃u���b�N��T��
		//�S������ΎO���W�����v�@�W�����v�̍��������߂�

		for (int i = 0; i < BLOCK_MAX; i++)
		{
			//�S���̃u���b�N������������I��
			if (blockexist1 == true)
			{
				break;
			}
			//x���W����������Ȃ��Ȃ��΂�
			if (block[i].pos.x != x)
			{
				continue;
			}

			//y�������Ȃ�
			if (block[i].pos.y <= (y - SIZE / 2) &&
				block[i].pos.y >= (y - (SIZE + SIZE / 2)))
			{
				blockexist1 = true;
			}

		}

		for (int i = 0; i < MOVE_BLOCK_MAX; i++)
		{
			//�S���̃u���b�N������������I��
			if (blockexist1 == true)
			{
				break;
			}
			//x���W����������Ȃ��Ȃ��΂�
			if (m_block[i].pos.x != x)
			{
				continue;
			}

			//y�������Ȃ�
			if (m_block[i].pos.y <= (y - SIZE / 2) &&
				m_block[i].pos.y >= (y - (SIZE + SIZE / 2)))
			{
				blockexist1 = true;
			}
		}

		for (int i = 0; i < WALL_MAX; i++)
		{
			//�S���̃u���b�N������������I��
			if (blockexist1 == true)
			{
				break;
			}
			//x���W����������Ȃ��Ȃ��΂�
			if (gimmickwall[i].pos.x != x)
			{
				continue;
			}

			//y�������Ȃ�
			if (gimmickwall[i].pos.y <= (y - SIZE / 2) &&
				gimmickwall[i].pos.y >= (y - (SIZE + SIZE / 2)))
			{
				blockexist1 = true;
			}

		}


		//���i��ׂ�Ƃ����ϐ���n��
		//blockexisit��false�ɂ���

		//�ǂ�����������Ȃ�������
		if (blockexist1 == false)
		{
			catjump_height = 1;
			enablejump = true;
		}
		//��ゾ�����݂���
		else if (blockexist1 == true)
		{
			catjump_height = 2;
			enablejump = false;
		}
	}

	//���̃u���b�N�������݂����ۂǂ����邩�͍���l����
	//else if (blockexist1 == false && blockexist2 == true)

	blockexist1 = false;
	return catjump_height;
}


////�u���b�N�ƂԂ������Ƃ���ׂ鍂�������ׂ�֐� ���u���b�N�ƂԂ������Ƃ�
////����:block�̃|�C���^,�L�|�C���^,�Ԃ������u���b�N�̓Y����
//float SearchJumpHeightB(BLOCK* b, CAT* c, int i)
//{
//	//�W�����v�t���O��true��������
//					//���ɂ��Ă�����
//	if (GetJumpFlag() == true)
//	{
//
//		//�S�u���b�N��T�m
//		//�Ԃ������u���b�N�Ɠ���x���W�ň��̍����̃u���b�N��T��
//		//���ꂪ����������̍����̃u���b�N��T��
//		//�S������ΎO���W�����v�@�W�����v�̍��������߂�
//		for (int a = 0; a < BLOCK_MAX; a++)
//		{
//			//�S���̃u���b�N������������I��
//			if (blockexist1 == true)
//			{
//				break;
//			}
//			//x���W����������Ȃ��Ȃ��΂�
//			if (block[a].pos.x != b[i].pos.x)
//			{
//				continue;
//			}
//
//			//y�������Ȃ�
//			if (block[a].pos.y <= (b[i].pos.y - SIZE / 2) &&
//				block[a].pos.y >= (b[i].pos.y - (SIZE + SIZE / 2)))
//			{
//				blockexist1 = true;
//			}
//
//		}
//
//		for (int a = 0; a < MOVE_BLOCK_MAX; a++)
//		{
//			//�S���̃u���b�N������������I��
//			if (blockexist1 == true)
//			{
//				break;
//			}
//			//x���W����������Ȃ��Ȃ��΂�
//			if (m_block[a].pos.x != b[i].pos.x)
//			{
//				continue;
//			}
//
//			//y�������Ȃ�
//			if (m_block[a].pos.y <= (b[i].pos.y - SIZE / 2) &&
//				m_block[a].pos.y >= (b[i].pos.y - (SIZE + SIZE / 2)))
//			{
//				blockexist1 = true;
//			}
//		}
//
//		for (int a = 0; a < WALL_MAX; a++)
//		{
//			//�S���̃u���b�N������������I��
//			if (blockexist1 == true)
//			{
//				break;
//			}
//			//x���W����������Ȃ��Ȃ��΂�
//			if (gimmickwall[a].pos.x != b[i].pos.x)
//			{
//				continue;
//			}
//
//			//y�������Ȃ�
//			if (gimmickwall[a].pos.y <= (b[i].pos.y - SIZE / 2) &&
//				gimmickwall[a].pos.y >= (b[i].pos.y - (SIZE + SIZE / 2)))
//			{
//				blockexist1 = true;
//			}
//
//		}
//
//		//���i��ׂ�Ƃ����ϐ���n��
//		//blockexisit��false�ɂ���
//
//		//�ǂ�����������Ȃ�������
//		if (blockexist1 == false)
//		{
//			catjump_height = 1;
//			enablejump = true;
//		}
//		//��ゾ�����݂���
//		else if (blockexist1 == true)
//		{
//			catjump_height = 2;
//			enablejump = false;
//		}
//	}
//
//	//���̃u���b�N�������݂����ۂǂ����邩�͍���l����
//	//else if (blockexist1 == false && blockexist2 == true)
//
//	blockexist1 = false;
//	return catjump_height;
//}
//
////�M�~�b�N�u���b�N�ƂԂ������Ƃ���ׂ鍂�������ׂ�֐� ���u���b�N�ƂԂ������Ƃ�
////����:g_wall�̃|�C���^,�L�|�C���^,�Ԃ������u���b�N�̓Y����
//float SearchJumpHeightG(G_WALL* g, CAT* c, int i)
//{
//	//�W�����v�t���O��true��������
//					//���ɂ��Ă�����
//	if (GetJumpFlag() == true)
//	{
//
//		//�S�u���b�N��T�m
//		//�Ԃ������u���b�N�Ɠ���x���W�ň��̍����̃u���b�N��T��
//		//���ꂪ����������̍����̃u���b�N��T��
//		//�S������ΎO���W�����v�@�W�����v�̍��������߂�
//		for (int a = 0; a < BLOCK_MAX; a++)
//		{
//			//�S���̃u���b�N������������I��
//			if (blockexist1 == true)
//			{
//				break;
//			}
//			//x���W����������Ȃ��Ȃ��΂�
//			if (block[a].pos.x != g[i].pos.x)
//			{
//				continue;
//			}
//
//			//y�������Ȃ�
//			if (block[a].pos.y <= (g[i].pos.y - SIZE / 2) &&
//				block[a].pos.y >= (g[i].pos.y - (SIZE + SIZE / 2)))
//			{
//				blockexist1 = true;
//			}
//
//		}
//
//		for (int a = 0; a < MOVE_BLOCK_MAX; a++)
//		{
//			//�S���̃u���b�N������������I��
//			if (blockexist1 == true)
//			{
//				break;
//			}
//			//x���W����������Ȃ��Ȃ��΂�
//			if (m_block[a].pos.x != g[i].pos.x)
//			{
//				continue;
//			}
//
//			//y�������Ȃ�
//			if (m_block[a].pos.y <= (g[i].pos.y - SIZE / 2) &&
//				m_block[a].pos.y >= (g[i].pos.y - (SIZE + SIZE / 2)))
//			{
//				blockexist1 = true;
//			}
//		}
//
//		for (int a = 0; a < WALL_MAX; a++)
//		{
//			//�S���̃u���b�N������������I��
//			if (blockexist1 == true)
//			{
//				break;
//			}
//			//x���W����������Ȃ��Ȃ��΂�
//			if (gimmickwall[a].pos.x != g[i].pos.x)
//			{
//				continue;
//			}
//
//			//y�������Ȃ�
//			if (gimmickwall[a].pos.y <= (g[i].pos.y - SIZE / 2) &&
//				gimmickwall[a].pos.y >= (g[i].pos.y - (SIZE + SIZE / 2)))
//			{
//				blockexist1 = true;
//			}
//
//		}
//
//		//���i��ׂ�Ƃ����ϐ���n��
//		//blockexisit��false�ɂ���
//
//		//�ǂ�����������Ȃ�������
//		if (blockexist1 == false)
//		{
//			catjump_height = 1;
//			enablejump = true;
//		}
//		//��ゾ�����݂���
//		else if (blockexist1 == true)
//		{
//			catjump_height = 2;
//			enablejump = false;
//		}
//	}
//
//	//���̃u���b�N�������݂����ۂǂ����邩�͍���l����
//	//else if (blockexist1 == false && blockexist2 == true)
//
//	blockexist1 = false;
//	return catjump_height;
//}


int GetBlockNum()
{
	return blocknum;
}


//==============================================================================================================================
//		//HIT����֐��@�@�@�@�@�@�@�@�@�@�@/////////////////////////////////////////////////////////////////////////////////////
//==============================================================================================================================
bool CollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2,
	D3DXVECTOR2 size1, D3DXVECTOR2 size2)
{
	D3DXVECTOR2 min1, max1;
	D3DXVECTOR2 min2, max2;
	//�l�p�`1�̍���̍ŏ�x�ƍŏ�y
	min1.x = pos1.x - size1.x / 2;
	min1.y = pos1.y - size1.y / 2;
	//�����̂܂܂���3���@�G���������肷��Ƃ�낵
	//�l�p�`1�̉E���̍ő�x�ƍő�y
	max1.x = pos1.x + size1.x / 2;
	max1.y = pos1.y + size1.y / 2;
	//�l�p�`2�̍���̍ŏ�x�ƍŏ�y
	min2.x = pos2.x - size2.x / 2;
	min2.y = pos2.y - size2.y / 2;
	//�l�p�`1�̉E���̍ő�x�ƍő�y
	max2.x = pos2.x + size2.x / 2;
	max2.y = pos2.y + size2.y / 2;
	//�Փ˔���
	if (max1.x < min2.x)
	{
		return false;//����1�@�Փ˂��ĂȂ�
	}
	if (max1.y < min2.y)
	{
		return false;//����2�@�Փ˂��ĂȂ�
	}
	if (max2.x < min1.x)
	{
		return false;//����3�@�Փ˂��ĂȂ�
	}
	if (max2.y < min1.y)
	{
		return false;//����4�@�Փ˂��ĂȂ�
	}
	return true;//��4�����z������Փ˂��Ă�����Ă��Ƃ�����true
}
