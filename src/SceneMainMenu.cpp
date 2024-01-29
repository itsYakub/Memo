#include "SceneMainMenu.hpp"

#include <memory>

#include "raylib.h"
#include "raygui.h"

#include "Debug.hpp"
#include "SceneGameplay.hpp"
#include "SceneMenager.hpp"

SceneMainMenu::SceneMainMenu() {
    Debug::Log("Created the main menu scene");
}

void SceneMainMenu::Init() {
    Window::Get().SetRendererBackgroundColor(245, 245, 245);
    m_MainMenuState = STATE_DEFAULT;
}

void SceneMainMenu::Destroy() {
    Debug::Log("Closing the main menu scene...");
}

void SceneMainMenu::Update() {
    
}

void SceneMainMenu::Render() {
    Window& window = Window::Get();
    SceneMenager& scene_menager = SceneMenager::Get();

    switch(m_MainMenuState) {
        case STATE_DEFAULT:
            if(GuiButton(Rectangle { window.GetRendererCenter().x - 64, window.GetRendererCenter().y, 128, 24 }, GuiIconText(ICON_PLAYER_PLAY, "Play"))) {
                m_MainMenuState = STATE_LEVEL_CHOOSING;
            } 

            if(GuiButton(Rectangle { window.GetRendererCenter().x - 64, window.GetRendererCenter().y + 32, 128, 24 }, GuiIconText(ICON_EXIT, "Quit"))) {
                window.CloseCallback();
            } 

            break;

        case STATE_LEVEL_CHOOSING:
            if(GuiButton(Rectangle { window.GetRendererCenter().x - 64, window.GetRendererCenter().y - 32, 128, 24 }, GuiIconText(ICON_PLAYER_PLAY, "Easy"))) {
                scene_menager.LoadScene(std::make_unique<SceneGameplay>(DIFFICULTY_EASY));
            } 

            if(GuiButton(Rectangle { window.GetRendererCenter().x - 64, window.GetRendererCenter().y, 128, 24 }, GuiIconText(ICON_PLAYER_PLAY, "Normal"))) {
                scene_menager.LoadScene(std::make_unique<SceneGameplay>(DIFFICULTY_NORMAL));
            } 

            if(GuiButton(Rectangle { window.GetRendererCenter().x - 64, window.GetRendererCenter().y + 32, 128, 24 }, GuiIconText(ICON_PLAYER_PLAY, "Hard"))) {
                scene_menager.LoadScene(std::make_unique<SceneGameplay>(DIFFICULTY_HARD));
            } 

            if(GuiButton(Rectangle { window.GetRendererCenter().x - 64, window.GetRendererCenter().y + 64, 128, 24 }, GuiIconText(ICON_RESTART, "Back"))) {
                m_MainMenuState = STATE_DEFAULT;
            } 

            break;
    }
}