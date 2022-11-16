//当たり判定の処理
#include "main.h"
#include "collision.h"
#include "player.h"
#include "cat.h"
#include "block.h"
#include "Scene.h"
#include "sound.h"


//マクロ
//プロトタイプ宣言
//この中でしか使わない変数
//BBとは当たり判定の最低限の□
//四角形の中心座標２つとサイズ２つ true衝突
int temp = BLOCK_MAX;
 

//==========================================
//グローバル変数
//==========================================

//ブロックとネコがぶつかった際、
//そのブロックの１個上、２個上のブロックが存在するかどうかをいれる変数
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


//当たり判定を処理　判定を一気に行う
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
			//もし構造体を使ってなかったらスキップ
			if (block[i].use != true)
			{
				continue;
			}
			//当たり判定を行う
			bool hit = CollisionBB(
				cat->pos, block[i].pos,
				D3DXVECTOR2(cat->w, cat->h),
				D3DXVECTOR2(BASE_SIZE, SIZE)
			);
			//ブロックに触れていて
			if (hit == true)
			{
				//床ブロックより上(重力GRAVの影響も排除する)
				if (CatBottom - GRAV <= BlockTop && cat->pos.y < block[i].pos.y)
				{
					//ブロックと触れている時はブロックに沈み込まないように座標を固定する
					cat->pos.y = BlockTop - cat->h / 2;
					temp = BLOCK_MAX;
				}
				//床ブロックより下
				else if (CatTop <= BlockBottom &&
					cat->pos.y - (cat->h / 2 - GRAV) > block[i].pos.y + (SIZE / 2 - GRAV))
				{
					//ブロックにプレイヤーの上面で触れている時はジャンプ力を0にする
					cat->jump_y = 0;
				}
				//床ブロックより右
				else if (CatLeft <= BlockRight && cat->pos.x > BlockRight)
				{
					//ブロックと触れている時はブロックに沈み込まないように座標を固定する
					cat->pos.x = BlockRight + cat->w / 2;
					//壁にぶつかったら反転。右へ
					cat->move_flag = false;
				}
				//床ブロックより左
				else if (CatRight >= BlockLeft && cat->pos.x < block[i].pos.x)
				{//左
					//ブロックと触れている時はブロックに沈み込まないように座標を固定する
					cat->pos.x = BlockLeft - cat->w / 2;
					//壁にぶつかったら反転。左へ
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
		//動くブロックと猫の当たり判定/////////////////////////////////////////////////////////////////////
		for (int i = 0; i < MOVE_BLOCK_MAX; i++)
		{

			//もし構造体を使ってなかったらスキップ
			if (m_block[i].use != true)
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
				D3DXVECTOR2(cat->w, cat->h),
				D3DXVECTOR2(SIZE, SIZE)
			);
			//ブロックに触れていて
			if (hit == true)
			{
				//猫が床ブロックより上(重力GRAVの影響も排除する)
				if (CatBottom - GRAV <= BlockTopM && cat->pos.y < m_block[i].pos.y)
				{
					//ブロックと触れている時はブロックに沈み込まないように座標を固定する
					cat->pos.y = BlockTopM - 1 - cat->h / 2;
					cat->jump_flag = true;
					cat->nowjump_flag = 0;
				}
				//猫がブロックより右
				else if (CatLeft <= BlockRightM && cat->pos.x > BlockRightM)
				{
					//ブロックと触れている時はブロックに沈み込まないように座標を固定する
					cat->pos.x = BlockRightM + cat->w / 2;



				}
				//猫がブロックより左 
				else if (CatRight >= BlockLeftM && CatRight < m_block[i].pos.x)
				{//左
					//ブロックと触れている時はブロックに沈み込まないように座標を固定する
					cat->pos.x = BlockLeftM - cat->w / 2;

					//ブロックとぶつかったとき飛べる高さか調べる関数
					//引数:moveblockのポインタ,猫ポインタ,ぶつかったブロックの添え字
					//下で作成
					//CatJump(SearchJumpHeight(m_block, cat, i));

				}
			}
			else
			{
			}
		}

		//動くブロックと猫のジャンプセンサーの当たり判定/////////////////////////////////////////////////////////////////////
		for (int i = 0; i < MOVE_BLOCK_MAX; i++)
		{

			//もし構造体を使ってなかったらスキップ
			if (m_block[i].use != true)
			{
				continue;
			}

			float JumpSensorTopM = m_block[i].pos.y - SIZE / 2;
			float JumpSensorBottomM = m_block[i].pos.y + SIZE / 2;
			float JumpSensorLeftM = m_block[i].pos.x - SIZE / 2 - SENSOR_SIZE ;
			float JumpSensorRightM = m_block[i].pos.x + SIZE / 2 + SENSOR_SIZE;


			//当たり判定を行う
			bool hit = CollisionBB(
				cat->pos, m_block[i].pos,
				D3DXVECTOR2(cat->w + SENSOR_SIZE * 2, cat->h),
				D3DXVECTOR2(SIZE, SIZE)
			);
			//ブロックに触れていて
			if (hit == true)
			{
				//猫が床ブロックより右
				if (CatLeft <= JumpSensorRightM && cat->pos.x > JumpSensorRightM)
				{
					if (cat->move_flag == true)
					{
						//ブロックとぶつかったとき飛べる高さか調べる関数
						//引数:moveblockのポインタ,猫ポインタ,ぶつかったブロックの添え字
						//下で作成

						//ジャンプする段数が0以上4未満かどうか
						//0は何かしらのエラー　4は飛ばずに引き返す
						if (SearchJumpHeight(m_block, cat, i) > 0 &&
							SearchJumpHeight(m_block, cat, i) < 4)
						{
							//地面についているか
							if (cat->jump_flag = true)
							{
								CatJump(SearchJumpHeight(m_block, cat, i));
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

						//ジャンプする段数が0以上4未満かどうか
						//0は何かしらのエラー　4は飛ばずに引き返す
						if (SearchJumpHeight(m_block, cat, i) > 0 &&
							SearchJumpHeight(m_block, cat, i) < 4)
						{
							//地面についているか
							if (cat->jump_flag = true)
							{
								CatJump(SearchJumpHeight(m_block, cat, i));
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

		//床ブロックと猫のジャンプセンサーの当たり判定/////////////////////////////////////////////////////////////////////
		for (int i = 0; i < BLOCK_MAX; i++)
		{

			//もし構造体を使ってなかったらスキップ
			if (block[i].use != true)
			{
				continue;
			}

			float JumpSensorTopM = block[i].pos.y - SIZE / 2;
			float JumpSensorBottomM = block[i].pos.y + SIZE / 2;
			float JumpSensorLeftM = block[i].pos.x - BASE_SIZE / 2 - SENSOR_SIZE;
			float JumpSensorRightM = block[i].pos.x + BASE_SIZE / 2 + SENSOR_SIZE;


			//当たり判定を行う
			bool hit = CollisionBB(
				cat->pos, m_block[i].pos,
				D3DXVECTOR2(cat->w + SENSOR_SIZE * 2, cat->h),
				D3DXVECTOR2(BASE_SIZE, SIZE)
			);
			//ブロックに触れていて
			if (hit == true)
			{
				//猫が床ブロックより右
				if (CatLeft <= JumpSensorRightM && cat->pos.x > JumpSensorRightM)
				{
					if (cat->move_flag == true)
					{
						//ブロックとぶつかったとき飛べる高さか調べる関数
						//引数:moveblockのポインタ,猫ポインタ,ぶつかったブロックの添え字
						//下で作成

						//ジャンプする段数が0以上4未満かどうか
						//0は何かしらのエラー　4は飛ばずに引き返す
						if (SearchJumpHeight(m_block, cat, i) > 0 &&
							SearchJumpHeight(m_block, cat, i) < 4)
						{
							//地面についているか
							if (cat->jump_flag = true)
							{
								CatJump(SearchJumpHeight(m_block, cat, i));
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

						//ジャンプする段数が0以上4未満かどうか
						//0は何かしらのエラー　4は飛ばずに引き返す
						if (SearchJumpHeight(m_block, cat, i) > 0 &&
							SearchJumpHeight(m_block, cat, i) < 4)
						{
							//地面についているか
							if (cat->jump_flag = true)
							{
								CatJump(SearchJumpHeight(m_block, cat, i));
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
		
		//動くブロックと動かないブロックの当たり判定
		for (int i = 0; i < MOVE_BLOCK_MAX; i++)
		{
			//動くブロックは存在する？
			if (m_block[i].use == true)
			{
				float BlockTopI2 = m_block[i].pos.y - SIZE / 2;
				float BlockBottomI2 = m_block[i].pos.y + SIZE / 2;
				//もう一つの構造体を全て調べる
				for (int n = 0; n < BLOCK_MAX; n++)
				{
					//動かないブロックは実在する？
					if (block[n].use == true)
					{
						float BlockTop2 = block[n].pos.y - SIZE / 2;
						float BlockBottom2 = block[n].pos.y + SIZE / 2;
						//当たり判定
						bool hit = CollisionBB(
							m_block[i].pos, block[n].pos,
							D3DXVECTOR2(SIZE, SIZE),
							D3DXVECTOR2(BASE_SIZE, SIZE)
						);
						if (hit == true)
						{
							//Nブロックより上(重力GRAVの影響も排除する)
							if (BlockBottomI2 - GRAV <= BlockTop2 && m_block[i].pos.y < block[n].pos.y)
							{
								//ブロックと触れている時はブロックに沈み込まないように座標を固定する
								m_block[i].Speed.y = 0;
								m_block[i].pos.y = BlockTop2 - 1 - SIZE / 2;
							}
						}
					}
				}
			}
		}
		//動くブロック同士の当たり判定/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		for (int i = 0; i < MOVE_BLOCK_MAX; i++)
		{	
			//ブロックは存在する？
			if (m_block[i].use == true)
			{
				//存在が分かってから入れる
				float BlockTopI = m_block[i].pos.y - SIZE / 2;
				float BlockBottomI = m_block[i].pos.y + SIZE / 2;
				float BlockLeftI = m_block[i].pos.x - SIZE / 2;
				float BlockRightI = m_block[i].pos.x + SIZE / 2;
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
						float BlockLeftN = m_block[n].pos.x - SIZE / 2;
						float BlockRightN = m_block[n].pos.x + SIZE / 2;
						//当たり判定
						bool hit = CollisionBB(
							m_block[i].pos, m_block[n].pos,
							D3DXVECTOR2(SIZE, SIZE),
							D3DXVECTOR2(SIZE, SIZE)
						);
						if (hit == true)
						{
							//Nブロックより上(重力GRAVの影響も排除する)
							if ( m_block[i].pos.y < m_block[n].pos.y)
							{
								//BlockBottomI - GRAV  <= BlockTopN &&

								//下にあるブロックが地面に触れているブロックなのか確かめてそうなら当たり判定で止まる処理の追加の必要があるかも
								if (m_block[i].pos.x - SIZE / 2 <= m_block[n].pos.x && m_block[i].pos.x + SIZE / 2 >= m_block[n].pos.x)
								{
									if (m_block[i].Speed.y == 0 && m_block[n].Speed.y != 0)
									{
										//ブロックと触れている時はブロックに沈み込まないように座標を固定する
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
							////Nブロックより下
							//
							//if (BlockTopI <= BlockBottomN &&
							//	m_block[i].pos.y - (block[i].h / 2 - GRAV) - 10 > block[n].pos.y + (block[n].h / 2 - GRAV))
							//{

							//	//下にあるブロックが地面に触れているブロックなのか確かめてそうなら当たり判定で止まる処理の追加の必要があるかも
							//	if (m_block[i].pos.x == m_block[n].pos.x)
							//	{
							//		if (m_block[i].Speed.y == 0 || m_block[n].Speed.y == 0)
							//		{
							//			//ブロックと触れている時はブロックに沈み込まないように座標を固定する
							//			m_block[i].Speed.y = 0;
							//			m_block[n].Speed.y = 0;
							//			m_block[i].pos.y = BlockTopN - SIZE / 2;
							//			//block[i].Hit = true;
							//			//temp = BLOCK_MAX;
							//		}

							//	}

							//}
							//Nブロックより右
							if (BlockLeftI <= BlockRightN && m_block[i].pos.x > BlockRightN)
							{
								//ブロックと触れている時はブロックに沈み込まないように座標を固定する
								if (m_block[i].pos.y - SIZE / 2 <= m_block[n].pos.y && m_block[i].pos.y + SIZE / 2 >= m_block[n].pos.y)
								{
									if (m_block[i].Speed.y == 0 && m_block[n].Speed.y != 0)
									{
										//ブロックと触れている時はブロックに沈み込まないように座標を固定する
										
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
							//Nブロックより左 
							else if (BlockRightI >= BlockLeftN && BlockRightI < m_block[n].pos.x)
							{//左

								if (m_block[i].pos.y - SIZE / 2 <= m_block[n].pos.y && m_block[i].pos.y + SIZE / 2 >= m_block[n].pos.y)
								{
									if (m_block[i].Speed.y == 0 && m_block[n].Speed.y != 0)
									{
										//ブロックと触れている時はブロックに沈み込まないように座標を固定する

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
							//Nブロックより下
							//else if (BlockTopI <= BlockBottomN &&
							//	m_block[i].pos.y - (SIZE / 2 - GRAV) > m_block[n].pos.y + (SIZE / 2 - GRAV))
							//{
							//	m_block[i].pos.y = BlockBottomN + SIZE / 2;
							//}
						}
						//ジャンプ関係はあとで
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
	//四角形1の左上の最小xと最小y
	min1.x = pos1.x - size1.x / 2;
	min1.y = pos1.y - size1.y / 2;
	//↑このままあと3つ作る　絵を書いたりするとよろし
	//四角形1の右下の最大xと最大y
	max1.x = pos1.x + size1.x / 2;
	max1.y = pos1.y + size1.y / 2;
	//四角形2の左上の最小xと最小y
	min2.x = pos2.x - size2.x / 2;
	min2.y = pos2.y - size2.y / 2;
	//四角形1の右下の最大xと最大y
	max2.x = pos2.x + size2.x / 2;
	max2.y = pos2.y + size2.y / 2;
	//衝突判定
	if (max1.x < min2.x)
	{
		return false;//条件1　衝突してない
	}
	if (max1.y < min2.y)
	{
		return false;//条件2　衝突してない
	}
	if (max2.x < min1.x)
	{
		return false;//条件3　衝突してない
	}
	if (max2.y < min1.y)
	{
		return false;//条件4　衝突してない
	}
	//あと3つ条件を作る
	return true;//↑4つを乗り越えたら衝突しているってことだからtrue
}

//ブロックとぶつかったとき飛べる高さか調べる関数
//引数:moveblockのポインタ,猫ポインタ,ぶつかったブロックの添え字
float SearchJumpHeight(MOVE_BLOCK* mb, CAT* c, int i)
{
	//ジャンプフラグがtrueだったら
					//床についていたら
	if (GetJumpFlag() == true)
	{

		//全ブロックを探知
		//ぶつかったブロックと同じx座標で一個上の高さのブロックを探す
		//それがあったら二個上の高さのブロックを探す
		//全部あれば三個分ジャンプ　ジャンプの高さを決める
		for (int b = 0; b < MOVE_BLOCK_MAX; b++)
		{
			//x座標が同じなら
			if (mb[b].pos.x == mb[i].pos.x)
			{
				//y軸が一個上なら
				if (mb[b].pos.y <= (mb[i].pos.y - SIZE / 2) &&
					mb[b].pos.y >= (mb[i].pos.y - (SIZE + SIZE / 2)))
				{
					blockexist1 = true;
				}
				//2個上なら
				else if (mb[b].pos.y <= (mb[i].pos.y - (SIZE + SIZE / 2)) &&
					mb[b].pos.y >= (mb[i].pos.y - (SIZE * 2 + SIZE / 2)))
				{
					blockexist2 = true;
				}
				//3個上なら
				else if (mb[b].pos.y <= (mb[i].pos.y - (SIZE * 2 + SIZE / 2)) &&
					mb[b].pos.y >= (mb[i].pos.y - (SIZE * 3 + SIZE / 2)))
				{
					blockexist3 = true;
				}

			}

			//全部のブロックが見つかったら終了
			if (blockexist1 == true && blockexist2 == true && blockexist3 == true)
			{
				break;
			}
		}

		//何段飛べるという変数を渡す
		//blockexisitをfalseにする

		//どっちも見つからなかった時
		if (blockexist1 == false && blockexist2 == false)
		{
			catjump_height = 1;
			enablejump = true;
		}
		//一個上だけ存在する
		else if (blockexist1 == true && blockexist2 == false)
		{
			catjump_height = 2;
			enablejump = true;
		}
		//一個上と二個上存在する
		else if (blockexist1 == true && blockexist2 == true && blockexist3 == false)
		{
			catjump_height = 3;
			enablejump = true;
		}
		//全部存在する
		else if (blockexist1 == true && blockexist2 == true && blockexist3 == true)
		{
			catjump_height = 4;
			enablejump = false;
		}

		//二個上のブロックだけ存在した際どうするかは今後考える
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