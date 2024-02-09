#include "SceneSettings.hpp"

#include <memory>

#include "raylib.h"
#include "raygui.h"

#include "ResourceMenager.hpp"

#include "SceneMenager.hpp"
#include "SceneMainMenu.hpp"

#include "SoundMenager.hpp"

#include "Settings.hpp"

#include "ResourceMenager.hpp"

SceneSettings::SceneSettings() { }

void SceneSettings::Init() {
    Window::Get().SetRendererBackgroundColor(235, 235, 235);

    m_SettingSection = SECTION_GAMEPLAY;
    m_CurrentSettingSection = m_SettingSection;
}

void SceneSettings::Destroy() {

}

void SceneSettings::Update() {
    
}

void SceneSettings::Render() {
    // TODO: 
    // - Implement the check for the arrow widgets if the're is an option to go between pages and don't go outside the bounds
    
    std::string section_name;

    auto& sounds = SoundMenager::Get();
    auto& settings = Settings::Get();
     
    switch (m_SettingSection) {
        case SECTION_GAMEPLAY:
            section_name = std::string(TextFormat("%i. Gameplay", m_SettingSection));

            if(GuiButton(Rectangle { 136, 264, 128, 24 }, GuiIconText(ICON_RESTART, "Back"))) {
                SceneMenager::Get().LoadScene(std::make_unique<SceneMainMenu>());
                sounds.PlaySoundFromCache("click");
            }

            // Setting: GAMEPLAY_DISPLAY_TIME
            GuiLabel(Rectangle { 24, 120, 288, 24 }, "Display the gameplay time:");
            GuiCheckBox(Rectangle { 368, 120, 24, 24 }, nullptr, &settings.GetSettingB(GAMEPLAY_DISPLAY_TIME));

            // Setting: GAMEPLAY_COUNTDOWN_AFTER_PAUSE
            GuiLabel(Rectangle { 24, 152, 288, 24 }, "Countdown after pause:");
            GuiCheckBox(Rectangle { 368, 152, 24, 24 }, nullptr, &settings.GetSettingB(GAMEPLAY_COUNTDOWN_AFTER_PAUSE));

            // Setting: GAMEPLAY_COUNTDOWN_AT_THE_BEGINNING
            GuiLabel(Rectangle { 24, 184, 288, 24 }, "Beginning countdown:");
            GuiCheckBox(Rectangle { 368, 184, 24, 24 }, nullptr, &settings.GetSettingB(GAMEPLAY_COUNTDOWN_AT_THE_BEGINNING));
            
            // Setting: GAMEPLAY_DESELECT_TIME
            GuiLabel(Rectangle { 24, 216, 240, 24 }, "Deselect time:");
            GuiSlider(Rectangle { 272, 216, 120, 24 }, nullptr, nullptr, &settings.GetSettingF(GAMEPLAY_DESELECT_TIME), 0.1f, 0.8f);


            break;
    }

    GuiSetStyle(LABEL, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);

    GuiSetStyle(DEFAULT, TEXT_SIZE, 64);
    GuiLabel(Rectangle { 0, 8, 400, 64 }, "Settings");
    GuiSetStyle(DEFAULT, TEXT_SIZE, ResourceMenager::Get().GetCurrentFont().baseSize);

    GuiLabel(Rectangle { 120, 80, 160, 24 }, section_name.c_str());
    if(GuiButton(Rectangle { 96, 80, 24, 24 }, GuiIconText(ICON_ARROW_LEFT_FILL, nullptr))) {
        sounds.PlaySoundFromCache("click");
    }

    if(GuiButton(Rectangle { 280, 80, 24, 24 }, GuiIconText(ICON_ARROW_RIGHT_FILL, nullptr))) {
        sounds.PlaySoundFromCache("click");
    }

    GuiSetStyle(LABEL, TEXT_ALIGNMENT, DEFAULT);

}