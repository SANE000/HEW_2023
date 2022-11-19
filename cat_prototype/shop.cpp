

#include "shop.h"
#include "texture.h"
#include "inputx.h"
#include "keyboard.h"
#include "scene.h"
#include "sprite.h"

//�}�b�v����悤��block��polygon�C���N���[�h����@init draw�����Ăяo��
#include "block.h"
#include "polygon.h"
#include "etcUI.h"


//==========================================
//�O���[�o���ϐ�
//==========================================
//�L�[�{�[�h���͗p�A�����͖h�~����
static int time = 0;
//����
int g_money;
MONEY money[MONEY_MAX];

int haveblock[HAVE_BLOCK_MAX];

SHOP_CURSOR cursor;

SHOP_ITEM g_item[SHOP_ITEM_MAX];

//�}�b�v������{�^���������Ă��邩�ǂ���
bool map_flag;
bool confirmation_flag;
bool start_flag;

int shopconfirmtexNo;
int startconfirmtexNo;

HRESULT InitShop()
{
	InitBlock();
	InitPolygon();
	InitEtc();

	shopconfirmtexNo = LoadTexture((char*)"data\\texture\\shop_confirm.png");;
	startconfirmtexNo = LoadTexture((char*)"data\\texture\\start_confirm.png");;

	//����������
	g_money = 100;

	map_flag = false;
	confirmation_flag = false;
	start_flag = false;

	//�������u���b�N��ێ�����z����������@-1�̏ꍇ�g���Ă��Ȃ�
	for (int i = 0; i < HAVE_BLOCK_MAX; i++)
	{
		haveblock[i] = -1;
	}

	//�J�[�\��������
	cursor.pos.x = CURSOR_X_00;
	cursor.pos.y = CURSOR_Y_00;
	cursor.w = CURSOR_SIZE_W;
	cursor.h = CURSOR_SIZE_H;
	cursor.texNo = LoadTexture((char*)"data\\texture\\shop_cursor.png");

	//�V���b�v�A�C�e��������(�z�u)
	for (int i = 0; i < SHOP_ITEM_MAX; i++)
	{
		g_item[i].pos.x = CURSOR_X_00 + (CURSOR_MOVE_X * (i % 5));

		if (i >= 0 && i <= 4)
		{
			g_item[i].pos.y = CURSOR_Y_00;
		}
		else if (i >= 5 && i <= 9)
		{
			g_item[i].pos.y = CURSOR_Y_00 + CURSOR_MOVE_Y;
		}
		else if (i >= 10 && i <= 14)
		{
			g_item[i].pos.y = CURSOR_Y_00 +( CURSOR_MOVE_Y * 2 );
		}
		
		g_item[i].w = SHOP_ITEM_SIZE_W;
		g_item[i].h = SHOP_ITEM_SIZE_H;

		//�l�i�͂�������S��10
		g_item[i].price = 10;

		g_item[i].texNo = LoadTexture((char*)"data\\texture\\soil_block.png");
	}

	g_item[0].texNo = LoadTexture((char*)"data\\texture\\shop_block_00.png");
	g_item[1].texNo = LoadTexture((char*)"data\\texture\\shop_block_01.png");
	g_item[2].texNo = LoadTexture((char*)"data\\texture\\shop_block_02.png");
	g_item[3].texNo = LoadTexture((char*)"data\\texture\\shop_block_03.png");
	g_item[4].texNo = LoadTexture((char*)"data\\texture\\shop_block_04.png");

	for (int i = 0; i < MONEY_MAX; i++)
	{
		money[i].pos.x = MONEY_SIZE_W + (i * MONEY_SIZE_W);
		money[i].pos.y = MONEY_SIZE_H;
		money[i].w = MONEY_SIZE_W;
		money[i].h = MONEY_SIZE_H;
		money[i].texNo = LoadTexture((char*)"data\\texture\\time.png");
		money[i].patern = 0;
	}

	return S_OK;
}

void UninitShop()
{


}

void UpdateShop()
{
	//���t���[�����炷
	if (time > 0)
	{
		time -= 1;
	}
	//�}�b�v�����{�^��
	if (Keyboard_IsKeyDown(KK_M) && time <= 0 || IsButtonTriggered(0, XINPUT_GAMEPAD_START) && time<=0 )
	{
		if (map_flag == false)
		{
			map_flag = true;
		}
		else if (map_flag == true)
		{
			//������x�����ă}�b�v�I��
			map_flag = false;
		}
		//���ԃ��Z�b�g
		time = WAIT_TIME;
	}


	//�}�b�v���Ă�Ƃ��͏������s��Ȃ�
	if (map_flag == false)
	{
		//�m�F���b�Z�[�W���o�Ă�Ƃ��͂ق��̑��삪�ł��Ȃ��悤�ɂ���

		//�w���̍ۊm�F���b�Z�[�W������@y/n����͂ōw����I��
		if (confirmation_flag == true)
		{
			//�w��
			if (Keyboard_IsKeyDown(KK_Y) && time <= 0 ||IsButtonTriggered(0, XINPUT_GAMEPAD_B) && time <= 0)
			{
				
				Buyblock();

				confirmation_flag = false;
				time = WAIT_TIME;
			}
			//�w�����Ȃ�
			else if (Keyboard_IsKeyDown(KK_N) && time <= 0 || IsButtonTriggered(0, XINPUT_GAMEPAD_A) && time <= 0)
			{
				confirmation_flag = false;
				time = WAIT_TIME;
			}
		}
		//�X�^�[�g�̍ۂ̊m�F���b�Z�[�W
		else if(start_flag == true)
		{
			//�n�߂�
			if (Keyboard_IsKeyDown(KK_Y) && time <= 0 || IsButtonTriggered(0, XINPUT_GAMEPAD_B) && time <= 0)
			{
				start_flag = false;
				SetScene(SCENE_GAME);
				time = WAIT_TIME;
				
			}
			//�n�߂Ȃ�
			else if (Keyboard_IsKeyDown(KK_N) && time <= 0 || IsButtonTriggered(0, XINPUT_GAMEPAD_A) && time <= 0)
			{
				start_flag = false;
				time = WAIT_TIME;
			}
			
		}
		else
		{
			//�J�[�\������@�Ƃ肠����
			if (Keyboard_IsKeyDown(KK_RIGHT) && time <= 0 || GetThumbLeftX(0) > 0 && time <= 0)
			{//�E
				if (cursor.pos.x != CURSOR_X_04)
				{
					cursor.pos.x += CURSOR_MOVE_X;
				}
				time = WAIT_TIME;

			}
			else if (Keyboard_IsKeyDown(KK_LEFT) && time <= 0 || GetThumbLeftX(0) < 0 && time <= 0)
			{//��
				if (cursor.pos.x != CURSOR_X_00)
				{
					cursor.pos.x -= CURSOR_MOVE_X;
				}
				time = WAIT_TIME;
			}
			else if (Keyboard_IsKeyDown(KK_DOWN) && time <= 0 || GetThumbLeftY(0) < 0 && time <= 0)
			{//��
				if (cursor.pos.y != CURSOR_Y_02)
				{
					cursor.pos.y += CURSOR_MOVE_Y;
				}
				time = WAIT_TIME;
			}
			else if (Keyboard_IsKeyDown(KK_UP) && time <= 0 || GetThumbLeftY(0) > 0 && time <= 0)
			{//��
				if (cursor.pos.y != CURSOR_Y_00)
				{
					cursor.pos.y -= CURSOR_MOVE_Y;
				}
				time = WAIT_TIME;
			}


			//�w���{�^���@->�@�m�F�{�^��

			if (Keyboard_IsKeyDown(KK_SPACE) && time <= 0 || IsButtonTriggered(0, XINPUT_GAMEPAD_B) && time <= 0)
			{
				//�w���m�F
				confirmation_flag = true;
				time = WAIT_TIME;
			}

			if (Keyboard_IsKeyDown(KK_S) && time <= 0 || IsButtonTriggered(0, XINPUT_GAMEPAD_A) && time <= 0)
			{
				//�X�^�[�g�m�F
				start_flag = true;
				time = WAIT_TIME;

			}

		}

		for (int i = 0; i < MONEY_MAX; i++)
		{
			if (i == 0)
			{
				money[i].patern = (g_money / 100) % 10;
			}
			else  if (i == 1)
			{
				money[i].patern = (g_money / 10) % 10;
			}
			else if (i == 2)
			{
				money[i].patern = g_money % 10;
			}
		}

	}
	//�}�b�v������Ƃ�����������
	if (map_flag == true)
	{
		UpdateEtc();
		UpdateBlock();
	}
		
}

void DrawShop()
{
	//�}�b�v����{�^����������}�b�v��draw���Ă�ŕ\������
	if (map_flag == true)
	{
		DrawPolygon();
		DrawBlock();
		DrawEtc();
	}
	else
	{
		//�����`��
		for (int i = 0; i < MONEY_MAX; i++)
		{
			GetDeviceContext()->PSSetShaderResources
			(0, 1, GetTexture(money[i].texNo));

			//�X�v���C�g�̕`��
			DrawSpriteColorRotate(
				money[i].pos.x,
				money[i].pos.y,
				money[i].w,
				money[i].h,
				0,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				money[i].patern,
				1.0f / 10.0f,//��
				1.0f,//�c
				10//���̃p�^�[������
			);
		}


		//�A�C�e���`��
		//�e�N�X�`���̃Z�b�g
		for (int i = 0; i < SHOP_ITEM_MAX; i++)
		{
			GetDeviceContext()->PSSetShaderResources
			(0, 1, GetTexture(g_item[i].texNo));

			//�X�v���C�g�̕`��
			DrawSpriteColorRotate(
				g_item[i].pos.x,
				g_item[i].pos.y,
				g_item[i].w,
				g_item[i].h,
				0,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				0,
				1.0f,//��
				1.0f,//�c
				1//���̃p�^�[������
			);
		}
	
		//�J�[�\���`��
		GetDeviceContext()->PSSetShaderResources
		(0, 1, GetTexture(cursor.texNo));

		//�X�v���C�g�̕`��
		DrawSpriteColorRotate(
			cursor.pos.x,
			cursor.pos.y,
			cursor.w,
			cursor.h,
			0,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			0,
			1.0f,//��
			1.0f,//�c
			1//���̃p�^�[������
		);

		//�X�^�[�g�m�F�t���O��true��������
		if (start_flag == true)
		{
			GetDeviceContext()->PSSetShaderResources
			(0, 1, GetTexture(startconfirmtexNo));

			//�X�v���C�g�̕`��
			DrawSpriteColorRotate(
				CONFIRM_WINDOW_X,
				CONFIRM_WINDOW_Y,
				CONFIRM_WINDOW_SIZE_W,
				CONFIRM_WINDOW_SIZE_H,
				0,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				0,
				1.0f,//��
				1.0f,//�c
				1//���̃p�^�[������
			);

		}
		//�w���m�F�t���O��true��������
		else if (confirmation_flag == true)
		{
			GetDeviceContext()->PSSetShaderResources
			(0, 1, GetTexture(shopconfirmtexNo));

			//�X�v���C�g�̕`��
			DrawSpriteColorRotate(
				CONFIRM_WINDOW_X,
				CONFIRM_WINDOW_Y,
				CONFIRM_WINDOW_SIZE_W,
				CONFIRM_WINDOW_SIZE_H,
				0,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				0,
				1.0f,//��
				1.0f,//�c
				1//���̃p�^�[������
			);

		}

	}



}

//�u���b�N�w���{�^�����������ۂǂ̃u���b�N�����ׂĔz��ɓ����
void Buyblock()
{
	int blocktype = -1;
	
	if (cursor.pos.y == CURSOR_Y_00)
	{
		if (cursor.pos.x == CURSOR_X_00)
		{
			blocktype = 0;
		}
		else if (cursor.pos.x == CURSOR_X_01)
		{
			blocktype = 1;
		}
		else if (cursor.pos.x == CURSOR_X_02)
		{
			blocktype = 2;
		}
		else if (cursor.pos.x == CURSOR_X_03)
		{
			blocktype = 3;
		}
		else if (cursor.pos.x == CURSOR_X_04)
		{
			blocktype = 4;
		}
	}
	else if (cursor.pos.y == CURSOR_Y_01)
	{
		if (cursor.pos.x == CURSOR_X_00)
		{
			blocktype = 5;
		}
		else if (cursor.pos.x == CURSOR_X_01)
		{
			blocktype = 6;
		}
		else if (cursor.pos.x == CURSOR_X_02)
		{
			blocktype = 7;
		}
		else if (cursor.pos.x == CURSOR_X_03)
		{
			blocktype = 8;
		}
		else if (cursor.pos.x == CURSOR_X_04)
		{
			blocktype = 9;
		}
	}
	else if (cursor.pos.y == CURSOR_Y_02)
	{
		if (cursor.pos.x == CURSOR_X_00)
		{
			blocktype = 10;
		}
		else if (cursor.pos.x == CURSOR_X_01)
		{
			blocktype = 11;
		}
		else if (cursor.pos.x == CURSOR_X_02)
		{
			blocktype = 12;
		}
		else if (cursor.pos.x == CURSOR_X_03)
		{
			blocktype = 13;
		}
		else if (cursor.pos.x == CURSOR_X_04)
		{
			blocktype = 14;
		}
	}
	
	//����������Ă��甃��
	if (g_money >= g_item[blocktype].price)
	{
		for (int i = 0; i < HAVE_BLOCK_MAX; i++)
		{
			//�g���ĂȂ��Ƃ����T��
			if (haveblock[i] == -1)
			{
				haveblock[i] = blocktype;
				g_money -= g_item[blocktype].price;
				break;
			}
		}
	}
	

}

int GetHaveBlock(int i)
{
	return haveblock[i];
}
//�}�b�v�{�^���������ꂽ���Ƃ�Ԃ��֐�
bool WatchMapFlag()
{
	return map_flag;
}
