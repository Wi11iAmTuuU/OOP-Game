#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CCharacter.h"
#include "Map.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CCharacter: Character class
	/////////////////////////////////////////////////////////////////////////////

	CCharacter::CCharacter()
	{
		Initialize();
		//
		const int INITIAL_VELOCITY = 10;	// 初始上升速度
		//const int FLOOR = 1095;				// 地板座標
		floor = 1095;
		rising = true;
		falling = true;
		initial_velocity = INITIAL_VELOCITY;
		velocity = initial_velocity;
		IsJumping = false;
		//
	}

	int CCharacter::GetX1()
	{
		return x;
	}

	int CCharacter::GetY1()
	{
		return y;
	}

	int CCharacter::GetX2()
	{
		return x + animation.Width();
	}

	int CCharacter::GetY2()
	{
		return y + animation.Height();
	}

	void CCharacter::Initialize()
	{
		const int X_POS = 960;
		const int Y_POS = 1095;
		x = X_POS;
		y = Y_POS;
		isMovingLeft = isMovingRight = isMovingJump = isMovingDown =false;
	}

	void CCharacter::LoadBitmap()
	{
		animation.AddBitmap("RES\\Character1.bmp", RGB(255, 255, 255));
		animation_Underarm.AddBitmap("RES\\CharacterD.bmp", RGB(255, 255, 255));
		animation_Left.AddBitmap("RES\\CharacterL.bmp", RGB(255, 255, 255));
	}

	void CCharacter::OnMove(Map *m)
	{
		const int STEP_SIZE = 5;
		int i, j;
		animation.OnMove();
		if (isMovingLeft && !isMovingDown) {
			for (i = 0; i < animation.Height(); i++) {  //判斷往左邊走兩個格有沒有撞到障礙物
				if (!(m->isEmpty(x - 5, y + i))) {
					break;
				}
			}
			for (j = 0; j < animation.Width(); j++) {
				if (!(m->isEmpty(x + j, y + animation.Height()))) {
					falling = false;
					break;
				}
				else falling = true;
			}
			if (i == animation.Height()) {  
				x -= STEP_SIZE;
			}
			if (j == animation.Width() && IsJumping == false) {   //判斷下方如果沒東西會掉下去
				while (falling == true) {
					velocity = 1;
					for (i = 0; i < animation.Width(); i++) {
						if (!(m->isEmpty(x + i, y + animation.Height() + velocity))) {
							y = y + velocity - 5;
							velocity = initial_velocity;	// 重設上升初始速度
							falling = false;
							break;
						}
					}
					if (i == animation.Width()) {
						y += velocity;
						velocity++;
					}
				}
			}
		}
		if (isMovingRight && !isMovingDown){
			for (i = 0; i < animation.Height(); i++) {   //判斷往右邊走兩個有沒有撞到障礙物
				if (!(m->isEmpty(x + animation.Width() + 5, y + i))) {
					break;
				}
			}
			for (j = 0; j < animation.Width(); j++) {
				if (!(m->isEmpty(x + j, y + animation.Height()))) {
					falling = false;
					break;
				}
				else falling = true;
			}
			if (i == animation.Height()) {
				x += STEP_SIZE;
			}
			
			if (j == animation.Width() && IsJumping == false) {   //判斷下方如果沒東西會掉下去
				while (falling == true) {
					velocity = 1;
					for (i = 0; i < animation.Width(); i++) {
						if (!(m->isEmpty(x + i, y + animation.Height() + velocity))) {
							y = y + velocity - 5;
							velocity = initial_velocity;	// 重設上升初始速度
							falling = false;
							break;
						}
					}
					if (i == animation.Width()) {
						y += velocity;
						velocity++;
					}
				}
			}
		}
		//
		if (isMovingDown) {
			
		}	
		//
		if (isMovingJump && !IsJumping && !isMovingDown) {
			IsJumping = true;		// 跳躍狀態
		}
		if (isMovingJump && IsJumping == true && rising == false && IsJumpTwice == false) {
			IsJumpTwice = true;				// 二段跳啟動
			rising = true;					// 重設上升狀態
			velocity = initial_velocity;	// 重設上升初始速度
		}
		//
		if (IsJumping == true) {
			if (isMovingDown) {
				isMovingDown = false;
			}
			if (rising) {			// 上升狀態
				if (velocity > 0) {
					for (i = 0; i < animation.Width(); i++) {  //上升時判斷上方是否有碰撞到東西
						if (!(m->isEmpty(x + i, y - velocity))) {
							rising = false;
							velocity = 1;
							break;
						}
					}
					if (i == animation.Width()) {
						y -= velocity;	// 當速度 > 0時，y軸上升(移動velocity個點，velocity的單位為 點/次)
						velocity--;		// 受重力影響，下次的上升速度降低
					}
				}
				else {
					rising = false; // 當速度 <= 0，上升終止，下次改為下降
					velocity = 1;	// 下降的初速(velocity)為1
				}
			}
			else {				// 下降狀態
				for (i = 0; i < animation.Width(); i++) {
					if (!(m->isEmpty(x + i, y + animation.Height() + velocity))) {
						y = y + velocity - 5;
						rising = true;
						velocity = initial_velocity;	// 重設上升初始速度
						IsJumping = false;				// 跳躍狀態結束
						IsJumpTwice = false;
						break;
					}
				}
				if (i == animation.Width()) {

					y += velocity;
					velocity++;

				}
				//if (y < floor - 1) {  // 當y座標還沒碰到地板
				//	y += velocity;	// y軸下降(移動velocity個點，velocity的單位為 點/次)
				//	velocity++;		// 受重力影響，下次的下降速度增加
				//}
				//else {
				//	y = floor - 1;  // 當y座標低於地板，更正為地板上
				//	rising = true;	// 探底反彈，下次改為上升
				//	velocity = initial_velocity;	// 重設上升初始速度
				//	IsJumping = false;				// 跳躍狀態結束
				//	IsJumpTwice = false;			// 二段跳結束
				//}
			}
		}
		//
	}

	void CCharacter::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void CCharacter::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}

	void CCharacter::SetMovingJump(bool flag)
	{
		isMovingJump = flag;
	}

	void CCharacter::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	void CCharacter::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void CCharacter::OnShow(Map *m)
	{
		if (isMovingDown && !IsJumping)
		{
			animation_Underarm.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
			animation_Underarm.OnShow();
		}
		else if(isMovingLeft){
			animation_Left.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
			animation_Left.OnShow();
		}
		else
		{
			animation.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
			animation.OnShow();
		}
	}
}