#pragma once
#include "../Base/SceneBase.h"
#include "SceneGameCommon.h"
#include "../../MathLib/MathLib.h"

/*仮なのであとで移行します*/
namespace ColInfo
{
	//最大当たり判定ポリゴン数
	constexpr int kMaxColHitPolyNum = 2000;
	//壁押し出し処理の最大試行回数
	constexpr int kMaxColHitTryNum = 16;
	//壁押し出し時にスライドさせる距離
	constexpr float kColHitSlideLength = 1.0f;
}


class SceneGame : public SceneBase
{
private:
    /*キャラクター*/
	std::shared_ptr<Player> m_player;       //プレイヤー
    std::shared_ptr<EnemyFox> m_enemyFox;   //狐の敵

	/*敵マネージャー*/
	std::shared_ptr<EnemyManager> m_enemyManager;//敵のマネージャ

    /*カメラ*/
	std::shared_ptr<Camera> m_camera;       //カメラ
	/*マップ*/
	std::shared_ptr<TutorialMap> m_tutorialMap;//チュートリアルマップ

	/*メニュ全般*/
	std::shared_ptr<MenuSystem> m_menuSystem;
	
	/*コマンド系*/
	std::shared_ptr<Command> m_command;


	/*数学関数*/
	std::shared_ptr<MathLib> m_mathLib;

	/*変数宣言*/
	bool m_isLoading;//ロード中かどうか
	bool m_isOpenMenu;//メニューを開いているかどうか

	//bool m_isBattle;//戦闘中かどうか

	void PlayerControlCamera();


public:
	SceneGame();
	~SceneGame()override;

	void Init() override;
	void Update() override;
	void Draw() override;
	void Final() override;

	void IsTestPhsycse();
	void IsTestPhsycseEnemy();

	void CapsuleHitResolve();


private:
	bool m_isLookOn = false;


	/*セーブテスト実装*/
	VECTOR m_savePointPos = VGet(0,20,0);
	float m_savePointRadius = 50.0f;
	void SavePoint();
	void SaveGame();
	int TestHiScore = 0;


	/*テスト用変数*/
	VECTOR boxPos;
	VECTOR boxSize;

	/*仮ライト*/
	int lightHandle;

	/*当たり判定のテスト*/
	struct Polygon
	{
		VECTOR vertex[3];
		VECTOR Normal = VGet(0,0,0);
		VECTOR center = VGet(0,0,0);
	}m_polygon[3];

	MV1_COLL_RESULT_POLY_DIM m_hitDim{};




};

