#pragma once
#include "../../Entity/Entity.h"

class TutorialMap : public Entity
{
private:
	std::shared_ptr<ComponentModel> m_model;
	std::shared_ptr<ComponentTransform> m_transform;

public:
	TutorialMap();
	~TutorialMap();

	void Init();
	void Update();
	void Draw();
	void Final();

	void DrawGrid(float areaSize, int numLines, float lineHeight);
	void DrawBox(VECTOR _boxPos, VECTOR _boxSize);


	//ƒ‚ƒfƒ‹‚ðŽæ“¾‚·‚é
	int GetModelHandle() const { return m_model->m_modelHandle; }

};

