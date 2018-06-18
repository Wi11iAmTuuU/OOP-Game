/*
* mygame.cpp: 本檔案儲遊戲本身的class的implementation
* Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
*
* This file is part of game, a free game development framework for windows.
*
* game is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* game is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
* History:
*   2002-03-04 V3.1
*          Add codes to demostrate the use of CMovingBitmap::ShowBitmap(CMovingBitmap &).
*	 2004-03-02 V4.0
*      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
*         demonstrate the use of states.
*      2. Demo the use of CInteger in CGameStateRun.
*   2005-09-13
*      Rewrite the codes for CBall and Ccharacter.
*   2005-09-20 V4.2Beta1.
*   2005-09-29 V4.2Beta2.
*      1. Add codes to display IDC_GAMECURSOR in GameStateRun.
*   2006-02-08 V4.2
*      1. Revise sample screens to display in English only.
*      2. Add code in CGameStateInit to demo the use of PostQuitMessage().
*      3. Rename OnInitialUpdate() -> OnInit().
*      4. Fix the bug that OnBeginState() of GameStateInit is not called.
*      5. Replace AUDIO_CANYON as AUDIO_NTUT.
*      6. Add help bitmap to CGameStateRun.
*   2006-09-09 V4.3
*      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
*         event driven.
*   2006-12-30
*      1. Bug fix: fix a memory leak problem by replacing PostQuitMessage(0) as
*         PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0).
*   2008-02-15 V4.4
*      1. Add namespace game_framework.
*      2. Replace the demonstration of animation as a new bouncing ball.
*      3. Use ShowInitProgress(percent) to display loading progress.
*   2010-03-23 V4.6
*      1. Demo MP3 support: use lake.mp3 to replace lake.wav.
*/

#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"

namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	/////////////////////////////////////////////////////////////////////////////

	CGameStateInit::CGameStateInit(CGame* g)
		: CGameState(g)
	{
	}

	void CGameStateInit::OnInit()
	{
		//
		// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
		//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
		//
		ShowInitProgress(0);	// 一開始的loading進度為0%
								//
								// 開始載入資料
								//
		Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
								//
								// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
								//
		Menu.LoadBitmap();
		CAudio::Instance()->Load(AUDIO_MENU, "RES\\Menu\\Menu_BGM.mp3");	// 載入編號1的聲音
		CAudio::Instance()->Load(AUDIO_DOOR, "RES\\SE\\DoorBlock.mp3");
		CAudio::Instance()->Load(AUDIO_JUMP, "RES\\SE\\JumpBlock.mp3");
		CAudio::Instance()->Load(AUDIO_PORTAL, "RES\\SE\\TPBlock.mp3");
		CAudio::Instance()->Load(AUDIO_WATER, "RES\\SE\\WaterBlock.mp3");
		CAudio::Instance()->Load(AUDIO_UNPASS, "RES\\SE\\UNpass.mp3");
		CAudio::Instance()->Load(AUDIO_DIAMOND, "RES\\SE\\Diamond.mp3");
		CAudio::Instance()->Play(AUDIO_MENU, true);
	}

	void CGameStateInit::OnBeginState()
	{

	}

	void CGameStateInit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_ESC = 27;
		const char KEY_ENTER = 13;
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_SPACE = 0x20; // keyboard空白鍵
		const char KEY_RIGHT = 0x27; // keyboard右箭頭

		if (nChar == KEY_LEFT) {
			Menu.clickLeft();
		}
		else if (nChar == KEY_RIGHT) {
			Menu.clickRight();
		}
		else if (nChar == KEY_SPACE || nChar == KEY_ENTER)
			if (Menu.clickEnter()) {
				GotoGameState(GAME_STATE_RUN);						// 切換至GAME_STATE_RUN
			}
			else
			{
			}
		else if (nChar == KEY_ESC) {								// Demo 關閉遊戲的方法
			PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// 關閉遊戲
		}
		else {}
	}

	void CGameStateInit::OnShow()
	{
		Menu.OnShow();
	}

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	/////////////////////////////////////////////////////////////////////////////

	CGameStateOver::CGameStateOver(CGame* g)
		: CGameState(g)
	{
	}

	void CGameStateOver::OnMove()
	{
		counter--;

		if (counter < 0)
			GotoGameState(GAME_STATE_INIT);
	}

	void CGameStateOver::OnBeginState()
	{
		counter = 30 * 5; // 5 seconds
	}

	void CGameStateOver::OnInit()
	{
		//
		// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
		//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
		//
		ShowInitProgress(66);	// 接個前一個狀態的進度，此處進度視為66%
								//
								// 開始載入資料
								//
		Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
								//
								// 最終進度為100%
								//
		ShowInitProgress(100);
		//
		BigShow.Initialize();
		BigShow.LoadBitmap();
	}

	void CGameStateOver::OnShow()
	{
		BigShow.OnShow();
	}

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	/////////////////////////////////////////////////////////////////////////////

	CGameStateRun::CGameStateRun(CGame* g)
		: CGameState(g), MapNumber(0)
	{
		gamemap[0].SetCheckpoint(960, 1160);
		gamemap[1].SetCheckpoint(960, 1160);
		gamemap[2].SetCheckpoint(880, 1160);
	}

	CGameStateRun::~CGameStateRun()
	{
	}

	void CGameStateRun::OnBeginState()
	{
		const int BACKGROUND_X = 0;
		//
		diamond[1][0].SetMapXY(37, 21);
		diamond[1][0].SetIsAlive(true);
		diamond[1][1].SetMapXY(18, 19);
		diamond[1][1].SetIsAlive(true);
		diamond[1][2].SetMapXY(16, 17);
		diamond[1][2].SetIsAlive(true);
		diamond[1][3].SetMapXY(4, 27);
		diamond[1][3].SetIsAlive(true);
		diamond[1][4].SetMapXY(16, 28);
		diamond[1][4].SetIsAlive(true);
		//
		diamond[2][0].SetMapXY(33, 26);
		diamond[2][0].SetIsAlive(true);
		diamond[2][1].SetMapXY(38, 10);
		diamond[2][1].SetIsAlive(true);
		diamond[2][2].SetMapXY(9, 27);
		diamond[2][2].SetIsAlive(true);
		diamond[2][3].SetMapXY(7, 7);
		diamond[2][3].SetIsAlive(true);
		diamond[2][4].SetMapXY(36, 3);
		diamond[2][4].SetIsAlive(true);
		//
		character.Initialize();
		background.SetTopLeft(BACKGROUND_X, 0);				// 設定背景的起始座標
		help.SetTopLeft(0, SIZE_Y - help.Height());			// 設定說明圖的起始座標
		GameMap = &gamemap[MapNumber];
		GameMap->ReadMap(MapNumber);                               // 設定起始座標
		escmenu.Initialize();
		pass = false;
		// 音樂 //
		//CAudio::Instance()->Play(AUDIO_LAKE, true);			// 撥放 WAVE
	}

	void CGameStateRun::OnMove()							// 移動遊戲元素
	{
		const int NUMDIAMOND = 5;	// 鑽石的總數
									//
									// 如果希望修改cursor的樣式，則將下面程式的commment取消即可
									//
									// SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));
									//
									//
									// 移動主角
									//
		character.OnMove(&gamemap[MapNumber], &MapNumber, &counter, &escmenu);

		//
		if (MapNumber != 0) {
			for (int i = 0; i < NUMDIAMOND; i++)
				if (diamond[MapNumber][i].IsAlive() && diamond[MapNumber][i].HitCharacter(&character))
				{
					diamond[MapNumber][i].SetIsAlive(false);
					counter.Add(1);
				}
		}

		//
		if (MapNumber != 1)
		{
			for (int i = 0; i < NUMDIAMOND; i++)
				diamond[1][i].SetIsAlive(true);

			gamemap[1].SetCheckpoint(960, 1160);
		}
		if (MapNumber != 2)
		{
			for (int i = 0; i < NUMDIAMOND; i++)
				diamond[2][i].SetIsAlive(true);

			gamemap[2].SetCheckpoint(880, 1160);
		}
		if (MapNumber == 0 && !pass) {
			int passcount = 0;
			for (int i = 1; i < 5; i++) {
				if (gamemap[i].GetIsPass()) {
					passcount ++;
				}
			}
			if (passcount == 2) {
				pass = true;
				GotoGameState(GAME_STATE_OVER);
			}
		}
		GameMap->OnMove(character.GetX1(), character.GetY1());
	}

	void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
	{
		const int NUMDIAMOND = 5;	// 鑽石的總數
		const int NUMMAP = 5;		// 地圖數量
									//
									// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
									//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
									//
		ShowInitProgress(33);	// 接個前一個狀態的進度，此處進度視為33%
								//
								// 開始載入資料
								//
		counter.LoadBitmap();
		character.LoadBitmap();

		for (int j = 0; j < NUMMAP; j++)
			for (int i = 0; i < NUMDIAMOND; i++)
				diamond[j][i].LoadBitmap();

		background.LoadBitmap("RES\\background1920.bmp");					// 載入背景的圖形
																			//
																			// 完成部分Loading動作，提高進度
																			//
		ShowInitProgress(50);
		Sleep(300); // 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
					//
					// 繼續載入其他資料
					//
		help.LoadBitmap(IDB_HELP, RGB(255, 255, 255));				// 載入說明的圖形
		corner.LoadBitmap(IDB_CORNER);							// 載入角落圖形
		corner.ShowBitmap(background);							// 將corner貼到background
		escmenu.LoadBitmap();
		// 音樂 //
		//CAudio::Instance()->Load(AUDIO_DING,  "sounds\\ding.wav");	// 載入編號0的聲音ding.wav
		//
		// 此OnInit動作會接到CGameStaterOver::OnInit()，所以進度還沒到100%
		//
		for (int i = 0; i < 5; i++) {
			gamemap[i].LoadBitmap();
		}
	}

	void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_SPACE = 0x20; // keyboard空白鍵
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_Q = 0x51; // keyboard上箭頭
		const char KEY_ESC = 27;
		const char KEY_ENTER = 13;
		const char KEY_p = 80;
		bool ESCstop = false;

		if (nChar == KEY_LEFT)
			character.SetMovingLeft(true);

		if (nChar == KEY_RIGHT)
			character.SetMovingRight(true);

		if (nChar == KEY_SPACE)
			character.SetMovingJump(true);

		if (nChar == KEY_DOWN)
			character.SetMovingDown(true);

		if (nChar == KEY_UP)
			character.SetMovingUp(true);

		if (nChar == KEY_Q)
			character.SetMovingDie(true);

		// ESCmenu用 //
		if (nChar == KEY_ESC && character.GetIsESC()) {
			character.SetIsESC(false);
			escmenu.SetState(0);
			ESCstop = true;
		}

		if (nChar == KEY_LEFT && character.GetIsESC())
			escmenu.clickLeft();

		if (nChar == KEY_RIGHT && character.GetIsESC())
			escmenu.clickRight();

		if (nChar == KEY_ESC && MapNumber != 0 && !ESCstop) {
			character.SetIsESC(true);
			escmenu.SetState(1);
		}

		if (nChar == KEY_ENTER && character.GetIsESC()) {
			int WHAT2DO = escmenu.clickEnter();
			if (WHAT2DO == 1) {
				MapNumber = 0;
				counter.ResetDiamondCount();
				character.SetXY(960, 1125);
				character.SetIsESC(false);
				escmenu.SetState(0);
			}
			else if (WHAT2DO == 2) {
				counter.ResetDiamondCount();
				character.SetXY(960, 1125);
				character.SetIsESC(false);
				escmenu.SetState(0);
				for (int i = 0; i < 5; i++)
					diamond[1][i].SetIsAlive(true);

				gamemap[1].SetCheckpoint(960, 1125);
			}
			else {
				if (!escmenu.GetMusicState()) {
					CAudio::Instance()->Stop(AUDIO_MENU);
				}
				else
				{
					CAudio::Instance()->Play(AUDIO_MENU, true);
				}
			}
		}
		//////////////
		if (nChar == KEY_p) {
			GotoGameState(GAME_STATE_OVER);
		}
	}

	void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_SPACE = 0x20; // keyboard空白鍵
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_Q = 0x51; // keyboard上箭頭

		if (nChar == KEY_LEFT)
			character.SetMovingLeft(false);

		if (nChar == KEY_RIGHT)
			character.SetMovingRight(false);

		if (nChar == KEY_SPACE)
			character.SetMovingJump(false);

		if (nChar == KEY_DOWN)
			character.SetMovingDown(false);

		if (nChar == KEY_UP)
			character.SetMovingUp(false);

		if (nChar == KEY_Q)
			character.SetMovingDie(false);
	}

	void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{
		// 沒事。如果需要處理滑鼠移動的話，寫code在這裡
	}

	void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
		// 沒事。如果需要處理滑鼠移動的話，寫code在這裡
	}


	void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
		// 沒事。如果需要處理滑鼠移動的話，寫code在這裡
	}

	void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{
		// 沒事。如果需要處理滑鼠移動的話，寫code在這裡
	}

	void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
		// 沒事。如果需要處理滑鼠移動的話，寫code在這裡
	}

	void CGameStateRun::OnShow()
	{
		const int NUMDIAMOND = 5;	// 鑽石的總數
									//
									//  注意：Show裡面千萬不要移動任何物件的座標，移動座標的工作應由Move做才對，
									//        否則當視窗重新繪圖時(OnDraw)，物件就會移動，看起來會很怪。換個術語
									//        說，Move負責MVC中的Model，Show負責View，而View不應更動Model。
									//
									//
									//  貼上背景圖、撞擊數、球、擦子、彈跳的球
									//
		background.ShowBitmap();			// 貼上背景圖
		help.ShowBitmap();					// 貼上說明圖
		GameMap = &gamemap[MapNumber];
		GameMap->ReadMap(MapNumber);
		GameMap->OnShow(MapNumber);
		character.OnShow(GameMap);					// 貼上擦子

													//
		for (int i = 0; i < NUMDIAMOND; i++)
			diamond[MapNumber][i].OnShow(GameMap);				// 貼上第i號

																//for (int i = 0; i < NUMDIAMOND; i++)
																//	diamond[i].OnShow(GameMap);				// 貼上第i號
		counter.OnShow();
		escmenu.OnShow();
		//
		//  貼上左上及右下角落的圖
		//
		corner.SetTopLeft(0, 0);
		corner.ShowBitmap();
		corner.SetTopLeft(SIZE_X - corner.Width(), SIZE_Y - corner.Height());
		corner.ShowBitmap();
	}

}