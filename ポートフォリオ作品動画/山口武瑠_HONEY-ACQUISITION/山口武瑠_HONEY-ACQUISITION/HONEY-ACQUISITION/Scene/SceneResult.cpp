#include "SceneResult.h"
#include "DxLib.h"
#include "../Game.h"
#include "../Scene/SceneManager.h"

SceneResult::SceneResult():
	arrowPos_x			(410),
	arrowPos_y			(650),
	BoxPos_x1			(300),
	BoxPos_x2			(350),
	BoxPos_y1			(300),
	BoxPos_y2			(350),
	ArrowPosX			(170),
	ArrowPosY			(385),
	
	EndGameBotton		(false),
	
	ResultHandle		(LoadGraph("img/RESULT.png")),
	TitleBackHandle		(LoadGraph("img/TitleBack.png")),
	ArrowHandle			(LoadGraph("img/arrow.png")),
	RetryHandle			(LoadGraph("img/retry.png")),
	hakaHanlde			(LoadGraph("img/haka_02.png")),
	
	ResultSoundHandle	(LoadSoundMem("sound/Risut.mp3"))
{
}

SceneResult::~SceneResult()
{
}

void SceneResult::Init()
{
	arrowPos_y			= 385;
	arrowPos_x			= 170;
	
	EndGameBotton		= false;
	
	ResultHandle		= LoadGraph("img/RSULTgameover.png");
	TitleBackHandle		= LoadGraph("img/TitleBack.png");
	ArrowHandle			= LoadGraph("img/arrow.png");
	RetryHandle			= LoadGraph("img/retry.png");
	hakaHanlde			= LoadGraph("img/haka_02.png");

	ResultSoundHandle	= LoadSoundMem("sound/Risut.mp3");
	PlaySoundMem		(ResultSoundHandle, DX_PLAYTYPE_LOOP);
}

void SceneResult::Update()
{
	
	if (CheckHitKey(KEY_INPUT_LEFT) != 0 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT) != 0)
	{
		ArrowPosX = 170;
	}

	if (CheckHitKey(KEY_INPUT_RIGHT) != 0 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT) != 0)
	{
		ArrowPosX = 315;
	}

	if (ArrowPosX == 170)
	{
		if (CheckHitKey(KEY_INPUT_SPACE) != 0)
		{
			SceneManager::SceneMgr_ChangeScene(SceneManager::eScene_Title);
		}
		if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) == 0)
		{
		}
		else
		{
			SceneManager::SceneMgr_ChangeScene(SceneManager::eScene_Title);
		}

	}

	if (ArrowPosX == 315)
	{
		if (CheckHitKey(KEY_INPUT_SPACE) != 0)
		{
			SceneManager::SceneMgr_ChangeScene(SceneManager::eScene_GameStart);
		}

		if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) == 0)
		{
		}
		else
		{
			SceneManager::SceneMgr_ChangeScene(SceneManager::eScene_GameStart);
		}

	}

}

void SceneResult::Draw()
{
	
	DrawGraph(160, 100, ResultHandle, true);
	
	DrawGraph(220, 410, TitleBackHandle, true);

	DrawGraph(370, 410, RetryHandle, true);

	DrawGraph(290, 280, hakaHanlde, true);

	DrawGraph(ArrowPosX, ArrowPosY, ArrowHandle, true);
	
	if (EndGameBotton == true)
	{
		DrawFormatString(200, 200, 0xffffff, "endGameBottonPush");
	}
}

void SceneResult::Final()
{
	DeleteGraph		(ResultHandle);
	DeleteGraph		(TitleBackHandle);
	DeleteGraph		(RetryHandle);
	DeleteGraph		(hakaHanlde);
	DeleteGraph		(ArrowHandle);
	DeleteSoundMem	(ResultSoundHandle);
}

