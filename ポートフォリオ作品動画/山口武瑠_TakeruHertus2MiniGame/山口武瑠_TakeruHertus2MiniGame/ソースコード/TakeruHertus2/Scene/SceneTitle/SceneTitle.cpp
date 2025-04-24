#include "SceneTitle.h"
#include "../../Application/GameConstant.h"

SceneTitle::SceneTitle()
	: m_isLoading(false)
{
	m_systemTitle = std::make_shared<SceneSystemTitle>();
	m_font = std::make_shared<Font>();
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{
	m_systemTitle->Init();
	m_isLoading = true;
	m_font->Init();
}

void SceneTitle::Update()
{
	if (m_isLoading)
	{
		if (GetASyncLoadNum() == 0)
		{
			m_isLoading = false;
		}
	}
	else
	{
		m_systemTitle->Update();
	}
	m_font->Update();
}

void SceneTitle::Draw()
{
	if (m_isLoading)
	{
		
		m_font->Draw();

		// ロードの進行状況を計算
		int totalLoadTasks = SCENESYSTEMTITLE::OBJECTNUM; // 総ロードタスク数を取得する関数（仮定）
		int remainingLoadTasks = GetASyncLoadNum(); // 残りのロードタスク数を取得
		float progress = 1.0f - (static_cast<float>(remainingLoadTasks) / totalLoadTasks);

		// バーの描画
		int barWidth = 200; // バーの幅
		int barHeight = 20; // バーの高さ
		int barX = 100; // バーのX座標
		int barY = 50; // バーのY座標
		DrawBox(barX, barY, barX + static_cast<int>(barWidth * progress), barY + barHeight, 0x00ff00, TRUE); // プログレスバー
		DrawBox(barX, barY, barX + barWidth, barY + barHeight, 0xffffff, false);

		if (GetASyncLoadNum() == 0)
		{
			m_isLoading = false;
		}
	}
	else
	{
		m_systemTitle->Draw();
	
	}
}

void SceneTitle::Final()
{
	m_systemTitle->Final();
	m_font->Final();
}
