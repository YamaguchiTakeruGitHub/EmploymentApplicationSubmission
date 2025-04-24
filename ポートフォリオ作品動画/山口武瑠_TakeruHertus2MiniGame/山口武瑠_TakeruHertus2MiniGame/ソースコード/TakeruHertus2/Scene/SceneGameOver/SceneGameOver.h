#pragma once
#include "../Base/SceneBase.h"

class SceneGameOver : public SceneBase
{
public:
	SceneGameOver();
	~SceneGameOver() override;

	void Init() override;
	void Update() override;
	void Draw() override;
	void Final() override;
};

