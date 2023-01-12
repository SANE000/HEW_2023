
#include "bomb.h"
#include "block.h"
#include "gimmick_wall.h"
#include "blockpreview.h"


void UpdateBomb(float x, float y)
{
	BLOCK* b = GetBlock();
	MOVE_BLOCK* m = GetMoveBlock();
	G_WALL* g = GetGimmickWall();


	//���������u���b�N�̐���ێ�����(�Ԃ������u���b�N�̎���@8����������I��)
	int findblock = 0;

	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (findblock >= 8)
		{
			break;
		}
		if (b[i].use == false)
		{
			continue;
		}

		//�Ԃ������u���b�N���獶�E�̃u���b�N�͈͓̔�
		if (b[i].pos.x >= (x - DRAW_SIZE) && b[i].pos.x <= (x + DRAW_SIZE))
		{
			//�Ԃ������u���b�N�̏㉺�̃u���b�N�͈͓̔�
			if (b[i].pos.y >= (y - DRAW_SIZE) && b[i].pos.y <= (y + DRAW_SIZE))
			{
				//�u���b�N����
				b[i].use = false;
				b[i].draw_use = false;
				findblock++;

				for (int j = 0; j < MOVE_BLOCK_MAX; j++)
				{
					if (m[j].use == false)
					{
						continue;
					}

					//��ꂽ�u���b�N��X�������� = ��ɏ���Ă�u���b�N�@
					//�X�s�[�h��0���瓮���悤�ɕύX����
					if (m[j].pos.x == b[i].pos.x)
					{
						m[j].Speed.y = GRAV;
					}
				}
			}
		}
	}

	for (int i = 0; i < MOVE_BLOCK_MAX; i++)
	{
		if (findblock >= 8)
		{
			break;
		}
		if (m[i].use == false)
		{
			continue;
		}

		//�Ԃ������u���b�N���獶�E�̃u���b�N�͈͓̔�
		if (m[i].pos.x >= (x - DRAW_SIZE) && m[i].pos.x <= (x + DRAW_SIZE))
		{
			//�Ԃ������u���b�N�̏㉺�̃u���b�N�͈͓̔�
			if (m[i].pos.y >= (y - DRAW_SIZE) && m[i].pos.y <= (y + DRAW_SIZE))
			{
				//�u���b�N����
				m[i].use = false;
				findblock++;

				for (int j = 0; j < MOVE_BLOCK_MAX; j++)
				{
					if (m[j].use == false)
					{
						continue;
					}

					//��ꂽ�u���b�N��X�������� = ��ɏ���Ă�u���b�N�@
					//�X�s�[�h��0���瓮���悤�ɕύX����
					if (m[j].pos.x == m[i].pos.x)
					{
						m[j].Speed.y = GRAV;
					}
				}

			}
		}
	}

	for (int i = 0; i < WALL_MAX; i++)
	{
		if (findblock >= 8)
		{
			break;
		}
		if (g[i].use == false)
		{
			continue;
		}

		//�Ԃ������u���b�N���獶�E�̃u���b�N�͈͓̔�
		if (g[i].pos.x >= (x - DRAW_SIZE) && g[i].pos.x <= (x + DRAW_SIZE))
		{
			//�Ԃ������u���b�N�̏㉺�̃u���b�N�͈͓̔�
			if (g[i].pos.y >= (y - DRAW_SIZE) && g[i].pos.y <= (y + DRAW_SIZE))
			{
				//�u���b�N����
				g[i].use = false;
				findblock++;

				for (int j = 0; j < MOVE_BLOCK_MAX; j++)
				{
					if (m[j].use == false)
					{
						continue;
					}

					//��ꂽ�u���b�N��X�������� = ��ɏ���Ă�u���b�N�@
					//�X�s�[�h��0���瓮���悤�ɕύX����
					if (m[j].pos.x == g[i].pos.x)
					{
						m[j].Speed.y = GRAV;
					}
				}

			}
		}
	}




}
