#include "main.h"
#include "block.h"
#include "shop.h"
#include "texture.h"
#include "sprite.h"
#include "camera.h"

//プロトタイプ宣言
void InitStage11();
void InitStage12();
//==========================================
//グローバル変数
//==========================================
//偵察用
static double map_pos = 0;
//地面や足場の判定に使う
static BLOCK g_Block[BLOCK_MAX];
//==========================================
//ステージ選ぶ変数
//==========================================

//ステージ選択テスト用なので手動で選ぶ。
//ステージ選択画面ができたら消しちゃってください
static int stage = 1;
//stage = 0 が stage11(), それ以外がstage12()が選ばれるようになっています

//ブロックもガワだけ変えたボタンと反転ブロックは設置しましたが中身の機能は
//なにもやってないので担当者さん機能実装よろしくお願いします！

HRESULT InitBlock()
{
	//BLOCK構造体の初期化
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		//テクスチャロード 画像の名前を入れよう
		g_Block[i].texNo = LoadTexture((char*)"data\\texture\\block.png");
	}
	//ステージテスト
	if (stage == 0)
	{
		//足場ブロックの設置.一番最後に設定
		InitStage11();
	}
	else
	{
		InitStage12();
	}
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
	//マップボタンが押されたら
	if (WatchMapFlag() == true)
	{//画面端になるまで座標を引いていく
		if (map_pos <= -SCREEN_WIDTH * 5)
		{
			//画面端になったら止める
			map_pos += 0;
		}
		else
		{
			map_pos -= WATCH;
		}
	}
	else
	{
		//マップボタンが押されてないなら0にする
		map_pos = 0;
	}
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
			//ブロックによってパターンの変更
			//パターンによって効果があってもいいかも
			//stage11では
			//21~29 or 33~44 or 108~110は表面では無い方へ変更
			//stage12では
			if (stage == 0)
			{
				if (i >= 21 && i <= 29 || i >= 33 && i <= 44 || i >= 108 && i <= 110)
				{
					//草がないタイプの床ブロック
					g_Block[i].Patern = 1.0f;
				}
				else
				{
					//草あり
					g_Block[i].Patern = 0.0f;
				}
			}
			else
			{
				if (i >= 9 && i <= 14 || i >= 67 && i <= 69 || i >= 102 && i <= 106)
				{
					//草がないタイプの床ブロック
					g_Block[i].Patern = 1.0f;
				}
				else if(i == 73 || i == 86)
				{
					//反転ブロック
					g_Block[i].Patern = 2.0f;
				}
				else if (i == 54)
				{
					//ボタンブロック
					g_Block[i].Patern = 3.0f;
				}
				else
				{
					//草あり
					g_Block[i].Patern = 0.0f;
				}
			}
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
			1.0f/7.0f,//横
			1.0f,//縦
			7//総枚数
			);
		}
	}	
}
//構造体の先頭ポインタを返す　皆が使えるように
BLOCK *GetBlock()
{
	return &g_Block[0];
}
void InitStage12()
{
	//足場に関しては,ザーッと並べる感じにしてみました
	//一画面 横 16 マス * 縦 9 マス　で　やってます
	// X方向　画面左端から右に * 数字(マス)
	// Y方向　画面下端から上に * 数字(マス)
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
	//土
	g_Block[9].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[10].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[11].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[12].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 6);
	g_Block[13].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[14].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 8);
	//ここから普通
	g_Block[15].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 9, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[16].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 10, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[17].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 11, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[18].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 9, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[19].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 10, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[20].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 11, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[21].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 12, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[22].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[23].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 14, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[24].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 12, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[25].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[26].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 14, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[27].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[28].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 16, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[29].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 17, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[30].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 18, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[31].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 19, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[32].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 20, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[33].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 27, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[34].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 28, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[35].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 29, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[36].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 30, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[37].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 31, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[38].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 32, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[39].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 33, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[40].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 34, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[41].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 35, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[42].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 36, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[43].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 37, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[44].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 38, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[45].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 36, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[46].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 37, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[47].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 38, DEFO_SIZE_Y - DRAW_SIZE * 2);

	g_Block[48].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 39, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[49].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 40, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[50].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 41, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[51].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 39, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[52].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 40, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[53].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 41, DEFO_SIZE_Y - DRAW_SIZE * 2);
	//ボタン
	g_Block[54].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 40, DEFO_SIZE_Y - DRAW_SIZE * 3);
	//ここから普通
	g_Block[55].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[56].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 46, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[57].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 47, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[58].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 48, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[59].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 49, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[60].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 50, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[61].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 51, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[62].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 52, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[63].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 53, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[64].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 54, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[65].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 55, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[66].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 56, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//土
	g_Block[67].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 57, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[68].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 58, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[69].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 59, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//ここから普通
	g_Block[70].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 57, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[71].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 58, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[72].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 59, DEFO_SIZE_Y - DRAW_SIZE * 1);
	//反転ブロック
	g_Block[73].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 59, DEFO_SIZE_Y - DRAW_SIZE * 5);
	//ここから普通
	g_Block[74].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 60, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[75].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 61, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[76].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 62, DEFO_SIZE_Y - DRAW_SIZE * 2);

	g_Block[77].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 60, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[78].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 61, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[79].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 62, DEFO_SIZE_Y - DRAW_SIZE * 5);

	g_Block[80].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 63, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[81].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 64, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[82].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 65, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[83].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 66, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[84].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 67, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[85].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 68, DEFO_SIZE_Y - DRAW_SIZE * 2);
	//反転ブロック
	g_Block[86].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 69, DEFO_SIZE_Y - DRAW_SIZE * 2);
	//ここから普通
	g_Block[87].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 69, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[88].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 70, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[89].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 71, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[90].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 72, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[91].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 73, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[92].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 74, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[93].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 75, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[94].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 76, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[95].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 77, DEFO_SIZE_Y - DRAW_SIZE * 5);

	g_Block[96].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 78, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[97].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 79, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[98].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 80, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[99].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 81, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[100].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 82, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[101].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 83, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//土
	g_Block[102].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 83, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[103].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 83, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[104].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 83, DEFO_SIZE_Y - DRAW_SIZE * 6);
	g_Block[105].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 83, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[106].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 83, DEFO_SIZE_Y - DRAW_SIZE * 8);
	//ここから普通
	g_Block[107].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 84, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[108].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 85, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[109].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 86, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[110].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 84, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[111].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 85, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[112].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 86, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_Block[113].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 87, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[114].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 88, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[115].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 89, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[116].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 87, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[117].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 88, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[118].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 89, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_Block[119].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 90, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[120].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 91, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[121].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 92, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[122].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 93, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[123].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 94, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[124].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 95, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//ブロック余り自由に使ってください
	g_Block[125].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 95, DEFO_SIZE_Y - DRAW_SIZE * 0);
}

void InitStage11()
{
	//足場に関しては,ザーッと並べる感じにしてみました
	//一画面 横 16 マス * 縦 9 マス　で　やってます
	// X方向　画面左端から右に * 数字(マス)
	// Y方向　画面下端から上に * 数字(マス)
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
	
	g_Block[66].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 48, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[67].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 49, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[68].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 50, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[69].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 51, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[70].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 52, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[71].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 53, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[72].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 54, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[73].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 55, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[74].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 56, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[75].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 57, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[76].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 58, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[77].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 59, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[78].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 60, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[79].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 61, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[80].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 62, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[81].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 63, DEFO_SIZE_Y - DRAW_SIZE * 6);
	g_Block[82].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 64, DEFO_SIZE_Y - DRAW_SIZE * 6);
	g_Block[83].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 65, DEFO_SIZE_Y - DRAW_SIZE * 6);

	g_Block[84].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 69, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[85].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 70, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[86].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 71, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[87].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 72, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[88].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 73, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[89].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 74, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[90].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 75, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[91].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 76, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[92].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 77, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[93].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 75, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[94].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 76, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[95].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 77, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[96].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 78, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[97].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 79, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[98].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 80, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[99].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 78, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[100].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 79, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[101].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 80, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[102].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 81, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[103].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 82, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[104].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 83, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[105].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 81, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[106].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 82, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[107].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 83, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[108].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 84, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[109].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 85, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[110].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 86, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[111].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 84, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[112].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 85, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[113].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 86, DEFO_SIZE_Y - DRAW_SIZE * 1);

	g_Block[114].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 84, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[115].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 85, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[116].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 86, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[117].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 87, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[118].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 88, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[119].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 89, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[120].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 90, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[121].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 91, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[122].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 92, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[123].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 93, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[124].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 94, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[125].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 95, DEFO_SIZE_Y - DRAW_SIZE * 0);
}

