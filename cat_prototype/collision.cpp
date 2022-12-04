//�����蔻��̏���
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
//==========================================
//�O���[�o���ϐ�
//==========================================

//�L�̃W�����v�t���O�p
int temp = 0;
int m_temp = 0;
int g_temp = 0;
CAT *cat = GetCat();
PLAYER* player = GetPlayer();
BLOCK *block = GetBlock();
MOVE_BLOCK *m_block = GetMoveBlock();
G_WALL* gimmickwall = GetGimmickWall();


//�u���b�N�ƃl�R���Ԃ������ہA
//���̃u���b�N�̂P��A�Q��̃u���b�N�����݂��邩�ǂ����������ϐ�
bool blockexist1;

bool enablejump;

float catjump_height;

int blocknum;

//==============================================================================================================================
//		//�v���g�^�C�v�錾                //////////////////////////////////////////////////////////////////////////////////////
//==============================================================================================================================

//�u���b�N���m�̓����蔻��𕪂��܂����B
void BlockCollision();

//������
HRESULT InitCollsion()
{
	blockexist1 = false;

	enablejump = false;

	catjump_height = 0;

	return S_OK;
}

//�X�V�����@�����蔻�����C�ɍs��
void UpdateCollision()
{
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
					cat->pos.x = GimmickWallLeft - SIZE / 2 - cat->dir.x -1;

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
		//==============================================================================================================================
		//		//�u���b�N�W�����v�Z���T�[�ƔL�̓����蔻��//////////////////////////////////////////////////////////////////////////////
		//==============================================================================================================================
		for (int i = 0; i < BLOCK_MAX; i++)
		{

			//�����\���̂��g���ĂȂ�������X�L�b�v
			if (block[i].use != true)
			{
				continue;
			}
			
			float JumpSensorTopM = block[i].pos.y - SIZE / 2;
			float JumpSensorBottomM = block[i].pos.y + SIZE / 2;
			float JumpSensorLeftM = block[i].pos.x - SIZE / 2 - SENSOR_SIZE;
			float JumpSensorRightM = block[i].pos.x + SIZE / 2 + SENSOR_SIZE;

			//�����蔻����s��
			bool hit = CollisionBB(
				cat->pos, block[i].pos,
				D3DXVECTOR2(SIZE + SENSOR_SIZE*2, 1.0f),
				D3DXVECTOR2(SIZE, SIZE)
			);
			//�u���b�N�ɐG��Ă���
			if (hit == true)
			{
				//�ڂ̑O�̃u���b�N�̍������Ƃ�
				int jumpheight = SearchJumpHeightB(block, cat, i);

				//�L�����u���b�N���E
				if (CatLeft <= JumpSensorRightM && cat->pos.x > JumpSensorRightM)
				{
					if (cat->move_flag == true)
					{
						//�u���b�N�ƂԂ������Ƃ���ׂ鍂�������ׂ�֐�
						//����:moveblock�̃|�C���^,�L�|�C���^,�Ԃ������u���b�N�̓Y����
						//���ō쐬

						//�W�����v����i����0�ȏ�2�������ǂ���
						//0�͉�������̃G���[�@2�͔�΂��Ɉ����Ԃ�
						if (jumpheight > 0 &&
							jumpheight < 2)
						{
							//�n�ʂɂ��Ă��邩
							if (cat->jump_flag == true)
							{
								CatJump(jumpheight);
							}
						}
						else
						{
							if (cat->jump_flag == true)
							{
								//�����Ԃ�
								ChangeMoveFlag(cat);
							}
						}

					}
				}
				//�L�����u���b�N��荶
				else if (CatRight >= JumpSensorLeftM && CatRight < block[i].pos.x)
				{//��

					if (cat->move_flag == false)
					{
						//�u���b�N�ƂԂ������Ƃ���ׂ鍂�������ׂ�֐�
						//����:moveblock�̃|�C���^,�L�|�C���^,�Ԃ������u���b�N�̓Y����
						//���ō쐬

						//�W�����v����i����0�ȏ�2�������ǂ���
						//0�͉�������̃G���[�@2�͔�΂��Ɉ����Ԃ�
						if (jumpheight > 0 &&
							jumpheight < 2)
						{
							//�n�ʂɂ��Ă��邩
							if (cat->jump_flag == true)
							{
								CatJump(jumpheight);
							}
						}
						else
						{
							if (cat->jump_flag == true)
							{
								//�����Ԃ�
								ChangeMoveFlag(cat);
							}
						}
					}
				}
			}
		}
		//==============================================================================================================================
		//		//MOVE�u���b�N�W�����v�Z���T�[�ƔL�̓����蔻��//////////////////////////////////////////////////////////////////////////
		//==============================================================================================================================
		for (int i = 0; i < MOVE_BLOCK_MAX; i++)
		{

			//�����\���̂��g���ĂȂ�������X�L�b�v
			if (m_block[i].use != true)
			{
				continue;
			}

			float JumpSensorTopM = m_block[i].pos.y - SIZE / 2;
			float JumpSensorBottomM = m_block[i].pos.y + SIZE / 2;
			float JumpSensorLeftM = m_block[i].pos.x - SIZE / 2 - SENSOR_SIZE;
			float JumpSensorRightM = m_block[i].pos.x + SIZE / 2 + SENSOR_SIZE;
			//�����蔻����s��
			bool hit = CollisionBB(
				cat->pos, m_block[i].pos,
				D3DXVECTOR2(SIZE + SENSOR_SIZE * 2, 1.0f),
				D3DXVECTOR2(SIZE, SIZE)
			);
			//�u���b�N�ɐG��Ă���
			if (hit == true)
			{
				//�ڂ̑O�̃u���b�N�̍������Ƃ�
				int jumpheight = SearchJumpHeight(m_block, cat, i);

				//�L�����u���b�N���E
				if (CatLeft <= JumpSensorRightM && cat->pos.x > JumpSensorRightM)
				{
					if (cat->move_flag == true)
					{
						//�u���b�N�ƂԂ������Ƃ���ׂ鍂�������ׂ�֐�
						//����:moveblock�̃|�C���^,�L�|�C���^,�Ԃ������u���b�N�̓Y����
						//���ō쐬

						//�W�����v����i����0�ȏ�2�������ǂ���
						//0�͉�������̃G���[�@2�͔�΂��Ɉ����Ԃ�
						if (jumpheight > 0 &&
							jumpheight < 2)
						{
							//�n�ʂɂ��Ă��邩
							if (cat->jump_flag == true)
							{
								CatJump(jumpheight);
							}
						}
						else
						{
							//�����Ԃ�
							ChangeMoveFlag(cat);
						}

					}
				}
				//�L�����u���b�N��荶
				else if (CatRight >= JumpSensorLeftM && CatRight < m_block[i].pos.x)
				{//��

					if (cat->move_flag == false)
					{
						//�u���b�N�ƂԂ������Ƃ���ׂ鍂�������ׂ�֐�
						//����:moveblock�̃|�C���^,�L�|�C���^,�Ԃ������u���b�N�̓Y����
						//���ō쐬

						//�W�����v����i����0�ȏ�2�������ǂ���
						//0�͉�������̃G���[�@2�͔�΂��Ɉ����Ԃ�
						if (jumpheight > 0 &&
							jumpheight < 2)
						{
							//�n�ʂɂ��Ă��邩
							if (cat->jump_flag == true)
							{
								CatJump(jumpheight);
							}
						}
						else
						{
							//�����Ԃ�
							ChangeMoveFlag(cat);
						}
					}
				}
			}
		}
//==============================================================================================================================
//		//�M�~�b�N�ǃW�����v�Z���T�[�ƔL�̓����蔻��//////////////////////////////////////////////////////////////////////////
//==============================================================================================================================
		for (int i = 0; i < WALL_MAX; i++)
		{

			//�����\���̂��g���ĂȂ�������X�L�b�v
			if (gimmickwall[i].use != true)
			{
				continue;
			}

			float JumpSensorTopM = gimmickwall[i].pos.y - SIZE / 2;
			float JumpSensorBottomM = gimmickwall[i].pos.y + SIZE / 2;
			float JumpSensorLeftM = gimmickwall[i].pos.x - SIZE / 2 - SENSOR_SIZE;
			float JumpSensorRightM = gimmickwall[i].pos.x + SIZE / 2 + SENSOR_SIZE;
			//�����蔻����s��
			bool hit = CollisionBB(
				cat->pos, gimmickwall[i].pos,
				D3DXVECTOR2(SIZE + SENSOR_SIZE * 2, 1.0f),
				D3DXVECTOR2(SIZE, SIZE)
			);
			//�u���b�N�ɐG��Ă���
			if (hit == true)
			{
				//�ڂ̑O�̃u���b�N�̍������Ƃ�
				int jumpheight = SearchJumpHeightG(gimmickwall, cat, i);

				//�L�����u���b�N���E
				if (CatLeft <= JumpSensorRightM && cat->pos.x > JumpSensorRightM)
				{
					if (cat->move_flag == true)
					{
						//�u���b�N�ƂԂ������Ƃ���ׂ鍂�������ׂ�֐�
						//����:moveblock�̃|�C���^,�L�|�C���^,�Ԃ������u���b�N�̓Y����
						//���ō쐬

						//�W�����v����i����0�ȏ�2�������ǂ���
						//0�͉�������̃G���[�@2�͔�΂��Ɉ����Ԃ�
						if (jumpheight > 0 &&
							jumpheight < 2)
						{
							//�n�ʂɂ��Ă��邩
							if (cat->jump_flag == true)
							{
								CatJump(jumpheight);
							}
						}
						else
						{
							//�����Ԃ�
							ChangeMoveFlag(cat);
						}

					}
				}
				//�L�����u���b�N��荶
				else if (CatRight >= JumpSensorLeftM && CatRight < gimmickwall[i].pos.x)
				{//��

					if (cat->move_flag == false)
					{
						//�u���b�N�ƂԂ������Ƃ���ׂ鍂�������ׂ�֐�
						//����:moveblock�̃|�C���^,�L�|�C���^,�Ԃ������u���b�N�̓Y����
						//���ō쐬

						//�W�����v����i����0�ȏ�2�������ǂ���
						//0�͉�������̃G���[�@2�͔�΂��Ɉ����Ԃ�
						if (jumpheight > 0 &&
							jumpheight < 2)
						{
							//�n�ʂɂ��Ă��邩
							if (cat->jump_flag == true)
							{
								CatJump(jumpheight);
							}
						}
						else
						{
							//�����Ԃ�
							ChangeMoveFlag(cat);
						}
					}
				}
			}
		}
		//�u���b�N���m�̓����蔻��
		BlockCollision();
	}
}

//==============================================================================================================================
//		//�W�����v�֘A�̊֐��B�@�@�@�@�@�@//////////////////////////////////////////////////////////////////////////////////////
//==============================================================================================================================

//�u���b�N�ƂԂ������Ƃ���ׂ鍂�������ׂ�֐��@�����u���b�N�ƂԂ������Ƃ�
//����:moveblock�̃|�C���^,�L�|�C���^,�Ԃ������u���b�N�̓Y����
float SearchJumpHeight(MOVE_BLOCK* mb, CAT* c, int i)
{
	//�W�����v�t���O��true��������
					//���ɂ��Ă�����
	if (GetJumpFlag() == true)
	{

		//�S�u���b�N��T�m
		//�Ԃ������u���b�N�Ɠ���x���W�ň��̍����̃u���b�N��T��
		//���ꂪ����������̍����̃u���b�N��T��
		//�S������ΎO���W�����v�@�W�����v�̍��������߂�

		for (int a = 0; a < MOVE_BLOCK_MAX; a++)
		{
			//�S���̃u���b�N������������I��
			if (blockexist1 == true)
			{
				break;
			}

			//x���W�������Ȃ�
			if (mb[a].pos.x == mb[i].pos.x)
			{
				//y�������Ȃ�
				if (mb[a].pos.y <= (mb[i].pos.y - SIZE / 2) &&
					mb[a].pos.y >= (mb[i].pos.y - (SIZE + SIZE / 2)))
				{
					blockexist1 = true;
				}
				////2��Ȃ�
				//else if (mb[b].pos.y <= (mb[i].pos.y - (SIZE + SIZE / 2)) &&
				//	mb[b].pos.y >= (mb[i].pos.y - (SIZE * 2 + SIZE / 2)))
				//{
				//	blockexist2 = true;
				//}
				////3��Ȃ�
				//else if (mb[b].pos.y <= (mb[i].pos.y - (SIZE * 2 + SIZE / 2)) &&
				//	mb[b].pos.y >= (mb[i].pos.y - (SIZE * 3 + SIZE / 2)))
				//{
				//	blockexist3 = true;
				//}

			}

		}

		//���i��ׂ�Ƃ����ϐ���n��
		//blockexisit��false�ɂ���

		//�ǂ�����������Ȃ�������
		if (blockexist1 == false)
		{
			catjump_height = 1;
			enablejump = true;
		}
		//��ゾ�����݂���
		else if (blockexist1 == true)
		{
			catjump_height = 2;
			enablejump = false;
		}
		////���Ɠ�㑶�݂���
		//else if (blockexist1 == true && blockexist2 == true )
		//{
		//	catjump_height = 3;
		//	enablejump = true;
		//}
		////�S�����݂���
		//else if (blockexist1 == true && blockexist2 == true && blockexist3 == true)
		//{
		//	catjump_height = 4;
		//	enablejump = false;
	}

	//���̃u���b�N�������݂����ۂǂ����邩�͍���l����
	//else if (blockexist1 == false && blockexist2 == true)

	blockexist1 = false;
	return catjump_height;
}

//�u���b�N�ƂԂ������Ƃ���ׂ鍂�������ׂ�֐� ���u���b�N�ƂԂ������Ƃ�
//����:block�̃|�C���^,�L�|�C���^,�Ԃ������u���b�N�̓Y����
float SearchJumpHeightB(BLOCK* b, CAT* c, int i)
{
	//�W�����v�t���O��true��������
					//���ɂ��Ă�����
	if (GetJumpFlag() == true)
	{

		//�S�u���b�N��T�m
		//�Ԃ������u���b�N�Ɠ���x���W�ň��̍����̃u���b�N��T��
		//���ꂪ����������̍����̃u���b�N��T��
		//�S������ΎO���W�����v�@�W�����v�̍��������߂�
		for (int a = 0; a < BLOCK_MAX; a++)
		{
			//�S���̃u���b�N������������I��
			if (blockexist1 == true)
			{
				break;
			}

			//x���W�������Ȃ�
			if (b[a].pos.x == b[i].pos.x)
			{
				//y�������Ȃ�
				if (b[a].pos.y <= (b[i].pos.y - SIZE / 2) &&
					b[a].pos.y >= (b[i].pos.y - (SIZE + SIZE / 2)))
				{
					blockexist1 = true;
				}
				////2��Ȃ�
				//else if (mb[b].pos.y <= (mb[i].pos.y - (SIZE + SIZE / 2)) &&
				//	mb[b].pos.y >= (mb[i].pos.y - (SIZE * 2 + SIZE / 2)))
				//{
				//	blockexist2 = true;
				//}
				////3��Ȃ�
				//else if (mb[b].pos.y <= (mb[i].pos.y - (SIZE * 2 + SIZE / 2)) &&
				//	mb[b].pos.y >= (mb[i].pos.y - (SIZE * 3 + SIZE / 2)))
				//{
				//	blockexist3 = true;
				//}

			}

		}

		for (int a = 0; a < BLOCK_MAX; a++)
		{
			//�S���̃u���b�N������������I��
			if (blockexist1 == true)
			{
				break;
			}

			//x���W�������Ȃ�
			if (b[a].pos.x == b[i].pos.x)
			{
				//y�������Ȃ�
				if (b[a].pos.y <= (b[i].pos.y - SIZE / 2) &&
					b[a].pos.y >= (b[i].pos.y - (SIZE + SIZE / 2)))
				{
					blockexist1 = true;
				}
				////2��Ȃ�
				//else if (mb[b].pos.y <= (mb[i].pos.y - (SIZE + SIZE / 2)) &&
				//	mb[b].pos.y >= (mb[i].pos.y - (SIZE * 2 + SIZE / 2)))
				//{
				//	blockexist2 = true;
				//}
				////3��Ȃ�
				//else if (mb[b].pos.y <= (mb[i].pos.y - (SIZE * 2 + SIZE / 2)) &&
				//	mb[b].pos.y >= (mb[i].pos.y - (SIZE * 3 + SIZE / 2)))
				//{
				//	blockexist3 = true;
				//}

			}

		}

		//���i��ׂ�Ƃ����ϐ���n��
		//blockexisit��false�ɂ���

		//�ǂ�����������Ȃ�������
		if (blockexist1 == false)
		{
			catjump_height = 1;
			enablejump = true;
		}
		//��ゾ�����݂���
		else if (blockexist1 == true)
		{
			catjump_height = 2;
			enablejump = false;
		}
	}

	//���̃u���b�N�������݂����ۂǂ����邩�͍���l����
	//else if (blockexist1 == false && blockexist2 == true)

	blockexist1 = false;
	return catjump_height;
}

//�M�~�b�N�u���b�N�ƂԂ������Ƃ���ׂ鍂�������ׂ�֐� ���u���b�N�ƂԂ������Ƃ�
//����:g_wall�̃|�C���^,�L�|�C���^,�Ԃ������u���b�N�̓Y����
float SearchJumpHeightG(G_WALL* g, CAT* c, int i)
{
	//�W�����v�t���O��true��������
					//���ɂ��Ă�����
	if (GetJumpFlag() == true)
	{

		//�S�u���b�N��T�m
		//�Ԃ������u���b�N�Ɠ���x���W�ň��̍����̃u���b�N��T��
		//���ꂪ����������̍����̃u���b�N��T��
		//�S������ΎO���W�����v�@�W�����v�̍��������߂�
		for (int a = 0; a < WALL_MAX; a++)
		{
			//�S���̃u���b�N������������I��
			if (blockexist1 == true)
			{
				break;
			}

			//x���W�������Ȃ�
			if (g[a].pos.x == g[i].pos.x)
			{
				//y�������Ȃ�
				if (g[a].pos.y <= (g[i].pos.y - SIZE / 2) &&
					g[a].pos.y >= (g[i].pos.y - (SIZE + SIZE / 2)))
				{
					blockexist1 = true;
				}
			}

		}

		for (int a = 0; a < WALL_MAX; a++)
		{
			//�S���̃u���b�N������������I��
			if (blockexist1 == true)
			{
				break;
			}

			//x���W�������Ȃ�
			if (g[a].pos.x == g[i].pos.x)
			{
				//y�������Ȃ�
				if (g[a].pos.y <= (g[i].pos.y - SIZE / 2) &&
					g[a].pos.y >= (g[i].pos.y - (SIZE + SIZE / 2)))
				{
					blockexist1 = true;
				}
			}

		}

		//���i��ׂ�Ƃ����ϐ���n��
		//blockexisit��false�ɂ���

		//�ǂ�����������Ȃ�������
		if (blockexist1 == false)
		{
			catjump_height = 1;
			enablejump = true;
		}
		//��ゾ�����݂���
		else if (blockexist1 == true)
		{
			catjump_height = 2;
			enablejump = false;
		}
	}

	//���̃u���b�N�������݂����ۂǂ����邩�͍���l����
	//else if (blockexist1 == false && blockexist2 == true)

	blockexist1 = false;
	return catjump_height;
}


int GetBlockNum()
{
	return blocknum;
}


void BlockCollision()
{
	//==============================================================================================================================
	//		//�M�~�b�N�ǂ�MOVE�u���b�N���m�̓����蔻��//////////////////////////////////////////////////////////////////////////////
	//==============================================================================================================================
	//�����u���b�N�Ɠ����Ȃ��u���b�N�̓����蔻��
	for (int i = 0; i < MOVE_BLOCK_MAX; i++)
	{
		//�����u���b�N�͑��݂���H
		if (m_block[i].use == true)
		{
			float BlockTopI = m_block[i].pos.y - SIZE / 2;
			float BlockBottomI = m_block[i].pos.y + SIZE / 2;
			//������̍\���̂�S�Ē��ׂ�
			for (int n = 0; n < WALL_MAX; n++)
			{
				//�M�~�b�N�ǂ͎��݂���H
				if (gimmickwall[n].use == true)
				{
					float G_Top = gimmickwall[n].pos.y - SIZE / 2;
					float G_Bottom = gimmickwall[n].pos.y + SIZE / 2;
					//�����蔻��
					bool hit = CollisionBB(
						m_block[i].pos, gimmickwall[n].pos,
						D3DXVECTOR2(SIZE, SIZE),
						D3DXVECTOR2(SIZE, SIZE)
					);
					if (hit == true)
					{
						//N�u���b�N����(�d��GRAV�̉e�����r������)
						if (BlockBottomI - GRAV <= G_Top && m_block[i].pos.y < gimmickwall[n].pos.y)
						{
							//�u���b�N�ƐG��Ă��鎞�̓u���b�N�ɒ��ݍ��܂Ȃ��悤�ɍ��W���Œ肷��
							m_block[i].pos.y = G_Top - 1 - DRAW_SIZE / 2;
						}
					}
				}
			}
		}
	}
	//==============================================================================================================================
	//		//�����u���b�N�Ɠ����Ȃ��u���b�N�̓����蔻��////////////////////////////////////////////////////////////////////////////
	//==============================================================================================================================
	for (int i = 0; i < MOVE_BLOCK_MAX; i++)
	{
		//�����u���b�N�͑��݂���H
		if (m_block[i].use == true)
		{
			float BlockTopI = m_block[i].pos.y - SIZE / 2;
			float BlockBottomI = m_block[i].pos.y + SIZE / 2;
			//������̍\���̂�S�Ē��ׂ�
			for (int n = 0; n < BLOCK_MAX; n++)
			{
				//�����Ȃ��u���b�N�͎��݂���H
				if (block[n].use == true)
				{
					float BlockTop = block[n].pos.y - SIZE / 2;
					float BlockBottom = block[n].pos.y + SIZE / 2;
					//�����蔻��
					bool hit = CollisionBB(
						m_block[i].pos, block[n].pos,
						D3DXVECTOR2(SIZE, SIZE),
						D3DXVECTOR2(SIZE, SIZE)
					);
					if (hit == true)
					{
						//N�u���b�N����(�d��GRAV�̉e�����r������)
						if (BlockBottomI - GRAV <= BlockTop && m_block[i].pos.y < block[n].pos.y)
						{
							//�u���b�N�ƐG��Ă��鎞�̓u���b�N�ɒ��ݍ��܂Ȃ��悤�ɍ��W���Œ肷��
							m_block[i].Speed.y = 0;
							m_block[i].pos.y = BlockTop - 1 - DRAW_SIZE / 2;
						}
					}
				}
			}
		}
	}

	//==============================================================================================================================
//		//MOVE�u���b�N���m�̓����蔻��//////////////////////////////////////////////////////////////////////////////////////////
//==============================================================================================================================
	for (int i = 0; i < MOVE_BLOCK_MAX; i++)
	{
		//�u���b�N�͑��݂���H
		if (m_block[i].use == true)
		{
			//���݂��������Ă�������
			float BlockTopI = m_block[i].pos.y - SIZE / 2;
			float BlockBottomI = m_block[i].pos.y + SIZE / 2;
			float BlockLeftI = m_block[i].pos.x - DRAW_SIZE / 2;
			float BlockRightI = m_block[i].pos.x + DRAW_SIZE / 2;
			//������̍\���̂�S�Ē��ׂ�
			for (int n = 0; n < MOVE_BLOCK_MAX; n++)
			{
				if (m_block[n].use == true)
				{
					//�����Ǝ����̓����蔻��͂Ƃ�Ȃ��ŃX�L�b�v
					if (i == n)
					{
						continue;
					}
					//���݂������莩���ȊO������������
					float BlockTopN = m_block[n].pos.y - SIZE / 2;
					float BlockBottomN = m_block[n].pos.y + SIZE / 2;
					float BlockLeftN = m_block[n].pos.x - DRAW_SIZE / 2;
					float BlockRightN = m_block[n].pos.x + DRAW_SIZE / 2;
					//�����蔻��
					bool hit = CollisionBB(
						m_block[i].pos, m_block[n].pos,
						D3DXVECTOR2(DRAW_SIZE, SIZE + GRAV * 2),
						D3DXVECTOR2(DRAW_SIZE, SIZE + GRAV * 2)
					);
					if (hit == true)
					{
						//N�u���b�N����(�d��GRAV�̉e�����r������)
						if (m_block[i].pos.y < m_block[n].pos.y)
						{
							//BlockBottomI - GRAV  <= BlockTopN &&

							//���ɂ���u���b�N���n�ʂɐG��Ă���u���b�N�Ȃ̂��m���߂Ă����Ȃ瓖���蔻��Ŏ~�܂鏈���̒ǉ��̕K�v�����邩��
							if (m_block[i].pos.x - DRAW_SIZE / 2 <= m_block[n].pos.x && m_block[i].pos.x + DRAW_SIZE / 2 >= m_block[n].pos.x)
							{
								if (m_block[i].Speed.y == 0 && m_block[n].Speed.y != 0)
								{
									//�u���b�N�ƐG��Ă��鎞�̓u���b�N�ɒ��ݍ��܂Ȃ��悤�ɍ��W���Œ肷��
									m_block[n].Speed.y = 0;
									m_block[n].pos.y = BlockBottomI + DRAW_SIZE / 2;
								}
								else if (m_block[n].Speed.y == 0 && m_block[i].Speed.y != 0)
								{
									m_block[i].Speed.y = 0;
									//��i�Ȃ̂ɓo��Ȃ��ꏊ���ł��邽�ߏ������₵�܂���
									m_block[i].pos.y = BlockTopN - 2 - DRAW_SIZE / 2;
								}
							}
						}
						//N�u���b�N��艺(�d��GRAV�̉e�����r������)
						if (m_block[i].pos.y > m_block[n].pos.y)
						{
							//BlockBottomI - GRAV  <= BlockTopN &&

							//���ɂ���u���b�N���n�ʂɐG��Ă���u���b�N�Ȃ̂��m���߂Ă����Ȃ瓖���蔻��Ŏ~�܂鏈���̒ǉ��̕K�v�����邩��
							if (m_block[i].pos.x - DRAW_SIZE / 2 <= m_block[n].pos.x && m_block[i].pos.x + DRAW_SIZE / 2 >= m_block[n].pos.x)
							{
								if (m_block[i].Speed.y == 0 && m_block[n].Speed.y != 0)
								{
									//�u���b�N�ƐG��Ă��鎞�̓u���b�N�ɒ��ݍ��܂Ȃ��悤�ɍ��W���Œ肷��
									m_block[n].Speed.y = 0;
									//��i�Ȃ̂ɓo��Ȃ��ꏊ���ł��邽�ߏ������₵�܂���
									m_block[n].pos.y = BlockTopI - 2 - DRAW_SIZE / 2;

								}
								else if (m_block[n].Speed.y == 0 && m_block[i].Speed.y != 0)
								{
									m_block[i].Speed.y = 0;
									m_block[i].pos.y = BlockBottomN + DRAW_SIZE / 2;

								}
							}
						}

						//N�u���b�N���E
						if (BlockLeftI <= BlockRightN && m_block[i].pos.x > BlockRightN)
						{
							//�u���b�N�ƐG��Ă��鎞�̓u���b�N�ɒ��ݍ��܂Ȃ��悤�ɍ��W���Œ肷��
							if (m_block[i].pos.y - SIZE / 2 <= m_block[n].pos.y && m_block[i].pos.y + SIZE / 2 >= m_block[n].pos.y)
							{
								//�����O���[�v�̃u���b�N��
								if (m_block[i].group == m_block[n].group)
								{
									if (m_block[i].Speed.y == 0 && m_block[n].Speed.y != 0)
									{
										//�u���b�N�ƐG��Ă��鎞�̓u���b�N�ɒ��ݍ��܂Ȃ��悤�ɍ��W���Œ肷��

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
						//N�u���b�N��荶 
						else if (BlockRightI >= BlockLeftN && BlockRightI < m_block[n].pos.x)
						{//��

							if (m_block[i].pos.y - SIZE / 2 <= m_block[n].pos.y && m_block[i].pos.y + SIZE / 2 >= m_block[n].pos.y)
							{
								if (m_block[i].group == m_block[n].group)
								{
									if (m_block[i].Speed.y == 0 && m_block[n].Speed.y != 0)
									{
										//�u���b�N�ƐG��Ă��鎞�̓u���b�N�ɒ��ݍ��܂Ȃ��悤�ɍ��W���Œ肷��
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

//==============================================================================================================================
//		//HIT����֐��@�@�@�@�@�@�@�@�@�@�@/////////////////////////////////////////////////////////////////////////////////////
//==============================================================================================================================
bool CollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2,
	D3DXVECTOR2 size1, D3DXVECTOR2 size2)
{
	D3DXVECTOR2 min1, max1;
	D3DXVECTOR2 min2, max2;
	//�l�p�`1�̍���̍ŏ�x�ƍŏ�y
	min1.x = pos1.x - size1.x / 2;
	min1.y = pos1.y - size1.y / 2;
	//�����̂܂܂���3���@�G���������肷��Ƃ�낵
	//�l�p�`1�̉E���̍ő�x�ƍő�y
	max1.x = pos1.x + size1.x / 2;
	max1.y = pos1.y + size1.y / 2;
	//�l�p�`2�̍���̍ŏ�x�ƍŏ�y
	min2.x = pos2.x - size2.x / 2;
	min2.y = pos2.y - size2.y / 2;
	//�l�p�`1�̉E���̍ő�x�ƍő�y
	max2.x = pos2.x + size2.x / 2;
	max2.y = pos2.y + size2.y / 2;
	//�Փ˔���
	if (max1.x < min2.x)
	{
		return false;//����1�@�Փ˂��ĂȂ�
	}
	if (max1.y < min2.y)
	{
		return false;//����2�@�Փ˂��ĂȂ�
	}
	if (max2.x < min1.x)
	{
		return false;//����3�@�Փ˂��ĂȂ�
	}
	if (max2.y < min1.y)
	{
		return false;//����4�@�Փ˂��ĂȂ�
	}
	return true;//��4�����z������Փ˂��Ă�����Ă��Ƃ�����true
}
