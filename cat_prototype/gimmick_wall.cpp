
#include "main.h"
#include "gimmick_wall.h"
#include "block.h"
#include "texture.h"
#include "sprite.h"
#include "etcUI.h"
#include "shop.h"
#include "texture.h"
#include "sprite.h"
#include "camera.h"
#include "gimmick_wall.h"
#include "stageselect.h"
#include "result.h"

//==========================================
//
//==========================================

//g_wallのコリジョン！！！！！！！！

//==========================================
//グローバル変数
//==========================================
//壁の配列変数
G_WALL g_wall[WALL_MAX];


//現在のステージを入れる



//==========================================
//プロトタイプ宣言
//==========================================
void InitWall_12();
void InitWall_13();


HRESULT InitGimmickWall()
{
	int field_gw = SetField();
	int stage_gw = SetStage();
    int clear_gw = SetClear();

	for (int i = 0; i < WALL_MAX; i++)
	{
		g_wall[i].use = false;
		g_wall[i].texNo = LoadTexture((char*)"data\\texture\\block.png");
		g_wall[i].Patern = 7.0f;

	}

	switch (field_gw)
	{
		//1-1	
	case 0:
		if (stage_gw == 0)
		{

		}
		else if (stage_gw == 1 && clear_gw >= 1)
		{
			InitWall_12();

		}
		else if (stage_gw == 2 && clear_gw >= 2)
		{
			InitWall_13();
		}

		break;

		//1-2
	case 1:
		if (stage_gw == 0)
		{

		}
		else if (stage_gw == 1)
		{

		}
		else if (stage_gw == 2)
		{

		}

		break;

	case 2:

		if (stage_gw == 0)
		{

		}
		else if (stage_gw == 1)
		{

		}
		else if (stage_gw == 2)
		{

		}
		break;

	case 3:
		if (stage_gw == 0)
		{

		}
		else if (stage_gw == 1)
		{

		}
		else if (stage_gw == 2)
		{

		}

		break;

	case 4:
		if (stage_gw == 0)
		{

		}
		else if (stage_gw == 1)
		{

		}
		else if (stage_gw == 2)
		{

		}

		break;

	case 5:
		if (stage_gw == 0)
		{

		}
		else if (stage_gw == 1)
		{

		}
		else if (stage_gw == 2)
		{

		}
		break;


	}
	return S_OK;
}

void UninitGimmickWall()
{
	int field_gw = SetField();
	int stage_gw = SetStage();
	int clear_gw = SetClear();

	switch (field_gw)
	{
		//1-1	
	case 0:
		if (stage_gw == 0)
		{

		}
		else if (stage_gw == 1 && clear_gw >= 1)
		{
			for (int i = 0; i < WALL_MAX; i++)
			{
				if (g_wall[i].use == false)
				{
					continue;
				}
				//trueのやつだけ設定する
				g_wall[i].use = false;
			}
		}
		else if (stage_gw == 2 && clear_gw >= 2)
		{
			for (int i = 0; i < WALL_MAX; i++)
			{
				if (g_wall[i].use == false)
				{
					continue;
				}
				//trueのやつだけ設定する
				g_wall[i].use = false;
			}
		}

		break;

		//1-2
	case 1:
		if (stage_gw == 0)
		{

		}
		else if (stage_gw == 1)
		{

		}
		else if (stage_gw == 2)
		{

		}

		break;

	case 2:

		if (stage_gw == 0)
		{

		}
		else if (stage_gw == 1)
		{

		}
		else if (stage_gw == 2)
		{

		}
		break;

	case 3:
		if (stage_gw == 0)
		{

		}
		else if (stage_gw == 1)
		{

		}
		else if (stage_gw == 2)
		{

		}

		break;

	case 4:
		if (stage_gw == 0)
		{

		}
		else if (stage_gw == 1)
		{

		}
		else if (stage_gw == 2)
		{

		}

		break;

	case 5:
		if (stage_gw == 0)
		{

		}
		else if (stage_gw == 1)
		{

		}
		else if (stage_gw == 2)
		{

		}
		break;


	}
}

void UpdateGimmickWall()
{
	BLOCK* pb = GetBlock();


	int field_gw = SetField();
	int stage_gw = SetStage();
	int clear_gw = SetClear();

	switch (field_gw)
	{
		//1-1	
	case 0:
		if (stage_gw == 0)
		{

		}
		else if (stage_gw == 1 && clear_gw >= 1)
		{
			//ボタンが押されたら全部falseにする
			if (pb[54].button == false)
			{
				for (int i = 0; i < 8; i++)
				{
					g_wall[i].use = false;
				}
			}

		}
		else if (stage_gw == 2 && clear_gw >= 2)
		{
			//ボタンが押されたら全部falseにする
			if (pb[112].button == false)
			{
				for (int i = 0; i < 18; i++)
				{
					g_wall[i].use = false;
				}
			}
		}

		break;

		//1-2
	case 1:
		if (stage_gw == 0)
		{

		}
		else if (stage_gw == 1)
		{

		}
		else if (stage_gw == 2)
		{

		}

		break;

	case 2:

		if (stage_gw == 0)
		{

		}
		else if (stage_gw == 1)
		{

		}
		else if (stage_gw == 2)
		{

		}
		break;

	case 3:
		if (stage_gw == 0)
		{

		}
		else if (stage_gw == 1)
		{

		}
		else if (stage_gw == 2)
		{

		}

		break;

	case 4:
		if (stage_gw == 0)
		{

		}
		else if (stage_gw == 1)
		{

		}
		else if (stage_gw == 2)
		{

		}

		break;

	case 5:
		if (stage_gw == 0)
		{

		}
		else if (stage_gw == 1)
		{

		}
		else if (stage_gw == 2)
		{

		}
		break;


	}


}

void DrawGimmickWall()
{
	D3DXVECTOR2 basePos_gw = GetBase();
	double 	mappos_gw = GetMapPos();

	for (int i = 0; i < WALL_MAX; i++)
	{
		if (g_wall[i].use == true)
		{
			//テクスチャのセット
			GetDeviceContext()->PSSetShaderResources
			(0, 1, GetTexture(g_wall[i].texNo));
			//スプライトの描画
			DrawSpriteColorRotate
			(
				mappos_gw + basePos_gw.x + g_wall[i].pos.x,
				basePos_gw.y + g_wall[i].pos.y,
				DRAW_SIZE,
				DRAW_SIZE,
				g_wall[i].rot,
				g_wall[i].col,
				g_wall[i].Patern,
				1.0f / 12.0f,//横
				1.0f,//縦
				12//総枚数
			);

		}
	}

}

G_WALL* GetGimmickWall()
{
	return g_wall;
}


void InitWall_12()
{
	g_wall[0].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_wall[1].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_wall[2].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_wall[3].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_wall[4].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_wall[5].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 6);
	g_wall[6].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_wall[7].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 8);


	for (int i = 0; i < 8; i++)
	{
		g_wall[i].use = true;
	}
}

void InitWall_13()
{
	g_wall[0].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 75, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_wall[1].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 76, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_wall[2].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 77, DEFO_SIZE_Y - DRAW_SIZE * 1);

	g_wall[3].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 78, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_wall[4].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 79, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_wall[5].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 80, DEFO_SIZE_Y - DRAW_SIZE * 2);

	g_wall[6].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 81, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_wall[7].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 82, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_wall[8].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 83, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_wall[9].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 84, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_wall[10].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 85, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_wall[11].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 86, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_wall[12].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 87, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_wall[13].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 88, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_wall[14].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 89, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_wall[15].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 90, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_wall[16].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 91, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_wall[17].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 92, DEFO_SIZE_Y - DRAW_SIZE * 4);

	for (int i = 0; i < 18; i++)
	{
		g_wall[i].use = true;
	}
}