namespace game_framework{
	class Counter
	{
	public:
		Counter();
		void LoadBitmap();								// 載入圖形
		void OnShow(Map*);								// 將圖形貼到畫面
		void SetMapXY(Map*);							// 設定圓心的座標
		void Add(int n);								// 增加整數值
	protected:
		CAnimation oneDiamond;		// 動畫1
		CAnimation twoDiamond;		// 動畫2
		CAnimation threeDiamond;	// 動畫3
		CAnimation fourDiamond;		// 動畫4
		CAnimation fiveDiamond;		// 動畫5
		int x, y;					// 左上角座標
	private:
		int DiamondCount;			// 鑽石計數
	};
}