#include "cat.h"
#include "main.h"
#include "blockpreview.h"
#include "inputx.h"
#include "texture.h"
#include "sprite.h"
#include "Scene.h"
#include "sound.h"
#include "collision.h"
#include "camera.h"
#include "jumpflag.h"	


//グローバル変数
//int JumpSoundNo = 0;

//爪とぎの秒数を知るため	
int tumetogi_count = 0;

//プレイヤーオブジェクト
static CAT g_Cat;
static MOVE_BLOCK *m_block = GetMoveBlock();

HRESULT InitCat()
{
	//テクスチャロード 画像の名前を入れよう
	g_Cat.texNo = LoadTexture((char*)"data\\texture\\cat.png");
	//構造体の初期化
	g_Cat.pos.x = DEFO_SIZE_X;
	g_Cat.pos.y = CAT_INIT_Y;
	g_Cat.dir.x = WALK;
	g_Cat.move_flag = false;
	g_Cat.jump_flag = false;
	g_Cat.tumetogi_flag = false;
	g_Cat.jump_y = 0.0f;
	g_Cat.limit_jump = 0.0f;
	g_Cat.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Cat.patern = 0.0f;
	g_Cat.half_flag = false;
	g_Cat.goal_flag = false;
	//使用中フラグをオンにする
	g_Cat.use = true;

	g_Cat.nowjump_flag = 0;

	//サウンドのロード
	//char filename[] = "data\\SE\\boyoyon.wav";
	//JumpSoundNo = LoadSound(filename);
	//HRESULTに値を返して正常終了したことを連絡する
	return S_OK;
}
//終了処理
void UnInitCat()
{

}
//更新処理
void UpdateCat()
{
	//空中に浮いているときだけ重力の影響
	if (g_Cat.jump_flag == false)
	{
		g_Cat.pos.y += GRAV;
	}
	//右に向かって進んでいるとき
	if (g_Cat.move_flag == false)
	{

		//地面についているとき
		if (g_Cat.jump_flag == true)
		{
			//猫アニメーションパターン管理
			g_Cat.patern += 0.04f;

			//爪とぎアニメーション 右
			if (g_Cat.tumetogi_flag == true)
			{
				if (g_Cat.patern < 4.0f)
				{
					g_Cat.patern = 4.0f;
				}

				tumetogi_count++;


				if (g_Cat.patern > 6.0f)
				{
					g_Cat.patern = 4.0f;
				}
			}
			else
			{

				//右に向かって歩く猫アニメ
				if (g_Cat.patern > 1.9f)
				{
					g_Cat.patern = 0.0f;
				}
				else if (g_Cat.patern > 2.0f)
				{
					g_Cat.patern = 0.0f;
				}

			}

		}
		else
		{
			//猫アニメーションパターン管理
			g_Cat.patern += 0.20f;

			//ジャンプパワーが0以上だったら　
			if (g_Cat.jump_y > 0.0f)
			{

				//ジャンプ猫アニメ　右
				if (g_Cat.patern > 10.0f)
				{
					g_Cat.patern = 9.0f;
				}
			}
			else
			{
				//落ちる猫アニメ　右
				g_Cat.patern = 10.0f;

			}
		}
	}
	//左に向かって進んでいるとき
	else
	{
		g_Cat.patern += 0.04f;

		//地面についているとき
		if (g_Cat.jump_flag == true)
		{
			//爪とぎアニメーション 左
			if (g_Cat.tumetogi_flag == true)
			{
				tumetogi_count++;

				if (g_Cat.patern > 8.0f)
				{
					g_Cat.patern = 6.0f;
				}
			}
			//左に向かって歩く猫アニメ
			else if (g_Cat.patern > 4.0f)
			{

				g_Cat.patern = 2.0f;
			}
			else if (g_Cat.patern < 2.0f)
			{
				g_Cat.patern = 2.0f;
			}
		}
		else
		{
			//猫アニメーションパターン管理
			g_Cat.patern += 0.20f;

			//ジャンプパワーが0以上だったら　
			if (g_Cat.jump_y > 0.0f)
			{

				//ジャンプ猫アニメ　左
				if (g_Cat.patern > 13.0f)
				{
					g_Cat.patern = 12.0f;
				}
			}
			else
			{
				//落ちる猫アニメ　左
				g_Cat.patern = 13.0f;

			}


		}

	}

	if (tumetogi_count > 180 && g_Cat.tumetogi_flag == true)
	{
		g_Cat.tumetogi_flag = false;
	}

	//爪とぎ中は進まない
	if (g_Cat.tumetogi_flag == false)
	{
		if (tumetogi_count > 0)
			tumetogi_count = 0;

		//自動で移動(壁にぶつかるor初期値まで戻ったら反転)
		if (g_Cat.move_flag == false)
		{
			//同じタイミングでジャンプが始まるため、飛ぶ段数に応じて飛んでる最中はX方面の移動を遅くする
			if (g_Cat.nowjump_flag > 0)
			{
				g_Cat.pos.x += g_Cat.dir.x / g_Cat.nowjump_flag;
			}
			else
			{
				g_Cat.pos.x += g_Cat.dir.x;
			}
		}
		else
		{
			//同じタイミングでジャンプが始まるため、飛ぶ段数に応じて飛んでる最中はX方面の移動を遅くする
			if (g_Cat.nowjump_flag > 0)
			{
				g_Cat.pos.x += g_Cat.dir.x / g_Cat.nowjump_flag;
			}
			else
			{
				g_Cat.pos.x += g_Cat.dir.x;
			}
		}
	}
	//画面外へはいかないようにする
	if (g_Cat.pos.x < CAT_SIZE_W/2)
	{
		g_Cat.pos.x = CAT_SIZE_W / 2;
		//初期値まで戻ってきたら反転する
		ChangeMoveFlag(&g_Cat);
	}
	else if (g_Cat.pos.x >= SCREEN_WIDTH * 6 - CAT_SIZE_W/2)
	{
		g_Cat.pos.x = SCREEN_WIDTH * 6 - CAT_SIZE_W / 2;
		//終端値まで行ってしまったらきたら反転する
		ChangeMoveFlag(&g_Cat);
	}
	//ジャンプパワー
	g_Cat.pos.y -= g_Cat.jump_y;

	//プレイヤーが限界高度を超えたら
	if (g_Cat.pos.y <= g_Cat.limit_jump)
	{
		//飛び上がる力を0にする
		g_Cat.jump_y = 0;
	}
	////中間ポイント
	if (g_Cat.pos.x >= CAT_GOLL/2 && g_Cat.jump_flag == true)
	{
		g_Cat.half_flag = true;//中間ポイントフラグON
	}
	////ゴール//jump_flugは床ブロックと触れているかを取るので空中ゴールはしない
	if (g_Cat.pos.x >= CAT_GOLL && g_Cat.jump_flag == true)
	{
		g_Cat.goal_flag = true;//ゴールフラグON

		//スコアシーンに遷移
		SetScene(SCENE_SCORE);
	}
	//猫が穴に落ちてしまった場合
	if (g_Cat.pos.y >= SCREEN_HEIGHT)
	{
		//ゲームオーバー
		SetScene(SCENE_GAMEOVER);
	}
}
void DrawCat()
{	
	D3DXVECTOR2 basePos = GetBase();
	//テクスチャのセット
	GetDeviceContext()->PSSetShaderResources
	(0, 1, GetTexture(g_Cat.texNo));
	g_Cat.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//スプライトの描画
	DrawSpriteColorRotate(
		basePos.x + g_Cat.pos.x,
		basePos.y + g_Cat.pos.y,
		DRAW_SIZE,
		DRAW_SIZE,
		g_Cat.rot,
		g_Cat.col,
		g_Cat.patern,		
		1.0f / 8.0f,//横
		1.0f / 3.0f,//縦
		8//横のパターン枚数
	);
}
//構造体の先頭ポインタを返す　皆が使えるように
CAT *GetCat()
{
	return &g_Cat;
}

//ジャンプフラグを取得
bool GetJumpFlag()
{
	return g_Cat.jump_flag;
}

//ジャンプ関数
void CatJump(float jumpheight)
{
	//ジャンプ

	/*	PlaySound(JumpSoundNo, 0);
		SetVolume(JumpSoundNo, 0.1f);*/

	//猫が飛び上がる高さ
	//現在の猫の位置から　collisionの中で引数で貰った段数　×　ブロックの高さ　飛ぶ
	//穴に落ちながら飛び上がるバグを修正
	//下から一個分以下に猫が行ってしまったらジャンプはしない
	if (g_Cat.pos.y <= DEFO_SIZE_Y - DEFO_SIZE_X)
	{
		g_Cat.limit_jump = g_Cat.pos.y - (DRAW_SIZE * jumpheight);


		g_Cat.jump_y = JUMP;

		g_Cat.nowjump_flag = jumpheight;
		g_Cat.jump_flag = false;

		//右に進んでいたら
		if (g_Cat.move_flag == false)
		{
			g_Cat.patern = 8.0f;
		}
		else
			//左に進んでいたら
		{
			g_Cat.patern = 11.0f;
		}
	}
}

void ChangeMoveFlag(CAT* c)
{
	if (c->move_flag == true)
	{
		c->move_flag = false;
		g_Cat.dir *= -1;

	}
	else if (c->move_flag == false)
	{
		c->move_flag = true;
		g_Cat.dir *= -1;
	}
}

bool HalfWayFlag()
{
	return g_Cat.half_flag;
}
