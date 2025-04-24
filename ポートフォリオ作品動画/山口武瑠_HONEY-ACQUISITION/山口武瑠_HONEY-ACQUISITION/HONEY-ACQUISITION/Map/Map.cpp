#include "Map.h"
#include "../Player/Player.h"
#include "../Game.h"

Map::Map():
	m_mapHandle()
{
	m_pPlayer = new Player;

}

Map::~Map()
{
	delete m_pPlayer;
	m_pPlayer = nullptr;
}

void Map::Init()
{
	m_mapHandle;
}

void Map::Updata()
{
}

void Map::Draw()
{
	//マップの背景の描画
	DrawGraph(0, 0, m_mapHandle, true);

#if _DEBUG
	//マスの表示
	for (int y = 0; y < Game::MapChipHeight; y++)
	{
		for (int x = 0; x < Game::MapChipWidth; x++)
		{
			if (Game::MapData[y][x] == 0 || Game::MapData[y][x] == 8)
			{
				DrawBox(x * Game::MapChipSize, y * Game::MapChipSize,
					x * Game::MapChipSize + Game::MapChipSize, y * Game::MapChipSize + Game::MapChipSize, 0xffffff, false);
			}
		}
	}


#endif//DEBUG
}

void Map::Final()
{
	DeleteGraph(m_mapHandle);
}
