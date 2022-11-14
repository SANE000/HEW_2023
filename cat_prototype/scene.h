#pragma once
//�}�N��

//�V�[���ԍ�
enum SCENE
{
	SCENE_NONE = 0,
	SCENE_SHOP,
	SCENE_GAME,
	SCENE_MAX//4
};

//prototype�錾
void InitScene(SCENE no);
void UninitScene();
void UpdateScene();
void DrawScene();

void SetScene(SCENE no);//�V�����V�[�����Z�b�g����
void CheckScene();		//�V�[���̐ؑփ��N�G�X�g���`�F�b�N����