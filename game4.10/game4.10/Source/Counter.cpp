#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Counter.h"

namespace game_framework
{
Counter::Counter()
{
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
void Counter::OnShow()
{
    if (DiamondCount == 1)
    {
        oneDiamond.SetTopLeft(0, 0);
        oneDiamond.OnShow();
    }
    else if (DiamondCount == 2)
    {
        twoDiamond.SetTopLeft(0, 0);
        twoDiamond.OnShow();
    }
    else if (DiamondCount == 3)
    {
        threeDiamond.SetTopLeft(0, 0);
        threeDiamond.OnShow();
    }
    else if (DiamondCount == 4)
    {
        fourDiamond.SetTopLeft(0, 0);
        fourDiamond.OnShow();
    }
    else if (DiamondCount == 5)
    {
        fiveDiamond.SetTopLeft(0, 0);
        fiveDiamond.OnShow();
    }
    else {}
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