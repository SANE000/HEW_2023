#include "texture.h"
//�}�N��
#define MAX_TEXTURE_NUM (100)//���[�h���E
//�O���[�o���ϐ�
//�e�N�X�`�����̃|�C���^�z��
static ID3D11ShaderResourceView *g_pTexture[MAX_TEXTURE_NUM];

//���[�h�ς݂̃e�N�X�`���̐�
static UINT g_TextureIndex;

//�e�N�X�`���t�@�C�����̃o�b�t�@ �t�@�C������255�����܂�
static char g_TextureName[MAX_TEXTURE_NUM][256];

//�w��̃e�N�X�`�������擾
//in	�g�p�������e�N�X�`���n���h��
//out	�e�N�X�`�����̃|�C���^�̓������|�C���^�ϐ��̃|�C���^
ID3D11ShaderResourceView **GetTexture(int index)
{
	//�G���[�`�F�b�N
	//0�����Ȃ�
	if (index < 0)
	{
		return NULL;
	}
	//���[�h���I�[�o�[
	if (index >= g_TextureIndex)
	{
		return NULL;
	}
	//�C���f�b�N�X�������ꏊ�̔z��̃|�C���^��Ԃ�
	return &g_pTexture[index];
}
//�e�N�X�`���̏I������
//���[�h�ς݂̃e�N�X�`����S�ĉ��
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
//�e�N�X�`���̃��[�h
//�e�N�X�`���t�@�C�����̐擪�|�C���^
int LoadTexture(char*filename)
{
	//���łɓǂݍ��܂ꂽ�e�N�X�`�����𒲂ׂē������O�����݂����
	//�e�N�X�`�����̊i�[���ꂽ�z��̔ԍ���Ԃ��B������̔�r�֐�
	for (int i = 0; i < g_TextureIndex; i++)
	{
		//�e�N�X�`�������rstrcmp���g��
		if (strcmp(g_TextureName[i], filename) == 0)
		{//if(strcmp(&g_TextureName[i][0], filename) == 0)
			//������������
			return i;
		}
	}
	//�ǂݍ��ݐ������E�𒴂��Ă��Ȃ����H
	if (g_TextureIndex == MAX_TEXTURE_NUM)
	{
		//i�͕��̐��͂��肦�Ȃ��̂�-1�ɂȂ����Ƃ��̓G���[
		return -1;//�ǂݍ��߂Ȃ��̂ŃG���[�R�[�h��Ԃ�
	}

	//�e�N�X�`���̃��[�h���n�܂�c�ƂĂ������̂Ł��œǂݍ��܂Ȃ��悤�ɂ��Ă�
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
		return -2;//�ǂݍ��ݎ��s
	}
	//���[�h�����e�N�X�`�����̓o�^
	//���x�͕�����̃R�s�[strcpy�������Z�L�����e�B�ʂ���strcpy_s��
	strcpy_s(g_TextureName[g_TextureIndex], 256, filename);
	//strcpy_s(&g_TextureName[g_TextureIndex][0], 256, filename);
	//��������������
	//���݂̐����ꎞ�ޔ�
	int retIndex = g_TextureIndex;
	//���݂̐��𑝂₵�Ă���
	g_TextureIndex++;
	//�ޔ����Ă����l��Ԃ�
	return retIndex;
}

