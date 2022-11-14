
#pragma once
#include "renderer.h"

int LoadTexture(char*filename);
void UninitTexture();

//指定のテクスチャ情報を取得
//in	テクスチャハンドル
//ポインタが2つ！？ポインタ変数のポインタなのだ
ID3D11ShaderResourceView** GetTexture(int index);