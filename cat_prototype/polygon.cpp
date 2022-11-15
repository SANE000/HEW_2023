/*==============================================================================

   ���_�Ǘ� [polygon.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include	"polygon.h"
#include	"sprite.h"
#include    "texture.h"
#include	"inputx.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NUM_VERTEX 4
#define	NUM_TRIANGLE_VERTEX	(4)	//�O�p�`�p���_��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static	ID3D11ShaderResourceView	*g_BackTexture = NULL;
//�e�N�X�`���̃t�@�C���p�X
static	char	*g_BackTextureName = (char*)"data/texture/background_park.png";
//�e�N�X�`�����ۑ������@�|�C���^�ϐ��̏������� NULL !!
//�摜�P���ɂ��P�K�v�Ȃ̂��c��
//�e�N�X�`���C���f�b�N�X
int TextureBGNo = 0;

float	PositionX = SCREEN_WIDTH / 2;//��ʒ������W
float	PositionY = SCREEN_HEIGHT / 2;

D3DXVECTOR3	MoveVec;

typedef struct
{
	D3DXVECTOR3 Position;
	D3DXVECTOR2 Size;
	D3DXCOLOR Color;
	float Rotate;
}BG;

BG *SampleBG;


//=============================================================================
// ����������
//=============================================================================
HRESULT InitPolygon(void)
{
	SampleBG = new BG;

	SampleBG->Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);
	SampleBG->Size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	SampleBG->Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	SampleBG->Rotate = 0;

	ID3D11Device *pDevice = GetDevice();
	//texture.h�̂������ł����܂Ō��炷���Ƃ��ł���
	/*�����Ńe�N�X�`����ǂݍ��ނ��I(���[�h)*/
	//�ǂݍ��߂Ȃ������狭���I��
	TextureBGNo = LoadTexture(g_BackTextureName);
	if (TextureBGNo == -1)
	{
		exit(999);
	}
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UnInitPolygon(void)
{
	if (SampleBG)
	{
		delete	SampleBG;
		SampleBG = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePolygon(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPolygon(void)
{
	
	//�ϐ������₻��
	{
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(TextureBGNo));//&g_BackTexture);
		//�T�C�Y���C��t���悤�B
		static float patern = 0;
		DrawSpriteColorRotate(
			SampleBG->Position.x,
			SampleBG->Position.y,
			SampleBG->Size.x,
			SampleBG->Size.y,
			SampleBG->Rotate,
			SampleBG->Color,
			0,//�A�j���[�V�����ԍ��w�i������ς��Ȃ�
			1.0f,//���T�C�Y�w�i���X�g2�݂����ɕς�������������
			1.0f,//�c�T�C�Y
			1//���̃p�^�[����
		);
	}
}





