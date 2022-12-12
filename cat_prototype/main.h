/*==============================================================================

   共通ヘッダー [main.h]
                                                         Author : 
                                                         Date   : 
--------------------------------------------------------------------------------

==============================================================================*/
#ifndef MAIN_H
#define MAIN_H
#pragma once


#pragma warning(push)
#pragma warning(disable:4005)

#define _CRT_SECURE_NO_WARNINGS			// scanf のwarning防止
#include <stdio.h>

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <d3dx9.h>

#define DIRECTINPUT_VERSION 0x0800		// 警告対処
#include "dinput.h"
#include "mmsystem.h"

#pragma warning(pop)



//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCREEN_WIDTH	(960)				// ウインドウの幅
#define SCREEN_HEIGHT	(540)				// ウインドウの高さ
//弾をつくるから限界座標を作ろう
//上
#define SCREEN_LIMIT_UP (0)
//下
#define SCREEN_LIMIT_DOWN (540)
//左
#define SCREEN_LIMIT_LEFT (0)
//右
#define SCREEN_LIMIT_RIGHT (960)
//ブロック描画,当たり判定用
//判定用サイズ
#define SIZE			 (59)
//描画用サイズ
#define DRAW_SIZE		 (60)
//左から
#define DEFO_SIZE_X		 (DRAW_SIZE/2)
//下から
#define DEFO_SIZE_Y		 (SCREEN_HEIGHT - DEFO_SIZE_X)
//偵察速度
#define WATCH 2.0f
//重力
#define GRAV 2.5f
//連続入力防止用待機時間
#define WAIT_TIME 10;
//タイマー関連
#define TIME_MAX 3
#define TIME_POS_X 530
#define TIME_POS_Y 50
#define TIME_SIZE_W 50
#define TIME_SIZE_H 50
//制限時間
#define TIME_LIMIT 60


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
#endif // MAIN_H
