#pragma once

#include "Scene.hpp"

class SceneSettings : public Scene {    
private:
    enum SceneSettingSection {
        SECTION_GAMEPLAY,
        SECTION_IO,
    };

    SceneSettingSection m_SettingSection;
    int m_CurrentSettingSection;

public:
    SceneSettings();
    void Init() override;
    void Destroy() override;
    void Update() override;
    void Render() override;
};