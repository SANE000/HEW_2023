

#include "blocktype.h"
#include <random>


//==========================================
//グローバル変数
//==========================================


void BlockType::InitBlocktype()
{
	std::random_device rd;	//乱数を生成する構造体

	std::mt19937 mt(rd());//疑似乱数

	std::uniform_int_distribution<> dist(0, 3);	//余剰演算　0～3までの乱数を獲得

	m_type = dist(mt);
	m_use = false;
	
}
