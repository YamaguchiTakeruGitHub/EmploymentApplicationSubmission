#include "ComponentCapsule.h"

ComponentCapsule::ComponentCapsule(std::shared_ptr<ComponentTransform> _transform)
	: m_transform(_transform)
{
}

void ComponentCapsule::Draw()
{
#ifdef _DEBUG

	VECTOR pos = m_transform->position;
//	DrawCapsule3D(VGet(pos.x, pos.y + height, pos.z), VGet(pos.x, pos.y + radius, pos.z), radius, 5, 0xff0000, 0xff0000, false);
#endif // _DEBUG

}
