#include "renderer.h"
#include "main.h"

//マクロ
#define NUM_VERTEX 4

static	ID3D11Buffer		*g_VertexBufferTriangle = NULL;
//表示座標X,Y,サイズ横,縦,回転角度,カラー,パターン番号,
//パターンサイズ横,縦,横に並ぶパターン数
void DrawSpriteColorRotate(float posx, float posy, int size_w,
	int size_h, float kakudo, D3DXCOLOR col,
	float PaternNo,
	float uv_w, float uv_h,
	int NumPatern)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	//頂点バッファへの書き込み許可をもらう
	GetDeviceContext()->Map(g_VertexBufferTriangle, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	//頂点構造体の型にポインター型を変換をする
	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	//変数を付けて足していくと絵が動く！
	static float ofset = 0.0f;

	//頂点 V0をセット
	vertex[0].Position = D3DXVECTOR3(-size_w / 2, -size_h / 2, 0.0f);
	vertex[0].Diffuse = col;	// D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f + ofset, 0.0f);
	//頂点 V1をセット
	vertex[1].Position = D3DXVECTOR3(+size_w / 2, -size_h / 2, 0.0f);
	vertex[1].Diffuse = col;	// D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f + ofset, 0.0f);
	//頂点 V2をセット
	vertex[2].Position = D3DXVECTOR3(-size_w / 2, +size_h / 2, 0.0f);
	vertex[2].Diffuse = col;	// D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f + ofset, 1.0f);//修正した！
	//頂点 V3をセット
	vertex[3].Position = D3DXVECTOR3(+size_w / 2, +size_h / 2, 0.0f);
	vertex[3].Diffuse = col;	// D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f + ofset, 1.0f);//修正した！
	//足していくところ
	//ofset += 1.0f / 60.0f;
	//60で割ってるので1秒で一個画像が動くよ！

		//UVアニメ
	//引き数にしちゃう
		//最初の一回だけ初期化のゼロ、その後は値が保存される！
		//static float PaternNo = 0;
		//float uv_w = 0.5f;//キャラクターの横サイズ
		//float uv_h = 0.5f;//キャラクターの縦サイズ　　田みたいな感じ
		//int NumPatern = 2;//キャラクターの横の枚数
		////パターン番号を少しずつ増やすことで遅く出来るのだ
		//PaternNo += 0.01f;
		////パターン番号が4以上になったら
		//if (PaternNo >= 4)
		//{
		//	//いきなり=0;にしちゃうと誤差が発生する！そこで
		//	//まず引き算で少数を残してあげよう
		//	PaternNo -= 4.0f;
		//}
		//増やした後に整数値に代入することで小数点を切り捨て！
		int no = PaternNo;

		//左上(LEFT-TOP)のUV座標を計算
		float uv_left = (no % NumPatern) * uv_w;//左上U
		float uv_top = (no / NumPatern) * uv_h;//V座標

		////テクスチャ座標を書き換える
		vertex[0].TexCoord = D3DXVECTOR2(uv_left, uv_top);//LEFT-TOP
		vertex[1].TexCoord = D3DXVECTOR2(uv_left+uv_w, uv_top);//RIGHT-TOP
		vertex[2].TexCoord = D3DXVECTOR2(uv_left, uv_top + uv_h);//LEFT-BOTTOM
		vertex[3].TexCoord = D3DXVECTOR2(uv_left+uv_w, uv_top + uv_h);//RIGHT-BOTTOM

		//これで動くようになりました！
		//パラパラ漫画みたいになるぞ！これで歩きモーションとかできる？
		//あとは背景を動かさないように関数で分けたりなど自分で設定！！

		//度をラジアンへ変換
		float	rad = D3DXToRadian(kakudo);
		float	x, y;

		for (int i = 0; i < 4; i++)
		{
			x = vertex[i].Position.x * cosf(rad) - vertex[i].Position.y * sinf(rad);
			y = vertex[i].Position.y * cosf(rad) + vertex[i].Position.x * sinf(rad);

			vertex[i].Position.x = x + posx;
			vertex[i].Position.y = y + posy;
		}
		GetDeviceContext()->Unmap(g_VertexBufferTriangle, 0);//書き込み終了
	    //表示したいポリゴンの頂点バッファを設定
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBufferTriangle, &stride, &offset);
		// プリミティブトポロジ設定
		GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		//ポリゴン描画
		GetDeviceContext()->Draw(NUM_VERTEX, 0);
}

	void InitSptite()
	{
		{//三角形用の頂点初期化処理
	// 頂点バッファ生成
			D3D11_BUFFER_DESC bd;
			ZeroMemory(&bd, sizeof(bd));
			bd.Usage = D3D11_USAGE_DYNAMIC;
			bd.ByteWidth = sizeof(VERTEX_3D) * NUM_VERTEX;//頂点1個＊頂点数のサイズで作る
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBufferTriangle);
		}
	}
	
	void UnInitSptite()
	{
		if (g_VertexBufferTriangle)
		{
			g_VertexBufferTriangle->Release();//使い終わったので解放する
			g_VertexBufferTriangle = NULL;
		}

	}
