#pragma once
#include "../Base/SceneBase.h"
#include "../../Object/SceneSystem/SceneSystemTitle/SceneSystemTitle.h"
#include "../../InputDevice/InputManager.h"

namespace TITLEUINUMBER
{
	static constexpr int RESOURCENUM = 7;//タイトルで扱うリソースの数
}

class SceneDebugTitleUIEdit : public SceneBase
{
private:
	std::shared_ptr<InputManager> m_Idm;
	std::shared_ptr<SceneSystemTitle> m_systemTitle;

	int mouseX, mouseY;//マウス
	
	/*変数宣言*/
	bool m_isMenu;//メニュが開かれているか
	bool m_isAttachGraph[TITLEUINUMBER::RESOURCENUM];
	bool m_isMenuHitString[TITLEUINUMBER::RESOURCENUM];
	bool m_isAttachGraphNumber[TITLEUINUMBER::RESOURCENUM];

	int m_resourceNum[TITLEUINUMBER::RESOURCENUM];		//使用するリソースの数
	int m_resourceHitColor[TITLEUINUMBER::RESOURCENUM];//メニュー画面の文字の色


	VECTOR m_resourcePos[TITLEUINUMBER::RESOURCENUM];	//リソースの座標
	VECTOR m_resourceGraphPos[TITLEUINUMBER::RESOURCENUM];	//リソースの座標

	VECTOR m_resourceCurrentPos[TITLEUINUMBER::RESOURCENUM];

	void UpdateMenuHitSelect();
	void UpdateMenuAttachSelect(int _attachNum);

	void DrawMenuString();
	void DrawMenuHitDebug();

public:
	SceneDebugTitleUIEdit();
	~SceneDebugTitleUIEdit()override;

	void Init() override;
	void Update() override;
	void Draw() override;
	void Final() override;
};

