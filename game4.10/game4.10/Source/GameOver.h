#pragma once
namespace game_framework
{
	class GameOver
	{
	public:
		GameOver();							// 設定為初始值
		void Initialize();					// 設定為初始值
		void LoadBitmap();					// 載入圖形
		void OnShow();						// 將圖形貼到畫面
	protected:
		CAnimation congratulations;					// 遊戲開始
		int y;
	};
}