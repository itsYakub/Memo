#pragma once

#include <array>

#include "Scene.hpp"

class SceneMainMenu : public Scene {    
private:
    enum MainMenuState { 
        STATE_DEFAULT = 0,
        STATE_LEVEL_CHOOSING
    };

    MainMenuState m_MainMenuState;

public:
    SceneMainMenu();
    void Init() override;
    void Destroy() override;
    void Update() override;
    void Render() override;
};