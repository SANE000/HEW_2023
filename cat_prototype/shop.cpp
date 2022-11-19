

#include "shop.h"
#include "texture.h"
#include "inputx.h"
#include "keyboard.h"
#include "scene.h"
#include "sprite.h"

//マップ見るようにblockとpolygonインクルードする　init drawだけ呼び出す
#include "block.h"
#include "polygon.h"
#include "etcUI.h"


//==========================================
//グローバル変数
//==========================================
//キーボード入力用連続入力防止時間
static int time = 0;
//お金
int g_money;
MONEY money[MONEY_MAX];

int haveblock[HAVE_BLOCK_MAX];

SHOP_CURSOR cursor;

SHOP_ITEM g_item[SHOP_ITEM_MAX];

//マップを見るボタンを押しているかどうか
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

	//初期所持金
	g_money = 100;

	map_flag = false;
	confirmation_flag = false;
	start_flag = false;

	//買ったブロックを保持する配列を初期化　-1の場合使っていない
	for (int i = 0; i < HAVE_BLOCK_MAX; i++)
	{
		haveblock[i] = -1;
	}

	//カーソル初期化
	cursor.pos.x = CURSOR_X_00;
	cursor.pos.y = CURSOR_Y_00;
	cursor.w = CURSOR_SIZE_W;
	cursor.h = CURSOR_SIZE_H;
	cursor.texNo = LoadTexture((char*)"data\\texture\\shop_cursor.png");

	//ショップアイテム初期化(配置)
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

		//値段はいったん全部10
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
	//毎フレーム減らす
	if (time > 0)
	{
		time -= 1;
	}
	//マップ見れるボタン
	if (Keyboard_IsKeyDown(KK_M) && time <= 0 || IsButtonTriggered(0, XINPUT_GAMEPAD_START) && time<=0 )
	{
		if (map_flag == false)
		{
			map_flag = true;
		}
		else if (map_flag == true)
		{
			//もう一度押してマップ終了
			map_flag = false;
		}
		//時間リセット
		time = WAIT_TIME;
	}


	//マップ見てるときは処理を行わない
	if (map_flag == false)
	{
		//確認メッセージが出てるときはほかの操作ができないようにする

		//購入の際確認メッセージを入れる　y/nを入力で購入を選ぶ
		if (confirmation_flag == true)
		{
			//購入
			if (Keyboard_IsKeyDown(KK_Y) && time <= 0 ||IsButtonTriggered(0, XINPUT_GAMEPAD_B) && time <= 0)
			{
				
				Buyblock();

				confirmation_flag = false;
				time = WAIT_TIME;
			}
			//購入しない
			else if (Keyboard_IsKeyDown(KK_N) && time <= 0 || IsButtonTriggered(0, XINPUT_GAMEPAD_A) && time <= 0)
			{
				confirmation_flag = false;
				time = WAIT_TIME;
			}
		}
		//スタートの際の確認メッセージ
		else if(start_flag == true)
		{
			//始める
			if (Keyboard_IsKeyDown(KK_Y) && time <= 0 || IsButtonTriggered(0, XINPUT_GAMEPAD_B) && time <= 0)
			{
				start_flag = false;
				SetScene(SCENE_GAME);
				time = WAIT_TIME;
				
			}
			//始めない
			else if (Keyboard_IsKeyDown(KK_N) && time <= 0 || IsButtonTriggered(0, XINPUT_GAMEPAD_A) && time <= 0)
			{
				start_flag = false;
				time = WAIT_TIME;
			}
			
		}
		else
		{
			//カーソル操作　とりあえず
			if (Keyboard_IsKeyDown(KK_RIGHT) && time <= 0 || GetThumbLeftX(0) > 0 && time <= 0)
			{//右
				if (cursor.pos.x != CURSOR_X_04)
				{
					cursor.pos.x += CURSOR_MOVE_X;
				}
				time = WAIT_TIME;

			}
			else if (Keyboard_IsKeyDown(KK_LEFT) && time <= 0 || GetThumbLeftX(0) < 0 && time <= 0)
			{//左
				if (cursor.pos.x != CURSOR_X_00)
				{
					cursor.pos.x -= CURSOR_MOVE_X;
				}
				time = WAIT_TIME;
			}
			else if (Keyboard_IsKeyDown(KK_DOWN) && time <= 0 || GetThumbLeftY(0) < 0 && time <= 0)
			{//下
				if (cursor.pos.y != CURSOR_Y_02)
				{
					cursor.pos.y += CURSOR_MOVE_Y;
				}
				time = WAIT_TIME;
			}
			else if (Keyboard_IsKeyDown(KK_UP) && time <= 0 || GetThumbLeftY(0) > 0 && time <= 0)
			{//上
				if (cursor.pos.y != CURSOR_Y_00)
				{
					cursor.pos.y -= CURSOR_MOVE_Y;
				}
				time = WAIT_TIME;
			}


			//購入ボタン　->　確認ボタン

			if (Keyboard_IsKeyDown(KK_SPACE) && time <= 0 || IsButtonTriggered(0, XINPUT_GAMEPAD_B) && time <= 0)
			{
				//購入確認
				confirmation_flag = true;
				time = WAIT_TIME;
			}

			if (Keyboard_IsKeyDown(KK_S) && time <= 0 || IsButtonTriggered(0, XINPUT_GAMEPAD_A) && time <= 0)
			{
				//スタート確認
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
	//マップを見るときだけ動かす
	if (map_flag == true)
	{
		UpdateEtc();
		UpdateBlock();
	}
		
}

void DrawShop()
{
	//マップ見るボタン押したらマップのdrawを呼んで表示する
	if (map_flag == true)
	{
		DrawPolygon();
		DrawBlock();
		DrawEtc();
	}
	else
	{
		//お金描画
		for (int i = 0; i < MONEY_MAX; i++)
		{
			GetDeviceContext()->PSSetShaderResources
			(0, 1, GetTexture(money[i].texNo));

			//スプライトの描画
			DrawSpriteColorRotate(
				money[i].pos.x,
				money[i].pos.y,
				money[i].w,
				money[i].h,
				0,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				money[i].patern,
				1.0f / 10.0f,//横
				1.0f,//縦
				10//横のパターン枚数
			);
		}


		//アイテム描画
		//テクスチャのセット
		for (int i = 0; i < SHOP_ITEM_MAX; i++)
		{
			GetDeviceContext()->PSSetShaderResources
			(0, 1, GetTexture(g_item[i].texNo));

			//スプライトの描画
			DrawSpriteColorRotate(
				g_item[i].pos.x,
				g_item[i].pos.y,
				g_item[i].w,
				g_item[i].h,
				0,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				0,
				1.0f,//横
				1.0f,//縦
				1//横のパターン枚数
			);
		}
	
		//カーソル描画
		GetDeviceContext()->PSSetShaderResources
		(0, 1, GetTexture(cursor.texNo));

		//スプライトの描画
		DrawSpriteColorRotate(
			cursor.pos.x,
			cursor.pos.y,
			cursor.w,
			cursor.h,
			0,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			0,
			1.0f,//横
			1.0f,//縦
			1//横のパターン枚数
		);

		//スタート確認フラグがtrueだったら
		if (start_flag == true)
		{
			GetDeviceContext()->PSSetShaderResources
			(0, 1, GetTexture(startconfirmtexNo));

			//スプライトの描画
			DrawSpriteColorRotate(
				CONFIRM_WINDOW_X,
				CONFIRM_WINDOW_Y,
				CONFIRM_WINDOW_SIZE_W,
				CONFIRM_WINDOW_SIZE_H,
				0,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				0,
				1.0f,//横
				1.0f,//縦
				1//横のパターン枚数
			);

		}
		//購入確認フラグがtrueだったら
		else if (confirmation_flag == true)
		{
			GetDeviceContext()->PSSetShaderResources
			(0, 1, GetTexture(shopconfirmtexNo));

			//スプライトの描画
			DrawSpriteColorRotate(
				CONFIRM_WINDOW_X,
				CONFIRM_WINDOW_Y,
				CONFIRM_WINDOW_SIZE_W,
				CONFIRM_WINDOW_SIZE_H,
				0,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				0,
				1.0f,//横
				1.0f,//縦
				1//横のパターン枚数
			);

		}

	}



}

//ブロック購入ボタンを押した際どのブロックか調べて配列に入れる
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
	
	//お金が足りてたら買う
	if (g_money >= g_item[blocktype].price)
	{
		for (int i = 0; i < HAVE_BLOCK_MAX; i++)
		{
			//使ってないところを探す
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
//マップボタンが押されたことを返す関数
bool WatchMapFlag()
{
	return map_flag;
}
