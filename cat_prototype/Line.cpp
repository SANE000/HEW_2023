
#include "main.h"
#include "Line.h"

//===========================
//�v���g�^�C�v�錾
//===========================
void SetVertex(D3DXVECTOR3, D3DXVECTOR3, D3DXCOLOR);	//������\������

//=============================
//�O���[�o���ϐ�
//=============================
static	ID3D11Buffer		*g_VertexBuffer = NULL;		// ���_���


void InitLine()
{
	// ���_�o�b�t�@����
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(VERTEX_3D) * 2;//���_1�����_���̃T�C�Y�ō��
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);
		// ���_�o�b�t�@�X�V
		D3DXVECTOR3 st = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 ed = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		D3DXCOLOR	col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);

		SetVertex(st, ed, col);
	}
}

void UninitLine()
{
	// ���_�o�b�t�@�̉��
	if (g_VertexBuffer)
	{
		g_VertexBuffer->Release();//�g���I������̂ŉ������
		g_VertexBuffer = NULL;
	}

}

void DrawLine()
{
	// �\���������|���S���̒��_�o�b�t�@��ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);// LINELIST);

	//�\������
	static float startposX = 0;
	static float startposY = 0;

	D3DXVECTOR3 st = D3DXVECTOR3(startposX, startposY, 0.0f);
	D3DXVECTOR3 ed = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	D3DXCOLOR	col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	SetVertex(st, ed, col);

	startposX = cosf(1) * 100.0f;	//�J�n���W�̍X�V
	startposY = sinf(1) * 100.0f;



	// �|���S���`��
	GetDeviceContext()->Draw(2, 0);

}

void UpdateLine()
{
}


//=============================================================================
// ���_�f�[�^�ݒ�
//	�J�n���W, �I�����W, �F
//=============================================================================
void SetVertex(D3DXVECTOR3 StartPos, D3DXVECTOR3 EndPos, D3DXCOLOR color)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	//���_�o�b�t�@�ւ̏������݋������炤
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	//��{�ڂ̒����̒��_���Z�b�g
	vertex[0].Position = StartPos;
	vertex[0].Diffuse = color;
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = EndPos;
	vertex[1].Diffuse = color;
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	////��{�ڂ̒����̒��_���Z�b�g
	//vertex[2].Position = D3DXVECTOR3(SCREEN_WIDTH / 2, 0.0f + 50.0f, 0.0f);
	//vertex[2].Diffuse = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
	//vertex[2].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	//vertex[3].Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50.0f, 0.0f);
	//vertex[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	//vertex[3].TexCoord = D3DXVECTOR2(1.0f, 0.0f);



	GetDeviceContext()->Unmap(g_VertexBuffer, 0);
}
