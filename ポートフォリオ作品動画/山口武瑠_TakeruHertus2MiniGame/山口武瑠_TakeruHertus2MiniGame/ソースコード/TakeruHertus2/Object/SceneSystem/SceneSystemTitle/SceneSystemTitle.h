#pragma once
#include "../../Entity/Entity.h"
#include "../../../UI/UIManager.h"
#include "../../../InputDevice/InputManager.h"

namespace SCENESYSTEMTITLE
{
	static constexpr int OBJECTNUM = 10000;//ロード画面の確認をするためにあえて負荷をかける
	//static constexpr int OBJECTNUM =4;
}

class SceneSystemTitle : public Entity
{
private:
	/*インスタンス宣言（コンポーネント）*/
	std::vector<std::shared_ptr<ComponentTransform>> m_transform;
	std::vector<std::shared_ptr<ComponentGraph>> m_graph;

	/*インスタンス宣言*/
	std::shared_ptr<UIManager> m_uiManager;//UIマネージャ
	std::shared_ptr<InputManager> m_inputManager;//入力マネージャ

	/*変数宣言*/
	int m_selectedCellX;
	int m_selectedCellY;
	
	//選択肢の種類
	typedef enum
	{
		eSelect_NEWGAME,	//新規ゲーム
		eSelect_LOADGAME,	//ロード
		eSelect_BACK,		//戻る
		eSelect_ObjectNum	//選択肢の数-1
	}eSelect;

	//選択中の選択肢
	int m_currentSelect;
	
	//選択中の座標
	VECTOR m_currentSelectPos;

	//フェードエフェクト用の変数（将来的には別のクラスに写したい）
	int m_fadeCount;

public:
	SceneSystemTitle();
	~SceneSystemTitle();

	void Init();
	void Update();
	void Draw();
	void Final();

	void DrawGrid(int width, int height, int cellSize);
	void UpdateSelectedCell(int _mouseX, int _mouseY, int _cellSize);
	void DrawSelectedCell(int _cellSize);

private:
	void DrawCurrentSelect();

};

