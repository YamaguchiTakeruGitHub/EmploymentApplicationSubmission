#pragma once
#include "../Entity/Entity.h"
#include "../../InputDevice/InputManager.h"
#include "../../UI/UIManager.h"

namespace CommandParameter
{
	static constexpr int CommandNum = 4;
}

class Command : public Entity
{
private:
	/*インスタンス宣言：コンポーネント*/
	std::vector<std::shared_ptr<ComponentTransform>> m_transform;
	std::vector<std::shared_ptr<ComponentGraph>> m_graph;
	
	/*インスタンス宣言*/
	std::shared_ptr<UIManager> m_UI;
	std::shared_ptr<InputManager> m_Idm;

	/*変数＆関数宣言*/
	void CheckCommand();


	//選択コマンドの種類
	typedef enum
	{
		eSelect_Attack,
		eSelect_Magic,
		eSelect_Item,
		eSelect_Menu,
		eSelect_ObjectNum
	}eSelect;


	bool m_isAttack;//アタックコマンドの選択フラグ
	bool m_isMagic;	//マジックコマンドの選択フラグ
	bool m_isItem;	//アイテムコマンドの選択フラグ
	bool m_isMenu;	//メニューコマンドの選択フラグ

	bool m_isSpecialCommands;//特殊コマンドのフラグ

	int m_currentSelect;	//現在の選択

public:
	Command();

	void Init();
	void Update();
	void Draw();
	void Final();

	//===============================================================
	// セッターゲッター
	//===============================================================
	void SetIsSpecialCommands(const bool& _isSpecialCommands) { m_isSpecialCommands = _isSpecialCommands; }
	bool GetIsSpecialCommands() const { return m_isSpecialCommands; }

	bool GetIsAttack() const { return m_isAttack; }
	bool GetIsMagic() const { return m_isMagic; }
	bool GetIsItem() const { return m_isItem; }
	bool GetIsMenu() const { return m_isMenu; }

};

