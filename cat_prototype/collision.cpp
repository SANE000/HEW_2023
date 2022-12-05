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
#include "Scene.h"

#include "cat_collision.h"
#include "dogCollision.h"
#include "jumpsensor_collision.h"
#include "block_collision.h"

//==========================================
//グローバル変数
//==========================================

//猫のジャンプフラグ用
int temp = 0;
int m_temp = 0;
int g_temp = 0;
CAT *cat = GetCat();
PLAYER* player = GetPlayer();
BLOCK *block = GetBlock();
MOVE_BLOCK *m_block = GetMoveBlock();
G_WALL* gimmickwall = GetGimmickWall();


//ブロックとネコがぶつかった際、
//そのブロックの１個上、２個上のブロックが存在するかどうかをいれる変数
bool blockexist1;

bool enablejump;

float catjump_height;

int blocknum;

//==============================================================================================================================
//		//プロトタイプ宣言                //////////////////////////////////////////////////////////////////////////////////////
//==============================================================================================================================


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
	UpdateCatCollision();
	UpdateDogCollision();
	UpdateJumpSensorCollision();
	UpdateBlockCollision();

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

//ギミックブロックとぶつかったとき飛べる高さか調べる関数 床ブロックとぶつかったとき
//引数:g_wallのポインタ,猫ポインタ,ぶつかったブロックの添え字
float SearchJumpHeightG(G_WALL* g, CAT* c, int i)
{
	//ジャンプフラグがtrueだったら
					//床についていたら
	if (GetJumpFlag() == true)
	{

		//全ブロックを探知
		//ぶつかったブロックと同じx座標で一個上の高さのブロックを探す
		//それがあったら二個上の高さのブロックを探す
		//全部あれば三個分ジャンプ　ジャンプの高さを決める
		for (int a = 0; a < WALL_MAX; a++)
		{
			//全部のブロックが見つかったら終了
			if (blockexist1 == true)
			{
				break;
			}

			//x座標が同じなら
			if (g[a].pos.x == g[i].pos.x)
			{
				//y軸が一個上なら
				if (g[a].pos.y <= (g[i].pos.y - SIZE / 2) &&
					g[a].pos.y >= (g[i].pos.y - (SIZE + SIZE / 2)))
				{
					blockexist1 = true;
				}
			}

		}

		for (int a = 0; a < WALL_MAX; a++)
		{
			//全部のブロックが見つかったら終了
			if (blockexist1 == true)
			{
				break;
			}

			//x座標が同じなら
			if (g[a].pos.x == g[i].pos.x)
			{
				//y軸が一個上なら
				if (g[a].pos.y <= (g[i].pos.y - SIZE / 2) &&
					g[a].pos.y >= (g[i].pos.y - (SIZE + SIZE / 2)))
				{
					blockexist1 = true;
				}
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
