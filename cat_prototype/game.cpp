#include "main.h"
#include "renderer.h"
#include "Game.h"
#include "polygon.h"
#include "player.h"
#include "cat.h"
#include "block.h"
#include "blockpreview.h"
#include "timer.h"
#include "etcUI.h"
#include "collision.h"
#include "sound.h"
#include "blocktype.h"
#include "camera.h"
#include "result.h"

//�}�N����`
//���Ƃ̓^�C���\���A

//==========================================
//�O���[�o���ϐ�
//==========================================

//������
void InitGame()
{
	////////////////�Q�[���֘A�̏�����
//�|���S���̏�����
		//�T�E���h�̃��[�h
	//char filename[] = "data\\BGM\\sample000.wav";
	//GameSoundNo = LoadSound(filename);
	//PlaySound(GameSoundNo, -1);
	//SetVolume(GameSoundNo,0.1f);
	//�w�i�̏�����
	InitPolygon();
	InitEtc();
	//�^�C�}�[�̏�����
	InitTime();
	//�X�e�[�W�̏�����
	InitCamera();
	InitPlayer();
	InitCat();
	InitBlock();
	InitPreview();
	InitCollsion();
	InitResult();


	///////////////////////////////
}
//�X�V����
void UninitGame()
{
	////////////////�Q�[���֘A
	//BGM�̏I��
	//StopSound(GameSoundNo);
	UnInitBlock();
	UnInitPreview();
	UnInitCat();
	UnInitPlayer();
	UninitCamera();
	UnInitTime();
	UnInitEtc();
	//�w�i�̏I��
	UnInitPolygon();
	////////////////�Q�[���֘A
}
//�I������
void UpdateGame()
{
	////////////////�Q�[���֘A
	//�w�i�̍X�V
	UpdatePolygon();
	UpdateEtc();
	//�X�e�[�W�̍X�V
	UpdatePlayer();
	UpdateCat();
	UpdateCamera();
	UpdateBlock();
	UpdatePreview();
	UpdateCollision();
	UpdateResult();
	////////////////�Q�[���֘A
}
//�`�揈��
void DrawGame()
{
	////////////////�Q�[���֘A
	//�w�i�`��
	DrawPolygon();
	//�u���b�N�̕\��
	DrawBlock();
	DrawPreview();
	//�L�̕\��
	DrawCat();
	//�S�[�����̑�UI
	DrawEtc();
	DrawTime();
	//�v���C���[�̕`��//�͉��̕��ɁI
	DrawPlayer();
	// �o�b�N�o�b�t�@�A�t�����g�o�b�t�@����ւ�
	////////////////�Q�[���֘A
}
