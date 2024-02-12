#include "SceneMainMenu.hpp"

#include <memory>

#include "raylib.h"
#include "raygui.h"

#include "Debug.hpp"
#include "SceneGameplay.hpp"
#include "SceneMenager.hpp"
#include "SceneSettings.hpp"

#include "FileSystem.hpp"

#include "ResourceMenager.hpp"

#include "SoundMenager.hpp"

SceneMainMenu::SceneMainMenu() { }

void SceneMainMenu::Init() {
    Window::Get().SetRendererBackgroundColor(245, 245, 245);
    m_MainMenuState = STATE_DEFAULT;
}

void SceneMainMenu::Destroy() {

}

void SceneMainMenu::Update() {
    
}

void SceneMainMenu::Render() {
    auto& window = Window::Get();
    auto& scene_menager = SceneMenager::Get();
    auto& resources = ResourceMenager::Get();
    auto& sound_menager = SoundMenager::Get();

    switch(m_MainMenuState) {
        case STATE_DEFAULT:
            DrawTextureEx(resources.GetTextureByName("background"), Vector2 { 0, 0 }, 0.0f, 10.0f, WHITE);

            GuiSetStyle(LABEL, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);

            GuiSetStyle(DEFAULT, TEXT_SIZE, 96);
            GuiLabel(Rectangle { 56, 24, 288, 96 }, "Memo");
            GuiSetStyle(DEFAULT, TEXT_SIZE, resources.GetCurrentFont().baseSize);

            GuiSetStyle(LABEL, TEXT_ALIGNMENT, DEFAULT);

            // Main GUI buttons

            if(GuiButton(Rectangle { 136, 136, 128, 24 }, GuiIconText(ICON_PLAYER_PLAY, "Play"))) {
                m_MainMenuState = STATE_LEVEL_CHOOSING;
                sound_menager.PlaySoundFromCache("click");
            } 

            if(GuiButton(Rectangle { 136, 168, 128, 24 }, GuiIconText(ICON_GEAR_BIG, "Settings"))) {
                scene_menager.LoadScene(std::make_unique<SceneSettings>());
                sound_menager.PlaySoundFromCache("click");
            } 

            if(GuiButton(Rectangle { 136, 200, 128, 24 }, GuiIconText(ICON_EXIT, "Quit"))) {
                window.CloseCallback();
                sound_menager.PlaySoundFromCache("click");
            } 

            // Other GUI buttons
            // Github button (Icon ID 220 - Github)
            if(GuiLabelButton(Rectangle { 8, 264, 24, 24 }, GuiIconText(220, nullptr))) {
                OpenURL("https://github.com/itsYakub/Memo");
            }

            // Ko-fi button (Icon ID 221 - Ko-Fi)
            if(GuiLabelButton(Rectangle { 40, 264, 24, 24 }, GuiIconText(221, nullptr))) {
                OpenURL("https://ko-fi.com/yakub");
            }

            break;

        case STATE_LEVEL_CHOOSING:
            DrawTextureEx(resources.GetTextureByName("background"), Vector2 { 0, 0 }, 0.0f, 10.0f, WHITE);

            GuiSetStyle(LABEL, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);

            GuiSetStyle(DEFAULT, TEXT_SIZE, 32);
            GuiLabel(Rectangle { 40, 24, 320, 96 }, "Choose a level");
            GuiSetStyle(DEFAULT, TEXT_SIZE, resources.GetCurrentFont().baseSize);

            GuiSetStyle(LABEL, TEXT_ALIGNMENT, DEFAULT);

            if(GuiButton(Rectangle { 120, 136, 160, 24 }, FileSystem::Get().GetJson()["player"]["level_finish"][0] ? TextFormat("Easy (%.2fs)", (float) FileSystem::Get().GetJson()["player"]["level_best_time"][0]) : "Easy")) {
                scene_menager.LoadScene(std::make_unique<SceneGameplay>(DIFFICULTY_EASY));
                sound_menager.PlaySoundFromCache("click");
            } 

            if(GuiButton(Rectangle { 120, 168, 160, 24 }, FileSystem::Get().GetJson()["player"]["level_finish"][1] ? TextFormat("Normal (%.2fs)", (float) FileSystem::Get().GetJson()["player"]["level_best_time"][1]) : "Normal")) {
                scene_menager.LoadScene(std::make_unique<SceneGameplay>(DIFFICULTY_NORMAL));
                sound_menager.PlaySoundFromCache("click");
            } 

            if(GuiButton(Rectangle { 120, 200, 160, 24 }, FileSystem::Get().GetJson()["player"]["level_finish"][2] ? TextFormat("Hard (%.2fs)", (float) FileSystem::Get().GetJson()["player"]["level_best_time"][2]) : "Hard")) {
                scene_menager.LoadScene(std::make_unique<SceneGameplay>(DIFFICULTY_HARD));
                sound_menager.PlaySoundFromCache("click");
            } 

            if(GuiButton(Rectangle { 120, 232, 160, 24 }, GuiIconText(ICON_RESTART, "Back"))) {
                m_MainMenuState = STATE_DEFAULT;
                sound_menager.PlaySoundFromCache("click");
            } 

            break;
    }
}