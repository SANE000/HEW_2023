#include "main.h"
#include "block.h"
#include "player.h"
#include "texture.h"
#include "sprite.h"
#include "blocktype.h"
#include "shop.h"
#include "inputx.h"
#include "keyboard.h"
#include "camera.h"

//マクロ定義をヘッダーに移動

//プロトタイプ宣言
void InitStage11();
//==========================================
//グローバル変数
//==========================================
static int time = 0;
//ブロックオブジェクト
//地面や足場の判定に使う

static BLOCK g_Block[BLOCK_MAX];
static MOVE_BLOCK g_MoveBlock[MOVE_BLOCK_MAX];
static PREVIEW_BLOCK g_PreviewBlock[PREVIEW_BLOCK_MAX];

BlockType blocktype[BLOCKTYPE_MAX];

int nexttype = 0;

int use_haveblock_number = 0;
int before_use_haveblock_number = 0;


//設置するブロックの数　blocktypeに応じて変化
int previewblocknum = 0;

HRESULT InitBlock()
{
	nexttype = 0;

	use_haveblock_number = 0;
	before_use_haveblock_number = 0;


	//BLOCK構造体の初期化
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		//テクスチャロード 画像の名前を入れよう
		g_Block[i].texNo = LoadTexture((char*)"data\\texture\\grass_block.png");
	}
	//足場ブロックの設置.一番最後に設定
	InitStage11();
	//射出ブロック初期化
	for (int i = 0; i < MOVE_BLOCK_MAX; i++)
	{
		g_MoveBlock[i].use = false;
		g_MoveBlock[i].pos = D3DXVECTOR2(0, 0);
		g_MoveBlock[i].rot = 0.0f;
		g_MoveBlock[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_MoveBlock[i].texNo = LoadTexture((char*)"data\\texture\\sand_block.png");
		g_MoveBlock[i].type = 1;
		//下にまっすぐ撃つ想定
		g_MoveBlock[i].Speed.x = 0.0f;
		g_MoveBlock[i].Speed.y = 0.0f;
	}
	//プレビューブロック初期化
	for (int i = 0; i < PREVIEW_BLOCK_MAX; i++)
	{
		g_PreviewBlock[i].use = false;
		g_PreviewBlock[i].pos = D3DXVECTOR2(0, 0);
		g_PreviewBlock[i].rot = 0.0f;
		g_PreviewBlock[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_PreviewBlock[i].texNo = LoadTexture((char*)"data\\texture\\cursor_02.png");

	}

	//ブロックタイプの処理の初期化
	for (int i = 0; i < BLOCKTYPE_MAX; i++)
	{
		blocktype[i].SetType(GetHaveBlock(i));
		//blocktype[i].InitBlocktype();
	}

	for (int i = 0; i < BLOCKTYPE_MAX; i++)
	{
		blocktype[i].ChangeUse(false);

		//-1の時はブロックを買っていないため使用フラグをtrueにして使えなくする
		if (blocktype[i].Gettype() == -1)
		{
			blocktype[i].ChangeUse(true);
		}
		
	}
	
	BlockPreview(GetPlayer()->pos);

	return S_OK;
}
//終了処理
void UnInitBlock()
{
	for (int i = 0; i < BLOCKTYPE_MAX; i++)
	{
		blocktype[i].UninitBlocktype();
	}
}
//更新処理
void UpdateBlock()
{
	if (time > 0)
	{
		time -= 1;
	}

	if (FalseExistCheck() == true)
	{
		if (Keyboard_IsKeyDown(KK_RIGHT) && time <= 0 || IsButtonTriggered(0, XINPUT_GAMEPAD_RIGHT_SHOULDER) && time <= 0)
		{//右
			//コメント書くのムズイので処理の内容が分からない場合實吉まで聞きに来てください。申し訳ない分かりづれぇ

			//使うブロックを変える　配列の一個次のブロックを使う
			//もし次のブロックがすでに使用済みだったら使用済みじゃなくなるまで進める
			do
			{
				use_haveblock_number++;
				//255番目まで調べたら次は0に戻る
				if (use_haveblock_number == BLOCKTYPE_MAX)
				{
					use_haveblock_number = 0;
				}
			} while (blocktype[use_haveblock_number].GetUse() == true);

			////-1の場合はブロックを買ってないため、先頭に戻る
			//if (blocktype[use_haveblock_number].Gettype() == -1)
			//{
			//	use_haveblock_number = 0;
			//	for (int i = 0; i < BLOCKTYPE_MAX; i++)
			//	{
			//		//まだ使ってなくてブロックを買っている配列番号ならよし
			//		if (blocktype[use_haveblock_number].Gettype() != -1 && blocktype[use_haveblock_number].GetUse() == false)
			//		{
			//			break;
			//		}
			//		use_haveblock_number++;
			//	}

			//}
			time = WAIT_TIME;
		}
		else if (Keyboard_IsKeyDown(KK_LEFT) && time <= 0 || IsButtonTriggered(0, XINPUT_GAMEPAD_LEFT_SHOULDER) && time <= 0)
		{//左
			//使うブロックを変える　配列の一個前のブロックを使う
			//もし前のブロックがすでに使用済みだったら使用済みじゃなくなるまで戻る
			do
			{
				use_haveblock_number--;
				//0番目から戻ると一番後ろに進む
				if (use_haveblock_number < 0)
				{
					use_haveblock_number = (BLOCKTYPE_MAX - 1);
				}
			} while (blocktype[use_haveblock_number].GetUse() == true);

			
			time = WAIT_TIME;
		}

		//前フレームと値が変わっていた場合
		if (use_haveblock_number != before_use_haveblock_number)
		{
			FalsePreviewBlock();
			BlockPreview(GetPlayer()->pos);
		}

		UpdateBlockPreview(GetPlayer()->pos);
	}
	


	////ランダム生成するブロックの種類の配列を使い切った場合もう一度ランダム生成する
	//if (blocktype[BLOCKTYPE_MAX - 1].GetUse() == true)
	//{
	//	for (int i = 0; i < BLOCKTYPE_MAX; i++)
	//	{
	//		blocktype[i].InitBlocktype();
	//	}
	//}
	

	for (int i = 0; i < MOVE_BLOCK_MAX; i++)
	{
		//まず構造体を使用してるかチェック
		if (g_MoveBlock[i].use == true)
		{
			////座標の更新
			g_MoveBlock[i].pos += g_MoveBlock[i].Speed;
			//画面下まで着いたらスピードを0にして固定する
			if (g_MoveBlock[i].pos.y > (SCREEN_HEIGHT - DRAW_SIZE/ 2.0))
			{
				g_MoveBlock[i].Speed.y = 0.0f;
				g_MoveBlock[i].pos.y = (SCREEN_HEIGHT - DRAW_SIZE / 2.0);
			}
		}
	}


	//今回のこの変数の値を覚えておく　
	before_use_haveblock_number = use_haveblock_number;

}
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
			BASE_DRAW_SIZE,
			DRAW_SIZE,
			g_Block[i].rot,
			g_Block[i].col,
			g_Block[i].Patern,
			3.0f,
			1.0f,
			1
			);
		}
	}
	//射出されるブロック
	for (int i = 0; i < MOVE_BLOCK_MAX; i++)
	{
		if (g_MoveBlock[i].use == true)
		{
			//テクスチャのセット
			GetDeviceContext()->PSSetShaderResources
			(0, 1, GetTexture(g_MoveBlock[i].texNo));
			//スプライトの描画

			//typeごとに数や配置を変える
			DrawSpriteColorRotate
			(
				basePos.x + g_MoveBlock[i].pos.x,
				basePos.y + g_MoveBlock[i].pos.y,
				DRAW_SIZE,
				DRAW_SIZE,
				g_MoveBlock[i].rot,
				g_MoveBlock[i].col,
				0,
				1.0f,
				1.0f,
				1
			);
		}
	}

	if (FalseExistCheck() == true)
	{
		//プレビューブロック
		for (int i = 0; i < PREVIEW_BLOCK_MAX; i++)
		{
			if (g_PreviewBlock[i].use == true)
			{
				//テクスチャのセット
				GetDeviceContext()->PSSetShaderResources
				(0, 1, GetTexture(g_PreviewBlock[i].texNo));
				//スプライトの描画

				//typeごとに数や配置を変える
				DrawSpriteColorRotate
				(
					basePos.x + g_PreviewBlock[i].pos.x,
					basePos.y + g_PreviewBlock[i].pos.y,
					DRAW_SIZE,
					DRAW_SIZE,
					0.0f,
					g_PreviewBlock[i].col,
					0,
					1.0f,
					1.0f,
					1
				);
			}
		}
	}
	
}
//構造体の先頭ポインタを返す　皆が使えるように
BLOCK *GetBlock()
{
	return &g_Block[0];
}
MOVE_BLOCK *GetMoveBlock()
{
	return &g_MoveBlock[0];
}
PREVIEW_BLOCK *GetPreviewBlock()
{
	return g_PreviewBlock;
}

void SetMoveBlock()
{
	for (int b = 0; b < previewblocknum; b++)
	{
		//構造体を全て調べる
		for (int i = 0; i < MOVE_BLOCK_MAX; i++)
		{
			//弾が無いとこを見つける
			if (g_MoveBlock[i].use == false)
			{
				//typeに応じてblockをたくさんつくる
				//発生座標
				g_MoveBlock[i].pos = g_PreviewBlock[b].pos;
				//フラグを使用中にして
				g_MoveBlock[i].use = true;
				g_MoveBlock[i].Speed.y = GRAV;
				////サウンド再生
				//PlaySound(BulletSoundNo, 0);
				//1つ作ったら終わり！
				break;
			}
		}
	}
	
		
	//使用済みにする
	blocktype[use_haveblock_number].ChangeUse(true);

	if (FalseExistCheck() == true)
	{
		//使用済みにした番号を使えないように番号を進める
		do
		{
			use_haveblock_number++;
			//255番目まで調べたら次は0に戻る
			if (use_haveblock_number == BLOCKTYPE_MAX)
			{
				use_haveblock_number = 0;
			}
		} while (blocktype[use_haveblock_number].GetUse() == true);

		previewblocknum = 0;

		FalsePreviewBlock();
		BlockPreview(GetPlayer()->pos);

	}
	

	
	/*previewblocknum = 0;

	FalsePreviewBlock();
	BlockPreview(GetPlayer()->pos);*/

	
}

//ブロックの設置プレビュー
void BlockPreview(D3DXVECTOR2 pos)
{
	//プレビューはuseがtrueならdrawするようにしたい
	//setblockの最後で全部falseにする?
	
	//updateでボタンが押されたらrotが変化する
	//rotに応じてブロックが回転するような処理を入れたい

	//次のタイプを取得
	nexttype = blocktype[use_haveblock_number].Gettype();
		

	switch (nexttype)
	{
		//ブロックの順番の優先度
		//中心が一番最初　左のほうが優先　上のほうが優先

	case 0:
		//■■■
		//　　■
		previewblocknum = 4;
		for (int i = 0; i < previewblocknum; i++)
		{
			g_PreviewBlock[i].use = true;
		}

		g_PreviewBlock[0].pos = pos;

		g_PreviewBlock[1].pos = D3DXVECTOR2(pos.x - SIZE, pos.y);
		g_PreviewBlock[2].pos = D3DXVECTOR2(pos.x + SIZE, pos.y);
		g_PreviewBlock[3].pos = D3DXVECTOR2(pos.x + SIZE, pos.y + SIZE + GRAV);
	
		break;

	case 1:
		//■
		//■
		//■
		//■
		//■

		previewblocknum = 5;
		for (int i = 0; i < previewblocknum; i++)
		{
			g_PreviewBlock[i].use = true;
		}

		g_PreviewBlock[0].pos = pos;

		g_PreviewBlock[1].pos = D3DXVECTOR2(pos.x , pos.y - SIZE * 2 - 5);
		g_PreviewBlock[2].pos = D3DXVECTOR2(pos.x , pos.y - SIZE - GRAV);
		g_PreviewBlock[3].pos = D3DXVECTOR2(pos.x , pos.y + SIZE + GRAV);
		g_PreviewBlock[4].pos = D3DXVECTOR2(pos.x, pos.y + SIZE * 2 + 5);

		break;

	case 2:
		//　■
		//■■■
		//　■

		previewblocknum = 5;
		for (int i = 0; i < previewblocknum; i++)
		{
			g_PreviewBlock[i].use = true;
		}

		g_PreviewBlock[0].pos = pos;

		g_PreviewBlock[1].pos = D3DXVECTOR2(pos.x, pos.y - SIZE - GRAV);
		g_PreviewBlock[2].pos = D3DXVECTOR2(pos.x, pos.y + SIZE + GRAV);
		g_PreviewBlock[3].pos = D3DXVECTOR2(pos.x - SIZE, pos.y);
		g_PreviewBlock[4].pos = D3DXVECTOR2(pos.x + SIZE, pos.y);

		break;

	case 3:
		//■■
		//■■ //右下が中心とする

		previewblocknum = 4;
		for (int i = 0; i < previewblocknum; i++)
		{
			g_PreviewBlock[i].use = true;
		}

		g_PreviewBlock[0].pos = pos;

		g_PreviewBlock[1].pos = D3DXVECTOR2(pos.x, pos.y - SIZE - GRAV);
		g_PreviewBlock[2].pos = D3DXVECTOR2(pos.x - SIZE, pos.y - SIZE - 1);
		g_PreviewBlock[3].pos = D3DXVECTOR2(pos.x - SIZE, pos.y);
		
		break;

	case 4:
		//□
		previewblocknum = 1;
		g_PreviewBlock[0].use = true;

		g_PreviewBlock[0].pos = pos;

		break;

	}
	
}

void UpdateBlockPreview(D3DXVECTOR2 pos)
{
	//中心のブロックは□で書いておく
	//空中でブロックとブロックがぶつかると当たり判定が発動して止まるためｙ座標は少し放しておくこと
	switch (nexttype)
	{
		//ブロックの順番の優先度
		//中心が一番最初　左のほうが優先　上のほうが優先

	case 0:
		//■□■
		//　　■

		g_PreviewBlock[0].pos = pos;

		if (g_PreviewBlock[0].rot == 0)
		{
			g_PreviewBlock[1].pos = D3DXVECTOR2(pos.x - SIZE, pos.y);
			g_PreviewBlock[2].pos = D3DXVECTOR2(pos.x + SIZE, pos.y);
			g_PreviewBlock[3].pos = D3DXVECTOR2(pos.x + SIZE, pos.y + SIZE + GRAV);
		}
		//　■
		//　□
		//■■
		if (g_PreviewBlock[0].rot == 90)
		{
			g_PreviewBlock[1].pos = D3DXVECTOR2(pos.x, pos.y - SIZE - GRAV);
			g_PreviewBlock[2].pos = D3DXVECTOR2(pos.x, pos.y + SIZE + GRAV);
			g_PreviewBlock[3].pos = D3DXVECTOR2(pos.x - SIZE, pos.y + SIZE + GRAV);
		}
		//■
		//■□■
		if (g_PreviewBlock[0].rot == 180)
		{
			g_PreviewBlock[1].pos = D3DXVECTOR2(pos.x - SIZE, pos.y - SIZE - GRAV);
			g_PreviewBlock[2].pos = D3DXVECTOR2(pos.x - SIZE, pos.y);
			g_PreviewBlock[3].pos = D3DXVECTOR2(pos.x + SIZE, pos.y);

		}
		//■■
		//□
		//■
		if (g_PreviewBlock[0].rot == 270)
		{
			g_PreviewBlock[1].pos = D3DXVECTOR2(pos.x, pos.y - SIZE - GRAV);
			g_PreviewBlock[2].pos = D3DXVECTOR2(pos.x, pos.y + SIZE + GRAV);
			g_PreviewBlock[3].pos = D3DXVECTOR2(pos.x + SIZE, pos.y - SIZE - GRAV);
		}
		break;

	case 1:
		//■
		//■
		//□
		//■
		//■

		g_PreviewBlock[0].pos = pos;

		if (g_PreviewBlock[0].rot == 0 || g_PreviewBlock[0].rot == 180)
		{
			g_PreviewBlock[1].pos = D3DXVECTOR2(pos.x, pos.y - SIZE * 2 - 5);
			g_PreviewBlock[2].pos = D3DXVECTOR2(pos.x, pos.y - SIZE - GRAV);
			g_PreviewBlock[3].pos = D3DXVECTOR2(pos.x, pos.y + SIZE + GRAV);
			g_PreviewBlock[4].pos = D3DXVECTOR2(pos.x, pos.y + SIZE * 2 + 5);
		}
		//■■□■■
		else if (g_PreviewBlock[0].rot == 90 || g_PreviewBlock[0].rot == 270)
		{
			g_PreviewBlock[1].pos = D3DXVECTOR2(pos.x - SIZE * 2, pos.y );
			g_PreviewBlock[2].pos = D3DXVECTOR2(pos.x - SIZE, pos.y);
			g_PreviewBlock[3].pos = D3DXVECTOR2(pos.x + SIZE, pos.y );
			g_PreviewBlock[4].pos = D3DXVECTOR2(pos.x + SIZE * 2, pos.y );
		}

		break;

	case 2:
		//どの角度でも一緒
		g_PreviewBlock[0].pos = pos;

		g_PreviewBlock[1].pos = D3DXVECTOR2(pos.x, pos.y - SIZE - GRAV);
		g_PreviewBlock[2].pos = D3DXVECTOR2(pos.x, pos.y + SIZE + GRAV);
		g_PreviewBlock[3].pos = D3DXVECTOR2(pos.x - SIZE, pos.y);
		g_PreviewBlock[4].pos = D3DXVECTOR2(pos.x + SIZE, pos.y);
		
		break;

	case 3:	
		//■■
		//■□

		//回転しても形は変わらないが右下が中心のため回転はする
		g_PreviewBlock[0].pos = pos;

		if (g_PreviewBlock[0].rot == 0)
		{
			g_PreviewBlock[1].pos = D3DXVECTOR2(pos.x, pos.y - SIZE - GRAV);
			g_PreviewBlock[2].pos = D3DXVECTOR2(pos.x - SIZE, pos.y - SIZE - GRAV);
			g_PreviewBlock[3].pos = D3DXVECTOR2(pos.x - SIZE, pos.y);
		}
		//■■
		//□■
		if (g_PreviewBlock[0].rot == 90)
		{
			g_PreviewBlock[1].pos = D3DXVECTOR2(pos.x, pos.y - SIZE - GRAV);
			g_PreviewBlock[2].pos = D3DXVECTOR2(pos.x + SIZE, pos.y - SIZE - GRAV);
			g_PreviewBlock[3].pos = D3DXVECTOR2(pos.x + SIZE, pos.y );
		}
		//□■
		//■■
		if (g_PreviewBlock[0].rot == 180)
		{
			g_PreviewBlock[1].pos = D3DXVECTOR2(pos.x , pos.y + SIZE + GRAV);
			g_PreviewBlock[2].pos = D3DXVECTOR2(pos.x + SIZE, pos.y);
			g_PreviewBlock[3].pos = D3DXVECTOR2(pos.x + SIZE, pos.y + SIZE + GRAV);

		}
		//■□
		//■■
		if (g_PreviewBlock[0].rot == 270)
		{
			g_PreviewBlock[1].pos = D3DXVECTOR2(pos.x, pos.y + SIZE + GRAV);
			g_PreviewBlock[2].pos = D3DXVECTOR2(pos.x - SIZE, pos.y );
			g_PreviewBlock[3].pos = D3DXVECTOR2(pos.x - SIZE, pos.y + SIZE + GRAV);
		}
		break;
	
	case 4:
		//□　	どの角度でも一緒

		g_PreviewBlock[0].pos = pos;
		break;
	}
}


//全部の使用フラグをfalseにする
void FalsePreviewBlock()
{
	for (int i = 0; i < PREVIEW_BLOCK_MAX; i++)
	{
		g_PreviewBlock[i].use = false;
		g_PreviewBlock[i].rot = 0;
	}
}

//falseが存在するかどうかチェックする	全部trueの時は買ったブロックを使い切ったということになる
bool FalseExistCheck()
{
	for (int i = 0; i < BLOCKTYPE_MAX; i++)
	{
		if (blocktype[i].GetUse() == false)
		{
			return true;
		}
	}

	return false;
}

void InitStage11()
{
	//足場に関しては,ザーッと並べる感じにする
//DRAW_SIZEをかけた分一マスずつずれていく
//大きな形ごとに分けるとわかりやすいかも
	g_Block[0].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 0, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[1].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 1, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[2].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 2, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[3].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 3, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[4].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 4, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[5].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 5, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[6].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 6, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[7].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 7, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[8].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 7, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[9].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 7, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[10].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 7, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[11].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[12].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[13].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[14].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[15].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_Block[16].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 9, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[17].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 10, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[18].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 11, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[19].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[20].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 14, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[21].pos = D3DXVECTOR2(BASE_DEFO_SIZE_X + BASE_DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 0);
}
