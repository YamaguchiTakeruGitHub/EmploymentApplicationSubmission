#pragma once
#include "../Entity/Entity.h"
#include "../../Object/Character/Player/Player.h"
#include "../../Object/Map/MiniGame_1Map/MiniGame_1Map.h"
#include "../../MathLib/MathLib.h"
#include "../../Object/Character/Enemy/EnemyFox/EnemyFox.h"

class Physycs : public Entity
{
private:
	std::shared_ptr<MathLib> m_mathLib;

	std::shared_ptr<Player> m_player;
	std::shared_ptr<MiniGame_1Map> m_miniGame_Map1;
	std::vector<std::shared_ptr<EnemyFox>> m_enemyFoxs;

	MV1_COLL_RESULT_POLY_DIM m_hitDim{};
	bool m_isGround = false;
	bool m_isWall = false;

	bool m_isEnemyGround[3];
	bool m_isEnmeyWall[3];

public:
	Physycs(std::shared_ptr<Player> _player, std::shared_ptr<MiniGame_1Map> _miniGame_Map1, const std::vector<std::shared_ptr<EnemyFox>>& enemies);
	~Physycs() {};

	void Init();
	void Update();
	//void Draw();
	//void Final();

	void PolygonHitCapsule(bool& _isGround, bool& _isWall, VECTOR& _resolvePos, float _capsuleHeight, float _capsuleRadius, int _polygonHandle);

private:
	void Update_Player();
	void Update_enemyFoxs();
	//ìGìØém
	void CheckEnemyCollisions();
	//ìGÇ∆ÉvÉåÉCÉÑÅ[
	void CheckPlayerEnemyCollisions();
};

