#pragma once

#include "Scene.hpp"

#include "Timer.hpp"

class SceneSplashScreen : public Scene {
private:
    Timer m_SplashScreenTimer;

public:
    SceneSplashScreen();
    void Init() override;
    void Destroy() override;
    void Update() override;
    void Render() override;
};