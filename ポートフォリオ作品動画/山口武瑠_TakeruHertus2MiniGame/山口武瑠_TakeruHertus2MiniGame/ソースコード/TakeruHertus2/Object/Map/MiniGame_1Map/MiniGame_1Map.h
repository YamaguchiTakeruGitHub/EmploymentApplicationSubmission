#pragma once
#include "../../Entity/Entity.h"

class MiniGame_1Map : public Entity
{
private:
	std::shared_ptr<ComponentModel> m_model;
	std::shared_ptr<ComponentTransform> m_transform;



public:
	MiniGame_1Map();
	~MiniGame_1Map();

	void Init();
	void Update();
	void Draw();
	void Final();

	//=================================================
	// セッターゲッター
	//=================================================
	int GetModelHandle() const { return m_model->m_modelHandle; }

};

