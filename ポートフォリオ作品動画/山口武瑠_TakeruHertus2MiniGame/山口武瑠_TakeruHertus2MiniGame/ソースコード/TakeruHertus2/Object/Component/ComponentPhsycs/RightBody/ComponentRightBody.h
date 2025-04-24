#pragma once
#include "../../Base/Component.h"

class ComponentRightBody : public Component
{
public:
	void Init() override {};
	void Update() override {};
	void Draw() override {};
	void Final() override {};

	VECTOR direction;
	VECTOR velocity;
	float speed;

};

