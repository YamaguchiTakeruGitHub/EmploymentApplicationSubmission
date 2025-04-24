#pragma once
#include "../Base/SceneBase.h"
#include "../../Object/SceneSystem/SceneSystemTitle/SceneSystemTitle.h"

#include "../../Object/Font/Font.h"

class SceneTitle : public SceneBase
{
private:
	std::shared_ptr<SceneSystemTitle> m_systemTitle;
	std::shared_ptr<Font> m_font;

	
	/*変数宣言*/
	bool m_isLoading;

public:
	SceneTitle();
	~SceneTitle();

	void Init() override;
	void Update() override;
	void Draw() override;
	void Final() override;
};



/*タイトル導入の流れ*/
//キャラクターイラストか3Dのモデルが挿絵で入り、タイトル画面にフェードインする