#pragma once
#include "../../Entity/Entity.h"
#include "../../../UI/UIManager.h"
#include "../../../InputDevice/InputManager.h"

namespace SCENESYSTEMTITLE
{
	static constexpr int OBJECTNUM = 10000;//���[�h��ʂ̊m�F�����邽�߂ɂ����ĕ��ׂ�������
	//static constexpr int OBJECTNUM =4;
}

class SceneSystemTitle : public Entity
{
private:
	/*�C���X�^���X�錾�i�R���|�[�l���g�j*/
	std::vector<std::shared_ptr<ComponentTransform>> m_transform;
	std::vector<std::shared_ptr<ComponentGraph>> m_graph;

	/*�C���X�^���X�錾*/
	std::shared_ptr<UIManager> m_uiManager;//UI�}�l�[�W��
	std::shared_ptr<InputManager> m_inputManager;//���̓}�l�[�W��

	/*�ϐ��錾*/
	int m_selectedCellX;
	int m_selectedCellY;
	
	//�I�����̎��
	typedef enum
	{
		eSelect_NEWGAME,	//�V�K�Q�[��
		eSelect_LOADGAME,	//���[�h
		eSelect_BACK,		//�߂�
		eSelect_ObjectNum	//�I�����̐�-1
	}eSelect;

	//�I�𒆂̑I����
	int m_currentSelect;
	
	//�I�𒆂̍��W
	VECTOR m_currentSelectPos;

	//�t�F�[�h�G�t�F�N�g�p�̕ϐ��i�����I�ɂ͕ʂ̃N���X�Ɏʂ������j
	int m_fadeCount;

public:
	SceneSystemTitle();
	~SceneSystemTitle();

	void Init();
	void Update();
	void Draw();
	void Final();

	void DrawGrid(int width, int height, int cellSize);
	void UpdateSelectedCell(int _mouseX, int _mouseY, int _cellSize);
	void DrawSelectedCell(int _cellSize);

private:
	void DrawCurrentSelect();

};

