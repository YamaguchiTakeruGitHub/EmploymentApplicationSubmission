#pragma once
#include "../Base/SceneBase.h"
class SceneLoad : public SceneBase
{
public:
	SceneLoad();
	~SceneLoad() override;

	void Init() override;
	void Update() override;
	void Draw() override;
	void Final() override;
};

