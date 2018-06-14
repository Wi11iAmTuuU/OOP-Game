#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CCharacter.h"

namespace game_framework
{
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
    IsDieing = false;
    IsReliving = false;
    dieCounter = 0;
	velocityLeft = velocityRight = 0;
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
    isMovingLeft = isMovingRight = isMovingJump = isMovingDown = isMovingUp = isMovingDie = false;
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
    animation_Die.AddBitmap("RES\\Character\\CharacterDie1.bmp", RGB(255, 255, 255));
    animation_Die.AddBitmap("RES\\Character\\CharacterDie2.bmp", RGB(255, 255, 255));
    animation_Die.AddBitmap("RES\\Character\\Character1.bmp", RGB(255, 255, 255));
    animation_Die.AddBitmap("RES\\Character\\CharacterDie1.bmp", RGB(255, 255, 255));
    animation_Die.AddBitmap("RES\\Character\\CharacterDie2.bmp", RGB(255, 255, 255));
    animation_Die.AddBitmap("RES\\Character\\Character1.bmp", RGB(255, 255, 255));
    animation_Die.AddBitmap("RES\\Character\\CharacterDie1.bmp", RGB(255, 255, 255));
    animation_Die.AddBitmap("RES\\Character\\CharacterDie2.bmp", RGB(255, 255, 255));
    animation_Die.AddBitmap("RES\\Character\\Character1.bmp", RGB(255, 255, 255));
    animation_Die.AddBitmap("RES\\Character\\CharacterDie3.bmp", RGB(255, 255, 255));
    animation_Die.AddBitmap("RES\\Character\\CharacterDie3.bmp", RGB(255, 255, 255));
    animation_Die.AddBitmap("RES\\Character\\CharacterDie3.bmp", RGB(255, 255, 255));
    //
    animation_relive.AddBitmap("RES\\Character\\CharacterDie3.bmp", RGB(255, 255, 255));
    animation_relive.AddBitmap("RES\\Character\\CharacterDie3.bmp", RGB(255, 255, 255));
    animation_relive.AddBitmap("RES\\Character\\CharacterDie3.bmp", RGB(255, 255, 255));
    animation_relive.AddBitmap("RES\\Character\\CharacterDie2.bmp", RGB(255, 255, 255));
    animation_relive.AddBitmap("RES\\Character\\CharacterDie1.bmp", RGB(255, 255, 255));
    animation_relive.AddBitmap("RES\\Character\\Character1.bmp", RGB(255, 255, 255));
}

void CCharacter::OnMove(Map* m, int* MapNumber, Counter* counter)
{
    const int STEP_SIZE = 5;
    int i, j;
    animation.OnMove();

    if (isMovingLeft && !isMovingDown)
    {
        for (i = 0; i < animation.Height(); i++)    //�P�_�����䨫��Ӯ榳�S�������ê��
        {
            if ((m->GetBlock(x - 5, y + i) != 0) && (m->GetBlock(x - 5, y + i) != 11) && (m->GetBlock(x - 5, y + i) != 12))
            {
                break;
            }
        }

        if (i == animation.Height())
        {
            if (((m->GetBlock(x, y + animation.Height() + 2) == 2)) || ((m->GetBlock(x + animation.Width(), y + animation.Height() + 2) == 2)))
            {
                x -= 2;
            }
            else if (((m->GetBlock(x, y + animation.Height() + 2) == 3)) || ((m->GetBlock(x + animation.Width(), y + animation.Height() + 2) == 3)))
            {
                x -= 8;
            }
            else if (((m->GetBlock(x, y + animation.Height() + 2) == 10)) || ((m->GetBlock(x + animation.Width(), y + animation.Height() + 2) == 10)))
            {
                if (m->GetBlock(x, y + animation.Height() + 2) == 10)
                {
                    m->SetCheckpoint(x, y + animation.Height() + 2);
                }

                if (m->GetBlock(x + animation.Width(), y + animation.Height() + 2) == 10)
                {
                    m->SetCheckpoint(x + animation.Width(), y + animation.Height() + 2);
                }

                x -= STEP_SIZE;
            }
            else
            {
                x -= STEP_SIZE;
            }
        }

        if (!IsJumping)
        {
            for (j = 0; j < animation.Width(); j++)    //�P�_�������ɤU�観�S���F��B���O���D���ɭ�
            {
                if ((m->GetBlock(x + j, y + animation.Height() + 1) != 0) && (m->GetBlock(x + j, y + animation.Height() + 1) != 11) && (m->GetBlock(x + j, y + animation.Height() + 1) != 12))
                {
                    Isfalling = false;
                    break;
                }
                else if (!Isfalling)
                {
                    Isfalling = true;
                    rising = false;
                    velocity = 1;
                }
            }
        }
    }

    if (isMovingRight && !isMovingDown)
    {
        for (i = 0; i < animation.Height(); i++)     //�P�_���k�䨫��Ӧ��S�������ê��
        {
            if ((m->GetBlock(x + animation.Width() + 5, y + i) != 0) && (m->GetBlock(x + animation.Width() + 5, y + i) != 11) && (m->GetBlock(x + animation.Width() + 5, y + i) != 12))
            {
                break;
            }
        }

        if (i == animation.Height())
        {
            if (((m->GetBlock(x, y + animation.Height() + 2) == 2)) || ((m->GetBlock(x + animation.Width(), y + animation.Height() + 2) == 2)))
            {
                x += 2;
            }
            else if (((m->GetBlock(x, y + animation.Height() + 2) == 3)) || ((m->GetBlock(x + animation.Width(), y + animation.Height() + 2) == 3)))
            {
                x += 8;
            }
            else if (((m->GetBlock(x, y + animation.Height() + 2) == 10)) || ((m->GetBlock(x + animation.Width(), y + animation.Height() + 2) == 10)))
            {
                if (m->GetBlock(x, y + animation.Height() + 2) == 10)
                {
                    m->SetCheckpoint(x, y + animation.Height() + 2);
                }

                if (m->GetBlock(x + animation.Width(), y + animation.Height() + 2) == 10)
                {
                    m->SetCheckpoint(x + animation.Width(), y + animation.Height() + 2);
                }

                x += STEP_SIZE;
            }
            else
            {
                x += STEP_SIZE;
            }
        }

        if (!IsJumping)
        {
            for (j = 0; j < animation.Width(); j++)    //�P�_���k���ɤU�観�S���F��B���O���D���ɭ�
            {
                if ((m->GetBlock(x + j, y + animation.Height() + 1) != 0) && (m->GetBlock(x + j, y + animation.Height() + 1) != 11) && (m->GetBlock(x + j, y + animation.Height() + 1) != 12))
                {
                    Isfalling = false;
                    break;
                }
                else if (!Isfalling)
                {
                    Isfalling = true;
                    rising = false;
                    velocity = 1;
                }
            }
        }
    }

    if (Isfalling == true && IsJumping == false)    //�P�_�O�_���U�����A
    {
        if (!rising)
        {
            for (i = 0; i < animation.Width(); i++)
            {
                for (j = 0; j < velocity; j++)
                {
                    if (!(m->isEmpty(x + i, y + animation.Height() + j)))
                    {
                        y = y + j - 2;
                        velocity = initial_velocity;	// ���]�W�ɪ�l�t��
                        Isfalling = false;
                        rising = true;
                        break;
                    }
                }

                if (j != velocity) break;
            }

            if (i == animation.Width())
            {
                y += velocity;
                velocity++;
            }
        }
    }

    if (isMovingDown)
    {
    }

    //
    if (isMovingJump && IsJumping == false && !isMovingDown)
    {
        IsJumping = true;		// ���D���A
    }

    if (isMovingJump && IsJumping == true && rising == false && IsJumpTwice == false)
    {
        IsJumpTwice = true;				// �G�q���Ұ�
        rising = true;					// ���]�W�ɪ��A
        velocity = initial_velocity;	// ���]�W�ɪ�l�t��
    }

    //
    if (IsJumping == true)
    {
        if (isMovingDown)
        {
            isMovingDown = false;
        }

        if (rising)  			// �W�ɪ��A
        {
            if (velocity > 0)
            {
                for (i = 0; i < animation.Width(); i++)    //�W�ɮɧP�_�W��O�_���I����F��
                {
                    for (j = 0; j < velocity; j++)
                    {
                        if ((m->GetBlock(x + i, y - j) != 0) && (m->GetBlock(x + i, y - j) != 11) && (m->GetBlock(x + i, y - j) != 12))
                        {
                            rising = false;
                            velocity = 1;
                            break;
                        }
                    }

                    if (j != velocity)  break;
                }

                if (i == animation.Width())
                {
                    y -= velocity;	// ��t�� > 0�ɡAy�b�W��(����velocity���I�Avelocity����쬰 �I/��)
                    velocity--;		// �����O�v�T�A�U�����W�ɳt�׭��C
                }
            }
            else
            {
                rising = false; // ��t�� <= 0�A�W�ɲפ�A�U���אּ�U��
                velocity = 1;	// �U������t(velocity)��1
            }
        }
        else  				// �U�����A
        {
            for (i = 0; i < animation.Width(); i++)
            {
                for (j = 0; j < velocity; j++)
                {
                    if ((m->GetBlock(x + i, y + animation.Height() + j) != 0) && (m->GetBlock(x + i, y + animation.Height() + j) != 11) && (m->GetBlock(x + i, y + animation.Height() + j) != 12))
                    {
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

            if (i == animation.Width())
            {
                y += velocity;
                velocity++;
            }
        }
    }

    if (isMovingDie)  									//���`�F��
    {
        IsDieing = true;
    }

    if (IsDieing)
    {
        if (dieCounter < 12)
        {
            dieCounter++;
        }
        else
        {
            dieCounter = 0;
            IsReliving = true;
            IsDieing = false;
            x = m->GetCheckpointX() * 48 + 3;
            y = (m->GetCheckpointY() - 1) * 40 + 5;
        }
    }

    if (IsReliving)
    {
        if (dieCounter  < 5)
        {
            dieCounter++;
        }
        else
        {
            dieCounter = 0;
            IsReliving = false;
        }
    }
	//
	if (IsJumpingRight == true) {
		if (velocityRight > 0) {
			for (i = 0; i < animation.Height(); i++) {  //�V�k�ɧP�_�k��O�_���I����F��
				for (j = 0; j < velocityRight; j++) {
					if ((m->GetBlock(x + animation.Width() + j, y + i) != 0) && (m->GetBlock(x + animation.Width() + j, y + i) != 11) && (m->GetBlock(x + animation.Width() + j, y + i) != 12)) {
						break;
					}
				}
				if (j != velocityRight)  break;
			}
			if (i == animation.Height()) {
				x += velocityRight;	// ��t�� > 0�ɡAy�b�W��(����velocity���I�Avelocity����쬰 �I/��)
				velocityRight--;		// �����O�v�T�A�U�����W�ɳt�׭��C
			}
			if ((m->GetBlock(x, y + animation.Height() + 1) != 0) && (m->GetBlock(x, y + animation.Height() + 1) != 11) && (m->GetBlock(x, y + animation.Height() + 1) != 12)) {
				Isfalling = false;
			}
			else {
				Isfalling = true;
			}
			if (Isfalling) {
				for (i = 0; i < animation.Width(); i++)
				{
					for (j = 0; j < velocity; j++)
					{
						if (!(m->isEmpty(x + i, y + animation.Height() + j)))
						{
							y = y + j - 2;
							velocity = initial_velocity;	// ���]�W�ɪ�l�t��
							Isfalling = false;
							rising = true;
							break;
						}
					}

					if (j != velocity) break;
				}

				if (i == animation.Width())
				{
					y += velocity;
					velocity++;
				}
			}
		}
		else {
			IsJumpingRight = false;
			velocity = initial_velocity;	// ���]�W�ɪ�l�t��
		}
	}

	if (IsJumpingLeft == true) {
		if (velocityLeft > 0) {
			for (i = 0; i < animation.Height(); i++) {  //�W�ɮɧP�_�k��O�_���I����F��
				for (j = 0; j < velocityLeft; j++) {
					if ((m->GetBlock(x - j, y + i) != 0)&& (m->GetBlock(x - j, y + i) != 12)) {
						break;
					}
				}
				if (j != velocityLeft)  break;
			}
			if (i == animation.Height()) {
				x -= velocityLeft;	// ��t�� > 0�ɡAy�b�W��(����velocity���I�Avelocity����쬰 �I/��)
				velocityLeft--;		// �����O�v�T�A�U�����W�ɳt�׭��C
			}
			if ((m->GetBlock(x, y + animation.Height() + 1) != 0) && (m->GetBlock(x, y + animation.Height() + 1) != 11) && (m->GetBlock(x, y + animation.Height() + 1) != 12)) {
				Isfalling = false;
			}
			else {
				Isfalling = true;
			}
			if (Isfalling) {
				for (i = 0; i < animation.Width(); i++)
				{
					for (j = 0; j < velocity; j++)
					{
						if (!(m->isEmpty(x + i, y + animation.Height() + j)))
						{
							y = y + j - 2;
							velocity = initial_velocity;	// ���]�W�ɪ�l�t��
							Isfalling = false;
							break;
						}
					}

					if (j != velocity) break;
				}

				if (i == animation.Width())
				{
					y += velocity;
					velocity++;
				}
			}
		}
		else {
			IsJumpingLeft = false;
		}
	}

    //
    if (isMovingUp)
    {
        if (m->GetBlock(x, y) == 11)
        {
            *MapNumber = 1;
            counter->ResetDiamondCount();
            x = 960;
            y = 1125;
        }
        else if (m->GetBlock(x, y) == 12 && (counter->GetDiamondCount() == 5))
        {
            *MapNumber = 0;
            counter->ResetDiamondCount();
            x = 960;
            y = 1125;
        }
    }

    //
	if (((m->GetBlock(x, y + animation.Height() + 2) == 4)) || ((m->GetBlock(x + animation.Width(), y + animation.Height() + 2) == 4))) {  //�V�k�۰ʤ��
		for (i = 0; i < animation.Height(); i++) {  //�P�_�k��O���O�Ū�
			if ((m->GetBlock(x + animation.Width() + 3, y + i) != 0) && (m->GetBlock(x + animation.Width() + 3, y + i) != 11) && (m->GetBlock(x + animation.Width() + 3, y + i) != 12)) {
				break;
			}
		}
		if (i == animation.Height()) {
			x += 3;
			if (!IsJumping) {
				for (j = 0; j < animation.Width(); j++) {  //�P�_���k���ɤU�観�S���F��B���O���D���ɭ�
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
	}
	if (((m->GetBlock(x, y + animation.Height() + 2) == 5)) || ((m->GetBlock(x + animation.Width(), y + animation.Height() + 2) == 5))) { //�V���۰ʤ��
		for (i = 0; i < animation.Height(); i++) {  //�P�_����O���O�Ū�
			if ((m->GetBlock(x - 3, y + i) != 0) && (m->GetBlock(x - 3, y + i) != 11) && (m->GetBlock(x - 3, y + i) != 12)) {
				break;
			}
		}
		if (i == animation.Height()) {
			x -= 3;
			if (!IsJumping) {
				for (j = 0; j < animation.Width(); j++) {  //�P�_�������ɤU�観�S���F��B���O���D���ɭ�
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
	}
	if (((m->GetBlock(x, y + animation.Height() + 2) == 9)) || ((m->GetBlock(x + animation.Width(), y + animation.Height() + 2) == 9))) { //�����
		IsDieing = true;
	}
	if (((m->GetBlock(x, y + animation.Height() + 2) == 10)) || ((m->GetBlock(x + animation.Width(), y + animation.Height() + 2) == 10))) { //CheckPoint���
		if (m->GetBlock(x, y + animation.Height() + 2) == 10) {
			m->SetCheckpoint(x, y + animation.Height() + 2);
		}
		if (m->GetBlock(x + animation.Width(), y + animation.Height() + 2) == 10) {
			m->SetCheckpoint(x + animation.Width(), y + animation.Height() + 2);
		}
	}
	if (((m->GetBlock(x, y + animation.Height() + 2) == 6)) || ((m->GetBlock(x + animation.Width(), y + animation.Height() + 2) == 6))) { //���D���  (�H���U��)
		IsJumping = true;
		velocity = 20;
	}
	else if (((m->GetBlock(x, y - 2) == 6)) || ((m->GetBlock(x + animation.Width(), y - 2) == 6))) { //���D���  (�H���W��)
		Isfalling = true;
		velocity = 20;
	}
	else if (((m->GetBlock(x - 5, y) == 6)) || ((m->GetBlock(x - 5, y + animation.Height()) == 6))) { //���D���  (�H������)
		IsJumpingRight = true;
		velocityRight = 20;
	}
	else if (((m->GetBlock(x + animation.Width() + 5, y) == 6)) || ((m->GetBlock(x + animation.Width() + 5, y + animation.Height()) == 6))) { //���D���  (�H���k��)
		IsJumpingLeft = true;
		velocityLeft = 20;
	}
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

void CCharacter::SetMovingDie(bool flag)
{
    isMovingDie = flag;
}

void CCharacter::SetMovingUp(bool flag)
{
    isMovingUp = flag;
}

void CCharacter::SetXY(int nx, int ny)
{
    x = nx;
    y = ny;
}

int CCharacter::GetMapNumber()
{
    return MapNumber;
}
void CCharacter::ChangeMapNumber(int index)
{
    MapNumber = index;
}

void CCharacter::OnShow(Map* m)
{
    if (isMovingDown && !IsJumping)
    {
        animation_Underarm.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
        animation_Underarm.OnShow();
    }
    else if (isMovingLeft)
    {
        animation_Left.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
        animation_Left.OnShow();
        animation_Left.OnMove();
    }
    else if (isMovingRight)
    {
        animation_right.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
        animation_right.OnShow();
        animation_right.OnMove();
    }
    else if (IsDieing)
    {
        animation_Die.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
        animation_Die.OnShow();
        animation_Die.OnMove();
    }
    else if (IsReliving)
    {
        animation_relive.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
        animation_relive.OnShow();
        animation_relive.OnMove();
    }
    else
    {
        animation.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
        animation.OnShow();
    }
}
}