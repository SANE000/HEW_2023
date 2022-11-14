#include "etcUI.h"
#include "texture.h"
#include "sprite.h"

//���̑���UI�֌W�̃}�N���₱�ꂩ��ǉ����邩���p
#define ETC_MAX 2
#define ETC_SIZE_W 100
#define ETC_SIZE_H 50
//�v���g�^�C�v�錾
///////////////////////�O���[�o���錾
static ETC g_etc[ETC_MAX];

ETC InitDate[] =
{
	{true,D3DXVECTOR2(SCREEN_WIDTH/2,100),0,0,ETC_SIZE_W,ETC_SIZE_H,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)},//�^�C��UI
	{true,D3DXVECTOR2(910,SCREEN_HEIGHT / 2-50),0,0,ETC_SIZE_W,ETC_SIZE_H*2,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)},//�S�[���\��
};

HRESULT InitEtc()
{
	//�\���̂̏�����
	for (int i = 0; i < ETC_MAX; i++)
	{
		g_etc[i] = InitDate[i];
		if (i == 0)
		{
			g_etc[i].texNo = LoadTexture((char*)"data\\texture\\timeUI.png");
		}
		else
		{
			g_etc[i].texNo = LoadTexture((char*)"data\\texture\\goal_flag.png");
		}
	}
	return S_OK;
}
//�I������
void UnInitEtc()
{

}
//�`�揈��
void DrawEtc()
{
	for (int i = 0; i < ETC_MAX; i++)
	{
		//�`��
		if (g_etc[i].use == true)
		{
				//�e�N�X�`���̃Z�b�g
				GetDeviceContext()->PSSetShaderResources
				(0, 1, GetTexture(g_etc[i].texNo));
				//�X�v���C�g�̕`��
				DrawSpriteColorRotate(
					g_etc[i].pos.x,
					g_etc[i].pos.y,
					g_etc[i].w,
					g_etc[i].h,
					g_etc[i].rot,
					g_etc[i].col,
					0,//�����Ȃ�����0
					1.0f,//��
					1.0f,//�c
					1
				);
		}
	}
}
//�\���̂̐擪�|�C���^��Ԃ��@�F���g����悤��
ETC *GetEtc()
{
	return &g_etc[0];
}
