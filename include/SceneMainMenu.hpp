#pragma once

#include "Scene.hpp"

class SceneMainMenu : public Scene {
private:

public:
    SceneMainMenu();
    void Init() override;
    void Destroy() override;
    void Update() override;
    void Render() override;
};