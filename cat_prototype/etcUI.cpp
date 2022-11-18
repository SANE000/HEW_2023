#include "etcUI.h"
#include "texture.h"
#include "sprite.h"
#include "camera.h"
#include "cat.h"

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
	{true,D3DXVECTOR2(CAT_GOLL + DRAW_SIZE,SCREEN_HEIGHT / 2 + 150),0,0,ETC_SIZE_W,ETC_SIZE_H*2,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)},//�S�[���\��
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
	D3DXVECTOR2 basePos = GetBase();

	for (int i = 0; i < ETC_MAX; i++)
	{
		//��ʏ�𓮂��Ȃ�UI�`��
		if (g_etc[0].use == true)
		{
				//�e�N�X�`���̃Z�b�g
				GetDeviceContext()->PSSetShaderResources
				(0, 1, GetTexture(g_etc[0].texNo));
				//�X�v���C�g�̕`��
				DrawSpriteColorRotate(
					g_etc[0].pos.x,
					g_etc[0].pos.y,
					g_etc[0].w,
					g_etc[0].h,
					g_etc[0].rot,
					g_etc[0].col,
					0,//�����Ȃ�����0
					1.0f,//��
					1.0f,//�c
					1
				);
		}
		//����UI�`��
		if(g_etc[1].use == true)
		{
			//�e�N�X�`���̃Z�b�g
			GetDeviceContext()->PSSetShaderResources
			(0, 1, GetTexture(g_etc[1].texNo));
			//�X�v���C�g�̕`��
			DrawSpriteColorRotate(
				basePos.x + g_etc[1].pos.x,
				basePos.y + g_etc[1].pos.y,
				g_etc[1].w,
				g_etc[1].h,
				g_etc[1].rot,
				g_etc[1].col,
				0,
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
