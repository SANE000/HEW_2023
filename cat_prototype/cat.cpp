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
#include "timer.h"
//グローバル変数
//int JumpSoundNo = 0;
//時間切れになったときのリセット処理用変数
bool Reset = false;
//プレイヤーオブジェクト
static CAT g_Cat;
static MOVE_BLOCK *m_block = GetMoveBlock();

HRESULT InitCat()
{
	//テクスチャロード 画像の名前を入れよう
	g_Cat.texNo = LoadTexture((char*)"data\\texture\\neko.png");
	//構造体の初期化
	g_Cat.pos.x = DEFO_SIZE_X;
	g_Cat.pos.y = CAT_INIT_Y;
	g_Cat.move_flag = false;
	g_Cat.jump_flag = false;
	g_Cat.jump_y = 0.0f;
	g_Cat.limit_jump = 0.0f;
	g_Cat.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Cat.patern = 0.0f;
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
	g_Cat.patern += 0.03;
	if (g_Cat.patern >= 2.0f)
	{
		g_Cat.patern -= 2.0f;
	}
	Reset = GetReset();
	//空中に浮いているときだけ重力の影響
	if (g_Cat.jump_flag == false)
	{
		g_Cat.pos.y += GRAV;
	}
	//自動で移動(壁にぶつかるor初期値まで戻ったら反転)
	if (g_Cat.move_flag == false)
	{
		//同じタイミングでジャンプが始まるため、飛ぶ段数に応じて飛んでる最中はX方面の移動を遅くする
		if (g_Cat.nowjump_flag > 0)
		{
			g_Cat.pos.x += WALK / g_Cat.nowjump_flag;
		}
		else
		{
			g_Cat.pos.x += WALK;
		}
	}
	else
	{
		//同じタイミングでジャンプが始まるため、飛ぶ段数に応じて飛んでる最中はX方面の移動を遅くする
		if (g_Cat.nowjump_flag > 0)
		{
			g_Cat.pos.x -= WALK / g_Cat.nowjump_flag;
		}
		else
		{
			g_Cat.pos.x -= WALK;
		}
	}
	//画面外へはいかないようにする
	if (g_Cat.pos.x < CAT_SIZE_W/2)
	{
		g_Cat.pos.x = CAT_SIZE_W / 2;
		//初期値まで戻ってきたら反転する
		ChangeMoveFlag(&g_Cat);
	}
	//////////猫のジャンプは今後実装予定/////////////////////////////////////////////////////
	//ジャンプパワー
	g_Cat.pos.y -= g_Cat.jump_y;

	//プレイヤーが限界高度を超えたら
	if (g_Cat.pos.y <= g_Cat.limit_jump)
	{
		//飛び上がる力を0にする
		g_Cat.jump_y = 0;
	}
	
	////ゴール//jump_flugは床ブロックと触れているかを取るので空中ゴールはしない
	if (g_Cat.pos.x >= CAT_GOLL && g_Cat.jump_flag == true)
	{
		////テストだから初期位置に戻す
		//g_Cat.pos.x = CAT_INIT_X;
		//g_Cat.pos.y = CAT_INIT_Y;
		g_Cat.goal_flag = true;//ゴールフラグON

		//スコアシーンに遷移
		SetScene(SCENE_SCORE);
	}
	//猫が穴に落ちてしまった場合
	if (g_Cat.pos.y >= SCREEN_HEIGHT)
	{
		//テストだから初期位置に戻す
		g_Cat.pos.x = CAT_INIT_X;
		g_Cat.pos.y = CAT_INIT_Y;
	}
	//==============================================================================================================================
	//		//時間切れ処理              ///////////////////////////////////////////////////////////////////////////////////////////
	//==============================================================================================================================
	if (GetLimitFrame() < 0)
	{
		//テストだから初期位置に戻し,jump_flugも初期設定に戻す
		g_Cat.pos.x = CAT_INIT_X;
		g_Cat.pos.y = CAT_INIT_Y;
		g_Cat.jump_flag = false;
		//時間もテストなので戻す。ゲームオーバー処理かショップに戻る処理とか決めたい
		//リセットするとブロックは消えるが使ってしまった分は戻ってこないのでそこも直したいです
		//11/18日
		Reset = true;
		//MOVEブロックも全部消す処理
		for (int i = 0; i < MOVE_BLOCK_MAX; i++)
		{
			if (m_block[i].use == true)
			{
				m_block[i].use = false;
				//全てをfalseにするためbreakはつけない
			}
		}
		
	}
}
void DrawCat()
{	
	D3DXVECTOR2 basePos = GetBase();
	//テクスチャのセット
	GetDeviceContext()->PSSetShaderResources
	(0, 1, GetTexture(g_Cat.texNo));
	g_Cat.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//スプラsイトの描画
	DrawSpriteColorRotate(
		basePos.x + g_Cat.pos.x,
		basePos.y + g_Cat.pos.y,
		DRAW_SIZE,
		DRAW_SIZE,
		g_Cat.rot,
		g_Cat.col,
		g_Cat.patern,		
		1.0f / 2.0f,//横
		1.0f,//縦
		2//横のパターン枚数
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
	g_Cat.limit_jump = g_Cat.pos.y - ( SIZE * jumpheight);


	g_Cat.jump_y = JUMP;

	g_Cat.nowjump_flag = jumpheight;
	g_Cat.jump_flag = false;
}

void ChangeMoveFlag(CAT* c)
{
	if (c->move_flag == true)
	{
		c->move_flag = false;
	}
	else if (c->move_flag == false)
	{
		c->move_flag = true;
	}
}
//時間をもとに戻すフラグ
bool ResetTime()
{
	return Reset;
}
