
#pragma once


#include "main.h"

//==========================================
//�}�N����`
//==========================================
#define BLOCKTYPE_MAX 256	//�ێ�����u���b�N�^�C�v�̍ő吔


class BlockType
{
private:
	//�g�p���Ă��邩�ǂ���
	bool m_use;
	//���ݒu����u���b�N�̃^�C�v
	int m_type;

public:
	BlockType(){}

	//cpp�ɍ쐬
	void InitBlocktype();

	void UninitBlocktype(){}

	void UpdateBlocktype(){}

	void DrawBlocktype(){}


	//���̃u���b�N�̃^�C�v���擾����
	int Gettype() const {
		return m_type;
	}
	void SetType(int type) {
		m_type = type;
	}
	//�u���b�N��use��true�ɂ��� �u���b�N��ݒu����یĂяo��
	void ChangeUse(bool use) {
		m_use = use;
	}

	bool GetUse() const{
		return m_use;
	}
};




//==========================================
//�v���g�^�C�v�錾
//==========================================

