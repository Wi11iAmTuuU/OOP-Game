#pragma once
namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供可以用鍵盤或滑鼠控制的擦子
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////

	class Map
	{
	public:
		int  GetWidth();                    // 取得背景寬度
		int  GetHeight();                   // 取得背景高度
		int  ScreenX(int x);				// 螢幕 x 座標
		int  ScreenY(int y);				// 螢幕 y 座標
		int  GetBlock(int x, int y);		// 取得方塊
		void Initialize();					// 設定為初始值
		void LoadBitmap();					// 載入圖形
		void ReadMap(int);						// 載入地圖
		void OnMove(int, int);              // 地圖移動
		void OnShow(int);						// 將圖形貼到畫面
		void SetXY(int nx, int ny);         // 設定螢幕畫面左上角的座標
		bool isEmpty(int x, int y);         // 判斷碰壁;
		int	 Getsx();						// 計數器用
		int	 Getsy();						// 計數器用
		//int  GetMapNumber();				// 取的地圖編號
		//void ChangeMapNumber(int);             //改變地圖編號
	protected:
		CMovingBitmap background;			// 地圖
		CMovingBitmap Normalblock;			//顯示一般方塊
		CMovingBitmap LoseSpeedBlock;		//顯示減速方塊
		CMovingBitmap SpeedBlock;			//顯示加速方塊
		CMovingBitmap door;                 //顯示門
	private:
		int sx, sy;							// 左上角座標
		int Map1[30][40] = { 0 };   // 1 = 一般方塊 2 = 減速方塊 3 = 加速方塊 11 = 門

	};
}
