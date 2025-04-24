#pragma once
#include "../../Base/Component.h"
#include "../../ComponentTransform/ComponentTransform.h"

/// <summary>
/// カプセルの構造体（足元を座標とした場合の処理に対応）
/// </summary>
class ComponentCapsule : public Component
{
private:
	std::shared_ptr<ComponentTransform> m_transform;

public:
	ComponentCapsule(std::shared_ptr<ComponentTransform> _transform);
	void Init() override {};
	void Update() override {};
	void Draw() override;
	void Final() override {};

	float radius;			//半径
	float height;			//ポジションからの高さ
};

