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
	void Map::ReadMap(int MapNumber)
	{	
		if (MapNumber == 0) {
			ifstream fin("RES\\MAP\\Map1.txt");
			for (int i = 0; i < 30; i++) {
				for (int k = 0; k < 40; k++) {
					fin >> Map1[i][k];
				}
			}
			fin.close();
		}
		else if (MapNumber == 1) {
			ifstream fin("RES\\MAP\\Map2.txt");
			for (int i = 0; i < 30; i++) {
				for (int k = 0; k < 40; k++) {
					fin >> Map1[i][k];
				}
			}
			fin.close();
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
		Normalblock.LoadBitmap("RES\\normalblock.bmp", RGB(255, 255, 255));
		LoseSpeedBlock.LoadBitmap("RES\\LosespeedBlock.bmp", RGB(255, 255, 255));
		SpeedBlock.LoadBitmap("RES\\SpeedBlock.bmp", RGB(255, 255, 255));
		door.LoadBitmap("RES\\door.bmp", RGB(255, 255, 255));
	}

	void Map::OnMove(int x, int y)
	{
		sx = x - SIZE_X / 2;   //讓人物保持在地圖中間 
		sy = y - SIZE_Y / 2;

		if (x <= SIZE_X / 2) {    //設定當人物接近邊界時地圖移動停止 
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
	void Map::OnShow(int MapNumber)
	{
		background.SetTopLeft(-sx, -sy);
		background.ShowBitmap();
		for (int i = 0; i < 30; i++) {
			for (int j = 0; j < 40; j++) {
				int x = j * 48 - sx; // 算出第(i, j)這一格的 x 螢幕座標 
				int y = i * 40 - sy; // 算出第(i, j)這一格的 y 螢幕座標 
				if (MapNumber == 0) {
					switch (Map1[i][j]) {
					case 1:
						Normalblock.SetTopLeft(x, y); // 指定第(i, j)這一格的座標 
						Normalblock.ShowBitmap();
						break;
					case 11:
						door.SetTopLeft(x, y); // 指定第(i, j)這一格的座標 
						door.ShowBitmap();
						break;
					}
				}
				if (MapNumber == 1) {
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
					case 12:
						door.SetTopLeft(x, y); // 指定第(i, j)這一格的座標 
						door.ShowBitmap();
						break;
					}
				}
			}
		}
	}
	void Map::SetXY(int nx, int ny)   // 設定螢幕畫面左上角的座標 
	{
		sx = nx;
		sy = ny;
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
}