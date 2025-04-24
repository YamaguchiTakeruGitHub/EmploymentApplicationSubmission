#pragma once
#include "../../Entity/Entity.h"
#include "../../../UI/UIManager.h"
#include "../../../InputDevice/InputManager.h"

class SceneSystem_MiniGame_Title : public Entity
{
private:
    std::vector<std::shared_ptr<ComponentTransform>> m_transforms;
    std::vector<std::shared_ptr<ComponentGraph>> m_graphs;

    std::shared_ptr<InputManager> m_Idm;
    std::shared_ptr<UIManager> m_UI;

    //�I�����̎��
    typedef enum
    {
        eSelect_MiniGame_1,	//�V�K�Q�[��
        eSelect_MiniGame_2,	//���[�h
        eSelect_MiniGame_3,		//�߂�
        eSelect_ObjectNum	//�I�����̐�-1
    }eSelect;

    //�I�𒆂̑I����
    int m_currentSelect;

    //�I�𒆂̍��W
    VECTOR m_currentSelectPos;

    //�t�F�[�h�G�t�F�N�g�p�̕ϐ��i�����I�ɂ͕ʂ̃N���X�Ɏʂ������j
    int m_fadeCount;

    int m_push_B_DELAY;

public:
    SceneSystem_MiniGame_Title();

    void Init();
    void Update();
    void Draw();
    void Final();

private:
    void Update_SelectChengeScene();
    void Draw_FadeGraphs();

};

