#pragma once
#include "../Base/EnemyBase.h"


class EnemyFox : public EnemyBase
{
private:
	/*コンポーネントの宣言*/
	std::shared_ptr<ComponentTransform> m_transform;
	std::shared_ptr<ComponentRightBody> m_rightbody;
	std::shared_ptr<ComponentAnimation> m_animation;
	std::shared_ptr<ComponentCapsule> m_capsule;
	std::shared_ptr<ComponentModel> m_model;
	std::shared_ptr<ComponentStatus> m_status;


	/*関数＆変数宣言*/

	/// <summary>
	/// 敵の状態
	/// </summary>
	enum class EnemyState
	{
		Idel,	//とどまる
		Chase,	//追跡
		Attack,	//攻撃
		Retreat,//帰還
		Falling,//落下
		Deth,	//お亡くなり
	}m_state;//インスタンス簡易宣言

	//ねらう座標
	VECTOR m_targetPostion;

	//追跡判定距離
	float m_chaseDistance;

	//攻撃判定距離
	float m_attackDistance;

	//ファイルのパス
	std::string filename;

	//ファイルのデータ
	std::vector<std::vector<std::string>> Data;

	//移動の更新
	void UpdateMove(VECTOR& _targetPos);
	
	//状態の更新
	void UpdateState();
	
	bool m_isGround = false;

	//志望通知
	void CheckDeath();

public:
	EnemyFox();
	~EnemyFox() override;

	void Init();
	void Update();
	void Draw();
	void Final();

	//======================================================================
	// セッターゲッター
	//======================================================================
	//座標
	void SetPosition(const VECTOR& _pos) { m_transform->position = _pos; }
	VECTOR GetPosition() const { return m_transform->position; }

	//狙いを定めているターゲット
	void SetTargetPosition(const VECTOR& _targetPos) { m_targetPostion = _targetPos; }
	VECTOR GetTargetPosition() const { return m_targetPostion; }

	//カプセルの高さ
	float GetCapsuleHeight() const { return m_capsule->height; }

	//カプセルの半径
	void SetRadius(const float& _radius) { m_capsule->radius = _radius; }
	float GetRadius() const { return m_capsule->radius; }

	//地面についているか
	void SetIsGround(const bool& _isGround) { m_isGround = _isGround; }
	bool GetIsGround() const { return m_isGround; }

	/*ステータス関連*/
	void SetHp(const int& _hp) { m_status->SetHp(_hp); }
	int GetHP() const { return m_status->GetHp(); }

	int GetAttackValue() const { return m_status->GetAttackValue(); }

	void SetIsTakeDamage(const int& _damage) { m_status->IsTakeDamage(_damage); }

};

