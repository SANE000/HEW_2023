#include "timer.h"
#include "texture.h"
#include "sprite.h"

//�v���g�^�C�v�錾
///////////////////////�O���[�o���錾
static TIMER g_time[TIME_MAX];
int TimerFrame;

TIMER InitDate[] =
{
	//2�ڂ����TIME_POS_X��50�����点�΂悵
	{true,D3DXVECTOR2(TIME_POS_X,TIME_POS_Y),0,0,0,TIME_SIZE_W,TIME_SIZE_H,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)},//1�̈�
	{true,D3DXVECTOR2(TIME_POS_X-50,TIME_POS_Y),0,0,0,TIME_SIZE_W,TIME_SIZE_H,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)},//10�̈�
	{true,D3DXVECTOR2(TIME_POS_X-100,TIME_POS_Y),0,0,0,TIME_SIZE_W,TIME_SIZE_H,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)}//100�̈�
};

HRESULT InitTime()
{
	//�\���̂̏�����
	for (int i = 0; i < TIME_MAX; i++)
	{
		g_time[i] = InitDate[i];
		g_time[i].texNo = LoadTexture((char*)"data\\texture\\time.png");
	}
	//�^�C�}�[�̏�����
	TimerFrame = 5400;
	return S_OK;
}
//�I������
void UnInitTime()
{

}
//�`�揈��
void DrawTime()
{
	TimerFrame--;
	for (int i = 0; i < TIME_MAX; i++)
	{
		if (TimerFrame < 60000)
		{
			if (i == 0)
			{
				//1�̈ʂȂ̂Ŏ��Ԃ��J�E���g���Ă���TimerFrame��60�Ŋ�����
				//�����10�̏�]��10�ȏ�ɐ����������Ȃ��悤�ɂ��ăp�^�[�����o��
				g_time[i].patern = (TimerFrame / 60) % 10;
			}
			else if (i == 1)
			{
				//10�̈ʂȂ̂Ŏ��Ԃ��J�E���g���Ă���TimerFrame��600�Ŋ�����
				//�����10�̏�]��10�ȏ�ɐ����������Ȃ��悤�ɂ��ăp�^�[�����o��
				g_time[i].patern = (TimerFrame / 600) % 10;
			}
			else if (i == 2)
			{
				//100�̈ʂȂ̂Ŏ��Ԃ��J�E���g���Ă���TimerFrame��6000�Ŋ�����
				//�����10�̏�]��10�ȏ�ɐ����������Ȃ��悤�ɂ��ăp�^�[�����o��
				g_time[i].patern = (TimerFrame / 6000) % 10;
			}
		}
		else
		{
			//1000�b�𒴂�����S��999�b�ɂ���
			g_time[i].patern = 9.0f;
		}
		//�`��
		if (g_time[i].use == true)
		{
				//�e�N�X�`���̃Z�b�g
				GetDeviceContext()->PSSetShaderResources
				(0, 1, GetTexture(g_time[i].texNo));
				//�X�v���C�g�̕`��
				DrawSpriteColorRotate(
					g_time[i].pos.x,
					g_time[i].pos.y,
					g_time[i].w,
					g_time[i].h,
					g_time[i].rot,
					g_time[i].col,
					g_time[i].patern,
					1.0f/10,//��
					1.0f,//�c
					10
				);
		}
	}
}
//�\���̂̐擪�|�C���^��Ԃ��@�F���g����悤��
TIMER *GetTime()
{
	return &g_time[0];
}

int GetFirstFrame()
{
	return TimerFrame;
}

//�S�[���������̃^�C�}�[�̒l��Ԃ�
int GetTimer()
{
	for (int i = 0; i < TIME_MAX; i++)
	{
		if (i == 0)
		{
			//1�̈ʌv�Z���ē����
			g_time->result = g_time[i].patern;
		}
		else if (i == 1)
		{
			//10�̈ʌv�Z���đ���
			g_time->result += g_time[i].patern * 10;
		}
		else if (i == 2)
		{
			//100�̈ʌv�Z���đ���
			g_time->result += g_time[i].patern * 100;
		}
	}
	return g_time->result;
}

//�X�e�[�W���Ƃɐݒ肳�ꂽ�������Ԃ���c�莞�Ԉ���
int ResultTimer()
{
	//�����90�b�Őݒ�

	int num = 0;

	num = 90 - GetTimer();

	return num;

}