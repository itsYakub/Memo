#pragma once

#include "MatchTable.hpp"
#include "Scene.hpp"

#include "Timer.hpp"

class SceneGameplay : public Scene {
private:
    enum GameplayState {
        STATE_COUNTDOWN = 0,
        STATE_GAMEPLAY,
        STATE_COMPLETE,
        STATE_PAUSED
    };

    MatchTable m_MatchTable;

    const float COUNTDOWN_TIME = 3.0f;
    Timer m_CountdownTimer;
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