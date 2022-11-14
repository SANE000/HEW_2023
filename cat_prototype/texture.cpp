#include "texture.h"
//マクロ
#define MAX_TEXTURE_NUM (100)//ロード限界
//グローバル変数
//テクスチャ情報のポインタ配列
static ID3D11ShaderResourceView *g_pTexture[MAX_TEXTURE_NUM];

//ロード済みのテクスチャの数
static UINT g_TextureIndex;

//テクスチャファイル名のバッファ ファイル名は255文字まで
static char g_TextureName[MAX_TEXTURE_NUM][256];

//指定のテクスチャ情報を取得
//in	使用したいテクスチャハンドル
//out	テクスチャ情報のポインタの入ったポインタ変数のポインタ
ID3D11ShaderResourceView **GetTexture(int index)
{
	//エラーチェック
	//0未満なら
	if (index < 0)
	{
		return NULL;
	}
	//ロード数オーバー
	if (index >= g_TextureIndex)
	{
		return NULL;
	}
	//インデックスが示す場所の配列のポインタを返す
	return &g_pTexture[index];
}
//テクスチャの終了処理
//ロード済みのテクスチャを全て解放
void UninitTexture()
{
	for (int i = 0; i < g_TextureIndex; i++)
	{
		if (g_pTexture[i] != NULL)
		{
			g_pTexture[i]->Release();
			g_pTexture[i] = NULL;
		}
	}
}
//テクスチャのロード
//テクスチャファイル名の先頭ポインタ
int LoadTexture(char*filename)
{
	//すでに読み込まれたテクスチャ名を調べて同じ名前が存在すると
	//テクスチャ名の格納された配列の番号を返す。文字列の比較関数
	for (int i = 0; i < g_TextureIndex; i++)
	{
		//テクスチャ名を比較strcmpを使う
		if (strcmp(g_TextureName[i], filename) == 0)
		{//if(strcmp(&g_TextureName[i][0], filename) == 0)
			//正しい書き方
			return i;
		}
	}
	//読み込み数が限界を超えていないか？
	if (g_TextureIndex == MAX_TEXTURE_NUM)
	{
		//iは負の数はありえないので-1になったときはエラー
		return -1;//読み込めないのでエラーコードを返す
	}

	//テクスチャのロードが始まる…とても長いので↑で読み込まないようにしてる
	HRESULT hr = D3DX11CreateShaderResourceViewFromFile(
		GetDevice(),
		filename,
		NULL,
		NULL,
		&g_pTexture[g_TextureIndex],
		NULL
	);
	if (hr != S_OK)
	{
		return -2;//読み込み失敗
	}
	//ロードしたテクスチャ名の登録
	//今度は文字列のコピーstrcpyただしセキュリティ面からstrcpy_sだ
	strcpy_s(g_TextureName[g_TextureIndex], 256, filename);
	//strcpy_s(&g_TextureName[g_TextureIndex][0], 256, filename);
	//正しい書き方↑
	//現在の数を一時退避
	int retIndex = g_TextureIndex;
	//現在の数を増やしておく
	g_TextureIndex++;
	//退避していた値を返す
	return retIndex;
}

