#pragma once
#include "../EnemyFox/EnemyFox.h"

namespace EnemyManagerParameter
{
	static constexpr int enemyFoxNum = 10;
}

class EnemyManager
{
private:
	std::shared_ptr<EnemyFox> m_enemyFox[EnemyManagerParameter::enemyFoxNum];

public:
	EnemyManager();
	~EnemyManager();

	void Init();
	void Update();
	void Draw();
	void Final();

	void SetPosition(const VECTOR& _pos);
	VECTOR GetPosition() const;

	void SetTargetPosition(const VECTOR& _targetaPos);

	float GetCapsuleHeight() const;

	float GetCapsuleRadius() const;

	void SetIsGround(const bool& _isGround);
};

