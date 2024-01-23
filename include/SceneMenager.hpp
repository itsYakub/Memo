#pragma once

#include "Scene.hpp"

class SceneMenager {
private:
    Scene* m_CurrentScene;

    SceneMenager();
    ~SceneMenager();
public:
    static SceneMenager& Get() { static SceneMenager instance; return instance; }

    void LoadScene(Scene* scene);
    void UnloadScene();
    void UpdateScene();
    void RenderScene();
};