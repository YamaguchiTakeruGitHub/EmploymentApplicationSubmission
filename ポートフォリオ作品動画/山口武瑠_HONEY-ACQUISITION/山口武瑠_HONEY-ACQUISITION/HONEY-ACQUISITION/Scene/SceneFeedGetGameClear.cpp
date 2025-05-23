#include "SceneFeedGetGameClear.h"
#include "../Scene/SceneManager.h"

SceneFeedGetGameClear::SceneFeedGetGameClear() :
	BgHandle		(),
	BgFlashHandle	(LoadGraph("img/FlashhoneyMap.png")),
	SceneTimeCount	(GameClearData::SceneTime),
	FlashTimeCount	(GameClearData::FlashTime)
{
}

SceneFeedGetGameClear::~SceneFeedGetGameClear()
{
}

void SceneFeedGetGameClear::Init()
{
	BgHandle;
	BgFlashHandle	= LoadGraph("img/FlashhoneyMap.png");
	SceneTimeCount  = GameClearData::SceneTime;//scene遷移までの時間初期化
	FlashTimeCount  = GameClearData::FlashTime;
}

void SceneFeedGetGameClear::Update()
{
	SceneTimeCount--;

	if (SceneTimeCount >= 0)
	{
		FlashTimeCount--;

		if (FlashTimeCount == 0)
		{
			FlashTimeCount = 10;
		}
	}

	//timeCountが0になったらシーンを移行
	if (SceneTimeCount <= 0)
	{
		SceneManager::SceneMgr_ChangeScene(SceneManager::eScene_GameStart);
	}

}

void SceneFeedGetGameClear::Draw()
{
	if (FlashTimeCount == 1 || FlashTimeCount == 2 || FlashTimeCount == 3 || FlashTimeCount == 4 || FlashTimeCount == 6 || FlashTimeCount == 7 || FlashTimeCount == 8 || FlashTimeCount == 9 || FlashTimeCount == 10 )
	{
		DrawGraph(0, 0, BgFlashHandle, true);
	}
}

void SceneFeedGetGameClear::Final()
{
	DeleteGraph(BgFlashHandle);
}
