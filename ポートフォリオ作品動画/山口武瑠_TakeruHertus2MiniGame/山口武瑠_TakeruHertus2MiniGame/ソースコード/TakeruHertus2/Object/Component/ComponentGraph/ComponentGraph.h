#pragma once
#include "../Base/Component.h"
#include "../ComponentTransform/ComponentTransform.h"

/// <summary>
/// 画像を扱うコンポーネント(引数指定：_transform)
/// </summary>
class ComponentGraph : public Component
{
private:
	/*インスタンス宣言：コンポーネント*/
	//transform
	std::shared_ptr<ComponentTransform> m_transform;
	
	/*変数宣言*/
	//画像のハンドル
	int m_graphHandle;

public:
	ComponentGraph(std::shared_ptr<ComponentTransform> _transform);

	~ComponentGraph() override;

	void LoadGraph(const char* _filePath);

	int GetGraph() const { return m_graphHandle; }

	void Init() override;
	void Update() override;

	/// <summary>
	/// 通常描画
	/// </summary>
	void Draw() override;
	void Final() override;

	/*特殊描画*/

	/// <summary>
	/// フェードエフェクトで描画する
	/// </summary>
	/// <param name="_fadeSpeed">フェードする速度</param>
	void FadeEffectDraw(int _fadeSpeed);

};

