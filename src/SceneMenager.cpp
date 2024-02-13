#include "SceneMenager.hpp"

#include "Scene.hpp"
#include "Debug.hpp"

SceneMenager::SceneMenager() {
    Debug::Log("Scene Menager initialized successfully");
}

SceneMenager::~SceneMenager() {
    Debug::Log("Closing Sound Menager...");
    UnloadScene();
}

void SceneMenager::LoadScene(Scene* scene) {
    if(m_CurrentScene) { 
        UnloadScene();
    }

    m_CurrentScene = std::move(std::unique_ptr<Scene>(scene));
    m_CurrentScene->Init();
}

void SceneMenager::UnloadScene() {
    m_CurrentScene->Destroy();
}

void SceneMenager::UpdateScene() {
    if(!m_CurrentScene) return;

    m_CurrentScene->Update();
}

void SceneMenager::RenderScene() {
    if(!m_CurrentScene) return;

    m_CurrentScene->Render();
}