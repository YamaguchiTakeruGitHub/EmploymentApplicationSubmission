#include "SceneMain.h"
#include "TitleScene.h"
#include "SceneManager.h"
#include "../UITool/UI.h"
#include "../Feed/Feed.h"

#include "../Scene/PauseScene.h"
#include "../Scene/SceneResult.h"
#include "../Scene/SceneGameClear.h"
#include "../Scene/SceneGameStart.h"
#include "../Scene/SceneTitlestandBy.h"
#include "../Scene/SceneTransAnim.h"
#include "../Scene/SceneFeedGetGameClear.h"

static SceneManager::eScene mScene = SceneManager::eScene_Title;
static SceneManager::eScene mNextScene = SceneManager::eScene_None;

SceneManager::SceneManager() :
	GameOver_Flag	(false),
	m_score			(0)
{
	m_pTitle		= new TitleScene;
	m_pMain			= new SceneMain;
	m_pResult	    = new SceneResult;
	m_pClear		= new SceneGameClear;
	m_pTStandBy		= new SceneTitlestandBy;
	m_pGameStart	= new SceneGameStart;
	m_pTransAnim	= new SceneTransAnim;
	m_pUI			= new UI;
	m_pGetGameClear = new SceneFeedGetGameClear;
}

SceneManager::~SceneManager()
{

	delete m_pTitle;
	m_pTitle = nullptr;

	delete m_pMain;
	m_pMain = nullptr;

	delete m_pResult;
	m_pResult = nullptr;

	delete m_pClear;
	m_pClear = nullptr;

	delete m_pTStandBy;
	m_pTStandBy = nullptr;

	delete m_pGameStart;
	m_pGameStart = nullptr;
	
	delete m_pTransAnim;
	m_pTransAnim = nullptr;

	delete m_pUI;
	m_pUI = nullptr;

	delete m_pGetGameClear;
	m_pGetGameClear = nullptr;
}

void SceneManager::Init()
{
	InitalizeModule(mScene);
}

void SceneManager::Final()
{
	FinalizeModule(mScene);
}

void SceneManager::Update()
{
	if (mNextScene != eScene_None)
	{
		FinalizeModule	(mScene);
		mScene			 = mNextScene;
		mNextScene		= eScene_None;
		InitalizeModule	(mScene);
	}

	switch (mScene)
	{
	case eScene_TStandBy:
		m_pTStandBy->Update();
			break;
	case eScene_Title:
		m_pTitle->Update();
		break;
	case eScene_Main:
		m_pMain->Update();
		break;
	case eScene_Result:
		m_pResult->Update();
		break;
	case eScene_Clear:
		m_pClear->Update();
		break;
	case eScene_GameStart:
		m_pGameStart->Update();
		break;
	case eScene_anim:
		m_pTransAnim->Update();
		break;
	case eScene_GameClear:
		m_pGetGameClear->Update();
		break;
	}
}

void SceneManager::Draw()
{
	switch (mScene)
	{
	case eScene_TStandBy:
		m_pTStandBy->Draw();
		break;
	case eScene_Title:
		m_pTitle->Draw();
		break;
	case eScene_Main:
		m_pMain->Draw();
		break;
	case eScene_Result:
		m_pResult->Draw();
		break;
	case eScene_Clear:
		m_pClear->Draw();
		break;
	case eScene_GameStart:
		m_pGameStart->Draw();
		break;
	case eScene_anim:
		m_pTransAnim->Draw();
		break;
	case eScene_GameClear:
		m_pGetGameClear->Draw();
		break;
	}
}

void SceneManager::SceneMgr_ChangeScene(eScene NextScene)
{
	mNextScene = NextScene;
}

void SceneManager::InitalizeModule(eScene scene) 
{
	switch (mScene)
	{
	case eScene_TStandBy:
		m_pTStandBy->init();
		break;
	case eScene_Title:
		m_pTitle->Init();
		break;
	case eScene_Main:
		m_pMain->Init();
		break;
	case eScene_Result:
		m_pResult->Init();
		break;
	case eScene_Clear:
		m_pClear->Init();
		break;
	case eScene_GameStart:
		m_pGameStart->Init();
		break;
	case eScene_anim:
		m_pTransAnim->Init();
		break;
	case eScene_GameClear:
		m_pGetGameClear->Init();
		break;
	}
}

void SceneManager::FinalizeModule(eScene scene)
{
	switch (mScene)
	{
	case eScene_TStandBy:
		m_pTStandBy->Final();
		break;
	case eScene_Title:
		m_pTitle->Final();
		break;
	case eScene_Main:
		m_pMain->Final();
		break;
	case eScene_Result:
		m_pResult->Final();
		break;
	case eScene_Clear:
		m_pClear->Final();
		break;
	case eScene_GameStart:
		m_pGameStart->Final();
		break;
	case eScene_anim:
		m_pTransAnim->Final();
		break;
	case eScene_GameClear:
		m_pGetGameClear->Final();
		break;
	}
}

void SceneManager::ScorePlayerCountManager(int score, int point)
{
	if (score >= point)
	{
		SceneManager::SceneMgr_ChangeScene(SceneManager::eScene_GameClear);
	}
}

void SceneManager::addScore(int points)
{
	m_score += points;
}

