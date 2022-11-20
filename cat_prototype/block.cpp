#include "main.h"
#include "block.h"
#include "shop.h"
#include "texture.h"
#include "sprite.h"
#include "camera.h"

//�v���g�^�C�v�錾
void InitStage11();
void InitStage12();
//==========================================
//�O���[�o���ϐ�
//==========================================
//��@�p
static double map_pos = 0;
//�n�ʂ⑫��̔���Ɏg��
static BLOCK g_Block[BLOCK_MAX];
//==========================================
//�X�e�[�W�I�ԕϐ�
//==========================================

//�X�e�[�W�I���e�X�g�p�Ȃ̂Ŏ蓮�őI�ԁB
//�X�e�[�W�I����ʂ��ł��������������Ă�������
static int stage = 1;
//stage = 0 �� stage11(), ����ȊO��stage12()���I�΂��悤�ɂȂ��Ă��܂�

//�u���b�N���K�������ς����{�^���Ɣ��]�u���b�N�͐ݒu���܂��������g�̋@�\��
//�Ȃɂ�����ĂȂ��̂ŒS���҂���@�\������낵�����肢���܂��I

HRESULT InitBlock()
{
	//BLOCK�\���̂̏�����
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		//�e�N�X�`�����[�h �摜�̖��O�����悤
		g_Block[i].texNo = LoadTexture((char*)"data\\texture\\block.png");
	}
	//�X�e�[�W�e�X�g
	if (stage == 0)
	{
		//����u���b�N�̐ݒu.��ԍŌ�ɐݒ�
		InitStage11();
	}
	else
	{
		InitStage12();
	}
	//
	return S_OK;
}
//�I������
void UnInitBlock()
{

}
//�X�V����
void UpdateBlock()
{
	//�}�b�v�{�^���������ꂽ��
	if (WatchMapFlag() == true)
	{//��ʒ[�ɂȂ�܂ō��W�������Ă���
		if (map_pos <= -SCREEN_WIDTH * 5)
		{
			//��ʒ[�ɂȂ�����~�߂�
			map_pos += 0;
		}
		else
		{
			map_pos -= WATCH;
		}
	}
	else
	{
		//�}�b�v�{�^����������ĂȂ��Ȃ�0�ɂ���
		map_pos = 0;
	}
}
//�`�揈��
void DrawBlock()
{
	D3DXVECTOR2 basePos = GetBase();

	//�����Ȃ��X�e�[�W�u���b�N
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (g_Block[i].use == true)
		{
			//�u���b�N�ɂ���ăp�^�[���̕ύX
			//�p�^�[���ɂ���Č��ʂ������Ă���������
			//stage11�ł�
			//21~29 or 33~44 or 108~110�͕\�ʂł͖������֕ύX
			//stage12�ł�
			if (stage == 0)
			{
				if (i >= 21 && i <= 29 || i >= 33 && i <= 44 || i >= 108 && i <= 110)
				{
					//�����Ȃ��^�C�v�̏��u���b�N
					g_Block[i].Patern = 1.0f;
				}
				else
				{
					//������
					g_Block[i].Patern = 0.0f;
				}
			}
			else
			{
				if (i >= 9 && i <= 14 || i >= 67 && i <= 69 || i >= 102 && i <= 106)
				{
					//�����Ȃ��^�C�v�̏��u���b�N
					g_Block[i].Patern = 1.0f;
				}
				else if(i == 73 || i == 86)
				{
					//���]�u���b�N
					g_Block[i].Patern = 2.0f;
				}
				else if (i == 54)
				{
					//�{�^���u���b�N
					g_Block[i].Patern = 3.0f;
				}
				else
				{
					//������
					g_Block[i].Patern = 0.0f;
				}
			}
			//�e�N�X�`���̃Z�b�g
			GetDeviceContext()->PSSetShaderResources
			(0, 1, GetTexture(g_Block[i].texNo));
			//�X�v���C�g�̕`��
			DrawSpriteColorRotate
			(
			map_pos + basePos.x + g_Block[i].pos.x,
			basePos.y + g_Block[i].pos.y,
			DRAW_SIZE,
			DRAW_SIZE,
			g_Block[i].rot,
			g_Block[i].col,
			g_Block[i].Patern,
			1.0f/7.0f,//��
			1.0f,//�c
			7//������
			);
		}
	}	
}
//�\���̂̐擪�|�C���^��Ԃ��@�F���g����悤��
BLOCK *GetBlock()
{
	return &g_Block[0];
}
void InitStage12()
{
	//����Ɋւ��Ă�,�U�[�b�ƕ��ׂ銴���ɂ��Ă݂܂���
	//���� �� 16 �}�X * �c 9 �}�X�@�Ł@����Ă܂�
	// X�����@��ʍ��[����E�� * ����(�}�X)
	// Y�����@��ʉ��[������ * ����(�}�X)
	//�傫�Ȍ`���Ƃɕ�����Ƃ킩��₷������
	g_Block[0].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 0, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[1].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 1, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[2].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 2, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[3].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 3, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[4].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 4, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[5].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 5, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[6].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 6, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[7].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 7, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[8].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//�y
	g_Block[9].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[10].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[11].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[12].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 6);
	g_Block[13].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[14].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 8);
	//�������畁��
	g_Block[15].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 9, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[16].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 10, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[17].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 11, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[18].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 9, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[19].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 10, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[20].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 11, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[21].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 12, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[22].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[23].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 14, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[24].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 12, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[25].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[26].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 14, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[27].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[28].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 16, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[29].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 17, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[30].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 18, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[31].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 19, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[32].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 20, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[33].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 27, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[34].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 28, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[35].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 29, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[36].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 30, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[37].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 31, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[38].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 32, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[39].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 33, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[40].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 34, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[41].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 35, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[42].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 36, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[43].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 37, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[44].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 38, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[45].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 36, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[46].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 37, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[47].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 38, DEFO_SIZE_Y - DRAW_SIZE * 2);

	g_Block[48].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 39, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[49].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 40, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[50].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 41, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[51].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 39, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[52].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 40, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[53].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 41, DEFO_SIZE_Y - DRAW_SIZE * 2);
	//�{�^��
	g_Block[54].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 40, DEFO_SIZE_Y - DRAW_SIZE * 3);
	//�������畁��
	g_Block[55].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[56].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 46, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[57].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 47, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[58].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 48, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[59].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 49, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[60].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 50, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[61].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 51, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[62].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 52, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[63].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 53, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[64].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 54, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[65].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 55, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[66].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 56, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//�y
	g_Block[67].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 57, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[68].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 58, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[69].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 59, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//�������畁��
	g_Block[70].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 57, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[71].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 58, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[72].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 59, DEFO_SIZE_Y - DRAW_SIZE * 1);
	//���]�u���b�N
	g_Block[73].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 59, DEFO_SIZE_Y - DRAW_SIZE * 5);
	//�������畁��
	g_Block[74].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 60, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[75].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 61, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[76].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 62, DEFO_SIZE_Y - DRAW_SIZE * 2);

	g_Block[77].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 60, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[78].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 61, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[79].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 62, DEFO_SIZE_Y - DRAW_SIZE * 5);

	g_Block[80].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 63, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[81].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 64, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[82].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 65, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[83].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 66, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[84].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 67, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[85].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 68, DEFO_SIZE_Y - DRAW_SIZE * 2);
	//���]�u���b�N
	g_Block[86].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 69, DEFO_SIZE_Y - DRAW_SIZE * 2);
	//�������畁��
	g_Block[87].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 69, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[88].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 70, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[89].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 71, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[90].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 72, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[91].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 73, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[92].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 74, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[93].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 75, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[94].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 76, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[95].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 77, DEFO_SIZE_Y - DRAW_SIZE * 5);

	g_Block[96].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 78, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[97].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 79, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[98].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 80, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[99].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 81, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[100].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 82, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[101].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 83, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//�y
	g_Block[102].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 83, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[103].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 83, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[104].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 83, DEFO_SIZE_Y - DRAW_SIZE * 6);
	g_Block[105].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 83, DEFO_SIZE_Y - DRAW_SIZE * 7);
	g_Block[106].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 83, DEFO_SIZE_Y - DRAW_SIZE * 8);
	//�������畁��
	g_Block[107].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 84, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[108].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 85, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[109].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 86, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[110].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 84, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[111].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 85, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[112].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 86, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_Block[113].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 87, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[114].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 88, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[115].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 89, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[116].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 87, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[117].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 88, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[118].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 89, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_Block[119].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 90, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[120].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 91, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[121].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 92, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[122].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 93, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[123].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 94, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[124].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 95, DEFO_SIZE_Y - DRAW_SIZE * 0);
	//�u���b�N�]�莩�R�Ɏg���Ă�������
	g_Block[125].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 95, DEFO_SIZE_Y - DRAW_SIZE * 0);
}

void InitStage11()
{
	//����Ɋւ��Ă�,�U�[�b�ƕ��ׂ銴���ɂ��Ă݂܂���
	//���� �� 16 �}�X * �c 9 �}�X�@�Ł@����Ă܂�
	// X�����@��ʍ��[����E�� * ����(�}�X)
	// Y�����@��ʉ��[������ * ����(�}�X)
	//�傫�Ȍ`���Ƃɕ�����Ƃ킩��₷������
	g_Block[0].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 0, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[1].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 1, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[2].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 2, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[3].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 3, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[4].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 4, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[5].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 5, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[6].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 6, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[7].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 7, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[8].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 8, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[9].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 9, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[10].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 10, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[11].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 11, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[12].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 12, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[13].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 13, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[14].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 14, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[15].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 15, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[16].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 16, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[17].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 17, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[18].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 18, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[19].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 19, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[20].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 20, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[21].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 21, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[22].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 22, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[23].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[24].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 21, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[25].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 22, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[26].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[27].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 21, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[28].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 22, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[29].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 2);

	g_Block[30].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 21, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[31].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 22, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[32].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 23, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[33].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 24, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[34].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 25, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[35].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 26, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[36].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 24, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[37].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 25, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[38].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 26, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[39].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 24, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[40].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 25, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[41].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 26, DEFO_SIZE_Y - DRAW_SIZE * 2);
	g_Block[42].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 24, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[43].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 25, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[44].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 26, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[45].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 24, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[46].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 25, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[47].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 26, DEFO_SIZE_Y - DRAW_SIZE * 4);

	g_Block[48].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 27, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[49].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 28, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[50].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 29, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[51].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 30, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[52].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 31, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[53].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 32, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[54].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 33, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[55].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 34, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[56].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 35, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[57].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 39, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[58].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 40, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[59].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 41, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[60].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 42, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[61].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 43, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[62].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 44, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[63].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 45, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[64].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 46, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[65].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 47, DEFO_SIZE_Y - DRAW_SIZE * 0);
	
	g_Block[66].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 48, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[67].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 49, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[68].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 50, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[69].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 51, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[70].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 52, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[71].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 53, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[72].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 54, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[73].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 55, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[74].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 56, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[75].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 57, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[76].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 58, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[77].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 59, DEFO_SIZE_Y - DRAW_SIZE * 4);
	g_Block[78].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 60, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[79].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 61, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[80].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 62, DEFO_SIZE_Y - DRAW_SIZE * 5);
	g_Block[81].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 63, DEFO_SIZE_Y - DRAW_SIZE * 6);
	g_Block[82].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 64, DEFO_SIZE_Y - DRAW_SIZE * 6);
	g_Block[83].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 65, DEFO_SIZE_Y - DRAW_SIZE * 6);

	g_Block[84].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 69, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[85].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 70, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[86].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 71, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[87].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 72, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[88].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 73, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[89].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 74, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[90].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 75, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[91].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 76, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[92].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 77, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[93].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 75, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[94].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 76, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[95].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 77, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[96].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 78, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[97].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 79, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[98].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 80, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[99].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 78, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[100].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 79, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[101].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 80, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[102].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 81, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[103].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 82, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[104].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 83, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[105].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 81, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[106].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 82, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[107].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 83, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[108].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 84, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[109].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 85, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[110].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 86, DEFO_SIZE_Y - DRAW_SIZE * 0);

	g_Block[111].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 84, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[112].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 85, DEFO_SIZE_Y - DRAW_SIZE * 1);
	g_Block[113].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 86, DEFO_SIZE_Y - DRAW_SIZE * 1);

	g_Block[114].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 84, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[115].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 85, DEFO_SIZE_Y - DRAW_SIZE * 3);
	g_Block[116].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 86, DEFO_SIZE_Y - DRAW_SIZE * 3);

	g_Block[117].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 87, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[118].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 88, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[119].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 89, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[120].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 90, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[121].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 91, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[122].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 92, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[123].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 93, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[124].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 94, DEFO_SIZE_Y - DRAW_SIZE * 0);
	g_Block[125].pos = D3DXVECTOR2(DEFO_SIZE_X + DRAW_SIZE * 95, DEFO_SIZE_Y - DRAW_SIZE * 0);
}

