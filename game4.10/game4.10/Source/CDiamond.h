#include"Map.h"
namespace game_framework {


	class CDiamond
	{
	public:
		CDiamond();
		bool HitCharacter(CCharacter *character);						// �O�_�I�����l
		bool IsAlive();											// �O�_����
		void LoadBitmap();										// ���J�ϧ�
																//void OnMove();											// ����
		void OnShow(Map*);											// �N�ϧζK��e��
		void SetXY(int nx, int ny);								// �]�w��ߪ��y��
		void SetIsAlive(bool alive);							// �]�w�O�_����
	protected:
		CAnimation animation;		// ���l���ʵe
		int x, y;					// ���l���W���y��
		bool is_alive;				// �O�_����
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// �O�_�I��Ѽƽd�򪺯x��
	};
}
