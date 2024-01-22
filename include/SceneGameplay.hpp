#pragma once

#include "Scene.hpp"

#include "raylib.h"

#include "Window.hpp"
#include "MatchTable.hpp"

class SceneGameplay : public Scene {
private:
    Window* window;
    MatchTable m_MatchTable;

public:
    void Init(Window* window) override;
    void Destroy() override;
    void Update() override;
    void Render() override;
};