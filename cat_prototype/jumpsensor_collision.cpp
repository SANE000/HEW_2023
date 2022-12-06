
#include "cat.h"
#include "block.h"
#include "blockpreview.h"
#include "gimmick_wall.h"

#include "collision.h"


#include "jumpsensor_collision.h"

void UpdateJumpSensorCollision()
{
	CAT *cat = GetCat();

	BLOCK *block = GetBlock();
	MOVE_BLOCK *m_block = GetMoveBlock();
	G_WALL* gimmickwall = GetGimmickWall();


	float CatTop = cat->pos.y - CAT_SIZE_H / 2;
	float CatBottom = cat->pos.y + CAT_SIZE_H / 2;
	float CatLeft = cat->pos.x - CAT_SIZE_W / 2;
	float CatRight = cat->pos.x + CAT_SIZE_W / 2;

	if (cat->use == true)
	{




		//==============================================================================================================================
		//		//�u���b�N�W�����v�Z���T�[�ƔL�̓����蔻��//////////////////////////////////////////////////////////////////////////////
		//==============================================================================================================================
		for (int i = 0; i < BLOCK_MAX; i++)
		{

			//�����\���̂��g���ĂȂ�������X�L�b�v
			if (block[i].use != true)
			{
				continue;
			}

			float JumpSensorTopM = block[i].pos.y - SIZE / 2;
			float JumpSensorBottomM = block[i].pos.y + SIZE / 2;
			float JumpSensorLeftM = block[i].pos.x - SIZE / 2 - SENSOR_SIZE;
			float JumpSensorRightM = block[i].pos.x + SIZE / 2 + SENSOR_SIZE;

			//�����蔻����s��
			bool hit = CollisionBB(
				cat->pos, block[i].pos,
				D3DXVECTOR2(SIZE + SENSOR_SIZE * 2, 1.0f),
				D3DXVECTOR2(SIZE + SENSOR_SIZE * 2, SIZE)
			);
			//�u���b�N�ɐG��Ă���
			if (hit == true)
			{
				//�ڂ̑O�̃u���b�N�̍������Ƃ�
				int jumpheight = SearchJumpHeightB(block, cat, i);

				//�L�����u���b�N���E
				if (CatLeft <= JumpSensorRightM && cat->pos.x > JumpSensorRightM)
				{
					if (cat->move_flag == true)
					{
						//�u���b�N�ƂԂ������Ƃ���ׂ鍂�������ׂ�֐�
						//����:moveblock�̃|�C���^,�L�|�C���^,�Ԃ������u���b�N�̓Y����
						//���ō쐬

						//�W�����v����i����0�ȏ�2�������ǂ���
						//0�͉�������̃G���[�@2�͔�΂��Ɉ����Ԃ�
						if (jumpheight > 0 &&
							jumpheight < 2)
						{
							//�n�ʂɂ��Ă��邩
							if (cat->jump_flag == true)
							{
								CatJump(jumpheight);
							}
						}
						else
						{
							if (cat->jump_flag == true)
							{
								//�����Ԃ�
								ChangeMoveFlag(cat);
							}
						}

					}
				}
				//�L�����u���b�N��荶
				else if (CatRight >= JumpSensorLeftM && CatRight < block[i].pos.x)
				{//��

					if (cat->move_flag == false)
					{
						//�u���b�N�ƂԂ������Ƃ���ׂ鍂�������ׂ�֐�
						//����:moveblock�̃|�C���^,�L�|�C���^,�Ԃ������u���b�N�̓Y����
						//���ō쐬

						//�W�����v����i����0�ȏ�2�������ǂ���
						//0�͉�������̃G���[�@2�͔�΂��Ɉ����Ԃ�
						if (jumpheight > 0 &&
							jumpheight < 2)
						{
							//�n�ʂɂ��Ă��邩
							if (cat->jump_flag == true)
							{
								CatJump(jumpheight);
							}
						}
						else
						{
							if (cat->jump_flag == true)
							{
								//�����Ԃ�
								ChangeMoveFlag(cat);
							}
						}
					}
				}
			}
		}
		//==============================================================================================================================
		//		//MOVE�u���b�N�W�����v�Z���T�[�ƔL�̓����蔻��//////////////////////////////////////////////////////////////////////////
		//==============================================================================================================================
		for (int i = 0; i < MOVE_BLOCK_MAX; i++)
		{

			//�����\���̂��g���ĂȂ�������X�L�b�v
			if (m_block[i].use != true)
			{
				continue;
			}

			float JumpSensorTopM = m_block[i].pos.y - SIZE / 2;
			float JumpSensorBottomM = m_block[i].pos.y + SIZE / 2;
			float JumpSensorLeftM = m_block[i].pos.x - SIZE / 2 - SENSOR_SIZE;
			float JumpSensorRightM = m_block[i].pos.x + SIZE / 2 + SENSOR_SIZE;
			//�����蔻����s��
			bool hit = CollisionBB(
				cat->pos, m_block[i].pos,
				D3DXVECTOR2(SIZE + SENSOR_SIZE * 2, 1.0f),
				D3DXVECTOR2(SIZE + SENSOR_SIZE * 2 , SIZE)
			);
			//�u���b�N�ɐG��Ă���
			if (hit == true)
			{
				//�ڂ̑O�̃u���b�N�̍������Ƃ�
				int jumpheight = SearchJumpHeight(m_block, cat, i);

				//�L�����u���b�N���E
				if (CatLeft <= JumpSensorRightM && cat->pos.x > JumpSensorRightM)
				{
					if (cat->move_flag == true)
					{
						//�u���b�N�ƂԂ������Ƃ���ׂ鍂�������ׂ�֐�
						//����:moveblock�̃|�C���^,�L�|�C���^,�Ԃ������u���b�N�̓Y����
						//���ō쐬

						//�W�����v����i����0�ȏ�2�������ǂ���
						//0�͉�������̃G���[�@2�͔�΂��Ɉ����Ԃ�
						if (jumpheight > 0 &&
							jumpheight < 2)
						{
							//�n�ʂɂ��Ă��邩
							if (cat->jump_flag == true)
							{
								CatJump(jumpheight);
							}
						}
						else
						{
							//�����Ԃ�
							ChangeMoveFlag(cat);
						}

					}
				}
				//�L�����u���b�N��荶
				else if (CatRight >= JumpSensorLeftM && CatRight < m_block[i].pos.x)
				{//��

					if (cat->move_flag == false)
					{
						//�u���b�N�ƂԂ������Ƃ���ׂ鍂�������ׂ�֐�
						//����:moveblock�̃|�C���^,�L�|�C���^,�Ԃ������u���b�N�̓Y����
						//���ō쐬

						//�W�����v����i����0�ȏ�2�������ǂ���
						//0�͉�������̃G���[�@2�͔�΂��Ɉ����Ԃ�
						if (jumpheight > 0 &&
							jumpheight < 2)
						{
							//�n�ʂɂ��Ă��邩
							if (cat->jump_flag == true)
							{
								CatJump(jumpheight);
							}
						}
						else
						{
							//�����Ԃ�
							ChangeMoveFlag(cat);
						}
					}
				}
			}
		}
		//==============================================================================================================================
		//		//�M�~�b�N�ǃW�����v�Z���T�[�ƔL�̓����蔻��//////////////////////////////////////////////////////////////////////////
		//==============================================================================================================================
		for (int i = 0; i < WALL_MAX; i++)
		{

			//�����\���̂��g���ĂȂ�������X�L�b�v
			if (gimmickwall[i].use != true)
			{
				continue;
			}

			float JumpSensorTopM = gimmickwall[i].pos.y - SIZE / 2;
			float JumpSensorBottomM = gimmickwall[i].pos.y + SIZE / 2;
			float JumpSensorLeftM = gimmickwall[i].pos.x - SIZE / 2 - SENSOR_SIZE;
			float JumpSensorRightM = gimmickwall[i].pos.x + SIZE / 2 + SENSOR_SIZE;
			//�����蔻����s��
			bool hit = CollisionBB(
				cat->pos, gimmickwall[i].pos,
				D3DXVECTOR2(SIZE + SENSOR_SIZE * 2, 1.0f),
				D3DXVECTOR2(SIZE + SENSOR_SIZE * 2, SIZE)
			);
			//�u���b�N�ɐG��Ă���
			if (hit == true)
			{
				//�ڂ̑O�̃u���b�N�̍������Ƃ�
				int jumpheight = SearchJumpHeightG(gimmickwall, cat, i);

				//�L�����u���b�N���E
				if (CatLeft <= JumpSensorRightM && cat->pos.x > JumpSensorRightM)
				{
					if (cat->move_flag == true)
					{
						//�u���b�N�ƂԂ������Ƃ���ׂ鍂�������ׂ�֐�
						//����:moveblock�̃|�C���^,�L�|�C���^,�Ԃ������u���b�N�̓Y����
						//���ō쐬

						//�W�����v����i����0�ȏ�2�������ǂ���
						//0�͉�������̃G���[�@2�͔�΂��Ɉ����Ԃ�
						if (jumpheight > 0 &&
							jumpheight < 2)
						{
							//�n�ʂɂ��Ă��邩
							if (cat->jump_flag == true)
							{
								CatJump(jumpheight);
							}
						}
						else
						{
							//�����Ԃ�
							ChangeMoveFlag(cat);
						}

					}
				}
				//�L�����u���b�N��荶
				else if (CatRight >= JumpSensorLeftM && CatRight < gimmickwall[i].pos.x)
				{//��

					if (cat->move_flag == false)
					{
						//�u���b�N�ƂԂ������Ƃ���ׂ鍂�������ׂ�֐�
						//����:moveblock�̃|�C���^,�L�|�C���^,�Ԃ������u���b�N�̓Y����
						//���ō쐬

						//�W�����v����i����0�ȏ�2�������ǂ���
						//0�͉�������̃G���[�@2�͔�΂��Ɉ����Ԃ�
						if (jumpheight > 0 &&
							jumpheight < 2)
						{
							//�n�ʂɂ��Ă��邩
							if (cat->jump_flag == true)
							{
								CatJump(jumpheight);
							}
						}
						else
						{
							//�����Ԃ�
							ChangeMoveFlag(cat);
						}
					}
				}
			}
		}
	}

}
