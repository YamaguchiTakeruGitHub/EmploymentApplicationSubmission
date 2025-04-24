#pragma once
#include "../Base/Component.h"
#include "../ComponentTransform/ComponentTransform.h"

/// <summary>
/// フォントを扱うコンポーネント(引数指定：_transform)
/// </summary>
class ComponentFont : public Component
{
private:
	std::shared_ptr<ComponentTransform> m_transform;
	int m_fontHandle;		//フォントのハンドル
	const char* m_letter;	//描画する文

public:
	ComponentFont(std::shared_ptr<ComponentTransform> _transform);
	~ComponentFont();

	void LoadFont(const char* _path, int _fontSize, int _fontThick);

	void Init() override;
	void Update() override;
	void Draw() override;
	void Final() override;

	//======================================================================
	// セッターゲッター
	//======================================================================

	void SetFontLetter(const char* _letter) { m_letter = _letter; }
	const char* GetFontLetter() const { return m_letter; }

};

