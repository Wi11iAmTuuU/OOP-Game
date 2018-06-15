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
		void StorePortal();                 // �s�x�a�϶ǰe�̦�l
        void ReadMap(int);					// ���J�a��
        void OnMove(int, int);              // �a�ϲ���
        void OnShow(int);					// �N�ϧζK��e��
        void SetXY(int nx, int ny);         // �]�w�ù��e�����W�����y��
        void SetCheckpoint(int, int);		// �]�w�O���I�y��
        bool isEmpty(int x, int y);         // �P�_�I��;
        int	 Getsx();						// �p�ƾ���
        int	 Getsy();						// �p�ƾ���
        int	 GetCheckpointX();				// �O���I��
        int	 GetCheckpointY();				// �O���I��
		int  GetPortalX(int);				// �ǰe����
		int  GetPortalY(int);				// �ǰe����
        //int  GetMapNumber();				// �����a�Ͻs��
        //void ChangeMapNumber(int);             //���ܦa�Ͻs��
protected:
	CMovingBitmap background;			// �a��
	CMovingBitmap Normalblock;			//��ܤ@����
	CMovingBitmap LoseSpeedBlock;		//��ܴ�t���
	CMovingBitmap SpeedBlock;			//��ܥ[�t���
	CMovingBitmap AutoSpeedBlockRight;  //��ܩ��k�۰ʤ��
	CMovingBitmap AutoSpeedBlockLeft;   //��ܩ����۰ʤ��
	CMovingBitmap WaterBlock;           //��ܤ����
	CMovingBitmap CheckpointBlock;		//��ܰO���I���
	CMovingBitmap LightCheckpointBlock; //��ܰO���I���(�}��)
	CMovingBitmap JumpBlock;			//��ܸ��D���
	CMovingBitmap door;                 //��ܪ�
	CMovingBitmap PortalBlock;          //��ܶǰe��
private:
	int sx, sy;							// ���W���y��
	int Map1[30][40] = { 0 };   // 1 = �@���� 2 = ��t��� 3 = �[�t��� 4 = �V�k�۰ʤ�� 5 = �V���۰ʤ�� 
								// 6 = ���D��� 9 = ����� 10 = CheckPoint 12 = �� �ǰe�� = 50~59 
	int Portal[20][2] = { 0 };
	int CheckpointX, CheckpointY;
};
}
