#include "SceneGameStart.h"
#include "DxLib.h"
#include "../Map/Map.h"
#include "../Scene/SceneManager.h"
#include "../Game.h"

SceneGameStart::SceneGameStart() :
	Time				(10),
	GSFlashPoint		(0),
	StartTime			(0),
	
	StartTimeFlag		(false),
	
	StartText			(LoadGraph("img/READYTXT.png")),
	PoText				(LoadGraph("img/PLAYERONETXT.png")),
	GSBHandle			(LoadGraph("img/honeyMap.png")),
	GSPlayerRogoHandle	(LoadGraph("img/PlayerRogo.png")),
	FeedhandleStart		(LoadGraph("img/honey.png")),
	m_GameStartSound	(LoadSoundMem("sound/gameStartSound.wav")),
	GSPlayerHandle		(LoadGraph("img/beeLeft.png"))
{
}

SceneGameStart::~SceneGameStart()
{
}

void SceneGameStart::Init()
{
	StartTime			= 0;
	
	StartTimeFlag		= false;
	
	StartText			= LoadGraph("img/READYTXT.png");
	GSBHandle			= LoadGraph("img/honeyMap.png");
	PoText				= LoadGraph("img/PLAYERONETXT.png");
	FeedhandleStart		= LoadGraph("img/honey.png");
	GSPlayerHandle		= LoadGraph("img/beeLeft.png");
	GSPlayerRogoHandle	= LoadGraph("img/PlayerRogo.png");
	
	m_GameStartSound	= LoadSoundMem("sound/gameStartSound.wav");
	PlaySoundMem		(m_GameStartSound, DX_PLAYTYPE_BACK, false);
}

void SceneGameStart::Update()
{

	StartTime++;
	if (StartTime >= 150)
	{
		StartTimeFlag = true;
		SceneManager::SceneMgr_ChangeScene(SceneManager::eScene_Main);
	}

	if (StartTime == 150)
	{
		StartTimeFlag = false;
		StartTime = 0;
	}

	//•¶Žš“_–Å‚Ì’l‚ð’Ç‰Á‚µ‚Ä‚¢‚­
	GSFlashPoint++;

	//’l‚ª10‚É‚È‚Á‚½‚ç‚O‚É‚·‚é
	if (GSFlashPoint == 10)
	{
		GSFlashPoint = 0;
	}

}

void SceneGameStart::Draw()
{

	for (int y = 0; y < Game::MapChipHeight; y++)
	{
		for (int x = 0; x < Game::MapChipWidth; x++)
		{
			if (Game::MapData[y][x] == 8)
			{
				DrawGraph(x * Game::MapChipSize, y * Game::MapChipSize, FeedhandleStart, true);
			}
		}
	}
	DrawGraph(0, 0, GSBHandle, true);
	DrawGraph(220, 475, StartText, true);
	DrawGraph(220, 335, PoText, true);

	
	if (GSFlashPoint == 1 || GSFlashPoint == 2 || GSFlashPoint == 4 || GSFlashPoint == 5 || GSFlashPoint == 7 || GSFlashPoint == 8 || GSFlashPoint == 10)
	{
		DrawGraph(300, 590, GSPlayerRogoHandle, true);
		DrawGraph(320, 610, GSPlayerHandle, true);
	}
}

void SceneGameStart::Final()
{
	DeleteSoundMem	(m_GameStartSound);
	DeleteGraph		(StartText);
	DeleteGraph		(PoText);
	DeleteGraph		(GSBHandle);
	DeleteGraph		(FeedhandleStart);
}
