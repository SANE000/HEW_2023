
#include "texture.h"
#include "sprite.h"
#include "cat.h"
#include "player.h"
#include "timer.h"
#include "result.h"
#include "main.h"


//==========================================
//�O���[�o���ϐ�
//==========================================
static int g_TextureNo = 0;	// �e�N�X�`�����ʎq
static int TextureBGNo = 0;	// �e�N�X�`�����ʎq
static int TextureSNo = 0;	// �e�N�X�`�����ʎq
static int TextureANo = 0;	// �e�N�X�`�����ʎq
static int TextureBNo = 0;	// �e�N�X�`�����ʎq
static int g_Time = 0;
static int g_Block = 0;
int Score = 0;



HRESULT InitResult()
{
	//�^�C�g����ʗp�e�N�X�`���̓ǂݍ���
	g_TextureNo = LoadTexture((char*)"data/TEXTURE/time.png");
	TextureBGNo = LoadTexture((char*)"data/TEXTURE/Result_alpha_bg.png");
	TextureSNo = LoadTexture((char*)"data/TEXTURE/Result_alpha_s.png");
	TextureANo = LoadTexture((char*)"data/TEXTURE/Result_alpha_a.png");
	TextureBNo = LoadTexture((char*)"data/TEXTURE/Result_alpha_b.png");

	return S_OK;
}

void UninitResult()
{
	////

}

void UpdateResult()
{
	//�X�R�A�v�Z//�R�R�v�����i�[�Ɍ��߂Ă��炤�̖Y��Ă�
	if (BlockScore() <= 4 && ResultTimer() <= 20)
	{
		Score = SCORE::SCORE_S;
	}
	else if (BlockScore() <= 5 && ResultTimer() <= 35)
	{
		Score = SCORE::SCORE_A;
	}
	else
	{
		Score = SCORE::SCORE_B;
	}
}

void DrawResult()
{
	{
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(TextureBGNo));//&Result_alpha_bg);
		//�T�C�Y���C��t���悤�B
		static float patern = 0;
		DrawSpriteColorRotate(
			SCREEN_WIDTH / 2,
			SCREEN_HEIGHT / 2,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			0,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			0,//�A�j���[�V�����ԍ��w�i������ς��Ȃ�
			1.0f,//���T�C�Y�w�i���X�g2�݂����ɕς�������������
			1.0f,//�c�T�C�Y
			1//���̃p�^�[����
		);

		int time = g_Time;

		for (int i = 0; i < TIME_MAX - 1; i++)
		{
			//1�̈ʂ̐��l�����o��
			int suuji = time % 10;;

			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_TextureNo));//&time.png);
			DrawSpriteColorRotate(480.0f - (32.0f*i), 220.0f, 32.0f, 32.0f, 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				suuji, 0.1f, 1.0f, 10);

			//���l�S�̂�10�Ŋ���
			time /= 10;
		}

		int block = g_Block;

		for (int i = 0; i < 2; i++)
		{
			//1�̈ʂ̐��l�����o��
			int num = block % 10;;

			DrawSpriteColorRotate(480.0f - (32.0f*i), 355.0f, 32.0f, 32.0f, 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				num, 0.1f, 1.0f, 10);

			//���l�S�̂�10�Ŋ���
			block /= 10;
		}
		SetTime(ResultTimer());
		SetBlock(BlockScore());

		if (Score == SCORE::SCORE_S)
		{
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(TextureSNo));//&Result_alpha_s);
		//�T�C�Y���C��t���悤�B
			static float patern = 0;
			DrawSpriteColorRotate(
				SCREEN_WIDTH / 2,
				SCREEN_HEIGHT / 2,
				SCREEN_WIDTH,
				SCREEN_HEIGHT,
				0,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				0,//�A�j���[�V�����ԍ��w�i������ς��Ȃ�
				1.0f,//���T�C�Y�w�i���X�g2�݂����ɕς�������������
				1.0f,//�c�T�C�Y
				1//���̃p�^�[����
			);
		}
		else if (Score == SCORE::SCORE_A)
		{
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(TextureANo));//&Result_alpha_a);
		//�T�C�Y���C��t���悤�B
			static float patern = 0;
			DrawSpriteColorRotate(
				SCREEN_WIDTH / 2,
				SCREEN_HEIGHT / 2,
				SCREEN_WIDTH,
				SCREEN_HEIGHT,
				0,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				0,//�A�j���[�V�����ԍ��w�i������ς��Ȃ�
				1.0f,//���T�C�Y�w�i���X�g2�݂����ɕς�������������
				1.0f,//�c�T�C�Y
				1//���̃p�^�[����
			);
		}
		else if (Score == SCORE::SCORE_B)
		{
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(TextureBNo));//&Result_alpha_b);
		//�T�C�Y���C��t���悤�B
			static float patern = 0;
			DrawSpriteColorRotate(
				SCREEN_WIDTH / 2,
				SCREEN_HEIGHT / 2,
				SCREEN_WIDTH,
				SCREEN_HEIGHT,
				0,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				0,//�A�j���[�V�����ԍ��w�i������ς��Ȃ�
				1.0f,//���T�C�Y�w�i���X�g2�݂����ɕς�������������
				1.0f,//�c�T�C�Y
				1//���̃p�^�[����
			);
		}
	}

	
}

void SetTime(int time)
{
	g_Time = time;
}
void SetBlock(int block)
{
	g_Block = block;
}
