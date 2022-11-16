//�����蔻��̏���
#include "main.h"
#include "collision.h"
#include "player.h"
#include "cat.h"
#include "block.h"
#include "Scene.h"
#include "sound.h"


//�}�N��
//�v���g�^�C�v�錾
//���̒��ł����g��Ȃ��ϐ�
//BB�Ƃ͓����蔻��̍Œ���́�
//�l�p�`�̒��S���W�Q�ƃT�C�Y�Q�� true�Փ�
int temp = BLOCK_MAX;
 

//==========================================
//�O���[�o���ϐ�
//==========================================

//�u���b�N�ƃl�R���Ԃ������ہA
//���̃u���b�N�̂P��A�Q��̃u���b�N�����݂��邩�ǂ����������ϐ�
bool blockexist1;
bool blockexist2;
bool blockexist3;

bool enablejump;

float catjump_height;

int blocknum;


HRESULT InitCollsion()
{
	blockexist1 = false;
	blockexist2 = false;
	blockexist3 = false;

	enablejump = false;
	 
	catjump_height = 0;

	return S_OK;
}


//�����蔻��������@�������C�ɍs��
void UpdateCollision()
{
	CAT *cat = GetCat();
	PLAYER* player = GetPlayer();
	BLOCK *block = GetBlock();
	MOVE_BLOCK *m_block = GetMoveBlock();

	float CatTop = cat->pos.y - cat->h / 2;
	float CatBottom = cat->pos.y + cat->h / 2;
	float CatLeft = cat->pos.x - cat->w / 2;
	float CatRight = cat->pos.x + cat->w / 2;

	if (cat->use == true)
	{
		temp = BLOCK_MAX;

		for (int i = 0; i < BLOCK_MAX; i++)
		{
			float BlockTop = block[i].pos.y - SIZE / 2;
			float BlockBottom = block[i].pos.y + SIZE / 2;
			float BlockLeft = block[i].pos.x - BASE_SIZE / 2;
			float BlockRight = block[i].pos.x + BASE_SIZE / 2;
			//�����\���̂��g���ĂȂ�������X�L�b�v
			if (block[i].use != true)
			{
				continue;
			}
			//�����蔻����s��
			bool hit = CollisionBB(
				cat->pos, block[i].pos,
				D3DXVECTOR2(cat->w, cat->h),
				D3DXVECTOR2(BASE_SIZE, SIZE)
			);
			//�u���b�N�ɐG��Ă���
			if (hit == true)
			{
				//���u���b�N����(�d��GRAV�̉e�����r������)
				if (CatBottom - GRAV <= BlockTop && cat->pos.y < block[i].pos.y)
				{
					//�u���b�N�ƐG��Ă��鎞�̓u���b�N�ɒ��ݍ��܂Ȃ��悤�ɍ��W���Œ肷��
					cat->pos.y = BlockTop - cat->h / 2;
					temp = BLOCK_MAX;
				}
				//���u���b�N��艺
				else if (CatTop <= BlockBottom &&
					cat->pos.y - (cat->h / 2 - GRAV) > block[i].pos.y + (SIZE / 2 - GRAV))
				{
					//�u���b�N�Ƀv���C���[�̏�ʂŐG��Ă��鎞�̓W�����v�͂�0�ɂ���
					cat->jump_y = 0;
				}
				//���u���b�N���E
				else if (CatLeft <= BlockRight && cat->pos.x > BlockRight)
				{
					//�u���b�N�ƐG��Ă��鎞�̓u���b�N�ɒ��ݍ��܂Ȃ��悤�ɍ��W���Œ肷��
					cat->pos.x = BlockRight + cat->w / 2;
					//�ǂɂԂ������甽�]�B�E��
					cat->move_flag = false;
				}
				//���u���b�N��荶
				else if (CatRight >= BlockLeft && cat->pos.x < block[i].pos.x)
				{//��
					//�u���b�N�ƐG��Ă��鎞�̓u���b�N�ɒ��ݍ��܂Ȃ��悤�ɍ��W���Œ肷��
					cat->pos.x = BlockLeft - cat->w / 2;
					//�ǂɂԂ������甽�]�B����
					cat->move_flag = true;
				}
			}
			else
			{
				temp -= 1;
			}

			if (temp > 0)
			{
				cat->jump_flag = true;
				cat->nowjump_flag = 0;
			}
			else
			{
				cat->jump_flag = false;
			}
		}
		//�����u���b�N�ƔL�̓����蔻��/////////////////////////////////////////////////////////////////////
		for (int i = 0; i < MOVE_BLOCK_MAX; i++)
		{

			//�����\���̂��g���ĂȂ�������X�L�b�v
			if (m_block[i].use != true)
			{
				continue;
			}

			float BlockTopM = m_block[i].pos.y - SIZE / 2;
			float BlockBottomM = m_block[i].pos.y + SIZE / 2;
			float BlockLeftM = m_block[i].pos.x - SIZE / 2;
			float BlockRightM = m_block[i].pos.x + SIZE / 2;

			//�����蔻����s��
			bool hit = CollisionBB(
				cat->pos, m_block[i].pos,
				D3DXVECTOR2(cat->w, cat->h),
				D3DXVECTOR2(SIZE, SIZE)
			);
			//�u���b�N�ɐG��Ă���
			if (hit == true)
			{
				//�L�����u���b�N����(�d��GRAV�̉e�����r������)
				if (CatBottom - GRAV <= BlockTopM && cat->pos.y < m_block[i].pos.y)
				{
					//�u���b�N�ƐG��Ă��鎞�̓u���b�N�ɒ��ݍ��܂Ȃ��悤�ɍ��W���Œ肷��
					cat->pos.y = BlockTopM - 1 - cat->h / 2;
					cat->jump_flag = true;
					cat->nowjump_flag = 0;
				}
				//�L���u���b�N���E
				else if (CatLeft <= BlockRightM && cat->pos.x > BlockRightM)
				{
					//�u���b�N�ƐG��Ă��鎞�̓u���b�N�ɒ��ݍ��܂Ȃ��悤�ɍ��W���Œ肷��
					cat->pos.x = BlockRightM + cat->w / 2;



				}
				//�L���u���b�N��荶 
				else if (CatRight >= BlockLeftM && CatRight < m_block[i].pos.x)
				{//��
					//�u���b�N�ƐG��Ă��鎞�̓u���b�N�ɒ��ݍ��܂Ȃ��悤�ɍ��W���Œ肷��
					cat->pos.x = BlockLeftM - cat->w / 2;

					//�u���b�N�ƂԂ������Ƃ���ׂ鍂�������ׂ�֐�
					//����:moveblock�̃|�C���^,�L�|�C���^,�Ԃ������u���b�N�̓Y����
					//���ō쐬
					//CatJump(SearchJumpHeight(m_block, cat, i));

				}
			}
			else
			{
			}
		}

		//�����u���b�N�ƔL�̃W�����v�Z���T�[�̓����蔻��/////////////////////////////////////////////////////////////////////
		for (int i = 0; i < MOVE_BLOCK_MAX; i++)
		{

			//�����\���̂��g���ĂȂ�������X�L�b�v
			if (m_block[i].use != true)
			{
				continue;
			}

			float JumpSensorTopM = m_block[i].pos.y - SIZE / 2;
			float JumpSensorBottomM = m_block[i].pos.y + SIZE / 2;
			float JumpSensorLeftM = m_block[i].pos.x - SIZE / 2 - SENSOR_SIZE ;
			float JumpSensorRightM = m_block[i].pos.x + SIZE / 2 + SENSOR_SIZE;


			//�����蔻����s��
			bool hit = CollisionBB(
				cat->pos, m_block[i].pos,
				D3DXVECTOR2(cat->w + SENSOR_SIZE * 2, cat->h),
				D3DXVECTOR2(SIZE, SIZE)
			);
			//�u���b�N�ɐG��Ă���
			if (hit == true)
			{
				//�L�����u���b�N���E
				if (CatLeft <= JumpSensorRightM && cat->pos.x > JumpSensorRightM)
				{
					if (cat->move_flag == true)
					{
						//�u���b�N�ƂԂ������Ƃ���ׂ鍂�������ׂ�֐�
						//����:moveblock�̃|�C���^,�L�|�C���^,�Ԃ������u���b�N�̓Y����
						//���ō쐬

						//�W�����v����i����0�ȏ�4�������ǂ���
						//0�͉�������̃G���[�@4�͔�΂��Ɉ����Ԃ�
						if (SearchJumpHeight(m_block, cat, i) > 0 &&
							SearchJumpHeight(m_block, cat, i) < 4)
						{
							//�n�ʂɂ��Ă��邩
							if (cat->jump_flag = true)
							{
								CatJump(SearchJumpHeight(m_block, cat, i));
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

						//�W�����v����i����0�ȏ�4�������ǂ���
						//0�͉�������̃G���[�@4�͔�΂��Ɉ����Ԃ�
						if (SearchJumpHeight(m_block, cat, i) > 0 &&
							SearchJumpHeight(m_block, cat, i) < 4)
						{
							//�n�ʂɂ��Ă��邩
							if (cat->jump_flag = true)
							{
								CatJump(SearchJumpHeight(m_block, cat, i));
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

		//���u���b�N�ƔL�̃W�����v�Z���T�[�̓����蔻��/////////////////////////////////////////////////////////////////////
		for (int i = 0; i < BLOCK_MAX; i++)
		{

			//�����\���̂��g���ĂȂ�������X�L�b�v
			if (block[i].use != true)
			{
				continue;
			}

			float JumpSensorTopM = block[i].pos.y - SIZE / 2;
			float JumpSensorBottomM = block[i].pos.y + SIZE / 2;
			float JumpSensorLeftM = block[i].pos.x - BASE_SIZE / 2 - SENSOR_SIZE;
			float JumpSensorRightM = block[i].pos.x + BASE_SIZE / 2 + SENSOR_SIZE;


			//�����蔻����s��
			bool hit = CollisionBB(
				cat->pos, m_block[i].pos,
				D3DXVECTOR2(cat->w + SENSOR_SIZE * 2, cat->h),
				D3DXVECTOR2(BASE_SIZE, SIZE)
			);
			//�u���b�N�ɐG��Ă���
			if (hit == true)
			{
				//�L�����u���b�N���E
				if (CatLeft <= JumpSensorRightM && cat->pos.x > JumpSensorRightM)
				{
					if (cat->move_flag == true)
					{
						//�u���b�N�ƂԂ������Ƃ���ׂ鍂�������ׂ�֐�
						//����:moveblock�̃|�C���^,�L�|�C���^,�Ԃ������u���b�N�̓Y����
						//���ō쐬

						//�W�����v����i����0�ȏ�4�������ǂ���
						//0�͉�������̃G���[�@4�͔�΂��Ɉ����Ԃ�
						if (SearchJumpHeight(m_block, cat, i) > 0 &&
							SearchJumpHeight(m_block, cat, i) < 4)
						{
							//�n�ʂɂ��Ă��邩
							if (cat->jump_flag = true)
							{
								CatJump(SearchJumpHeight(m_block, cat, i));
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

						//�W�����v����i����0�ȏ�4�������ǂ���
						//0�͉�������̃G���[�@4�͔�΂��Ɉ����Ԃ�
						if (SearchJumpHeight(m_block, cat, i) > 0 &&
							SearchJumpHeight(m_block, cat, i) < 4)
						{
							//�n�ʂɂ��Ă��邩
							if (cat->jump_flag = true)
							{
								CatJump(SearchJumpHeight(m_block, cat, i));
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
		
		//�����u���b�N�Ɠ����Ȃ��u���b�N�̓����蔻��
		for (int i = 0; i < MOVE_BLOCK_MAX; i++)
		{
			//�����u���b�N�͑��݂���H
			if (m_block[i].use == true)
			{
				float BlockTopI2 = m_block[i].pos.y - SIZE / 2;
				float BlockBottomI2 = m_block[i].pos.y + SIZE / 2;
				//������̍\���̂�S�Ē��ׂ�
				for (int n = 0; n < BLOCK_MAX; n++)
				{
					//�����Ȃ��u���b�N�͎��݂���H
					if (block[n].use == true)
					{
						float BlockTop2 = block[n].pos.y - SIZE / 2;
						float BlockBottom2 = block[n].pos.y + SIZE / 2;
						//�����蔻��
						bool hit = CollisionBB(
							m_block[i].pos, block[n].pos,
							D3DXVECTOR2(SIZE, SIZE),
							D3DXVECTOR2(BASE_SIZE, SIZE)
						);
						if (hit == true)
						{
							//N�u���b�N����(�d��GRAV�̉e�����r������)
							if (BlockBottomI2 - GRAV <= BlockTop2 && m_block[i].pos.y < block[n].pos.y)
							{
								//�u���b�N�ƐG��Ă��鎞�̓u���b�N�ɒ��ݍ��܂Ȃ��悤�ɍ��W���Œ肷��
								m_block[i].Speed.y = 0;
								m_block[i].pos.y = BlockTop2 - 1 - SIZE / 2;
							}
						}
					}
				}
			}
		}
		//�����u���b�N���m�̓����蔻��/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		for (int i = 0; i < MOVE_BLOCK_MAX; i++)
		{	
			//�u���b�N�͑��݂���H
			if (m_block[i].use == true)
			{
				//���݂��������Ă�������
				float BlockTopI = m_block[i].pos.y - SIZE / 2;
				float BlockBottomI = m_block[i].pos.y + SIZE / 2;
				float BlockLeftI = m_block[i].pos.x - SIZE / 2;
				float BlockRightI = m_block[i].pos.x + SIZE / 2;
				//������̍\���̂�S�Ē��ׂ�
				for (int n = 0; n < MOVE_BLOCK_MAX; n++)
				{
					if (m_block[n].use == true)
					{
						//�����Ǝ����̓����蔻��͂Ƃ�Ȃ��ŃX�L�b�v
						if (i == n)
						{
							continue;
						}
						//���݂������莩���ȊO������������
						float BlockTopN = m_block[n].pos.y - SIZE / 2;
						float BlockBottomN = m_block[n].pos.y + SIZE / 2;
						float BlockLeftN = m_block[n].pos.x - SIZE / 2;
						float BlockRightN = m_block[n].pos.x + SIZE / 2;
						//�����蔻��
						bool hit = CollisionBB(
							m_block[i].pos, m_block[n].pos,
							D3DXVECTOR2(SIZE, SIZE),
							D3DXVECTOR2(SIZE, SIZE)
						);
						if (hit == true)
						{
							//N�u���b�N����(�d��GRAV�̉e�����r������)
							if ( m_block[i].pos.y < m_block[n].pos.y)
							{
								//BlockBottomI - GRAV  <= BlockTopN &&

								//���ɂ���u���b�N���n�ʂɐG��Ă���u���b�N�Ȃ̂��m���߂Ă����Ȃ瓖���蔻��Ŏ~�܂鏈���̒ǉ��̕K�v�����邩��
								if (m_block[i].pos.x - SIZE / 2 <= m_block[n].pos.x && m_block[i].pos.x + SIZE / 2 >= m_block[n].pos.x)
								{
									if (m_block[i].Speed.y == 0 && m_block[n].Speed.y != 0)
									{
										//�u���b�N�ƐG��Ă��鎞�̓u���b�N�ɒ��ݍ��܂Ȃ��悤�ɍ��W���Œ肷��
										m_block[n].Speed.y = 0;
										m_block[n].pos.y = BlockBottomI +1 + SIZE / 2;
										//block[i].Hit = true;
										//temp = BLOCK_MAX;
									}
									else if (m_block[n].Speed.y == 0 && m_block[i].Speed.y != 0)
									{
										m_block[i].Speed.y = 0;
										m_block[i].pos.y = BlockTopN -1 - SIZE / 2;
									}
									
									
								}
								
							}
							////N�u���b�N��艺
							//
							//if (BlockTopI <= BlockBottomN &&
							//	m_block[i].pos.y - (block[i].h / 2 - GRAV) - 10 > block[n].pos.y + (block[n].h / 2 - GRAV))
							//{

							//	//���ɂ���u���b�N���n�ʂɐG��Ă���u���b�N�Ȃ̂��m���߂Ă����Ȃ瓖���蔻��Ŏ~�܂鏈���̒ǉ��̕K�v�����邩��
							//	if (m_block[i].pos.x == m_block[n].pos.x)
							//	{
							//		if (m_block[i].Speed.y == 0 || m_block[n].Speed.y == 0)
							//		{
							//			//�u���b�N�ƐG��Ă��鎞�̓u���b�N�ɒ��ݍ��܂Ȃ��悤�ɍ��W���Œ肷��
							//			m_block[i].Speed.y = 0;
							//			m_block[n].Speed.y = 0;
							//			m_block[i].pos.y = BlockTopN - SIZE / 2;
							//			//block[i].Hit = true;
							//			//temp = BLOCK_MAX;
							//		}

							//	}

							//}
							//N�u���b�N���E
							if (BlockLeftI <= BlockRightN && m_block[i].pos.x > BlockRightN)
							{
								//�u���b�N�ƐG��Ă��鎞�̓u���b�N�ɒ��ݍ��܂Ȃ��悤�ɍ��W���Œ肷��
								if (m_block[i].pos.y - SIZE / 2 <= m_block[n].pos.y && m_block[i].pos.y + SIZE / 2 >= m_block[n].pos.y)
								{
									if (m_block[i].Speed.y == 0 && m_block[n].Speed.y != 0)
									{
										//�u���b�N�ƐG��Ă��鎞�̓u���b�N�ɒ��ݍ��܂Ȃ��悤�ɍ��W���Œ肷��
										
										m_block[n].Speed.y = 0;
										m_block[n].pos.x = BlockLeftI - SIZE / 2;
										m_block[n].pos.y = m_block[i].pos.y;
										
										//block[i].Hit = true;
										//temp = BLOCK_MAX;
									}
									else if (m_block[n].Speed.y == 0 && m_block[i].Speed.y != 0)
									{
										m_block[i].Speed.y = 0;
										m_block[i].pos.x = BlockRightN + SIZE / 2;
										m_block[i].pos.y = m_block[n].pos.y;
									}
									
								}
							}
							//N�u���b�N��荶 
							else if (BlockRightI >= BlockLeftN && BlockRightI < m_block[n].pos.x)
							{//��

								if (m_block[i].pos.y - SIZE / 2 <= m_block[n].pos.y && m_block[i].pos.y + SIZE / 2 >= m_block[n].pos.y)
								{
									if (m_block[i].Speed.y == 0 && m_block[n].Speed.y != 0)
									{
										//�u���b�N�ƐG��Ă��鎞�̓u���b�N�ɒ��ݍ��܂Ȃ��悤�ɍ��W���Œ肷��

										m_block[n].Speed.y = 0;
										m_block[n].pos.x = BlockRightI + SIZE / 2;
										m_block[n].pos.y = m_block[i].pos.y;

										//block[i].Hit = true;
										//temp = BLOCK_MAX;
									}
									else if (m_block[n].Speed.y == 0 && m_block[i].Speed.y != 0)
									{
										m_block[i].Speed.y = 0;
										m_block[i].pos.x = BlockLeftN - SIZE/ 2;
										m_block[i].pos.y = m_block[n].pos.y;
									}
								}
								
							}
							//N�u���b�N��艺
							//else if (BlockTopI <= BlockBottomN &&
							//	m_block[i].pos.y - (SIZE / 2 - GRAV) > m_block[n].pos.y + (SIZE / 2 - GRAV))
							//{
							//	m_block[i].pos.y = BlockBottomN + SIZE / 2;
							//}
						}
						//�W�����v�֌W�͂��Ƃ�
						//else
						//{
						//	temp -= 1;
						//}

						//if (temp > 0)
						//{
						//	cat->jump_flug = true;
						//}
						//else
						//{
						//	cat->jump_flug = false;
						//}
					}
				}
			}
		}
	}
}

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
	//����3���������
	return true;//��4�����z������Փ˂��Ă�����Ă��Ƃ�����true
}

//�u���b�N�ƂԂ������Ƃ���ׂ鍂�������ׂ�֐�
//����:moveblock�̃|�C���^,�L�|�C���^,�Ԃ������u���b�N�̓Y����
float SearchJumpHeight(MOVE_BLOCK* mb, CAT* c, int i)
{
	//�W�����v�t���O��true��������
					//���ɂ��Ă�����
	if (GetJumpFlag() == true)
	{

		//�S�u���b�N��T�m
		//�Ԃ������u���b�N�Ɠ���x���W�ň��̍����̃u���b�N��T��
		//���ꂪ����������̍����̃u���b�N��T��
		//�S������ΎO���W�����v�@�W�����v�̍��������߂�
		for (int b = 0; b < MOVE_BLOCK_MAX; b++)
		{
			//x���W�������Ȃ�
			if (mb[b].pos.x == mb[i].pos.x)
			{
				//y�������Ȃ�
				if (mb[b].pos.y <= (mb[i].pos.y - SIZE / 2) &&
					mb[b].pos.y >= (mb[i].pos.y - (SIZE + SIZE / 2)))
				{
					blockexist1 = true;
				}
				//2��Ȃ�
				else if (mb[b].pos.y <= (mb[i].pos.y - (SIZE + SIZE / 2)) &&
					mb[b].pos.y >= (mb[i].pos.y - (SIZE * 2 + SIZE / 2)))
				{
					blockexist2 = true;
				}
				//3��Ȃ�
				else if (mb[b].pos.y <= (mb[i].pos.y - (SIZE * 2 + SIZE / 2)) &&
					mb[b].pos.y >= (mb[i].pos.y - (SIZE * 3 + SIZE / 2)))
				{
					blockexist3 = true;
				}

			}

			//�S���̃u���b�N������������I��
			if (blockexist1 == true && blockexist2 == true && blockexist3 == true)
			{
				break;
			}
		}

		//���i��ׂ�Ƃ����ϐ���n��
		//blockexisit��false�ɂ���

		//�ǂ�����������Ȃ�������
		if (blockexist1 == false && blockexist2 == false)
		{
			catjump_height = 1;
			enablejump = true;
		}
		//��ゾ�����݂���
		else if (blockexist1 == true && blockexist2 == false)
		{
			catjump_height = 2;
			enablejump = true;
		}
		//���Ɠ�㑶�݂���
		else if (blockexist1 == true && blockexist2 == true && blockexist3 == false)
		{
			catjump_height = 3;
			enablejump = true;
		}
		//�S�����݂���
		else if (blockexist1 == true && blockexist2 == true && blockexist3 == true)
		{
			catjump_height = 4;
			enablejump = false;
		}

		//���̃u���b�N�������݂����ۂǂ����邩�͍���l����
		//else if (blockexist1 == false && blockexist2 == true)

		blockexist1 = false;
		blockexist2 = false;
		blockexist3 = false;
	}

	return catjump_height;
}

int GetBlockNum()
{
	return blocknum;
}