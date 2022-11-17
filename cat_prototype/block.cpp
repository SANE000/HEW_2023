#include "main.h"
#include "block.h"
#include "player.h"
#include "texture.h"
#include "sprite.h"
#include "blocktype.h"
#include "shop.h"
#include "inputx.h"
#include "keyboard.h"
#include "camera.h"

//�}�N����`���w�b�_�[�Ɉړ�

//�v���g�^�C�v�錾
void InitStage11();
//==========================================
//�O���[�o���ϐ�
//==========================================
static int time = 0;
//�u���b�N�I�u�W�F�N�g
//�n�ʂ⑫��̔���Ɏg��

static BLOCK g_Block[BLOCK_MAX];
static MOVE_BLOCK g_MoveBlock[MOVE_BLOCK_MAX];
static PREVIEW_BLOCK g_PreviewBlock[PREVIEW_BLOCK_MAX];

BlockType blocktype[BLOCKTYPE_MAX];

int nexttype = 0;

int use_haveblock_number = 0;
int before_use_haveblock_number = 0;


//�ݒu����u���b�N�̐��@blocktype�ɉ����ĕω�
int previewblocknum = 0;

HRESULT InitBlock()
{
	nexttype = 0;

	use_haveblock_number = 0;
	before_use_haveblock_number = 0;


	//BLOCK�\���̂̏�����
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		//�e�N�X�`�����[�h �摜�̖��O�����悤
		g_Block[i].texNo = LoadTexture((char*)"data\\texture\\grass_block.png");
	}
	//����u���b�N�̐ݒu.��ԍŌ�ɐݒ�
	InitStage11();
	//�ˏo�u���b�N������
	for (int i = 0; i < MOVE_BLOCK_MAX; i++)
	{
		g_MoveBlock[i].use = false;
		g_MoveBlock[i].pos = D3DXVECTOR2(0, 0);
		g_MoveBlock[i].rot = 0.0f;
		g_MoveBlock[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_MoveBlock[i].texNo = LoadTexture((char*)"data\\texture\\sand_block.png");
		g_MoveBlock[i].type = 1;
		//���ɂ܂��������z��
		g_MoveBlock[i].Speed.x = 0.0f;
		g_MoveBlock[i].Speed.y = 0.0f;
	}
	//�v���r���[�u���b�N������
	for (int i = 0; i < PREVIEW_BLOCK_MAX; i++)
	{
		g_PreviewBlock[i].use = false;
		g_PreviewBlock[i].pos = D3DXVECTOR2(0, 0);
		g_PreviewBlock[i].rot = 0.0f;
		g_PreviewBlock[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_PreviewBlock[i].texNo = LoadTexture((char*)"data\\texture\\cursor_02.png");

	}

	//�u���b�N�^�C�v�̏����̏�����
	for (int i = 0; i < BLOCKTYPE_MAX; i++)
	{
		blocktype[i].SetType(GetHaveBlock(i));
		//blocktype[i].InitBlocktype();
	}

	for (int i = 0; i < BLOCKTYPE_MAX; i++)
	{
		blocktype[i].ChangeUse(false);

		//-1�̎��̓u���b�N�𔃂��Ă��Ȃ����ߎg�p�t���O��true�ɂ��Ďg���Ȃ�����
		if (blocktype[i].Gettype() == -1)
		{
			blocktype[i].ChangeUse(true);
		}
		
	}
	
	BlockPreview(GetPlayer()->pos);

	return S_OK;
}
//�I������
void UnInitBlock()
{
	for (int i = 0; i < BLOCKTYPE_MAX; i++)
	{
		blocktype[i].UninitBlocktype();
	}
}
//�X�V����
void UpdateBlock()
{
	if (time > 0)
	{
		time -= 1;
	}

	if (FalseExistCheck() == true)
	{
		if (Keyboard_IsKeyDown(KK_RIGHT) && time <= 0 || IsButtonTriggered(0, XINPUT_GAMEPAD_RIGHT_SHOULDER) && time <= 0)
		{//�E
			//�R�����g�����̃��Y�C�̂ŏ����̓��e��������Ȃ��ꍇ���g�܂ŕ����ɗ��Ă��������B�\����Ȃ�������Âꂥ

			//�g���u���b�N��ς���@�z��̈���̃u���b�N���g��
			//�������̃u���b�N�����łɎg�p�ς݂�������g�p�ς݂���Ȃ��Ȃ�܂Ői�߂�
			do
			{
				use_haveblock_number++;
				//255�Ԗڂ܂Œ��ׂ��玟��0�ɖ߂�
				if (use_haveblock_number == BLOCKTYPE_MAX)
				{
					use_haveblock_number = 0;
				}
			} while (blocktype[use_haveblock_number].GetUse() == true);

			////-1�̏ꍇ�̓u���b�N�𔃂��ĂȂ����߁A�擪�ɖ߂�
			//if (blocktype[use_haveblock_number].Gettype() == -1)
			//{
			//	use_haveblock_number = 0;
			//	for (int i = 0; i < BLOCKTYPE_MAX; i++)
			//	{
			//		//�܂��g���ĂȂ��ău���b�N�𔃂��Ă���z��ԍ��Ȃ�悵
			//		if (blocktype[use_haveblock_number].Gettype() != -1 && blocktype[use_haveblock_number].GetUse() == false)
			//		{
			//			break;
			//		}
			//		use_haveblock_number++;
			//	}

			//}
			time = WAIT_TIME;
		}
		else if (Keyboard_IsKeyDown(KK_LEFT) && time <= 0 || IsButtonTriggered(0, XINPUT_GAMEPAD_LEFT_SHOULDER) && time <= 0)
		{//��
			//�g���u���b�N��ς���@�z��̈�O�̃u���b�N���g��
			//�����O�̃u���b�N�����łɎg�p�ς݂�������g�p�ς݂���Ȃ��Ȃ�܂Ŗ߂�
			do
			{
				use_haveblock_number--;
				//0�Ԗڂ���߂�ƈ�Ԍ��ɐi��
				if (use_haveblock_number < 0)
				{
					use_haveblock_number = (BLOCKTYPE_MAX - 1);
				}
			} while (blocktype[use_haveblock_number].GetUse() == true);

			
			time = WAIT_TIME;
		}

		//�O�t���[���ƒl���ς���Ă����ꍇ
		if (use_haveblock_number != before_use_haveblock_number)
		{
			FalsePreviewBlock();
			BlockPreview(GetPlayer()->pos);
		}

		UpdateBlockPreview(GetPlayer()->pos);
	}
	


	////�����_����������u���b�N�̎�ނ̔z����g���؂����ꍇ������x�����_����������
	//if (blocktype[BLOCKTYPE_MAX - 1].GetUse() == true)
	//{
	//	for (int i = 0; i < BLOCKTYPE_MAX; i++)
	//	{
	//		blocktype[i].InitBlocktype();
	//	}
	//}
	

	for (int i = 0; i < MOVE_BLOCK_MAX; i++)
	{
		//�܂��\���̂��g�p���Ă邩�`�F�b�N
		if (g_MoveBlock[i].use == true)
		{
			////���W�̍X�V
			g_MoveBlock[i].pos += g_MoveBlock[i].Speed;
			//��ʉ��܂Œ�������X�s�[�h��0�ɂ��ČŒ肷��
			if (g_MoveBlock[i].pos.y > (SCREEN_HEIGHT - DRAW_SIZE/ 2.0))
			{
				g_MoveBlock[i].Speed.y = 0.0f;
				g_MoveBlock[i].pos.y = (SCREEN_HEIGHT - DRAW_SIZE / 2.0);
			}
		}
	}


	//����̂��̕ϐ��̒l���o���Ă����@
	before_use_haveblock_number = use_haveblock_number;

}
void DrawBlock()
{
	D3DXVECTOR2 basePos = GetBase();

	//�����Ȃ��X�e�[�W�u���b�N
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (g_Block[i].use == true)
		{
			//�e�N�X�`���̃Z�b�g
			GetDeviceContext()->PSSetShaderResources
			(0, 1, GetTexture(g_Block[i].texNo));
			//�X�v���C�g�̕`��
			DrawSpriteColorRotate
			(
			basePos.x + g_Block[i].pos.x,
			basePos.y + g_Block[i].pos.y,
			BASE_DRAW_SIZE,
			DRAW_SIZE,
			g_Block[i].rot,
			g_Block[i].col,
			g_Block[i].Patern,
			3.0f,
			1.0f,
			1
			);
		}
	}
	//�ˏo�����u���b�N
	for (int i = 0; i < MOVE_BLOCK_MAX; i++)
	{
		if (g_MoveBlock[i].use == true)
		{
			//�e�N�X�`���̃Z�b�g
			GetDeviceContext()->PSSetShaderResources
			(0, 1, GetTexture(g_MoveBlock[i].texNo));
			//�X�v���C�g�̕`��

			//type���Ƃɐ���z�u��ς���
			DrawSpriteColorRotate
			(
				basePos.x + g_MoveBlock[i].pos.x,
				basePos.y + g_MoveBlock[i].pos.y,
				DRAW_SIZE,
				DRAW_SIZE,
				g_MoveBlock[i].rot,
				g_MoveBlock[i].col,
				0,
				1.0f,
				1.0f,
				1
			);
		}
	}

	if (FalseExistCheck() == true)
	{
		//�v���r���[�u���b�N
		for (int i = 0; i < PREVIEW_BLOCK_MAX; i++)
		{
			if (g_PreviewBlock[i].use == true)
			{
				//�e�N�X�`���̃Z�b�g
				GetDeviceContext()->PSSetShaderResources
				(0, 1, GetTexture(g_PreviewBlock[i].texNo));
				//�X�v���C�g�̕`��

				//type���Ƃɐ���z�u��ς���
				DrawSpriteColorRotate
				(
					basePos.x + g_PreviewBlock[i].pos.x,
					basePos.y + g_PreviewBlock[i].pos.y,
					DRAW_SIZE,
					DRAW_SIZE,
					0.0f,
					g_PreviewBlock[i].col,
					0,
					1.0f,
					1.0f,
					1
				);
			}
		}
	}
	
}
//�\���̂̐擪�|�C���^��Ԃ��@�F���g����悤��
BLOCK *GetBlock()
{
	return &g_Block[0];
}
MOVE_BLOCK *GetMoveBlock()
{
	return &g_MoveBlock[0];
}
PREVIEW_BLOCK *GetPreviewBlock()
{
	return g_PreviewBlock;
}

void SetMoveBlock()
{
	for (int b = 0; b < previewblocknum; b++)
	{
		//�\���̂�S�Ē��ׂ�
		for (int i = 0; i < MOVE_BLOCK_MAX; i++)
		{
			//�e�������Ƃ���������
			if (g_MoveBlock[i].use == false)
			{
				//type�ɉ�����block�������������
				//�������W
				g_MoveBlock[i].pos = g_PreviewBlock[b].pos;
				//�t���O���g�p���ɂ���
				g_MoveBlock[i].use = true;
				g_MoveBlock[i].Speed.y = GRAV;
				////�T�E���h�Đ�
				//PlaySound(BulletSoundNo, 0);
				//1�������I���I
				break;
			}
		}
	}
	
		
	//�g�p�ς݂ɂ���
	blocktype[use_haveblock_number].ChangeUse(true);

	if (FalseExistCheck() == true)
	{
		//�g�p�ς݂ɂ����ԍ����g���Ȃ��悤�ɔԍ���i�߂�
		do
		{
			use_haveblock_number++;
			//255�Ԗڂ܂Œ��ׂ��玟��0�ɖ߂�
			if (use_haveblock_number == BLOCKTYPE_MAX)
			{
				use_haveblock_number = 0;
			}
		} while (blocktype[use_haveblock_number].GetUse() == true);

		previewblocknum = 0;

		FalsePreviewBlock();
		BlockPreview(GetPlayer()->pos);

	}
	

	
	/*previewblocknum = 0;

	FalsePreviewBlock();
	BlockPreview(GetPlayer()->pos);*/

	
}

//�u���b�N�̐ݒu�v���r���[
void BlockPreview(D3DXVECTOR2 pos)
{
	//�v���r���[��use��true�Ȃ�draw����悤�ɂ�����
	//setblock�̍Ō�őS��false�ɂ���?
	
	//update�Ń{�^���������ꂽ��rot���ω�����
	//rot�ɉ����ău���b�N����]����悤�ȏ�������ꂽ��

	//���̃^�C�v���擾
	nexttype = blocktype[use_haveblock_number].Gettype();
		

	switch (nexttype)
	{
		//�u���b�N�̏��Ԃ̗D��x
		//���S����ԍŏ��@���̂ق����D��@��̂ق����D��

	case 0:
		//������
		//�@�@��
		previewblocknum = 4;
		for (int i = 0; i < previewblocknum; i++)
		{
			g_PreviewBlock[i].use = true;
		}

		g_PreviewBlock[0].pos = pos;

		g_PreviewBlock[1].pos = D3DXVECTOR2(pos.x - SIZE, pos.y);
		g_PreviewBlock[2].pos = D3DXVECTOR2(pos.x + SIZE, pos.y);
		g_PreviewBlock[3].pos = D3DXVECTOR2(pos.x + SIZE, pos.y + SIZE + GRAV);
	
		break;

	case 1:
		//��
		//��
		//��
		//��
		//��

		previewblocknum = 5;
		for (int i = 0; i < previewblocknum; i++)
		{
			g_PreviewBlock[i].use = true;
		}

		g_PreviewBlock[0].pos = pos;

		g_PreviewBlock[1].pos = D3DXVECTOR2(pos.x , pos.y - SIZE * 2 - 5);
		g_PreviewBlock[2].pos = D3DXVECTOR2(pos.x , pos.y - SIZE - GRAV);
		g_PreviewBlock[3].pos = D3DXVECTOR2(pos.x , pos.y + SIZE + GRAV);
		g_PreviewBlock[4].pos = D3DXVECTOR2(pos.x, pos.y + SIZE * 2 + 5);

		break;

	case 2:
		//�@��
		//������
		//�@��

		previewblocknum = 5;
		for (int i = 0; i < previewblocknum; i++)
		{
			g_PreviewBlock[i].use = true;
		}

		g_PreviewBlock[0].pos = pos;

		g_PreviewBlock[1].pos = D3DXVECTOR2(pos.x, pos.y - SIZE - GRAV);
		g_PreviewBlock[2].pos = D3DXVECTOR2(pos.x, pos.y + SIZE + GRAV);
		g_PreviewBlock[3].pos = D3DXVECTOR2(pos.x - SIZE, pos.y);
		g_PreviewBlock[4].pos = D3DXVECTOR2(pos.x + SIZE, pos.y);

		break;

	case 3:
		//����
		//���� //�E�������S�Ƃ���

		previewblocknum = 4;
		for (int i = 0; i < previewblocknum; i++)
		{
			g_PreviewBlock[i].use = true;
		}

		g_PreviewBlock[0].pos = pos;

		g_PreviewBlock[1].pos = D3DXVECTOR2(pos.x, pos.y - SIZE - GRAV);
		g_PreviewBlock[2].pos = D3DXVECTOR2(pos.x - SIZE, pos.y - SIZE - 1);
		g_PreviewBlock[3].pos = D3DXVECTOR2(pos.x - SIZE, pos.y);
		
		break;

	case 4:
		//��
		previewblocknum = 1;
		g_PreviewBlock[0].use = true;

		g_PreviewBlock[0].pos = pos;

		break;

	}
	
}

void UpdateBlockPreview(D3DXVECTOR2 pos)
{
	//���S�̃u���b�N�́��ŏ����Ă���
	//�󒆂Ńu���b�N�ƃu���b�N���Ԃ���Ɠ����蔻�肪�������Ď~�܂邽�߂����W�͏��������Ă�������
	switch (nexttype)
	{
		//�u���b�N�̏��Ԃ̗D��x
		//���S����ԍŏ��@���̂ق����D��@��̂ق����D��

	case 0:
		//������
		//�@�@��

		g_PreviewBlock[0].pos = pos;

		if (g_PreviewBlock[0].rot == 0)
		{
			g_PreviewBlock[1].pos = D3DXVECTOR2(pos.x - SIZE, pos.y);
			g_PreviewBlock[2].pos = D3DXVECTOR2(pos.x + SIZE, pos.y);
			g_PreviewBlock[3].pos = D3DXVECTOR2(pos.x + SIZE, pos.y + SIZE + GRAV);
		}
		//�@��
		//�@��
		//����
		if (g_PreviewBlock[0].rot == 90)
		{
			g_PreviewBlock[1].pos = D3DXVECTOR2(pos.x, pos.y - SIZE - GRAV);
			g_PreviewBlock[2].pos = D3DXVECTOR2(pos.x, pos.y + SIZE + GRAV);
			g_PreviewBlock[3].pos = D3DXVECTOR2(pos.x - SIZE, pos.y + SIZE + GRAV);
		}
		//��
		//������
		if (g_PreviewBlock[0].rot == 180)
		{
			g_PreviewBlock[1].pos = D3DXVECTOR2(pos.x - SIZE, pos.y - SIZE - GRAV);
			g_PreviewBlock[2].pos = D3DXVECTOR2(pos.x - SIZE, pos.y);
			g_PreviewBlock[3].pos = D3DXVECTOR2(pos.x + SIZE, pos.y);

		}
		//����
		//��
		//��
		if (g_PreviewBlock[0].rot == 270)
		{
			g_PreviewBlock[1].pos = D3DXVECTOR2(pos.x, pos.y - SIZE - GRAV);
			g_PreviewBlock[2].pos = D3DXVECTOR2(pos.x, pos.y + SIZE + GRAV);
			g_PreviewBlock[3].pos = D3DXVECTOR2(pos.x + SIZE, pos.y - SIZE - GRAV);
		}
		break;

	case 1:
		//��
		//��
		//��
		//��
		//��

		g_PreviewBlock[0].pos = pos;

		if (g_PreviewBlock[0].rot == 0 || g_PreviewBlock[0].rot == 180)
		{
			g_PreviewBlock[1].pos = D3DXVECTOR2(pos.x, pos.y - SIZE * 2 - 5);
			g_PreviewBlock[2].pos = D3DXVECTOR2(pos.x, pos.y - SIZE - GRAV);
			g_PreviewBlock[3].pos = D3DXVECTOR2(pos.x, pos.y + SIZE + GRAV);
			g_PreviewBlock[4].pos = D3DXVECTOR2(pos.x, pos.y + SIZE * 2 + 5);
		}
		//����������
		else if (g_PreviewBlock[0].rot == 90 || g_PreviewBlock[0].rot == 270)
		{
			g_PreviewBlock[1].pos = D3DXVECTOR2(pos.x - SIZE * 2, pos.y );
			g_PreviewBlock[2].pos = D3DXVECTOR2(pos.x - SIZE, pos.y);
			g_PreviewBlock[3].pos = D3DXVECTOR2(pos.x + SIZE, pos.y );
			g_PreviewBlock[4].pos = D3DXVECTOR2(pos.x + SIZE * 2, pos.y );
		}

		break;

	case 2:
		//�ǂ̊p�x�ł��ꏏ
		g_PreviewBlock[0].pos = pos;

		g_PreviewBlock[1].pos = D3DXVECTOR2(pos.x, pos.y - SIZE - GRAV);
		g_PreviewBlock[2].pos = D3DXVECTOR2(pos.x, pos.y + SIZE + GRAV);
		g_PreviewBlock[3].pos = D3DXVECTOR2(pos.x - SIZE, pos.y);
		g_PreviewBlock[4].pos = D3DXVECTOR2(pos.x + SIZE, pos.y);
		
		break;

	case 3:	
		//����
		//����

		//��]���Ă��`�͕ς��Ȃ����E�������S�̂��߉�]�͂���
		g_PreviewBlock[0].pos = pos;

		if (g_PreviewBlock[0].rot == 0)
		{
			g_PreviewBlock[1].pos = D3DXVECTOR2(pos.x, pos.y - SIZE - GRAV);
			g_PreviewBlock[2].pos = D3DXVECTOR2(pos.x - SIZE, pos.y - SIZE - GRAV);
			g_PreviewBlock[3].pos = D3DXVECTOR2(pos.x - SIZE, pos.y);
		}
		//����
		//����
		if (g_PreviewBlock[0].rot == 90)
		{
			g_PreviewBlock[1].pos = D3DXVECTOR2(pos.x, pos.y - SIZE - GRAV);
			g_PreviewBlock[2].pos = D3DXVECTOR2(pos.x + SIZE, pos.y - SIZE - GRAV);
			g_PreviewBlock[3].pos = D3DXVECTOR2(pos.x + SIZE, pos.y );
		}
		//����
		//����
		if (g_PreviewBlock[0].rot == 180)
		{
			g_PreviewBlock[1].pos = D3DXVECTOR2(pos.x , pos.y + SIZE + GRAV);
			g_PreviewBlock[2].pos = D3DXVECTOR2(pos.x + SIZE, pos.y);
			g_PreviewBlock[3].pos = D3DXVECTOR2(pos.x + SIZE, pos.y + SIZE + GRAV);

		}
		//����
		//����
		if (g_PreviewBlock[0].rot == 270)
		{
			g_PreviewBlock[1].pos = D3DXVECTOR2(pos.x, pos.y + SIZE + GRAV);
			g_PreviewBlock[2].pos = D3DXVECTOR2(pos.x - SIZE, pos.y );
			g_PreviewBlock[3].pos = D3DXVECTOR2(pos.x - SIZE, pos.y + SIZE + GRAV);
		}
		break;
	
	case 4:
		//���@	�ǂ̊p�x�ł��ꏏ

		g_PreviewBlock[0].pos = pos;
		break;
	}
}


//�S���̎g�p�t���O��false�ɂ���
void FalsePreviewBlock()
{
	for (int i = 0; i < PREVIEW_BLOCK_MAX; i++)
	{
		g_PreviewBlock[i].use = false;
		g_PreviewBlock[i].rot = 0;
	}
}

//false�����݂��邩�ǂ����`�F�b�N����	�S��true�̎��͔������u���b�N���g���؂����Ƃ������ƂɂȂ�
bool FalseExistCheck()
{
	for (int i = 0; i < BLOCKTYPE_MAX; i++)
	{
		if (blocktype[i].GetUse() == false)
		{
			return true;
		}
	}

	return false;
}

void InitStage11()
{
	//����Ɋւ��Ă�,�U�[�b�ƕ��ׂ銴���ɂ���
//DRAW_SIZE������������}�X������Ă���
//�傫�Ȍ`���Ƃɕ�����Ƃ킩��₷������
	g_Block[0].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 0, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[1].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 1, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[2].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 2, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[3].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 3, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[4].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 4, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[5].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 5, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[6].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 6, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[7].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 7, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[8].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 7, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[9].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 7, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[10].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 7, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[11].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[12].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[13].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[14].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[15].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_Block[16].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 9, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[17].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 10, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[18].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 11, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[19].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[20].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 14, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[21].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 0);
}
