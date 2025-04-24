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
/// ���j���[�S�ʂ̏����𐿂�����(SaveMenu,GameMenu)
/// </summary>
class MenuSystem : public Entity
{
private:
	/*�C���X�^���X�錾*/
	std::shared_ptr<InputManager> m_Idm;
	std::shared_ptr<UIManager> m_UI;
	
	/*�C���X�^���X�錾�F�R���|�[�l���g*/
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
	// �Z�b�^�[�Q�b�^�[
	//======================================================================

	/*���j���J�t���O*/
	void SetIsMenuOpen(const bool& _isMenuOpen) { m_isMenuOpen = _isMenuOpen; }//���j���J�t���O���Z�b�g
	bool GetIsMenuOpen() const { return m_isMenuOpen; }//���j���J�t���O���擾

	
};

