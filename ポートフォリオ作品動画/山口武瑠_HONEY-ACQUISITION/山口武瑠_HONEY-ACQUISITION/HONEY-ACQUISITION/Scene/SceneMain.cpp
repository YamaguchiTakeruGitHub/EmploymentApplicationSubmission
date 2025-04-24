#include "DxLib.h"
#include "SceneMain.h"
#include "../Map/Map.h"
#include "../Player/Player.h"
#include "../Enemy/Enemy.h"
#include "../Feed/Feed.h"
#include "../Feed/PowerFeed.h"
#include "../Feed/bonusFeed.h"
#include "../UITool/UI.h"
#include "../Enemy/EnemyTwo.h"
#include "../Enemy/EnemyThree.h"

#pragma warning(disable:4819)

SceneMain::SceneMain():
	TitleReturnBotton								(false),
	m_MainSoundHandle								(LoadSoundMem("sound/BGM.mp3"))
{
	//メモリにグラフをぶちコム
	m_mapHandle			 = LoadGraph				("img/honeyMap.png");	//マップ
	m_feedHandle		 = LoadGraph				("img/honey.png");		//エサ
	m_powerFeedHandle	 = LoadGraph				("img/PowerHoney.png"); //パワーエサのハンドル（後々別ファイルに移す）
	m_bonusFeedHandle	 = LoadGraph				("img/POTECHI.png");
	m_playerHandle		 = LoadGraph				("img/beeRight.png");	//プレイヤー
	m_enemyBlinkyHandle	 = LoadGraph				("img/brownbear.png");	//敵（赤）
	m_enemyTwoHandle	 = LoadGraph				("img/whitebear.png");
	m_enemyThreeHandle   = LoadGraph				("img/panda.png");

	//メモリにサウンドをぶち込む


	m_pUI				 = new UI;
	m_pMap				 = new Map;
	m_pFeed				 = new Feed;
	m_pPowerFeed		 = new PowerFeed;
	m_pbonusFeed		 = new bonusFeed;
	m_pPlayer			 = new Player;
	m_pEnemy			 = new Enemy;
	m_pEnemyTwo			 = new EnemyTwo;
	m_pEnemyThree		 = new EnemyThree;


	m_pMap				->MapSetHandle				(&m_mapHandle);
	m_pFeed				->FeedSetHandle				(&m_feedHandle);
	m_pPowerFeed		->PowerFeedSetHandle		(&m_powerFeedHandle);
	m_pbonusFeed		->BonusFeedSetHandle		(&m_bonusFeedHandle);
	m_pPlayer			->playerSetHandle			(&m_playerHandle);
	m_pEnemy			->enemyBlinkySetHandle		(&m_enemyBlinkyHandle);
	m_pEnemyTwo			->enemyTwoSetHandle			(&m_enemyTwoHandle);
	m_pEnemyThree		->enemyThreeSetHandle		(&m_enemyThreeHandle);
}

SceneMain::~SceneMain()
{
	m_pUI				= nullptr;
	m_pMap				= nullptr;
	m_pFeed				= nullptr;
	m_pPowerFeed		= nullptr;
	m_pbonusFeed		= nullptr;
	m_pEnemy			= nullptr;
	m_pEnemyTwo			= nullptr;
	m_pPlayer			= nullptr;
	m_pEnemyThree	    = nullptr;


	delete				m_pUI;
	delete				m_pMap;
	delete				m_pFeed;
	delete				m_pPowerFeed;
	delete				m_pbonusFeed;
	delete				m_pEnemy;
	delete				m_pEnemyTwo;
	delete				m_pPlayer;
	delete				m_pEnemyThree;
}

void SceneMain::Init()
{
	m_mapHandle				= LoadGraph				("img/honeyMap.png");		//マップ
	m_feedHandle			= LoadGraph				("img/honey.png");			//エサ
	m_powerFeedHandle		= LoadGraph				("img/PowerHoney.png");		//パワーエサ
	m_bonusFeedHandle		= LoadGraph				("img/POTECHI.png");			//ボーナスエサ
	m_playerHandle			= LoadGraph				("img/beeLeft.png");			//プレイヤー
	m_enemyBlinkyHandle		= LoadGraph				("img/brownbear.png");		//敵（赤）
	m_enemyTwoHandle		= LoadGraph				("img/whitebear.png");
	m_enemyThreeHandle		= LoadGraph				("img/panda.png");

	m_pUI					= new UI;
	m_pMap					= new Map;
	m_pFeed					= new Feed;
	m_pPowerFeed			= new PowerFeed;
	m_pbonusFeed			= new bonusFeed;
	m_pPlayer				= new Player;
	m_pEnemy				= new Enemy;
	m_pEnemyTwo				= new EnemyTwo;
	m_pEnemyThree			= new EnemyThree;



	m_pMap					->MapSetHandle			(&m_mapHandle);
	m_pFeed					->FeedSetHandle			(&m_feedHandle);
	m_pPowerFeed			->PowerFeedSetHandle	(&m_powerFeedHandle);
	m_pbonusFeed			->BonusFeedSetHandle	(&m_bonusFeedHandle);
	m_pPlayer				->playerSetHandle		(&m_playerHandle);
	m_pEnemy				->enemyBlinkySetHandle	(&m_enemyBlinkyHandle);
	m_pEnemyTwo				->enemyTwoSetHandle		(&m_enemyTwoHandle);
	m_pEnemyThree			->enemyThreeSetHandle	(&m_enemyThreeHandle);
	m_pUI					->Init					(*m_pPlayer, *m_pEnemy);
	m_pMap					->Init					();
	m_pFeed					->Init					(*m_pPlayer);
	m_pPowerFeed			->Init					();
	m_pbonusFeed			->Init					(*m_pPlayer);
	m_pPlayer				->Init					(*m_pEnemy, *m_pUI);
	m_pEnemy				->Init					(*m_pPlayer, *m_pPowerFeed, *m_pEnemyTwo, *m_pEnemyThree);
	m_pEnemyTwo				->Init					(*m_pPlayer, *m_pPowerFeed, *m_pEnemy, *m_pEnemyThree);
	m_pEnemyThree			->Init					(*m_pPlayer,*m_pPowerFeed, *m_pEnemy, *m_pEnemyTwo);
	m_MainSoundHandle		= LoadSoundMem			("sound/BGM.mp3");
	PlaySoundMem									(m_MainSoundHandle, DX_PLAYTYPE_LOOP);
}

void SceneMain::Update()
{
	
	m_pMap					->Updata				();
	m_pUI					->Update				(*m_pPlayer, *m_pEnemy);
	m_pFeed					->Update				(*m_pPlayer);
	m_pPowerFeed			->Update				(*m_pPlayer);
	m_pbonusFeed			->Update				(*m_pPlayer);
	m_pPlayer				->Update				(*m_pEnemy, *m_pFeed, *m_pUI);
	m_pEnemy				->Update				(*m_pPlayer, *m_pPowerFeed, *m_pEnemyTwo, *m_pEnemyThree);
	m_pEnemyTwo				->Update				(*m_pPlayer, *m_pPowerFeed, *m_pEnemy, *m_pEnemyThree);
	m_pEnemyThree			->Update				(*m_pPlayer, *m_pPowerFeed, *m_pEnemy, *m_pEnemyTwo);
	
}

void SceneMain::Draw()
{
	m_pUI					->Draw					(*m_pPlayer, *m_pEnemy);
	m_pMap					->Draw					();
	m_pFeed					->Draw					(*m_pPlayer);
	m_pPowerFeed			->Draw					();
	m_pbonusFeed			->Draw					(*m_pPlayer);
	m_pPlayer				->Draw					(*m_pEnemy, *m_pUI);
	m_pEnemy				->Draw					(*m_pPlayer, *m_pPowerFeed, *m_pEnemyTwo, *m_pEnemyThree);
	m_pEnemyTwo				->Draw					(*m_pPlayer, *m_pPowerFeed, *m_pEnemy, *m_pEnemyThree);
	m_pEnemyThree			->Draw					(*m_pPlayer, *m_pPowerFeed, *m_pEnemy, *m_pEnemyTwo);
}

void SceneMain::Final()
{
	m_pUI					->Final					();
	m_pMap					->Final					();
	m_pFeed					->Final					();
	m_pPowerFeed			->Final					();
	m_pbonusFeed			->Final					();
	m_pPlayer				->Final					();
	m_pEnemy				->Final					();
	m_pEnemyTwo				->Final					();
	m_pEnemyThree			->Final					();
	DeleteSoundMem									(m_MainSoundHandle);
}
