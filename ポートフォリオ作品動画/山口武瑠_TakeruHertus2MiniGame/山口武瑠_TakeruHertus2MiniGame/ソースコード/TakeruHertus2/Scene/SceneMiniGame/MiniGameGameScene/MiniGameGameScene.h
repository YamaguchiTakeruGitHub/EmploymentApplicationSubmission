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

	std::vector<std::shared_ptr<EnemyFox>> m_enemyFox; // std::vector�ɕύX
	std::shared_ptr<EnemyFox> m_lockedOnEnemy;//���݃��b�N�I�����Ă���G

	std::shared_ptr<Physycs> m_physycs;

	std::shared_ptr<InputManager> m_Idm;

	int LightHandle[3];

	bool m_isLoading;//���[�h�����ǂ���

private:
	/*�ʂ̃V�[���Ŏ������Ă������߂�������͉��u��*/
	bool m_isGameOver;
	bool m_isGameClear;

	int m_GameOverGraphHandle;
	int m_GameClearGraphHandle;

	int m_pushRunTime;
	/*�ʂ̃V�[���Ŏ������Ă������߂�������͉��u��*/


public:
	MiniGameGameScene();
	~MiniGameGameScene();

	void Init() override;
	void Update() override;
	void Draw() override;
	void Final() override;

private:
	void UpdateRun();//�{����
	void DrawRun();//�{�`��

	void PlayerControlCamera();//�v���C���[���J����������s��

	void Update_LockOnCamera();//���b�N�I���̂�������@

	std::shared_ptr<EnemyFox> GetClosestEnemy();//��ԃv���C���[����߂��G
	void LockOnToEnemy(std::shared_ptr<EnemyFox> enemy);//�G�̃��b�N�I��
	void UnlockEnemy();//���b�N�I������

	bool AreAllEnemiesDefeated();//�G�����ׂē|���ꂽ���ǂ���

private:
	void DrawLoadinBar();
	float GetLoadingProgress();

	VECTOR WorldToScreen(const VECTOR& worldPos)
	{
		// 3D���W��2D�X�N���[�����W�ɕϊ�
		return ConvWorldPosToScreenPos(worldPos);
	}
};

