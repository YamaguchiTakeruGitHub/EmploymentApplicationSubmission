#include "EnemyManager.h"

EnemyManager::EnemyManager()
{
	for (int i = 0; i < EnemyManagerParameter::enemyFoxNum; i++)
	{
		m_enemyFox[i] = std::make_shared<EnemyFox>();
	}
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Init()
{
	for (int i = 0; i < EnemyManagerParameter::enemyFoxNum; i++)
	{
		m_enemyFox[i]->Init();
	}
}

void EnemyManager::Update()
{
	for (int i = 0; i < EnemyManagerParameter::enemyFoxNum; i++)
	{
		m_enemyFox[i]->Update();
	}
}

void EnemyManager::Draw()
{
	for (int i = 0; i < EnemyManagerParameter::enemyFoxNum; i++)
	{
		m_enemyFox[i]->Draw();
	}
}

void EnemyManager::Final()
{
	for (int i = 0; i < EnemyManagerParameter::enemyFoxNum; i++)
	{
		m_enemyFox[i]->Final();
	}
}

void EnemyManager::SetPosition(const VECTOR& _pos)
{
	for (int i = 0; i < EnemyManagerParameter::enemyFoxNum; i++)
	{
		m_enemyFox[i]->SetPosition(_pos);
	}
}

VECTOR EnemyManager::GetPosition() const
{
	for (int i = 0; i < EnemyManagerParameter::enemyFoxNum; i++)
	{
		return m_enemyFox[i]->GetPosition();
	}
}

void EnemyManager::SetTargetPosition(const VECTOR& _targetaPos)
{
	for (int i = 0; i < EnemyManagerParameter::enemyFoxNum; i++)
	{
		m_enemyFox[i]->SetTargetPosition(_targetaPos);
	}
}

float EnemyManager::GetCapsuleHeight() const
{
	for (int i = 0; i < EnemyManagerParameter::enemyFoxNum; i++)
	{
		return m_enemyFox[i]->GetCapsuleHeight();
	}
}

float EnemyManager::GetCapsuleRadius() const
{
	for (int i = 0; i < EnemyManagerParameter::enemyFoxNum; i++)
	{
		return m_enemyFox[i]->GetRadius();
	}
}

void EnemyManager::SetIsGround(const bool& _isGround)
{
	for (int i = 0; i < EnemyManagerParameter::enemyFoxNum; i++)
	{
		m_enemyFox[i]->SetIsGround(_isGround);
	}
}
