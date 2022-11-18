#include "main.h"
#include "block.h"
#include "texture.h"
#include "sprite.h"
#include "camera.h"

//プロトタイプ宣言
void InitStage11();
//==========================================
//グローバル変数
//==========================================

//地面や足場の判定に使う
static BLOCK g_Block[BLOCK_MAX];

HRESULT InitBlock()
{
	//BLOCK構造体の初期化
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		//テクスチャロード 画像の名前を入れよう
		//ブロックによってテクスチャの変更
		//21~29
		//33~44は表面では無い方へ変更
		if (i >= 21 && i <= 29)
		{
			g_Block[i].texNo = LoadTexture((char*)"data\\texture\\under_soil_block.png");
		}
		else if (i >= 33 && i <= 44)
		{
			g_Block[i].texNo = LoadTexture((char*)"data\\texture\\under_soil_block.png");
		}
		else
		{
			g_Block[i].texNo = LoadTexture((char*)"data\\texture\\grass_block.png");
		}
	}
	//足場ブロックの設置.一番最後に設定
	InitStage11();
	//
	return S_OK;
}
//終了処理
void UnInitBlock()
{

}
//更新処理
void UpdateBlock()
{

}
//描画処理
void DrawBlock()
{
	D3DXVECTOR2 basePos = GetBase();

	//動かないステージブロック
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (g_Block[i].use == true)
		{
			//テクスチャのセット
			GetDeviceContext()->PSSetShaderResources
			(0, 1, GetTexture(g_Block[i].texNo));
			//スプライトの描画
			DrawSpriteColorRotate
			(
			basePos.x + g_Block[i].pos.x,
			basePos.y + g_Block[i].pos.y,
			DRAW_SIZE,
			DRAW_SIZE,
			g_Block[i].rot,
			g_Block[i].col,
			g_Block[i].Patern,
			1.0f,
			1.0f,
			1
			);
		}
	}	
}
//構造体の先頭ポインタを返す　皆が使えるように
BLOCK *GetBlock()
{
	return &g_Block[0];
}

void InitStage11()
{
	//足場に関しては,ザーッと並べる感じにする
	//DRAW_SIZEをかけた分一マスずつずれていく
	//大きな形ごとに分けるとわかりやすいかも
	g_Block[0].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 0, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[1].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 1, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[2].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 2, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[3].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 3, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[4].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 4, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[5].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 5, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[6].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 6, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[7].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 7, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[8].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[9].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 9, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[10].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 10, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[11].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 11, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[12].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 12, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[13].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[14].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 14, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[15].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[16].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 16, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[17].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 17, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[18].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 18, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[19].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 19, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[20].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 20, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[21].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 21, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[22].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 22, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[23].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[24].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 21, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[25].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 22, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[26].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[27].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 21, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[28].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 22, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[29].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 2);

	g_Block[30].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 21, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[31].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 22, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[32].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[33].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 24, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[34].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 25, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[35].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 26, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[36].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 24, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[37].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 25, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[38].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 26, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[39].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 24, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[40].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 25, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[41].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 26, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[42].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 24, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[43].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 25, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[44].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 26, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[45].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 24, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[46].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 25, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[47].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 26, DEFO_SIZE_Y - DRAW_SIZE * 4);


	g_Block[48].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 27, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[49].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 28, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[50].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 29, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[51].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 30, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[52].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 31, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[53].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 32, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[54].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 33, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[55].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 34, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[56].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 35, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[57].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 39, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[58].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 40, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[59].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 41, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[60].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 42, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[61].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 43, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[62].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 44, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[63].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[64].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 46, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[65].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 47, DEFO_SIZE_Y - DRAW_SIZE * 0);
}
