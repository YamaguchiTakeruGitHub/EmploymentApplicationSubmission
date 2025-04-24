#pragma once
#include "../Game.h"

class Player;
class Map
{
public:
	Map();
	~Map();

	void Init();
	void Updata();
	void Draw();
	void Final();


	void MapSetHandle(int* handle) { m_mapHandle = *handle; }


	int m_mapHandle;

private:
	Player* m_pPlayer;

};

