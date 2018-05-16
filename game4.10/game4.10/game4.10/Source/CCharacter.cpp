#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CCharacter.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CCharacter: Character class
	/////////////////////////////////////////////////////////////////////////////

	CCharacter::CCharacter()
	{
		Initialize();
		//
		const int INITIAL_VELOCITY = 10;	// 初始上升速度
		rising = true;
		falling = true;
		initial_velocity = INITIAL_VELOCITY;
		velocity = initial_velocity;
		IsJumping = false;
		Isfalling = false;
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
		const int Y_POS = 1125;
		x = X_POS;
		y = Y_POS;
		isMovingLeft = isMovingRight = isMovingJump = isMovingDown = false;
		isMovingFly = false;
	}

	void CCharacter::LoadBitmap()
	{
		animation.AddBitmap("RES\\Character\\Character1.bmp", RGB(255, 255, 255));
		//
		animation_right.AddBitmap("RES\\Character\\CharacterW1.bmp", RGB(255, 255, 255));
		animation_right.AddBitmap("RES\\Character\\CharacterW2.bmp", RGB(255, 255, 255));
		animation_right.AddBitmap("RES\\Character\\Character1.bmp", RGB(255, 255, 255));
		//
		animation_Underarm.AddBitmap("RES\\Character\\CharacterD.bmp", RGB(255, 255, 255));
		//
		animation_Left.AddBitmap("RES\\Character\\CharacterW1L.bmp", RGB(255, 255, 255));
		animation_Left.AddBitmap("RES\\Character\\CharacterW2L.bmp", RGB(255, 255, 255));
		animation_Left.AddBitmap("RES\\Character\\CharacterL.bmp", RGB(255, 255, 255));
		//
	}

	void CCharacter::OnMove(Map *m,int *MapNumber,Counter *counter)
	{
		const int STEP_SIZE = 5;
		int i, j;
		animation.OnMove();
		if (isMovingLeft && !isMovingDown) {
			for (i = 0; i < animation.Height(); i++) {  //判斷往左邊走兩個格有沒有撞到障礙物
				if ((m->GetBlock(x - 5, y + i) != 0) && (m->GetBlock(x - 5, y + i) != 11) && (m->GetBlock(x - 5, y + i) != 12)) {
					break;
				}
			}
			if (i == animation.Height()) {
				if (((m->GetBlock(x, y + animation.Height() + 2) == 2)) || ((m->GetBlock(x + animation.Width(), y + animation.Height() + 2) == 2))) {
					x -= 2;
				}
				else if (((m->GetBlock(x, y + animation.Height() + 2) == 3)) || ((m->GetBlock(x + animation.Width(), y + animation.Height() + 2) == 3))) {
					x -= 8;
				}
				else {
					x -= STEP_SIZE;
				}
			}
			if (!IsJumping) {
				for (j = 0; j < animation.Width(); j++) {  //判斷往左走時下方有沒有東西且不是跳躍的時候
					/*if (!(m->isEmpty(x + j, y + animation.Height() + 1))) {
						Isfalling = false;
						break;
					}*/
					if ((m->GetBlock(x + j, y + animation.Height() + 1) != 0) && (m->GetBlock(x + j, y + animation.Height() + 1) != 11) && (m->GetBlock(x + j, y + animation.Height() + 1) != 12)) {
						Isfalling = false;
						break;
					}
					else if (!Isfalling) {
						Isfalling = true;
						rising = false;
						velocity = 1;
					}
				}
			}
		}
		if (isMovingRight && !isMovingDown) {
			for (i = 0; i < animation.Height(); i++) {   //判斷往右邊走兩個有沒有撞到障礙物
				if ((m->GetBlock(x + animation.Width() + 5, y + i) != 0) && (m->GetBlock(x + animation.Width() + 5, y + i) != 11) && (m->GetBlock(x + animation.Width() + 5, y + i) != 12)) {
					break;
				}
			}
			if (i == animation.Height()) {
				if (((m->GetBlock(x, y + animation.Height() + 2) == 2)) || ((m->GetBlock(x + animation.Width(), y + animation.Height() + 2) == 2))) {
					x += 2;
				}
				else if (((m->GetBlock(x, y + animation.Height() + 2) == 3)) || ((m->GetBlock(x + animation.Width(), y + animation.Height() + 2) == 3))) {
					x += 8;
				}
				else {
					x += STEP_SIZE;
				}
			}
			if (!IsJumping) {
				for (j = 0; j < animation.Width(); j++) {  //判斷往右走時下方有沒有東西且不是跳躍的時候
					/*if (!(m->isEmpty(x + j, y + animation.Height() + 1))) {
						Isfalling = false;
						break;
					}*/
					if ((m->GetBlock(x + j, y + animation.Height() + 1) != 0) && (m->GetBlock(x + j, y + animation.Height() + 1) != 11) && (m->GetBlock(x + j, y + animation.Height() + 1) != 12)) {
						Isfalling = false;
						break;
					}
					else if (!Isfalling) {
						Isfalling = true;
						rising = false;
						velocity = 1;
					}
				}
			}
		}
		if (Isfalling == true && IsJumping == false) {  //判斷是否為下降狀態
			if (!rising) {
				for (i = 0; i < animation.Width(); i++) {
					for (j = 0; j < velocity; j++) {
						if (!(m->isEmpty(x + i, y + animation.Height() + j))) {
							y = y + j - 2;
							velocity = initial_velocity;	// 重設上升初始速度
							Isfalling = false;
							rising = true;
							break;
						}
					}
					if (j != velocity) break;
				}
				if (i == animation.Width()) {
					y += velocity;
					velocity++;
				}
			}
		}
		if (isMovingDown) {

		}
		//
		if (isMovingJump && IsJumping == false && !isMovingDown) {
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
						for (j = 0; j < velocity; j++) {
							/*if (!(m->isEmpty(x + i, y - j))) {
								rising = false;
								velocity = 1;
								break;
							}*/
							if ((m->GetBlock(x + i, y - j) != 0) && (m->GetBlock(x + i, y - j) != 11) && (m->GetBlock(x + i, y - j) != 12)) {
								rising = false;
								velocity = 1;
								break;
							}
						}
						if (j != velocity)  break;
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
					for (j = 0; j < velocity; j++) {
						//if (!(m->isEmpty(x + i, y + animation.Height() + j))) {  //判斷人物下方是不是有障礙物
						//	y = y + j;
						//	rising = true;
						//	velocity = initial_velocity;	// 重設上升初始速度
						//	IsJumping = false;				// 跳躍狀態結束
						//	IsJumpTwice = false;
						//	break;
						//}
						if ((m->GetBlock(x + i, y + animation.Height() + j) != 0) && (m->GetBlock(x + i, y + animation.Height() + j) != 11) && (m->GetBlock(x + i, y + animation.Height() + j) != 12)) {
							y = y + j;
							rising = true;
							velocity = initial_velocity;	// 重設上升初始速度
							IsJumping = false;				// 跳躍狀態結束
							IsJumpTwice = false;
							break;
						}
					}
					if (j != velocity) break;
				}
				if (i == animation.Width()) {
					y += velocity;
					velocity++;
				}
			}
		}
		//
		if (isMovingFly)
		{
			if (m->GetBlock(x, y) == 11) {
				*MapNumber = 1;
				counter->ResetDiamondCount();
			}
			else if (m->GetBlock(x, y) == 12) {
				*MapNumber = 0;
				counter->ResetDiamondCount();
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

	void CCharacter::SetMovingFly(bool flag)
	{
		isMovingFly = flag;
	}

	void CCharacter::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	int CCharacter::GetMapNumber()
	{
		return MapNumber;
	}
	void CCharacter::ChangeMapNumber(int index)
	{
		MapNumber = index;
	}

	void CCharacter::OnShow(Map *m)
	{
		if (isMovingDown && !IsJumping)
		{
			animation_Underarm.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
			animation_Underarm.OnShow();
		}
		else if (isMovingLeft) {
			animation_Left.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
			animation_Left.OnShow();
			animation_Left.OnMove();
		}
		else if (isMovingRight) {
			animation_right.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
			animation_right.OnShow();
			animation_right.OnMove();
		}
		else
		{
			animation.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
			animation.OnShow();
		}
	}
}