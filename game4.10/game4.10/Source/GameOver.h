#pragma once
namespace game_framework
{
	class GameOver
	{
	public:
		GameOver();							// �]�w����l��
		void Initialize();					// �]�w����l��
		void LoadBitmap();					// ���J�ϧ�
		void OnShow();						// �N�ϧζK��e��
	protected:
		CAnimation congratulations;					// �C���}�l
		int y;
	};
}