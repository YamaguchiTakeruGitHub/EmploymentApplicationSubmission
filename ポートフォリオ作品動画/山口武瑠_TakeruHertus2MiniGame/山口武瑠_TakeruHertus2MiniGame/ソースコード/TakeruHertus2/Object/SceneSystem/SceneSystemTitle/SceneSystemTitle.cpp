#include "SceneSystemTitle.h"

SceneSystemTitle::SceneSystemTitle()
	: m_selectedCellX(0)//�G�f�B�^�[�p�̑I�����WX
	, m_selectedCellY(0)//�G�f�B�^�[�p�̑I�����WY
	, m_currentSelect(eSelect_NEWGAME)//�I�𒆂̑I����

	, m_fadeCount(0)//�t�F�[�h�G�t�F�N�g�p�̕ϐ�
{
	/*�C���X�^���X�錾�i�R���|�[�l���g�j*/
	for (int i = 0; i < SCENESYSTEMTITLE::OBJECTNUM; i++)
	{
		AddComponent<ComponentTransform>();
		m_transform.push_back(GetComponent<ComponentTransform>());//�����ɗv�f��ǉ�

		AddComponent<ComponentGraph>(m_transform[i]);//�������Q��
		m_graph.push_back(GetComponent<ComponentGraph>());//�����ɗv�f��ǉ�
	}
	

	/*�C���X�^���X�錾*/
	m_uiManager = std::make_shared<UIManager>();//UI�}�l�[�W��
	m_inputManager = std::make_shared<InputManager>();//���̓}�l�[�W��
}

SceneSystemTitle::~SceneSystemTitle()
{

}

void SceneSystemTitle::Init()
{
	/*�ϐ�������*/
	m_selectedCellX = 0;//�G�f�B�^�[�p�̑I�����WX
	m_selectedCellY = 0;//�G�f�B�^�[�p�̑I�����WY	
	m_currentSelect = eSelect_NEWGAME;//�����̑I����
	m_fadeCount = 0;//�t�F�[�h�G�t�F�N�g�p�̕ϐ�

	/*�C���X�^���X������*/
	m_uiManager->Init();
	m_inputManager->Init();

	/*�R���|�[�l���g������*/
	Entity::InitComponent();
	
	/*NewGame*/
	m_transform[0]->position = VGet(0, -14, 0);
	m_graph[0]->LoadGraph("../Data/Asset/2D/SceneTitle/NewGame.png");
	
	/*LoadGame*/
	m_transform[1]->position = VGet(0, -15, 0);
	m_graph[1]->LoadGraph("../Data/Asset/2D/SceneTitle/LoadGame.png");
	
	/*Back*/
	m_transform[2]->position = VGet(0, -15, 0);
	m_graph[2]->LoadGraph("../Data/Asset/2D/SceneTitle/back.png");

	/*�w�i*/
	m_transform[3]->position = VGet(0, 0, 0);
	m_graph[3]->LoadGraph("../Data/Asset/2D/SceneTitle/backGround.png");

	/*��I��*/
	m_transform[4]->position = VGet(0, 0, 0);
	m_graph[4]->LoadGraph("../Data/Asset/2D/SceneTitle/TitleSelect.png");

	/*�Q�[�����S*/
	m_transform[5]->position = VGet(0, 0, 0);
	m_graph[5]->LoadGraph("../Data/Asset/2D/SceneTitle/TitleRogo.png");

	/*���[�h�̃e�X�g�p�ɕ��ׂ������Ă��܂�*/
	for (int i = 7; i < SCENESYSTEMTITLE::OBJECTNUM; i++)
	{
		m_transform[i]->position = VGet(i * 10, 0, 0);
		m_graph[i]->LoadGraph("../Data/Asset/2D/SceneTitle/add_0.png");
	}


}

void SceneSystemTitle::Update()
{
	/*�C���X�^���X�X�V*/
	m_inputManager->Update();
	
	/*�O��̑I������ۑ�*/
	auto previouseSelect = m_currentSelect;

	/*�R���|�[�l���g�X�V*/
	for (int i = 0; i < SCENESYSTEMTITLE::OBJECTNUM; i++)
	{
		m_transform[i]->Update();
		m_graph[i]->Update();
	}

	/*�Z���N�g�̍X�V*/
	m_uiManager->m_select->UpSelect(m_currentSelect, eSelect_ObjectNum, m_inputManager->m_joyPad->isDUP == true);
	m_uiManager->m_select->DownSelect(m_currentSelect, eSelect_ObjectNum, m_inputManager->m_joyPad->isDDOWN == true);
	
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
	
}

void SceneSystemTitle::Draw()
{
	
	for (int i = 0; i < SCENESYSTEMTITLE::OBJECTNUM; i++)
	{
		if (i > 2)
		{
			m_transform[i]->Draw();
			m_graph[i]->Draw();	
		}
	}

	DrawCurrentSelect();

	if (m_currentSelect == eSelect_NEWGAME)
	{
		DrawString(0, 0, "newGame", 0xff0000);
	}
	if (m_currentSelect == eSelect_LOADGAME)
	{
		DrawString(0, 0, "loadGame", 0xff0000);
	}
	if (m_currentSelect == eSelect_BACK)
	{
		DrawString(0, 0, "back", 0xff0000);
	}


}

void SceneSystemTitle::Final()
{
	for (int i = 0; i < SCENESYSTEMTITLE::OBJECTNUM; i++)
	{
		m_transform[i]->Final();
		m_graph[i]->Final();
	}
	
}

void SceneSystemTitle::DrawGrid(int _width, int _height, int _cellSize)
{
	for (int x = 0; x <= _width; x += _cellSize)
	{
		DrawLine(x, 0, x, _height, 0xffffff, true);
	}
	for (int y = 0; y <= _height; y += _cellSize)
	{
		DrawLine(0, y, _width, y, 0xffffff, true);
	}
}

void SceneSystemTitle::UpdateSelectedCell(int _mouseX, int _mouseY, int _cellSize)
{
	m_selectedCellX = _mouseX / _cellSize;
	m_selectedCellY = _mouseY / _cellSize;
}

void SceneSystemTitle::DrawSelectedCell(int _cellSize)
{
	if (m_selectedCellX >= 0 && m_selectedCellY >= 0)
	{
		int x = m_selectedCellX * _cellSize;
		int y = m_selectedCellY * _cellSize;
		DrawBox(x, y, x + _cellSize, y + _cellSize, 0xff0000, true);
	}
}

void SceneSystemTitle::DrawCurrentSelect()
{
	switch (m_currentSelect)
	{
	case eSelect_NEWGAME:
		m_graph[0]->FadeEffectDraw(m_fadeCount);
		break;
	case eSelect_LOADGAME:
		m_graph[1]->FadeEffectDraw(m_fadeCount);
		break;
	case eSelect_BACK:
		m_graph[2]->FadeEffectDraw(m_fadeCount);
		break;
	}
	
}