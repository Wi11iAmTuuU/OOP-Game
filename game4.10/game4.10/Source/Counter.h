#pragma once
#include"Map.h"
namespace game_framework
{
class Counter
{
    public:
        Counter();
        void LoadBitmap();								// 載入圖形
        void OnShow();								// 將圖形貼到畫面
        void Add(int n);								// 增加整數值
        void ResetDiamondCount();
        int  GetDiamondCount();
    protected:
        CAnimation oneDiamond;		// 動畫1
        CAnimation twoDiamond;		// 動畫2
        CAnimation threeDiamond;	// 動畫3
        CAnimation fourDiamond;		// 動畫4
        CAnimation fiveDiamond;		// 動畫5
    private:
        int DiamondCount;			// 鑽石計數
};
}