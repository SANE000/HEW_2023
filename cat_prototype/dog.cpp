#include "main.h"
#include "dog.h"
#include "texture.h"
#include "sprite.h"
#include "camera.h"
#include "shop.h"
#include "stageselect.h"
//------------------------
//グローバル変数
//------------------------
static int field;
static int stage;
static DOG g_Dog[DOG_MAX];

DOG InitData[] = 
{
	{true,false,false,D3DXVECTOR2(580,210),0,D3DXVECTOR2(0.0f,0),0,DOG_SIZE_W,DOG_SIZE_H,D3DXVECTOR2(0,0),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),200,0,0},
	{true,false,false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 59, DEFO_SIZE_Y - DRAW_SIZE * 6),0,D3DXVECTOR2(0.0f,0),0,DOG_SIZE_W,DOG_SIZE_H,D3DXVECTOR2(0,0),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),200,0,0},
	{true,false,false,D3DXVECTOR2(5200,210),0,D3DXVECTOR2(0.0f,0),0,DOG_SIZE_W,DOG_SIZE_H,D3DXVECTOR2(0,0),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),200,0,0}
};

//------------------------
//DOG初期化
//------------------------
HRESULT InitDog()
{
	//ステージを把握して
	field = SetField();
	stage = SetStage();
	//1-2だけ犬を表示
	if (field == 0)
	{
		if (stage == 1)
		{
			for (int i = 0; i < DOG_MAX; i++)
			{
				g_Dog[i] = InitData[i];

				g_Dog[i].texNo = LoadTexture((char*)"data\\texture\\dog_sample.png");
			}
		}
	}
	return S_OK;
}

//------------------------
//DOG終了処理
//------------------------
void UnInitDog()
{

}

//------------------------
//DOG更新処理
//------------------------
void UpdateDog()
{

	for (int i = 0; i < DOG_MAX; i++)
	{
		if (g_Dog[i].jump_flag == false)
		{
			g_Dog[i].pos.y += GRAV;
		}

		//if (g_Dog[i].move_flag == false)
		//{
		//	g_Dog[i].pos.x += g_Dog[i].dir.x;
		//}
		
		//if (g_Dog[i].move_flag == false)
		//{
		//	g_Dog[i].pos.x += DOG_SPEED;
		//}
	}
}

//------------------------
//DOG描画処理
//------------------------
void DrawDog()
{
	for (int i = 0; i < DOG_MAX; i++)
	{
		D3DXVECTOR2 basePos = GetBase();
		if (g_Dog[i].use = true)
		{
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Dog[i].texNo));

			//スプライト描画
			//SetBlendState(BLEND_MODE_ADD);  //透明になる
			DrawSpriteColorRotate(
				basePos.x + g_Dog[i].pos.x,
				basePos.y + g_Dog[i].pos.y,
				g_Dog[i].w,
				g_Dog[i].h,
				g_Dog[i].rot,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				(int)g_Dog[i].anime,				//パターン番後			0
				1.0f / 1.0f,						//パターンの横サイズ	
				1.0f / 1.0f,						//パターンの縦サイズ	
				1									//パターンの横の数		
			);
			SetBlendState(BLEND_MODE_ALPHABLEND);
		}
	}
}

DOG * GetDog()
{
	return &g_Dog[0];
}

void ChangeDogMoveFlag(DOG* d)
{
	if (d->move_flag == true)
	{
		d->move_flag = false;
		g_Dog[0].dir *= -1;

	}
	else if (d->move_flag == false)
	{
		d->move_flag = true;
		g_Dog[0].dir *= -1;
	}
}
