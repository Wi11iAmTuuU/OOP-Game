#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CCharacter.h"
#include "Map.h"
#include "fstream"
namespace game_framework
{
	Map::Map()
	{
		IsPass = false;
	}
	int Map::GetWidth() //取得背景寬度
{
    return background.Width();
}
int Map::GetHeight() //取得背景長度
{
    return background.Height();
}
int Map::ScreenX(int x) //回傳人物在螢幕上座標
{
    return x - sx;
}
int Map::ScreenY(int y) //回傳人物在螢幕上座標
{
    return y - sy;
}
int Map::GetBlock(int x, int y)
{
    int gx = x / 48; // 轉換為X軸格座標(整數除法)
    int gy = y / 40; // 轉換為Y軸格座標(整數除法)
    //map[x][y]中的y表示X軸的格數，x表示Y軸
    return Map1[gy][gx]; // 回傳方塊
}

void Map::StorePortal()
{
	int index = 50;
	int i, j, k;
	int check = 0;
	for (i = 0; i < 20; i++) {
		for (j = 0; j < 30; j++) {
			for (k = 0; k < 40; k++) {
				if (Map1[j][k] == index) {
					Portal[i][0] = j + 1;
					Portal[i][1] = k + 1;
					check = 1;
					break;
				}
			}
			if (check == 1) {
				index++;
				break;
			}
		}
		check = 0;
	}
}
void Map::ReadMap(int MapNumber)
{
    if (MapNumber == 0)
    {
        ifstream fin("RES\\MAP\\Map1.txt");

        for (int i = 0; i < 30; i++)
        {
            for (int k = 0; k < 40; k++)
            {
                fin >> Map1[i][k];
            }
        }
        fin.close();
		StorePortal();
    }
    else if (MapNumber == 1)
    {
        ifstream fin("RES\\MAP\\Map2.txt");

        for (int i = 0; i < 30; i++)
        {
            for (int k = 0; k < 40; k++)
            {
                fin >> Map1[i][k];
            }
        }
        fin.close();
		StorePortal();
    }
	else if (MapNumber == 2)
	{
		ifstream fin("RES\\MAP\\Map3.txt");

		for (int i = 0; i < 30; i++)
		{
			for (int k = 0; k < 40; k++)
			{
				fin >> Map1[i][k];
			}
		}
		fin.close();
		StorePortal();
	}
	else if (MapNumber == 3)
	{
		ifstream fin("RES\\MAP\\Map4.txt");

		for (int i = 0; i < 30; i++)
		{
			for (int k = 0; k < 40; k++)
			{
				fin >> Map1[i][k];
			}
		}
		fin.close();
		StorePortal();
	}
}
void Map::Initialize() //初始化
{
    //const int X_POS = 0;
    //const int Y_POS = 0;
    //sx = X_POS;
    //sy = Y_POS;
}
void Map::LoadBitmap() //載入圖片
{
	background.LoadBitmap(IDB_BACKGROUND);
	Normalblock.LoadBitmap("RES\\Block\\normalblock.bmp", RGB(255, 255, 255));
	LoseSpeedBlock.LoadBitmap("RES\\Block\\LosespeedBlock.bmp", RGB(255, 255, 255));
	SpeedBlock.LoadBitmap("RES\\Block\\SpeedBlock.bmp", RGB(255, 255, 255));
	AutoSpeedBlockRight.LoadBitmap("RES\\Block\\AutoSpeedBlockRight.bmp", RGB(255, 255, 255));
	AutoSpeedBlockLeft.LoadBitmap("RES\\Block\\AutoSpeedBlockLeft.bmp", RGB(255, 255, 255));
	LightCheckpointBlock.LoadBitmap("RES\\Block\\LightCheckpointBlock.bmp", RGB(255, 255, 255));
	CheckpointBlock.LoadBitmap("RES\\Block\\CheckpointBlock.bmp", RGB(255, 255, 255));
	door.LoadBitmap("RES\\Block\\door.bmp", RGB(255, 255, 255));
	WaterBlock.LoadBitmap("RES\\Block\\waterblock.bmp", RGB(255, 255, 255));
	JumpBlock.LoadBitmap("RES\\Block\\Jumpblock.bmp", RGB(255, 255, 255));
	PortalBlock.LoadBitmap("RES\\Block\\Portalblock.bmp", RGB(255, 255, 255));
}

void Map::OnMove(int x, int y)
{
    sx = x - SIZE_X / 2;   //讓人物保持在地圖中間
    sy = y - SIZE_Y / 2;

    if (x <= SIZE_X / 2)      //設定當人物接近邊界時地圖移動停止
    {
        sx = 0;
    }

    if (x >= background.Width() - SIZE_X / 2)
    {
        sx = background.Width() - SIZE_X;
    }

    if (y <= SIZE_Y / 2)
    {
        sy = 0;
    }

    if (y >= background.Height() - SIZE_Y / 2)
    {
        sy = background.Height() - SIZE_Y;
    }
}
void Map::OnShow(int MapNumber)
{
	background.SetTopLeft(-sx, -sy);
	background.ShowBitmap();
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 40; j++) {
			int x = j * 48 - sx; // 算出第(i, j)這一格的 x 螢幕座標 
			int y = i * 40 - sy; // 算出第(i, j)這一格的 y 螢幕座標 
			switch (Map1[i][j]) {
				case 1:
					Normalblock.SetTopLeft(x, y); // 指定第(i, j)這一格的座標 
					Normalblock.ShowBitmap();
					break;
				case 2:
					LoseSpeedBlock.SetTopLeft(x, y); // 指定第(i, j)這一格的座標 
					LoseSpeedBlock.ShowBitmap();
					break;
				case 3:
					SpeedBlock.SetTopLeft(x, y); // 指定第(i, j)這一格的座標 
					SpeedBlock.ShowBitmap();
					break;
				case 4:
					AutoSpeedBlockRight.SetTopLeft(x, y); // 指定第(i, j)這一格的座標 
					AutoSpeedBlockRight.ShowBitmap();
					break;
				case 5:
					AutoSpeedBlockLeft.SetTopLeft(x, y); // 指定第(i, j)這一格的座標 
					AutoSpeedBlockLeft.ShowBitmap();
					break;
				case 6:
					JumpBlock.SetTopLeft(x, y); // 指定第(i, j)這一格的座標 
					JumpBlock.ShowBitmap();
					break;
				case 9:
					WaterBlock.SetTopLeft(x, y); // 指定第(i, j)這一格的座標 
					WaterBlock.ShowBitmap();
					break;
				case 20:
					door.SetTopLeft(x, y); // 指定第(i, j)這一格的座標 
					door.ShowBitmap();
					break;
				case 21:
					door.SetTopLeft(x, y); // 指定第(i, j)這一格的座標 
					door.ShowBitmap();
					break;
				case 22:
					door.SetTopLeft(x, y); // 指定第(i, j)這一格的座標 
					door.ShowBitmap();
					break;
				case 23:
					door.SetTopLeft(x, y); // 指定第(i, j)這一格的座標 
					door.ShowBitmap();
					break;
				case 50:
					PortalBlock.SetTopLeft(x, y); // 指定第(i, j)這一格的座標 
					PortalBlock.ShowBitmap();
					break;
				case 51:
					PortalBlock.SetTopLeft(x, y); // 指定第(i, j)這一格的座標 
					PortalBlock.ShowBitmap();
					break;
				case 52:
					PortalBlock.SetTopLeft(x, y); // 指定第(i, j)這一格的座標 
					PortalBlock.ShowBitmap();
					break;
				case 53:
					PortalBlock.SetTopLeft(x, y); // 指定第(i, j)這一格的座標 
					PortalBlock.ShowBitmap();
					break;
				case 54:
					PortalBlock.SetTopLeft(x, y); // 指定第(i, j)這一格的座標 
					PortalBlock.ShowBitmap();
					break;
				case 55:
					PortalBlock.SetTopLeft(x, y); // 指定第(i, j)這一格的座標 
					PortalBlock.ShowBitmap();
					break;
				case 56:
					PortalBlock.SetTopLeft(x, y); // 指定第(i, j)這一格的座標 
					PortalBlock.ShowBitmap();
					break;
				case 57:
					PortalBlock.SetTopLeft(x, y); // 指定第(i, j)這一格的座標 
					PortalBlock.ShowBitmap();
					break;
				case 58:
					PortalBlock.SetTopLeft(x, y); // 指定第(i, j)這一格的座標 
					PortalBlock.ShowBitmap();
					break;
				case 59:
					PortalBlock.SetTopLeft(x, y); // 指定第(i, j)這一格的座標 
					PortalBlock.ShowBitmap();
					break;
				case 60:
					PortalBlock.SetTopLeft(x, y); // 指定第(i, j)這一格的座標 
					PortalBlock.ShowBitmap();
					break;
				case 61:
					PortalBlock.SetTopLeft(x, y); // 指定第(i, j)這一格的座標 
					PortalBlock.ShowBitmap();
					break;
				case 62:
					PortalBlock.SetTopLeft(x, y); // 指定第(i, j)這一格的座標 
					PortalBlock.ShowBitmap();
					break;
				case 63:
					PortalBlock.SetTopLeft(x, y); // 指定第(i, j)這一格的座標 
					PortalBlock.ShowBitmap();
					break;
				case 64:
					PortalBlock.SetTopLeft(x, y); // 指定第(i, j)這一格的座標 
					PortalBlock.ShowBitmap();
					break;
				case 65:
					PortalBlock.SetTopLeft(x, y); // 指定第(i, j)這一格的座標 
					PortalBlock.ShowBitmap();
					break;
				case 10:
					if (i == CheckpointY && j == CheckpointX) {
						LightCheckpointBlock.SetTopLeft(x, y);
						LightCheckpointBlock.ShowBitmap();
					}
					else
					{
						CheckpointBlock.SetTopLeft(x, y);
						CheckpointBlock.ShowBitmap();
					}
					break;
			}
		}
	}
}
void Map::SetXY(int nx, int ny)   // 設定螢幕畫面左上角的座標
{
    sx = nx;
    sy = ny;
}
void Map::SetCheckpoint(int X, int Y)
{
    CheckpointX = X / 48; // 轉換為X軸格座標(整數除法)
    CheckpointY = Y / 40; // 轉換為Y軸格座標(整數除法)
}
void Map::SetIsPass(bool pass)
{
	IsPass = pass;
}
bool Map::isEmpty(int x, int y)
{
    int gx = x / 48; // 轉換為X軸格座標(整數除法)
    int gy = y / 40; // 轉換為Y軸格座標(整數除法)
    //map[x][y]中的y表示X軸的格數，x表示Y軸
    return Map1[gy][gx] == 0; // 假設 0 代表空的
}
int Map::Getsx()
{
    return sx;
}
int Map::Getsy()
{
    return sy;
}
int Map::GetCheckpointX()
{
    return CheckpointX;
}
int Map::GetCheckpointY()
{
    return CheckpointY;
}
int Map::GetPortalX(int index)
{
	if (index < 60) {
		index = index % 10;
		return Portal[index][1] - 1;
	}
	else {
		index = index % 10 + 10;
		return Portal[index][1] - 1;
	}
}
int Map::GetPortalY(int index)
{
	if (index < 60) {
		index = index % 10;
		return Portal[index][0] - 1;
	}
	else {
		index = index % 10 + 10;
		return Portal[index][0] - 1;
	}
}
bool Map::GetIsPass()
{
	return IsPass;
}
//int Map::GetMapNumber()
//{
//	return MapNumber;
//}
//void Map::ChangeMapNumber(int index)
//{
//	MapNumber = index;
//}
}