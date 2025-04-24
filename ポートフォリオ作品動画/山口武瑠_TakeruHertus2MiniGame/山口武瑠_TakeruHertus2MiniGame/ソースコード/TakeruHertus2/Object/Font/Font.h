#pragma once
#include "../Entity/Entity.h"
#include "../../UI/Easing/Easing.h"

namespace FONT
{
	static constexpr int FontNum = 1;
}

class Font : public Entity
{
private:
	std::vector<std::shared_ptr<ComponentFont>> m_font;
	std::vector<std::shared_ptr<ComponentTransform>> m_transform;
	Easing m_easing;


	int m_esingTime = 0;

public:
	Font();
	~Font();

	void Init();
	void Update();
	void Draw();
	void Final();


};

