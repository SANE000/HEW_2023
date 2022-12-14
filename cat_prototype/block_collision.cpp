

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
//		//ギミック壁とMOVEブロック同士の当たり判定//////////////////////////////////////////////////////////////////////////////
//==============================================================================================================================
//動くブロックと動かないブロックの当たり判定
	for (int i = 0; i < MOVE_BLOCK_MAX; i++)
	{
		//動くブロックは存在する？
		if (m_block[i].use == true)
		{
			float BlockTopI = m_block[i].pos.y - SIZE / 2;
			float BlockBottomI = m_block[i].pos.y + SIZE / 2;
			//もう一つの構造体を全て調べる
			for (int n = 0; n < WALL_MAX; n++)
			{
				//ギミック壁は実在する？
				if (gimmickwall[n].use == true)
				{
					float G_Top = gimmickwall[n].pos.y - SIZE / 2;
					float G_Bottom = gimmickwall[n].pos.y + SIZE / 2;
					//当たり判定
					bool hit = CollisionBB(
						m_block[i].pos, gimmickwall[n].pos,
						D3DXVECTOR2(SIZE, SIZE),
						D3DXVECTOR2(SIZE, SIZE)
					);
					if (hit == true)
					{
						//Nブロックより上(重力GRAVの影響も排除する)
						if (BlockBottomI - GRAV <= G_Top && m_block[i].pos.y < gimmickwall[n].pos.y)
						{
							//ブロックと触れている時はブロックに沈み込まないように座標を固定する
							m_block[i].pos.y = G_Top - 1 - DRAW_SIZE / 2;
						

							//当たったギミックウォールの添え字を入れる
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
					//消えたギミックウォールに当たって止まっていたブロックの動きを元に戻す
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
	//		//動くブロックと動かないブロックの当たり判定////////////////////////////////////////////////////////////////////////////
	//==============================================================================================================================
	for (int i = 0; i < MOVE_BLOCK_MAX; i++)
	{
		//動くブロックは存在する？
		if (m_block[i].use == true)
		{
			float BlockTopI = m_block[i].pos.y - SIZE / 2;
			float BlockBottomI = m_block[i].pos.y + SIZE / 2;
			//もう一つの構造体を全て調べる
			for (int n = 0; n < BLOCK_MAX; n++)
			{
				//動かないブロックは実在する？
				if (block[n].use == true)
				{
					float BlockTop = block[n].pos.y - SIZE / 2;
					float BlockBottom = block[n].pos.y + SIZE / 2;
					//当たり判定
					bool hit = CollisionBB(
						m_block[i].pos, block[n].pos,
						D3DXVECTOR2(SIZE, SIZE),
						D3DXVECTOR2(SIZE, SIZE)
					);
					if (hit == true)
					{
						//Nブロックより上(重力GRAVの影響も排除する)
						if (BlockBottomI - GRAV <= BlockTop && m_block[i].pos.y < block[n].pos.y)
						{
							//ブロックと触れている時はブロックに沈み込まないように座標を固定する
							m_block[i].Speed.y = 0;
							m_block[i].pos.y = BlockTop - 1 - DRAW_SIZE / 2;
						}
					}
				}
			}
		}
	}

	//==============================================================================================================================
//		//MOVEブロック同士の当たり判定//////////////////////////////////////////////////////////////////////////////////////////
//==============================================================================================================================
	for (int i = 0; i < MOVE_BLOCK_MAX; i++)
	{
		//ブロックは存在する？
		if (m_block[i].use == true)
		{
			//存在が分かってから入れる
			float BlockTopI = m_block[i].pos.y - SIZE / 2;
			float BlockBottomI = m_block[i].pos.y + SIZE / 2;
			float BlockLeftI = m_block[i].pos.x - DRAW_SIZE / 2;
			float BlockRightI = m_block[i].pos.x + DRAW_SIZE / 2;
			//もう一つの構造体を全て調べる
			for (int n = 0; n < MOVE_BLOCK_MAX; n++)
			{
				if (m_block[n].use == true)
				{
					//自分と自分の当たり判定はとらないでスキップ
					if (i == n)
					{
						continue;
					}
					//存在が分かり自分以外だったら入れる
					float BlockTopN = m_block[n].pos.y - SIZE / 2;
					float BlockBottomN = m_block[n].pos.y + SIZE / 2;
					float BlockLeftN = m_block[n].pos.x - DRAW_SIZE / 2;
					float BlockRightN = m_block[n].pos.x + DRAW_SIZE / 2;
					//当たり判定
					bool hit = CollisionBB(
						m_block[i].pos, m_block[n].pos,
						D3DXVECTOR2(DRAW_SIZE, SIZE + GRAV * 2),
						D3DXVECTOR2(DRAW_SIZE, SIZE + GRAV * 2)
					);
					if (hit == true)
					{
						//Nブロックより上(重力GRAVの影響も排除する)
						if (m_block[i].pos.y < m_block[n].pos.y)
						{
							//BlockBottomI - GRAV  <= BlockTopN &&

							//下にあるブロックが地面に触れているブロックなのか確かめてそうなら当たり判定で止まる処理の追加の必要があるかも
							if (m_block[i].pos.x - DRAW_SIZE / 2 <= m_block[n].pos.x && m_block[i].pos.x + DRAW_SIZE / 2 >= m_block[n].pos.x)
							{
								
								//ギミックウォールに触っているブロックに当たった時止まる
								if (m_block[n].gimmickwall != -1 && m_block[i].gimmickwall == -1)
								{
									m_block[i].Speed.y = 0;
									//一段なのに登れない場所ができるため少し増やしました
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
									//ブロックと触れている時はブロックに沈み込まないように座標を固定する
									m_block[n].Speed.y = 0;
									m_block[n].pos.y = BlockBottomI + DRAW_SIZE / 2;
								}
								else if (m_block[n].Speed.y == 0 && m_block[i].Speed.y != 0)
								{
									m_block[i].Speed.y = 0;
									//一段なのに登れない場所ができるため少し増やしました
									m_block[i].pos.y = BlockTopN - 1 - DRAW_SIZE / 2;
								}
							}
						}
						//Nブロックより下(重力GRAVの影響も排除する)
						if (m_block[i].pos.y > m_block[n].pos.y)
						{
							//BlockBottomI - GRAV  <= BlockTopN &&

							//下にあるブロックが地面に触れているブロックなのか確かめてそうなら当たり判定で止まる処理の追加の必要があるかも
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
									//一段なのに登れない場所ができるため少し増やしました
									m_block[n].pos.y = BlockTopI - 2 - DRAW_SIZE / 2;
									m_block[n].gimmickwall = m_block[i].gimmickwall;

								}
								else if (m_block[i].Speed.y == 0 && m_block[n].Speed.y != 0)
								{
									//ブロックと触れている時はブロックに沈み込まないように座標を固定する
									m_block[n].Speed.y = 0;
									//一段なのに登れない場所ができるため少し増やしました
									m_block[n].pos.y = BlockTopI - 1 - DRAW_SIZE / 2;

								}
								else if (m_block[n].Speed.y == 0 && m_block[i].Speed.y != 0)
								{
									m_block[i].Speed.y = 0;
									m_block[i].pos.y = BlockBottomN + DRAW_SIZE / 2;

								}
							}
						}

						//Nブロックより右
						if (BlockLeftI <= BlockRightN && m_block[i].pos.x > BlockRightN)
						{
							//ブロックと触れている時はブロックに沈み込まないように座標を固定する
							if (m_block[i].pos.y - SIZE / 2 <= m_block[n].pos.y && m_block[i].pos.y + SIZE / 2 >= m_block[n].pos.y)
							{
								//同じグループのブロックか
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
										//ブロックと触れている時はブロックに沈み込まないように座標を固定する

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
						//Nブロックより左 
						else if (BlockRightI >= BlockLeftN && BlockRightI < m_block[n].pos.x)
						{//左

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
										//ブロックと触れている時はブロックに沈み込まないように座標を固定する
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
