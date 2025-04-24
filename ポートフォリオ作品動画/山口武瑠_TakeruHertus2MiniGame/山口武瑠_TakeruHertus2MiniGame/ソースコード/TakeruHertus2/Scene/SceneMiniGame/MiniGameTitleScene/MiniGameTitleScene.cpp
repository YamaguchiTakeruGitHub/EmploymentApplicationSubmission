#include "MiniGameTitleScene.h"
#include "../../Manager/SceneManager.h"

MiniGameTitleScene::MiniGameTitleScene()
{
	m_titleSystem = std::make_shared<SceneSystem_MiniGame_Title>();
}

MiniGameTitleScene::~MiniGameTitleScene()
{
}

void MiniGameTitleScene::Init()
{
	m_titleSystem->Init();
}

void MiniGameTitleScene::Update()
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
		m_titleSystem->Update();
	}
}

void MiniGameTitleScene::Draw()
{
	if (m_isLoading)
	{
		DrawLoadinBar();

		if (GetASyncLoadNum() == 0)
		{
			m_isLoading = false;
		}
	}
	else
	{
		m_titleSystem->Draw();
	}
}

void MiniGameTitleScene::Final()
{
	m_titleSystem->Final();
}


void MiniGameTitleScene::DrawLoadinBar()
{
	float progress = GetLoadingProgress();
	int barWidth = 200;
	int barHeight = 20;
	int x = (640 - barWidth) / 2; // 画面中央に配置
	int y = 360; // 画面中央に配置

	DrawBox(x, y, x + barWidth, y + barHeight, GetColor(255, 255, 255), TRUE); // 白い枠
	DrawBox(x, y, x + static_cast<int>(barWidth * progress), y + barHeight, GetColor(0, 255, 0), TRUE); // 緑の進捗バー
}


float MiniGameTitleScene::GetLoadingProgress()
{
	int totalResources = 3; // 仮に10個のリソースがあるとする
	int loadedResources = totalResources - GetASyncLoadNum();
	return static_cast<float>(loadedResources) / totalResources;
}