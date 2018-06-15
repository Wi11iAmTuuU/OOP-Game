#pragma once
#include "Map.h"
namespace game_framework
{
	class EscMenu
	{
	public:
		EscMenu();							// �]�w����l��
		void Initialize();					// �]�w����l��
		void LoadBitmap();					// ���J�ϧ�
		void OnShow();						// �N�ϧζK��e��
		void clickLeft();					// �V���@��
		void clickRight();					// �V�k�@��
		int  clickEnter();					// �i�J���A
		bool GetMusicState();				// ���o���֪��A
		void SetState(int s);
	protected:
		CAnimation Empty;					// �C���}�l
		CAnimation FingerHomeVolume;		// �C���}�l
		CAnimation FingerHomeMute;			// �C���}�l
		CAnimation FingerReVolume;			// ���ֶ}��
		CAnimation FingerReMute;			// ��������
		CAnimation FingerVolume;			// �C���}�l
		CAnimation FingerMute;				// �C���}�l
		int state;							// �ثe���A 
											// 0->EMPTY 1->�^��j�U 2->���d���s 3->���ֱҳ�
		bool MusicState;					// ���֪��A
	};
}
