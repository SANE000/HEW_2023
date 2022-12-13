#include "main.h"
#include "blocktype.h"
#include "blockpreview.h"
#include "camera.h"
#include "player.h"
#include "texture.h"
#include "sprite.h"
#include "shop.h"
#include "inputx.h"
#include "keyboard.h"
#include "stageselect.h"
//==========================================
//グローバル変数
//==========================================
static int time = 0;

static PREVIEW_BLOCK g_PreviewBlock[PREVIEW_BLOCK_MAX];
static MOVE_BLOCK g_MoveBlock[MOVE_BLOCK_MAX];
BlockType blocktype[BLOCKTYPE_MAX];

int nexttype = 0;

int use_haveblock_number = 0;
int before_use_haveblock_number = 0;
//設置するブロックの数　blocktypeに応じて変化
int previewblocknum = 0;

//いくつ買ったかを保持する変数
int haveblocknum;
//フィールドを貰ってくる
static int field;
//==========================================
//初期化処理
//==========================================
HRESULT InitPreview()
{
	nexttype = 0;

	use_haveblock_number = 0;
	before_use_haveblock_number = 0;
	field = SetField();

	//射出ブロック初期化
	for (int i = 0; i < MOVE_BLOCK_MAX; i++)
	{
		g_MoveBlock[i].use = false;
		g_MoveBlock[i].pos = D3DXVECTOR2(0, 0);
		g_MoveBlock[i].rot = 0.0f;
		g_MoveBlock[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_MoveBlock[i].texNo = LoadTexture((char*)"data\\texture\\moveblock.png");
		g_MoveBlock[i].type = 1;
		g_MoveBlock[i].Speed.x = 0.0f;
		g_MoveBlock[i].Speed.y = 0.0f;
		g_MoveBlock[i].group = 0;
		g_MoveBlock[i].Patern = field;
	}

	//プレビューブロック初期化
	for (int i = 0; i < PREVIEW_BLOCK_MAX; i++)
	{
		g_PreviewBlock[i].use = false;
		g_PreviewBlock[i].pos = D3DXVECTOR2(0, 0);
		g_PreviewBlock[i].rot = 0.0f;
		g_PreviewBlock[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_PreviewBlock[i].type = 0;
		g_PreviewBlock[i].texNo = LoadTexture((char*)"data\\texture\\cursor_02.png");
	}

	//ブロックタイプの処理の初期化
	for (int i = 0; i < BLOCKTYPE_MAX; i++)
	{
		//何かブロックを買ってたらプラス１する
		if (GetHaveBlock(i) != -1)
		{
			//何個買ってるかを保持する変数
			haveblocknum++;
		}
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
//==========================================
//終了処理
//==========================================
void UnInitPreview()
{
	for (int i = 0; i < BLOCKTYPE_MAX; i++)
	{
		blocktype[i].UninitBlocktype();
	}
}
//==========================================
//更新処理
//==========================================
void UpdatePreview()
{
	//timeが0になるまで毎フレーム減らす
	if (time > 0)
	{
		time -= 1;
	}

	//今現在のブロックタイプを貰う
	int nowblock = blocktype[use_haveblock_number].Gettype();
	int before_use_haveblock_number = use_haveblock_number;

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

				//買ったブロックの個数番目まで調べたら次は0に戻る
				if (use_haveblock_number == haveblocknum)
				{
					use_haveblock_number = 0;
				}

				//一番最初のブロックに戻ってきたら終わる
				if (before_use_haveblock_number == use_haveblock_number)
				{
					break;
				}

			} while (blocktype[use_haveblock_number].GetUse() == true ||
				blocktype[use_haveblock_number].Gettype() == nowblock);	//未使用で現在のブロックと違う種類になるまで進める

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
					use_haveblock_number = (haveblocknum - 1);
				}

				//一番最初のブロックに戻ってきたら終わる
				if (before_use_haveblock_number == use_haveblock_number)
				{
					break;
				}


			} while (blocktype[use_haveblock_number].GetUse() == true ||
				blocktype[use_haveblock_number].Gettype() == nowblock);	//未使用で現在のブロックと違う種類になるまで進める


			time = WAIT_TIME;
		}

		//前フレームと値が変わっていた場合
		if (use_haveblock_number != before_use_haveblock_number)
		{
			FalsePreviewBlock();
			BlockPreview(GetPlayer()->pos);
		}
	}

	//今回のこの変数の値を覚えておく　
	before_use_haveblock_number = use_haveblock_number;

	for (int i = 0; i < MOVE_BLOCK_MAX; i++)
	{
		//まず構造体を使用してるかチェック
		if (g_MoveBlock[i].use == true)
		{
			////座標の更新
			g_MoveBlock[i].pos += g_MoveBlock[i].Speed;
			//画面下まで着いたらスピードを0にして固定する
			if (g_MoveBlock[i].pos.y > (SCREEN_HEIGHT - DRAW_SIZE / 2.0))
			{
				g_MoveBlock[i].Speed.y = 0.0f;
				g_MoveBlock[i].pos.y = (SCREEN_HEIGHT - DRAW_SIZE / 2.0);
			}
		}
	}


	////ランダム生成するブロックの種類の配列を使い切った場合もう一度ランダム生成する
	//if (blocktype[BLOCKTYPE_MAX - 1].GetUse() == true)
	//{
	//	for (int i = 0; i < BLOCKTYPE_MAX; i++)
	//	{
	//		blocktype[i].InitBlocktype();
	//	}
	//}
}
//==========================================
//描画処理
//==========================================
void DrawPreview()
{
	D3DXVECTOR2 basePos = GetBase();

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
				g_MoveBlock[i].Patern,
				1.0f/7.0f,
				1.0f,
				7
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
	for (int i = 0; i < haveblocknum; i++)
	{
		if (blocktype[i].GetUse() == false)
		{
			return true;
		}
	}
	return false;
}
//==========================================
//MOVEブロック射出処理
//==========================================
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
				switch (g_PreviewBlock[b].type)
				{
					//バネブロック
				case 5:
					g_MoveBlock[i].Patern = 3.0f;
					break;
					//爪とぎ
				case 6:
					g_MoveBlock[i].Patern = 6.0f;
					break;
				default:
					break;
				}

				//typeに応じてblockをたくさんつくる
				//発生座標
				g_MoveBlock[i].pos = g_PreviewBlock[b].pos;
				//フラグを使用中にして
				g_MoveBlock[i].use = true;
				g_MoveBlock[i].Speed.y = GRAV;
				g_MoveBlock[i].group = BlockScore();
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
			//買ったブロック個数番目まで調べたら次は0に戻る
			if (use_haveblock_number == haveblocknum)
			{
				use_haveblock_number = 0;
			}
		} while (blocktype[use_haveblock_number].GetUse() == true);

		previewblocknum = 0;

		FalsePreviewBlock();
		BlockPreview(GetPlayer()->pos);

	}
	else
	{
		//使い切ったら当たり判定が残らないように消す
		FalsePreviewBlock();
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

	for (int i = 0; i < PREVIEW_BLOCK_MAX; i++)
	{
		g_PreviewBlock[i].type = nexttype;
	}


	switch (nexttype)
	{
		//ブロックの順番の優先度
		//中心が一番最初　左のほうが優先　上のほうが優先

	case 0:
		//　■
		//■□
		previewblocknum = 3;
		for (int i = 0; i < previewblocknum; i++)
		{
			g_PreviewBlock[i].use = true;
		}

		g_PreviewBlock[0].pos = pos;

		g_PreviewBlock[1].pos = D3DXVECTOR2(pos.x, pos.y - DRAW_SIZE);
		g_PreviewBlock[2].pos = D3DXVECTOR2(pos.x - DRAW_SIZE, pos.y);

		break;

	case 1:
		//■
		//■
		//■

		previewblocknum = 3;
		for (int i = 0; i < previewblocknum; i++)
		{
			g_PreviewBlock[i].use = true;
		}

		g_PreviewBlock[0].pos = pos;

		g_PreviewBlock[1].pos = D3DXVECTOR2(pos.x, pos.y - DRAW_SIZE);
		g_PreviewBlock[2].pos = D3DXVECTOR2(pos.x, pos.y + DRAW_SIZE);

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

		g_PreviewBlock[1].pos = D3DXVECTOR2(pos.x, pos.y - DRAW_SIZE);
		g_PreviewBlock[2].pos = D3DXVECTOR2(pos.x, pos.y + DRAW_SIZE);
		g_PreviewBlock[3].pos = D3DXVECTOR2(pos.x - DRAW_SIZE, pos.y);
		g_PreviewBlock[4].pos = D3DXVECTOR2(pos.x + DRAW_SIZE, pos.y);

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

		g_PreviewBlock[1].pos = D3DXVECTOR2(pos.x, pos.y - DRAW_SIZE);
		g_PreviewBlock[2].pos = D3DXVECTOR2(pos.x - DRAW_SIZE, pos.y - DRAW_SIZE);
		g_PreviewBlock[3].pos = D3DXVECTOR2(pos.x - DRAW_SIZE, pos.y);

		break;

	case 4:
		//□
		previewblocknum = 1;
		g_PreviewBlock[0].use = true;

		g_PreviewBlock[0].pos = pos;

		break;

	case 5:
		//ばねブロック
		previewblocknum = 1;
		g_PreviewBlock[0].use = true;

		g_PreviewBlock[0].pos = pos;

		break;
	case 6:
		//爪とぎブロック
		previewblocknum = 1;
		g_PreviewBlock[0].use = true;

		g_PreviewBlock[0].pos = pos;
		break;


	}

}

void UpdateBlockPreview(D3DXVECTOR2 pos)
{
	//中心のブロックは□で書いておく
	//空中でブロックとブロックがぶつかると当たり判定が発動して止まるためｙ座標は少し放しておくこと <-もう大丈夫！くっつけても動きます
	switch (nexttype)
	{
		//ブロックの順番の優先度
		//中心が一番最初　左のほうが優先　上のほうが優先

	case 0:


		g_PreviewBlock[0].pos = pos;


		//　■
		//■□
		if (g_PreviewBlock[0].rot == 0)
		{
			g_PreviewBlock[1].pos = D3DXVECTOR2(pos.x - DRAW_SIZE, pos.y);
			g_PreviewBlock[2].pos = D3DXVECTOR2(pos.x, pos.y - DRAW_SIZE);
		}
		//■
		//□■
		if (g_PreviewBlock[0].rot == 90)
		{
			g_PreviewBlock[1].pos = D3DXVECTOR2(pos.x, pos.y - DRAW_SIZE);
			g_PreviewBlock[2].pos = D3DXVECTOR2(pos.x + DRAW_SIZE, pos.y);

		}
		//□■
		//■
		if (g_PreviewBlock[0].rot == 180)
		{
			g_PreviewBlock[1].pos = D3DXVECTOR2(pos.x, pos.y + DRAW_SIZE);
			g_PreviewBlock[2].pos = D3DXVECTOR2(pos.x + DRAW_SIZE, pos.y);
		}
		//■□
		//　■
		if (g_PreviewBlock[0].rot == 270)
		{
			g_PreviewBlock[1].pos = D3DXVECTOR2(pos.x - DRAW_SIZE, pos.y);
			g_PreviewBlock[2].pos = D3DXVECTOR2(pos.x, pos.y + DRAW_SIZE);
		}
		break;

	case 1:
		//■
		//□
		//■

		g_PreviewBlock[0].pos = pos;

		if (g_PreviewBlock[0].rot == 0 || g_PreviewBlock[0].rot == 180)
		{
			g_PreviewBlock[1].pos = D3DXVECTOR2(pos.x, pos.y - DRAW_SIZE);
			g_PreviewBlock[2].pos = D3DXVECTOR2(pos.x, pos.y + DRAW_SIZE);
		}
		//■□■
		else if (g_PreviewBlock[0].rot == 90 || g_PreviewBlock[0].rot == 270)
		{
			g_PreviewBlock[1].pos = D3DXVECTOR2(pos.x - DRAW_SIZE, pos.y);
			g_PreviewBlock[2].pos = D3DXVECTOR2(pos.x + DRAW_SIZE, pos.y);
		}

		break;

	case 2:
		//どの角度でも一緒
		g_PreviewBlock[0].pos = pos;

		g_PreviewBlock[1].pos = D3DXVECTOR2(pos.x, pos.y - DRAW_SIZE);
		g_PreviewBlock[2].pos = D3DXVECTOR2(pos.x, pos.y + DRAW_SIZE);
		g_PreviewBlock[3].pos = D3DXVECTOR2(pos.x - DRAW_SIZE, pos.y);
		g_PreviewBlock[4].pos = D3DXVECTOR2(pos.x + DRAW_SIZE, pos.y);

		break;

	case 3:
		//■■
		//■□

		//回転しても形は変わらないが右下が中心のため回転はする
		g_PreviewBlock[0].pos = pos;

		if (g_PreviewBlock[0].rot == 0)
		{
			g_PreviewBlock[1].pos = D3DXVECTOR2(pos.x, pos.y - DRAW_SIZE);
			g_PreviewBlock[2].pos = D3DXVECTOR2(pos.x - DRAW_SIZE, pos.y - DRAW_SIZE);
			g_PreviewBlock[3].pos = D3DXVECTOR2(pos.x - DRAW_SIZE, pos.y);
		}
		//■■
		//□■
		if (g_PreviewBlock[0].rot == 90)
		{
			g_PreviewBlock[1].pos = D3DXVECTOR2(pos.x, pos.y - DRAW_SIZE);
			g_PreviewBlock[2].pos = D3DXVECTOR2(pos.x + DRAW_SIZE, pos.y - DRAW_SIZE);
			g_PreviewBlock[3].pos = D3DXVECTOR2(pos.x + DRAW_SIZE, pos.y);
		}
		//□■
		//■■
		if (g_PreviewBlock[0].rot == 180)
		{
			g_PreviewBlock[1].pos = D3DXVECTOR2(pos.x, pos.y + DRAW_SIZE);
			g_PreviewBlock[2].pos = D3DXVECTOR2(pos.x + DRAW_SIZE, pos.y);
			g_PreviewBlock[3].pos = D3DXVECTOR2(pos.x + DRAW_SIZE, pos.y + DRAW_SIZE);

		}
		//■□
		//■■
		if (g_PreviewBlock[0].rot == 270)
		{
			g_PreviewBlock[1].pos = D3DXVECTOR2(pos.x, pos.y + DRAW_SIZE);
			g_PreviewBlock[2].pos = D3DXVECTOR2(pos.x - DRAW_SIZE, pos.y);
			g_PreviewBlock[3].pos = D3DXVECTOR2(pos.x - DRAW_SIZE, pos.y + DRAW_SIZE);
		}
		break;

	case 4:
		//□　	どの角度でも一緒

		g_PreviewBlock[0].pos = pos;
		break;

	case 5:
		//ばねブロック	//どの角度でも一緒
		//横にはじけるようになってもいいかも
		previewblocknum = 1;
		g_PreviewBlock[0].use = true;

		g_PreviewBlock[0].pos = pos;

		break;
	case 6:
		//爪とぎブロック	//どの角度でも一緒
		previewblocknum = 1;
		g_PreviewBlock[0].use = true;

		g_PreviewBlock[0].pos = pos;
		break;

	}
}

MOVE_BLOCK *GetMoveBlock()
{
	return &g_MoveBlock[0];
}

PREVIEW_BLOCK *GetPreviewBlock()
{
	return g_PreviewBlock;
}