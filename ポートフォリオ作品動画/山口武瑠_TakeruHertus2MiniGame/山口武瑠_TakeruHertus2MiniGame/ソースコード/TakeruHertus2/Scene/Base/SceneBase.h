#pragma once
#include "SceneType.h"
#include <EffekseerForDXLib.h>
#include <DxLib.h>
#include <memory>
#include "../../InputDevice/InputManager.h"

/// <summary>
/// シーンのベース
/// </summary>
class SceneBase
{
protected:
	//ここで入力デバイスのインスタンスを作成して継承先のクラスでインスタンス化せずに扱う
	std::shared_ptr<InputManager> m_Idm;

public:
	SceneBase();
	virtual ~SceneBase() {}

	virtual void Init() {}
	virtual void Update() {}
	virtual void Draw() {}
	virtual void Final() {}
};