
#include "main.h"
#include "jumpflag.h"
#include "cat.h"
#include "block.h"
#include "blockpreview.h"
#include"gimmick_wall.h"
#include "collision.h"

void UpdateJumpFlag()
{
	CAT* cat = GetCat();
	BLOCK* block = GetBlock();
	MOVE_BLOCK* m_block = GetMoveBlock();
	G_WALL* g_wall = GetGimmickWall();

	bool CanJump = false;

	if (cat->use == true)
	{
		//�u���b�N���m�F
		for (int i = 0; i < BLOCK_MAX; i++)
		{
			//�g���Ă��邩
			if (block[i].use != true)
			{
				continue;
			}
			//�L���牓�����͔�΂�
			else if (block[i].pos.x <(cat->pos.x - 120) || block[i].pos.x >(cat->pos.x + 120))
			{
				continue;
			}

			//�L���u���b�N�̂ق������ɂ�����
			if (cat->pos.y < block[i].pos.y)
			{
				//�L�̔���̉��ʂ��u���b�N�̏�ʂ������ɂ�����
				if (cat->pos.y + CAT_SIZE_H / 2 > block[i].pos.y - DRAW_SIZE / 2)
				{
					//�L�̒��S��x���W���u���b�N�̒��ɂ����܂��Ă�����
					//�P�W�͔L�̃p�^�[���؂�ւ��ŗ����Ă��Ȃ��̂ɗ�����G�ɂȂ邽�ߔ������p�̐����i�����Ă��W�����v�t���O�͑��v�j
					if (block[i].pos.x - (DRAW_SIZE / 2) - 18 <= cat->pos.x && block[i].pos.x + (DRAW_SIZE / 2) + 18 >= cat->pos.x)
					{
						CanJump = true;
					}
				}
			}



			if (CanJump == true)
			{
				break;
			}

		}

		for (int i = 0; i < MOVE_BLOCK_MAX; i++)
		{
			if (CanJump == true)
			{
				break;
			}

			//�g���Ă��邩
			if (m_block[i].use != true)
			{
				continue;
			}
			//�L���牓�����͔�΂�
			else if (m_block[i].pos.x <(cat->pos.x - 120) || m_block[i].pos.x >(cat->pos.x + 120))
			{
				continue;
			}

			//�L���u���b�N�̂ق������ɂ�����
			if (cat->pos.y < m_block[i].pos.y)
			{
				//�L�̔���̉��ʂ��u���b�N�̏�ʂ������ɂ�����
				if (cat->pos.y + CAT_SIZE_H / 2 > m_block[i].pos.y - DRAW_SIZE / 2)
				{
					//�L�̒��S��x���W���u���b�N�̒��ɂ����܂��Ă�����
					//�P�W�͔L�̃p�^�[���؂�ւ��ŗ����Ă��Ȃ��̂ɗ�����G�ɂȂ邽�ߔ������p�̐����i�����Ă��W�����v�t���O�͑��v�j
					if (m_block[i].pos.x - (DRAW_SIZE / 2) - 18 <= cat->pos.x && m_block[i].pos.x + (DRAW_SIZE / 2) + 18 >= cat->pos.x)
					{
						CanJump = true;
					}
				}
			}

		}

		for (int i = 0; i < WALL_MAX; i++)
		{
			if (CanJump == true)
			{
				break;
			}

			//�g���Ă��邩
			if (g_wall[i].use != true)
			{
				continue;
			}
			//�L���牓�����͔�΂�
			else if (g_wall[i].pos.x <(cat->pos.x - 120) || g_wall[i].pos.x >(cat->pos.x + 120))
			{
				continue;
			}

			//�L���u���b�N�̂ق������ɂ�����
			if (cat->pos.y < g_wall[i].pos.y)
			{
				//�L�̔���̉��ʂ��u���b�N�̏�ʂ������ɂ�����
				if (cat->pos.y + CAT_SIZE_H / 2 > g_wall[i].pos.y - DRAW_SIZE / 2)
				{
					//�L�̒��S��x���W���u���b�N�̒��ɂ����܂��Ă�����
					//�P�W�͔L�̃p�^�[���؂�ւ��ŗ����Ă��Ȃ��̂ɗ�����G�ɂȂ邽�ߔ������p�̐����i�����Ă��W�����v�t���O�͑��v�j
					if (g_wall[i].pos.x - (DRAW_SIZE / 2) - 18 <= cat->pos.x && g_wall[i].pos.x + (DRAW_SIZE / 2) + 18 >= cat->pos.x)
					{
						CanJump = true;
					}
				}
			}


		}

	}

	if (CanJump == true)
	{
		cat->jump_flag = true;
		cat->nowjump_flag = 0;
	}
	else
	{
		cat->jump_flag = false;
	}

}
