#include "SceneGameplay.hpp"

#include "MatchTable.hpp"

void SceneGameplay::Init(Window* window) {
    this->m_MatchTable = MatchTable(DIFFICULTY_EASY);
    this->window = window;
}

void SceneGameplay::Destroy() {

}

void SceneGameplay::Update() {
    m_MatchTable.MatchTableProcessInput(window->GetVirtualMousePosition());
}

void SceneGameplay::Render() {
    for(auto& i : m_MatchTable.GetTable()) {
        i.Render();
    }
}
