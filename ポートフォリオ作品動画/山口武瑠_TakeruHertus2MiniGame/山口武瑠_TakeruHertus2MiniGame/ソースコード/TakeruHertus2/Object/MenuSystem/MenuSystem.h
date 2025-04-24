#pragma once
#include "../Entity/Entity.h"
#include "../../InputDevice/InputManager.h"
#include "../../UI/UIManager.h"

namespace MENUSYSTEM
{
	static constexpr int MenuObjectNum = 1;
	static constexpr int MenuItemsNum = 5;
}

/// <summary>
/// メニュー全般の処理を請け負う(SaveMenu,GameMenu)
/// </summary>
class MenuSystem : public Entity
{
private:
	/*インスタンス宣言*/
	std::shared_ptr<InputManager> m_Idm;
	std::shared_ptr<UIManager> m_UI;
	
	/*インスタンス宣言：コンポーネント*/
	std::vector<std::shared_ptr<ComponentTransform>> m_transform;
	std::vector<std::shared_ptr<ComponentGraph>> m_graph;

	bool m_isMenuOpen;


	

public:
	MenuSystem();
	~MenuSystem();
	void Init();
	void Update();
	void Draw();
	void Final();

	//======================================================================
	// セッターゲッター
	//======================================================================

	/*メニュ開閉フラグ*/
	void SetIsMenuOpen(const bool& _isMenuOpen) { m_isMenuOpen = _isMenuOpen; }//メニュ開閉フラグをセット
	bool GetIsMenuOpen() const { return m_isMenuOpen; }//メニュ開閉フラグを取得

	
};

