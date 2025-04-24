#pragma once
#include "KeyBoard/KeyBoard.h"
#include "JoyPad/JoyPad.h"
#include <memory>

/*入力デバイスのマネージャー*/
class InputManager
{
public:
	InputManager();
	~InputManager();

	void Init();	//入力デバイスの初期化
	void Update();	//入力デバイスの更新

	std::shared_ptr<KeyBoard> m_keyboard;//キーボード
	std::shared_ptr<JoyPad> m_joyPad;	 //コントローラー
};

