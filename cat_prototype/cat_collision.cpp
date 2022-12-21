
#include "cat.h"
#include "block.h"
#include "blockpreview.h"
#include "gimmick_wall.h"

#include "collision.h"
#include "scene.h"

#include "cat_collision.h"
#include "jumpflag.h"

void UpdateCatCollision()
{
	//int temp = 0;
	//int m_temp = 0;
	//int g_temp = 0;
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
		//temp = BLOCK_MAX;
		//m_temp = MOVE_BLOCK_MAX;
		//g_temp = WALL_MAX;

		//==============================================================================================================================
		//		//動かないブロックと猫の当たり判定//////////////////////////////////////////////////////////////////////////////////////
		//==============================================================================================================================
		for (int i = 0; i < BLOCK_MAX; i++)
		{
			float BlockTop = block[i].pos.y - SIZE / 2;
			float BlockBottom = block[i].pos.y + SIZE / 2;
			float BlockLeft = block[i].pos.x - SIZE / 2;
			float BlockRight = block[i].pos.x + SIZE / 2;
			//もし構造体を使ってなかったらスキップ
			if (block[i].use != true)
			{
				//if (temp > 0)
				//{
				//	temp -= 1;
				//}
				continue;
			}
			//猫から遠い所は飛ばす
			else if (block[i].pos.x <(cat->pos.x - 90) || block[i].pos.x >(cat->pos.x + 90))
			{
				continue;
			}

			//当たり判定を行う
			bool hit = CollisionBB(
				cat->pos, block[i].pos,
				D3DXVECTOR2(CAT_SIZE_W, CAT_SIZE_H),
				D3DXVECTOR2(SIZE, SIZE)
			);
			//ブロックに触れていて
			if (hit == true)
			{
				//床ブロックより上(重力GRAVの影響も排除する)
				if (CatBottom - GRAV <= BlockTop && cat->pos.y < block[i].pos.y)
				{
					//ブロックと触れている時はブロックに沈み込まないように座標を固定する
					cat->pos.y = BlockTop - CAT_SIZE_H / 2;
					//temp = BLOCK_MAX;

					if (block[i].Patern == 2.0f)
					{
						if (block[i].pos.x - 10.0f < cat->pos.x && block[i].pos.x + 10.0f > cat->pos.x)
						{
							ChangeMoveFlag(cat);
						}
					}

					//サボテンに触れたら
					if (block[i].Patern >= 15.0f && block[i].Patern <= 16.9f)
					{
						if (block[i].pos.x - 25.0f < cat->pos.x && block[i].pos.x + 25.0f > cat->pos.x)
						{
							//ゲームオーバー
							SetScene(SCENE_GAMEOVER);
						}
					}

					//	バネブロックか砂嵐で中心あたりに乗った時跳ねる処理
					if (block[i].Patern >= 9.0f && block[i].Patern <= 11.9f || block[i].Patern >= 17.0f && block[i].Patern <= 19.9f)
					{
						if (cat->move_flag == false)
						{
							cat->patern = 8.0f;
						}
						else
						{
							cat->patern = 11.0f;
						}
						//曲がって
						block[i].Patern += 0.1f / 2;

						if (block[i].pos.x - 5.0f < cat->pos.x && block[i].pos.x + 5.0f > cat->pos.x)
						{
							//とりあえず7段	
							CatJump(7.0f);
							//飛んだ瞬間に戻る
							if (block[i].Patern >= 9.0f && block[i].Patern <= 11.9f)
							{
								block[i].Patern = 9.0f;
							}

							if (block[i].Patern >= 17.0f && block[i].Patern <= 19.9f)
							{
								block[i].Patern = 17.0f;
							}
						}//中途半端に乗った後でもバネが起動するようにしました
						else if (block[i].Patern >= 11.8f && block[i].Patern <= 11.9f || block[i].Patern >= 19.8f && block[i].Patern <= 19.9f)
						{
							//とりあえず7段	
							CatJump(7.0f);
							//飛んだ瞬間に戻る
							if (block[i].Patern >= 11.8f && block[i].Patern <= 11.9f)
							{
								block[i].Patern = 9.0f;
							}

							if (block[i].Patern >= 19.8f && block[i].Patern <= 19.9f)
							{
								block[i].Patern = 17.0f;
							}
						}
					}

					if (block[i].Patern >= 13.0f && block[i].Patern <= 14.9f)
					{
						if (block[i].Patern == 13.0f)
						{
							block[i].Patern = 14.0f;
						}
						block[i].Patern += 0.9 / ONTIME;
						block[i].ontime -= 1.0f;
						if (block[i].ontime <= 0)
						{
							//仮の番号。なにも描画しない
							block[i].Patern = 35.0f;
							block[i].use = false;
						}
					}
					//ワープ
					if (block[i].Patern == 31.0f)
					{
						if (block[i].pos.x - 15.0f < cat->pos.x && block[i].pos.x + 15.0f > cat->pos.x)
						{
							cat->pos = block[i].warpos;
						}
					}

					if (block[i].Patern == 22.0f)
					{
						cat->onmove = 0.5f;
					}
					else if (block[i].Patern == 23.0f || block[i].Patern == 29.0f)
					{
						cat->onmove = -0.5f;
					}
					else
					{
						cat->onmove = 0.0f;
					}

					if (block[i].button == true)
					{
						//触れた瞬間falseにならないように中心あたりでfalseにする
						if (block[i].pos.x - 15.0f < cat->pos.x && block[i].pos.x + 15.0f > cat->pos.x)
						{
							block[i].button = false;
							block[i].use = false;
						}

					}
				}
				//床ブロックより下
				else if (CatTop <= BlockBottom &&
					cat->pos.y - (CAT_SIZE_H / 2 - GRAV) > block[i].pos.y + (SIZE / 2 - GRAV))
				{
					//ブロックにプレイヤーの上面で触れている時はジャンプ力を0にする
					cat->jump_y = 0;

					//if (temp > 0)
					//{
					//	temp -= 1;
					//}
				}
				//床ブロックより右
				else if (CatLeft <= BlockRight && cat->pos.x > BlockRight)
				{
					//ブロックと触れている時はブロックに沈み込まないように座標を固定する
					cat->pos.x = BlockRight + CAT_SIZE_W / 2;
					//サボテンに触れたら
					if (block[i].Patern >= 15.0f && block[i].Patern <= 16.9f)
					{
						//ゲームオーバー
						SetScene(SCENE_GAMEOVER);
					}
					//壁にぶつかったら反転。右へ
					//ChangeMoveFlag(cat);

					//if (temp > 0)
					//{
					//	temp -= 1;
					//}

				}
				//床ブロックより左
				else if (CatRight >= BlockLeft && cat->pos.x < block[i].pos.x)
				{//左
					//ブロックと触れている時はブロックに沈み込まないように座標を固定する
					cat->pos.x = BlockLeft - CAT_SIZE_W / 2;
					//サボテンに触れたら
					if (block[i].Patern >= 15.0f && block[i].Patern <= 16.9f)
					{
						//ゲームオーバー
						SetScene(SCENE_GAMEOVER);
					}
					//壁にぶつかったら反転。左へ
					//ChangeMoveFlag(cat);

					//if (temp > 0)
					//{
					//	temp -= 1;
					//}

				}
			}
			//else
			//{
			//	if (temp > 0)
			//	{
			//		temp -= 1;
			//	}
			//}
		}
		//==============================================================================================================================
		//			//MOVEブロックと猫の当たり判定//////////////////////////////////////////////////////////////////////////////////////
		//==============================================================================================================================
		for (int i = 0; i < MOVE_BLOCK_MAX; i++)
		{

			//もし構造体を使ってなかったらスキップ
			if (m_block[i].use != true)
			{
				//if (m_temp > 0)
				//{
				//	m_temp -= 1;
				//}
				continue;
			}
			//猫から遠い所は飛ばす
			else if (m_block[i].pos.x <(cat->pos.x - 90) || m_block[i].pos.x >(cat->pos.x + 90))
			{
				continue;
			}

			float BlockTopM = m_block[i].pos.y - SIZE / 2;
			float BlockBottomM = m_block[i].pos.y + SIZE / 2;
			float BlockLeftM = m_block[i].pos.x - SIZE / 2;
			float BlockRightM = m_block[i].pos.x + SIZE / 2;

			//当たり判定を行う
			bool hit = CollisionBB(
				cat->pos, m_block[i].pos,
				D3DXVECTOR2(CAT_SIZE_W, CAT_SIZE_H),
				D3DXVECTOR2(SIZE, SIZE)
			);
			//ブロックに触れていて
			if (hit == true)
			{
				//猫が床ブロックより上(重力GRAVの影響も排除する)
				if (CatBottom - GRAV <= BlockTopM && cat->pos.y < m_block[i].pos.y)
				{
					//ブロックと触れている時はブロックに沈み込まないように座標を固定する
					cat->pos.y = BlockTopM - CAT_SIZE_H / 2;
					cat->onmove = 0.0f;
					//m_temp = MOVE_BLOCK_MAX;

					//	バネブロックか砂嵐で中心あたりに乗った時跳ねる処理
					if (m_block[i].Patern >= 5.0f && m_block[i].Patern <= 7.9f)
					{
						if (cat->move_flag == false)
						{
							cat->patern = 8.0f;
						}
						else
						{
							cat->patern = 11.0f;
						}
						//曲がって
						m_block[i].Patern += 0.1f / 2;
						if (m_block[i].pos.x - 5.0f < cat->pos.x && m_block[i].pos.x + 5.0f > cat->pos.x)
						{
							//とりあえず3段	
							CatJump(3.0f);
							//飛んだ瞬間に戻る
							if (m_block[i].Patern >= 5.0f && m_block[i].Patern <= 7.9f)
							{
								m_block[i].Patern = 5.0f;
							}
						}
						else if (m_block[i].Patern >= 7.8f && m_block[i].Patern <= 7.9f)
						{
							//とりあえず3段	
							CatJump(3.0f);
							//飛んだ瞬間に戻る
							m_block[i].Patern = 5.0f;
						}
					}

					//	爪とぎブロック
					if (m_block[i].Patern >= 8.0f && m_block[i].Patern <= 8.9f)
					{
						if (m_block[i].pos.x - 1.0f < cat->pos.x && m_block[i].pos.x + 1.0f > cat->pos.x)
						{
							cat->tumetogi_flag = true;
						}

					}
				}
				//猫がブロックより右
				else if (CatLeft <= BlockRightM && cat->pos.x > BlockRightM)
				{
					//ブロックと触れている時はブロックに沈み込まないように座標を固定する
					cat->pos.x = BlockRightM + CAT_SIZE_W / 2 + cat->dir.x + 1;

					//if (m_temp > 0)
					//{
					//	m_temp -= 1;
					//}
				}
				//猫がブロックより左 
				else if (CatRight >= BlockLeftM && CatRight < m_block[i].pos.x)
				{//左
					//ブロックと触れている時はブロックに沈み込まないように座標を固定する
					cat->pos.x = BlockLeftM - CAT_SIZE_W / 2 - cat->dir.x - 1;

					//ブロックとぶつかったとき飛べる高さか調べる関数
					//引数:moveblockのポインタ,猫ポインタ,ぶつかったブロックの添え字
					//下で作成
					//CatJump(SearchJumpHeight(m_block, cat, i));
					//if (m_temp > 0)
					//{
					//	m_temp -= 1;
					//}
				}
			}
			else
			{
				//if (m_temp > 0)
				//{
				//	m_temp -= 1;
				//}
			}
		}
		//==============================================================================================================================
		//			//ギミックウォールと猫の当たり判定/////////////////////////////////////////////////////////////////////////////////
		//==============================================================================================================================
		for (int i = 0; i < WALL_MAX; i++)
		{

			//もし構造体を使ってなかったらスキップ
			if (gimmickwall[i].use != true)
			{
				//if (g_temp > 0)
				//{
				//	g_temp -= 1;
				//}
				continue;
			}
			//猫から遠い所は飛ばす
			else if (gimmickwall[i].pos.x <(cat->pos.x - 90) || gimmickwall[i].pos.x >(cat->pos.x + 90))
			{
				continue;
			}

			float GimmickWallTop = gimmickwall[i].pos.y - SIZE / 2;
			float GimmickWallBottom = gimmickwall[i].pos.y + SIZE / 2;
			float GimmickWallLeft = gimmickwall[i].pos.x - SIZE / 2;
			float GimmickWallRight = gimmickwall[i].pos.x + SIZE / 2;

			//当たり判定を行う
			bool hit = CollisionBB(
				cat->pos, gimmickwall[i].pos,
				D3DXVECTOR2(CAT_SIZE_W, CAT_SIZE_H),
				D3DXVECTOR2(SIZE, SIZE)
			);
			//ブロックに触れていて
			if (hit == true)
			{
				//ブロックより上(重力GRAVの影響も排除する)
				if (CatBottom - GRAV <= GimmickWallTop && cat->pos.y < gimmickwall[i].pos.y)
				{
					//ブロックと触れている時はブロックに沈み込まないように座標を固定する
					cat->pos.y = GimmickWallTop - CAT_SIZE_H / 2;
					cat->onmove = 0.0f;
					if (gimmickwall[i].pos.x - 25.0f < cat->pos.x && gimmickwall[i].pos.x + 25.0f > cat->pos.x)
					{
						//g_temp = WALL_MAX;
					}

				}
				//ブロックより下
				else if (CatTop <= GimmickWallBottom &&
					cat->pos.y - (CAT_SIZE_H / 2 - GRAV) > gimmickwall[i].pos.y + (SIZE / 2 - GRAV))
				{
					//ブロックにプレイヤーの上面で触れている時はジャンプ力を0にする
					cat->jump_y = 0;

					//if (g_temp > 0)
					//{
					//	g_temp -= 1;
					//}
				}
				//猫がブロックより右
				else if (CatLeft <= GimmickWallRight && cat->pos.x > GimmickWallRight)
				{
					//ブロックと触れている時はブロックに沈み込まないように座標を固定する
					cat->pos.x = GimmickWallRight + CAT_SIZE_W / 2 + cat->dir.x + 1;

					//壁にぶつかったら反転。右へ
					//ChangeMoveFlag(cat);

					//if (g_temp > 0)
					//{
					//	g_temp -= 1;
					//}
				}
				//猫がブロックより左 
				else if (CatRight >= GimmickWallLeft && CatRight < gimmickwall[i].pos.x)
				{//左
					//ブロックと触れている時はブロックに沈み込まないように座標を固定する
					cat->pos.x = GimmickWallLeft - CAT_SIZE_W / 2 - cat->dir.x - 1;

					//壁にぶつかったら反転。左へ
					//ChangeMoveFlag(cat);

					//if (g_temp > 0)
					//{
					//	g_temp -= 1;
					//}
				}
			}
			//else
			//{
			//	if (g_temp > 0)
			//	{
			//		g_temp -= 1;
			//	}
			//}
		}
		//全てのブロックを見た後にジャンプフラグを設定する
		/*if (g_temp > 0 || m_temp > 0 || temp > 2)
		{
			cat->jump_flag = true;
			cat->nowjump_flag = 0;
		}
		else
		{
			cat->jump_flag = false;
		}*/


		UpdateJumpFlag();
	}
}