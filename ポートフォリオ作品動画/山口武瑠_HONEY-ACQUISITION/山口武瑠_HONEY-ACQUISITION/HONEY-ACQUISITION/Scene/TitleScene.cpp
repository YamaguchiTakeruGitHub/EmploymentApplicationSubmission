#include "TitleScene.h"
#include "DxLib.h"
#include "../Game.h"
#include "SceneManager.h"
#include <ctime>



TitleScene::TitleScene() :
	timeCount						(0),
	taEx							(672),
	taEy							(400),
	taPx							(650),
	taPy							(400),
	Title_Y							(100),
	Title_X							(180),
	SceneChangTimeFlag				(false),
	TitleBottonFlag					(false),
	TitleAnimEnemyThreeHandle		(LoadGraph("img/panda.png")),
	TitleHandle						(LoadGraph("img/Title.png")),
	TitleAnimPlayerHandle			(LoadGraph("img/beeRight.png")),
	TitleAnimEnemyHandle			(LoadGraph("img/brownbear.png")),
	TitleAnimEnemyTwoHandle			(LoadGraph("img/whitebear.png")),
	TitleSound						(LoadSoundMem("sound/Title.mp3")),
	TitleSrectBerHandle				(LoadGraph("TitleSerectBer.png")),
	SceneChangTime					(),
	TitleLogo						(),
	TitleBotton						(),
	SceneCheang						(),
	CoinCredits						(),
	CreditsFlag						(),
	PushBottonFlag					(),
	KEY								(),
	coinbut							(),
	flashingPoint					(),
	BrightnessAdjustmentLevl		(),
	BrightnessAdjustmentFlag		()

{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Init()
{
	Title_X						= 180;
	Title_Y						= 100;
	CoinCredits					=   0;
	flashingPoint				=   0;
	BrightnessAdjustmentLevl	= 100;
	timeCount					=   0;
	taEx						=   0;
	taEy						= 500;
	taPx						=   0;
	taPy						= 500;

	CreditsFlag					= false;
	PushBottonFlag				= false;
	TitleBottonFlag				= false;

	TitleHandle					= LoadGraph		("img/Title.png");
	TitleAnimEnemyThreeHandle	= LoadGraph		("img/panda.png");
	TitleAnimPlayerHandle		= LoadGraph		("img/beeRight.png");
	TitleAnimEnemyHandle		= LoadGraph		("img/brownbear.png");
	TitleAnimEnemyTwoHandle		= LoadGraph		("img/whitebear.png");

	TitleSound					= LoadSoundMem	("sound/Title.mp3");

	PlaySoundMem				(TitleSound, DX_PLAYTYPE_LOOP);
}

void TitleScene::Update()
{

	
	BYTE key[256];
	KEY = GetKeyboardState(key);

	/*â∫ÇÃíÜÇ…É^ÉCÉgÉãÉ{É^ÉìÇ™âüÇ≥ÇÍÇÈÇ‹Ç≈ÇÃèàóùÇèëÇ≠*/
	if (TitleBottonFlag == false)
	{	
		//ï∂éöì_ñ≈ÇÃílÇí«â¡ÇµÇƒÇ¢Ç≠
		flashingPoint++;

		//ílÇ™10Ç…Ç»Ç¡ÇΩÇÁÇOÇ…Ç∑ÇÈ
		if (flashingPoint == 10)
		{
			flashingPoint = 0;
		}
	}

	if (timeCount <= 480 && timeCount >= 70)
	{
		UpdateTitleAnim1();
	}

	if (timeCount >= 10)
	{
		if (CheckHitKey(KEY_INPUT_SPACE) != 0)
		{
			SceneManager::SceneMgr_ChangeScene(SceneManager::eScene_GameStart);
		}

		if (CheckHitKey(KEY_INPUT_T) != 0)
		{
			SceneManager::SceneMgr_ChangeScene(SceneManager::eScene_Result);
		}

		if (CheckHitKey(KEY_INPUT_R) != 0)
		{
			SceneManager::SceneMgr_ChangeScene(SceneManager::eScene_TStandBy);
		}

		if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) == 0)
		{
			// âüÇ≥ÇÍÇƒÇ¢Ç»Ç¢
		}
		else
		{
			// âüÇ≥ÇÍÇƒÇ¢ÇÈ
			SceneManager::SceneMgr_ChangeScene(SceneManager::eScene_GameStart);
		}

	}

	if (timeCount >= 660)
	{
		SceneManager::SceneMgr_ChangeScene(SceneManager::eScene_TStandBy);
	}
	timeCount += 1;
}

void TitleScene::Draw()
{
	DrawGraph		(Title_X, Title_Y, TitleHandle, true);
	
	if (flashingPoint == 2 || flashingPoint == 3 || flashingPoint == 4 || flashingPoint == 5 || flashingPoint == 6 || flashingPoint == 7 || flashingPoint == 8)
	{
		DrawString	(210, 300, "PUSHÅ@< A or SPACE >Å@BUTTON", 0xffd700, Game::ColorBit);
	}

	DrawString		(250, 335, " ÇPÅ@PLAYER ONLY", 0x00ffff, Game::ColorBit);

	DrawString		(220, 370, "BONUS POTECHI FOR 100 PTS", 0xffb6c1, Game::ColorBit);

	DrawString		(245, 400, "  Å¸Å@TAKERU 2024", 0x00ffff, Game::ColorBit);

	if (timeCount <= 480 && timeCount >= 70)
	{
		DrawTitleAnim1();
	}

}

void TitleScene::Final()
{
	DeleteSoundMem	(TitleSound);
	DeleteGraph		(TitleAnimPlayerHandle);
	DeleteGraph		(TitleAnimEnemyHandle);
	DeleteGraph		(TitleAnimEnemyTwoHandle);
	DeleteGraph		(TitleAnimEnemyThreeHandle);

}

void TitleScene::UpdateTitleAnim1()
{
	if (taEx <= 790)
	{
		taEx += 3;
	}

	if (taPx <= 672)
	{
		taPx += 3;
	}
}

void TitleScene::DrawTitleAnim1()
{
	DrawGraph	(taEx - 40, taEy, TitleAnimEnemyHandle, true);
	DrawGraph	(taEx - 80, taEy, TitleAnimEnemyTwoHandle, true);
	DrawGraph	(taEx - 120, taEy, TitleAnimEnemyThreeHandle, true);
	DrawGraph	(taPx, taPy, TitleAnimPlayerHandle, true);
	DrawString	(taPx + 20, taPy - 16, "Å´ÇoÇkÇ`ÇxÇdÇq", 0xffff00, 16);
	DrawString	(taEx - 105, taEy + 58 , "ÇdÇmÇdÇlÇxÇr", 0xff0000, 16);

}

CoinBUT TitleScene::Getcoinbut() const
{
	return coinbut;
}
