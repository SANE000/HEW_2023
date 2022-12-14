

#include "cat.h"
#include "block.h"
#include "blockpreview.h"
#include "gimmick_wall.h"

#include "collision.h"


#include "block_collision.h"



void UpdateBlockCollision()
{

	BLOCK *block = GetBlock();
	MOVE_BLOCK *m_block = GetMoveBlock();
	G_WALL* gimmickwall = GetGimmickWall();




//==============================================================================================================================
//		//�M�~�b�N�ǂ�MOVE�u���b�N���m�̓����蔻��//////////////////////////////////////////////////////////////////////////////
//==============================================================================================================================
//�����u���b�N�Ɠ����Ȃ��u���b�N�̓����蔻��
	for (int i = 0; i < MOVE_BLOCK_MAX; i++)
	{
		//�����u���b�N�͑��݂���H
		if (m_block[i].use == true)
		{
			float BlockTopI = m_block[i].pos.y - SIZE / 2;
			float BlockBottomI = m_block[i].pos.y + SIZE / 2;
			//������̍\���̂�S�Ē��ׂ�
			for (int n = 0; n < WALL_MAX; n++)
			{
				//�M�~�b�N�ǂ͎��݂���H
				if (gimmickwall[n].use == true)
				{
					float G_Top = gimmickwall[n].pos.y - SIZE / 2;
					float G_Bottom = gimmickwall[n].pos.y + SIZE / 2;
					//�����蔻��
					bool hit = CollisionBB(
						m_block[i].pos, gimmickwall[n].pos,
						D3DXVECTOR2(SIZE, SIZE),
						D3DXVECTOR2(SIZE, SIZE)
					);
					if (hit == true)
					{
						//N�u���b�N����(�d��GRAV�̉e�����r������)
						if (BlockBottomI - GRAV <= G_Top && m_block[i].pos.y < gimmickwall[n].pos.y)
						{
							//�u���b�N�ƐG��Ă��鎞�̓u���b�N�ɒ��ݍ��܂Ȃ��悤�ɍ��W���Œ肷��
							m_block[i].pos.y = G_Top - 1 - DRAW_SIZE / 2;
						

							//���������M�~�b�N�E�H�[���̓Y����������
							if (m_block[i].gimmickwall == -1)
							{
								m_block[i].gimmickwall = n;
								m_block[i].Speed.y = 0;

							}
						
						}
					}
				}
				else
				{
					//�������M�~�b�N�E�H�[���ɓ������Ď~�܂��Ă����u���b�N�̓��������ɖ߂�
					if (n == m_block[i].gimmickwall)
					{
						m_block[i].gimmickwall = -1;
						m_block[i].Speed.y = GRAV;
					}
				}
			}
		}
	}
	//==============================================================================================================================
	//		//�����u���b�N�Ɠ����Ȃ��u���b�N�̓����蔻��////////////////////////////////////////////////////////////////////////////
	//==============================================================================================================================
	for (int i = 0; i < MOVE_BLOCK_MAX; i++)
	{
		//�����u���b�N�͑��݂���H
		if (m_block[i].use == true)
		{
			float BlockTopI = m_block[i].pos.y - SIZE / 2;
			float BlockBottomI = m_block[i].pos.y + SIZE / 2;
			//������̍\���̂�S�Ē��ׂ�
			for (int n = 0; n < BLOCK_MAX; n++)
			{
				//�����Ȃ��u���b�N�͎��݂���H
				if (block[n].use == true)
				{
					float BlockTop = block[n].pos.y - SIZE / 2;
					float BlockBottom = block[n].pos.y + SIZE / 2;
					//�����蔻��
					bool hit = CollisionBB(
						m_block[i].pos, block[n].pos,
						D3DXVECTOR2(SIZE, SIZE),
						D3DXVECTOR2(SIZE, SIZE)
					);
					if (hit == true)
					{
						//N�u���b�N����(�d��GRAV�̉e�����r������)
						if (BlockBottomI - GRAV <= BlockTop && m_block[i].pos.y < block[n].pos.y)
						{
							//�u���b�N�ƐG��Ă��鎞�̓u���b�N�ɒ��ݍ��܂Ȃ��悤�ɍ��W���Œ肷��
							m_block[i].Speed.y = 0;
							m_block[i].pos.y = BlockTop - 1 - DRAW_SIZE / 2;
						}
					}
				}
			}
		}
	}

	//==============================================================================================================================
//		//MOVE�u���b�N���m�̓����蔻��//////////////////////////////////////////////////////////////////////////////////////////
//==============================================================================================================================
	for (int i = 0; i < MOVE_BLOCK_MAX; i++)
	{
		//�u���b�N�͑��݂���H
		if (m_block[i].use == true)
		{
			//���݂��������Ă�������
			float BlockTopI = m_block[i].pos.y - SIZE / 2;
			float BlockBottomI = m_block[i].pos.y + SIZE / 2;
			float BlockLeftI = m_block[i].pos.x - DRAW_SIZE / 2;
			float BlockRightI = m_block[i].pos.x + DRAW_SIZE / 2;
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
					float BlockLeftN = m_block[n].pos.x - DRAW_SIZE / 2;
					float BlockRightN = m_block[n].pos.x + DRAW_SIZE / 2;
					//�����蔻��
					bool hit = CollisionBB(
						m_block[i].pos, m_block[n].pos,
						D3DXVECTOR2(DRAW_SIZE, SIZE + GRAV * 2),
						D3DXVECTOR2(DRAW_SIZE, SIZE + GRAV * 2)
					);
					if (hit == true)
					{
						//N�u���b�N����(�d��GRAV�̉e�����r������)
						if (m_block[i].pos.y < m_block[n].pos.y)
						{
							//BlockBottomI - GRAV  <= BlockTopN &&

							//���ɂ���u���b�N���n�ʂɐG��Ă���u���b�N�Ȃ̂��m���߂Ă����Ȃ瓖���蔻��Ŏ~�܂鏈���̒ǉ��̕K�v�����邩��
							if (m_block[i].pos.x - DRAW_SIZE / 2 <= m_block[n].pos.x && m_block[i].pos.x + DRAW_SIZE / 2 >= m_block[n].pos.x)
							{
								
								//�M�~�b�N�E�H�[���ɐG���Ă���u���b�N�ɓ����������~�܂�
								if (m_block[n].gimmickwall != -1 && m_block[i].gimmickwall == -1)
								{
									m_block[i].Speed.y = 0;
									//��i�Ȃ̂ɓo��Ȃ��ꏊ���ł��邽�ߏ������₵�܂���
									m_block[i].pos.y = BlockTopN - 2 - DRAW_SIZE / 2;
									m_block[i].gimmickwall = m_block[n].gimmickwall;
								}
								else if (m_block[i].gimmickwall != -1 && m_block[n].gimmickwall == -1)
								{
									m_block[n].Speed.y = 0;
									m_block[n].pos.y = BlockBottomI + DRAW_SIZE / 2;
									m_block[n].gimmickwall = m_block[i].gimmickwall;

								}
								else if (m_block[i].Speed.y == 0 && m_block[n].Speed.y != 0)
								{
									//�u���b�N�ƐG��Ă��鎞�̓u���b�N�ɒ��ݍ��܂Ȃ��悤�ɍ��W���Œ肷��
									m_block[n].Speed.y = 0;
									m_block[n].pos.y = BlockBottomI + DRAW_SIZE / 2;
								}
								else if (m_block[n].Speed.y == 0 && m_block[i].Speed.y != 0)
								{
									m_block[i].Speed.y = 0;
									//��i�Ȃ̂ɓo��Ȃ��ꏊ���ł��邽�ߏ������₵�܂���
									m_block[i].pos.y = BlockTopN - 1 - DRAW_SIZE / 2;
								}
							}
						}
						//N�u���b�N��艺(�d��GRAV�̉e�����r������)
						if (m_block[i].pos.y > m_block[n].pos.y)
						{
							//BlockBottomI - GRAV  <= BlockTopN &&

							//���ɂ���u���b�N���n�ʂɐG��Ă���u���b�N�Ȃ̂��m���߂Ă����Ȃ瓖���蔻��Ŏ~�܂鏈���̒ǉ��̕K�v�����邩��
							if (m_block[i].pos.x - DRAW_SIZE / 2 <= m_block[n].pos.x && m_block[i].pos.x + DRAW_SIZE / 2 >= m_block[n].pos.x)
							{

								if (m_block[n].gimmickwall != -1 && m_block[i].gimmickwall == -1)
								{
									m_block[i].Speed.y = 0;
									m_block[i].pos.y = BlockBottomN + DRAW_SIZE / 2;
									m_block[i].gimmickwall = m_block[n].gimmickwall;
								}
								else if (m_block[i].gimmickwall != -1 && m_block[n].gimmickwall == -1)
								{
									m_block[n].Speed.y = 0;
									//��i�Ȃ̂ɓo��Ȃ��ꏊ���ł��邽�ߏ������₵�܂���
									m_block[n].pos.y = BlockTopI - 2 - DRAW_SIZE / 2;
									m_block[n].gimmickwall = m_block[i].gimmickwall;

								}
								else if (m_block[i].Speed.y == 0 && m_block[n].Speed.y != 0)
								{
									//�u���b�N�ƐG��Ă��鎞�̓u���b�N�ɒ��ݍ��܂Ȃ��悤�ɍ��W���Œ肷��
									m_block[n].Speed.y = 0;
									//��i�Ȃ̂ɓo��Ȃ��ꏊ���ł��邽�ߏ������₵�܂���
									m_block[n].pos.y = BlockTopI - 1 - DRAW_SIZE / 2;

								}
								else if (m_block[n].Speed.y == 0 && m_block[i].Speed.y != 0)
								{
									m_block[i].Speed.y = 0;
									m_block[i].pos.y = BlockBottomN + DRAW_SIZE / 2;

								}
							}
						}

						//N�u���b�N���E
						if (BlockLeftI <= BlockRightN && m_block[i].pos.x > BlockRightN)
						{
							//�u���b�N�ƐG��Ă��鎞�̓u���b�N�ɒ��ݍ��܂Ȃ��悤�ɍ��W���Œ肷��
							if (m_block[i].pos.y - SIZE / 2 <= m_block[n].pos.y && m_block[i].pos.y + SIZE / 2 >= m_block[n].pos.y)
							{
								//�����O���[�v�̃u���b�N��
								if (m_block[i].group == m_block[n].group)
								{
									if (m_block[n].gimmickwall != -1 && m_block[i].gimmickwall == -1)
									{
										m_block[i].Speed.y = 0;
										m_block[i].pos.x = BlockRightN + DRAW_SIZE / 2;
										m_block[i].pos.y = m_block[n].pos.y;
										m_block[i].gimmickwall = m_block[n].gimmickwall;
									}
									else if (m_block[i].gimmickwall != -1 && m_block[n].gimmickwall == -1)
									{
										m_block[n].Speed.y = 0;
										m_block[n].pos.x = BlockLeftI - DRAW_SIZE / 2;
										m_block[n].pos.y = m_block[i].pos.y;
										m_block[n].gimmickwall = m_block[i].gimmickwall;
									}
									else if (m_block[i].Speed.y == 0 && m_block[n].Speed.y != 0)
									{
										//�u���b�N�ƐG��Ă��鎞�̓u���b�N�ɒ��ݍ��܂Ȃ��悤�ɍ��W���Œ肷��

										m_block[n].Speed.y = 0;
										m_block[n].pos.x = BlockLeftI - DRAW_SIZE / 2;
										m_block[n].pos.y = m_block[i].pos.y;

										//block[i].Hit = true;
										//temp = BLOCK_MAX;
									}
									else if (m_block[n].Speed.y == 0 && m_block[i].Speed.y != 0)
									{
										m_block[i].Speed.y = 0;
										m_block[i].pos.x = BlockRightN + DRAW_SIZE / 2;
										m_block[i].pos.y = m_block[n].pos.y;
									}
								}


							}
						}
						//N�u���b�N��荶 
						else if (BlockRightI >= BlockLeftN && BlockRightI < m_block[n].pos.x)
						{//��

							if (m_block[i].pos.y - SIZE / 2 <= m_block[n].pos.y && m_block[i].pos.y + SIZE / 2 >= m_block[n].pos.y)
							{
								if (m_block[i].group == m_block[n].group)
								{
									if (m_block[n].gimmickwall != -1 && m_block[i].gimmickwall == -1)
									{
										m_block[i].Speed.y = 0;
										m_block[i].pos.x = BlockLeftN - DRAW_SIZE / 2;
										m_block[i].pos.y = m_block[n].pos.y;

									}
									else if (m_block[i].gimmickwall != -1 && m_block[n].gimmickwall == -1)
									{
										m_block[n].Speed.y = 0;
										m_block[n].pos.x = BlockRightI + DRAW_SIZE / 2;
										m_block[n].pos.y = m_block[i].pos.y;
										m_block[n].gimmickwall = m_block[i].gimmickwall;
									}
									else if (m_block[i].Speed.y == 0 && m_block[n].Speed.y != 0)
									{
										//�u���b�N�ƐG��Ă��鎞�̓u���b�N�ɒ��ݍ��܂Ȃ��悤�ɍ��W���Œ肷��
										m_block[n].Speed.y = 0;
										m_block[n].pos.x = BlockRightI + DRAW_SIZE / 2;
										m_block[n].pos.y = m_block[i].pos.y;
									}
									else if (m_block[n].Speed.y == 0 && m_block[i].Speed.y != 0)
									{
										m_block[i].Speed.y = 0;
										m_block[i].pos.x = BlockLeftN - DRAW_SIZE / 2;
										m_block[i].pos.y = m_block[n].pos.y;
									}
								}

							}

						}
					}
				}
			}
		}
	}



}
