#pragma once
#include"Map.h"
namespace game_framework
{
class Counter
{
    public:
        Counter();
        void LoadBitmap();								// ���J�ϧ�
        void OnShow();								// �N�ϧζK��e��
        void Add(int n);								// �W�[��ƭ�
        void ResetDiamondCount();
        int  GetDiamondCount();
    protected:
        CAnimation oneDiamond;		// �ʵe1
        CAnimation twoDiamond;		// �ʵe2
        CAnimation threeDiamond;	// �ʵe3
        CAnimation fourDiamond;		// �ʵe4
        CAnimation fiveDiamond;		// �ʵe5
    private:
        int DiamondCount;			// �p�ۭp��
};
}