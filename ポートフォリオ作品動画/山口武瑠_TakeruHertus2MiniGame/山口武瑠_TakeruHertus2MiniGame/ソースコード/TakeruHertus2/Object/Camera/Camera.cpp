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

		// 注視点はエネミーの座標にします。
		m_target = m_lookOnTarget;
		// エネミーからプレイヤーに伸びるベクトルを求めます。
		VECTOR pos = VSub(m_playerPosition, m_lookOnTarget);
		// カメラの高さは一定にしたいので、y成分を0にします。
		pos.y = 0.0f;
		// ベクトルを正規化します。
		pos = VNorm(pos);
		// スカラーを掛けます
		pos = VScale(pos, 50.0f);
		// カメラがどれだけプレイヤーの座標より高いかを設定します。
		pos.y = 50.0f;
		// プレイヤーの座標に求めたベクトルを足して、カメラの座標とします。
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
