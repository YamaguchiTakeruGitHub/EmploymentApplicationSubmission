#pragma once
#include "../../Base/Component.h"
#include "../../ComponentTransform/ComponentTransform.h"
#include "../../ComponentPhsycs/RightBody/ComponentRightBody.h"
#include "../../ComponentPhsycs/Capsule/ComponentCapsule.h"
#include "../../ComponentPhsycs/Sphere/ComponentSphere.h"
#include "../PhsycsShapeType.h"//形状のタイプ


class ComponentPhsycs : public Component
{
private:
	std::shared_ptr<ComponentTransform> m_transform;
	std::shared_ptr<ComponentRightBody> m_rightbody;
	std::shared_ptr<ComponentCapsule> m_capsule;


public:
	ComponentPhsycs(std::shared_ptr<ComponentTransform> _transform, std::shared_ptr<ComponentRightBody> _rightBody);
	
	void Init() override;
	void Update() override;
	void Draw() override;
	void Final() override;

};

