#pragma once
//マクロ

//シーン番号
enum SCENE
{
	SCENE_NONE = 0, 
	SCENE_TITLE,
	SCENE_SELECT,
	SCENE_SHOP,
	SCENE_GAME,
	SCENE_SCORE,
	SCENE_GAMEOVER,
	SCENE_MAX//5
};

//prototype宣言
void InitScene(SCENE no);
void UninitScene();
void UpdateScene();
void DrawScene();

void SetScene(SCENE no);//新しいシーンをセットする
void CheckScene();		//シーンの切替リクエストをチェックする