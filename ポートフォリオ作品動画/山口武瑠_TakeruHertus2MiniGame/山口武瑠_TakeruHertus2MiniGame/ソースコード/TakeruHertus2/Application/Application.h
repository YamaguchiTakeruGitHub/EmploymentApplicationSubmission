#pragma once
#include <EffekseerForDXLib.h>
#include <DxLib.h>
#include "../Scene/Manager/SceneManager.h"

class Application final
{
public:
	/// <summary>
	/// シーンマネージャー依存
	/// </summary>
	/// <param name="_sceneManager"></param>
	Application(SceneManager& _sceneManager);
	~Application();
	
	/// <summary>
	/// 初期化
	/// </summary>
	/// <returns></returns>
	bool Init_App();

	/// <summary>
	/// 実行
	/// </summary>
	void Run_App();

	/// <summary>
	/// 解放
	/// </summary>
	void close_App();

private:
	//シーンマネージャーのインスタンス
	SceneManager& m_sceneManager;

};
