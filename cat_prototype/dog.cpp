#include "main.h"
#include "dog.h"
#include "cat.h"
#include "texture.h"
#include "sprite.h"
#include "camera.h"
#include "shop.h"
#include "stageselect.h"
#include "block.h"
#include "result.h"

//------------------------
//グローバル変数
//------------------------
static int field;
static int stage;
static int clear;
static DOG g_Dog[DOG_MAX];
//犬

DOG InitData12[] =
{
	{true,false,false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 0, DEFO_SIZE_Y - DRAW_SIZE * 1),0,D3DXVECTOR2(0.0f,0),0,DOG_SIZE_W,DOG_SIZE_H,D3DXVECTOR2(0,0),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),200,1,0},
	{true,false,false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 19, DEFO_SIZE_Y - DRAW_SIZE * 5),0,D3DXVECTOR2(0.0f,0),0,DOG_SIZE_W,DOG_SIZE_H,D3DXVECTOR2(0,0),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),200,1,0},
	{true,false,false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 36, DEFO_SIZE_Y - DRAW_SIZE * 7),0,D3DXVECTOR2(0.0f,0),0,DOG_SIZE_W,DOG_SIZE_H,D3DXVECTOR2(0,0),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),200,1,0}
};

DOG InitData13[] =
{
	{false,false,false,D3DXVECTOR2(0,0),0,D3DXVECTOR2(0.0f,0),0,DOG_SIZE_W,DOG_SIZE_H,D3DXVECTOR2(0,0),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),200,1,0},
	{true,false,false,D3DXVECTOR2(580,210),0,D3DXVECTOR2(0.0f,0),0,DOG_SIZE_W,DOG_SIZE_H,D3DXVECTOR2(0,0),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),200,1,0},
	{true,false,false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 54, DEFO_SIZE_Y - DRAW_SIZE * 5),0,D3DXVECTOR2(0.0f,0),0,DOG_SIZE_W,DOG_SIZE_H,D3DXVECTOR2(0,0),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),200,1,0}
};


//ミイラ猫
DOG InitData22[] =
{
	{true,false,false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 4, DEFO_SIZE_Y - DRAW_SIZE * 1),0,D3DXVECTOR2(0.0f,0),0,DOG_SIZE_W,DOG_SIZE_H,D3DXVECTOR2(0,0),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),200,1,0},
	{false,false,false,D3DXVECTOR2(0,0),0,D3DXVECTOR2(0.0f,0),0,DOG_SIZE_W,DOG_SIZE_H,D3DXVECTOR2(0,0),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),200,1,0},
	{true,false,false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 47, DEFO_SIZE_Y - DRAW_SIZE * 1),0,D3DXVECTOR2(0.0f,0),0,DOG_SIZE_W,DOG_SIZE_H,D3DXVECTOR2(0,0),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),200,1,0}
};

DOG InitData23[] =
{
	{false,false,false,D3DXVECTOR2(0,0),0,D3DXVECTOR2(0.0f,0),0,DOG_SIZE_W,DOG_SIZE_H,D3DXVECTOR2(0,0),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),200,1,0},
	{true,false,false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 26, DEFO_SIZE_Y - DRAW_SIZE * 1),0,D3DXVECTOR2(0.0f,0),0,DOG_SIZE_W,DOG_SIZE_H,D3DXVECTOR2(0,0),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),200,1,0},
	{true,false,false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 47, DEFO_SIZE_Y - DRAW_SIZE * 1),0,D3DXVECTOR2(0.0f,0),0,DOG_SIZE_W,DOG_SIZE_H,D3DXVECTOR2(0,0),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),200,1,0}
};
//ネズミ 猫がおいかけちゃうようにする？
DOG InitData31[] =
{
	{true,false,false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 25, DEFO_SIZE_Y - DRAW_SIZE * 5),0,D3DXVECTOR2(0.0f,0),0,DOG_SIZE_W,DOG_SIZE_H,D3DXVECTOR2(0,0),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),200,1,0},
	{true,false,false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 48, DEFO_SIZE_Y - DRAW_SIZE * 1),0,D3DXVECTOR2(0.0f,0),0,DOG_SIZE_W,DOG_SIZE_H,D3DXVECTOR2(0,0),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),200,1,0},
	{true,false,false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 50, DEFO_SIZE_Y - DRAW_SIZE * 8),0,D3DXVECTOR2(0.0f,0),0,DOG_SIZE_W,DOG_SIZE_H,D3DXVECTOR2(0,0),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),200,1,0}
};

DOG InitData32[] =
{
	{true,false,false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 27, DEFO_SIZE_Y - DRAW_SIZE * 5),0,D3DXVECTOR2(0.0f,0),0,DOG_SIZE_W,DOG_SIZE_H,D3DXVECTOR2(0,0),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),200,1,0},
	{false,false,false,D3DXVECTOR2(0,0),0,D3DXVECTOR2(0.0f,0),0,DOG_SIZE_W,DOG_SIZE_H,D3DXVECTOR2(0,0),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),200,1,0},
	{false,false,false,D3DXVECTOR2(0,0),0,D3DXVECTOR2(0.0f,0),0,DOG_SIZE_W,DOG_SIZE_H,D3DXVECTOR2(0,0),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),200,1,0}
};

DOG InitData33[] =
{
	{true,false,false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 27, DEFO_SIZE_Y - DRAW_SIZE * 5),0,D3DXVECTOR2(0.0f,0),0,DOG_SIZE_W,DOG_SIZE_H,D3DXVECTOR2(0,0),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),200,1,0},
	{true,false,false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 53, DEFO_SIZE_Y - DRAW_SIZE * 8),0,D3DXVECTOR2(0.0f,0),0,DOG_SIZE_W,DOG_SIZE_H,D3DXVECTOR2(0,0),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),200,1,0},
	{true,false,false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 58, DEFO_SIZE_Y - DRAW_SIZE * 8),0,D3DXVECTOR2(0.0f,0),0,DOG_SIZE_W,DOG_SIZE_H,D3DXVECTOR2(0,0),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),200,1,0}
};
//サメ重力なしにしたい
DOG InitData41[] =
{
	{true,false,false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 28, DEFO_SIZE_Y - DRAW_SIZE * 7),0,D3DXVECTOR2(0.0f,0),0,DOG_SIZE_W,DOG_SIZE_H,D3DXVECTOR2(0,0),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),200,1,0},
	{true,false,false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 50, DEFO_SIZE_Y - DRAW_SIZE * 8),0,D3DXVECTOR2(0.0f,0),0,DOG_SIZE_W,DOG_SIZE_H,D3DXVECTOR2(0,0),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),200,1,0},
	{true,false,false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 61, DEFO_SIZE_Y - DRAW_SIZE * 8),0,D3DXVECTOR2(0.0f,0),0,DOG_SIZE_W,DOG_SIZE_H,D3DXVECTOR2(0,0),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),200,1,0}
};

DOG InitData42[] =
{
	{true,false,false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 21, DEFO_SIZE_Y - DRAW_SIZE * 7),0,D3DXVECTOR2(0.0f,0),0,DOG_SIZE_W,DOG_SIZE_H,D3DXVECTOR2(0,0),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),200,1,0},
	{true,false,false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 40, DEFO_SIZE_Y - DRAW_SIZE * 8),0,D3DXVECTOR2(0.0f,0),0,DOG_SIZE_W,DOG_SIZE_H,D3DXVECTOR2(0,0),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),200,1,0},
	{false,false,false,D3DXVECTOR2(0,0),0,D3DXVECTOR2(0.0f,0),0,DOG_SIZE_W,DOG_SIZE_H,D3DXVECTOR2(0,0),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),200,1,0}
};

DOG InitData43[] =
{//
	{true,false,false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 1),0,D3DXVECTOR2(0.0f,0),0,DOG_SIZE_W,DOG_SIZE_H,D3DXVECTOR2(0,0),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),200,1,0},
	{false,false,false,D3DXVECTOR2(0,0),0,D3DXVECTOR2(0.0f,0),0,DOG_SIZE_W,DOG_SIZE_H,D3DXVECTOR2(0,0),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),200,1,0},
	{false,false,false,D3DXVECTOR2(0,0),0,D3DXVECTOR2(0.0f,0),0,DOG_SIZE_W,DOG_SIZE_H,D3DXVECTOR2(0,0),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),200,1,0}
};

DOG InitData51[] =
{//
	{true,false,false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 17, DEFO_SIZE_Y - DRAW_SIZE * 4),0,D3DXVECTOR2(0.0f,0),0,DOG_SIZE_W,DOG_SIZE_H,D3DXVECTOR2(0,0),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),200,1,0},
	{true,false,false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 39, DEFO_SIZE_Y - DRAW_SIZE * 3),0,D3DXVECTOR2(0.0f,0),0,DOG_SIZE_W,DOG_SIZE_H,D3DXVECTOR2(0,0),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),200,1,0},
	{true,false,false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 48, DEFO_SIZE_Y - DRAW_SIZE * 6),0,D3DXVECTOR2(0.0f,0),0,DOG_SIZE_W,DOG_SIZE_H,D3DXVECTOR2(0,0),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),200,1,0}
};

DOG InitData52[] =
{//
	{false,false,false,D3DXVECTOR2(0,0),0,D3DXVECTOR2(0.0f,0),0,DOG_SIZE_W,DOG_SIZE_H,D3DXVECTOR2(0,0),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),200,1,0},
	{true,false,false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 27, DEFO_SIZE_Y - DRAW_SIZE * 6),0,D3DXVECTOR2(0.0f,0),0,DOG_SIZE_W,DOG_SIZE_H,D3DXVECTOR2(0,0),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),200,1,0},
	{true,false,false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 53, DEFO_SIZE_Y - DRAW_SIZE * 1),0,D3DXVECTOR2(0.0f,0),0,DOG_SIZE_W,DOG_SIZE_H,D3DXVECTOR2(0,0),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),200,1,0}
};

DOG InitData53[] =
{//
	{true,false,false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 12, DEFO_SIZE_Y - DRAW_SIZE * 9),0,D3DXVECTOR2(0.0f,0),0,DOG_SIZE_W,DOG_SIZE_H,D3DXVECTOR2(0,0),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),200,1,0},
	{true,false,false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 22, DEFO_SIZE_Y - DRAW_SIZE * 11),0,D3DXVECTOR2(0.0f,0),0,DOG_SIZE_W,DOG_SIZE_H,D3DXVECTOR2(0,0),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),200,1,0},
	{true,false,false,D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 48, DEFO_SIZE_Y - DRAW_SIZE * 2),0,D3DXVECTOR2(0.0f,0),0,DOG_SIZE_W,DOG_SIZE_H,D3DXVECTOR2(0,0),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),200,1,0}
};

//------------------------
//DOG初期化
//------------------------
HRESULT InitDog()
{
	//ステージを把握して
	field = SetField();
	stage = SetStage();
	clear = SetClear();
	//1-2だけ犬を表示
	if (field == 0)
	{
		if (stage == 1 && clear >= 1)
		{
			for (int i = 0; i < DOG_MAX; i++)
			{
				g_Dog[i] = InitData12[i];

				g_Dog[i].texNo = LoadTexture((char*)"data\\texture\\dog_sample.png");
			}
		}
		else if (stage == 2 && clear >= 2)
		{
			for (int i = 0; i < DOG_MAX; i++)
			{
				g_Dog[i] = InitData13[i];

				g_Dog[i].texNo = LoadTexture((char*)"data\\texture\\dog_sample.png");
			}
		}
	}
	else if (field == 1)
	{
		if (stage == 1 && clear >= 4)
		{
			for (int i = 0; i < DOG_MAX; i++)
			{
				g_Dog[i] = InitData22[i];

				g_Dog[i].texNo = LoadTexture((char*)"data\\texture\\catmummy_sample.png");
			}
		}
		else if (stage == 2 && clear >= 5)
		{
			for (int i = 0; i < DOG_MAX; i++)
			{
				g_Dog[i] = InitData23[i];

				g_Dog[i].texNo = LoadTexture((char*)"data\\texture\\catmummy_sample.png");
			}
		}
	}
	else if (field == 2)
	{
		if (stage == 0 && clear >= 6)
		{
			for (int i = 0; i < DOG_MAX; i++)
			{
				g_Dog[i] = InitData31[i];

				g_Dog[i].texNo = LoadTexture((char*)"data\\texture\\nezumi.png");
			}
		}
		else if (stage == 1 && clear >= 7)
		{
			for (int i = 0; i < DOG_MAX; i++)
			{
				g_Dog[i] = InitData32[i];

				g_Dog[i].texNo = LoadTexture((char*)"data\\texture\\nezumi.png");
			}
		}
		else if (stage == 2 && clear >= 8)
		{
			for (int i = 0; i < DOG_MAX; i++)
			{
				g_Dog[i] = InitData33[i];

				g_Dog[i].texNo = LoadTexture((char*)"data\\texture\\nezumi.png");
			}
		}
	}
	else if (field == 3)
	{
		if (stage == 0 && clear >= 9)
		{
			for (int i = 0; i < DOG_MAX; i++)
			{
				g_Dog[i] = InitData41[i];

				g_Dog[i].texNo = LoadTexture((char*)"data\\texture\\same.png");
			}
		}
		else if (stage == 1 && clear >= 10)
		{
			for (int i = 0; i < DOG_MAX; i++)
			{
				g_Dog[i] = InitData42[i];

				g_Dog[i].texNo = LoadTexture((char*)"data\\texture\\same.png");
			}
		}
		else if (stage == 2 && clear >= 11)
		{
			for (int i = 0; i < DOG_MAX; i++)
			{
				g_Dog[i] = InitData43[i];

				g_Dog[i].texNo = LoadTexture((char*)"data\\texture\\same.png");
			}
		}
	}
	else if (field == 4)
	{
	if (stage == 0 && clear >= 12)
	{
		for (int i = 0; i < DOG_MAX; i++)
		{
			g_Dog[i] = InitData51[i];

			g_Dog[i].texNo = LoadTexture((char*)"data\\texture\\kariseizin.png");
		}
	}
	else if (stage == 1 && clear >= 13)
	{
		for (int i = 0; i < DOG_MAX; i++)
		{
			g_Dog[i] = InitData52[i];

			g_Dog[i].texNo = LoadTexture((char*)"data\\texture\\kariseizin.png");
		}
	}
	else if (stage == 2 && clear >= 14)
	{
		for (int i = 0; i < DOG_MAX; i++)
		{
			g_Dog[i] = InitData53[i];

			g_Dog[i].texNo = LoadTexture((char*)"data\\texture\\kariseizin.png");
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
	for (int i = 0; i < DOG_MAX; i++)
	{
		g_Dog[i].use = false;
	}
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

		if (g_Dog[i].use == true)
		{
			D3DXVECTOR2 CloseToDog;
			CloseToDog.x = 300.0f;
			D3DXVECTOR2 temp;
			CAT* cat = GetCat();
			temp = g_Dog[i].pos - cat->pos;
			if (temp.x <= CloseToDog.x)
			{
				if (g_Dog[i].framewait <= 0.0)
				{
					if (g_Dog[i].ugoki == 1)
					{
						D3DXVec2Normalize(&temp, &temp);
						temp *= 2.0f;
						g_Dog[i].move = temp;
						g_Dog[i].pos += -g_Dog[i].move;
					}
				}
				else
				{
					g_Dog[i].framewait--;
				}
			}
		}
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
		double mappos = GetMapPos();

		if (g_Dog[i].use == true)
		{
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Dog[i].texNo));

			//スプライト描画
			//SetBlendState(BLEND_MODE_ADD);  //透明になる
			DrawSpriteColorRotate(
				mappos + basePos.x + g_Dog[i].pos.x,
				basePos.y + g_Dog[i].pos.y,
				DRAW_SIZE,
				DRAW_SIZE,
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
