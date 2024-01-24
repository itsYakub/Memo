#include "SceneMainMenu.hpp"

#include "raylib.h"
#include "raygui.h"

#include "Debug.hpp"
#include "SceneGameplay.hpp"
#include "SceneMenager.hpp"

#include "SoundMenager.hpp"

SceneMainMenu::SceneMainMenu() {
    Debug::Log("Created the main menu scene");
}

void SceneMainMenu::Init() {
    Window::Get().SetRendererBackgroundColor(245, 245, 245);
}

void SceneMainMenu::Destroy() {
    Debug::Log("Closing the main menu scene...");
}

void SceneMainMenu::Update() {
    
}

void SceneMainMenu::Render() {
    if(GuiButton(Rectangle { 0, 0, 100, 25 }, "Play Easy")) {
        SceneMenager::Get().LoadScene(new SceneGameplay(DIFFICULTY_EASY));
    } 

    if(GuiButton(Rectangle { 0, 50, 100, 25 }, "Play Normal")) {
        SceneMenager::Get().LoadScene(new SceneGameplay(DIFFICULTY_NORMAL));
    } 

    if(GuiButton(Rectangle { 0, 100, 100, 25 }, "Play Hard")) {
        SceneMenager::Get().LoadScene(new SceneGameplay(DIFFICULTY_HARD));
    }     

    if(GuiButton(Rectangle { 0, 150, 100, 25}, "Quit")) {
        Window::Get().CloseCallback();
    }
}