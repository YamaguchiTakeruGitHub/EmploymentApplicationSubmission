#include "MiniGame_1Map.h"

MiniGame_1Map::MiniGame_1Map()
{
	AddComponent<ComponentTransform>();
	m_transform = GetComponent<ComponentTransform>();

	AddComponent<ComponentModel>();
	m_model = GetComponent<ComponentModel>();
}

MiniGame_1Map::~MiniGame_1Map()
{
}

void MiniGame_1Map::Init()
{
	Entity::InitComponent();

	m_transform->position = VGet(0, 0, 0);

	m_model->LoadModel("../Data/Asset/3D/Map/MiniGameMap1/MiniGameMap1.mv1");

}

void MiniGame_1Map::Update()
{
	Entity::UpdateComponent();

	MV1SetPosition(m_model->m_modelHandle, m_transform->position);
}

void MiniGame_1Map::Draw()
{
	Entity::DrawComponent();
}

void MiniGame_1Map::Final()
{
	Entity::FinalComponent();
}
