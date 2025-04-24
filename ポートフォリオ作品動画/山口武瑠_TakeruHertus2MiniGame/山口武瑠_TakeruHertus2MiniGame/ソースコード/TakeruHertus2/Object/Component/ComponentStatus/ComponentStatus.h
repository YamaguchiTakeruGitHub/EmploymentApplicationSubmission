#pragma once
#include "../Base/Component.h"

/// <summary>
/// ステータスを扱う構造体
/// </summary>
class ComponentStatus : public Component
{
private:
	/*基本ステータス*/
	int level;
	int exp, nextExp;

	/*共通ステータス（敵、プレイヤー、味方）*/
	int attack;
	int defense;
	
	float hp, maxHp;
	float mp, maxMp;
	
	/*異常状態*/

public:
	ComponentStatus();

	void Init() override;
	void Update() override;
	void Draw() override;
	void Final() override;

	/*ステータス更新処理の補助関数*/

	void AddExp(int _value);	//経験値を加算し、レベルアップ処理を行う
	void LevelUp();				//レベルアップ処理
	void IsTakeDamage(int _dmg);//ダメージ計算フラグ
	void Heal(int _amount);		//回復処理

	//======================================================================
	// セッターゲッター
	//======================================================================
	
	/*レベル*/
	void SetLevel(const int& _level) { level = _level; }
	int GetLevel() const { return level; }

	/*現在の経験値*/
	void SetExp(const int& _exp) { exp = _exp; }
	int GetExp() const { return exp; }

	/*次の経験値*/
	void SetNextExp(const int& _nextExp) { nextExp = _nextExp; }
	int GetNextExp() const { return nextExp; }

	/*攻撃力*/
	void SetAttackValue(const int& _attackValue) { attack = _attackValue; }
	int GetAttackValue() const { return attack; }

	/*防御力*/
	void SetDefenceValue(const int& _defenceValue) { defense = _defenceValue; }
	int GetDefenceValue() const { return defense; }

	/*体力*/
	void SetHp(const float& _hp) { hp = _hp; }
	float GetHp() const { return hp; }

	/*最大体力*/
	void SetMaxHp(const float& _maxHp) { maxHp = _maxHp; }
	float GetMaxHp() const { return maxHp; }

	/*魔力*/
	void SetMp(const float& _mp) { mp = _mp; }
	float GetMp() const { return mp; }

	/*最大魔力*/
	void SetMaxMp(const float& _maxMp) { maxMp = _maxMp; }//最大MPのセット
	float GetMaxMp() const { return maxMp; }//最大MPのゲット


};

