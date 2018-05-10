#pragma once
#include"Map.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供可以用鍵盤或滑鼠控制的擦子
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////

	class CCharacter
	{
	public:
		CCharacter();
		int  GetX1();					// 擦子左上角 x 座標
		int  GetY1();					// 擦子左上角 y 座標
		int  GetX2();					// 擦子右下角 x 座標
		int  GetY2();					// 擦子右下角 y 座標
		void Initialize();				// 設定擦子為初始值
		void LoadBitmap();				// 載入圖形
		void OnMove(Map*,int*);					// 移動擦子
		void OnShow(Map*);					// 將擦子圖形貼到畫面
		void SetMovingLeft(bool flag);	// 設定是否正在往左移動
		void SetMovingRight(bool flag); // 設定是否正在往右移動
		void SetMovingJump(bool flag);	// 設定是否正在往上移動
		void SetMovingDown(bool flag);	// 設定是否正在往下移動
		//
		void SetMovingFly(bool flag);	// 設定是否正在往下移動
		//
		void SetXY(int nx, int ny);		// 設定擦子左上角座標
		int  GetMapNumber();				// 取的地圖編號
		void ChangeMapNumber(int);             //改變地圖編號
	protected:
		CAnimation animation;		// 擦子的動畫
		CAnimation animation_Underarm;		// 擦子的動畫
		CAnimation animation_Left;		// 擦子的動畫
		CAnimation animation_right;		// 擦子的動畫
		int x, y;					// 擦子左上角座標
		int MapNumber;
		//
		int floor;				// 地板的Y座標
		bool rising;			// true表上升、false表下降
		bool falling;           // true表下降、false表上升
		int initial_velocity;	// 初始速度
		int velocity;			// 目前的速度(點/次)
		bool IsJumping;			// true表跳耀、false表非跳耀
		bool IsJumpTwice;		// true表已二段跳、false表未二段跳
		bool Isfalling;
		//
		bool isMovingFly;
		//
		bool isMovingLeft;			// 是否正在往左移動
		bool isMovingRight;			// 是否正在往右移動
		bool isMovingJump;			// 是否正在往上移動
		bool isMovingDown;			// 是否正在往下移動
	};
}