#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "GameStartview.h"
namespace game_framework
{
GameStartView::GameStartView()
{
	Initialize();
}
void GameStartView::Initialize()
{
	state = 0;				// 最初始(遊戲開始)
	MusicState = true;		// 音樂設定(開啟)
}
void GameStartView::LoadBitmap()
{
	FingerMute.AddBitmap("RES\\Menu\\Menu_fingermute.bmp");
	FingerPlayMute.AddBitmap("RES\\Menu\\Menu_fingerplay_mute.bmp");
	FingerVolume.AddBitmap("RES\\Menu\\Menu_fingervolume.bmp");
	FingerPlayVolume.AddBitmap("RES\\Menu\\Menu_fingerplay_volume.bmp");
}
void GameStartView::OnShow()
{
    if (state == 0 && MusicState)
    {
        FingerPlayVolume.SetTopLeft(0, 0);
		FingerPlayVolume.OnShow();
    }
    else if (state == 0 && !MusicState)
    {
        FingerPlayMute.SetTopLeft(0, 0);
        FingerPlayMute.OnShow();
    }
    else if (state == 1 && MusicState)
    {
        FingerVolume.SetTopLeft(0, 0);
        FingerVolume.OnShow();
    }
    else if (state == 1 && !MusicState)
    {
        FingerMute.SetTopLeft(0, 0);
        FingerMute.OnShow();
    }
}
void GameStartView::clickLeft()
{
    if (state == 1)
    {
        state = 0;
    }
	else {}	
}
void GameStartView::clickRight()
{
    if (state == 0)
    {
        state = 1;
    }
	else {}
}
int GameStartView::clickEnter()
{
    if (state == 0)
    {
        return 1;
    }
    else
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
}
bool GameStartView::GetMusicState()
{
	return MusicState;
}
}