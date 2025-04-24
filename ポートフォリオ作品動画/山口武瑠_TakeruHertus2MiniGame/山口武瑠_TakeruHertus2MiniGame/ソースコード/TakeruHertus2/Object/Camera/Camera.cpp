#include "Camera.h"
#include "../GameTag.h"

Camera::Camera()
{
	AddComponent<ComponentTransform>();
	m_transform = GetComponent<ComponentTransform>();

	AddComponent<ComponentCameraControl>(m_transform);
	m_cameraControl = GetComponent<ComponentCameraControl>();

}

void Camera::Init()
{
	Entity::InitComponent();
	
	SetCameraNearFar(2.0f, 6000.0f);
}

void Camera::Update()
{
	Effekseer_Sync3DSetting();
	if (m_tag == TagCameraObject::CONTROL)
	{
		m_cameraControl->SetTarget(m_target);
		m_cameraControl->Update();
	}



	if (m_cameraControl->GetIsLookOn() == true)
	{

		// �����_�̓G�l�~�[�̍��W�ɂ��܂��B
		m_target = m_lookOnTarget;
		// �G�l�~�[����v���C���[�ɐL�т�x�N�g�������߂܂��B
		VECTOR pos = VSub(m_playerPosition, m_lookOnTarget);
		// �J�����̍����͈��ɂ������̂ŁAy������0�ɂ��܂��B
		pos.y = 0.0f;
		// �x�N�g���𐳋K�����܂��B
		pos = VNorm(pos);
		// �X�J���[���|���܂�
		pos = VScale(pos, 50.0f);
		// �J�������ǂꂾ���v���C���[�̍��W��荂������ݒ肵�܂��B
		pos.y = 50.0f;
		// �v���C���[�̍��W�ɋ��߂��x�N�g���𑫂��āA�J�����̍��W�Ƃ��܂��B
		m_transform->position = VAdd(m_playerPosition, pos);

		SetCameraPositionAndTarget_UpVecY(m_transform->position, m_target);
	}
	else
	{
		SetCameraPositionAndTarget_UpVecY(m_transform->position, m_target);
	}


}

void Camera::Draw()
{
	Entity::DrawComponent();
}

void Camera::Final()
{
	Entity::FinalComponent();
}
