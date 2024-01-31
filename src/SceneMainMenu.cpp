#include "SceneMainMenu.hpp"

#include <memory>

#include "raylib.h"
#include "raygui.h"

#include "Debug.hpp"
#include "SceneGameplay.hpp"
#include "SceneMenager.hpp"

#include "PlayerData.hpp"

SceneMainMenu::SceneMainMenu() { }

void SceneMainMenu::Init() {
    Window::Get().SetRendererBackgroundColor(235, 235, 235);
    m_MainMenuState = STATE_DEFAULT;
}

void SceneMainMenu::Destroy() {

}

void SceneMainMenu::Update() {
    
}

void SceneMainMenu::Render() {
    Window& window = Window::Get();
    SceneMenager& scene_menager = SceneMenager::Get();

    switch(m_MainMenuState) {
        case STATE_DEFAULT:
            GuiSetStyle(LABEL, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);

            GuiSetStyle(DEFAULT, TEXT_SIZE, 96);
            GuiLabel(Rectangle { 48, 24, 304, 120 }, "Memo");
            GuiSetStyle(DEFAULT, TEXT_SIZE, 10);

            if(GuiButton(Rectangle { 136, 168, 128, 24 }, GuiIconText(ICON_PLAYER_PLAY, "Play"))) {
                m_MainMenuState = STATE_LEVEL_CHOOSING;
            } 

            if(GuiButton(Rectangle { 136, 200, 128, 24 }, GuiIconText(ICON_GEAR_BIG, "Settings"))) {
                
            } 

            if(GuiButton(Rectangle { 136, 232, 128, 24 }, GuiIconText(ICON_EXIT, "Quit"))) {
                window.CloseCallback();
            } 

            break;

        case STATE_LEVEL_CHOOSING:
            if(GuiButton(Rectangle { window.GetRendererCenter().x - 64, window.GetRendererCenter().y - 32, 128, 20 }, GuiIconText(ICON_PLAYER_PLAY, PlayerData::Get().GetCompleteState(0) ? TextFormat("Easy (%0.02fs)", PlayerData::Get().GetCompleteTime(0)) : "Easy"))) {
                scene_menager.LoadScene(std::make_unique<SceneGameplay>(DIFFICULTY_EASY));
            } 

            if(GuiButton(Rectangle { window.GetRendererCenter().x - 64, window.GetRendererCenter().y, 128, 20 }, GuiIconText(ICON_PLAYER_PLAY, PlayerData::Get().GetCompleteState(1) ? TextFormat("Normal (%0.02fs)", PlayerData::Get().GetCompleteTime(1)) : "Normal"))) {
                scene_menager.LoadScene(std::make_unique<SceneGameplay>(DIFFICULTY_NORMAL));
            } 

            if(GuiButton(Rectangle { window.GetRendererCenter().x - 64, window.GetRendererCenter().y + 32, 128, 20 }, GuiIconText(ICON_PLAYER_PLAY, PlayerData::Get().GetCompleteState(2) ? TextFormat("Hard (%0.02fs)", PlayerData::Get().GetCompleteTime(2)) : "Hard"))) {
                scene_menager.LoadScene(std::make_unique<SceneGameplay>(DIFFICULTY_HARD));
            } 

            if(GuiButton(Rectangle { window.GetRendererCenter().x - 64, window.GetRendererCenter().y + 64, 128, 20 }, GuiIconText(ICON_RESTART, "Back"))) {
                m_MainMenuState = STATE_DEFAULT;
            } 

            break;
    }
}