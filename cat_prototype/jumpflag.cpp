
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
		//ブロックを確認
		for (int i = 0; i < BLOCK_MAX; i++)
		{
			//使っているか
			if (block[i].use != true)
			{
				continue;
			}
			//猫から遠い所は飛ばす
			else if (block[i].pos.x <(cat->pos.x - 120) || block[i].pos.x >(cat->pos.x + 120))
			{
				continue;
			}

			//猫よりブロックのほうが下にあって
			if (cat->pos.y < block[i].pos.y)
			{
				//猫の判定の下面がブロックの上面よりも下にあって
				if (cat->pos.y + CAT_SIZE_H / 2 > block[i].pos.y - DRAW_SIZE / 2)
				{
					//猫の中心のx座標がブロックの中におさまっていたら
					//１８は猫のパターン切り替えで落ちていないのに落ちる絵になるため微調整用の数字（無くてもジャンプフラグは大丈夫）
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

			//使っているか
			if (m_block[i].use != true)
			{
				continue;
			}
			//猫から遠い所は飛ばす
			else if (m_block[i].pos.x <(cat->pos.x - 120) || m_block[i].pos.x >(cat->pos.x + 120))
			{
				continue;
			}

			//猫よりブロックのほうが下にあって
			if (cat->pos.y < m_block[i].pos.y)
			{
				//猫の判定の下面がブロックの上面よりも下にあって
				if (cat->pos.y + CAT_SIZE_H / 2 > m_block[i].pos.y - DRAW_SIZE / 2)
				{
					//猫の中心のx座標がブロックの中におさまっていたら
					//１８は猫のパターン切り替えで落ちていないのに落ちる絵になるため微調整用の数字（無くてもジャンプフラグは大丈夫）
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

			//使っているか
			if (g_wall[i].use != true)
			{
				continue;
			}
			//猫から遠い所は飛ばす
			else if (g_wall[i].pos.x <(cat->pos.x - 120) || g_wall[i].pos.x >(cat->pos.x + 120))
			{
				continue;
			}

			//猫よりブロックのほうが下にあって
			if (cat->pos.y < g_wall[i].pos.y)
			{
				//猫の判定の下面がブロックの上面よりも下にあって
				if (cat->pos.y + CAT_SIZE_H / 2 > g_wall[i].pos.y - DRAW_SIZE / 2)
				{
					//猫の中心のx座標がブロックの中におさまっていたら
					//１８は猫のパターン切り替えで落ちていないのに落ちる絵になるため微調整用の数字（無くてもジャンプフラグは大丈夫）
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
