#include "ComponentGraph.h"

ComponentGraph::ComponentGraph(std::shared_ptr<ComponentTransform> _transform)
	: m_transform(_transform)
	, m_graphHandle(-1)
{
}

ComponentGraph::~ComponentGraph()
{
	if (m_graphHandle != -1)
	{
		DeleteGraph(m_graphHandle);
	}
}

void ComponentGraph::LoadGraph(const char* _filePath)
{
	SetUseASyncLoadFlag(true);//非同期読み込み
	m_graphHandle = DxLib::LoadGraph(_filePath);
	SetUseASyncLoadFlag(false);//解除

	if (m_graphHandle != -1)
	{
#ifdef _DEBUG
		DrawString(0, 0, "グラフを読み込めませんでした。", 0xffffff);
#endif // _DEBUG
	}
}

void ComponentGraph::Init()
{
}

void ComponentGraph::Update()
{
}

void ComponentGraph::Draw()
{
	if (m_graphHandle != -1)
	{
		DrawGraph(m_transform->position.x, m_transform->position.y, m_graphHandle, true);
	}
	else
	{
		DrawString(0, 0, "グラフが読み込めず描画失敗。", 0xffffff);
	}
}

void ComponentGraph::Final()
{
	DeleteGraph(m_graphHandle);
}

void ComponentGraph::FadeEffectDraw(int _fadeSpeed)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _fadeSpeed);
	if (m_graphHandle != -1)
	{
		DrawGraph(m_transform->position.x, m_transform->position.y, m_graphHandle, true);
	}
	else
	{
		DrawString(0, 0, "フェードイン＿グラフが読み込めず描画失敗。", 0xffffff);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
