#include "main.h"
#include "renderer.h"
#include "Game.h"
#include "polygon.h"
#include "timer.h"
#include "collision.h"
#include "sound.h"
#include "blocktype.h"
#include "camera.h"
#include "result.h"
#include "Select.h"
#include "StageSelect.h"
#include "selectUI.h"

void InitSelect()
{
	InitselUI();
	InitStageSelect();
}
void UpdateSelect()
{
	UpdateStageSelect();
	UpdateselUI();
}
void UninitSelect()
{
	UnInitStageSelect();
	UnInitselUI();
}
void DrawSelect()
{
	DrawStageSelect();
	DrawselUI();
}