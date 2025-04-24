#pragma once
#include "../Base/Component.h"

/// <summary>
/// コンボシステムを扱うコンポーネント：初期化を行う際は総括初期化のあとにセッターにて設定
/// </summary>
class ComponentComboSystem : public Component
{
private:
	//コンボ中の経過時間
	float m_comboTimer;
	//コンボをリセットする時間
	float m_comboResetTime;
	//コンボのカウント
	int m_comboCount;
	//前のコンボカウント
	int m_comboOldCount;

	//最大コンボ数
	int m_comboMaxCount;
	//現在コンボ中かどうか
	bool m_isCombo;


public:
	ComponentComboSystem();


	void Init() override;
	void Update() override;
	void Draw() override;
	void Final() override;

	void IncrementCombo();

//======================================================================
// セッターゲッター
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

