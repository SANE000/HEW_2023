
#include "bomb.h"
#include "block.h"
#include "gimmick_wall.h"
#include "blockpreview.h"


void UpdateBomb(float x, float y)
{
	BLOCK* b = GetBlock();
	MOVE_BLOCK* m = GetMoveBlock();
	G_WALL* g = GetGimmickWall();


	//見つかったブロックの数を保持する(ぶつかったブロックの周り　8個見つかったら終了)
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

		//ぶつかったブロックから左右のブロックの範囲内
		if (b[i].pos.x >= (x - DRAW_SIZE) && b[i].pos.x <= (x + DRAW_SIZE))
		{
			//ぶつかったブロックの上下のブロックの範囲内
			if (b[i].pos.y >= (y - DRAW_SIZE) && b[i].pos.y <= (y + DRAW_SIZE))
			{
				//ブロックを壊す
				b[i].use = false;
				b[i].draw_use = false;
				findblock++;

				for (int j = 0; j < MOVE_BLOCK_MAX; j++)
				{
					if (m[j].use == false)
					{
						continue;
					}

					//壊れたブロックとX軸が同じ = 上に乗ってるブロック　
					//スピードを0から動くように変更する
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

		//ぶつかったブロックから左右のブロックの範囲内
		if (m[i].pos.x >= (x - DRAW_SIZE) && m[i].pos.x <= (x + DRAW_SIZE))
		{
			//ぶつかったブロックの上下のブロックの範囲内
			if (m[i].pos.y >= (y - DRAW_SIZE) && m[i].pos.y <= (y + DRAW_SIZE))
			{
				//ブロックを壊す
				m[i].use = false;
				findblock++;

				for (int j = 0; j < MOVE_BLOCK_MAX; j++)
				{
					if (m[j].use == false)
					{
						continue;
					}

					//壊れたブロックとX軸が同じ = 上に乗ってるブロック　
					//スピードを0から動くように変更する
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

		//ぶつかったブロックから左右のブロックの範囲内
		if (g[i].pos.x >= (x - DRAW_SIZE) && g[i].pos.x <= (x + DRAW_SIZE))
		{
			//ぶつかったブロックの上下のブロックの範囲内
			if (g[i].pos.y >= (y - DRAW_SIZE) && g[i].pos.y <= (y + DRAW_SIZE))
			{
				//ブロックを壊す
				g[i].use = false;
				findblock++;

				for (int j = 0; j < MOVE_BLOCK_MAX; j++)
				{
					if (m[j].use == false)
					{
						continue;
					}

					//壊れたブロックとX軸が同じ = 上に乗ってるブロック　
					//スピードを0から動くように変更する
					if (m[j].pos.x == g[i].pos.x)
					{
						m[j].Speed.y = GRAV;
					}
				}

			}
		}
	}




}
