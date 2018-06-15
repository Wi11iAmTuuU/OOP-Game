#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "EscMenu.h"
////////////////////////////////////////////////////////////////////
///////////////////先備份開始目錄的ＣＯＤＥ/////////////////////////
////////////////////////////////////////////////////////////////////
namespace game_framework
{
	EscMenu::EscMenu()
	{
		Initialize();
	}
	void EscMenu::Initialize()
	{
		state = 0;				// 最初始(遊戲開始)
		MusicState = true;		// 音樂設定(開啟)
	}
	void EscMenu::LoadBitmap()
	{
		Empty.AddBitmap("RES\\ESC\\empty.bmp", RGB(255, 255, 255));
		FingerHomeVolume.AddBitmap("RES\\ESC\\ESC_home_volume.bmp", RGB(255, 255, 255));
		FingerHomeMute.AddBitmap("RES\\ESC\\ESC_home_mute.bmp", RGB(255, 255, 255));
		FingerReVolume.AddBitmap("RES\\ESC\\ESC_re_volume.bmp", RGB(255, 255, 255));
		FingerReMute.AddBitmap("RES\\ESC\\ESC_re_mute.bmp", RGB(255, 255, 255));
		FingerVolume.AddBitmap("RES\\ESC\\ESC_volume.bmp", RGB(255, 255, 255));
		FingerMute.AddBitmap("RES\\ESC\\ESC_mute.bmp", RGB(255, 255, 255));
	}
	void EscMenu::OnShow()
	{
		if (state == 0)
		{
			Empty.SetTopLeft(0, 0);
			Empty.OnShow();
		}
		else if (state == 1 && MusicState)
		{
			FingerHomeVolume.SetTopLeft(0, 0);
			FingerHomeVolume.OnShow();
		}
		else if (state == 1 && !MusicState)
		{
			FingerHomeMute.SetTopLeft(0, 0);
			FingerHomeMute.OnShow();
		}
		else if (state == 2 && MusicState)
		{
			FingerReVolume.SetTopLeft(0, 0);
			FingerReVolume.OnShow();
		}
		else if (state == 2 && !MusicState)
		{
			FingerReMute.SetTopLeft(0, 0);
			FingerReMute.OnShow();
		}
		else if (state == 3 && MusicState)
		{
			FingerVolume.SetTopLeft(0, 0);
			FingerVolume.OnShow();
		}
		else if (state == 3 && !MusicState)
		{
			FingerMute.SetTopLeft(0, 0);
			FingerMute.OnShow();
		}
	}
	void EscMenu::clickLeft()
	{
		if (state == 2)
		{
			state = 1;
		}
		else if (state == 3)
		{
			state = 2;
		}
		else {}
	}
	void EscMenu::clickRight()
	{
		if (state == 1)
		{
			state = 2;
		}
		else if (state == 2)
		{
			state = 3;
		}
		else {}
	}
	int EscMenu::clickEnter()
	{
		if (state == 1)
		{
			return 1;
		}
		else if (state == 2) {
			return 2;
		}
		else if(state == 3)
		{
			if (MusicState) {
				MusicState = false;
				return 0;
			}
			else {
				MusicState = true;
				return 0;
			}
		}
		else 
		{
			return 0;
		}
	}
	bool EscMenu::GetMusicState()
	{
		return MusicState;
	}
	void EscMenu::SetState(int s)
	{
		state = s;
	}
}