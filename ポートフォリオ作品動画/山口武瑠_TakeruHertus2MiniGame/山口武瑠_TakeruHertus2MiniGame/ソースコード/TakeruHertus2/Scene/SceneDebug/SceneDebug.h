#pragma once
#include "../Base/SceneBase.h"
#include "../../InputDevice/InputManager.h"
#include "../../UI/UIManager.h"

/// <summary>
/// デバックシーン
/// </summary>
class SceneDebug : public SceneBase
{
private:

	std::shared_ptr<UIManager> m_UI;//UIのシステムを扱う
	
	/*選択のポジション*/
	struct Position
	{
		VECTOR Title;
		VECTOR Game;
		VECTOR GameOver;
		VECTOR Clear;
		VECTOR Load;
		VECTOR DebugTitleUIEdit;
		VECTOR nowPoint;
	}m_pos;

	/*選択しの列挙型*/
	typedef enum
	{
		eSelect_Title,				//タイトルシーン	
		eSelect_Game,				//ゲームシーン
		eSelect_GameOver,			//ゲームオーバーシーン
		eSelect_Clear,				//クリアシーン
		eSelect_Load,				//ロードシーン
		eSelect_DebugTitleUIEdit,	//UIエディット

		eSelect_Num,				//選択肢の数判別
	}eSelect;

	int m_nowSelect;//現在選択している項目の格納

	/// <summary>
	/// 現在の選択
	/// </summary>
	void SelectNow();

	/// <summary>
	/// 選択した項目の実行
	/// </summary>
	void SelectPushEntryScene();


public:
	SceneDebug();
	~SceneDebug()override;

	void Init() override;
	void Update() override;
	void Draw() override;
	void Final() override;

};

