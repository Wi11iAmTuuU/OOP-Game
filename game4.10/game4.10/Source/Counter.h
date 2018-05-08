namespace game_framework{
	class Counter
	{
	public:
		Counter();
		void LoadBitmap();								// ���J�ϧ�
		void OnShow(Map*);								// �N�ϧζK��e��
		void SetMapXY(Map*);							// �]�w��ߪ��y��
		void Add(int n);								// �W�[��ƭ�
	protected:
		CAnimation oneDiamond;		// �ʵe1
		CAnimation twoDiamond;		// �ʵe2
		CAnimation threeDiamond;	// �ʵe3
		CAnimation fourDiamond;		// �ʵe4
		CAnimation fiveDiamond;		// �ʵe5
		int x, y;					// ���W���y��
	private:
		int DiamondCount;			// �p�ۭp��
	};
}