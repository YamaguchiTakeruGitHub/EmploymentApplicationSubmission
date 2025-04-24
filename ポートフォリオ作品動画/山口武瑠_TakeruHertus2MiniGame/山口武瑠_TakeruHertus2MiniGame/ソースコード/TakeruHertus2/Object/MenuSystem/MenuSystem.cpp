#include "MenuSystem.h"


MenuSystem::MenuSystem()
	: m_isMenuOpen(false)//���j���J�t���O
{
	/*�C���X�^���X��*/
	m_Idm = std::make_shared<InputManager>();
	m_UI  = std::make_shared<UIManager>();

	/*�C���X�^���X���F�R���|�[�l���g*/
	for (int i = 0; i < MENUSYSTEM::MenuObjectNum; i++)
	{
		AddComponent<ComponentTransform>();
		m_transform.push_back(GetComponent<ComponentTransform>());//�����ɗv�f��ǉ�

		AddComponent<ComponentGraph>(m_transform[i]);//�������Q��
		m_graph.push_back(GetComponent<ComponentGraph>());//�����ɗv�f��ǉ�
	}
}

MenuSystem::~MenuSystem()
{
}

void MenuSystem::Init()
{
	m_Idm->Init();

	/*�����o�ϐ�������*/
	m_isMenuOpen = false;//���j���J�t���O

	/*�R���|�[�l���g������*/
	for (int i = 0; i < MENUSYSTEM::MenuObjectNum; i++)
	{
		Entity::InitComponent();
	}
}

void MenuSystem::Update()
{
	m_Idm->Update();

	if (m_Idm->m_joyPad->isSTART == true && m_isMenuOpen == false)
	{
		m_isMenuOpen = true;
	}

	for (int i = 0; i < MENUSYSTEM::MenuObjectNum; i++)
	{
		Entity::UpdateComponent();
	}
}

void MenuSystem::Draw()
{
	
	if (m_isMenuOpen == true)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 155);
		DrawBox(0, 0, 1280, 740, 0x000000, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	for (int i = 0; i < MENUSYSTEM::MenuObjectNum; i++)
	{
		Entity::DrawComponent();
	}
}

void MenuSystem::Final()
{
	for (int i = 0; i < MENUSYSTEM::MenuObjectNum; i++)
	{
		Entity::FinalComponent();
	}
}


/*���T�ŏI��点�鎖*/
//���j���[�V�X�e���̊���
//UI�֌W���e�X�g����
//���[�h�A�Z�[�u���������Q�[��scene�Ńe�X�g����
//�C���Q�[���̎���(�G�Ƃ̐퓬��U�����@�A�R�}���h�Ƃ��Q�[���̗V�т̕��������)
//��L���I��莟�擖���蔻��̏C�����s��
//�C�x���g�V�[���̊ȈՎ����̎d�g�݂����
//�G�t�F�N�g�֘A������
//�A�j���[�V�����̊֘A��������
//

//�ق��F�X

//2�����ɃQ�[�����쐬���Ă�����{�I�Ȏ����͏I��点�āA�R���̂P�`10�ŃQ�[���̊�����������

