#pragma once

#include <memory>

#include "Scene.hpp"

class SceneMenager {
private:
    std::unique_ptr<Scene> m_CurrentScene;

    SceneMenager();
    ~SceneMenager();
public:
    static SceneMenager& Get() { static SceneMenager instance; return instance; }

    void LoadScene(std::unique_ptr<Scene> scene);
    void UnloadScene();
    void UpdateScene();
    void RenderScene();
};