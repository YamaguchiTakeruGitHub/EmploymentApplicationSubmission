#include "SceneTitlestandBy.h"
#include <DxLib.h>
#include "../Scene/SceneManager.h"


SceneTitlestandBy::SceneTitlestandBy() :
	cax					(-100),
	cay					(100),
	px					(-100),
	py					(160),
	ex					(-140),
	ey					(220),
	extwo				(-140),
	eytwo				(270),
	hx					(-100),
	hy					(280),
	phx					(-100),
	phy					(340),
	pox					(-100),
	poy					(400),
	Pvx					(-100),
	Pvy					(460),
	timeCount			(0),
	FeedanimPointFlash	(0),

	playerSTHandle		(LoadGraph("img/beeLeft.png")),
	enemySTHandle		(LoadGraph("img/brownbear.png")),
	enemySTHandleTwo	(LoadGraph("img/whitebear.png")),
	enemySTHandleThree	(),
	honeySTHandle		(LoadGraph("img/honey.png")),
	powerHoneySTHandle	(LoadGraph("img/PowerHoney.png")),
	potechiSTHandle		(LoadGraph("img/POTECHI.png")),
	
	m_TitleStandBySoundHandle(LoadSoundMem("sound/TitleST.mp3"))
{
}

SceneTitlestandBy::~SceneTitlestandBy()
{
}

void SceneTitlestandBy::init()
{
	cax					= -100;
	cay					= 100;
	px					= -100;
	py					= 160;
	ex					= -140;
	ey					= 220;
	extwo				= -140;
	eytwo				= 270;
	hx					= -100;
	hy					= 280;
	phx					= -100;
	phy					= 340;
	pox					= -100;
	poy					= 400;
	Pvx					= -100;
	Pvy					= 460;
	timeCount			= 0;
	FeedanimPointFlash	= 0;

	playerSTHandle		= LoadGraph("img/beeLeftTitleanim.png");
	enemySTHandle		= LoadGraph("img/brownbearTitleanim.png");
	honeySTHandle		= LoadGraph("img/honey.png");
	powerHoneySTHandle	= LoadGraph("img/PowerHoney.png");
	potechiSTHandle		= LoadGraph("img/POTECHI.png");


	m_TitleStandBySoundHandle = LoadSoundMem("sound/TitleST.mp3");
	PlaySoundMem(m_TitleStandBySoundHandle, DX_PLAYTYPE_LOOP);
}

void SceneTitlestandBy::Update()
{
	if (cax <= 200)
	{
		cax += 5;
	}

	if (cax >= 200 && px <= 405)
	{
		px += 5;
	}

	if (cax >= 200 && px >= 405 && ex <= 400)
	{
		ex += 5;
	}
	
	if (cax >= 200 && px >= 405 && ex >= 400 && extwo <= 400)
	{
		extwo += 5;
	}

	if (cax >= 200 && px >= 405 && ex >= 400 && hx <= 450)
	{
		hx += 5;
	}

	if (cax >= 200 && px >= 405 && ex >= 400 && hx >= 450 && phx <= 450)
	{
		phx += 5;
	}

	if (cax >= 200 && px >= 405 && ex >= 400 && hx >= 450 && phx >= 450 && pox <= 450)
	{
		pox += 5;
	}

	if (cax >= 200 && px >= 405 && ex >= 400 && hx >= 450 && phx >= 450 && pox >= 450 && Pvx <= 430)
	{
		Pvx += 5;
	}

	if (CheckHitKey(KEY_INPUT_SPACE) != 0)
	{
		SceneManager::SceneMgr_ChangeScene(SceneManager::eScene_Title);
	}

	

	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) == 0)
	{
		// ‰Ÿ‚³‚ê‚Ä‚¢‚È‚¢
	}
	else
	{
		// ‰Ÿ‚³‚ê‚Ä‚¢‚é
		SceneManager::SceneMgr_ChangeScene(SceneManager::eScene_Title);
	}

	if (timeCount >= 750)
	{
		SceneManager::SceneMgr_ChangeScene(SceneManager::eScene_Title);
	}

	//•¶š“_–Å‚Ì’l‚ğ’Ç‰Á‚µ‚Ä‚¢‚­
	FeedanimPointFlash++;

	//’l‚ª10‚É‚È‚Á‚½‚ç‚O‚É‚·‚é
	if (FeedanimPointFlash == 10)
	{
		FeedanimPointFlash = 0;
	}
	timeCount++;
}

void SceneTitlestandBy::Draw()
{
	
	DrawFormatString	(50, 0, 0xffffff, "‚P‚t‚o");
	DrawFormatString	(55, 20, 0xffffff, "‚O‚O");
	DrawFormatString	(270, 0, 0xffffff, "‚g‚h‚f‚g@‚r‚b‚n‚q‚d");

	DrawString			(cax, cay, "‚b‚g‚`‚q‚`‚b‚s‚d‚q@/@‚h‚s‚d‚l", 0xffffff,16);

	DrawGraph			(px -200, py , playerSTHandle, true);
	DrawString			(px - 150, py, "‚o‚k‚`‚x‚d‚q@/@‚a‚d‚d", 0xffff00, 16);

	DrawGraph			(ex - 200, ey, enemySTHandle, true);
	DrawString			(ex - 150, ey, "‚d‚m‚d‚l‚x@/@‚a‚q‚n‚v‚m‚a‚d‚`‚q", 0xff0000, 16);

	DrawGraph			(hx - 245, hy, honeySTHandle, true);
	DrawString			(hx - 200, hy, "‚h‚s‚d‚l@/@‚g‚n‚m‚d‚x", 0xffff00, 16);

	if (FeedanimPointFlash == 1 || FeedanimPointFlash == 2 || FeedanimPointFlash == 3 || FeedanimPointFlash == 4 || FeedanimPointFlash == 5 || FeedanimPointFlash == 6 || FeedanimPointFlash == 7 || FeedanimPointFlash == 8 || FeedanimPointFlash == 9 || FeedanimPointFlash == 10)
	{
		DrawGraph(phx - 245, phy, powerHoneySTHandle, true);
	}

	DrawString			(phx - 200, phy, "‚h‚s‚d‚l@/@‚o‚n‚v‚d‚q‚g‚n‚m‚d‚x", 0xfa500, 16);


	DrawGraph			(pox - 245, poy, potechiSTHandle, true);

	DrawString			(pox - 200, poy, "‚h‚s‚d‚l@/@‚o‚n‚s‚d‚b‚g‚h", 0xffff00, 16);

	DrawString			(Pvx -250, Pvy, "ƒ‚l‚`‚s‚d‚q‚h‚`‚k@‚o‚q‚n‚u‚h‚r‚h‚n‚m„\n@@@@`‚c‚n‚s@‚h‚k‚k‚t‚r‚s`\n@@@@@@`‚c‚n‚s‚n‚v‚m`\n@@@`‚h‚v‚`‚r‚h‚q‚n-‚r‚n‚t‚m‚c‚r`\n", 0x4666ff, 16);

}

void SceneTitlestandBy::Final()
{
	DeleteSoundMem		(m_TitleStandBySoundHandle);
}
