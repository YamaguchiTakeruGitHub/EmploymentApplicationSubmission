#pragma once
#include "../Base/Component.h"

/// <summary>
/// 3Dモデルを扱うコンポーネント
/// </summary>
class ComponentModel : public Component
{
private:

public:
	/// <summary>
	/// 呼び出し時にモデルの解放を行う
	/// </summary>
	~ComponentModel() override;

	/// <summary>
	/// モデルのロードを行う
	/// </summary>
	/// <param name="_filePath">3Dモデルのパス</param>
	void LoadModel(const char* _filePath);

	/// <summary>
	/// モデルを他クラスで取得する
	/// </summary>
	/// <returns>モデルハンドル</returns>
	int GetModel() const { return m_modelHandle; }

	void Init() override;
	void Update() override;
	void Draw() override;
	void Final() override;

	int m_modelHandle;//モデルのハンドル

};

