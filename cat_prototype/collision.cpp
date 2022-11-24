//当たり判定の処理
#include "main.h"
#include "collision.h"
#include "player.h"
#include "cat.h"
#include "block.h"
#include "blockpreview.h"
#include "Scene.h"
#include "sound.h"
#include "gimmick_wall.h"
//==========================================
//グローバル変数
//==========================================

//猫のジャンプフラグ用
int temp = BLOCK_MAX;

CAT *cat = GetCat();
PLAYER* player = GetPlayer();
BLOCK *block = GetBlock();
MOVE_BLOCK *m_block = GetMoveBlock();
BLOCK* gimmickwall = GetGimmickWall();


//ブロックとネコがぶつかった際、
//そのブロックの１個上、２個上のブロックが存在するかどうかをいれる変数
bool blockexist1;

bool enablejump;

float catjump_height;

int blocknum;

//==============================================================================================================================
//		//プロトタイプ宣言                //////////////////////////////////////////////////////////////////////////////////////
//==============================================================================================================================

//ブロック同士の当たり判定を分けました。
void BlockCollision();

//初期化
HRESULT InitCollsion()
{
	blockexist1 = false;

	enablejump = false;

	catjump_height = 0;

	return S_OK;
}

//更新処理　当たり判定を一気に行う
void UpdateCollision()
{
	float CatTop = cat->pos.y - SIZE / 2;
	float CatBottom = cat->pos.y + SIZE / 2;
	float CatLeft = cat->pos.x - SIZE / 2;
	float CatRight = cat->pos.x + SIZE / 2;

	if (cat->use == true)
	{
		temp = BLOCK_MAX;
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
				continue;
			}
			//当たり判定を行う
			bool hit = CollisionBB(
				cat->pos, block[i].pos,
				D3DXVECTOR2(SIZE, SIZE),
				D3DXVECTOR2(SIZE, SIZE)
			);
			//ブロックに触れていて
			if (hit == true)
			{

				//床ブロックより上(重力GRAVの影響も排除する)
				if (CatBottom - GRAV <= BlockTop && cat->pos.y < block[i].pos.y)
				{
					//ブロックと触れている時はブロックに沈み込まないように座標を固定する
					cat->pos.y = BlockTop - GRAV - SIZE / 2;
					temp = BLOCK_MAX;

					//ブロックと触れている時はブロックに沈み込まないように座標を固定する
					cat->pos.y = BlockTop - GRAV - SIZE / 2;
					temp = BLOCK_MAX;

					if (block[i].Patern == 2.0f)
					{
						ChangeMoveFlag(cat);
					}

					if (block[i].button == true)
					{
						//触れた瞬間falseにならないように中心あたりでfalseにする
						if (block[i].pos.x - 10.0f < cat->pos.x && block[i].pos.x + 10.0f > cat->pos.x)
						{
							block[i].button = false;
						}

					}
				}
				//床ブロックより下
				else if (CatTop <= BlockBottom &&
					cat->pos.y - (SIZE / 2 - GRAV) > block[i].pos.y + (SIZE / 2 - GRAV))
				{
						//ブロックにプレイヤーの上面で触れている時はジャンプ力を0にする
						cat->jump_y = 0;

					
				}
				//床ブロックより右
				else if (CatLeft <= BlockRight && cat->pos.x > BlockRight)
				{
					//ブロックと触れている時はブロックに沈み込まないように座標を固定する
					cat->pos.x = BlockRight + SIZE / 2;
					//壁にぶつかったら反転。右へ
					ChangeMoveFlag(cat);
					
				}
				//床ブロックより左
				else if (CatRight >= BlockLeft && cat->pos.x < block[i].pos.x)
				{//左
					//ブロックと触れている時はブロックに沈み込まないように座標を固定する
					cat->pos.x = BlockLeft - SIZE / 2;
					//壁にぶつかったら反転。左へ
					ChangeMoveFlag(cat);
					
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
		//==============================================================================================================================
		//			//MOVEブロックと猫の当たり判定//////////////////////////////////////////////////////////////////////////////////////
		//==============================================================================================================================
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
				D3DXVECTOR2(SIZE, SIZE),
				D3DXVECTOR2(SIZE, SIZE)
			);
			//ブロックに触れていて
			if (hit == true)
			{
				//猫が床ブロックより上(重力GRAVの影響も排除する)
				if (CatBottom - GRAV <= BlockTopM && cat->pos.y < m_block[i].pos.y)
				{
					//ブロックと触れている時はブロックに沈み込まないように座標を固定する
					cat->pos.y = BlockTopM - GRAV - SIZE / 2;
					cat->jump_flag = true;
					cat->nowjump_flag = 0;
				}
				//猫がブロックより右
				else if (CatLeft <= BlockRightM && cat->pos.x > BlockRightM)
				{
					//ブロックと触れている時はブロックに沈み込まないように座標を固定する
					cat->pos.x = BlockRightM + SIZE / 2;
				}
				//猫がブロックより左 
				else if (CatRight >= BlockLeftM && CatRight < m_block[i].pos.x)
				{//左
					//ブロックと触れている時はブロックに沈み込まないように座標を固定する
					cat->pos.x = BlockLeftM - SIZE / 2;

					//ブロックとぶつかったとき飛べる高さか調べる関数
					//引数:moveblockのポインタ,猫ポインタ,ぶつかったブロックの添え字
					//下で作成
					//CatJump(SearchJumpHeight(m_block, cat, i));

				}
			}
		}

		//==============================================================================================================================
		//			//ギミックウォールと猫の当たり判定//////////////////////////////////////////////////////////////////////////////////////
		//==============================================================================================================================
		for (int i = 0; i < WALL_MAX; i++)
		{

			//もし構造体を使ってなかったらスキップ
			if (gimmickwall[i].use != true)
			{
				continue;
			}

			float GimmickWallTopM = gimmickwall[i].pos.y - SIZE / 2;
			float GimmickWallBottomM = gimmickwall[i].pos.y + SIZE / 2;
			float GimmickWallLeftM = gimmickwall[i].pos.x - SIZE / 2;
			float GimmickWallRightM = gimmickwall[i].pos.x + SIZE / 2;

			//当たり判定を行う
			bool hit = CollisionBB(
				cat->pos, gimmickwall[i].pos,
				D3DXVECTOR2(SIZE, SIZE),
				D3DXVECTOR2(SIZE, SIZE)
			);
			//ブロックに触れていて
			if (hit == true)
			{
				//猫がブロックより右
				if (CatLeft <= GimmickWallRightM && cat->pos.x > GimmickWallRightM)
				{
					//ブロックと触れている時はブロックに沈み込まないように座標を固定する
					cat->pos.x = GimmickWallRightM + SIZE / 2 + cat->dir.x + 1;

					//壁にぶつかったら反転。右へ
					ChangeMoveFlag(cat);
				}
				//猫がブロックより左 
				else if (CatRight >= GimmickWallLeftM && CatRight < gimmickwall[i].pos.x)
				{//左
					//ブロックと触れている時はブロックに沈み込まないように座標を固定する
					cat->pos.x = GimmickWallLeftM - SIZE / 2 - cat->dir.x -1;

					//壁にぶつかったら反転。左へ
					ChangeMoveFlag(cat);

				}
			}
		}

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
				D3DXVECTOR2(SIZE + SENSOR_SIZE*2, 1.0f),
				D3DXVECTOR2(SIZE, SIZE)
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
				D3DXVECTOR2(SIZE, SIZE)
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
		//ブロック同士の当たり判定
		BlockCollision();
	}
}

//==============================================================================================================================
//		//ジャンプ関連の関数達　　　　　　//////////////////////////////////////////////////////////////////////////////////////
//==============================================================================================================================

//ブロックとぶつかったとき飛べる高さか調べる関数　動くブロックとぶつかったとき
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

		for (int a = 0; a < MOVE_BLOCK_MAX; a++)
		{
			//全部のブロックが見つかったら終了
			if (blockexist1 == true)
			{
				break;
			}

			//x座標が同じなら
			if (mb[a].pos.x == mb[i].pos.x)
			{
				//y軸が一個上なら
				if (mb[a].pos.y <= (mb[i].pos.y - SIZE / 2) &&
					mb[a].pos.y >= (mb[i].pos.y - (SIZE + SIZE / 2)))
				{
					blockexist1 = true;
				}
				////2個上なら
				//else if (mb[b].pos.y <= (mb[i].pos.y - (SIZE + SIZE / 2)) &&
				//	mb[b].pos.y >= (mb[i].pos.y - (SIZE * 2 + SIZE / 2)))
				//{
				//	blockexist2 = true;
				//}
				////3個上なら
				//else if (mb[b].pos.y <= (mb[i].pos.y - (SIZE * 2 + SIZE / 2)) &&
				//	mb[b].pos.y >= (mb[i].pos.y - (SIZE * 3 + SIZE / 2)))
				//{
				//	blockexist3 = true;
				//}

			}

		}

		//何段飛べるという変数を渡す
		//blockexisitをfalseにする

		//どっちも見つからなかった時
		if (blockexist1 == false)
		{
			catjump_height = 1;
			enablejump = true;
		}
		//一個上だけ存在する
		else if (blockexist1 == true)
		{
			catjump_height = 2;
			enablejump = false;
		}
		////一個上と二個上存在する
		//else if (blockexist1 == true && blockexist2 == true )
		//{
		//	catjump_height = 3;
		//	enablejump = true;
		//}
		////全部存在する
		//else if (blockexist1 == true && blockexist2 == true && blockexist3 == true)
		//{
		//	catjump_height = 4;
		//	enablejump = false;
	}

	//二個上のブロックだけ存在した際どうするかは今後考える
	//else if (blockexist1 == false && blockexist2 == true)

	blockexist1 = false;
	return catjump_height;
}

//ブロックとぶつかったとき飛べる高さか調べる関数 床ブロックとぶつかったとき
//引数:blockのポインタ,猫ポインタ,ぶつかったブロックの添え字
float SearchJumpHeightB(BLOCK* b, CAT* c, int i)
{
	//ジャンプフラグがtrueだったら
					//床についていたら
	if (GetJumpFlag() == true)
	{

		//全ブロックを探知
		//ぶつかったブロックと同じx座標で一個上の高さのブロックを探す
		//それがあったら二個上の高さのブロックを探す
		//全部あれば三個分ジャンプ　ジャンプの高さを決める
		for (int a = 0; a < BLOCK_MAX; a++)
		{
			//全部のブロックが見つかったら終了
			if (blockexist1 == true)
			{
				break;
			}

			//x座標が同じなら
			if (b[a].pos.x == b[i].pos.x)
			{
				//y軸が一個上なら
				if (b[a].pos.y <= (b[i].pos.y - SIZE / 2) &&
					b[a].pos.y >= (b[i].pos.y - (SIZE + SIZE / 2)))
				{
					blockexist1 = true;
				}
				////2個上なら
				//else if (mb[b].pos.y <= (mb[i].pos.y - (SIZE + SIZE / 2)) &&
				//	mb[b].pos.y >= (mb[i].pos.y - (SIZE * 2 + SIZE / 2)))
				//{
				//	blockexist2 = true;
				//}
				////3個上なら
				//else if (mb[b].pos.y <= (mb[i].pos.y - (SIZE * 2 + SIZE / 2)) &&
				//	mb[b].pos.y >= (mb[i].pos.y - (SIZE * 3 + SIZE / 2)))
				//{
				//	blockexist3 = true;
				//}

			}

		}

		for (int a = 0; a < BLOCK_MAX; a++)
		{
			//全部のブロックが見つかったら終了
			if (blockexist1 == true)
			{
				break;
			}

			//x座標が同じなら
			if (b[a].pos.x == b[i].pos.x)
			{
				//y軸が一個上なら
				if (b[a].pos.y <= (b[i].pos.y - SIZE / 2) &&
					b[a].pos.y >= (b[i].pos.y - (SIZE + SIZE / 2)))
				{
					blockexist1 = true;
				}
				////2個上なら
				//else if (mb[b].pos.y <= (mb[i].pos.y - (SIZE + SIZE / 2)) &&
				//	mb[b].pos.y >= (mb[i].pos.y - (SIZE * 2 + SIZE / 2)))
				//{
				//	blockexist2 = true;
				//}
				////3個上なら
				//else if (mb[b].pos.y <= (mb[i].pos.y - (SIZE * 2 + SIZE / 2)) &&
				//	mb[b].pos.y >= (mb[i].pos.y - (SIZE * 3 + SIZE / 2)))
				//{
				//	blockexist3 = true;
				//}

			}

		}

		//何段飛べるという変数を渡す
		//blockexisitをfalseにする

		//どっちも見つからなかった時
		if (blockexist1 == false)
		{
			catjump_height = 1;
			enablejump = true;
		}
		//一個上だけ存在する
		else if (blockexist1 == true)
		{
			catjump_height = 2;
			enablejump = false;
		}
	}

	//二個上のブロックだけ存在した際どうするかは今後考える
	//else if (blockexist1 == false && blockexist2 == true)

	blockexist1 = false;
	return catjump_height;
}


int GetBlockNum()
{
	return blocknum;
}

//==============================================================================================================================
//		//ブロック同士の当たり判定//////////////////////////////////////////////////////////////////////////////////////////////
//==============================================================================================================================
void BlockCollision()
{
	//動くブロックと動かないブロックの当たり判定
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
							m_block[i].pos.y = BlockTop - DRAW_SIZE / 2;
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
						if (m_block[i].pos.y < m_block[n].pos.y)
						{
							//BlockBottomI - GRAV  <= BlockTopN &&

							//下にあるブロックが地面に触れているブロックなのか確かめてそうなら当たり判定で止まる処理の追加の必要があるかも
							if (m_block[i].pos.x - SIZE / 2 <= m_block[n].pos.x && m_block[i].pos.x + SIZE / 2 >= m_block[n].pos.x)
							{
								if (m_block[i].Speed.y == 0 && m_block[n].Speed.y != 0)
								{
									//ブロックと触れている時はブロックに沈み込まないように座標を固定する
									m_block[n].Speed.y = 0;
									m_block[n].pos.y = BlockBottomI + DRAW_SIZE / 2;
								}
								else if (m_block[n].Speed.y == 0 && m_block[i].Speed.y != 0)
								{
									m_block[i].Speed.y = 0;
									m_block[i].pos.y = BlockTopN - 1 - DRAW_SIZE / 2;
								}
							}
						}
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
						//Nブロックより左 
						else if (BlockRightI >= BlockLeftN && BlockRightI < m_block[n].pos.x)
						{//左

							if (m_block[i].pos.y - SIZE / 2 <= m_block[n].pos.y && m_block[i].pos.y + SIZE / 2 >= m_block[n].pos.y)
							{
								if (m_block[i].Speed.y == 0 && m_block[n].Speed.y != 0)
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

//==============================================================================================================================
//		//HIT判定関数　　　　　　　　　　　/////////////////////////////////////////////////////////////////////////////////////
//==============================================================================================================================
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
	return true;//↑4つを乗り越えたら衝突しているってことだからtrue
}
