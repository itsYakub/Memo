#include "SceneGameplay.hpp"

#include "raylib.h"
#include "raygui.h"

#include "MatchTable.hpp"
#include "Window.hpp"
#include "Debug.hpp"

#include "SceneMenager.hpp"
#include "SceneMainMenu.hpp"

SceneGameplay::SceneGameplay(const MatchTableDifficulty difficulty) {
    this->m_MatchTable = MatchTable(difficulty);

    Debug::Log("Created the gameplay scene");
}

void SceneGameplay::Init() {
    Window::Get().SetRendererBackgroundColor(245, 245, 245);
}

void SceneGameplay::Destroy() {
    for(auto& i : m_MatchTable.GetTable()) {
        i.Unload();
    }

    Debug::Log("Closing the gameplay scene...");
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

    if(GuiButton(Rectangle{ Window::Get().GetRendererSize().x - 20.0f, 4.0f, 16.0f, 16.0f }, GuiIconText(ICON_EXIT, nullptr))) {
        SceneMenager::Get().LoadScene(new SceneMainMenu());
    }
}
