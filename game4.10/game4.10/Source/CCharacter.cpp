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
		const int INITIAL_VELOCITY = 10;	// ��l�W�ɳt��
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
			for (i = 0; i < animation.Height(); i++) {  //�P�_�����䨫��Ӯ榳�S�������ê��
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
				for (j = 0; j < animation.Width(); j++) {  //�P�_�������ɤU�観�S���F��B���O���D���ɭ�
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
			for (i = 0; i < animation.Height(); i++) {   //�P�_���k�䨫��Ӧ��S�������ê��
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
				for (j = 0; j < animation.Width(); j++) {  //�P�_���k���ɤU�観�S���F��B���O���D���ɭ�
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
		if (Isfalling == true && IsJumping == false) {  //�P�_�O�_���U�����A
			if (!rising) {
				for (i = 0; i < animation.Width(); i++) {
					for (j = 0; j < velocity; j++) {
						if (!(m->isEmpty(x + i, y + animation.Height() + j))) {
							y = y + j - 2;
							velocity = initial_velocity;	// ���]�W�ɪ�l�t��
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
			IsJumping = true;		// ���D���A
		}
		if (isMovingJump && IsJumping == true && rising == false && IsJumpTwice == false) {
			IsJumpTwice = true;				// �G�q���Ұ�
			rising = true;					// ���]�W�ɪ��A
			velocity = initial_velocity;	// ���]�W�ɪ�l�t��
		}
		//
		if (IsJumping == true) {
			if (isMovingDown) {
				isMovingDown = false;
			}
			if (rising) {			// �W�ɪ��A
				if (velocity > 0) {
					for (i = 0; i < animation.Width(); i++) {  //�W�ɮɧP�_�W��O�_���I����F��
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
						y -= velocity;	// ��t�� > 0�ɡAy�b�W��(����velocity���I�Avelocity����쬰 �I/��)
						velocity--;		// �����O�v�T�A�U�����W�ɳt�׭��C
					}
				}
				else {
					rising = false; // ��t�� <= 0�A�W�ɲפ�A�U���אּ�U��
					velocity = 1;	// �U������t(velocity)��1
				}
			}
			else {				// �U�����A
				for (i = 0; i < animation.Width(); i++) {
					for (j = 0; j < velocity; j++) {
						//if (!(m->isEmpty(x + i, y + animation.Height() + j))) {  //�P�_�H���U��O���O����ê��
						//	y = y + j;
						//	rising = true;
						//	velocity = initial_velocity;	// ���]�W�ɪ�l�t��
						//	IsJumping = false;				// ���D���A����
						//	IsJumpTwice = false;
						//	break;
						//}
						if ((m->GetBlock(x + i, y + animation.Height() + j) != 0) && (m->GetBlock(x + i, y + animation.Height() + j) != 11) && (m->GetBlock(x + i, y + animation.Height() + j) != 12)) {
							y = y + j;
							rising = true;
							velocity = initial_velocity;	// ���]�W�ɪ�l�t��
							IsJumping = false;				// ���D���A����
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