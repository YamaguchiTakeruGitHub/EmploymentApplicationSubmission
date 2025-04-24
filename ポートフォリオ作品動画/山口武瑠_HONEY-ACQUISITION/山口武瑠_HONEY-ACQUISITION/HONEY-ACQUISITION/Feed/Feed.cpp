#include "Feed.h"
#include "../Game.h"
#include "../Player/Player.h"

Feed::Feed():
	m_feedHandleh(),
	FeedExistence(true),
	FeedPosX(0),
	FeedPosY(0),
	GetFeedSound(LoadSoundMem("sound/feedGet.mp3"))
{
}

Feed::~Feed()
{
	DeleteSoundMem(GetFeedSound);
	DeleteGraph(m_feedHandleh);
}

void Feed::Init(Player& player)
{
	m_feedHandleh;
	FeedExistence = true;
	FeedPosX = 0;
	FeedPosY = 0;

	if (FeedMapPos[player.PlayerPos_Y][player.PlayerPos_X] == 8)
	{
		PlaySoundMem(GetFeedSound, DX_PLAYTYPE_BACK);
	}


	int row1[] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
	int row2[] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
	int row3[] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
	int row4[] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
	int row5[] = { 1,8,8,8,8,8,8,8,8,8,8,8,8,1,1,8,8,8,8,8,8,8,8,8,8,8,8,1 };
	int row6[] = { 1,8,1,1,1,1,8,1,1,1,1,1,8,1,1,8,1,1,1,1,1,8,1,1,1,1,8,1 };
	int row7[] = { 1,0,1,1,1,1,8,1,1,1,1,1,8,1,1,8,1,1,1,1,1,8,1,1,1,1,0,1 };
	int row8[] = { 1,8,1,1,1,1,8,1,1,1,1,1,8,1,1,8,1,1,1,1,1,8,1,1,1,1,8,1 };
	int row9[] = { 1,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,1 };
	int row10[] ={ 1,8,1,1,1,1,8,1,1,8,1,1,1,1,1,1,1,1,8,1,1,8,1,1,1,1,8,1 };
	int row11[] ={ 1,8,1,1,1,1,8,1,1,8,1,1,1,1,1,1,1,1,8,1,1,8,1,1,1,1,8,1 };
	int row12[] ={ 1,8,8,8,8,8,8,1,1,8,8,8,8,1,1,8,8,8,8,1,1,8,8,8,8,8,8,1 };
	int row13[] ={ 1,1,1,1,1,1,8,1,1,1,1,1,0,1,1,0,1,1,1,1,1,8,1,1,1,1,1,1 };
	int row14[] ={ 1,1,1,1,1,1,8,1,1,1,1,1,0,1,1,0,1,1,1,1,1,8,1,1,1,1,1,1 };
	int row15[] ={ 1,1,1,1,1,1,8,1,1,0,0,0,0,0,0,0,0,0,0,1,1,8,1,1,1,1,1,1 };
	int row16[] ={ 1,1,1,1,1,1,8,1,1,0,1,1,1,1,1,1,1,1,0,1,1,8,1,1,1,1,1,1 };
	int row17[] ={ 1,1,1,1,1,1,8,1,1,0,1,0,0,0,0,0,0,1,0,1,1,8,1,1,1,1,1,1 };
	int row18[] ={ 4,0,0,0,0,0,8,0,0,0,1,0,0,0,0,0,0,1,0,0,0,8,0,0,0,0,0,5 };
	int row19[] ={ 1,1,1,1,1,1,8,1,1,0,1,0,0,0,0,0,0,1,0,1,1,8,1,1,1,1,1,1 };
	int row20[] ={ 1,1,1,1,1,1,8,1,1,0,1,1,1,1,1,1,1,1,0,1,1,8,1,1,1,1,1,1 };
	int row21[] ={ 1,1,1,1,1,1,8,1,1,0,0,0,0,0,0,0,0,0,0,1,1,8,1,1,1,1,1,1 };
	int row22[] ={ 1,1,1,1,1,1,8,1,1,0,1,1,1,1,1,1,1,1,0,1,1,8,1,1,1,1,1,1 };
	int row23[] ={ 1,1,1,1,1,1,8,1,1,0,1,1,1,1,1,1,1,1,0,1,1,8,1,1,1,1,1,1 };
	int row24[] ={ 1,8,8,8,8,8,8,8,8,8,8,8,8,1,1,8,8,8,8,8,8,8,8,8,8,8,8,1 };
	int row25[] ={ 1,8,1,1,1,1,8,1,1,1,1,1,8,1,1,8,1,1,1,1,1,8,1,1,1,1,8,1 };
	int row26[] ={ 1,8,1,1,1,1,8,1,1,1,1,1,8,1,1,8,1,1,1,1,1,8,1,1,1,1,8,1 };
	int row27[] ={ 1,0,8,8,1,1,8,8,8,8,8,8,8,0,0,8,8,8,8,8,8,8,1,1,8,8,0,1 };
	int row28[] ={ 1,1,1,8,1,1,8,1,1,8,1,1,1,1,1,1,1,1,8,1,1,8,1,1,8,1,1,1 };
	int row29[] ={ 1,1,1,8,1,1,8,1,1,8,1,1,1,1,1,1,1,1,8,1,1,8,1,1,8,1,1,1 };
	int row30[] ={ 1,8,8,8,8,8,8,1,1,8,8,8,8,1,1,8,8,8,8,1,1,8,8,8,8,8,8,1 };
	int row31[] ={ 1,8,1,1,1,1,1,1,1,1,1,1,8,1,1,8,1,1,1,1,1,1,1,1,1,1,8,1 };
	int row32[] ={ 1,8,1,1,1,1,1,1,1,1,1,1,8,1,1,8,1,1,1,1,1,1,1,1,1,1,8,1 };
	int row33[] ={ 1,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,1 };
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
			FeedMapPos[y][x] = rows[y][x];
		}
	}
}

void Feed::Update(Player& player)
{
	if (FeedMapPos[player.PlayerPos_Y][player.PlayerPos_X] == 8)
	{
		PlaySoundMem(GetFeedSound, DX_PLAYTYPE_BACK);
		FeedMapPos[player.PlayerPos_Y][player.PlayerPos_X] = 0;
		player.score += 10;
		player.ClearManager += 1;
	}
}

void Feed::Draw(Player& player)
{	
	//‰a‚Ì•`‰æ
	for (int y = 0; y < Game::MapChipHeight; y++)
	{
		for (int x = 0; x < Game::MapChipWidth; x++)
		{
			if (FeedMapPos[y][x] == 8)
			{
				DrawGraph(x * Game::MapChipSize, y * Game::MapChipSize, m_feedHandleh, true);
			}
		}
	}

	
	

}

void Feed::Final()
{
	DeleteSoundMem(GetFeedSound);
	DeleteGraph(m_feedHandleh);

}
