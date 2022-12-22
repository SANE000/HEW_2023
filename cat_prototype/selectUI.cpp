#include "texture.h"
#include "selectUI.h"
#include "sprite.h"
#include "shop.h"
#include "player.h"
#include "camera.h"
#include "cat.h"
#include "inputx.h"
#include "keyboard.h"
#include "stageselect.h"
#include "result.h"

static int g_TextureScoreNo = 0;	// テクスチャ識別子
static int ClearStage;
static bool UseWorld = true;  //ワールド選択中か
static int world;


static SelUI g_selUI[UI_MAX];
												  
SelUI InitData[] = {							  
	{false ,D3DXVECTOR2(170.0f,150.0f),D3DXVECTOR2(50.0f,50.0f),0,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),0},
	{false ,D3DXVECTOR2(485.0f,150.0f),D3DXVECTOR2(50.0f,50.0f),0,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),0},
	{false ,D3DXVECTOR2(800.0f,150.0f),D3DXVECTOR2(50.0f,50.0f),0,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),0}

};




HRESULT InitselUI()
{
	for (int i = 0; i < FIELD_MAX;)
	{
		for (int n = 0; n < 3; i++,n++) {
			g_selUI[i] = InitData[n];
		}
	}

	g_TextureScoreNo = LoadTexture((char*)"data\\texture\\ClearRank.png");
	


	ClearStage = (SetField() * 3) + SetStage();

	g_selUI[ClearStage].Patern = GetScore(ClearStage);

	for (int i = 0; i < ClearStage + 2; i++)
	{
		g_selUI[i].Patern = GetScore(i);
		g_selUI[i].use = true;

		g_selUI[i].rank = GetScore(i);
		if (g_selUI[i].Patern > g_selUI[i].rank || g_selUI[i].Patern == 0) {
			g_selUI[i].Patern = GetScore(i);
		}
	}
	
	world = 0;

	return S_OK;
}
void UnInitselUI()
{

}
void UpdateselUI()
{	
	UseWorld = SelectWorld();
	world = SetField();
}
void DrawselUI()
{
	GetDeviceContext()->PSSetShaderResources
	(0, 1, GetTexture(g_TextureScoreNo));

	if (UseWorld == false)
	{
		for (int i = world * 3; i < world * 3 + 3; i++) {
			if (g_selUI[i].use == true)
			{

				DrawSpriteColorRotate
				(
					g_selUI[i].pos.x,
					g_selUI[i].pos.y,
					g_selUI[i].size.x,
					g_selUI[i].size.y,
					g_selUI[i].rot,
					g_selUI[i].col,
					g_selUI[i].Patern,
					1.0f / 4.0f,//横
					1.0f,//縦
					4//総枚数
				);
			}
		}
	}
}