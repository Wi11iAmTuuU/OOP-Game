#pragma once
#include"Map.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���ѥi�H����L�ηƹ�������l
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////

	class CCharacter
	{
	public:
		CCharacter();
		int  GetX1();					// ���l���W�� x �y��
		int  GetY1();					// ���l���W�� y �y��
		int  GetX2();					// ���l�k�U�� x �y��
		int  GetY2();					// ���l�k�U�� y �y��
		void Initialize();				// �]�w���l����l��
		void LoadBitmap();				// ���J�ϧ�
		void OnMove(Map*,int*);					// �������l
		void OnShow(Map*);					// �N���l�ϧζK��e��
		void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
		void SetMovingRight(bool flag); // �]�w�O�_���b���k����
		void SetMovingJump(bool flag);	// �]�w�O�_���b���W����
		void SetMovingDown(bool flag);	// �]�w�O�_���b���U����
		//
		void SetMovingFly(bool flag);	// �]�w�O�_���b���U����
		//
		void SetXY(int nx, int ny);		// �]�w���l���W���y��
		int  GetMapNumber();				// �����a�Ͻs��
		void ChangeMapNumber(int);             //���ܦa�Ͻs��
	protected:
		CAnimation animation;		// ���l���ʵe
		CAnimation animation_Underarm;		// ���l���ʵe
		CAnimation animation_Left;		// ���l���ʵe
		CAnimation animation_right;		// ���l���ʵe
		int x, y;					// ���l���W���y��
		int MapNumber;
		//
		int floor;				// �a�O��Y�y��
		bool rising;			// true��W�ɡBfalse��U��
		bool falling;           // true��U���Bfalse��W��
		int initial_velocity;	// ��l�t��
		int velocity;			// �ثe���t��(�I/��)
		bool IsJumping;			// true���ģ�Bfalse��D��ģ
		bool IsJumpTwice;		// true��w�G�q���Bfalse���G�q��
		bool Isfalling;
		//
		bool isMovingFly;
		//
		bool isMovingLeft;			// �O�_���b��������
		bool isMovingRight;			// �O�_���b���k����
		bool isMovingJump;			// �O�_���b���W����
		bool isMovingDown;			// �O�_���b���U����
	};
}