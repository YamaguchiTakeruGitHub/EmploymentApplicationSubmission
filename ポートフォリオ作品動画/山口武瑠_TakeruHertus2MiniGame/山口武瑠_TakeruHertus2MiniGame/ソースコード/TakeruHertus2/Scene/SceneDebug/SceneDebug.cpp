#include "SceneDebug.h"
#include "../Manager/SceneManager.h"

void SceneDebug::SelectNow()
{
	//現在のシーンに応じて、選択カーソルのY軸に各シーンの選択肢のY軸を格納
	switch (m_nowSelect)
	{
	case eSelect_Title:
		m_pos.nowPoint.y = m_pos.Title.y;
		break;
	case eSelect_Game:
		m_pos.nowPoint.y = m_pos.Game.y;
		break;
	case eSelect_GameOver:
		m_pos.nowPoint.y = m_pos.GameOver.y;
		break;
	case eSelect_Clear:
		m_pos.nowPoint.y = m_pos.Clear.y;
		break;
	case eSelect_Load:
		m_pos.nowPoint.y = m_pos.Load.y;
		break;
	case eSelect_DebugTitleUIEdit:
		m_pos.nowPoint.y = m_pos.DebugTitleUIEdit.y;
		break;
	}
}

void SceneDebug::SelectPushEntryScene()
{
	//選択肢のシーンを実行
	if (m_Idm->m_joyPad->isB == true)
	{
		switch (m_nowSelect)
		{
		case eSelect_Title:
			SceneManager::GetInstance().ChangeScene(SceneType::Title);
			break;
		case eSelect_Game:
			SceneManager::GetInstance().ChangeScene(SceneType::Game);
			break;
		case eSelect_GameOver:
			SceneManager::GetInstance().ChangeScene(SceneType::GameOver);
			break;
		case eSelect_Clear:
			SceneManager::GetInstance().ChangeScene(SceneType::Clear);
			break;
		case eSelect_Load:
			SceneManager::GetInstance().ChangeScene(SceneType::Loading);
			break;
		case eSelect_DebugTitleUIEdit:
			SceneManager::GetInstance().ChangeScene(SceneType::DebugTitleUIEdit);
			break;
		}
	}
}

SceneDebug::SceneDebug()
	: m_nowSelect(0)
	, m_pos()
{
	m_UI = std::make_shared<UIManager>();//インスタンス化

	/*ポジションの初期化*/
	m_pos.Title = VGet(30,20,0);
	m_pos.Game = VGet(30, 40, 0);
	m_pos.GameOver = VGet(30, 60, 0);
	m_pos.Clear = VGet(30, 80, 0);
	m_pos.Load = VGet(30, 100, 0);
	m_pos.DebugTitleUIEdit = VGet(30, 120, 0);

	m_nowSelect = eSelect_Title;		//現在選択のシーン
}

SceneDebug::~SceneDebug()
{
	//解放するリソースはないので記入無し
}

void SceneDebug::Init()
{
	m_Idm->Init();						//入力デバイスの初期化
	m_UI->Init();						//UIの初期化

	/*各シーンの座標の初期化*/
	m_pos.Title = VGet(30, 20, 0);	
	m_pos.Game = VGet(30, 40, 0);		
	m_pos.GameOver = VGet(30, 60, 0);
	m_pos.Clear = VGet(30, 80, 0);
	m_pos.Load = VGet(30, 100, 0);
	m_pos.DebugTitleUIEdit = VGet(30, 120, 0);


	m_nowSelect = eSelect_Title;		//現在の選択肢をタイトルに設定
}

void SceneDebug::Update()
{
	//入力デバイスのの更新
	m_Idm->Update();

	//上選択の更新
	m_UI->m_select->UpSelect(m_nowSelect, eSelect_Num, m_Idm->m_joyPad->isDUP == true);

	//下選択の更新
	m_UI->m_select->DownSelect(m_nowSelect, eSelect_Num, m_Idm->m_joyPad->isDDOWN == true);

	/*現在の選択肢とその決定*/
	SelectPushEntryScene();
	SelectNow();
}

void SceneDebug::Draw()
{
	/*ＣＵＩ*/
#ifdef _DEBUG
	DrawString(0, 0, "DebugScene", 0xffffff);
	DrawString(m_pos.Title.x, m_pos.Title.y, "TitleScene", 0xffffff);
	DrawString(m_pos.Game.x, m_pos.Game.y, "GameScene", 0xfffffff);
	DrawString(m_pos.GameOver.x, m_pos.GameOver.y, "GameOverScene", 0xffffff);
	DrawString(m_pos.Clear.x, m_pos.Clear.y, "ClearScene", 0xfffffff);
	DrawString(m_pos.Load.x, m_pos.Load.y, "LoadScene", 0xffffff);
	DrawString(m_pos.DebugTitleUIEdit.x, m_pos.DebugTitleUIEdit.y, "DebugTitleUIEdit", 0xffffff);

	DrawString(m_pos.nowPoint.x, m_pos.nowPoint.y, "→", 0xffffff);

#endif // _DEBUG

}

void SceneDebug::Final()
{
	/*解放するリソースはないので記入無し*/
}
