/*==============================================================================

   DirectXの初期化 [main.cpp]
                                                         Author : 
                                                         Date   : 
--------------------------------------------------------------------------------

==============================================================================*/
#include "main.h"
#include "renderer.h"
#include "inputx.h"//入力処理
#include "keyboard.h"
#include "texture.h"
#include "polygon.h"//新しいのを入れたのが分かる
#include "player.h"
#include "block.h"
#include "collision.h"
#include "sprite.h"
#include "Game.h"
#include "Scene.h"
#include "sound.h"
#include "select.h"

//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************
#pragma comment (lib, "d3d11.lib")		
#pragma comment (lib, "d3dcompiler.lib")
#pragma comment (lib, "d3dx11.lib")	
#pragma comment (lib, "d3dx9.lib")	
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "dxerr.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "xinput.lib")

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME			"GameWindow"				// ウインドウのクラス名
#define WINDOW_CAPTION		"DirectXの初期化"			// ウインドウのキャプション名

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);


//*****************************************************************************
// グローバル変数:
//*****************************************************************************

#ifdef _DEBUG
int		g_CountFPS;							// FPSカウンタ
char	g_DebugStr[2048] = WINDOW_CAPTION;	// デバッグ文字表示用
#endif

											//=============================================================================
// メイン関数(WinMain)
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// 無くても良いけど、警告が出る（未使用宣言）
	UNREFERENCED_PARAMETER(lpCmdLine);		// 無くても良いけど、警告が出る（未使用宣言）

	// 時間計測用FPS
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;
	
	WNDCLASS wc = {};
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = CLASS_NAME;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);

	RegisterClass(&wc);
	
	// ウィンドウの作成
	HWND hWnd = CreateWindow(CLASS_NAME,
						WINDOW_CAPTION,
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,																		// ウィンドウの左座標
						CW_USEDEFAULT,																		// ウィンドウの上座標
						SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME)*2,									// ウィンドウ横幅
						SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME)*2+GetSystemMetrics(SM_CYCAPTION),	// ウィンドウ縦幅
						NULL,
						NULL,
						hInstance,
						NULL);

	// DirectXの初期化(ウィンドウを作成してから行う)
	if(FAILED(Init(hInstance, hWnd, true)))
	{
		return -1;
	}

	// フレームカウント初期化
	timeBeginPeriod(1);	// 分解能を設定
	dwExecLastTime = dwFPSLastTime = timeGetTime();	// システム時刻をミリ秒単位で取得
	dwCurrentTime = dwFrameCount = 0;
	
	// ウインドウの表示(Init()の後に呼ばないと駄目)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG			msg;

	// メッセージループ
	while(1)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{//メッセージがあれば実行
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{//Peekメッセージが無かったらゲーム関連の処理実行。
			dwCurrentTime = timeGetTime();					// システム時刻を取得

			if ((dwCurrentTime - dwFPSLastTime) >= 1000)	// 1秒ごとに実行
			{
#ifdef _DEBUG
				g_CountFPS = dwFrameCount;
#endif
				dwFPSLastTime = dwCurrentTime;				// FPSを測定した時刻を保存
				dwFrameCount = 0;							// カウントをクリア
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))	// 1/60秒ごとに実行
			{
				dwExecLastTime = dwCurrentTime;	// 処理した時刻を保存

#ifdef _DEBUG	// デバッグ版の時だけFPSを表示する
				wsprintf(g_DebugStr, WINDOW_CAPTION);
				wsprintf(&g_DebugStr[strlen(g_DebugStr)], " FPS:%d", g_CountFPS);
				SetWindowText(hWnd, g_DebugStr);
#endif
				//実際のゲームの処理
				Update();			// 更新処理
				Draw();				// 描画処理
				CheckScene();
				dwFrameCount++;		// 処理回数のカウントを加算
			}
		}
	}
	
	timeEndPeriod(1);				// 分解能を戻す

	// 終了処理
	Uninit();

	return (int)msg.wParam;
}

//=============================================================================
// プロシージャ
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	Keyboard_ProcessMessage(message, wParam, lParam);
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// レンダリング処理の初期化
	InitRenderer(hInstance, hWnd, bWindow);
	//宣言
	Keyboard_Initialize();
	//入力処理の初期化
	InitInput(hInstance, hWnd);
	//サウンドはシーンが始まる前に置いておく
	InitSound(hWnd);
	InitSptite();
	InitScene(SCENE::SCENE_TITLE);

	return S_OK;
}


//=============================================================================
// 終了処理
//=============================================================================
void Uninit(void)
{
	UninitScene();
	UninitSound();
	//スプライト終了処理
	UnInitSptite();
	//これ一つでOK
	UninitTexture();
	//入力終了処理
	UninitInput();
	// レンダリングの終了処理
	UninitRenderer();
}

//=============================================================================
// 更新処理
//=============================================================================
void Update(void)
{
	UpdateInput();
	UpdateScene();
}

//=============================================================================
// 描画処理
//=============================================================================
void Draw(void)
{
	// バックバッファクリアしてからなんでも描き出す
	Clear();
	SetWorldViewProjection2D();
	// 2D描画なので深度無効
	SetDepthEnable(false);
	DrawScene();
	Present();
}


