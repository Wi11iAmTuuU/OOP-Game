#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CCharacter.h"
#include "Map.h"
#include "fstream"
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
	void Map::ReadMap()
	{
		ifstream fin("RES\\MAP\\Map2.txt");
		for (int i = 0; i < 30; i++) {
			for (int k = 0; k < 40; k++) {
				fin >> Map1[i][k];
			}
		}
		fin.close();
	}
	void Map::Initialize() //��l��
	{
		ReadMap();
		//const int X_POS = 0;
		//const int Y_POS = 0;
		//sx = X_POS;
		//sy = Y_POS;
	}
	void Map::LoadBitmap() //���J�Ϥ�
	{
		background.LoadBitmap(IDB_BACKGROUND);
		block.LoadBitmap(IDB_normalblock1, RGB(255, 255, 255));
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
		for (int i = 0; i < 30; i++) {
			for (int j = 0; j < 40; j++) {
				int x = j * 48 - sx; // ��X��(i, j)�o�@�檺 x �ù��y�� 
				int y = i * 40 - sy; // ��X��(i, j)�o�@�檺 y �ù��y�� 
				switch (Map1[i][j]) {
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
		int gx = x / 48; // �ഫ��X�b��y��(��ư��k) 
		int gy = y / 40; // �ഫ��Y�b��y��(��ư��k) 
						 //map[x][y]����y���X�b����ơAx���Y�b 
		return Map1[gy][gx] == 0; // ���] 0 �N��Ū� 
	}
}
