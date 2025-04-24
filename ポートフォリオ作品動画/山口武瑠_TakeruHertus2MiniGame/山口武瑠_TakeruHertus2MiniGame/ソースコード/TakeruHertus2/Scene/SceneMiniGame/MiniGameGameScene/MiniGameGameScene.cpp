#include "MiniGameGameScene.h"
#include "../../Manager/SceneManager.h"
#include <limits>
#include <algorithm>

MiniGameGameScene::MiniGameGameScene()
	: LightHandle{-1,-1, -1}
	, m_isLoading(true)

	/*仮start*/
	, m_isGameOver(false)
	, m_isGameClear(false)
	, m_GameOverGraphHandle(-1)
	, m_GameClearGraphHandle(-1)
	, m_pushRunTime(0)
	/*仮end*/
{
	m_command = std::make_shared<Command>();
	m_camera = std::make_shared<Camera>();
	m_player = std::make_shared<Player>();
	m_map1 = std::make_shared<MiniGame_1Map>();

	m_enemyFox.resize(EP::EnemyNum);
	for (int i = 0; i < m_enemyFox.size(); i++)
	{
		m_enemyFox[i] = std::make_shared<EnemyFox>();
	}

	m_physycs = std::make_shared<Physycs>(m_player, m_map1, m_enemyFox);

	m_Idm = std::make_shared<InputManager>();
}



MiniGameGameScene::~MiniGameGameScene()
{
}

void MiniGameGameScene::Init()
{
	m_Idm->Init();

	// ディレクショナルライトの設定
	LightHandle[0] = CreateDirLightHandle(VGet(0.0f, -1.0f, 0.0f)); // 初期方向

	LightHandle[1] = CreateDirLightHandle(VGet(0, 1.0f, 0));

	SetLightEnable(TRUE);

	m_command->Init();
	m_camera->Init();
	m_player->Init();
	m_map1->Init();

	for (int i = 0; i < m_enemyFox.size(); i++)
	{
		m_enemyFox[i]->Init();
	}

	m_enemyFox[0]->SetPosition(VGet(0,0,0));
	m_enemyFox[1]->SetPosition(VGet(100, 0, 0));
	m_enemyFox[2]->SetPosition(VGet(-100, 0, 0));

	m_isLoading = true;

	/*仮start*/
	m_isGameClear = false;
	m_isGameOver = false;

	m_GameClearGraphHandle = LoadGraph("../Data/Asset/2D/MiniGame/TitleScene/MiniGameGameClear.png");
	m_GameOverGraphHandle = LoadGraph("../Data/Asset/2D/MiniGame/TitleScene/MiniGameGameOverBackGround.png");
	
	m_pushRunTime = 0;
	/*仮end*/
}

void MiniGameGameScene::Update()
{
	m_Idm->Update();

	if (m_isLoading)
	{
		if (GetASyncLoadNum() == 0)
		{
			m_isLoading = false;
		}
	}
	else
	{
		if (m_isGameClear == false && m_isGameOver == false)
		{
			UpdateRun();
		}

		/*仮start*/
		if (m_isGameOver == true)
		{
			if (m_pushRunTime >= 100)
			{
				m_pushRunTime = 100;
			}
			else
			{
				m_pushRunTime++;
			}

			if (m_Idm->m_joyPad->isB == true && m_pushRunTime == 100)
			{
				SceneManager::GetInstance().ChangeScene(SceneType::MiniGame_Title);
			}

			if (m_Idm->m_joyPad->isA == true && m_pushRunTime == 100)
			{
				Effkseer_End();			//エふぇくしあの解放
				DxLib_End();			//DxLibの解放
			}
		}

		if (m_isGameClear == true)
		{
			if (m_pushRunTime >= 100)
			{
				m_pushRunTime = 100;
			}
			else
			{
				m_pushRunTime++;
			}

			if (m_Idm->m_joyPad->isB == true && m_pushRunTime == 100)
			{
				SceneManager::GetInstance().ChangeScene(SceneType::MiniGame_Title);
			}
		}
		/*仮end*/

	}
}

void MiniGameGameScene::Draw()
{
	if (m_isLoading)
	{
		DrawLoadinBar();
		
		if (GetASyncLoadNum() == 0)
		{
			m_isLoading = false;
		}
	}
	else
	{
		DrawRun();
		/*仮start*/
		if (m_isGameOver == true)
		{
			DrawGraph(0, 0, m_GameOverGraphHandle, true);
		}

		if (m_isGameClear == true)
		{
			DrawGraph(0, 0, m_GameClearGraphHandle, true);
		}
		/*仮end*/


	}
}

void MiniGameGameScene::Final()
{
	m_command->Final();
	m_camera->Final();
	m_player->Final();
	m_map1->Final();

	for (int i = 0; i < m_enemyFox.size(); i++)
	{
		m_enemyFox[i]->Final();
	}

	DeleteLightHandle(LightHandle[0]);
	DeleteLightHandle(LightHandle[1]);

	/*仮start*/
	DeleteGraph(m_GameClearGraphHandle);
	DeleteGraph(m_GameOverGraphHandle);
	/*仮end*/


}

void MiniGameGameScene::UpdateRun()
{
	m_command->Update();
	m_player->SetIsAttackCheck(m_command->GetIsAttack());//攻撃コマンドが反応しているか

	/*攻撃処理*/
	for (auto& enemy : m_enemyFox)
	{
		if (VSize(VSub(enemy->GetPosition(), m_player->GetAttackPosition())) <= enemy->GetRadius() + m_player->GetAttackRadius())
		{
			if (m_command->GetIsAttack() == true)
			{
				enemy->SetIsTakeDamage(m_player->GetAttackValue());
			}
		}
	}

	// プレイヤーのY座標が-300以下になったらHPを0にする
	if (m_player->GetPosition().y < -300)
	{
		m_player->SetHP(0);

	}

	// 敵のY座標が-300以下になったらHPを0にする
	for (auto& enemy : m_enemyFox)
	{
		if (enemy->GetPosition().y < -300)
		{
			enemy->SetHp(0);
		}
	}

	m_physycs->Update();
	PlayerControlCamera();
	m_map1->Update();


	for (int i = 0; i < m_enemyFox.size(); i++)
	{
		m_enemyFox[i]->SetTargetPosition(m_player->GetPosition());
		m_enemyFox[i]->Update();
	}

	Update_LockOnCamera();

	//敵がすべて倒されたかを確認
	if (AreAllEnemiesDefeated())
	{
		m_isGameClear = true;
	}

	if (m_player->GetHp() == 0)
	{
		m_isGameOver = true;
	}

	

	SetLightPositionHandle(LightHandle[0], VGet(-200, 200, 0));
}

void MiniGameGameScene::DrawRun()
{
	m_player->Draw();
	m_map1->Draw();

	for (int i = 0; i < m_enemyFox.size(); i++)
	{
		m_enemyFox[i]->Draw();
		// 敵の頭上にHPバーを表示
		VECTOR enemyPos = m_enemyFox[i]->GetPosition();
		enemyPos.y += 20; // 頭上に表示するためにY座標を調整
		VECTOR screenPos = WorldToScreen(enemyPos);

		int hp = m_enemyFox[i]->GetHP();
		int maxHp = 100; // 最大HPを仮定
		int barWidth = 50;
		int barHeight = 5;
		int barX = static_cast<int>(screenPos.x) - barWidth / 2;
		int barY = static_cast<int>(screenPos.y) - barHeight / 2;

		// HPバーの背景
		DrawBox(barX, barY, barX + barWidth, barY + barHeight, GetColor(255, 0, 0), TRUE);
		// HPバーの前景
		DrawBox(barX, barY, barX + static_cast<int>(barWidth * (hp / static_cast<float>(maxHp))), barY + barHeight, GetColor(0, 255, 0), TRUE);
	}
	m_command->Draw();

#ifdef _DEBUG
	//DrawString(0, 0, "MiniGame_GameScene", 0xffffff);

	// 残りの敵の数を表示
	int remainingEnemies = std::count_if(m_enemyFox.begin(), m_enemyFox.end(), [](const std::shared_ptr<EnemyFox>& enemy) {
		return enemy->GetHP() > 0;
		});
	//DrawFormatString(0, 20, 0xffffff, "EnemyNum:%d", remainingEnemies);
	//DrawFormatString(0, 160, 0xffffff, "PlayerHP:%d", m_player->GetHp());
	//DrawFormatString(0, 180, 0xffffff, "PlayerY:%f", m_player->GetPosition().y);


#endif // _DEBUG
}

void MiniGameGameScene::PlayerControlCamera()
{
	/*カメラの角度を考慮した座標に変換*/
	m_player->SetConversionHorizontalAngle(m_camera->GetHAngle());
	m_player->SetConversionCosParam(m_camera->GetCosParam());
	m_player->SetConversionSinParam(m_camera->GetSinParam());
	m_player->Update();

	m_camera->SetTag(TagCameraObject::CONTROL);

	m_camera->SetPlayerPosition(m_player->GetPosition());
	m_camera->SetTarget(m_player->GetPosition());
	//m_camera->SetLookOnTarget(m_enemyFox->GetPosition());

	//m_camera->SetLookOnTarget(m_enemyManager->GetPosition());

	m_camera->Update();
}

void MiniGameGameScene::Update_LockOnCamera()
{
	std::shared_ptr<EnemyFox> closestEnemy = GetClosestEnemy();
	if (closestEnemy)
	{
		LockOnToEnemy(closestEnemy);
	}
	//// ロックオン中でない場合のみ、プレイヤーから一番近い敵をロックオン
	//if (!m_lockedOnEnemy)
	//{
	//	std::shared_ptr<EnemyFox> closestEnemy = GetClosestEnemy();
	//	if (closestEnemy)
	//	{
	//		LockOnToEnemy(closestEnemy);
	//	}
	//}
	//else
	//{
	//	// ロックオン中の敵が存在する場合、その敵の位置をカメラに設定
	//	m_camera->SetLookOnTarget(m_lockedOnEnemy->GetPosition());

	//	// ロックオン中の敵が一定距離以上離れた場合、ロックオンを解除
	//	float distance = VSize(VSub(m_player->GetPosition(), m_lockedOnEnemy->GetPosition()));
	//	if (distance > 200.0f) // 例として200.0fを使用
	//	{
	//		UnlockEnemy();
	//	}
	//}
}

std::shared_ptr<EnemyFox> MiniGameGameScene::GetClosestEnemy()
{
	VECTOR playerPos = m_player->GetPosition();

	auto closestEnemyIt = std::min_element(m_enemyFox.begin(), m_enemyFox.end(),
		[playerPos](const std::shared_ptr<EnemyFox>& a, const std::shared_ptr<EnemyFox>& b) {
			float distanceA = VSize(VSub(playerPos, a->GetPosition()));
			float distanceB = VSize(VSub(playerPos, b->GetPosition()));
			return distanceA < distanceB;
		});

	if (closestEnemyIt != m_enemyFox.end())
	{
		return *closestEnemyIt;
	}
	return nullptr;
}

void MiniGameGameScene::LockOnToEnemy(std::shared_ptr<EnemyFox> enemy)
{
	m_lockedOnEnemy = enemy;
	m_camera->SetLookOnTarget(enemy->GetPosition());
}

void MiniGameGameScene::UnlockEnemy()
{
	m_lockedOnEnemy = nullptr;
}

bool MiniGameGameScene::AreAllEnemiesDefeated()
{
	return std::all_of(m_enemyFox.begin(), m_enemyFox.end(), [](const std::shared_ptr<EnemyFox>& enemy) {
		return enemy->GetHP() <= 0;
		});
}

void MiniGameGameScene::DrawLoadinBar()
{
	float progress = GetLoadingProgress();
	int barWidth = 200;
	int barHeight = 20;
	int x = (640 - barWidth) / 2; // 画面中央に配置
	int y = 360; // 画面中央に配置

	DrawBox(x, y, x + barWidth, y + barHeight, GetColor(255, 255, 255), TRUE); // 白い枠
	DrawBox(x, y, x + static_cast<int>(barWidth * progress), y + barHeight, GetColor(0, 255, 0), TRUE); // 緑の進捗バー
}


float MiniGameGameScene::GetLoadingProgress()
{
	int totalResources = 4; // 仮に10個のリソースがあるとする
	int loadedResources = totalResources - GetASyncLoadNum();
	return static_cast<float>(loadedResources) / totalResources;
}

