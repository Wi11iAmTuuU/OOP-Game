#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CCharacter.h"
#include "CBlock.h"
#include "CDiamond.h"

namespace game_framework {
	CDiamond::CDiamond()
	{
		is_alive = true;
		x = y = 0;
		mapX = mapY = 0;
	}

	bool CDiamond::HitCharacter(CCharacter * character)
	{
		return HitRectangle(character->GetX1(), character->GetY1(),
			character->GetX2(), character->GetY2());
	}

	bool CDiamond::IsAlive()
	{
		return is_alive;
	}

	void CDiamond::LoadBitmap()
	{
		animation.AddBitmap("RES\\Diamond.bmp", RGB(255, 255, 255));			// ���J�y���ϧ�
	}

	void CDiamond::OnShow(Map *m)
	{
		if (is_alive) {
			animation.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
			animation.OnShow();
		}
	}

	void CDiamond::SetMapXY(int nx, int ny)
	{
		mapX = nx; 
		mapY = ny;
		x = (mapX * 48)+6;
		y = (mapY * 40)+2;
	}

	void CDiamond::SetIsAlive(bool alive)
	{
		is_alive = alive;
	}

	bool CDiamond::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x;						// �y�����W��x�y��
		int y1 = y;						// �y�����W��y�y��
		int x2 = x1 + animation.Width();	// �y���k�U��x�y��
		int y2 = y1 + animation.Height();	// �y���k�U��y�y��
											//
											// �˴��y���x�λP�ѼƯx�άO�_���涰
											//
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}

}