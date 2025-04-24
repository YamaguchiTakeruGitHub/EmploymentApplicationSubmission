#include "Font.h"
#include "../GameTag.h"

Font::Font()
{
	for (int i = 0; i < FONT::FontNum; i++)
	{
		AddComponent<ComponentTransform>();
		m_transform.push_back(GetComponent<ComponentTransform>());

		AddComponent<ComponentFont>(m_transform[i]);
		m_font.push_back(GetComponent<ComponentFont>());
	}
}

Font::~Font()
{
}

void Font::Init()
{
	Entity::InitComponent();

	m_transform[0]->position = VGet(350, 0, 0);
	m_font[0]->SetFontLetter("NowLoading...");
	m_font[0]->LoadFont("‹àá`Žš Normal", 10, 7);
}

void Font::Update()
{
	Entity::UpdateComponent();

	if (m_esingTime >= 500)
	{
		m_esingTime = 0;
	}
	else
	{
		m_esingTime+=5;
	}
	
	m_transform[0]->position.y = m_easing.InCubic(m_esingTime, 500, 750, 200);
}

void Font::Draw()
{
	Entity::DrawComponent();
}

void Font::Final()
{
	Entity::FinalComponent();
}
