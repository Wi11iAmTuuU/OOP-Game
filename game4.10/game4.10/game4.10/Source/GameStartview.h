#pragma once
namespace game_framework
{
class GameStartView
{
    public:
        GameStartView();					// �]�w����l��
		void Initialize();					// �]�w����l��
        void LoadBitmap();					// ���J�ϧ�
        void OnShow();						// �N�ϧζK��e��
        void clickLeft();					// �V���@��
        void clickRight();					// �V�k�@��
        int  clickEnter();					// �i�J���A
		bool GetMusicState();				// ���o���֪��A
    protected:
		CAnimation FingerPlayVolume;		// �C���}�l
		CAnimation FingerPlayMute;			// �C���}�l
		CAnimation FingerMute;				// ���ֶ}��
		CAnimation FingerVolume;			// ��������
        int state;							// �ثe���A
        bool MusicState;					// ���֪��A
};
}