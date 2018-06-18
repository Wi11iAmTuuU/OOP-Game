#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "GameStartview.h"
namespace game_framework
{
GameStartView::GameStartView()
{
	Initialize();
}
void GameStartView::Initialize()
{
	state = 0;				// 最初始(遊戲開始)
}
void GameStartView::LoadBitmap()
{
	FingerPlay.AddBitmap("RES\\Menu\\Menu_fingerplay.bmp");
	FingerQuestion.AddBitmap("RES\\Menu\\Menu_fingerquestion.bmp");
	Question.AddBitmap("RES\\Menu\\Menu_question.bmp");
}
void GameStartView::OnShow()
{
    if (state == 0)
    {
		FingerPlay.SetTopLeft(0, 0);
		FingerPlay.OnShow();
    }
    else if (state == 1)
    {
		FingerQuestion.SetTopLeft(0, 0);
		FingerQuestion.OnShow();
    }
    else if (state == 2)
    {
		Question.SetTopLeft(0, 0);
		Question.OnShow();
    }
}
void GameStartView::clickLeft()
{
    if (state == 1)
    {
        state = 0;
    }
	else {}	
}
void GameStartView::clickRight()
{
    if (state == 0)
    {
        state = 1;
    }
	else {}
}
int GameStartView::clickEnter()
{
    if (state == 0)
    {
        return 1;
    }
    else if(state == 1)
    {
		state = 2;
    }
	else
	{
		state = 1;	
	}
	return 0;
}
}