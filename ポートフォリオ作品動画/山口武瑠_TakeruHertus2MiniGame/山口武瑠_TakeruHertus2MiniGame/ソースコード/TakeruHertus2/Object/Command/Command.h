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
	/*�C���X�^���X�錾�F�R���|�[�l���g*/
	std::vector<std::shared_ptr<ComponentTransform>> m_transform;
	std::vector<std::shared_ptr<ComponentGraph>> m_graph;
	
	/*�C���X�^���X�錾*/
	std::shared_ptr<UIManager> m_UI;
	std::shared_ptr<InputManager> m_Idm;

	/*�ϐ����֐��錾*/
	void CheckCommand();


	//�I���R�}���h�̎��
	typedef enum
	{
		eSelect_Attack,
		eSelect_Magic,
		eSelect_Item,
		eSelect_Menu,
		eSelect_ObjectNum
	}eSelect;


	bool m_isAttack;//�A�^�b�N�R�}���h�̑I���t���O
	bool m_isMagic;	//�}�W�b�N�R�}���h�̑I���t���O
	bool m_isItem;	//�A�C�e���R�}���h�̑I���t���O
	bool m_isMenu;	//���j���[�R�}���h�̑I���t���O

	bool m_isSpecialCommands;//����R�}���h�̃t���O

	int m_currentSelect;	//���݂̑I��

public:
	Command();

	void Init();
	void Update();
	void Draw();
	void Final();

	//===============================================================
	// �Z�b�^�[�Q�b�^�[
	//===============================================================
	void SetIsSpecialCommands(const bool& _isSpecialCommands) { m_isSpecialCommands = _isSpecialCommands; }
	bool GetIsSpecialCommands() const { return m_isSpecialCommands; }

	bool GetIsAttack() const { return m_isAttack; }
	bool GetIsMagic() const { return m_isMagic; }
	bool GetIsItem() const { return m_isItem; }
	bool GetIsMenu() const { return m_isMenu; }

};

