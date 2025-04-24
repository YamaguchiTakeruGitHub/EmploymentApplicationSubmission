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
	/*��x���ׂď���������*/
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
		m_isCombo = true;//�R���{��
		m_comboTimer += GAMECONSTANT::k_DELTA_TIME;
		if (m_comboTimer >= m_comboResetTime || //�R���{�t���[�����������Ԃɂ��������� 
			m_comboCount >= m_comboMaxCount + 1)	//�R���{�����ő�R���{���ɒB������
		{
			m_comboCount = 0;
			m_comboTimer = 0.0f;
		}
	}
	else
	{
		m_isCombo = false;//�R���{���ł͂Ȃ�
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
	m_comboOldCount = m_comboCount;//�O�̃R���{�����L�����Ă���
	m_comboCount++;
	m_comboTimer = 0.0f;
}
