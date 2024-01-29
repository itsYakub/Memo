#include "SceneGameplay.hpp"

#include <memory>

#include "raylib.h"
#include "raygui.h"

#include "MatchTable.hpp"
#include "Window.hpp"
#include "Debug.hpp"

#include "SceneMenager.hpp"
#include "SceneMainMenu.hpp"

SceneGameplay::SceneGameplay(const MatchTableDifficulty difficulty) : m_MatchTable(difficulty), m_GameTime(0), m_GameplayState(STATE_GAMEPLAY) {
    Debug::Log("Created the gameplay scene");
}

SceneGameplay::~SceneGameplay() {
    Destroy();
}

void SceneGameplay::Init() {
    Window::Get().SetRendererBackgroundColor(245, 245, 245);
}

void SceneGameplay::Destroy() {
    Debug::Log("Closing the gameplay scene...");
}

void SceneGameplay::Update() {
    if(!m_MatchTable.GetCompleteState() && m_GameplayState == STATE_GAMEPLAY) {
        m_MatchTable.MatchTableProcessInput();
        m_GameTime += GetFrameTime();

        if(IsKeyPressed(KEY_ESCAPE)) {
            m_GameplayState = STATE_PAUSED;
        }
    } 
    
    else if(m_MatchTable.GetCompleteState()) {
        m_GameplayState = STATE_COMPLETE;
    }
}

void SceneGameplay::Render() {
    auto& window = Window::Get();

    switch(m_GameplayState) {
        case STATE_GAMEPLAY: 
            for(auto& i : m_MatchTable.GetTable()) {
                i.Render();
            }

            if(GuiLabelButton(Rectangle{ window.GetRendererSize().x - 80.0f, 4.0f, 64.0f, 16.0f }, GuiIconText(ICON_EXIT, "Exit"))) {
                SceneMenager::Get().LoadScene(std::make_unique<SceneMainMenu>());
            }

            if(GuiLabelButton(Rectangle{ window.GetRendererSize().x - 80.0f, 20.0f, 64.0f, 16.0f }, GuiIconText(ICON_RESTART, "Restart"))) {
                SceneMenager::Get().LoadScene(std::make_unique<SceneGameplay>((MatchTableDifficulty) m_MatchTable.GetDifficultyValue()));
            }


            GuiLabel(Rectangle { 0, 0, 128, 16 }, TextFormat("Time: %0.02fs", m_GameTime));

            break;

        case STATE_COMPLETE:
            GuiLabel(Rectangle { 0, 0, 192, 24 }, "Level Complete!");
            GuiLabel(Rectangle { 0, 24, 192, 24 }, GuiIconText(ICON_CLOCK, TextFormat("Time: %0.02fs", m_GameTime)));
            
            if(GuiButton(Rectangle { 0, 48, 96, 24 }, GuiIconText(ICON_RESTART, "Play again"))) {
                SceneMenager::Get().LoadScene(std::make_unique<SceneGameplay>((MatchTableDifficulty) m_MatchTable.GetDifficultyValue()));
            }

            if(GuiButton(Rectangle { 96, 48, 96, 24 }, GuiIconText(ICON_EXIT, "Quit"))) {
                SceneMenager::Get().LoadScene(std::make_unique<SceneMainMenu>());
            }

            break;

        case STATE_PAUSED: 
            GuiLabel(Rectangle { 0, 0, 128, 24 }, GuiIconText(ICON_PLAYER_PAUSE, "Pause"));
            if(GuiButton(Rectangle { 0, 24, 64, 24 }, GuiIconText(ICON_RESTART, "Resume"))) {
                m_GameplayState = STATE_GAMEPLAY;
            }

            if(GuiButton(Rectangle { 64, 24, 64, 24 }, GuiIconText(ICON_EXIT, "Quit"))) {
                SceneMenager::Get().LoadScene(std::make_unique<SceneMainMenu>());
            }

            break;
    }
        
}
