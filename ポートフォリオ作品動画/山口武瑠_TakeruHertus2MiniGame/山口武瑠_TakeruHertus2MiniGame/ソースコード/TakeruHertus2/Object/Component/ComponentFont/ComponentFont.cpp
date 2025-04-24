#include "ComponentFont.h"
#include "../../../Object/GameTag.h"

ComponentFont::ComponentFont(std::shared_ptr<ComponentTransform> _transform)
	: m_transform(_transform)
	, m_fontHandle(-1)
{
}

ComponentFont::~ComponentFont()
{
}

void ComponentFont::LoadFont(const char* _path, int _fontSize, int _fontThick)
{
	m_fontHandle = CreateFontToHandle(_path, _fontSize, _fontThick, DX_FONTTYPE_NORMAL);
}

void ComponentFont::Init()
{
}

void ComponentFont::Update()
{
}

void ComponentFont::Draw()
{
	
	DrawStringToHandle(m_transform->position.x, m_transform->position.y, m_letter, 0xffffff, m_fontHandle);
	
}

void ComponentFont::Final()
{
	//フォントハンドルに何かしら入っていれば
	if (m_fontHandle != -1)
	{
		DeleteFontToHandle(m_fontHandle);//ハンドルを削除する
	}
}
