
#include "main.h"
#include "Linecircle.h"

//===========================
//�v���g�^�C�v�錾
//===========================
void SetVertexCircle(D3DXVECTOR3, float, int);	//���p�`��\������
//�\�����W�@���a�@���_��

//=============================
//�O���[�o���ϐ�
//=============================
static	ID3D11Buffer		*g_VertexBuffer = NULL;		// ���_���


void InitLineCircle()
{
	// ���_�o�b�t�@����
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(VERTEX_3D) * 65;//���_1�����_���̃T�C�Y�ō��
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);
		// ���_�o�b�t�@�X�V
		D3DXVECTOR3 position = D3DXVECTOR3(100.0f, 200.0f, 0.0f);

		SetVertexCircle(position, 100.0f, 64);
	}
}

void UninitLineCircle()
{
	// ���_�o�b�t�@�̉��
	if (g_VertexBuffer)
	{
		g_VertexBuffer->Release();//�g���I������̂ŉ������
		g_VertexBuffer = NULL;
	}

}

void DrawLineCircle()
{
	// �\���������|���S���̒��_�o�b�t�@��ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);// LINELIST);


	D3DXVECTOR3 position = D3DXVECTOR3(100.0f,200.0f, 0.0f);

	SetVertexCircle(position, 100.0f, 64);


	// �|���S���`��
	GetDeviceContext()->Draw(64 + 1, 0);

}

void UpdateLineCircle()
{
}


//=============================================================================
// ���_�f�[�^�ݒ�
//	�J�n���W, ���a, ���_��
//=============================================================================
void SetVertexCircle(D3DXVECTOR3 Pos, float Rad, int NumVertex)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	//���_�o�b�t�@�ւ̏������݋������炤
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;//��������ł����|�C���^�����炦��

	float kakudo = 0;
	float rad = D3DXToRadian(kakudo);
	float x, y = 0;

	for (int i = 0; i < NumVertex; i++)
	{
		//��{�ڂ̒����̒��_���Z�b�g
		vertex[i].Position.x = cosf(D3DXToRadian(kakudo)) * Rad + Pos.x;
		vertex[i].Position.y = sinf(D3DXToRadian(kakudo)) * Rad + Pos.y;
		vertex[i].Position.z = 0;


		vertex[i].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[i].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		kakudo += (360.0f / NumVertex);
	}


	for (int i = 0; i < NumVertex; i++)
	{
		x = vertex[i].Position.x * cosf(rad) - vertex[i].Position.y * sin(rad);
		y = vertex[i].Position.x * sinf(rad) + vertex[i].Position.y * cos(rad);


		vertex[i].Position.x = x + SCREEN_WIDTH /2;
		vertex[i].Position.y = y + SCREEN_HEIGHT / 2;
	}


	//�Ō�̒��_�͐퓬�̒��_�Ɠ���
	vertex[NumVertex] = vertex[0];



	GetDeviceContext()->Unmap(g_VertexBuffer, 0);
}
