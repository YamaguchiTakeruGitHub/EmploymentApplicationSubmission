#include "PowerFeed.h"
#include "../Game.h"
#include "../Player/Player.h"

PowerFeed::PowerFeed():
	m_powerFeedHandle(),
	FeedPointFlash(),
	powerFeedSoundHandle(LoadSoundMem("sound/PFedGet.mp3"))
{
}

PowerFeed::~PowerFeed()
{
}

void PowerFeed::Init()
{
	m_powerFeedHandle;

	int row1[] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
	int row2[] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
	int row3[] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
	int row4[] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
	int row5[] = { 1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1 };
	int row6[] = { 1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1 };
	int row7[] = { 1,9,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,9,1 };
	int row8[] = { 1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1 };
	int row9[] = { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 };
	int row10[] ={ 1,0,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,0,1 };
	int row11[] ={ 1,0,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,0,1 };
	int row12[] ={ 1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1 };
	int row13[] ={ 1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1 };
	int row14[] ={ 1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1 };
	int row15[] ={ 1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1 };
	int row16[] ={ 1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1 };
	int row17[] ={ 1,1,1,1,1,1,0,1,1,0,1,0,0,0,0,0,0,1,0,1,1,0,1,1,1,1,1,1 };
	int row18[] ={ 4,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,5 };
	int row19[] ={ 1,1,1,1,1,1,0,1,1,0,1,0,0,0,0,0,0,1,0,1,1,0,1,1,1,1,1,1 };
	int row20[] ={ 1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1 };
	int row21[] ={ 1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1 };
	int row22[] ={ 1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1 };
	int row23[] ={ 1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1 };
	int row24[] ={ 1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1 };
	int row25[] ={ 1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1 };
	int row26[] ={ 1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1 };
	int row27[] ={ 1,9,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,9,1 };
	int row28[] ={ 1,1,1,0,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,0,1,1,1 };
	int row29[] ={ 1,1,1,0,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,0,1,1,1 };
	int row30[] ={ 1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1 };
	int row31[] ={ 1,0,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1 };
	int row32[] ={ 1,0,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1 };
	int row33[] ={ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 };
	int row34[] ={ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
	int row35[] ={ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
	int row36[] ={ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };

	int* rows[] = { row1,row2, row3, row4, row5, row6, row7, row8, row9, row10,
				   row11,row12, row13, row14, row15, row16, row17, row18, row19, row20,
				   row21,row22, row23, row24, row25, row26, row27, row28, row29, row30,
				   row31,row32, row33, row34, row35, row36 };

	for (int y = 0; y < Game::MapChipHeight; y++)
	{
		for (int x = 0; x < Game::MapChipWidth; x++)
		{
			PowerFeedMapPos[y][x] = rows[y][x];
		}
	}

}

void PowerFeed::Update(Player& player)
{
	//パワー餌とプレイヤーの当たり判定＆スコア加算（一エサ50点加算）
	if (PowerFeedMapPos[player.PlayerPos_Y][player.PlayerPos_X] == 9)
	{
		PowerFeedMapPos[player.PlayerPos_Y][player.PlayerPos_X] = 0;

		PlaySoundMem(powerFeedSoundHandle, DX_PLAYTYPE_BACK);
		player.score += 50;


		player.ClearManager += 1;
	}

	if (player.Player_GameOverFlag == false)
	{
		//文字点滅の値を追加していく
		FeedPointFlash++;

		//値が10になったら０にする
		if (FeedPointFlash == 10)
		{
			FeedPointFlash = 0;
		}
	}

}

void PowerFeed::Draw()
{
	//パワー餌の描画
	if (FeedPointFlash == 1 || FeedPointFlash == 2 || FeedPointFlash == 4 || FeedPointFlash == 5 || FeedPointFlash == 7 || FeedPointFlash == 8 || FeedPointFlash == 10)
	{
		for (int y = 0; y < Game::MapChipHeight; y++)
		{
			for (int x = 0; x < Game::MapChipWidth; x++)
			{
				if (PowerFeedMapPos[y][x] == 9)
				{

					DrawGraph(x * Game::MapChipSize, y * Game::MapChipSize, m_powerFeedHandle, true);

				}
			}
		}
	}
}

void PowerFeed::Final()
{
	DeleteGraph(m_powerFeedHandle);
	DeleteSoundMem(powerFeedSoundHandle);
}
