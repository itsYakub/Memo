#pragma once

#include "Scene.hpp"

class SceneMenager {
private:
    Scene* m_CurrentScene;

    SceneMenager() = default;
    ~SceneMenager() = default;
public:
    static SceneMenager& Get() { static SceneMenager instance; return instance; }

    void LoadScene(Scene* scene);
    void UnloadScene();
    void UpdateScene();
    void RenderScene();
};