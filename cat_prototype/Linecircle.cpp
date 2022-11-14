
#include "main.h"
#include "Linecircle.h"

//===========================
//プロトタイプ宣言
//===========================
void SetVertexCircle(D3DXVECTOR3, float, int);	//多角形を表示する
//表示座標　半径　頂点数

//=============================
//グローバル変数
//=============================
static	ID3D11Buffer		*g_VertexBuffer = NULL;		// 頂点情報


void InitLineCircle()
{
	// 頂点バッファ生成
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(VERTEX_3D) * 65;//頂点1個＊頂点数のサイズで作る
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);
		// 頂点バッファ更新
		D3DXVECTOR3 position = D3DXVECTOR3(100.0f, 200.0f, 0.0f);

		SetVertexCircle(position, 100.0f, 64);
	}
}

void UninitLineCircle()
{
	// 頂点バッファの解放
	if (g_VertexBuffer)
	{
		g_VertexBuffer->Release();//使い終わったので解放する
		g_VertexBuffer = NULL;
	}

}

void DrawLineCircle()
{
	// 表示したいポリゴンの頂点バッファを設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);// LINELIST);


	D3DXVECTOR3 position = D3DXVECTOR3(100.0f,200.0f, 0.0f);

	SetVertexCircle(position, 100.0f, 64);


	// ポリゴン描画
	GetDeviceContext()->Draw(64 + 1, 0);

}

void UpdateLineCircle()
{
}


//=============================================================================
// 頂点データ設定
//	開始座標, 半径, 頂点数
//=============================================================================
void SetVertexCircle(D3DXVECTOR3 Pos, float Rad, int NumVertex)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	//頂点バッファへの書き込み許可をもらう
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;//書き込んでいいポインタをもらえる

	float kakudo = 0;
	float rad = D3DXToRadian(kakudo);
	float x, y = 0;

	for (int i = 0; i < NumVertex; i++)
	{
		//一本目の直線の頂点をセット
		vertex[i].Position.x = cosf(D3DXToRadian(kakudo)) * Rad + Pos.x;
		vertex[i].Position.y = sinf(D3DXToRadian(kakudo)) * Rad + Pos.y;
		vertex[i].Position.z = 0;


		vertex[i].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[i].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		kakudo += (360.0f / NumVertex);
	}


	for (int i = 0; i < NumVertex; i++)
	{
		x = vertex[i].Position.x * cosf(rad) - vertex[i].Position.y * sin(rad);
		y = vertex[i].Position.x * sinf(rad) + vertex[i].Position.y * cos(rad);


		vertex[i].Position.x = x + SCREEN_WIDTH /2;
		vertex[i].Position.y = y + SCREEN_HEIGHT / 2;
	}


	//最後の頂点は戦闘の頂点と同じ
	vertex[NumVertex] = vertex[0];



	GetDeviceContext()->Unmap(g_VertexBuffer, 0);
}
