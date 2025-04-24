#include "SceneSystem_MiniGame_Title.h"
#include "../../../Scene/Manager/SceneManager.h"

namespace OBJECT
{
	static constexpr int NUM = 4;//�I�u�W�F�N�g�̌�
}

SceneSystem_MiniGame_Title::SceneSystem_MiniGame_Title()
	: m_currentSelect(eSelect_MiniGame_1)//�I�𒆂̑I����
	, m_currentSelectPos(VGet(0,0,0))
	, m_fadeCount(0)//�t�F�[�h�G�t�F�N�g�p�̕ϐ�
	, m_push_B_DELAY(0)
{
	/*�C���X�^���X�錾�i�R���|�[�l���g�j*/
	for (int i = 0; i < OBJECT::NUM; i++)
	{
		AddComponent<ComponentTransform>();
		m_transforms.push_back(GetComponent<ComponentTransform>());//�����ɗv�f��ǉ�

		AddComponent<ComponentGraph>(m_transforms[i]);//�������Q��
		m_graphs.push_back(GetComponent<ComponentGraph>());//�����ɗv�f��ǉ�
	}

	m_Idm = std::make_shared<InputManager>();
	m_UI = std::make_shared<UIManager>();

}

void SceneSystem_MiniGame_Title::Init()
{
	m_Idm->Init();
	m_UI->Init();

	m_currentSelect = eSelect_MiniGame_1;//�����̑I����
	m_fadeCount = 0;//�t�F�[�h�G�t�F�N�g�p�̕ϐ�
	m_push_B_DELAY = 0;

	/*�w�i*/
	m_transforms[0]->position = VGet(0, 0, 0);
	m_graphs[0]->LoadGraph("../Data/Asset/2D/MiniGame/TitleScene/BackGround2.png");

	/*�o�g���^�C���A�^�b�N*/
	m_transforms[1]->position = VGet(0, 0, 0);
	m_graphs[1]->LoadGraph("../Data/Asset/2D/MiniGame/TitleScene/SelectBattleTimeAttack.png");

	/*�����Ȃ�*/
	m_transforms[2]->position = VGet(0, 0, 0);
	m_graphs[2]->LoadGraph("../Data/Asset/2D/MiniGame/TitleScene/SelectNone.png");

	/*����*/
	m_transforms[3]->position = VGet(0, 0, 0);
	m_graphs[3]->LoadGraph("../Data/Asset/2D/MiniGame/TitleScene/LetterBattleTimeAttack.png");

	Entity::InitComponent();
}

void SceneSystem_MiniGame_Title::Update()
{
	m_Idm->Update();

	/*�O��̑I������ۑ�*/
	auto previouseSelect = m_currentSelect;

	for (int i = 0; i < OBJECT::NUM; i++)
	{
		m_transforms[i]->Update();
		m_graphs[i]->Update();
	}

	/*�Z���N�g�̍X�V*/
	m_UI->m_select->LeftSelect(m_currentSelect, eSelect_ObjectNum, m_Idm->m_joyPad->isDLEFT == true);
	m_UI->m_select->RightSelect(m_currentSelect, eSelect_ObjectNum, m_Idm->m_joyPad->isDRIGHT == true);

	/*�I�������ς������t�F�[�h�����Z�b�g*/
	if (previouseSelect != m_currentSelect)
	{
		m_fadeCount = 0;
	}

	/*�t�F�[�h�C��*/
	if (m_fadeCount >= 255)
	{
		m_fadeCount = 255;
	}
	else
	{
		m_fadeCount += 5;
	}

	/*����{�^����������悤�ɂȂ�܂ł̒x������*/
	if (m_push_B_DELAY >= 60)
	{
		m_push_B_DELAY = 60;
	}
	else
	{
		m_push_B_DELAY++;
	}

	Update_SelectChengeScene();
}

void SceneSystem_MiniGame_Title::Draw()
{
	m_transforms[0]->Draw();
	m_graphs[0]->Draw();

	Draw_FadeGraphs();

}

void SceneSystem_MiniGame_Title::Final()
{
	for (int i = 0; i < OBJECT::NUM; i++)
	{
		m_transforms[i]->Final();
		m_graphs[i]->Final();
	}
}

void SceneSystem_MiniGame_Title::Update_SelectChengeScene()
{
	if (m_Idm->m_joyPad->isB == true && m_push_B_DELAY == 60)
	{
		switch (m_currentSelect)
		{
		case eSelect_MiniGame_1:
			SceneManager::GetInstance().ChangeScene(SceneType::MiniGame_Game);
			
			break;
		case eSelect_MiniGame_2:
			break;
		case eSelect_MiniGame_3:
			break;
		}
	}
}

void SceneSystem_MiniGame_Title::Draw_FadeGraphs()
{
	switch (m_currentSelect)
	{
	case eSelect_MiniGame_1:
		m_graphs[1]->FadeEffectDraw(m_fadeCount);
		m_graphs[3]->FadeEffectDraw(m_fadeCount);
		
		break;
	case eSelect_MiniGame_2:
		m_graphs[2]->FadeEffectDraw(m_fadeCount);

		break;
	case eSelect_MiniGame_3:
		m_graphs[2]->FadeEffectDraw(m_fadeCount);

		break;
	}
}
