#pragma once
#include "../../Base/SceneBase.h"
#include "../../../InputDevice/InputManager.h"
#include "../../../Object/SceneSystem/MiniGameTitleSystem/SceneSystem_MiniGame_Title.h"

class MiniGameTitleScene : public SceneBase
{
private:
    std::shared_ptr<SceneSystem_MiniGame_Title> m_titleSystem;
    bool m_isLoading;//ÉçÅ[ÉhíÜÇ©Ç«Ç§Ç©


public:

    MiniGameTitleScene();
    ~MiniGameTitleScene();

    void Init() override;
    void Update() override;
    void Draw() override;
    void Final() override;
 
private:
    void DrawLoadinBar();
    float GetLoadingProgress();
	

};

