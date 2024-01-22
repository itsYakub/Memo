#pragma once

#include "MatchTable.hpp"
#include "Scene.hpp"
#include "Window.hpp"

class SceneGameplay : public Scene {
private:
    MatchTable m_MatchTable;

public:
    SceneGameplay(const MatchTableDifficulty difficulty);
    void Init() override;
    void Destroy() override;
    void Update() override;
    void Render() override;
};