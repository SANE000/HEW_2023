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
//横3倍した判定サイズ
#define BASE_SIZE	 (DRAW_SIZE*3-1)
//横3倍した足場用サイズ
#define BASE_DRAW_SIZE	 (DRAW_SIZE*3)
//横3倍した足場初期位置
#define BASE_DEFO_SIZE_X (BASE_DRAW_SIZE/2)
//重力
#define GRAV 2.5f
//タイマー関連
#define WAIT_TIME 10;
#define TIME_MAX 3
#define TIME_POS_X 530
#define TIME_POS_Y 50
#define TIME_SIZE_W 50
#define TIME_SIZE_H 50

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
#endif // MAIN_H
