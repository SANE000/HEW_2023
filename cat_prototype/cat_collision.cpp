
#include "cat.h"
#include "block.h"
#include "blockpreview.h"
#include "gimmick_wall.h"

#include "collision.h"
#include "scene.h"

#include "cat_collision.h"

void UpdateCatCollision()
{
	int temp = 0;
	int m_temp = 0;
	int g_temp = 0;
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
		temp = BLOCK_MAX;
		m_temp = MOVE_BLOCK_MAX;
		//==============================================================================================================================
		//		//�����Ȃ��u���b�N�ƔL�̓����蔻��//////////////////////////////////////////////////////////////////////////////////////
		//==============================================================================================================================
		for (int i = 0; i < BLOCK_MAX; i++)
		{
			float BlockTop = block[i].pos.y - SIZE / 2;
			float BlockBottom = block[i].pos.y + SIZE / 2;
			float BlockLeft = block[i].pos.x - SIZE / 2;
			float BlockRight = block[i].pos.x + SIZE / 2;
			//�����\���̂��g���ĂȂ�������X�L�b�v
			if (block[i].use != true)
			{
				if (temp > 0)
				{
					temp -= 1;
				}
				continue;
			}
			//�����蔻����s��
			bool hit = CollisionBB(
				cat->pos, block[i].pos,
				D3DXVECTOR2(CAT_SIZE_W, CAT_SIZE_H),
				D3DXVECTOR2(SIZE, SIZE)
			);
			//�u���b�N�ɐG��Ă���
			if (hit == true)
			{

				//���u���b�N����(�d��GRAV�̉e�����r������)
				if (CatBottom - GRAV <= BlockTop && cat->pos.y < block[i].pos.y)
				{
					//�u���b�N�ƐG��Ă��鎞�̓u���b�N�ɒ��ݍ��܂Ȃ��悤�ɍ��W���Œ肷��
					cat->pos.y = BlockTop - GRAV - SIZE / 2;
					temp = BLOCK_MAX;

					if (block[i].Patern == 2.0f)
					{
						if (block[i].pos.x - 10.0f < cat->pos.x && block[i].pos.x + 10.0f > cat->pos.x)
						{
							ChangeMoveFlag(cat);
						}
					}

					//�T�{�e���ɐG�ꂽ��
					if (block[i].Patern >= 15.0f && block[i].Patern <= 16.9f)
					{
						if (block[i].pos.x - 25.0f < cat->pos.x && block[i].pos.x + 25.0f > cat->pos.x)
						{
							//�Q�[���I�[�o�[
							SetScene(SCENE_GAMEOVER);
						}
					}

					//	�o�l�u���b�N�������Œ��S������ɏ���������˂鏈��
					if (block[i].Patern >= 9.0f && block[i].Patern <= 11.9f || block[i].Patern >= 17.0f && block[i].Patern <= 19.9f)
					{
						//�Ȃ�����
						block[i].Patern += 0.1f;
						if (block[i].pos.x - 5.0f < cat->pos.x && block[i].pos.x + 5.0f > cat->pos.x)
						{
							//�Ƃ肠����7�i	
							CatJump(7.0f);
							//��񂾏u�Ԃɖ߂�
							if (block[i].Patern >= 9.0f && block[i].Patern <= 11.9f)
							{
								block[i].Patern = 9.0f;
							}

							if (block[i].Patern >= 17.0f && block[i].Patern <= 19.9f)
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
						block[i].ontime -= 1;
						if (block[i].ontime <= 0)
						{
							//���̔ԍ��B�Ȃɂ��`�悵�Ȃ�
							block[i].Patern = 23.0f;
							block[i].use = false;
						}
					}

					if (block[i].button == true)
					{
						//�G�ꂽ�u��false�ɂȂ�Ȃ��悤�ɒ��S�������false�ɂ���
						if (block[i].pos.x - 10.0f < cat->pos.x && block[i].pos.x + 10.0f > cat->pos.x)
						{
							block[i].button = false;
							block[i].use = false;
						}

					}
				}
				//���u���b�N��艺
				else if (CatTop <= BlockBottom &&
					cat->pos.y - (SIZE / 2 - GRAV) > block[i].pos.y + (SIZE / 2 - GRAV))
				{
					//�u���b�N�Ƀv���C���[�̏�ʂŐG��Ă��鎞�̓W�����v�͂�0�ɂ���
					cat->jump_y = 0;


				}
				//���u���b�N���E
				else if (CatLeft <= BlockRight && cat->pos.x > BlockRight)
				{
					//�u���b�N�ƐG��Ă��鎞�̓u���b�N�ɒ��ݍ��܂Ȃ��悤�ɍ��W���Œ肷��
					cat->pos.x = BlockRight + SIZE / 2;
					//�T�{�e���ɐG�ꂽ��
					if (block[i].Patern >= 15.0f && block[i].Patern <= 16.9f)
					{
						//�Q�[���I�[�o�[
						SetScene(SCENE_GAMEOVER);
					}
					//�ǂɂԂ������甽�]�B�E��
					ChangeMoveFlag(cat);

				}
				//���u���b�N��荶
				else if (CatRight >= BlockLeft && cat->pos.x < block[i].pos.x)
				{//��
					//�u���b�N�ƐG��Ă��鎞�̓u���b�N�ɒ��ݍ��܂Ȃ��悤�ɍ��W���Œ肷��
					cat->pos.x = BlockLeft - SIZE / 2;
					//�T�{�e���ɐG�ꂽ��
					if (block[i].Patern >= 15.0f && block[i].Patern <= 16.9f)
					{
						//�Q�[���I�[�o�[
						SetScene(SCENE_GAMEOVER);
					}
					//�ǂɂԂ������甽�]�B����
					ChangeMoveFlag(cat);

				}
			}
			else
			{
				if (temp > 0)
				{
					temp -= 1;
				}
			}
		}
		//==============================================================================================================================
		//			//MOVE�u���b�N�ƔL�̓����蔻��//////////////////////////////////////////////////////////////////////////////////////
		//==============================================================================================================================
		for (int i = 0; i < MOVE_BLOCK_MAX; i++)
		{

			//�����\���̂��g���ĂȂ�������X�L�b�v
			if (m_block[i].use != true)
			{
				if (m_temp > 0)
				{
					m_temp -= 1;
				}
				continue;
			}

			float BlockTopM = m_block[i].pos.y - SIZE / 2;
			float BlockBottomM = m_block[i].pos.y + SIZE / 2;
			float BlockLeftM = m_block[i].pos.x - SIZE / 2;
			float BlockRightM = m_block[i].pos.x + SIZE / 2;

			//�����蔻����s��
			bool hit = CollisionBB(
				cat->pos, m_block[i].pos,
				D3DXVECTOR2(CAT_SIZE_W, CAT_SIZE_H),
				D3DXVECTOR2(SIZE, SIZE)
			);
			//�u���b�N�ɐG��Ă���
			if (hit == true)
			{
				//�L�����u���b�N����(�d��GRAV�̉e�����r������)
				if (CatBottom - GRAV <= BlockTopM && cat->pos.y < m_block[i].pos.y)
				{
					//�u���b�N�ƐG��Ă��鎞�̓u���b�N�ɒ��ݍ��܂Ȃ��悤�ɍ��W���Œ肷��
					cat->pos.y = BlockTopM - GRAV - SIZE / 2;
					m_temp = MOVE_BLOCK_MAX;
						
					//	�o�l�u���b�N�������Œ��S������ɏ���������˂鏈��
					if (m_block[i].Patern >= 2.0f && m_block[i].Patern <= 4.9f)
					{
						//�Ȃ�����
						m_block[i].Patern += 0.1f;
						if (m_block[i].pos.x - 5.0f < cat->pos.x && m_block[i].pos.x + 5.0f > cat->pos.x)
						{
							//�Ƃ肠����3�i	
							CatJump(3.0f);
							//��񂾏u�Ԃɖ߂�
							if (m_block[i].Patern >= 2.0f && m_block[i].Patern <= 4.9f)
							{
								m_block[i].Patern = 2.0f;
							}
						}
					}

					//	�܂Ƃ��u���b�N
					if (m_block[i].Patern >= 5.0f && m_block[i].Patern <= 5.9f)
					{
						if (m_block[i].pos.x - 2.5f < cat->pos.x && m_block[i].pos.x + 2.5f > cat->pos.x)
						{
							cat->tumetogi_flag = true;
						}

					}

						
						;
				}
				//�L���u���b�N���E
				else if (CatLeft <= BlockRightM && cat->pos.x > BlockRightM)
				{
					//�u���b�N�ƐG��Ă��鎞�̓u���b�N�ɒ��ݍ��܂Ȃ��悤�ɍ��W���Œ肷��
					cat->pos.x = BlockRightM + SIZE / 2;
				}
				//�L���u���b�N��荶 
				else if (CatRight >= BlockLeftM && CatRight < m_block[i].pos.x)
				{//��
					//�u���b�N�ƐG��Ă��鎞�̓u���b�N�ɒ��ݍ��܂Ȃ��悤�ɍ��W���Œ肷��
					cat->pos.x = BlockLeftM - SIZE / 2;

					//�u���b�N�ƂԂ������Ƃ���ׂ鍂�������ׂ�֐�
					//����:moveblock�̃|�C���^,�L�|�C���^,�Ԃ������u���b�N�̓Y����
					//���ō쐬
					//CatJump(SearchJumpHeight(m_block, cat, i));

				}
			}
			else
			{
				if (m_temp > 0)
				{
					m_temp -= 1;
				}
			}
		}
		//==============================================================================================================================
		//			//�M�~�b�N�E�H�[���ƔL�̓����蔻��/////////////////////////////////////////////////////////////////////////////////
		//==============================================================================================================================
		for (int i = 0; i < WALL_MAX; i++)
		{

			//�����\���̂��g���ĂȂ�������X�L�b�v
			if (gimmickwall[i].use != true)
			{
				if (g_temp > 0)
				{
					g_temp -= 1;
				}
				continue;
			}

			float GimmickWallTop = gimmickwall[i].pos.y - SIZE / 2;
			float GimmickWallBottom = gimmickwall[i].pos.y + SIZE / 2;
			float GimmickWallLeft = gimmickwall[i].pos.x - SIZE / 2;
			float GimmickWallRight = gimmickwall[i].pos.x + SIZE / 2;

			//�����蔻����s��
			bool hit = CollisionBB(
				cat->pos, gimmickwall[i].pos,
				D3DXVECTOR2(CAT_SIZE_W, CAT_SIZE_H),
				D3DXVECTOR2(SIZE, SIZE)
			);
			//�u���b�N�ɐG��Ă���
			if (hit == true)
			{
				//�u���b�N����(�d��GRAV�̉e�����r������)
				if (CatBottom - GRAV <= GimmickWallTop && cat->pos.y < gimmickwall[i].pos.y)
				{
					//�u���b�N�ƐG��Ă��鎞�̓u���b�N�ɒ��ݍ��܂Ȃ��悤�ɍ��W���Œ肷��
					cat->pos.y = GimmickWallTop - GRAV - SIZE / 2;
					g_temp = WALL_MAX;
				}
				//�u���b�N��艺
				else if (CatTop <= GimmickWallBottom &&
					cat->pos.y - (CAT_SIZE_H / 2 - GRAV) > gimmickwall[i].pos.y + (SIZE / 2 - GRAV))
				{
					//�u���b�N�Ƀv���C���[�̏�ʂŐG��Ă��鎞�̓W�����v�͂�0�ɂ���
					cat->jump_y = 0;
				}
				//�L���u���b�N���E
				else if (CatLeft <= GimmickWallRight && cat->pos.x > GimmickWallRight)
				{
					//�u���b�N�ƐG��Ă��鎞�̓u���b�N�ɒ��ݍ��܂Ȃ��悤�ɍ��W���Œ肷��
					cat->pos.x = GimmickWallRight + SIZE / 2 + cat->dir.x + 1;

					//�ǂɂԂ������甽�]�B�E��
					ChangeMoveFlag(cat);
				}
				//�L���u���b�N��荶 
				else if (CatRight >= GimmickWallLeft && CatRight < gimmickwall[i].pos.x)
				{//��
					//�u���b�N�ƐG��Ă��鎞�̓u���b�N�ɒ��ݍ��܂Ȃ��悤�ɍ��W���Œ肷��
					cat->pos.x = GimmickWallLeft - SIZE / 2 - cat->dir.x - 1;

					//�ǂɂԂ������甽�]�B����
					ChangeMoveFlag(cat);
				}
			}
			else
			{
				if (g_temp > 0)
				{
					g_temp -= 1;
				}
			}
		}
		//�S�Ẵu���b�N��������ɃW�����v�t���O��ݒ肷��
		if (g_temp > 0 || m_temp > 0 || temp > 2)
		{
			cat->jump_flag = true;
			cat->nowjump_flag = 0;
		}
		else
		{
			cat->jump_flag = false;
		}

	}
}