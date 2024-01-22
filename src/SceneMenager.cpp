#include "SceneMenager.hpp"

#include "Scene.hpp"

void SceneMenager::LoadScene(Scene* scene) {
        if(m_CurrentScene != nullptr) UnloadScene();

        m_CurrentScene = scene;
        m_CurrentScene->Init();
    }

void SceneMenager::UnloadScene() {
    m_CurrentScene->Destroy();
    m_CurrentScene = nullptr;
}

void SceneMenager::UpdateScene() {
    if(m_CurrentScene == nullptr) return;

    m_CurrentScene->Update();
}

void SceneMenager::RenderScene() {
    if(m_CurrentScene == nullptr) return;

    m_CurrentScene->Render();
}