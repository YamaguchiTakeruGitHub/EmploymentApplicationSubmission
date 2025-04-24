#include "MenuSystem.h"


MenuSystem::MenuSystem()
	: m_isMenuOpen(false)//メニュ開閉フラグ
{
	/*インスタンス化*/
	m_Idm = std::make_shared<InputManager>();
	m_UI  = std::make_shared<UIManager>();

	/*インスタンス化：コンポーネント*/
	for (int i = 0; i < MENUSYSTEM::MenuObjectNum; i++)
	{
		AddComponent<ComponentTransform>();
		m_transform.push_back(GetComponent<ComponentTransform>());//末尾に要素を追加

		AddComponent<ComponentGraph>(m_transform[i]);//末尾を参照
		m_graph.push_back(GetComponent<ComponentGraph>());//末尾に要素を追加
	}
}

MenuSystem::~MenuSystem()
{
}

void MenuSystem::Init()
{
	m_Idm->Init();

	/*メンバ変数初期化*/
	m_isMenuOpen = false;//メニュ開閉フラグ

	/*コンポーネント初期化*/
	for (int i = 0; i < MENUSYSTEM::MenuObjectNum; i++)
	{
		Entity::InitComponent();
	}
}

void MenuSystem::Update()
{
	m_Idm->Update();

	if (m_Idm->m_joyPad->isSTART == true && m_isMenuOpen == false)
	{
		m_isMenuOpen = true;
	}

	for (int i = 0; i < MENUSYSTEM::MenuObjectNum; i++)
	{
		Entity::UpdateComponent();
	}
}

void MenuSystem::Draw()
{
	
	if (m_isMenuOpen == true)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 155);
		DrawBox(0, 0, 1280, 740, 0x000000, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	for (int i = 0; i < MENUSYSTEM::MenuObjectNum; i++)
	{
		Entity::DrawComponent();
	}
}

void MenuSystem::Final()
{
	for (int i = 0; i < MENUSYSTEM::MenuObjectNum; i++)
	{
		Entity::FinalComponent();
	}
}


/*今週で終わらせる事*/
//メニューシステムの完成
//UI関係をテスト実装
//ロード、セーブを実装しゲームsceneでテスト実装
//インゲームの実装(敵との戦闘や攻撃魔法、コマンドとかゲームの遊びの部分をやる)
//上記が終わり次第当たり判定の修正を行う
//イベントシーンの簡易実装の仕組みを作る
//エフェクト関連を実装
//アニメーションの関連を見直し
//

//ほか色々

//2月中にゲームを作成していく基本的な実装は終わらせて、３月の１～10でゲームの完成をさせる

