#include"Map.h"
namespace game_framework {


	class CDiamond
	{
	public:
		CDiamond();
		bool HitCharacter(CCharacter *character);						// 是否碰到擦子
		bool IsAlive();											// 是否活著
		void LoadBitmap();										// 載入圖形
																//void OnMove();											// 移動
		void OnShow(Map*);											// 將圖形貼到畫面
		void SetMapXY(int nx, int ny);								// 設定圓心的座標
		void SetIsAlive(bool alive);							// 設定是否活著
	protected:
		CAnimation animation;		// 鑽石的動畫
		int x, y;					// 鑽石左上角座標
		int mapX, mapY;				// 鑽石的簡易座標
		bool is_alive;				// 是否活著
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// 是否碰到參數範圍的矩形
	};
}
