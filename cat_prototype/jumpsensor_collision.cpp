
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
		//		//ブロックジャンプセンサーと猫の当たり判定//////////////////////////////////////////////////////////////////////////////
		//==============================================================================================================================
		for (int i = 0; i < BLOCK_MAX; i++)
		{

			//もし構造体を使ってなかったらスキップ
			if (block[i].use != true)
			{
				continue;
			}

			float JumpSensorTopM = block[i].pos.y - SIZE / 2;
			float JumpSensorBottomM = block[i].pos.y + SIZE / 2;
			float JumpSensorLeftM = block[i].pos.x - SIZE / 2 - SENSOR_SIZE;
			float JumpSensorRightM = block[i].pos.x + SIZE / 2 + SENSOR_SIZE;

			//当たり判定を行う
			bool hit = CollisionBB(
				cat->pos, block[i].pos,
				D3DXVECTOR2(SIZE + SENSOR_SIZE * 2, 1.0f),
				D3DXVECTOR2(SIZE + SENSOR_SIZE * 2, SIZE)
			);
			//ブロックに触れていて
			if (hit == true)
			{
				//目の前のブロックの高さをとる
				int jumpheight = SearchJumpHeightB(block, cat, i);

				//猫が床ブロックより右
				if (CatLeft <= JumpSensorRightM && cat->pos.x > JumpSensorRightM)
				{
					if (cat->move_flag == true)
					{
						//ブロックとぶつかったとき飛べる高さか調べる関数
						//引数:moveblockのポインタ,猫ポインタ,ぶつかったブロックの添え字
						//下で作成

						//ジャンプする段数が0以上2未満かどうか
						//0は何かしらのエラー　2は飛ばずに引き返す
						if (jumpheight > 0 &&
							jumpheight < 2)
						{
							//地面についているか
							if (cat->jump_flag == true)
							{
								CatJump(jumpheight);
							}
						}
						else
						{
							if (cat->jump_flag == true)
							{
								//引き返す
								ChangeMoveFlag(cat);
							}
						}

					}
				}
				//猫が床ブロックより左
				else if (CatRight >= JumpSensorLeftM && CatRight < block[i].pos.x)
				{//左

					if (cat->move_flag == false)
					{
						//ブロックとぶつかったとき飛べる高さか調べる関数
						//引数:moveblockのポインタ,猫ポインタ,ぶつかったブロックの添え字
						//下で作成

						//ジャンプする段数が0以上2未満かどうか
						//0は何かしらのエラー　2は飛ばずに引き返す
						if (jumpheight > 0 &&
							jumpheight < 2)
						{
							//地面についているか
							if (cat->jump_flag == true)
							{
								CatJump(jumpheight);
							}
						}
						else
						{
							if (cat->jump_flag == true)
							{
								//引き返す
								ChangeMoveFlag(cat);
							}
						}
					}
				}
			}
		}
		//==============================================================================================================================
		//		//MOVEブロックジャンプセンサーと猫の当たり判定//////////////////////////////////////////////////////////////////////////
		//==============================================================================================================================
		for (int i = 0; i < MOVE_BLOCK_MAX; i++)
		{

			//もし構造体を使ってなかったらスキップ
			if (m_block[i].use != true)
			{
				continue;
			}

			float JumpSensorTopM = m_block[i].pos.y - SIZE / 2;
			float JumpSensorBottomM = m_block[i].pos.y + SIZE / 2;
			float JumpSensorLeftM = m_block[i].pos.x - SIZE / 2 - SENSOR_SIZE;
			float JumpSensorRightM = m_block[i].pos.x + SIZE / 2 + SENSOR_SIZE;
			//当たり判定を行う
			bool hit = CollisionBB(
				cat->pos, m_block[i].pos,
				D3DXVECTOR2(SIZE + SENSOR_SIZE * 2, 1.0f),
				D3DXVECTOR2(SIZE + SENSOR_SIZE * 2 , SIZE)
			);
			//ブロックに触れていて
			if (hit == true)
			{
				//目の前のブロックの高さをとる
				int jumpheight = SearchJumpHeight(m_block, cat, i);

				//猫が床ブロックより右
				if (CatLeft <= JumpSensorRightM && cat->pos.x > JumpSensorRightM)
				{
					if (cat->move_flag == true)
					{
						//ブロックとぶつかったとき飛べる高さか調べる関数
						//引数:moveblockのポインタ,猫ポインタ,ぶつかったブロックの添え字
						//下で作成

						//ジャンプする段数が0以上2未満かどうか
						//0は何かしらのエラー　2は飛ばずに引き返す
						if (jumpheight > 0 &&
							jumpheight < 2)
						{
							//地面についているか
							if (cat->jump_flag == true)
							{
								CatJump(jumpheight);
							}
						}
						else
						{
							//引き返す
							ChangeMoveFlag(cat);
						}

					}
				}
				//猫が床ブロックより左
				else if (CatRight >= JumpSensorLeftM && CatRight < m_block[i].pos.x)
				{//左

					if (cat->move_flag == false)
					{
						//ブロックとぶつかったとき飛べる高さか調べる関数
						//引数:moveblockのポインタ,猫ポインタ,ぶつかったブロックの添え字
						//下で作成

						//ジャンプする段数が0以上2未満かどうか
						//0は何かしらのエラー　2は飛ばずに引き返す
						if (jumpheight > 0 &&
							jumpheight < 2)
						{
							//地面についているか
							if (cat->jump_flag == true)
							{
								CatJump(jumpheight);
							}
						}
						else
						{
							//引き返す
							ChangeMoveFlag(cat);
						}
					}
				}
			}
		}
		//==============================================================================================================================
		//		//ギミック壁ジャンプセンサーと猫の当たり判定//////////////////////////////////////////////////////////////////////////
		//==============================================================================================================================
		for (int i = 0; i < WALL_MAX; i++)
		{

			//もし構造体を使ってなかったらスキップ
			if (gimmickwall[i].use != true)
			{
				continue;
			}

			float JumpSensorTopM = gimmickwall[i].pos.y - SIZE / 2;
			float JumpSensorBottomM = gimmickwall[i].pos.y + SIZE / 2;
			float JumpSensorLeftM = gimmickwall[i].pos.x - SIZE / 2 - SENSOR_SIZE;
			float JumpSensorRightM = gimmickwall[i].pos.x + SIZE / 2 + SENSOR_SIZE;
			//当たり判定を行う
			bool hit = CollisionBB(
				cat->pos, gimmickwall[i].pos,
				D3DXVECTOR2(SIZE + SENSOR_SIZE * 2, 1.0f),
				D3DXVECTOR2(SIZE + SENSOR_SIZE * 2, SIZE)
			);
			//ブロックに触れていて
			if (hit == true)
			{
				//目の前のブロックの高さをとる
				int jumpheight = SearchJumpHeightG(gimmickwall, cat, i);

				//猫が床ブロックより右
				if (CatLeft <= JumpSensorRightM && cat->pos.x > JumpSensorRightM)
				{
					if (cat->move_flag == true)
					{
						//ブロックとぶつかったとき飛べる高さか調べる関数
						//引数:moveblockのポインタ,猫ポインタ,ぶつかったブロックの添え字
						//下で作成

						//ジャンプする段数が0以上2未満かどうか
						//0は何かしらのエラー　2は飛ばずに引き返す
						if (jumpheight > 0 &&
							jumpheight < 2)
						{
							//地面についているか
							if (cat->jump_flag == true)
							{
								CatJump(jumpheight);
							}
						}
						else
						{
							//引き返す
							ChangeMoveFlag(cat);
						}

					}
				}
				//猫が床ブロックより左
				else if (CatRight >= JumpSensorLeftM && CatRight < gimmickwall[i].pos.x)
				{//左

					if (cat->move_flag == false)
					{
						//ブロックとぶつかったとき飛べる高さか調べる関数
						//引数:moveblockのポインタ,猫ポインタ,ぶつかったブロックの添え字
						//下で作成

						//ジャンプする段数が0以上2未満かどうか
						//0は何かしらのエラー　2は飛ばずに引き返す
						if (jumpheight > 0 &&
							jumpheight < 2)
						{
							//地面についているか
							if (cat->jump_flag == true)
							{
								CatJump(jumpheight);
							}
						}
						else
						{
							//引き返す
							ChangeMoveFlag(cat);
						}
					}
				}
			}
		}
	}

}
