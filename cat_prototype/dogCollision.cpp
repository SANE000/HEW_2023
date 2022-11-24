#include "main.h"
#include "dogCollision.h"
#include "cat.h"
#include "Scene.h"
#include "shop.h"

//bool DogCollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2);

//int temp = BLOCK_MAX;

//---------------------------
//当たり判定を処理
//---------------------------
void UpdateDogCollision()
{
	int temp = BLOCK_MAX;

	DOG* dog = GetDog();
	CAT* cat = GetCat();
	BLOCK* block = GetBlock();
	MOVE_BLOCK* m_block = GetMoveBlock();

	float CatTop = cat->pos.y - SIZE / 2;
	float CatBottom = cat->pos.y + SIZE / 2;
	float CatLeft = cat->pos.x - SIZE / 2;
	float CatRight = cat->pos.x + SIZE / 2;

	// dog vs cat
	if (cat->use == true)
	{
		for (int i = 0; i < DOG_MAX; i++)
		{
			if (dog[i].use == true)
			{
				bool hit = DogCollisionBB(cat->pos, dog[i].pos, D3DXVECTOR2(SIZE, SIZE), D3DXVECTOR2(dog[i].w, dog[i].h));
				if (hit == true)
				{
					//ChangeMoveFlag(cat);
					SetScene(SCENE_SHOP);
					//cat->use = false;
					//cat->move_flag = false;
					//cat->jump_flag = false;
				}
			}
		}
	}


	// dog vs block
	for (int i = 0; i < DOG_MAX; i++)
	{
		float DogTop = dog[i].pos.y - SIZE / 2;
		float DogBottom = dog[i].pos.y + SIZE / 2;
		float DogLeft = dog[i].pos.x - SIZE / 2;
		float DogRight = dog[i].pos.x + SIZE / 2;

		if (dog[i].use == true)
		{
			for (int b = 0; b < BLOCK_MAX; b++)
			{
				float BlockTop = block[b].pos.y - SIZE / 2;
				float BlockBottom = block[b].pos.y + SIZE / 2;
				float BlockLeft = block[b].pos.x - SIZE / 2;
				float BlockRight = block[b].pos.x + SIZE / 2;
				//もし構造体を使ってなかったらスキップ
				if (block[b].use != true)
				{
					continue;
				}
				//
				bool hit = DogCollisionBB(dog[i].pos, block[b].pos, D3DXVECTOR2(dog[i].w, dog[i].h), D3DXVECTOR2(SIZE, SIZE));
				if (hit == true)
				{
					//床ブロックより上(重力GRAVの影響も排除する)
					if (DogBottom - GRAV <= BlockTop && dog[i].pos.y < block[b].pos.y)
					{
						//ブロックと触れている時はブロックに沈み込まないように座標を固定する
						dog[i].pos.y = BlockTop - GRAV - SIZE / 2;
						temp = BLOCK_MAX;

						if (block[b].button == true)
						{
							//触れた瞬間falseにならないように中心あたりでfalseにする
							if (block[b].pos.x - 10.0f < dog[i].pos.x && block[b].pos.x + 10.0f > dog[i].pos.x)
							{
								block[b].button = false;
							}

						}

					}
					//床ブロックより下
					else if (DogTop <= BlockBottom &&
						dog[i].pos.y - (SIZE / 2 - GRAV) > block[b].pos.y + (SIZE / 2 - GRAV))
					{
						dog[i].use = false;
					}
					//床ブロックより右
					else if (DogLeft <= BlockRight && dog[i].pos.x > BlockRight)
					{
						//ブロックと触れている時はブロックに沈み込まないように座標を固定する
						dog[i].pos.x = BlockRight + SIZE / 2;
						//壁にぶつかったら反転。右へ
						//ChangeMoveFlag(cat);
					}
					//床ブロックより左
					else if (DogRight >= BlockLeft && dog[i].pos.x < block[i].pos.x)
					{//左
						//ブロックと触れている時はブロックに沈み込まないように座標を固定する
						dog[i].pos.x = BlockLeft - SIZE / 2;
						//壁にぶつかったら反転。左へ
						//ChangeMoveFlag(cat);
					}
				}
			}
		}

		//dog vs move_block
		for (int i = 0; i < DOG_MAX; i++)
		{
			float DogTop = dog[i].pos.y - SIZE / 2;
			float DogBottom = dog[i].pos.y + SIZE / 2;
			float DogLeft = dog[i].pos.x - SIZE / 2;
			float DogRight = dog[i].pos.x + SIZE / 2;

			if (dog[i].use == true)
			{
				for (int b = 0; b < MOVE_BLOCK_MAX; b++)
				{
					float BlockTopM = m_block[b].pos.y - SIZE / 2;
					float BlockBottomM = m_block[b].pos.y + SIZE / 2;
					float BlockLeftM = m_block[b].pos.x - SIZE / 2;
					float BlockRightM = m_block[b].pos.x + SIZE / 2;

					if (m_block[b].use != true)
					{
						continue;
					}

					bool hit = DogCollisionBB(dog[i].pos, m_block[b].pos, D3DXVECTOR2(dog[i].w, dog[i].h), D3DXVECTOR2(SIZE, SIZE));
					if (hit == true)
					{
						//犬が床ブロックより上(重力GRAVの影響も排除する)
						if (DogBottom - GRAV <= BlockTopM && dog[i].pos.y < m_block[b].pos.y)
						{
							//ブロックと触れている時はブロックに沈み込まないように座標を固定する
							dog[i].pos.y = BlockTopM - GRAV - SIZE / 2;
						}
						//犬がブロックより右
						else if (DogLeft <= BlockRightM && dog[i].pos.x > BlockRightM)
						{
							//ブロックと触れている時はブロックに沈み込まないように座標を固定する
							dog[i].pos.x = BlockRightM + SIZE / 2;
						}
						//犬がブロックより左 
						else if (DogRight >= BlockLeftM && DogRight < m_block[b].pos.x)
						{//左
							//ブロックと触れている時はブロックに沈み込まないように座標を固定する
							dog[i].pos.x = BlockLeftM - SIZE / 2;
						}
					}

				}
			}
		}

		//close to dog
		if (cat->use == true)
		{
			for (int i = 0; i < DOG_MAX; i++)
			{
				if (dog[i].use == true)
				{
					//if (cat->pos.x > (dog[i].pos.x - cat->pos.x) - 30)
					//{
					//	dog[i].pos.x += -DOG_SPEED * 0.1f;
					//	if (dog[i].pos.x < cat->pos.x)
					//	{
					//		dog[i].pos.x = cat->pos.x;

					//	}
					//}
					if (dog[i].pos.x < cat->pos.x)
					{
						if (dog[i].framewait <= 0.0)
						{
							dog[i].pos.x += DOG_SPEED * 0.6f;
						}
						else
						{
							dog[i].framewait--;
						}
					}
				}
			}
		}

	}
}

//--------------------------------------------------------------------------
//四角形　VS　四角形
//--------------------------------------------------------------------------
bool DogCollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2)
{
	D3DXVECTOR2  min1, max1; //四角形1
	D3DXVECTOR2  min2, max2; //四角形2

	min1.x = pos1.x - size1.x / 2;  //四角形1　左上
	min1.y = pos1.y - size1.y / 2;

	max1.x = pos1.x + size1.x / 2;  //四角形1　右下
	max1.y = pos1.y + size1.y / 2;

	min2.x = pos2.x - size2.x / 2;  //四角形2　左上
	min2.y = pos2.y - size2.y / 2;

	max2.x = pos2.x + size2.x / 2;  //四角形2　右下
	max2.y = pos2.y + size2.y / 2;

	//衝突判定
	if (max1.x < min2.x)
	{
		return false;
	}

	if (max2.x < min1.x)
	{
		return false;
	}

	if (max1.y < min2.y)
	{
		return false;
	}

	if (max2.y < min1.y)
	{
		return false;
	}

	return true; 
}