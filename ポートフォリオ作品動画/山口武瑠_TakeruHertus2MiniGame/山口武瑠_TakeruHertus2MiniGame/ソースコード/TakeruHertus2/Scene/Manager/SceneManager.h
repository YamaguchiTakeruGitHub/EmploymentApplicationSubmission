#pragma once
#include "../Base/SceneBase.h"

/// <summary>
/// シーンマネージャー
/// </summary>
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void Init();
	void Update();
	void Draw();
	void Final();

	/// <summary>
	/// 継承先で取得するインスタンス
	/// </summary>
	/// <returns></returns>
	static SceneManager& GetInstance() { static SceneManager instance; return instance; }

	/// <summary>
	/// 継承先で扱うシーン遷移
	/// </summary>
	/// <param name="_newScene"></param>
	void ChangeScene(SceneType _newScene);

private:
	std::shared_ptr<SceneBase> m_currentScene;
	std::shared_ptr<SceneBase> m_titleScene;
	std::shared_ptr<SceneBase> m_gameScene;
	std::shared_ptr<SceneBase> m_gameOverScene;
	std::shared_ptr<SceneBase> m_clearScene;
	std::shared_ptr<SceneBase> m_loadScene;
	std::shared_ptr<SceneBase> m_debugScene;
	std::shared_ptr<SceneBase> m_debugTitleUIEditScene;

	std::shared_ptr<SceneBase> m_miniGame_TitleScene;
	std::shared_ptr<SceneBase> m_miniGame_GameScene;
};

