#pragma once
#include "../Base/Component.h"
#include "../ComponentTransform/ComponentTransform.h"

/// <summary>
/// �t�H���g�������R���|�[�l���g(�����w��F_transform)
/// </summary>
class ComponentFont : public Component
{
private:
	std::shared_ptr<ComponentTransform> m_transform;
	int m_fontHandle;		//�t�H���g�̃n���h��
	const char* m_letter;	//�`�悷�镶

public:
	ComponentFont(std::shared_ptr<ComponentTransform> _transform);
	~ComponentFont();

	void LoadFont(const char* _path, int _fontSize, int _fontThick);

	void Init() override;
	void Update() override;
	void Draw() override;
	void Final() override;

	//======================================================================
	// �Z�b�^�[�Q�b�^�[
	//======================================================================

	void SetFontLetter(const char* _letter) { m_letter = _letter; }
	const char* GetFontLetter() const { return m_letter; }

};

