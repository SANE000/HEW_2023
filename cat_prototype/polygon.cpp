/*==============================================================================

   頂点管理 [polygon.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include	"polygon.h"
#include	"sprite.h"
#include    "texture.h"
#include	"inputx.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NUM_VERTEX 4
#define	NUM_TRIANGLE_VERTEX	(4)	//三角形用頂点数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static	ID3D11ShaderResourceView	*g_BackTexture = NULL;
//テクスチャのファイルパス
static	char	*g_BackTextureName = (char*)"data/texture/background_park.png";
//テクスチャ情報保存するやつ　ポインタ変数の初期化は NULL !!
//画像１枚につき１個必要なのだ…↑
//テクスチャインデックス
int TextureBGNo = 0;

float	PositionX = SCREEN_WIDTH / 2;//画面中央座標
float	PositionY = SCREEN_HEIGHT / 2;

D3DXVECTOR3	MoveVec;

typedef struct
{
	D3DXVECTOR3 Position;
	D3DXVECTOR2 Size;
	D3DXCOLOR Color;
	float Rotate;
}BG;

BG *SampleBG;


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPolygon(void)
{
	SampleBG = new BG;

	SampleBG->Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);
	SampleBG->Size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	SampleBG->Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	SampleBG->Rotate = 0;

	ID3D11Device *pDevice = GetDevice();
	//texture.hのおかげでここまで減らすことができた
	/*ここでテクスチャを読み込むぞ！(ロード)*/
	//読み込めなかったら強制終了
	TextureBGNo = LoadTexture(g_BackTextureName);
	if (TextureBGNo == -1)
	{
		exit(999);
	}
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UnInitPolygon(void)
{
	if (SampleBG)
	{
		delete	SampleBG;
		SampleBG = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePolygon(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPolygon(void)
{
	
	//変数も増やそう
	{
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(TextureBGNo));//&g_BackTexture);
		//サイズを気を付けよう。
		static float patern = 0;
		DrawSpriteColorRotate(
			SampleBG->Position.x,
			SampleBG->Position.y,
			SampleBG->Size.x,
			SampleBG->Size.y,
			SampleBG->Rotate,
			SampleBG->Color,
			0,//アニメーション番号背景だから変わらない
			1.0f,//横サイズ背景もスト2みたいに変えたかったらやれ
			1.0f,//縦サイズ
			1//横のパターン数
		);
	}
}





