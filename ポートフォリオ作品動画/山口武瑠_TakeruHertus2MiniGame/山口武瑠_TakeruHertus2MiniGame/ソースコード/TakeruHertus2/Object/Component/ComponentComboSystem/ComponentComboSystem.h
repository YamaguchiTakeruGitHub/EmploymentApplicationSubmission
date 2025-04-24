#pragma once
#include "../Base/Component.h"

/// <summary>
/// �R���{�V�X�e���������R���|�[�l���g�F���������s���ۂ͑����������̂��ƂɃZ�b�^�[�ɂĐݒ�
/// </summary>
class ComponentComboSystem : public Component
{
private:
	//�R���{���̌o�ߎ���
	float m_comboTimer;
	//�R���{�����Z�b�g���鎞��
	float m_comboResetTime;
	//�R���{�̃J�E���g
	int m_comboCount;
	//�O�̃R���{�J�E���g
	int m_comboOldCount;

	//�ő�R���{��
	int m_comboMaxCount;
	//���݃R���{�����ǂ���
	bool m_isCombo;


public:
	ComponentComboSystem();


	void Init() override;
	void Update() override;
	void Draw() override;
	void Final() override;

	void IncrementCombo();

//======================================================================
// �Z�b�^�[�Q�b�^�[
//======================================================================
	void SetComboTimer(const float& _comboTimer) { m_comboTimer = _comboTimer; }
	float GetComboTimer() const { return m_comboTimer; }

	void SetComboResetTime(const float& _comboResetTime) { m_comboResetTime = _comboResetTime; }
	float GetComboResetTime() const { return m_comboResetTime; }

	void SetComboCount(const int& _comboCount) { m_comboCount = _comboCount; }
	int GetComboCount() const { return m_comboCount; }

	void SetComboOldCount(const int& _comboOldCount) { m_comboOldCount = _comboOldCount; }
	int GetComboOldCount() const { return m_comboOldCount; }

	void SetComboMaxCount(const int& _comboMaxCount) { m_comboMaxCount = _comboMaxCount; }
	int GetComboMaxCount() const { return m_comboMaxCount; }

	void SetIsCombo(const bool& _isCombo) { m_isCombo = _isCombo; }
	bool GetIsCombo() const { return m_isCombo; }

};

