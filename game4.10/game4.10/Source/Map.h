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
		void StorePortal();                 // 存儲地圖傳送們位子
        void ReadMap(int);					// 載入地圖
        void OnMove(int, int);              // 地圖移動
        void OnShow(int);					// 將圖形貼到畫面
        void SetXY(int nx, int ny);         // 設定螢幕畫面左上角的座標
        void SetCheckpoint(int, int);		// 設定記錄點座標
        bool isEmpty(int x, int y);         // 判斷碰壁;
        int	 Getsx();						// 計數器用
        int	 Getsy();						// 計數器用
        int	 GetCheckpointX();				// 記錄點用
        int	 GetCheckpointY();				// 記錄點用
		int  GetPortalX(int);				// 傳送門用
		int  GetPortalY(int);				// 傳送門用
        //int  GetMapNumber();				// 取的地圖編號
        //void ChangeMapNumber(int);             //改變地圖編號
protected:
	CMovingBitmap background;			// 地圖
	CMovingBitmap Normalblock;			//顯示一般方塊
	CMovingBitmap LoseSpeedBlock;		//顯示減速方塊
	CMovingBitmap SpeedBlock;			//顯示加速方塊
	CMovingBitmap AutoSpeedBlockRight;  //顯示往右自動方塊
	CMovingBitmap AutoSpeedBlockLeft;   //顯示往左自動方塊
	CMovingBitmap WaterBlock;           //顯示水方塊
	CMovingBitmap CheckpointBlock;		//顯示記錄點方塊
	CMovingBitmap LightCheckpointBlock; //顯示記錄點方塊(開啟)
	CMovingBitmap JumpBlock;			//顯示跳躍方塊
	CMovingBitmap door;                 //顯示門
	CMovingBitmap PortalBlock;          //顯示傳送門
private:
	int sx, sy;							// 左上角座標
	int Map1[30][40] = { 0 };   // 1 = 一般方塊 2 = 減速方塊 3 = 加速方塊 4 = 向右自動方塊 5 = 向左自動方塊 
								// 6 = 跳躍方塊 9 = 水方塊 10 = CheckPoint 12 = 門 傳送門 = 50~59 
	int Portal[20][2] = { 0 };
	int CheckpointX, CheckpointY;
};
}
