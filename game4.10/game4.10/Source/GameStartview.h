#pragma once
namespace game_framework
{
class GameStartView
{
    public:
        GameStartView();					// 設定為初始值
		void Initialize();					// 設定為初始值
        void LoadBitmap();					// 載入圖形
        void OnShow();						// 將圖形貼到畫面
        void clickLeft();					// 向左一格
        void clickRight();					// 向右一格
        int  clickEnter();					// 進入狀態
    protected:
		CAnimation FingerPlay;				// 遊戲開始
		CAnimation FingerQuestion;			// 說明開始
		CAnimation Question;				// 說明
        int state;							// 目前狀態
};
}