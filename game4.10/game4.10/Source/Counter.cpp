#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Counter.h"

namespace game_framework {
	Counter::Counter()
	{
		x = y = 0;
		DiamondCount = 0;
	}
	void Counter::LoadBitmap()
	{
		oneDiamond.AddBitmap("RES\\counter\\oneDiamond.bmp", RGB(255, 255, 255));
		twoDiamond.AddBitmap("RES\\counter\\twoDiamond.bmp", RGB(255, 255, 255));
		threeDiamond.AddBitmap("RES\\counter\\threeDiamond.bmp", RGB(255, 255, 255));
		fourDiamond.AddBitmap("RES\\counter\\fourDiamond.bmp", RGB(255, 255, 255));
		fiveDiamond.AddBitmap("RES\\counter\\fiveDiamond.bmp", RGB(255, 255, 255));
	}
	void Counter::OnShow(Map *m)
	{
		if (DiamondCount == 1) {
			oneDiamond.SetTopLeft(x,y);
			oneDiamond.OnShow();
		}else if (DiamondCount == 2) {
			twoDiamond.SetTopLeft(x, y);
			twoDiamond.OnShow();
		}else if (DiamondCount == 3) {
			threeDiamond.SetTopLeft(x, y);
			threeDiamond.OnShow();
		}else if (DiamondCount == 4) {
			fourDiamond.SetTopLeft(x, y);
			fourDiamond.OnShow();
		}else if (DiamondCount == 5) {
			fiveDiamond.SetTopLeft(x, y);
			fiveDiamond.OnShow();
		}
		else{}
	}
	void Counter::SetMapXY(Map *m)
	{
		x = m->Getsx();
		y = m->Getsy();
	}
	void Counter::Add(int n)
	{
		DiamondCount += n;
	}
	void Counter::ResetDiamondCount()
	{
		DiamondCount = 0;
	}
	int Counter::GetDiamondCount()
	{
		return DiamondCount;
	}
}