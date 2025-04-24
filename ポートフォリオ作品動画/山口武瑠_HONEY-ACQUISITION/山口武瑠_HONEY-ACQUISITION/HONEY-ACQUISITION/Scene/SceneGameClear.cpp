#include "SceneGameClear.h"
#include "DxLib.h"
#include "../Game.h"
#include "../Player/Player.h"
#include "../Scene/SceneManager.h"

SceneGameClear::SceneGameClear() :
	flowerHandle		(LoadGraph("img/cosmos_white.png")),
	souzenHandle		(LoadGraph("img/sougen.png")),
	beehandle			(LoadGraph("img/bee.png")),
	torideHandle		(LoadGraph("img/toride.png")),
	bakuhatuHandle		(LoadGraph("img/bakuhatsu_01.png")),
	kowaretasiroHandle	(LoadGraph("img/takibi_off.png")),
	eeekeyhandle		(LoadGraph("img/eeekey.png")),
	beePosX				(110),
	beePosY				(110)


{
}

SceneGameClear::~SceneGameClear()
{
}

void SceneGameClear::Init()
{
	flowerHandle;
	souzenHandle;
	beehandle;
	torideHandle;
	bakuhatuHandle;
	kowaretasiroHandle;
	eeekeyhandle;
	beePosX = 110;
	beePosY = 110;
}

void SceneGameClear::Final()
{
}

void SceneGameClear::Update()
{
	if (beePosX != 440 && beePosY != 440)
	{
		beePosX++;
		beePosY++;
	}
}

void SceneGameClear::Draw()
{
	DrawString(0, 0, "ÉQÅ[ÉÄÉNÉäÉA", 0xffffff, Game::ColorBit);
	
	for (int y = 0; y < Game::MapChipHeight; y++)
	{
		for (int x = 0; x < Game::MapChipWidth; x++)
		{
			DrawGraph(x * Game::MapChipSize, y * Game::MapChipSize, souzenHandle, true);
		}
	}

	DrawGraph(440, 440, flowerHandle, true);
	DrawGraph(100, 100, torideHandle, true);
	DrawGraph(beePosX, beePosY, beehandle, true);

	DrawFormatString(0, 0, 0x000000, "x=%d,y=%d", beePosX, beePosY);

	if (beePosX <= 440 && beePosY <= 440 && beePosX >= 350 && beePosY >= 350)
	{
		if (beePosX >= 360 && beePosY >= 360 && beePosX <= 440 && beePosY <= 440)
		{
			DrawGraph(100, 100, bakuhatuHandle, true);
		}
		if (beePosX >= 365 && beePosY >= 365 && beePosX <= 440 && beePosY <= 440)
		{
			DrawGraph(130, 105, bakuhatuHandle, true);
		}
		if (beePosX >= 370 && beePosY >= 370 && beePosX <= 440 && beePosY <= 440)
		{
			DrawGraph(110, 130, bakuhatuHandle, true);
		}
	}

	if (beePosX == 380 && beePosY == 380)
	{
		DeleteGraph(bakuhatuHandle);
		DeleteGraph(torideHandle);
	}

	if (beePosX >= 387 && beePosY >= 387 && beePosX <= 440 && beePosY <= 440)
	{
		DrawGraph(100, 100, kowaretasiroHandle, true);

		DrawGraph(0, 0, eeekeyhandle, true);

	}

	if (CheckHitKey(KEY_INPUT_SPACE) != 0)
	{
		SceneManager::SceneMgr_ChangeScene(SceneManager::eScene_Title);

	}

}


