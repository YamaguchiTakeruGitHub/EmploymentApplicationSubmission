#include "Entity.h"

void Entity::InitComponent()
{
	for (auto& pair : components)
	{
		auto& component = pair.second;
		component->Init();
	}
}

void Entity::UpdateComponent()
{
	for (auto& pair : components)
	{
		auto& component = pair.second;
		component->Update();
	}
}

void Entity::DrawComponent()
{
	for (auto& pair : components)
	{
		auto& component = pair.second;
		component->Draw();
	}
}

void Entity::FinalComponent()
{
	for (auto& pair : components)
	{
		auto& component = pair.second;
		component->Final();
	}
}
