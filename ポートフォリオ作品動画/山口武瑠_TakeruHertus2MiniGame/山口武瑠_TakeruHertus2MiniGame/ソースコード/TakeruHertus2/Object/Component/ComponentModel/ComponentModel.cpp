#include "ComponentModel.h"

ComponentModel::~ComponentModel()
{
	//モデルハンドルに何かしら入っていれば
	if (m_modelHandle != -1)
	{
		//モデルを解放
		MV1DeleteModel(m_modelHandle);
	}
}

void ComponentModel::LoadModel(const char* _filePath)
{
	SetUseASyncLoadFlag(true);//非同期読み込み有効
	//モデルのロード
	m_modelHandle = MV1LoadModel(_filePath);
	SetUseASyncLoadFlag(false);//以降非同期読み込み判定してはいけないため解除

	//もしモデルに何も入らなかったら
	if (m_modelHandle == -1)
	{
#ifdef _DEBUG
		DrawFormatString(0, 40, 0xff0000, "モデルを読み込めませんでした");
#endif // _DEBUG
	}

}

void ComponentModel::Init()
{
}

void ComponentModel::Update()
{
}

void ComponentModel::Draw()
{
	//モデルに何かしら入っていれば
	if (m_modelHandle != -1)
	{
		//モデルを描画する
		MV1DrawModel(m_modelHandle);
	}
}

void ComponentModel::Final()
{
	//モデルに何かしら入っていれば
	if (m_modelHandle != -1)
	{
		//モデルを解放する
		MV1DeleteModel(m_modelHandle);
	}
}
