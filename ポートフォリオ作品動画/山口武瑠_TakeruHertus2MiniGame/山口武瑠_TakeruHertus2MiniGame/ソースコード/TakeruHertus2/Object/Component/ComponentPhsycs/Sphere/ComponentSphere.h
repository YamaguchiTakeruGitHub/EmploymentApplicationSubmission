#pragma once
#include "../../Base/Component.h"

class ComponentSphere : public Component
{
public:
	void Init() override {};
	void Update() override {};
	void Draw() override {};
	void Final() override {};

	float radius;
};

