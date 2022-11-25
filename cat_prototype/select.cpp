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

void InitSelect()
{
	InitStageSelect();
}
void UpdateSelect()
{
	UpdateStageSelect();
}
void UninitSelect() 
{
	UnInitStageSelect();
}
void DrawSelect()
{
	DrawStageSelect();
}