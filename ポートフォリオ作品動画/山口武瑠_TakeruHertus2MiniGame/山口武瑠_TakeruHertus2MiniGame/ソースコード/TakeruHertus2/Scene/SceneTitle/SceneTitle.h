#pragma once
#include "../Base/SceneBase.h"
#include "../../Object/SceneSystem/SceneSystemTitle/SceneSystemTitle.h"

#include "../../Object/Font/Font.h"

class SceneTitle : public SceneBase
{
private:
	std::shared_ptr<SceneSystemTitle> m_systemTitle;
	std::shared_ptr<Font> m_font;

	
	/*�ϐ��錾*/
	bool m_isLoading;

public:
	SceneTitle();
	~SceneTitle();

	void Init() override;
	void Update() override;
	void Draw() override;
	void Final() override;
};



/*�^�C�g�������̗���*/
//�L�����N�^�[�C���X�g��3D�̃��f�����}�G�œ���A�^�C�g����ʂɃt�F�[�h�C������