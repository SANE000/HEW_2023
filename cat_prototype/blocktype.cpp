

#include "blocktype.h"
#include <random>


//==========================================
//�O���[�o���ϐ�
//==========================================


void BlockType::InitBlocktype()
{
	std::random_device rd;	//�����𐶐�����\����

	std::mt19937 mt(rd());//�^������

	std::uniform_int_distribution<> dist(0, 3);	//�]�艉�Z�@0�`3�܂ł̗������l��

	m_type = dist(mt);
	m_use = false;
	
}
