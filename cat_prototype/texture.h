
#pragma once
#include "renderer.h"

int LoadTexture(char*filename);
void UninitTexture();

//�w��̃e�N�X�`�������擾
//in	�e�N�X�`���n���h��
//�|�C���^��2�I�H�|�C���^�ϐ��̃|�C���^�Ȃ̂�
ID3D11ShaderResourceView** GetTexture(int index);