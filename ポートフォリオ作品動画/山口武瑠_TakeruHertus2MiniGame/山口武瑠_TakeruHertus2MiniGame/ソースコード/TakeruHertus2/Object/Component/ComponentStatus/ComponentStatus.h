#pragma once
#include "../Base/Component.h"

/// <summary>
/// �X�e�[�^�X�������\����
/// </summary>
class ComponentStatus : public Component
{
private:
	/*��{�X�e�[�^�X*/
	int level;
	int exp, nextExp;

	/*���ʃX�e�[�^�X�i�G�A�v���C���[�A�����j*/
	int attack;
	int defense;
	
	float hp, maxHp;
	float mp, maxMp;
	
	/*�ُ���*/

public:
	ComponentStatus();

	void Init() override;
	void Update() override;
	void Draw() override;
	void Final() override;

	/*�X�e�[�^�X�X�V�����̕⏕�֐�*/

	void AddExp(int _value);	//�o���l�����Z���A���x���A�b�v�������s��
	void LevelUp();				//���x���A�b�v����
	void IsTakeDamage(int _dmg);//�_���[�W�v�Z�t���O
	void Heal(int _amount);		//�񕜏���

	//======================================================================
	// �Z�b�^�[�Q�b�^�[
	//======================================================================
	
	/*���x��*/
	void SetLevel(const int& _level) { level = _level; }
	int GetLevel() const { return level; }

	/*���݂̌o���l*/
	void SetExp(const int& _exp) { exp = _exp; }
	int GetExp() const { return exp; }

	/*���̌o���l*/
	void SetNextExp(const int& _nextExp) { nextExp = _nextExp; }
	int GetNextExp() const { return nextExp; }

	/*�U����*/
	void SetAttackValue(const int& _attackValue) { attack = _attackValue; }
	int GetAttackValue() const { return attack; }

	/*�h���*/
	void SetDefenceValue(const int& _defenceValue) { defense = _defenceValue; }
	int GetDefenceValue() const { return defense; }

	/*�̗�*/
	void SetHp(const float& _hp) { hp = _hp; }
	float GetHp() const { return hp; }

	/*�ő�̗�*/
	void SetMaxHp(const float& _maxHp) { maxHp = _maxHp; }
	float GetMaxHp() const { return maxHp; }

	/*����*/
	void SetMp(const float& _mp) { mp = _mp; }
	float GetMp() const { return mp; }

	/*�ő喂��*/
	void SetMaxMp(const float& _maxMp) { maxMp = _maxMp; }//�ő�MP�̃Z�b�g
	float GetMaxMp() const { return maxMp; }//�ő�MP�̃Q�b�g


};

