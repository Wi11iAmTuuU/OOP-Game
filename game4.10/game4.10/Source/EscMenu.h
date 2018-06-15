#pragma once
#include "Map.h"
namespace game_framework
{
	class EscMenu
	{
	public:
		EscMenu();							// 設定為初始值
		void Initialize();					// 設定為初始值
		void LoadBitmap();					// 載入圖形
		void OnShow();						// 將圖形貼到畫面
		void clickLeft();					// 向左一格
		void clickRight();					// 向右一格
		int  clickEnter();					// 進入狀態
		bool GetMusicState();				// 取得音樂狀態
		void SetState(int s);
	protected:
		CAnimation Empty;					// 遊戲開始
		CAnimation FingerHomeVolume;		// 遊戲開始
		CAnimation FingerHomeMute;			// 遊戲開始
		CAnimation FingerReVolume;			// 音樂開啟
		CAnimation FingerReMute;			// 音樂關閉
		CAnimation FingerVolume;			// 遊戲開始
		CAnimation FingerMute;				// 遊戲開始
		int state;							// 目前狀態 
											// 0->EMPTY 1->回到大廳 2->關卡重製 3->音樂啟閉
		bool MusicState;					// 音樂狀態
	};
}
