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
		int  GetWidth();                    //���o�I���e��
		int  GetHeight();                   //���o�I������
		int  ScreenX(int x);    // �ù� x �y��
		int  ScreenY(int y);    // �ù� y �y��
		void Initialize();     // �]�w����l��
		void LoadBitmap();   // ���J�ϧ�
		void ReadMap();      //���J�a��
		void OnMove(int, int);               // �a�ϲ���
		void OnShow();      // �N�ϧζK��e��
		void SetXY(int nx, int ny);         // �]�w�ù��e�����W�����y��
		bool isEmpty(int x, int y);         // �P�_�I��;
	protected:
		CMovingBitmap background;   // �a��
		CMovingBitmap block;     //��ܦa�ι�
	private:
		int sx, sy;       // ���W���y��
		//int mapSize_X, mapSize_Y;   //�a�ϩҤ������
		int Map1[30][40] = { 0 };

	};
}
