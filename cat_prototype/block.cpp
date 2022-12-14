#include "main.h"
#include "block.h"
#include "shop.h"
#include "texture.h"
#include "sprite.h"
#include "camera.h"
#include "cat.h"
#include "gimmick_wall.h"
#include "stageselect.h"
#include "inputx.h"
#include "keyboard.h"
#include "result.h"

//プロトタイプ宣言
void InitStage11();
void InitStage12();
void InitStage13();
void InitStage21();
void InitStage22();
void InitStage23();
void InitStage31();
void InitStage32();
//void InitStage33();
//==========================================
//グローバル変数
//==========================================
//偵察用
static int time = 0;
static double map_pos = 0;
//地面や足場の判定に使う
static BLOCK g_Block[BLOCK_MAX];
//==========================================
//ステージ選ぶ変数
//==========================================

//ステージ選択テスト用なので手動でInitで選んでます。
//ステージ選択画面ができたら消しちゃってください
static int clear;
static int field;
static int stage;
//world = 0なら一面の
//stage = 0ならステージ1
//あわせて1-1が選ばれる仕組み

HRESULT InitBlock()
{
	/////////////ここでステージセレクトのセッターゲットしたらいけるかな
	field = SetField();
	stage = SetStage();
	clear = SetClear();
	//BLOCK構造体の初期化
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		//テクスチャロード 画像の名前を入れよう
		g_Block[i].use = true;
		g_Block[i].moveflug = false;
		g_Block[i].texNo = LoadTexture((char*)"data\\texture\\block.png");
		//ブロックのリセット
		if (field == 0)
		{
			g_Block[i].Patern = 0.0f;
		}
		else if (field == 1)
		{
			g_Block[i].Patern = 12.0f;
		}
		else if (field == 2)
		{
			g_Block[i].Patern = 24.0f;
		}
	}
	////////////////////////////////////////////////////////////////////
	//ステージテスト
	//増えてきたらswitch構文でつくってもいいかも
	if (field == 0)
	{
		if (stage == 0 && clear >= 0)
		{
			//足場ブロックの設置.一番最後に設定
			InitStage11();
		}
		else if (stage == 1 && clear >= 1)
		{
			InitStage12();
			InitGimmickWall();
		}
		else if (stage == 2 && clear >= 2)
		{
			InitStage13();
			InitGimmickWall();
		}
	}
	else if (field == 1)
	{
		if (stage == 0 && clear >= 3)
		{
			InitStage21();
		}
		else if (stage == 1 && clear >= 4)
		{
			InitStage22();
		}
		else if (stage == 2 && clear >= 5)
		{
			InitStage23();
			InitGimmickWall();
		}
	}
	else if (field == 2)
	{
		if (stage == 0 && clear >= 6)
		{
			InitStage31();
			InitGimmickWall();
		}
		else if (stage == 1 && clear >= 7)
		{
			InitStage32();
			InitGimmickWall();
		}
		else if (stage == 2 && clear >= 8)
		{
			//InitStage33();
		}
	}
	else
	{
		//違うワールドのとき用
		exit(1);
	}
	//
	return S_OK;
}
//終了処理
void UnInitBlock()
{
	UninitGimmickWall();
}
//更新処理
void UpdateBlock()
{
	D3DXVECTOR2 basePos = GetBase();
	CAT* pCat = GetCat();
	//マップボタンが押されたら
	if (WatchMapFlag() == true)
	{//画面端になるまで座標を引いていく
		if (time > 0)
		{
			time -= 1;
		}
		//自動スクロールから,分かりやすいように自分で動かせるようにした
		if (Keyboard_IsKeyDown(KK_D) && time <= 0 || GetThumbLeftX(0) > 0 && time <= 0)
		{
			if (map_pos > -SCREEN_WIDTH * 3 + (-basePos.x))
			{
				//画面端になったら止める
				map_pos -= SCREEN_WIDTH;
				time = 20;
			}
		}
		else if (Keyboard_IsKeyDown(KK_A) && time <= 0 || GetThumbLeftX(0) < 0 && time <= 0)
		{
			if (map_pos < 0 - (basePos.x))
			{
				map_pos += SCREEN_WIDTH;
				time = 20;
			}
		}
	}
	else
	{
		//マップボタンが押されてないなら0にする
		map_pos = 0;
	}
	//縦に動くやつ
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		//まず移動するやつかチェック
		if (g_Block[i].Patern == 20.0f)
		{
			//画面上まで着いたらスピードを逆にする
			if (g_Block[i].pos.y < (DRAW_SIZE / 2.0))
			{
				g_Block[i].pos.y = (DRAW_SIZE / 2.0);
				g_Block[i].Speed.y = (GRAV / 4);
			}
			//画面下まで着いたらスピードを逆にする
			if (g_Block[i].pos.y > (SCREEN_HEIGHT - DRAW_SIZE / 2.0))
			{
				g_Block[i].pos.y = (SCREEN_HEIGHT - DRAW_SIZE / 2.0);
				g_Block[i].Speed.y = -(GRAV / 4);
			}
			//動くので座標の更新
			g_Block[i].pos += g_Block[i].Speed;
		}
	}
	//横に動くやつ
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		//まず移動するやつかチェック
		if (g_Block[i].Patern == 21.0f)
		{
			//右へ5つまで着いたらスピードを逆にする
			if (g_Block[i].pos.x > g_Block[i].limitmax)
			{
				g_Block[i].pos.x = g_Block[i].limitmax;
				g_Block[i].Speed.x = -(GRAV / 4);
			}
			//左へ5つまで着いたらスピードを逆にする
			if (g_Block[i].pos.x < g_Block[i].limitmin)
			{
				g_Block[i].pos.x = g_Block[i].limitmin;
				g_Block[i].Speed.x = (GRAV / 4);
			}
			//動くので座標の更新
			g_Block[i].pos += g_Block[i].Speed;
		}
	}
	//近づいたら下に動くやつ
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		//まず移動するやつかチェック
		if (g_Block[i].Patern == 25.0f)
		{
			//猫が近くにいて動いてないかチェック
			if (pCat->pos.x > g_Block[i].pos.x - (DRAW_SIZE * 4) && g_Block[i].moveflug == false)
			{
				//一回だけ呼ぶ
				g_Block[i].Speed.y = (GRAV / 2);
				g_Block[i].moveflug = true;
			}
			//限界値まで着いたら止める
			if (g_Block[i].pos.y > g_Block[i].limitmax)
			{
				g_Block[i].pos.y = g_Block[i].limitmax;
				g_Block[i].Speed.y = 0;
			}
			//動くので座標の更新
			g_Block[i].pos += g_Block[i].Speed;
		}
	}
	//ボタンを押した後の処理
	UpdateGimmickWall();
}
//描画処理
void DrawBlock()
{
	D3DXVECTOR2 basePos = GetBase();

	//動かないステージブロック
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		//ブロックによってパターンの変更
		//パターンによって効果があってもいいかも
		//stage11では
		//21~29 or 33~44 or 108~110は表面では無い方へ変更
		//stage12では
		if (field == 0)
		{
			if (stage == 1)
			{
				if (i == 50)
				{
					//ボタンブロック
					if (g_Block[i].button == true)
					{

						g_Block[i].Patern = 3.0f;
					}
					else
					{
						g_Block[i].Patern = 4.0f;
					}
				}
			}
			else if (stage == 2)
			{
				if (i == 52)
				{
					//ボタンブロック
					if (g_Block[i].button == true)
					{

						g_Block[i].Patern = 3.0f;
					}
					else
					{
						g_Block[i].Patern = 4.0f;
					}
				}
			}
		}
		else if (field == 1)
		{
			//背景のサボテンとブロックのサボテンを分かりやすくするための反転動き
			if (g_Block[i].Patern >= 15.0f && g_Block[i].Patern <= 16.9f)
			{
				g_Block[i].Patern += 0.05f;
			}
			else if (g_Block[i].Patern >= 16.9f && g_Block[i].Patern < 17.0f)
			{
				g_Block[i].Patern = 15.0f;
			}
			//ボタン
			if (stage == 2)
			{
				//赤
				if (i == 7)
				{
					//ボタンブロック
					if (g_Block[i].button == true)
					{

						g_Block[i].Patern = 5.0f;
					}
					else
					{
						g_Block[i].Patern = 6.0f;
					}
				}
				else if (i == 9)//青
				{
					//ボタンブロック
					if (g_Block[i].button == true)
					{

						g_Block[i].Patern = 3.0f;
					}
					else
					{
						g_Block[i].Patern = 4.0f;
					}
				}
			}
		}
		else if (field == 2)
		{
			//ボタン
			if (stage == 0)
			{
				if (i == 66)//青
				{
					//ボタンブロック
					if (g_Block[i].button == true)
					{

						g_Block[i].Patern = 3.0f;
					}
					else
					{
						g_Block[i].Patern = 4.0f;
					}
				}
			}
			else if (stage == 1)
			{
				if (i == 25)//青
				{
					//ボタンブロック
					if (g_Block[i].button == true)
					{

						g_Block[i].Patern = 3.0f;
					}
					else
					{
						g_Block[i].Patern = 4.0f;
					}
				}
				else if (i == 62)//青
				{
					//ボタンブロック
					if (g_Block[i].button == true)
					{

						g_Block[i].Patern = 3.0f;
					}
					else
					{
						g_Block[i].Patern = 4.0f;
					}
				}
			}
		}
		if (g_Block[i].draw_use == true)
		{
			//テクスチャのセット
			GetDeviceContext()->PSSetShaderResources
			(0, 1, GetTexture(g_Block[i].texNo));
			//スプライトの描画
			DrawSpriteColorRotate
			(
				map_pos + basePos.x + g_Block[i].pos.x,
				basePos.y + g_Block[i].pos.y,
				DRAW_SIZE,
				DRAW_SIZE,
				g_Block[i].rot,
				g_Block[i].col,
				g_Block[i].Patern,
				1.0f / 12.0f,//横
				1.0f / 3.0f,//縦
				12//横の総枚数
			);
		}

		DrawGimmickWall();
	}
}
//構造体の先頭ポインタを返す　皆が使えるように
BLOCK *GetBlock()
{
	return &g_Block[0];
}

double GetMapPos()
{
	return map_pos;
}

int GetStage()
{
	return stage;
}

void InitStage32()
{
	//足場に関しては,ザーッと並べる感じにしてみました
	//一画面 横 16 マス * 縦 9 マス　で　やってます
	// X方向　画面左端から右に * 数字(マス)
	// Y方向　画面下端から上に * 数字(マス)
	//大きな形ごとに分けるとわかりやすいかも

	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (i >= 31 && i <= 36)
		{
			//-ベルトコンベアブロック32,35 アニメ中心点はここ
			g_Block[i].Patern = 23.0f;
		}

		//余りのブロック
		if (i >= 79 && i <= 125)
		{
			//使わないブロックは当たり判定は取らない
			g_Block[i].use = false;
			g_Block[i].draw_use = false;
		}
	}
	g_Block[0].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 0, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[1].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 1, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[2].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 2, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[3].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 3, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[4].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 4, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[5].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 5, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[6].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 0, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[7].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 1, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[8].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 2, DEFO_SIZE_Y - DRAW_SIZE * 5);

	g_Block[9].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 3, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[10].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 4, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[11].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 5, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_Block[12].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 6, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[13].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 7, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[14].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[15].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 6, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[16].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 9, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[17].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 10, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//反転ブロック
	g_Block[18].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 11, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[18].Patern = 2.0f;
	//段ボールブロック
	g_Block[19].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 12, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[20].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[21].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 14, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[22].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 12, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[23].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[24].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 14, DEFO_SIZE_Y - DRAW_SIZE * 5);
	//青ボタン
	g_Block[25].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 4, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[25].button = true;
	//ここから普通
	g_Block[26].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 16, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[27].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 17, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[28].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 18, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[29].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 19, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[30].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 20, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//-ベルトコンベア//etcで追加せよ32.35
	g_Block[31].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 21, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[32].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 22, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[33].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[34].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 24, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[35].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 25, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[36].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 26, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//ここから普通
	g_Block[37].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 27, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[38].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 28, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[39].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 29, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[40].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 27, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[41].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 28, DEFO_SIZE_Y - DRAW_SIZE * 4);
	//この上に敵
	g_Block[42].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 29, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_Block[43].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 30, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[44].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 31, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//ここから三面
	g_Block[45].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 32, DEFO_SIZE_Y - DRAW_SIZE * 0);
	
	g_Block[46].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 30, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[47].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 31, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[48].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 32, DEFO_SIZE_Y - DRAW_SIZE * 4);
	//段ボール
	g_Block[49].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 26, DEFO_SIZE_Y - DRAW_SIZE * 5);
	//ここから普通
	g_Block[50].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 33, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[51].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 34, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[52].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 35, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[53].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 36, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[54].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 37, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[55].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 38, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//段ボール
	g_Block[56].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 39, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[57].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 39, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[58].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 39, DEFO_SIZE_Y - DRAW_SIZE * 6);
	g_Block[59].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 39, DEFO_SIZE_Y - DRAW_SIZE * 7);
	//koko
	g_Block[60].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 40, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[61].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 41, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//青ボタン
	g_Block[62].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 41, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[62].button = true;
	//ここから普通
	g_Block[63].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 42, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[64].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 40, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[65].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 41, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[66].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 42, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_Block[67].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 43, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[68].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 44, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[69].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 44, DEFO_SIZE_Y - DRAW_SIZE * 1);

	g_Block[70].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 50, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[71].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 51, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[72].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 52, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[73].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 53, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[74].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 54, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[75].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 55, DEFO_SIZE_Y - DRAW_SIZE * 1);

	g_Block[76].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 61, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[77].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 62, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[78].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 63, DEFO_SIZE_Y - DRAW_SIZE * 1);
	
	//移動するブロックについては
	//初期位置を設定後に詳しいことは設定
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		//段
		if (i >= 19 && i <= 24 || i == 49 || i >= 56 && i <= 59)
		{
			g_Block[i].Patern = 25.0f;
			g_Block[i].Speed.x = 0;
			//下の最大値を決定
			g_Block[i].limitmax = g_Block[i].pos.y + (DRAW_SIZE * 4);
		}
		//横に動くやつ
		if (i >= 70 && i <= 75)
		{
			g_Block[i].Patern = 21.0f;
			g_Block[i].Speed.x = (GRAV / 4);
			//左右の最大値を決定
			g_Block[i].limitmax = g_Block[i].pos.x + DRAW_SIZE * 5;
			g_Block[i].limitmin = g_Block[i].pos.x - DRAW_SIZE * 5;
		}
	}
}

void InitStage31()
{
//足場に関しては,ザーッと並べる感じにしてみました
//一画面 横 16 マス * 縦 9 マス　で　やってます
// X方向　画面左端から右に * 数字(マス)
// Y方向　画面下端から上に * 数字(マス)
//大きな形ごとに分けるとわかりやすいかも

	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (i >= 15 && i <= 23 || i >= 38 && i <= 40 || i >= 60 && i <= 62)
		{
			//+ベルトコンベアブロック16,19,22,39,61　アニメ中心点はここ
			g_Block[i].Patern = 22.0f;
		}

		if (i >= 51 && i <= 59)
		{
			//-ベルトコンベアブロック52,55,58 アニメ中心点はここ
			g_Block[i].Patern = 23.0f;
		}

		//余りのブロック
		if (i >= 91 && i <= 125)
		{
			//使わないブロックは当たり判定は取らない
			g_Block[i].use = false;
			g_Block[i].draw_use = false;
		}
	}
	g_Block[0].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 0, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[1].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 1, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[2].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 2, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[3].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 3, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[4].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 4, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[5].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 5, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[6].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 6, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[7].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 7, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[8].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[9].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 9, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[10].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 10, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[11].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 11, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[12].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 12, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[13].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[14].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 14, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//+ベルトコンベア
	g_Block[15].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 6, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[16].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 7, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[17].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 1);

	g_Block[18].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 9, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[19].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 10, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[20].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 11, DEFO_SIZE_Y - DRAW_SIZE * 1);

	g_Block[21].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 12, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[22].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[23].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 14, DEFO_SIZE_Y - DRAW_SIZE * 1);
	//ここから普通
	g_Block[24].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 21, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[25].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 22, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[26].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[27].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[28].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[29].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 6);
	g_Block[30].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[31].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 8);

	g_Block[32].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 24, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[33].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 25, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[34].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 26, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[35].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 27, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[36].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 28, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[37].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 29, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//+ベルトコンベア
	g_Block[38].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 24, DEFO_SIZE_Y - DRAW_SIZE * 4);
	//この上に敵
	g_Block[39].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 25, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[40].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 26, DEFO_SIZE_Y - DRAW_SIZE * 4);
	//普通
	g_Block[41].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 31, DEFO_SIZE_Y - DRAW_SIZE * 3);
	//ここから三面
	g_Block[42].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 32, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[43].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 33, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[44].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 34, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[45].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 35, DEFO_SIZE_Y - DRAW_SIZE * 3);
	//反転
	g_Block[46].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 36, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[46].Patern = 2.0f;
	g_Block[47].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 37, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[48].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 38, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[49].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 39, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[50].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 40, DEFO_SIZE_Y - DRAW_SIZE * 3);
	//-ベルトコンベア
	g_Block[51].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 32, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[52].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 33, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[53].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 34, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[54].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 35, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[55].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 36, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[56].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 37, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[57].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 38, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[58].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 39, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[59].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 40, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//+ベルトコンベア
	g_Block[60].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 44, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[61].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[62].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 46, DEFO_SIZE_Y - DRAW_SIZE * 4);
	//ここから普通
	g_Block[63].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 44, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[64].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[65].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 46, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//青ボタン
	g_Block[66].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 46, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[66].button = true;
	//ここから普通
	g_Block[67].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 47, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[68].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 47, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[69].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 47, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[70].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 47, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[71].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 47, DEFO_SIZE_Y - DRAW_SIZE * 4);
	//この上に敵
	g_Block[72].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 48, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[73].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 49, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[74].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 50, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[75].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 48, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[76].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 49, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[77].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 50, DEFO_SIZE_Y - DRAW_SIZE * 4);
	//この上に敵
	g_Block[78].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 48, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[79].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 49, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[80].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 50, DEFO_SIZE_Y - DRAW_SIZE * 7);

	g_Block[81].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 51, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[82].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 52, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[83].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 53, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[84].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 54, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[85].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 55, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[86].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 56, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[87].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 61, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[88].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 62, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[89].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 63, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[90].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 16, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[90].Patern = 9.0f;
}

void InitStage23()
{
	//足場に関しては,ザーッと並べる感じにしてみました
	//一画面 横 16 マス * 縦 9 マス　で　やってます
	// X方向　画面左端から右に * 数字(マス)
	// Y方向　画面下端から上に * 数字(マス)
	//大きな形ごとに分けるとわかりやすいかも

	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (i >= 13 && i <= 14 || i == 20)
		{
			//サボテンブロック
			g_Block[i].Patern = 15.0f;
		}
		//脆い砂
		if (i >= 22 && i <= 34)
		{
			g_Block[i].Patern = 13.0f;
			g_Block[i].ontime = ONTIME;
		}
		//上下に動くやつ
		if (i >= 52 && i <= 55)
		{
			g_Block[i].Patern = 20.0f;
			g_Block[i].Speed.y = (GRAV / 4);
		}

		//余りのブロック
		if (i >= 56 && i <= 125)
		{
			//使わないブロックは当たり判定は取らない
			g_Block[i].use = false;
			g_Block[i].draw_use = false;
		}
	}
	g_Block[0].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 0, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[1].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 1, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[2].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 2, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[3].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 3, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[4].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 4, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[5].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 5, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[6].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 6, DEFO_SIZE_Y - DRAW_SIZE * 3);
	//赤ボタン
	g_Block[7].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 6, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[7].button = true;
	//間の地形
	g_Block[8].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 11, DEFO_SIZE_Y - DRAW_SIZE * 3);
	//青ボタン
	g_Block[9].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 11, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[9].button = true;
	//ここから普通二面
	g_Block[10].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 16, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[11].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 17, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[12].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 18, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[13].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 27, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[14].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 31, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[15].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 21, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[16].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 22, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[17].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//砂嵐ブロック
	g_Block[18].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 24, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[18].Patern = 17.0f;
	g_Block[19].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 29, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[19].Patern = 17.0f;
	//サボテン
	//この上に敵
	g_Block[20].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 26, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[21].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 34, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//脆い砂
	g_Block[22].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 35, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[23].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 36, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[24].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 37, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[25].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 38, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[26].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 39, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[27].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 40, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[28].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 41, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[29].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 42, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[30].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 43, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[31].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 44, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[32].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[33].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 46, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//この上に敵
	g_Block[34].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 47, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[35].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 48, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//ここから普通
	g_Block[36].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 46, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[37].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 47, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[38].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 48, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_Block[39].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 49, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[40].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 50, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[41].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 51, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_Block[42].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 49, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[43].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 50, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[44].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 51, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[45].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 52, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[46].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 52, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[47].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 59, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[48].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 60, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[49].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 61, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[50].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 62, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[51].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 63, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//動くもの
	g_Block[52].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 54, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[53].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 55, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[54].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 56, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[55].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 57, DEFO_SIZE_Y - DRAW_SIZE * 1);

}

void InitStage22()
{
	//足場に関しては,ザーッと並べる感じにしてみました
	//一画面 横 16 マス * 縦 9 マス　で　やってます
	// X方向　画面左端から右に * 数字(マス)
	// Y方向　画面下端から上に * 数字(マス)
	//大きな形ごとに分けるとわかりやすいかも
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (i >= 21 && i <= 26 || i >= 49 && i <= 51)
		{
			g_Block[i].Patern = 13.0f;
			g_Block[i].ontime = ONTIME;
		}
		//余りのブロック
		if (i >= 88 && i <= 125)
		{
			//使わないブロックは当たり判定は取らない
			g_Block[i].use = false;
			g_Block[i].draw_use = false;
		}
	}
	g_Block[0].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 0, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[1].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 1, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[2].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 2, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[3].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 3, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[4].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 4, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[5].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 5, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[6].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 6, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[7].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 7, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[8].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[9].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 3, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//この上に敵
	g_Block[10].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 4, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[11].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 5, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[12].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 6, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[13].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 7, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[14].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[15].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 9, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[16].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 10, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[17].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 11, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[18].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 12, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//反転ブロック
	g_Block[19].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[19].Patern = 2.0f;
	g_Block[20].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 14, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//ここから脆
	g_Block[21].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 9, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[22].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 10, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[23].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 11, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[24].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 12, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[25].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[26].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 14, DEFO_SIZE_Y - DRAW_SIZE * 3);
	//ここから普通
	g_Block[27].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 16, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[28].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 17, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[29].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 18, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[30].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 19, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[31].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 20, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[32].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 20, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[32].Patern = 15.0f;
	g_Block[33].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[34].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 16, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[35].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 17, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[36].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 18, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[37].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 19, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[38].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 2, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[39].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 3, DEFO_SIZE_Y - DRAW_SIZE * 0);

	//サボテン
	g_Block[40].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 20, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[41].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 20, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[40].Patern = 15.0f;
	g_Block[41].Patern = 15.0f;
	//ここから普通
	g_Block[42].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[43].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 24, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[44].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 25, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[45].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 26, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[46].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 27, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[47].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 28, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[48].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 29, DEFO_SIZE_Y - DRAW_SIZE * 3);
	//ここから脆
	g_Block[49].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 30, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[50].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 31, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[51].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 32, DEFO_SIZE_Y - DRAW_SIZE * 3);
	//ここから砂嵐
	g_Block[52].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 34, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[53].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 35, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[52].Patern = 17.0f;
	g_Block[53].Patern = 17.0f;
	//ここ反転
	g_Block[54].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 38, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[54].Patern = 2.0f;

	g_Block[55].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 39, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[56].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 40, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[57].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 41, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[58].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 42, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[59].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 43, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[60].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 44, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[61].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[62].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[63].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[64].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[65].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_Block[66].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[67].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 46, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[68].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 47, DEFO_SIZE_Y - DRAW_SIZE * 5);

	g_Block[69].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 48, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[70].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 49, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[71].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 50, DEFO_SIZE_Y - DRAW_SIZE * 5);

	g_Block[72].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 51, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[73].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 52, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[74].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 53, DEFO_SIZE_Y - DRAW_SIZE * 5);
	//ここからサボテン
	//この上に敵
	g_Block[75].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 47, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[76].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 49, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[77].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 51, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[78].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 53, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[75].Patern = 15.0f;
	g_Block[76].Patern = 15.0f;
	g_Block[77].Patern = 15.0f;
	g_Block[78].Patern = 15.0f;
	//ここから普通
	g_Block[79].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 55, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[80].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 56, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[81].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 57, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[82].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 58, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[83].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 59, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[84].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 60, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[85].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 61, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[86].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 62, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[87].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 63, DEFO_SIZE_Y - DRAW_SIZE * 0);
}

void InitStage21()
{
	//足場に関しては,ザーッと並べる感じにしてみました
	//一画面 横 16 マス * 縦 9 マス　で　やってます
	// X方向　画面左端から右に * 数字(マス)
	// Y方向　画面下端から上に * 数字(マス)
	//大きな形ごとに分けるとわかりやすいかも
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (i >= 15 && i <= 23 || i >= 80 && i <= 81)
		{
			//サボテンブロック
			g_Block[i].Patern = 15.0f;
		}
		//余りのブロック
		if (i >= 91 && i <= 125)
		{
			//使わないブロックは当たり判定は取らない
			g_Block[i].use = false;
			g_Block[i].draw_use = false;
		}

	}
	g_Block[0].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 0, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[1].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 1, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[2].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 2, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[3].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 3, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[4].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 4, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[5].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 5, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[5].Patern = 13.0f;
	g_Block[5].ontime = ONTIME;

	g_Block[6].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 6, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[7].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 7, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[8].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[9].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 9, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[10].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 10, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[11].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 11, DEFO_SIZE_Y - DRAW_SIZE * 1);

	g_Block[12].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 9, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[13].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 10, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[14].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 11, DEFO_SIZE_Y - DRAW_SIZE * 2);
	//サボテン
	g_Block[15].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[16].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[17].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 17, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[18].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 19, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[19].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 21, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[20].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[21].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 25, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[22].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 27, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[23].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 29, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//ここまで
	g_Block[24].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[25].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 16, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[26].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 17, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[27].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 18, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[28].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 19, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[29].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 20, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[30].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 21, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[31].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 22, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[32].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[33].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[34].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 16, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[35].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 17, DEFO_SIZE_Y - DRAW_SIZE * 7);

	g_Block[36].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 18, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[37].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 19, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[38].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 20, DEFO_SIZE_Y - DRAW_SIZE * 7);

	g_Block[39].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 21, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[40].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 22, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[41].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 7);

	g_Block[42].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 30, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[43].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 31, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[44].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 32, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[45].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 33, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[46].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 34, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[47].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 35, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[48].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 21, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[49].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 22, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[50].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 7);

	g_Block[51].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 24, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[52].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 25, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[53].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 26, DEFO_SIZE_Y - DRAW_SIZE * 7);

	g_Block[54].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 30, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[55].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 31, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[56].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 32, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//ここから三面
	g_Block[57].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 33, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[58].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 34, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[59].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 35, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[60].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 36, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[61].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 37, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//反転ブロック
	g_Block[62].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 37, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[62].Patern = 2.0f;
	g_Block[63].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 38, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[64].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 39, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[65].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 40, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[66].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 41, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[67].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 42, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[68].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 43, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[69].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 44, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//砂嵐ブロック
	g_Block[70].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[70].Patern = 17.0f;

	g_Block[71].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 48, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[72].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 48, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[73].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 48, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[74].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 48, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[75].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 51, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[76].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 52, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//崩れる砂
	g_Block[77].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 49, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[78].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 50, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[79].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 51, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[77].Patern = 13.0f;
	g_Block[78].Patern = 13.0f;
	g_Block[79].Patern = 13.0f;
	g_Block[77].ontime = ONTIME;
	g_Block[78].ontime = ONTIME;
	g_Block[79].ontime = ONTIME;
	//サボテン
	g_Block[80].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 51, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[81].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 52, DEFO_SIZE_Y - DRAW_SIZE * 1);
	//普通
	g_Block[82].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 55, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[83].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 56, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[84].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 57, DEFO_SIZE_Y - DRAW_SIZE * 2);

	g_Block[85].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 58, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[86].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 59, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[87].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 60, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[88].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 61, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[89].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 62, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[90].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 63, DEFO_SIZE_Y - DRAW_SIZE * 4);
}

void InitStage13()
{
	//足場に関しては,ザーッと並べる感じにしてみました
	//一画面 横 16 マス * 縦 9 マス　で　やってます
	// X方向　画面左端から右に * 数字(マス)
	// Y方向　画面下端から上に * 数字(マス)
	//大きな形ごとに分けるとわかりやすいかも
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		//余りのブロック
		if (i >= 56 && i <= 125)
		{
			//使わないブロックは当たり判定は取らない
			g_Block[i].use = false;
			g_Block[i].draw_use = false;
		}
	}
	//この上に犬
	g_Block[0].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 0, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[1].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 1, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[2].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 2, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[3].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 3, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[4].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 4, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[5].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 5, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[6].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 6, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[7].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 7, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[8].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//バネ
	g_Block[9].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[9].Patern = 9.0f;

	g_Block[10].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 12, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[11].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[12].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 14, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[13].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[14].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 16, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[15].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 17, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[16].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 18, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[17].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 16, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[18].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 17, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[19].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 18, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_Block[20].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 19, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[21].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 20, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[22].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 21, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//この上に犬
	g_Block[23].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 19, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[24].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 20, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[25].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 21, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_Block[26].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 22, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[27].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[28].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 24, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[29].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 22, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[30].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[31].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 24, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_Block[32].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 25, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[33].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 26, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[34].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 27, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[35].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 28, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[36].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 29, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[37].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 30, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[38].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 31, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[39].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 32, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[40].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 33, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[41].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 34, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[42].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 35, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[43].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 36, DEFO_SIZE_Y - DRAW_SIZE * 6);
	g_Block[44].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 37, DEFO_SIZE_Y - DRAW_SIZE * 6);
	g_Block[45].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 38, DEFO_SIZE_Y - DRAW_SIZE * 6);
	//この上に犬
	g_Block[46].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 39, DEFO_SIZE_Y - DRAW_SIZE * 6);
	g_Block[47].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 40, DEFO_SIZE_Y - DRAW_SIZE * 6);
	g_Block[48].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 41, DEFO_SIZE_Y - DRAW_SIZE * 6);

	g_Block[49].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 42, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[50].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 43, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[51].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 44, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//ボタン
	g_Block[52].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 57, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[52].button = true;
	//ここから普通
	g_Block[53].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 61, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[54].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 62, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[55].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 63, DEFO_SIZE_Y - DRAW_SIZE * 0);
}

void InitStage12()
{
	//足場に関しては,ザーッと並べる感じにしてみました
	//一画面 横 16 マス * 縦 9 マス　で　やってます
	// X方向　画面左端から右に * 数字(マス)
	// Y方向　画面下端から上に * 数字(マス)
	//大きな形ごとに分けるとわかりやすいかも
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (i >= 10 && i <= 14 || i >= 79 && i <= 83)
		{
			//草がないタイプの床ブロック
			g_Block[i].Patern = 1.0f;
		}
		//余りのブロック
		if (i >= 100 && i <= 125)
		{
			//使わないブロックは当たり判定は取らない
			g_Block[i].use = false;
			g_Block[i].draw_use = false;
		}
	}

	g_Block[0].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 0, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[1].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 1, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[2].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 2, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[3].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 3, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[4].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 4, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//反転ブロック
	g_Block[5].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 5, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[5].Patern = 2.0f;

	g_Block[6].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 6, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[7].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 7, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[8].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[9].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//土
	g_Block[10].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[11].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[12].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 6);
	g_Block[13].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[14].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 8);
	//ここから普通
	g_Block[15].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 9, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[16].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 10, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[17].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 11, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[18].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 9, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[19].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 10, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[20].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 11, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_Block[21].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 12, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[22].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[23].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 14, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[24].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 12, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[25].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[26].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 14, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_Block[27].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[28].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 16, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[29].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 17, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[30].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[31].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 16, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[32].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 17, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_Block[33].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 18, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[34].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 19, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[35].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 20, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[36].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 18, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[37].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 19, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[38].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 20, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_Block[39].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 21, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[40].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 22, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[41].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[42].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 21, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[43].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 22, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[44].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[45].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 24, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[46].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 25, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[47].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 26, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[48].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 24, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[49].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 25, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[50].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 25, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[50].button = true;
	g_Block[51].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 26, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[52].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 30, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[53].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 31, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[54].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 32, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[55].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 33, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[56].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 34, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[57].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 35, DEFO_SIZE_Y - DRAW_SIZE * 1);

	g_Block[58].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 36, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[59].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 37, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[60].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 38, DEFO_SIZE_Y - DRAW_SIZE * 2);

	g_Block[61].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 39, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[62].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 40, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[63].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 41, DEFO_SIZE_Y - DRAW_SIZE * 2);

	g_Block[64].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 42, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[65].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 43, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[66].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 44, DEFO_SIZE_Y - DRAW_SIZE * 2);

	g_Block[67].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[68].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 46, DEFO_SIZE_Y - DRAW_SIZE * 2);
	//反転ブロック
	g_Block[69].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 47, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[69].Patern = 2.0f;
	//ここから普通
	g_Block[70].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[71].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 46, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[72].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 47, DEFO_SIZE_Y - DRAW_SIZE * 7);

	g_Block[73].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 48, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[74].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 49, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[75].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 50, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[76].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 51, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[77].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 52, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[78].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 53, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//土
	g_Block[79].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 53, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[80].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 53, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[81].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 53, DEFO_SIZE_Y - DRAW_SIZE * 6);
	g_Block[82].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 53, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[83].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 53, DEFO_SIZE_Y - DRAW_SIZE * 8);
	//ここから普通
	g_Block[84].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 54, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[85].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 55, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[86].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 56, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//この上に犬
	g_Block[87].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 54, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[88].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 55, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[89].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 56, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_Block[90].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 57, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[91].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 58, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[92].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 59, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[93].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 57, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[94].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 58, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[95].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 59, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_Block[96].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 60, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[97].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 61, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[98].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 62, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[99].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 63, DEFO_SIZE_Y - DRAW_SIZE * 0);
}

void InitStage11()
{
	//足場に関しては,ザーッと並べる感じにしてみました
	//一画面 横 16 マス * 縦 9 マス　で　やってます
	// X方向　画面左端から右に * 数字(マス)
	// Y方向　画面下端から上に * 数字(マス)
	//大きな形ごとに分けるとわかりやすいかも
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (i >= 21 && i <= 29 || i >= 33 && i <= 44 || i >= 74 && i <= 76)
		{
			//草がないタイプの床ブロック
			g_Block[i].Patern = 1.0f;
		}

		if (i >= 92 && i <= 125)
		{
			//使わないブロックは当たり判定と描画は取らない
			g_Block[i].use = false;
			g_Block[i].draw_use = false;
		}
	}
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
	//ここから二面
	g_Block[16].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 16, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[17].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 17, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[18].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 18, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[19].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 19, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[20].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 20, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[21].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[22].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 24, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[23].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 25, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[24].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[25].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 24, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[26].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 25, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[27].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[28].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 24, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[29].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 25, DEFO_SIZE_Y - DRAW_SIZE * 2);

	g_Block[30].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[31].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 24, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[32].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 25, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[33].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 26, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[34].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 27, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[35].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 28, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[36].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 26, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[37].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 27, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[38].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 28, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[39].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 26, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[40].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 27, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[41].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 28, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[42].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 26, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[43].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 27, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[44].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 28, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[45].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 26, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[46].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 27, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[47].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 28, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_Block[48].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 21, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[49].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 22, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[50].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 29, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[51].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 30, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[52].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 31, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//1-1三面難しかったので調整しました
	g_Block[53].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 32, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[54].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 33, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[55].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 34, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[56].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 35, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[57].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 36, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[58].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 37, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[59].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 38, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[60].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 39, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[61].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 40, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[62].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 41, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[63].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 42, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[64].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 43, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_Block[65].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 44, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[66].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[67].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 46, DEFO_SIZE_Y - DRAW_SIZE * 5);

	g_Block[68].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 49, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[69].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 50, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[70].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 51, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[71].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 49, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[72].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 50, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[73].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 51, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[74].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 52, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[75].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 53, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[76].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 54, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//土
	g_Block[77].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 52, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[78].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 53, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[79].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 54, DEFO_SIZE_Y - DRAW_SIZE * 1);

	g_Block[80].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 52, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[81].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 53, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[82].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 54, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[83].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 55, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[84].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 56, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[85].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 57, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[86].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 58, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[87].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 59, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[88].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 60, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[89].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 61, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[90].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 62, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[91].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 63, DEFO_SIZE_Y - DRAW_SIZE * 0);
}