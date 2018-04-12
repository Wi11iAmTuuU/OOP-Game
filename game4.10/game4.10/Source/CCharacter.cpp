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
		const int INITIAL_VELOCITY = 10;	// ��l�W�ɳt��
		//const int FLOOR = 1095;				// �a�O�y��
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
			for (i = 0; i < animation.Height(); i++) {  //�P�_�����䨫��Ӯ榳�S�������ê��
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
			if (j == animation.Width() && IsJumping == false) {   //�P�_�U��p�G�S�F��|���U�h
				while (falling == true) {
					velocity = 1;
					for (i = 0; i < animation.Width(); i++) {
						if (!(m->isEmpty(x + i, y + animation.Height() + velocity))) {
							y = y + velocity - 5;
							velocity = initial_velocity;	// ���]�W�ɪ�l�t��
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
			for (i = 0; i < animation.Height(); i++) {   //�P�_���k�䨫��Ӧ��S�������ê��
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
			
			if (j == animation.Width() && IsJumping == false) {   //�P�_�U��p�G�S�F��|���U�h
				while (falling == true) {
					velocity = 1;
					for (i = 0; i < animation.Width(); i++) {
						if (!(m->isEmpty(x + i, y + animation.Height() + velocity))) {
							y = y + velocity - 5;
							velocity = initial_velocity;	// ���]�W�ɪ�l�t��
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
						if (!(m->isEmpty(x + i, y - velocity))) {
							rising = false;
							velocity = 1;
							break;
						}
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
					if (!(m->isEmpty(x + i, y + animation.Height() + velocity))) {
						y = y + velocity - 5;
						rising = true;
						velocity = initial_velocity;	// ���]�W�ɪ�l�t��
						IsJumping = false;				// ���D���A����
						IsJumpTwice = false;
						break;
					}
				}
				if (i == animation.Width()) {

					y += velocity;
					velocity++;

				}
				//if (y < floor - 1) {  // ��y�y���٨S�I��a�O
				//	y += velocity;	// y�b�U��(����velocity���I�Avelocity����쬰 �I/��)
				//	velocity++;		// �����O�v�T�A�U�����U���t�׼W�[
				//}
				//else {
				//	y = floor - 1;  // ��y�y�ЧC��a�O�A�󥿬��a�O�W
				//	rising = true;	// �����ϼu�A�U���אּ�W��
				//	velocity = initial_velocity;	// ���]�W�ɪ�l�t��
				//	IsJumping = false;				// ���D���A����
				//	IsJumpTwice = false;			// �G�q������
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