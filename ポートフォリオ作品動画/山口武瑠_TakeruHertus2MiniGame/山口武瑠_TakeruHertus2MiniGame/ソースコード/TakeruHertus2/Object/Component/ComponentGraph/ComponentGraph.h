#pragma once
#include "../Base/Component.h"
#include "../ComponentTransform/ComponentTransform.h"

/// <summary>
/// �摜�������R���|�[�l���g(�����w��F_transform)
/// </summary>
class ComponentGraph : public Component
{
private:
	/*�C���X�^���X�錾�F�R���|�[�l���g*/
	//transform
	std::shared_ptr<ComponentTransform> m_transform;
	
	/*�ϐ��錾*/
	//�摜�̃n���h��
	int m_graphHandle;

public:
	ComponentGraph(std::shared_ptr<ComponentTransform> _transform);

	~ComponentGraph() override;

	void LoadGraph(const char* _filePath);

	int GetGraph() const { return m_graphHandle; }

	void Init() override;
	void Update() override;

	/// <summary>
	/// �ʏ�`��
	/// </summary>
	void Draw() override;
	void Final() override;

	/*����`��*/

	/// <summary>
	/// �t�F�[�h�G�t�F�N�g�ŕ`�悷��
	/// </summary>
	/// <param name="_fadeSpeed">�t�F�[�h���鑬�x</param>
	void FadeEffectDraw(int _fadeSpeed);

};

