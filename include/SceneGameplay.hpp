#pragma once

#include "MatchTable.hpp"
#include "Scene.hpp"

class SceneGameplay : public Scene {
private:
    enum GameplayState {
        STATE_GAMEPLAY = 0,
        STATE_COMPLETE,
        STATE_PAUSED
    };

    MatchTable m_MatchTable;
    float m_GameTime;

    GameplayState m_GameplayState;

public:
    SceneGameplay(const MatchTableDifficulty difficulty);
    ~SceneGameplay() override;
    void Init() override;
    void Destroy() override;
    void Update() override;
    void Render() override;
};