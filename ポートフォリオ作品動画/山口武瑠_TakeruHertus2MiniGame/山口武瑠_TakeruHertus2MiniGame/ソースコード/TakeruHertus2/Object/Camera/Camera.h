#pragma once
#include "../Entity/Entity.h"

class Camera : public Entity
{
private:
	std::shared_ptr<ComponentTransform> m_transform;		//移動などのコンポーネント
	std::shared_ptr<ComponentCameraControl> m_cameraControl;//カメラのコントロール

	VECTOR m_lookOnTarget;
	VECTOR m_playerPosition;

	VECTOR m_target;
	std::string m_tag;

public:
	Camera();

	void Init();
	void Update();
	void Draw(); 
	void Final();

	/*===============================================================*/
	//セッターとゲッター
	/*===============================================================*/

	void SetTag(std::string _tag) { m_tag = _tag; }
	std::string GetTag() const { return m_tag; }

	void SetPlayerPosition(const VECTOR& _ppos) { m_playerPosition = _ppos; }
	VECTOR GetPlayerPosition()const { return m_playerPosition; }

	void SetPosition(const VECTOR& _pos) { m_transform->position; }
	VECTOR GetPosition() const { return m_transform->position; }

	void SetLookOnTarget(const VECTOR& _lookOnTarget) { m_lookOnTarget = _lookOnTarget; }
	VECTOR GetLookOnTarget() const { return m_lookOnTarget; }

	void SetTarget(const VECTOR& _target) { m_target = _target; }
	VECTOR GetTarget() const { return m_target; }

	void SetHAngle(const float& _hAngle) { m_cameraControl->SetHAngle(_hAngle); }
	float GetHAngle() const { return m_cameraControl->GetHAngle(); }

	void SetCosParam(const float& _cosParam) { m_cameraControl->SetCosParam(_cosParam); }
	float GetCosParam() const { return m_cameraControl->GetCosParam(); }

	void SetSinParam(const float& _sinParam) { m_cameraControl->SetSinParam(_sinParam); }
	float GetSinParam() const { return m_cameraControl->GetSinParam(); }


};

