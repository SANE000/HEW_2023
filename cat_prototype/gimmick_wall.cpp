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
#include "cat.h"

//==========================================
////g_wallのコリジョン！！！！！！！！
//==========================================

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
void InitWall_23();
void InitWall_31();
void InitWall_32();
void InitWall_33();
void InitWall_43();
void InitWall_51();
void InitWall_53();

HRESULT InitGimmickWall()
{
	int field_gw = SetField();
	int stage_gw = SetStage();
	int clear_gw = SetClear();

	for (int i = 0; i < WALL_MAX; i++)
	{
		g_wall[i].use = false;
		g_wall[i].texNo = LoadTexture((char*)"data\\texture\\block.png");
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
		else if (stage_gw == 2 && clear_gw >= 5)
		{
			InitWall_23();
		}

		break;

	case 2:

		if (stage_gw == 0)
		{
			InitWall_31();
		}
		else if (stage_gw == 1)
		{
			InitWall_32();
		}
		else if (stage_gw == 2)
		{
			InitWall_33();
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
			InitWall_43();
		}

		break;

	case 4:
		if (stage_gw == 0)
		{
			InitWall_51();
		}
		else if (stage_gw == 1)
		{

		}
		else if (stage_gw == 2)
		{
			InitWall_53();
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

		//2-1
	case 1:
		if (stage_gw == 0)
		{

		}
		else if (stage_gw == 1)
		{

		}
		else if (stage_gw == 2 && clear_gw >= 5)
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

	case 2:
		//3-1
		if (stage_gw == 0)
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
		else if (stage_gw == 1)
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
		else if (stage_gw == 2)
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

	case 3:
		if (stage_gw == 0)
		{

		}
		else if (stage_gw == 1)
		{

		}
		else if (stage_gw == 2)
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

	case 4:
		if (stage_gw == 0)
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
		else if (stage_gw == 1)
		{

		}
		else if (stage_gw == 2)
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
			if (pb[52].button == false)
			{
				for (int i = 0; i < 16; i++)
				{
					g_wall[i].use = false;
				}
			}

		}
		else if (stage_gw == 2 && clear_gw >= 2)
		{
			
			//ボタンが押されたら全部falseにする
			if (pb[50].button == false)
			{
				for (int i = 0; i < 8; i++)
				{
					g_wall[i].use = false;
				}
			}
		}

		break;

		//2-1
	case 1:
		if (stage_gw == 0)
		{

		}
		else if (stage_gw == 1)
		{

		}
		else if (stage_gw == 2 && clear_gw >= 5)
		{
			//赤ボタンaが押されたら全部trueにする
			if (pb[7].button == false)
			{
				for (int i = 0; i < 4; i++)
				{
					g_wall[i].use = true;
				}
			}
			//青ボタンaが押されたら全部falseにする
			if (pb[9].button == false)
			{
				for (int i = 4; i < 8; i++)
				{
					g_wall[i].use = false;
				}
			}
		}

		break;

	case 2:

		if (stage_gw == 0)
		{
			if (pb[66].button == false)
			{
				for (int i = 0; i < 7; i++)
				{
					g_wall[i].use = false;
				}
			}
		}
		else if (stage_gw == 1)
		{
			//青ボタンaが押されたら全部falseにする
			if (pb[25].button == false)
			{
				for (int i = 0; i < 10; i++)
				{
					g_wall[i].use = false;
				}
			}
			//青ボタンbが押されたら全部falseにする
			if (pb[62].button == false)
			{
				for (int i = 10; i < 17; i++)
				{
					g_wall[i].use = false;
				}
			}
		}
		else if (stage_gw == 2)
		{
			//赤ボタンaが押されたら全部trueにする
			if (pb[28].button == false)
			{
				for (int i = 0; i < 3; i++)
				{
					g_wall[i].use = true;
				}
			}
			//青ボタンaが押されたら全部falseにする
			if (pb[30].button == false)
			{
				for (int i = 3; i < 6; i++)
				{
					g_wall[i].use = false;
				}
			}
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
			//赤ボタンaが押されたら全部trueにする
			if (pb[68].button == false)
			{
				for (int i = 0; i < 26; i++)
				{
					g_wall[i].use = true;
				}
			}
		}

		break;

	case 4:
		if (stage_gw == 0)
		{
			//青ボタンaが押されたら全部falseにする
			if (pb[83].button == false)
			{
				for (int i = 0; i < 15; i++)
				{
					g_wall[i].use = false;
				}
			}
		}
		else if (stage_gw == 1)
		{

		}
		else if (stage_gw == 2)
		{
			//青ボタンaが押されたら全部falseにする
			if (pb[7].button == false)
			{
				for (int i = 0; i < 15; i++)
				{
					g_wall[i].use = false;
				}
			}
			//青ボタンbが押されたら全部falseにする
			if (pb[31].button == false)
			{
				for (int i = 15; i < 18; i++)
				{
					g_wall[i].use = false;
				}
			}
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
	CAT* c = GetCat();
	D3DXVECTOR2 basePos_gw = GetBase();
	double 	mappos_gw = GetMapPos();

	for (int i = 0; i < WALL_MAX; i++)
	{
		//偵察中は描写
		if (WatchMapFlag() == false)
		{
			//プレイ中は猫から遠いものは描画しない
			if (g_wall[i].pos.x < (c->pos.x - 960) || g_wall[i].pos.x >(c->pos.x + 960))
			{
				continue;
			}
		}

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
				1.0f / 3.0f,//縦
				12//総枚数
			);

		}
	}

}

G_WALL* GetGimmickWall()
{
	return g_wall;
}

void InitWall_53()
{
	g_wall[0].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_wall[1].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_wall[2].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 2);

	g_wall[3].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_wall[4].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_wall[5].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 5);

	g_wall[6].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 6);
	g_wall[7].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_wall[8].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 8);

	g_wall[9].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 14, DEFO_SIZE_Y - DRAW_SIZE * 8);
	g_wall[10].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 8);
	g_wall[11].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 12, DEFO_SIZE_Y - DRAW_SIZE * 8);
	g_wall[12].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 11, DEFO_SIZE_Y - DRAW_SIZE * 8);
	g_wall[13].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 10, DEFO_SIZE_Y - DRAW_SIZE * 8);
	//この上に敵
	g_wall[14].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 9, DEFO_SIZE_Y - DRAW_SIZE * 8);

	g_wall[15].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 42, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_wall[16].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 42, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_wall[17].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 42, DEFO_SIZE_Y - DRAW_SIZE * 4);
	//青
	for (int i = 0; i < 18; i++)
	{
		g_wall[i].use = true;
		g_wall[i].Patern = 7.0f;
	}
}

void InitWall_51()
{
	g_wall[0].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 48, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_wall[1].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 49, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_wall[2].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 50, DEFO_SIZE_Y - DRAW_SIZE * 5);

	g_wall[3].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 52, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_wall[4].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 53, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_wall[5].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 54, DEFO_SIZE_Y - DRAW_SIZE * 5);

	g_wall[6].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 55, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_wall[7].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 56, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_wall[8].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 57, DEFO_SIZE_Y - DRAW_SIZE * 5);

	g_wall[9].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 58, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_wall[10].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 59, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_wall[11].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 60, DEFO_SIZE_Y - DRAW_SIZE * 5);

	g_wall[12].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 61, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_wall[13].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 62, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_wall[14].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 63, DEFO_SIZE_Y - DRAW_SIZE * 5);

	//青
	for (int i = 0; i < 15; i++)
	{
		g_wall[i].use = true;
		g_wall[i].Patern = 7.0f;
	}
}

void InitWall_43()
{
	g_wall[0].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 39, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_wall[1].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 39, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_wall[2].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 39, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_wall[3].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 39, DEFO_SIZE_Y - DRAW_SIZE * 6);
	g_wall[4].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 39, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_wall[5].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 39, DEFO_SIZE_Y - DRAW_SIZE * 8);

	g_wall[6].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_wall[7].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_wall[8].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_wall[9].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_wall[10].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_wall[11].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_wall[12].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 6);

	g_wall[13].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 46, DEFO_SIZE_Y - DRAW_SIZE * 6);
	g_wall[14].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 47, DEFO_SIZE_Y - DRAW_SIZE * 6);
	g_wall[15].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 48, DEFO_SIZE_Y - DRAW_SIZE * 6);
	g_wall[16].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 49, DEFO_SIZE_Y - DRAW_SIZE * 6);
	g_wall[17].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 50, DEFO_SIZE_Y - DRAW_SIZE * 6);
	g_wall[18].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 51, DEFO_SIZE_Y - DRAW_SIZE * 6);
	g_wall[19].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 52, DEFO_SIZE_Y - DRAW_SIZE * 6);
	g_wall[20].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 53, DEFO_SIZE_Y - DRAW_SIZE * 6);
	g_wall[21].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 54, DEFO_SIZE_Y - DRAW_SIZE * 6);
	g_wall[22].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 55, DEFO_SIZE_Y - DRAW_SIZE * 6);
	g_wall[23].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 56, DEFO_SIZE_Y - DRAW_SIZE * 6);
	g_wall[24].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 57, DEFO_SIZE_Y - DRAW_SIZE * 6);
	g_wall[25].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 58, DEFO_SIZE_Y - DRAW_SIZE * 6);

	//赤
	for (int i = 0; i < 26; i++)
	{
		g_wall[i].use = false;
		g_wall[i].Patern = 8.0f;
	}
}

void InitWall_33()
{
	g_wall[0].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 22, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_wall[1].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_wall[2].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 24, DEFO_SIZE_Y - DRAW_SIZE * 1);

	g_wall[3].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 22, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_wall[4].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_wall[5].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 24, DEFO_SIZE_Y - DRAW_SIZE * 4);

	//赤
	for (int i = 0; i < 3; i++)
	{
		g_wall[i].use = false;
		g_wall[i].Patern = 8.0f;
	}
	//青
	for (int i = 3; i < 6; i++)
	{
		g_wall[i].use = true;
		g_wall[i].Patern = 7.0f;
	}
}

void InitWall_32()
{
	g_wall[0].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_wall[1].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_wall[2].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_wall[3].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_wall[4].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_wall[5].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_wall[6].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 6);
	g_wall[7].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_wall[8].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 8);
	g_wall[9].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 1);

	g_wall[10].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 44, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_wall[11].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 44, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_wall[12].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 44, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_wall[13].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 44, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_wall[14].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 44, DEFO_SIZE_Y - DRAW_SIZE * 6);
	g_wall[15].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 44, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_wall[16].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 44, DEFO_SIZE_Y - DRAW_SIZE * 8);

	//青
	for (int i = 0; i < 17; i++)
	{
		g_wall[i].use = true;
		g_wall[i].Patern = 7.0f;
	}
}
void InitWall_31()
{
	g_wall[0].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 47, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_wall[1].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 47, DEFO_SIZE_Y - DRAW_SIZE * 6);
	g_wall[2].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 47, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_wall[3].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 47, DEFO_SIZE_Y - DRAW_SIZE * 8);

	g_wall[4].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 41, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_wall[5].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 42, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_wall[6].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 43, DEFO_SIZE_Y - DRAW_SIZE * 0);

	//青
	for (int i = 0; i < 7; i++)
	{
		g_wall[i].use = true;
		g_wall[i].Patern = 7.0f;
	}
}

void InitWall_23()
{
	g_wall[0].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 7, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_wall[1].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_wall[2].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 9, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_wall[3].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 10, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_wall[4].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 12, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_wall[5].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_wall[6].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 14, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_wall[7].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 3);

	//赤
	for (int i = 0; i < 4; i++)
	{
		g_wall[i].use = false;
		g_wall[i].Patern = 8.0f;
	}
	//青
	for (int i = 4; i < 8; i++)
	{
		g_wall[i].use = true;
		g_wall[i].Patern = 7.0f;
	}
}

void InitWall_12()
{
	g_wall[0].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_wall[1].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 46, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_wall[2].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 47, DEFO_SIZE_Y - DRAW_SIZE * 1);

	g_wall[3].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 48, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_wall[4].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 49, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_wall[5].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 50, DEFO_SIZE_Y - DRAW_SIZE * 2);

	g_wall[6].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 51, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_wall[7].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 52, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_wall[8].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 53, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_wall[9].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 54, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_wall[10].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 55, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_wall[11].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 56, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_wall[12].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 57, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_wall[13].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 58, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_wall[14].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 59, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_wall[15].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 60, DEFO_SIZE_Y - DRAW_SIZE * 4);

	for (int i = 0; i < 16; i++)
	{
		g_wall[i].use = true;
		g_wall[i].Patern = 7.0f;
	}
}

void InitWall_13()
{
	g_wall[0].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 30, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_wall[1].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 30, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_wall[2].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 30, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_wall[3].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 30, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_wall[4].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 30, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_wall[5].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 30, DEFO_SIZE_Y - DRAW_SIZE * 6);
	g_wall[6].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 30, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_wall[7].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 30, DEFO_SIZE_Y - DRAW_SIZE * 8);


	for (int i = 0; i < 8; i++)
	{
		g_wall[i].use = true;
		g_wall[i].Patern = 7.0f;
	}
}