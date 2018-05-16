#pragma once
namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���ѥi�H����L�ηƹ�������l
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////

	class Map
	{
	public:
		int  GetWidth();                    // ���o�I���e��
		int  GetHeight();                   // ���o�I������
		int  ScreenX(int x);				// �ù� x �y��
		int  ScreenY(int y);				// �ù� y �y��
		int  GetBlock(int x, int y);		// ���o���
		void Initialize();					// �]�w����l��
		void LoadBitmap();					// ���J�ϧ�
		void ReadMap(int);						// ���J�a��
		void OnMove(int, int);              // �a�ϲ���
		void OnShow(int);						// �N�ϧζK��e��
		void SetXY(int nx, int ny);         // �]�w�ù��e�����W�����y��
		bool isEmpty(int x, int y);         // �P�_�I��;
		int	 Getsx();						// �p�ƾ���
		int	 Getsy();						// �p�ƾ���
		//int  GetMapNumber();				// �����a�Ͻs��
		//void ChangeMapNumber(int);             //���ܦa�Ͻs��
	protected:
		CMovingBitmap background;			// �a��
		CMovingBitmap Normalblock;			//��ܤ@����
		CMovingBitmap LoseSpeedBlock;		//��ܴ�t���
		CMovingBitmap SpeedBlock;			//��ܥ[�t���
		CMovingBitmap door;                 //��ܪ�
	private:
		int sx, sy;							// ���W���y��
		int Map1[30][40] = { 0 };   // 1 = �@���� 2 = ��t��� 3 = �[�t��� 11 = ��

	};
}
