#pragma once
#include "../../Base/Component.h"
#include "../../ComponentTransform/ComponentTransform.h"
#include "../../../../InputDevice/InputManager.h"

/// <summary>
/// �J�����̃p�����[�^�[
/// </summary>
namespace CAMERACONTROLPARAMETER
{
	static constexpr float ANGLE_SPEED			 = 0.8f;	//���񑬓x
	static constexpr float PLAYER_TARGET_HEIGHT  = 50.0f;	//�v���C���[��Y���W����ǂꂾ�������ʒu�𒍎��_�Ƃ��邩
	static constexpr float PLAYER_DISTANCE		 = 80.0f;  //�v���C���[�Ƃ̋���
}

/// <summary>
/// �����_�A�J�������x�A�����_����J�����܂ł̋������Ǘ�
/// </summary>
class ComponentCameraControl : public Component
{
private:
	std::shared_ptr<ComponentTransform> m_transform;//�ʒu�Ȃǂ������R���|�[�l���g
	std::shared_ptr<InputManager> m_Idm;			//���̓f�o�C�X

	VECTOR m_lookOnTarget;	//���b�N�I�����Ă���Ώ�
	VECTOR m_target;		//�J�����̒����_
	float m_sinParam;		//sin�p�����[�^
	float m_cosParam;		//cos�p�����[�^
	float m_horizontalAngle;//�����A���O��
	float m_verticalAngle;	//�����A���O��

	bool m_isLookOn;		//���b�N�I�������ǂ���


public:
	ComponentCameraControl(std::shared_ptr<ComponentTransform> _transform);

	void Init();
	void Update();
	void Draw();
	void Final();
private:
	void Update_LookOnSystem();


public:
	/*===============================================================*/
	//�Z�b�^�[�ƃQ�b�^�[
	/*===============================================================*/

	//�|�W�V����
	void SetPosition(const VECTOR& _pos) { m_transform->position = _pos; }
	VECTOR GetPositin() const { return m_transform->position; }

	/*���b�N�I�����Ă���Ώۂ̃f�[�^*/
	void SetLookOnTarget(const VECTOR& _lookOnTarget) { m_lookOnTarget = _lookOnTarget; }
	VECTOR GetLookOnTarget() const { return m_lookOnTarget; }

	/*�����_�̃f�[�^*/
	void SetTarget(const VECTOR& _target) { m_target = _target; }
	VECTOR GetTarget() const { return m_target; }

	/*Sin�p�����[�^�̃f�[�^*/
	void SetSinParam(const float& _sinParam) { m_sinParam = _sinParam; }
	float GetSinParam() const { return m_sinParam; }

	/*Cos�p�����[�^�̃f�[�^*/
	void SetCosParam(const float& _cosParam) { m_cosParam = _cosParam; }
	float GetCosParam() const { return m_cosParam; }

	/*�����A���O���̃f�[�^*/
	void SetHAngle(const float& _hAngle) { m_horizontalAngle = _hAngle; }
	float GetHAngle() const { return m_horizontalAngle; }

	/*�����A���O���̃f�[�^*/
	void SetVAngle(const float& _vAngle) { m_verticalAngle = _vAngle; }
	float GetVAngle() const { return m_verticalAngle; }


	/*���b�N�I�����Ă��邩�ǂ���*/
	void SetIsLookOn(const bool& _isLookOn) { m_isLookOn = _isLookOn; }
	bool GetIsLookOn() const { return m_isLookOn; }

};

