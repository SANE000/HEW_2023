
#pragma once

#include "main.h"


//==========================================
//マクロ定義
//==========================================
#define CURSOR_MOVE_X (192)
#define CURSOR_MOVE_Y (144)


#define	CURSOR_X_00	(96)
#define	CURSOR_X_01 (CURSOR_X_00 + CURSOR_MOVE_X)
#define CURSOR_X_02	(CURSOR_X_01 + CURSOR_MOVE_X)
#define CURSOR_X_03	(CURSOR_X_02 + CURSOR_MOVE_X)
#define CURSOR_X_04	(CURSOR_X_03 + CURSOR_MOVE_X)


		
#define CURSOR_Y_00	(144)
#define CURSOR_Y_01	(CURSOR_Y_00 + CURSOR_MOVE_Y)
#define CURSOR_Y_02	(CURSOR_Y_01 + CURSOR_MOVE_Y)
#define CURSOR_Y_03	()
#define CURSOR_Y_04	()


#define CURSOR_SIZE_W	(110)
#define CURSOR_SIZE_H	(110)

//買ったブロックを保持する配列の最大数　こんなにはきっといらない
#define HAVE_BLOCK_MAX	(30)

//ショップのアイテムの最大数
#define SHOP_ITEM_MAX	(10)

#define SHOP_ITEM_SIZE_W (96)
#define SHOP_ITEM_SIZE_H (96)

//お金の描画サイズ
#define MONEY_SIZE_W	(48)
#define MONEY_SIZE_H	(48)

//お金の桁数
#define MONEY_MAX		(3)
//ショップの飾り
#define SHOP_ETC_MAX	(3)


//確認メッセージウィンドウのサイズや位置
#define CONFIRM_WINDOW_SIZE_W	(400) //縦横比5:2
#define CONFIRM_WINDOW_SIZE_H	(160)

#define CONFIRM_WINDOW_X	(480)
#define CONFIRM_WINDOW_Y	(270)

//構造体定義
struct SHOP_CURSOR
{
	D3DXVECTOR2 pos;
	float w, h;
	int texNo;
};

struct SHOP_ITEM
{
	D3DXVECTOR2 pos;
	float w, h;
	int texNo;
	int price;
};

struct SHOP_ETC
{
	D3DXVECTOR2 pos;
	float w, h;
	int	texNo;
	float patern = 0.0f;
};

struct MONEY
{
	D3DXVECTOR2 pos;
	float w, h;
	int texNo;
	int patern;
};

//==========================================
//プロトタイプ宣言
//==========================================
HRESULT InitShop();
void UninitShop();
void UpdateShop();
void DrawShop();

void Buyblock();

int GetHaveBlock(int i);
//マップボタンが押されたことを返す
bool WatchMapFlag();

