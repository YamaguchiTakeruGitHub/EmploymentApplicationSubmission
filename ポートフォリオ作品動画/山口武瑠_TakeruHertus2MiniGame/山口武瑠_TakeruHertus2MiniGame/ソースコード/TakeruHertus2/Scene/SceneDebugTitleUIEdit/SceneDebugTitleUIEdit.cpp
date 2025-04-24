#include "SceneDebugTitleUIEdit.h"
#include "../../CSVLib/CsvData_Reading_And_Writing_Equipment.h"


SceneDebugTitleUIEdit::SceneDebugTitleUIEdit()
	: m_isMenu(false)
	, m_isAttachGraph()
	, m_resourceNum{-1,-1,-1,-1-1,-1,-1}
	, m_resourcePos()
	, m_resourceGraphPos()
	, m_resourceHitColor()
{
	m_systemTitle = std::make_shared<SceneSystemTitle>();
	m_Idm = std::make_shared<InputManager>();
}

SceneDebugTitleUIEdit::~SceneDebugTitleUIEdit()
{
}

void SceneDebugTitleUIEdit::Init()
{
	m_systemTitle->Init();
	m_isMenu = false;

	for (int i = 0; i < TITLEUINUMBER::RESOURCENUM; i++)
	{
		m_isAttachGraph[i] = false;
		m_resourcePos[i] = VGet(0, 0, 0);

		m_resourceHitColor[i] = 0x000000;
	}


	m_resourceNum[0] = LoadGraph("../Data/Asset/2D/SceneTitle/add_0.png");
	m_resourceNum[1] = LoadGraph("../Data/Asset/2D/SceneTitle/add_1.png");
	m_resourceNum[2] = LoadGraph("../Data/Asset/2D/SceneTitle/add_2.png");
	m_resourceNum[3] = LoadGraph("../Data/Asset/2D/SceneTitle/add_3.png");
	m_resourceNum[4] = LoadGraph("../Data/Asset/2D/SceneTitle/add_4.png");
	m_resourceNum[5] = LoadGraph("../Data/Asset/2D/SceneTitle/add_5.png");
	m_resourceNum[6] = LoadGraph("../Data/Asset/2D/SceneTitle/add_6.png");


	
	m_resourcePos[0] = VGet(220, 120, 0);
	m_resourcePos[1] = VGet(220, 140, 0);
	m_resourcePos[2] = VGet(220, 160, 0);
	m_resourcePos[3] = VGet(220, 180, 0);
	m_resourcePos[4] = VGet(220, 200, 0);
	m_resourcePos[5] = VGet(220, 220, 0);
	m_resourcePos[6] = VGet(220, 240, 0);

}

void SceneDebugTitleUIEdit::Update()
{
	
	GetMousePoint(&mouseX, &mouseY);
	m_systemTitle->UpdateSelectedCell(mouseX, mouseY, 20);

	if (m_isMenu == true)
	{
		UpdateMenuHitSelect();//選択肢の当たり判定

		
		/*離したらメニュを閉じる*/
		if (CheckHitKey(KEY_INPUT_SPACE) != 1)
		{
			m_isMenu = false;
		}
	}
	else
	{
		m_systemTitle->Update();
		for (int i = 0; i < TITLEUINUMBER::RESOURCENUM; i++)
		{
			if (m_isAttachGraphNumber[i] == true)
			{
				UpdateMenuAttachSelect(i);//選択したUIを配置する処理
			}
		}

		/*押したらメニュを開く*/
		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			m_isMenu = true;
		}
	}
}

void SceneDebugTitleUIEdit::Draw()
{
	m_systemTitle->DrawGrid(GAMECONSTANT::k_WindowWidth, GAMECONSTANT::k_WindowHeigth, 20);
	m_systemTitle->DrawSelectedCell(20);
	if (m_isMenu == true)
	{
		DrawBox(200, 100, 1000, 500, 0xffffff, true);
		DrawBox(600, 150, 900, 400, 0x00ff00, true);

		DrawMenuString();
		DrawMenuHitDebug();
		for (int i = 0; i < TITLEUINUMBER::RESOURCENUM; i++)
		{
			if (m_isMenuHitString[i])
			{
				DrawGraph(650, 200, m_resourceNum[i], true);
			}
		}
	}    
	else
	{
		DrawGraph(m_resourceGraphPos[0].x, m_resourceGraphPos[0].y, m_resourceNum[0], true);
	}
}

void SceneDebugTitleUIEdit::Final()
{
	m_systemTitle->Final();
}

void SceneDebugTitleUIEdit::UpdateMenuHitSelect()
{
	for (int i = 0; i < TITLEUINUMBER::RESOURCENUM; i++)
	{
		if (mouseX >= m_resourcePos[i].x && mouseX <= m_resourcePos[i].x + 60 &&
			mouseY >= m_resourcePos[i].y && mouseY <= m_resourcePos[i].y + 15)
		{
			DrawString(0, 0, "Hit", 0xff0000);
			m_resourceHitColor[i] = 0xff0000;
			m_isMenuHitString[i] = true;

			if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
			{
				m_isAttachGraphNumber[i] = true;
			}


		}
		else
		{
			m_resourceHitColor[i] = 0x000000;
			m_isMenuHitString[i] = false;
		}

	}
}

void SceneDebugTitleUIEdit::UpdateMenuAttachSelect(int _attachNum)
{
	for (int i = 0; i < TITLEUINUMBER::RESOURCENUM; i++)
	{
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
		{
			m_isAttachGraph[i] = true;
		}

		if (m_isAttachGraph[i] == false)
		{
			m_resourceGraphPos[i] = VGet(mouseX, mouseY, 0);
			m_resourceCurrentPos[i] = m_resourceGraphPos[i];
		}
		else
		{
			m_resourceGraphPos[i] = VGet(m_resourceCurrentPos[i].x, m_resourceCurrentPos[i].y, 0);

		}
	}

}

void SceneDebugTitleUIEdit::DrawMenuString()
{
	DrawString(m_resourcePos[0].x, m_resourcePos[0].y, "Graph_1", m_resourceHitColor[0]);
	DrawString(m_resourcePos[1].x, m_resourcePos[1].y, "Graph_2", m_resourceHitColor[1]);
	DrawString(m_resourcePos[2].x, m_resourcePos[2].y, "Graph_3", m_resourceHitColor[2]);
	DrawString(m_resourcePos[3].x, m_resourcePos[3].y, "Graph_4", m_resourceHitColor[3]);
	DrawString(m_resourcePos[4].x, m_resourcePos[4].y, "Graph_5", m_resourceHitColor[4]);
	DrawString(m_resourcePos[5].x, m_resourcePos[5].y, "Graph_6", m_resourceHitColor[5]);
	DrawString(m_resourcePos[6].x, m_resourcePos[6].y, "Graph_7", m_resourceHitColor[6]);
}

void SceneDebugTitleUIEdit::DrawMenuHitDebug()
{
	DrawBox(m_resourcePos[0].x, m_resourcePos[0].y, m_resourcePos[0].x + 60, m_resourcePos[0].y + 15, 0xff0000, false);
	DrawBox(m_resourcePos[1].x, m_resourcePos[1].y, m_resourcePos[1].x + 60, m_resourcePos[1].y + 15, 0xff0000, false);
	DrawBox(m_resourcePos[2].x, m_resourcePos[2].y, m_resourcePos[2].x + 60, m_resourcePos[2].y + 15, 0xff0000, false);
	DrawBox(m_resourcePos[3].x, m_resourcePos[3].y, m_resourcePos[3].x + 60, m_resourcePos[3].y + 15, 0xff0000, false);
	DrawBox(m_resourcePos[4].x, m_resourcePos[4].y, m_resourcePos[4].x + 60, m_resourcePos[4].y + 15, 0xff0000, false);
	DrawBox(m_resourcePos[5].x, m_resourcePos[5].y, m_resourcePos[5].x + 60, m_resourcePos[5].y + 15, 0xff0000, false);
	DrawBox(m_resourcePos[6].x, m_resourcePos[6].y, m_resourcePos[6].x + 60, m_resourcePos[6].y + 15, 0xff0000, false);
}