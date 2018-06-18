/*
* mygame.cpp: ���ɮ��x�C��������class��implementation
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
	// �o��class���C�����C���}�Y�e������
	/////////////////////////////////////////////////////////////////////////////

	CGameStateInit::CGameStateInit(CGame* g)
		: CGameState(g)
	{
	}

	void CGameStateInit::OnInit()
	{
		//
		// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
		//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
		//
		ShowInitProgress(0);	// �@�}�l��loading�i�׬�0%
								//
								// �}�l���J���
								//
		Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
								//
								// ��OnInit�ʧ@�|����CGameStaterRun::OnInit()�A�ҥH�i���٨S��100%
								//
		Menu.LoadBitmap();
		CAudio::Instance()->Load(AUDIO_MENU, "RES\\Menu\\Menu_BGM.mp3");	// ���J�s��1���n��
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
		const char KEY_LEFT = 0x25; // keyboard���b�Y
		const char KEY_SPACE = 0x20; // keyboard�ť���
		const char KEY_RIGHT = 0x27; // keyboard�k�b�Y

		if (nChar == KEY_LEFT) {
			Menu.clickLeft();
		}
		else if (nChar == KEY_RIGHT) {
			Menu.clickRight();
		}
		else if (nChar == KEY_SPACE || nChar == KEY_ENTER)
			if (Menu.clickEnter()) {
				GotoGameState(GAME_STATE_RUN);						// ������GAME_STATE_RUN
			}
			else
			{
			}
		else if (nChar == KEY_ESC) {								// Demo �����C������k
			PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// �����C��
		}
		else {}
	}

	void CGameStateInit::OnShow()
	{
		Menu.OnShow();
	}

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����������A(Game Over)
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
		// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
		//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
		//
		ShowInitProgress(66);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���66%
								//
								// �}�l���J���
								//
		Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
								//
								// �̲׶i�׬�100%
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
	// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
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
		background.SetTopLeft(BACKGROUND_X, 0);				// �]�w�I�����_�l�y��
		help.SetTopLeft(0, SIZE_Y - help.Height());			// �]�w�����Ϫ��_�l�y��
		GameMap = &gamemap[MapNumber];
		GameMap->ReadMap(MapNumber);                               // �]�w�_�l�y��
		escmenu.Initialize();
		pass = false;
		// ���� //
		//CAudio::Instance()->Play(AUDIO_LAKE, true);			// ���� WAVE
	}

	void CGameStateRun::OnMove()							// ���ʹC������
	{
		const int NUMDIAMOND = 5;	// �p�۪��`��
									//
									// �p�G�Ʊ�ק�cursor���˦��A�h�N�U���{����commment�����Y�i
									//
									// SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));
									//
									//
									// ���ʥD��
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

	void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
	{
		const int NUMDIAMOND = 5;	// �p�۪��`��
		const int NUMMAP = 5;		// �a�ϼƶq
									//
									// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
									//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
									//
		ShowInitProgress(33);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���33%
								//
								// �}�l���J���
								//
		counter.LoadBitmap();
		character.LoadBitmap();

		for (int j = 0; j < NUMMAP; j++)
			for (int i = 0; i < NUMDIAMOND; i++)
				diamond[j][i].LoadBitmap();

		background.LoadBitmap("RES\\background1920.bmp");					// ���J�I�����ϧ�
																			//
																			// ��������Loading�ʧ@�A�����i��
																			//
		ShowInitProgress(50);
		Sleep(300); // ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
					//
					// �~����J��L���
					//
		help.LoadBitmap(IDB_HELP, RGB(255, 255, 255));				// ���J�������ϧ�
		corner.LoadBitmap(IDB_CORNER);							// ���J�����ϧ�
		corner.ShowBitmap(background);							// �Ncorner�K��background
		escmenu.LoadBitmap();
		// ���� //
		//CAudio::Instance()->Load(AUDIO_DING,  "sounds\\ding.wav");	// ���J�s��0���n��ding.wav
		//
		// ��OnInit�ʧ@�|����CGameStaterOver::OnInit()�A�ҥH�i���٨S��100%
		//
		for (int i = 0; i < 5; i++) {
			gamemap[i].LoadBitmap();
		}
	}

	void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_LEFT = 0x25; // keyboard���b�Y
		const char KEY_SPACE = 0x20; // keyboard�ť���
		const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
		const char KEY_DOWN = 0x28; // keyboard�U�b�Y
		const char KEY_UP = 0x26; // keyboard�W�b�Y
		const char KEY_Q = 0x51; // keyboard�W�b�Y
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

		// ESCmenu�� //
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
		const char KEY_LEFT = 0x25; // keyboard���b�Y
		const char KEY_SPACE = 0x20; // keyboard�ť���
		const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
		const char KEY_DOWN = 0x28; // keyboard�U�b�Y
		const char KEY_UP = 0x26; // keyboard�W�b�Y
		const char KEY_Q = 0x51; // keyboard�W�b�Y

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

	void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
	{
		// �S�ơC�p�G�ݭn�B�z�ƹ����ʪ��ܡA�gcode�b�o��
	}

	void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
	{
		// �S�ơC�p�G�ݭn�B�z�ƹ����ʪ��ܡA�gcode�b�o��
	}


	void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
	{
		// �S�ơC�p�G�ݭn�B�z�ƹ����ʪ��ܡA�gcode�b�o��
	}

	void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
	{
		// �S�ơC�p�G�ݭn�B�z�ƹ����ʪ��ܡA�gcode�b�o��
	}

	void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
	{
		// �S�ơC�p�G�ݭn�B�z�ƹ����ʪ��ܡA�gcode�b�o��
	}

	void CGameStateRun::OnShow()
	{
		const int NUMDIAMOND = 5;	// �p�۪��`��
									//
									//  �`�N�GShow�̭��d�U���n���ʥ��󪫥󪺮y�СA���ʮy�Ъ��u�@����Move���~��A
									//        �_�h��������sø�Ϯ�(OnDraw)�A����N�|���ʡA�ݰ_�ӷ|�ܩǡC���ӳN�y
									//        ���AMove�t�dMVC����Model�AShow�t�dView�A��View�������Model�C
									//
									//
									//  �K�W�I���ϡB�����ơB�y�B���l�B�u�����y
									//
		background.ShowBitmap();			// �K�W�I����
		help.ShowBitmap();					// �K�W������
		GameMap = &gamemap[MapNumber];
		GameMap->ReadMap(MapNumber);
		GameMap->OnShow(MapNumber);
		character.OnShow(GameMap);					// �K�W���l

													//
		for (int i = 0; i < NUMDIAMOND; i++)
			diamond[MapNumber][i].OnShow(GameMap);				// �K�W��i��

																//for (int i = 0; i < NUMDIAMOND; i++)
																//	diamond[i].OnShow(GameMap);				// �K�W��i��
		counter.OnShow();
		escmenu.OnShow();
		//
		//  �K�W���W�Υk�U��������
		//
		corner.SetTopLeft(0, 0);
		corner.ShowBitmap();
		corner.SetTopLeft(SIZE_X - corner.Width(), SIZE_Y - corner.Height());
		corner.ShowBitmap();
	}

}