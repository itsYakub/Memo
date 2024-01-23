#include "SceneGameplay.hpp"

#include "raylib.h"

#include "MatchTable.hpp"
#include "Window.hpp"
#include "Debug.hpp"

SceneGameplay::SceneGameplay(const MatchTableDifficulty difficulty) {
    this->m_MatchTable = MatchTable(difficulty);

    Debug::Log("Created the gameplay scene");
}

void SceneGameplay::Init() {
    Window::Get().SetRendererBackgroundColor(245, 245, 245);
}

void SceneGameplay::Destroy() {

}

void SceneGameplay::Update() {
    this->m_MatchTable.MatchTableProcessInput();

    if(IsKeyPressed(KEY_R)) {
        this->m_MatchTable = MatchTable(DIFFICULTY_EASY);
    }
}

void SceneGameplay::Render() {
    for(auto& i : this->m_MatchTable.GetTable()) {
        i.Render();
    }
}
