#include "SceneBase.h"

SceneBase::SceneBase()
{
	//入力デバイスのインスタンス化
	m_Idm = std::make_shared<InputManager>();
}
