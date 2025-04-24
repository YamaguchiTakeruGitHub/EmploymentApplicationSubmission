#include "ComponentComboSystem.h"
#include "../../../Application/GameConstant.h"

ComponentComboSystem::ComponentComboSystem()
	: m_comboTimer		(0.0f)
	, m_comboResetTime	(0.0f)
	, m_comboCount		(0)
	, m_comboOldCount	(0)
	, m_isCombo			(false)
{
}

void ComponentComboSystem::Init()
{
	/*一度すべて初期化する*/
	m_comboTimer	 = 0.0f;
	m_comboResetTime = 0.0f;
	m_comboCount	 = 0;
	m_comboOldCount  = 0;
	m_isCombo		 = false;
}

void ComponentComboSystem::Update()
{
	if (m_comboCount > 0)
	{
		m_isCombo = true;//コンボ中
		m_comboTimer += GAMECONSTANT::k_DELTA_TIME;
		if (m_comboTimer >= m_comboResetTime || //コンボフレームが制限時間にたっしたら 
			m_comboCount >= m_comboMaxCount + 1)	//コンボ数が最大コンボ数に達したら
		{
			m_comboCount = 0;
			m_comboTimer = 0.0f;
		}
	}
	else
	{
		m_isCombo = false;//コンボ中ではない
	}


}

void ComponentComboSystem::Draw()
{
}

void ComponentComboSystem::Final()
{
}

void ComponentComboSystem::IncrementCombo()
{
	m_comboOldCount = m_comboCount;//前のコンボ数を記憶しておく
	m_comboCount++;
	m_comboTimer = 0.0f;
}
