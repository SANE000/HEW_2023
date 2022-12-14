#include "main.h"
#include "dogCollision.h"
#include "cat.h"
#include "Scene.h"
#include "shop.h"
#include "dog.h"
#include "block.h"
#include "blockpreview.h"
#include "gimmick_wall.h"

#include "collision.h"

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
	G_WALL* gimmickwall = GetGimmickWall();

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
				bool hit = CollisionBB(cat->pos, dog[i].pos, D3DXVECTOR2(SIZE, SIZE), D3DXVECTOR2(dog[i].w, dog[i].h));
				if (hit == true)
				{
					SetScene(SCENE_GAMEOVER);
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
				bool hit = CollisionBB(dog[i].pos, block[b].pos, D3DXVECTOR2(dog[i].w, dog[i].h), D3DXVECTOR2(SIZE, SIZE));
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
					}
					//床ブロックより左
					else if (DogRight >= BlockLeft && dog[i].pos.x < block[i].pos.x)
					{//左
						//ブロックと触れている時はブロックに沈み込まないように座標を固定する
						dog[i].pos.x = BlockLeft - SIZE / 2;
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

					bool hit = CollisionBB(dog[i].pos, m_block[b].pos, D3DXVECTOR2(dog[i].w, dog[i].h), D3DXVECTOR2(SIZE, SIZE));
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
		//dog vs gimmki_wall
		for (int i = 0; i < DOG_MAX; i++)
		{
			float DogTop = dog[i].pos.y - SIZE / 2;
			float DogBottom = dog[i].pos.y + SIZE / 2;
			float DogLeft = dog[i].pos.x - SIZE / 2;
			float DogRight = dog[i].pos.x + SIZE / 2;

			if (dog[i].use == true)
			{
				for (int b = 0; b < WALL_MAX; b++)
				{
					float BlockTopG = gimmickwall[b].pos.y - SIZE / 2;
					float BlockBottomG = gimmickwall[b].pos.y + SIZE / 2;
					float BlockLeftG = gimmickwall[b].pos.x - SIZE / 2;
					float BlockRightG = gimmickwall[b].pos.x + SIZE / 2;
					//もし構造体を使ってなかったらスキップ
					if (gimmickwall[b].use != true)
					{
						continue;
					}
					//
					bool hit = CollisionBB(dog[i].pos, gimmickwall[b].pos, D3DXVECTOR2(dog[i].w, dog[i].h), D3DXVECTOR2(SIZE, SIZE));
					if (hit == true)
					{
						//床ブロックより上(重力GRAVの影響も排除する)
						if (DogBottom - GRAV <= BlockTopG && dog[i].pos.y < gimmickwall[b].pos.y)
						{
							//ブロックと触れている時はブロックに沈み込まないように座標を固定する
							dog[i].pos.y = BlockTopG - GRAV - SIZE / 2;
							temp = BLOCK_MAX;
						}
						//床ブロックより下
						else if (DogTop <= BlockBottomG &&
							dog[i].pos.y - (SIZE / 2 - GRAV) > gimmickwall[b].pos.y + (SIZE / 2 - GRAV))
						{
							dog[i].use = false;
						}
						//床ブロックより右
						else if (DogLeft <= BlockRightG && dog[i].pos.x > BlockRightG)
						{
							//ブロックと触れている時はブロックに沈み込まないように座標を固定する
							dog[i].pos.x = BlockRightG + SIZE / 2;
						}
						//床ブロックより左
						else if (DogRight >= BlockLeftG && dog[i].pos.x < gimmickwall[i].pos.x)
						{//左
							//ブロックと触れている時はブロックに沈み込まないように座標を固定する
							dog[i].pos.x = BlockLeftG - SIZE / 2;
						}
					}
				}
			}
		}
		////close to dog
		//if (cat->use == true)
		//{
		//	for (int i = 0; i < DOG_MAX; i++)
		//	{
		//		if (dog[i].use == true)
		//		{
		//			if (dog[i].pos.x < cat->pos.x)
		//			{
		//				if (dog[i].framewait <= 0.0)
		//				{
		//					//要調整　バネや壁をすり抜けるためバグ修正が必要
		//					dog[i].pos.x += DOG_SPEED * 0.16f;
		//				}
		//				else
		//				{
		//					dog[i].framewait--;
		//				}
		//			}
		//		}
		//	}
		//}

	}
}

