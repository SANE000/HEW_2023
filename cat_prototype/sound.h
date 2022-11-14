
#pragma once

#include <windows.h>
#include "xaudio2.h"//Xaudio�𗘗p�������Ƃ��ɃC���N���[�h


bool InitSound(HWND hWnd);//�T�E���h�̏�����
void UninitSound(void);//�T�E���h�̏I��
//�f�[�^�̃��[�h
int LoadSound(char* pFilename);
//loopcount�Đ�0��K,-1�ȉ��Ń��[�v
void PlaySound(int index, int loopCount);
void StopSound(int index);//��~
void StopSoundAll(void);//�S�Ẳ������~
void SetVolume(int index, float vol);//volume�ύX

//�T�E���h�ǉ�
// 1.�R���g���[���[�Ɠ����^�C�~���O�ŏ��������I���������s��
// 2.�^�C�g���Ȃǂ̃V�[���������Ńf�[�^���[�h���Đ�����(BGM)
// 3.�I�������ōĐ���~(BGM)
// 4.�e,���������������Ń��[�h�͂��Ă���
// 5.�Đ��͂��ꂼ��̃^�C�~���O�ōs����,���[�v���Ƃ�
//   ����Đ�����Ȃ��悤�ɒ���
