#pragma once
#include "../../Base/SceneBase.h"
#include "../../../Object/Camera/Camera.h"
#include "../../../Object/Character/Player/Player.h"
#include "../../../Object/Character/Enemy/EnemyFox/EnemyFox.h"
#include "../../../Object/Map/MiniGame_1Map/MiniGame_1Map.h"

#include "../../../Object/Command/Command.h"

#include "../../../Object/Physycs/Physycs.h"

#include "../../../InputDevice/InputManager.h"

namespace EP
{
	static constexpr int EnemyNum = 3;
}

class MiniGameGameScene : public SceneBase
{
private:
	std::shared_ptr<Command> m_command;

	std::shared_ptr<Camera> m_camera;
	std::shared_ptr<Player> m_player;
	std::shared_ptr<MiniGame_1Map> m_map1;

	std::vector<std::shared_ptr<EnemyFox>> m_enemyFox; // std::vectorに変更
	std::shared_ptr<EnemyFox> m_lockedOnEnemy;//現在ロックオンしている敵

	std::shared_ptr<Physycs> m_physycs;

	std::shared_ptr<InputManager> m_Idm;

	int LightHandle[3];

	bool m_isLoading;//ロード中かどうか

private:
	/*別のシーンで実装していくためいったんは仮置き*/
	bool m_isGameOver;
	bool m_isGameClear;

	int m_GameOverGraphHandle;
	int m_GameClearGraphHandle;

	int m_pushRunTime;
	/*別のシーンで実装していくためいったんは仮置き*/


public:
	MiniGameGameScene();
	~MiniGameGameScene();

	void Init() override;
	void Update() override;
	void Draw() override;
	void Final() override;

private:
	void UpdateRun();//本処理
	void DrawRun();//本描画

	void PlayerControlCamera();//プレイヤーがカメラ操作を行う

	void Update_LockOnCamera();//ロックオンのこうしん　

	std::shared_ptr<EnemyFox> GetClosestEnemy();//一番プレイヤーから近い敵
	void LockOnToEnemy(std::shared_ptr<EnemyFox> enemy);//敵のロックオン
	void UnlockEnemy();//ロックオン解除

	bool AreAllEnemiesDefeated();//敵がすべて倒されたかどうか

private:
	void DrawLoadinBar();
	float GetLoadingProgress();

	VECTOR WorldToScreen(const VECTOR& worldPos)
	{
		// 3D座標を2Dスクリーン座標に変換
		return ConvWorldPosToScreenPos(worldPos);
	}
};

