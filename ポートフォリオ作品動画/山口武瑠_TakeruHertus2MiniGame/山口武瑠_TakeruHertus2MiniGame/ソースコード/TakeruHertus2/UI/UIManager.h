#pragma once
#include "Select/Select.h"
#include <memory>

class UIManager
{
public:
	UIManager();
	~UIManager();

	void Init();
	
	std::shared_ptr<Select> m_select;

};

