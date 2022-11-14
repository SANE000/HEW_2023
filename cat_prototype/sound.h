
#pragma once

#include <windows.h>
#include "xaudio2.h"//Xaudioを利用したいときにインクルード


bool InitSound(HWND hWnd);//サウンドの初期化
void UninitSound(void);//サウンドの終了
//データのロード
int LoadSound(char* pFilename);
//loopcount再生0一階,-1以下でループ
void PlaySound(int index, int loopCount);
void StopSound(int index);//停止
void StopSoundAll(void);//全ての音源を停止
void SetVolume(int index, float vol);//volume変更

//サウンド追加
// 1.コントローラーと同じタイミングで初期化＆終了処理を行う
// 2.タイトルなどのシーン初期化でデータロード＆再生処理(BGM)
// 3.終了処理で再生停止(BGM)
// 4.弾,爆発等も初期化でロードはしておく
// 5.再生はそれぞれのタイミングで行うが,ループごとに
//   毎回再生されないように注意
