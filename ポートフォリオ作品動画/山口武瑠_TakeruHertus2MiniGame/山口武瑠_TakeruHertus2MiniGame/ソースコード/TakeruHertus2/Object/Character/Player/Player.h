#pragma once
#include "../../Entity/Entity.h"

/// <summary>
/// �v���C���[
/// </summary>
class Player : public Entity
{
private:
	/*�C���X�^���X�錾�F�R���|�[�l���g*/
	std::shared_ptr<ComponentTransform> m_transform;
	std::shared_ptr<ComponentRightBody> m_rightbody;
	std::shared_ptr<ComponentMovement> m_movement;
	std::shared_ptr<ComponentModel> m_model;
	std::shared_ptr<ComponentCapsule> m_capsule;
	std::shared_ptr<ComponentAnimation> m_animation;
	std::shared_ptr<ComponentComboSystem> m_comboSystem;//�R���{�V�X�e��

	std::shared_ptr<ComponentStatus> m_status;//�X�e�[�^�X
	/*�C���X�^���X�錾*/


	/*�ϐ����֐��錾*/
	std::string filename;//�t�@�C���̃p�X
	std::vector<std::vector<std::string>> Data;//�t�@�C���̃f�[�^

	/// <summary>
	/// �R���{�n�̏���
	/// </summary>
	void UpdateCombo();

	/// <summary>
	/// �A�j���[�V�����̍X�V
	/// </summary>
	void UpdateAnimation();

	/// <summary>
	/// �s�������̍X�V
	/// </summary>
	void UpdateMomvement();


	/// <summary>
	/// �v���C���[�̏��
	/// </summary>
	enum class PlayerState
	{
		Idel,			//�Ƃǂ܂�
		Move,			//�ړ�
		Attack,			//�U��
		Falling,		//����
		GroundAttack,	//�n��U��
		AirAttack		//�󒆍U��
	}m_state;//�C���X�^���X�ȈՐ錾

	void UpdateState();

	//�R�}���h�֘A
	bool m_isAttackCheck;
	/*bool m_isMagicCheck;
	bool m_isItemCheck;
	bool m_isMenuCheck;*/


	/*�U���͈�*/
	VECTOR m_AttackPosition;
	float m_AttackRadius;

public:
	Player();
	~Player();

	void Init();
	void Update();
	void Draw();
	void Final();

	//======================================================================
	// �Z�b�^�[�Q�b�^�[
	//======================================================================
	//�|�W�V����
	void SetPosition(const VECTOR& _pos) { m_transform->position = _pos; }
	VECTOR GetPosition() const { return m_transform->position; }

	//���F���V�e�B
	void SetVelocity(const VECTOR& _velocity) { m_rightbody->velocity = _velocity; }
	VECTOR GetVelocity() const { return m_rightbody->velocity; }

	//�J�v�Z���̍���
	float GetCapsuleHeight() const { return m_capsule->height; }

	//�J�v�Z���̔��a
	void SetRadius(const float& _radius) { m_capsule->radius = _radius; }
	float GetRadius() const { return m_capsule->radius; }


	/*�U���͈�*/
	VECTOR GetAttackPosition() const { return m_AttackPosition; }
	float GetAttackRadius() const { return m_AttackRadius; }



	/*�X�e�[�^�X�֘A*/
	void SetHP(const int& _hp) { m_status->SetHp(_hp); }
	int GetHp() const { return m_status->GetHp(); }

	int GetAttackValue() const { return m_status->GetAttackValue(); }



	/*�R�}���h�`�F�b�N*/
	//�U���R�}���h���������Ă��邩���Z�b�g����
	void SetIsAttackCheck(const bool& _isAttackCheck) { m_isAttackCheck = _isAttackCheck; }

	/*Movement�n*/
	
	//�ړ�����
	void SetIsMove(const bool& _isMove) { m_movement->SetIsMove(_isMove); }
	bool GetIsMove() const { return m_movement->GetIsMove(); }

	//�W�����v����
	void SetIsJump(const bool& _isJump) { m_movement->SetIsJump(_isJump); }
	bool GetIsJump() const { return m_movement->GetIsJump(); }

	//�W�����v��
	float GetJumpPower() const { return m_movement->GetJumpPower(); }

	//�n�ʂɂ��Ă邩
	void SetIsGround(const bool& _isGround) { m_movement->SetIsGround(_isGround); }
	bool GetIsGround() const { return m_movement->GetIsGround(); }

	//�d��
	void SetGravity(const float& _gravity) { m_movement->SetGravity(_gravity); }
	float GetGravity() const { return m_movement->GetGravity(); }


	/*�J�����̌������l���������W�̕ϊ��p�Z�b�g�֐�*/
	void SetConversionHorizontalAngle(const float _cHAngle) { m_movement->SetConversionCameraHAngle(_cHAngle); }
	void SetConversionCosParam(const float _cCosParam) { m_movement->SetConversionCosParam(_cCosParam); }
	void SetConversionSinParam(const float _cSinParam) { m_movement->SetConversionSinParam(_cSinParam); }

};

