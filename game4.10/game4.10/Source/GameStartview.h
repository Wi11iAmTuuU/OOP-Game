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
    protected:
		CAnimation FingerPlay;				// �C���}�l
		CAnimation FingerQuestion;			// �����}�l
		CAnimation Question;				// ����
        int state;							// �ثe���A
};
}