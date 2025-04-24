#include "MiniGameGameScene.h"
#include "../../Manager/SceneManager.h"
#include <limits>
#include <algorithm>

MiniGameGameScene::MiniGameGameScene()
	: LightHandle{-1,-1, -1}
	, m_isLoading(true)

	/*��start*/
	, m_isGameOver(false)
	, m_isGameClear(false)
	, m_GameOverGraphHandle(-1)
	, m_GameClearGraphHandle(-1)
	, m_pushRunTime(0)
	/*��end*/
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

	// �f�B���N�V���i�����C�g�̐ݒ�
	LightHandle[0] = CreateDirLightHandle(VGet(0.0f, -1.0f, 0.0f)); // ��������

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

	/*��start*/
	m_isGameClear = false;
	m_isGameOver = false;

	m_GameClearGraphHandle = LoadGraph("../Data/Asset/2D/MiniGame/TitleScene/MiniGameGameClear.png");
	m_GameOverGraphHandle = LoadGraph("../Data/Asset/2D/MiniGame/TitleScene/MiniGameGameOverBackGround.png");
	
	m_pushRunTime = 0;
	/*��end*/
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

		/*��start*/
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
				Effkseer_End();			//�G�ӂ��������̉��
				DxLib_End();			//DxLib�̉��
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
		/*��end*/

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
		/*��start*/
		if (m_isGameOver == true)
		{
			DrawGraph(0, 0, m_GameOverGraphHandle, true);
		}

		if (m_isGameClear == true)
		{
			DrawGraph(0, 0, m_GameClearGraphHandle, true);
		}
		/*��end*/


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

	/*��start*/
	DeleteGraph(m_GameClearGraphHandle);
	DeleteGraph(m_GameOverGraphHandle);
	/*��end*/


}

void MiniGameGameScene::UpdateRun()
{
	m_command->Update();
	m_player->SetIsAttackCheck(m_command->GetIsAttack());//�U���R�}���h���������Ă��邩

	/*�U������*/
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

	// �v���C���[��Y���W��-300�ȉ��ɂȂ�����HP��0�ɂ���
	if (m_player->GetPosition().y < -300)
	{
		m_player->SetHP(0);

	}

	// �G��Y���W��-300�ȉ��ɂȂ�����HP��0�ɂ���
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

	//�G�����ׂē|���ꂽ�����m�F
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
		// �G�̓����HP�o�[��\��
		VECTOR enemyPos = m_enemyFox[i]->GetPosition();
		enemyPos.y += 20; // ����ɕ\�����邽�߂�Y���W�𒲐�
		VECTOR screenPos = WorldToScreen(enemyPos);

		int hp = m_enemyFox[i]->GetHP();
		int maxHp = 100; // �ő�HP������
		int barWidth = 50;
		int barHeight = 5;
		int barX = static_cast<int>(screenPos.x) - barWidth / 2;
		int barY = static_cast<int>(screenPos.y) - barHeight / 2;

		// HP�o�[�̔w�i
		DrawBox(barX, barY, barX + barWidth, barY + barHeight, GetColor(255, 0, 0), TRUE);
		// HP�o�[�̑O�i
		DrawBox(barX, barY, barX + static_cast<int>(barWidth * (hp / static_cast<float>(maxHp))), barY + barHeight, GetColor(0, 255, 0), TRUE);
	}
	m_command->Draw();

#ifdef _DEBUG
	//DrawString(0, 0, "MiniGame_GameScene", 0xffffff);

	// �c��̓G�̐���\��
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
	/*�J�����̊p�x���l���������W�ɕϊ�*/
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
	//// ���b�N�I�����łȂ��ꍇ�̂݁A�v���C���[�����ԋ߂��G�����b�N�I��
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
	//	// ���b�N�I�����̓G�����݂���ꍇ�A���̓G�̈ʒu���J�����ɐݒ�
	//	m_camera->SetLookOnTarget(m_lockedOnEnemy->GetPosition());

	//	// ���b�N�I�����̓G����苗���ȏ㗣�ꂽ�ꍇ�A���b�N�I��������
	//	float distance = VSize(VSub(m_player->GetPosition(), m_lockedOnEnemy->GetPosition()));
	//	if (distance > 200.0f) // ��Ƃ���200.0f���g�p
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
	int x = (640 - barWidth) / 2; // ��ʒ����ɔz�u
	int y = 360; // ��ʒ����ɔz�u

	DrawBox(x, y, x + barWidth, y + barHeight, GetColor(255, 255, 255), TRUE); // �����g
	DrawBox(x, y, x + static_cast<int>(barWidth * progress), y + barHeight, GetColor(0, 255, 0), TRUE); // �΂̐i���o�[
}


float MiniGameGameScene::GetLoadingProgress()
{
	int totalResources = 4; // ����10�̃��\�[�X������Ƃ���
	int loadedResources = totalResources - GetASyncLoadNum();
	return static_cast<float>(loadedResources) / totalResources;
}

