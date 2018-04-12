#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CCharacter.h"
#include "Map.h"

namespace game_framework {
	

	int Map::GetWidth() //���o�I���e�� 
	{
		return background.Width();
	}
	int Map::GetHeight() //���o�I������
	{
		return background.Height();
	}
	int Map::ScreenX(int x) //�^�ǤH���b�ù��W�y��  
	{
		return x - sx;
	}
	int Map::ScreenY(int y) //�^�ǤH���b�ù��W�y��  
	{
		return y - sy;
	}
	void Map::Initialize() //��l��
	{
		//const int X_POS = 0;
		//const int Y_POS = 0;
		//sx = X_POS;
		//sy = Y_POS;
	}
	void Map::LoadBitmap() //���J�Ϥ�
	{
		background.LoadBitmap(IDB_BACKGROUND);
		block.LoadBitmap(IDB_Brown);
	}
	void Map::OnMove(int x, int y) 
	{
		sx = x - SIZE_X / 2;   //���H���O���b�a�Ϥ��� 
		sy = y - SIZE_Y / 2;

		if (x <= SIZE_X / 2) {    //�]�w��H��������ɮɦa�ϲ��ʰ��� 
			sx = 0;
		}

		if (x >= background.Width() - SIZE_X / 2) {
			sx = background.Width() - SIZE_X;
		}

		if (y <= SIZE_Y / 2) {
			sy = 0;
		}

		if (y >= background.Height() - SIZE_Y / 2) {
			sy = background.Height() - SIZE_Y;
		}
	}
	void Map::OnShow()
	{
		background.SetTopLeft(-sx, -sy);
		background.ShowBitmap();
		for (int i = 0; i < 120; i++) {
			for (int j = 0; j < 160; j++) {
				int x = j * 12 - sx; // ��X��(i, j)�o�@�檺 x �ù��y�� 
				int y = i * 10 - sy; // ��X��(i, j)�o�@�檺 y �ù��y�� 
				switch (map[i][j]) {
				case 1:
					block.SetTopLeft(x, y); // ���w��(i, j)�o�@�檺�y�� 
					block.ShowBitmap();
					break;
				}
			}
		}
	}
	void Map::SetXY(int nx, int ny)   // �]�w�ù��e�����W�����y�� 
	{
		sx = nx;
		sy = ny;
	}
	bool Map::isEmpty(int x, int y)
	{
		int gx = x / 12; // �ഫ��X�b��y��(��ư��k) 
		int gy = y / 10; // �ഫ��Y�b��y��(��ư��k) 
						 //map[x][y]����y���X�b����ơAx���Y�b 
		return map[gy][gx] == 0; // ���] 0 �N��Ū� 
	}
}
