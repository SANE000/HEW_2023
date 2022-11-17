
#pragma once


#include "main.h"

//==========================================
//マクロ定義
//==========================================
#define BLOCKTYPE_MAX 256	//保持するブロックタイプの最大数


class BlockType
{
private:
	//使用しているかどうか
	bool m_use;
	//次設置するブロックのタイプ
	int m_type;

public:
	BlockType(){}

	//cppに作成
	void InitBlocktype();

	void UninitBlocktype(){}

	void UpdateBlocktype(){}

	void DrawBlocktype(){}


	//次のブロックのタイプを取得する
	int Gettype() const {
		return m_type;
	}
	void SetType(int type) {
		m_type = type;
	}
	//ブロックのuseをtrueにする ブロックを設置する際呼び出す
	void ChangeUse(bool use) {
		m_use = use;
	}

	bool GetUse() const{
		return m_use;
	}
};




//==========================================
//プロトタイプ宣言
//==========================================

