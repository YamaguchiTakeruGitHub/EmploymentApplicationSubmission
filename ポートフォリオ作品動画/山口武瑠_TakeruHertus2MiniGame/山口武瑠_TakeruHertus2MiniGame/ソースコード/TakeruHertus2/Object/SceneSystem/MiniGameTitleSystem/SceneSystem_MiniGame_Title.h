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

    //選択肢の種類
    typedef enum
    {
        eSelect_MiniGame_1,	//新規ゲーム
        eSelect_MiniGame_2,	//ロード
        eSelect_MiniGame_3,		//戻る
        eSelect_ObjectNum	//選択肢の数-1
    }eSelect;

    //選択中の選択肢
    int m_currentSelect;

    //選択中の座標
    VECTOR m_currentSelectPos;

    //フェードエフェクト用の変数（将来的には別のクラスに写したい）
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

