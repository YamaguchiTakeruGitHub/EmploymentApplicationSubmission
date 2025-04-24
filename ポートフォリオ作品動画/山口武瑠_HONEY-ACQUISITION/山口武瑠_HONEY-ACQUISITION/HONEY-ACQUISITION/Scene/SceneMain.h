#pragma once
#include "DxLib.h"

class Enemy;
class EnemyTwo;
class EnemyThree;
class Map;
class Player;
class Feed;
class PowerFeed;
class bonusFeed;
class UI;

class SceneMain
{
public:
		SceneMain	();
		~SceneMain	();

	void Init		();
	void Update		();
	void Draw		();
	void Final		();
	
	bool TitleReturnBotton;

	int m_MainSoundHandle;

private:
	int m_mapHandle;
	int m_playerHandle;
	int m_enemyBlinkyHandle;
	int m_enemyTwoHandle;
	int m_feedHandle;
	int m_powerFeedHandle;
	int m_bonusFeedHandle;
	int m_enemyThreeHandle;


	UI*			m_pUI;
	Map*		m_pMap;
	Player*		m_pPlayer;
	Enemy*		m_pEnemy;
	Feed*		m_pFeed;
	PowerFeed*	m_pPowerFeed;
	bonusFeed*  m_pbonusFeed;
	EnemyTwo*	m_pEnemyTwo;
	EnemyThree* m_pEnemyThree;
};

