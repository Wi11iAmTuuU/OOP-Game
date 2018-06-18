#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "GameOver.h"
namespace game_framework
{
	GameOver::GameOver()
	{
		Initialize();
	}
	void GameOver::Initialize()
	{
		y = 0;
	}
	void GameOver::LoadBitmap()
	{
		congratulations.AddBitmap("RES\\FINAL\\congratulations.bmp");
	}
	void GameOver::OnShow()
	{
		if (y > -960) {
			congratulations.SetTopLeft(0, y);
			y -= 7;
		}
		congratulations.OnShow();
	}
}