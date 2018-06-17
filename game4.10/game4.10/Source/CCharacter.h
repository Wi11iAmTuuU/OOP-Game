#pragma once
#include "Map.h"
#include "Counter.h"
#include "EscMenu.h"
namespace game_framework
{
/////////////////////////////////////////////////////////////////////////////
// �o��class���ѥi�H����L�ηƹ�������l
// �����N�i�H��g���ۤv���{���F
/////////////////////////////////////////////////////////////////////////////

class CCharacter
{
	enum AUDIO_ID  				// �w�q�U�ح��Ī��s��
	{
		AUDIO_MENU,				// 1
		AUDIO_DOOR,
		AUDIO_JUMP,
		AUDIO_PORTAL,
		AUDIO_WATER,
		AUDIO_UNPASS,
		AUDIO_DIAMOND
	};
    public:
        CCharacter();
        int  GetX1();						// ���l���W�� x �y��
        int  GetY1();						// ���l���W�� y �y��
        int  GetX2();						// ���l�k�U�� x �y��
        int  GetY2();						// ���l�k�U�� y �y��
		bool GetIsESC();
        void Initialize();					// �]�w���l����l��
        void LoadBitmap();					// ���J�ϧ�
        void SetXY(int nx, int ny);			// �]�w���l���W���y��
        void OnMove(Map*, int*, Counter*, EscMenu*);	// �������l
        void OnShow(Map*);					// �N���l�ϧζK��e��
        void SetMovingLeft(bool flag);		// �]�w�O�_���b��������
        void SetMovingRight(bool flag);		// �]�w�O�_���b���k����
        void SetMovingJump(bool flag);		// �]�w�O�_���b���W����
        void SetMovingDown(bool flag);		// �]�w�O�_���b���U����
        void SetMovingDie(bool flag);		// �]�w�O�_���b�۱�
		void SetIsESC(bool state);
        //
        void SetMovingUp(bool flag);		// �]�w�O�_���b���U����
        //
        int  GetMapNumber();				// �����a�Ͻs��
        void ChangeMapNumber(int);          // ���ܦa�Ͻs��
    protected:
        CAnimation animation;				// ���l���ʵe
        CAnimation animation_Underarm;		// ���l���ʵe
        CAnimation animation_Left;			// ���l���ʵe
        CAnimation animation_right;			// ���l���ʵe
        CAnimation animation_Die;			// ���l���ʵe
        CAnimation animation_relive;		// ���l���ʵe
		CAnimation animation_transfer;        // ���l���ʵe
        int x, y;							// ���l���W���y��

        int MapNumber;
        //
        int floor;				// �a�O��Y�y��
        bool rising;			// true��W�ɡBfalse��U��
        bool falling;           // true��U���Bfalse��W��
        int initial_velocity;	// ��l�t��
        int velocity;			// �ثe���t��(�I/��)
		int velocityLeft;
		int velocityRight;
        int dieCounter;			// ���`�p��
		int PortalCounter;		// �ǰe���p��
		int PortalNumber;       // �ǰe���s��
        bool IsJumping;			// true���ģ�Bfalse��D��ģ
        bool IsJumpTwice;		// true��w�G�q���Bfalse���G�q��
        bool Isfalling;
        bool IsDieing;
        bool IsReliving;
		bool IsJumpingRight;
		bool IsJumpingLeft;
		bool IsTransfer;
		bool IsESC;
        //
        bool isMovingUp;
        //
        bool isMovingLeft;			// �O�_���b��������
        bool isMovingRight;			// �O�_���b���k����
        bool isMovingJump;			// �O�_���b���W����
        bool isMovingDown;			// �O�_���b���U����
        bool isMovingDie;			// �O�_���b�۱�
};
}