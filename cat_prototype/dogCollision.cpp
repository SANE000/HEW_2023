#include "main.h"
#include "dogCollision.h"
#include "cat.h"
#include "Scene.h"
#include "shop.h"

//bool DogCollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2);

//int temp = BLOCK_MAX;

//---------------------------
//�����蔻�������
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
				//�����\���̂��g���ĂȂ�������X�L�b�v
				if (block[b].use != true)
				{
					continue;
				}
				//
				bool hit = DogCollisionBB(dog[i].pos, block[b].pos, D3DXVECTOR2(dog[i].w, dog[i].h), D3DXVECTOR2(SIZE, SIZE));
				if (hit == true)
				{
					//���u���b�N����(�d��GRAV�̉e�����r������)
					if (DogBottom - GRAV <= BlockTop && dog[i].pos.y < block[b].pos.y)
					{
						//�u���b�N�ƐG��Ă��鎞�̓u���b�N�ɒ��ݍ��܂Ȃ��悤�ɍ��W���Œ肷��
						dog[i].pos.y = BlockTop - GRAV - SIZE / 2;
						temp = BLOCK_MAX;

						if (block[b].button == true)
						{
							//�G�ꂽ�u��false�ɂȂ�Ȃ��悤�ɒ��S�������false�ɂ���
							if (block[b].pos.x - 10.0f < dog[i].pos.x && block[b].pos.x + 10.0f > dog[i].pos.x)
							{
								block[b].button = false;
							}

						}

					}
					//���u���b�N��艺
					else if (DogTop <= BlockBottom &&
						dog[i].pos.y - (SIZE / 2 - GRAV) > block[b].pos.y + (SIZE / 2 - GRAV))
					{
						dog[i].use = false;
					}
					//���u���b�N���E
					else if (DogLeft <= BlockRight && dog[i].pos.x > BlockRight)
					{
						//�u���b�N�ƐG��Ă��鎞�̓u���b�N�ɒ��ݍ��܂Ȃ��悤�ɍ��W���Œ肷��
						dog[i].pos.x = BlockRight + SIZE / 2;
						//�ǂɂԂ������甽�]�B�E��
						//ChangeMoveFlag(cat);
					}
					//���u���b�N��荶
					else if (DogRight >= BlockLeft && dog[i].pos.x < block[i].pos.x)
					{//��
						//�u���b�N�ƐG��Ă��鎞�̓u���b�N�ɒ��ݍ��܂Ȃ��悤�ɍ��W���Œ肷��
						dog[i].pos.x = BlockLeft - SIZE / 2;
						//�ǂɂԂ������甽�]�B����
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
						//�������u���b�N����(�d��GRAV�̉e�����r������)
						if (DogBottom - GRAV <= BlockTopM && dog[i].pos.y < m_block[b].pos.y)
						{
							//�u���b�N�ƐG��Ă��鎞�̓u���b�N�ɒ��ݍ��܂Ȃ��悤�ɍ��W���Œ肷��
							dog[i].pos.y = BlockTopM - GRAV - SIZE / 2;
						}
						//�����u���b�N���E
						else if (DogLeft <= BlockRightM && dog[i].pos.x > BlockRightM)
						{
							//�u���b�N�ƐG��Ă��鎞�̓u���b�N�ɒ��ݍ��܂Ȃ��悤�ɍ��W���Œ肷��
							dog[i].pos.x = BlockRightM + SIZE / 2;
						}
						//�����u���b�N��荶 
						else if (DogRight >= BlockLeftM && DogRight < m_block[b].pos.x)
						{//��
							//�u���b�N�ƐG��Ă��鎞�̓u���b�N�ɒ��ݍ��܂Ȃ��悤�ɍ��W���Œ肷��
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
//�l�p�`�@VS�@�l�p�`
//--------------------------------------------------------------------------
bool DogCollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2)
{
	D3DXVECTOR2  min1, max1; //�l�p�`1
	D3DXVECTOR2  min2, max2; //�l�p�`2

	min1.x = pos1.x - size1.x / 2;  //�l�p�`1�@����
	min1.y = pos1.y - size1.y / 2;

	max1.x = pos1.x + size1.x / 2;  //�l�p�`1�@�E��
	max1.y = pos1.y + size1.y / 2;

	min2.x = pos2.x - size2.x / 2;  //�l�p�`2�@����
	min2.y = pos2.y - size2.y / 2;

	max2.x = pos2.x + size2.x / 2;  //�l�p�`2�@�E��
	max2.y = pos2.y + size2.y / 2;

	//�Փ˔���
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