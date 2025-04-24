#include "SceneManager.h"
#include "../SceneTitle/SceneTitle.h"
#include "../SceneGame/SceneGame.h"
#include "../SceneGameOver/SceneGameOver.h"
#include "../SceneClear/SceneClear.h"
#include "../SceneLoad/SceneLoad.h"
#include "../SceneDebug/SceneDebug.h"
#include "../SceneDebugTitleUIEdit/SceneDebugTitleUIEdit.h"

#include "../SceneMiniGame/MiniGameGameScene/MiniGameGameScene.h"
#include "../SceneMiniGame/MiniGameTitleScene/MiniGameTitleScene.h"

SceneManager::SceneManager()
{
	/*シーンのインスタンス化*/
	m_titleScene = std::make_shared<SceneTitle>();
	m_gameScene = std::make_shared<SceneGame>();
	m_gameOverScene = std::make_shared<SceneGameOver>();
	m_clearScene = std::make_shared<SceneClear>();
	m_loadScene = std::make_shared<SceneLoad>();
	m_debugScene = std::make_shared<SceneDebug>();
	m_debugTitleUIEditScene = std::make_shared<SceneDebugTitleUIEdit>();

	m_miniGame_TitleScene = std::make_shared<MiniGameTitleScene>();
	m_miniGame_GameScene = std::make_shared<MiniGameGameScene>();

	/*最初に実行するシーンを現在のシーンに格納*/
#ifdef _DEBUG
	//m_currentScene = m_debugScene;
	m_currentScene = m_miniGame_TitleScene;

#else
	//m_currentScene = m_titleScene;
	m_currentScene = m_miniGame_TitleScene;

#endif // _DEBUG
}

SceneManager::~SceneManager()
{
	m_currentScene->Final();
}

void SceneManager::ChangeScene(SceneType _newScene)
{
	/*現在のシーンを解放してから現在のシーンに新しいシーンを格納*/
	m_currentScene->Final();
	switch (_newScene)
	{
	case SceneType::Title:
		m_currentScene = m_titleScene;
		break;
	case SceneType::Game:
		m_currentScene = m_gameScene;
		break;
	case SceneType::GameOver:
		m_currentScene = m_gameOverScene;
		break;
	case SceneType::Clear:
		m_currentScene = m_clearScene;
		break;
	case SceneType::Loading:
		m_currentScene = m_loadScene;
		break;
	case SceneType::Debug:
		m_currentScene = m_debugScene;
		break;
	case SceneType::DebugTitleUIEdit:
		m_currentScene = m_debugTitleUIEditScene;
		break;
	case SceneType::MiniGame_Title:
		m_currentScene = m_miniGame_TitleScene;
		break;
	case SceneType::MiniGame_Game:
		m_currentScene = m_miniGame_GameScene;
		break;

	}

	m_currentScene->Init();//初期化
}

void SceneManager::Init()
{
	m_currentScene->Init();
}

void SceneManager::Update()
{
	m_currentScene->Update();
}

void SceneManager::Draw()
{
	m_currentScene->Draw();
}

void SceneManager::Final()
{
	m_currentScene->Final();
}

