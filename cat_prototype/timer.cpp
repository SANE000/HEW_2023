#include "timer.h"
#include "cat.h"
#include "texture.h"
#include "sprite.h"

//プロトタイプ宣言
///////////////////////グローバル宣言
static TIMER g_time[TIME_MAX];
//制限時間の設定
//制限時間90秒に60を掛けてフレーム化しています
bool Half;
int TimerFrame;
int TimerLimit = TIME_LIMIT * 60;

TIMER InitDate[] =
{
	//2個目からはTIME_POS_Xを50ずつ減らせばよし
	{true,D3DXVECTOR2(TIME_POS_X,TIME_POS_Y),0,0,0,TIME_SIZE_W,TIME_SIZE_H,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)},//1の位
	{true,D3DXVECTOR2(TIME_POS_X-50,TIME_POS_Y),0,0,0,TIME_SIZE_W,TIME_SIZE_H,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)},//10の位
	{true,D3DXVECTOR2(TIME_POS_X-100,TIME_POS_Y),0,0,0,TIME_SIZE_W,TIME_SIZE_H,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)}//100の位
};

HRESULT InitTime()
{
	//構造体の初期化
	for (int i = 0; i < TIME_MAX; i++)
	{
		g_time[i] = InitDate[i];
		g_time[i].texNo = LoadTexture((char*)"data\\texture\\time.png");
	}
	//タイマーの初期化
	Half = false;
	TimerFrame = 0;
	return S_OK;
}
//終了処理
void UnInitTime()
{

}
//描画処理
void DrawTime()
{
	TimerFrame++;
	//中間地点まできたら一回だけ時間を戻す
	if (HalfWayFlag() == true && Half == false)
	{
		TimerFrame -= TimerLimit;
		Half = true;
	}
	for (int i = 0; i < TIME_MAX; i++)
	{
		if (TimerFrame < 60000)
		{
			if (i == 0)
			{
				//1の位なので時間をカウントしているTimerFrameを60で割って
				//それに10の剰余で10以上に数字をいかないようにしてパターンを出す
				g_time[i].patern = ((TimerLimit - TimerFrame) / 60) % 10;
			}
			else if (i == 1)
			{
				//10の位なので時間をカウントしているTimerFrameを600で割って
				//それに10の剰余で10以上に数字をいかないようにしてパターンを出す
				g_time[i].patern = ((TimerLimit - TimerFrame) / 600) % 10;
			}
			else if (i == 2)
			{
				//100の位なので時間をカウントしているTimerFrameを6000で割って
				//それに10の剰余で10以上に数字をいかないようにしてパターンを出す
				g_time[i].patern = ((TimerLimit - TimerFrame) / 6000) % 10;
			}
		}
		else
		{
			//1000秒を超えたら全て999秒にする
			g_time[i].patern = 9.0f;
		}
		//描画
		if (g_time[i].use == true)
		{
				//テクスチャのセット
				GetDeviceContext()->PSSetShaderResources
				(0, 1, GetTexture(g_time[i].texNo));
				//スプライトの描画
				DrawSpriteColorRotate(
					g_time[i].pos.x,
					g_time[i].pos.y,
					g_time[i].w,
					g_time[i].h,
					g_time[i].rot,
					g_time[i].col,
					g_time[i].patern,
					1.0f/10,//横
					1.0f,//縦
					10
				);
		}
	}
}
//構造体の先頭ポインタを返す　皆が使えるように
TIMER *GetTime()
{
	return &g_time[0];
}

////時間切れになった時のフラグcat.cppのリセット処理に続く
//bool GetReset()
//{
//	if (NotReset == false)
//	{
//		return NotReset;
//	}
//}

//残り制限時間を返す
int GetLimitFrame()
{
	return TimerLimit - TimerFrame;
}

//ゴールした時のタイマーの値を返す
int GetTimer()
{
	for (int i = 0; i < TIME_MAX; i++)
	{
		if (i == 0)
		{
			//1の位計算して入れる
			g_time->result = g_time[i].patern;
		}
		else if (i == 1)
		{
			//10の位計算して足す
			g_time->result += g_time[i].patern * 10;
		}
		else if (i == 2)
		{
			//100の位計算して足す
			g_time->result += g_time[i].patern * 100;
		}
	}
	return g_time->result;
}

//ステージごとに設定された制限時間から残り時間引く
//つまりは経過した時間です
int ResultTimer()
{
	int num = 120 - GetTimer();

	return num;
}