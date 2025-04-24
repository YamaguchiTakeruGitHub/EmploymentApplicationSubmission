#include "Command.h"

void Command::CheckCommand()
{
	if (m_Idm->m_joyPad->isB == true)
	{
		switch (m_currentSelect)
		{
		case eSelect_Attack:
			m_isAttack = true;
			break;

		case eSelect_Magic:
			m_isMagic = true;
			break;

		case eSelect_Item:
			m_isItem = true;
			break;

		case eSelect_Menu:
			m_isMenu = true;
			break;
		}
	}
	else
	{
		/*Œˆ’èƒ{ƒ^ƒ“‚ª“ü—Í‚³‚ê‚Ä‚¢‚È‚¢ê‡‚Íƒtƒ‰ƒO‚ð‚¨‚ë‚·*/
		m_isAttack	 = false;
		m_isMagic	 = false;
		m_isItem	 = false;
		m_isMenu	 = false;
	}



	if (m_isSpecialCommands == true)
	{
		if (m_Idm->m_joyPad->isY == true)
		{

		}
	}
}

Command::Command()
	: m_currentSelect(eSelect_Attack)
{
	for (int i = 0; i < CommandParameter::CommandNum; i++)
	{
		AddComponent<ComponentTransform>();
		m_transform.push_back(GetComponent<ComponentTransform>());

		AddComponent<ComponentGraph>(m_transform[i]);
		m_graph.push_back(GetComponent<ComponentGraph>());
	}

	m_Idm = std::make_shared<InputManager>();

	m_UI = std::make_shared<UIManager>();
}

void Command::Init()
{
	m_currentSelect = eSelect_Attack;
	m_UI->Init();
	m_Idm->Init();


	Entity::InitComponent();

	/*NewGame*/
	m_transform[0]->position = VGet(0, -14, 0);
	m_graph[0]->LoadGraph("");

	/*LoadGame*/
	m_transform[1]->position = VGet(0, -15, 0);
	m_graph[1]->LoadGraph("");

	/*Back*/
	m_transform[2]->position = VGet(0, -15, 0);
	m_graph[2]->LoadGraph("");

	/*”wŒi*/
	m_transform[3]->position = VGet(0, 0, 0);
	m_graph[3]->LoadGraph("");
}

void Command::Update()
{
	m_Idm->Update();

	/*m_isAttack = false;
	m_isMagic = false;
	m_isItem = false;
	m_isMenu = false;*/
	
	for (int i = 0; i < CommandParameter::CommandNum; i++)
	{
		m_transform[i]->Update();
		m_graph[i]->Update();
	}

	m_UI->m_select->UpSelect(m_currentSelect, eSelect_ObjectNum, m_Idm->m_joyPad->isDUP ==  true);
	m_UI->m_select->DownSelect(m_currentSelect, eSelect_ObjectNum, m_Idm->m_joyPad->isDDOWN == true);

	CheckCommand();
}

void Command::Draw()
{
	Entity::DrawComponent();

//#ifdef _DEBUG
//	if(m_currentSelect == eSelect_Attack) DrawString(20, 200, "AttackCommand", 0xffffff);
//	if (m_currentSelect == eSelect_Magic) DrawString(20, 200, "MagicCommand", 0xffffff);
//	if (m_currentSelect == eSelect_Item) DrawString(20, 200, "ItemCommand", 0xffffff);
//	if (m_currentSelect == eSelect_Menu) DrawString(20, 200, "MenuCommand", 0xffffff);
//	
//	if (m_isAttack == true) DrawString(20, 200, "AttackCommand", 0xff0000);
//	if (m_isMagic == true) DrawString(20, 200, "MagicCommand", 0xff0000);
//	if (m_isItem == true) DrawString(20, 200, "ItemCommand", 0xff0000);
//	if (m_isMenu == true) DrawString(20, 200, "MenuCommand", 0xff0000);
//
//	if (m_isSpecialCommands == true)
//	{
//		DrawString(0, 180, "ActionCommand!!", 0xff0000);
//	}
//
//#endif // _DEBUG

}

void Command::Final()
{
	Entity::FinalComponent();
}
