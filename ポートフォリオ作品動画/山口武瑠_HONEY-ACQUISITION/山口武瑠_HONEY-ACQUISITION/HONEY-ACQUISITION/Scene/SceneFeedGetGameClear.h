#pragma once
#include "DxLib.h"

struct GameClearData
{
	static const int SceneTime = 100;
	static const int FlashTime = 10;
};

class SceneManager;
class SceneFeedGetGameClear
{
public:
	SceneFeedGetGameClear();
	~SceneFeedGetGameClear();

	void Init();
	void Update();
	void Draw();
	void Final();

private:
	int BgHandle;
	int BgFlashHandle;
	int SceneTimeCount;
	int FlashTimeCount;
};

