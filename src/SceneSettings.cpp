#include "SceneSettings.hpp"

#include "raylib.h"
#include "raygui.h"

#include "SceneMenager.hpp"
#include "SceneMainMenu.hpp"

#include "ResourceMenager.hpp"
#include "Settings.hpp"

SceneSettings::SceneSettings() { }

void SceneSettings::Init() {
    Window::Get().SetVirtualWindowBackgroundColor(245, 245, 245);

    m_SettingSection = SECTION_GAMEPLAY;
    m_CurrentSettingSection = m_SettingSection;
}

void SceneSettings::Destroy() {

}

void SceneSettings::Update() {
    
}

void SceneSettings::Render() {
    std::string section_name;

    auto& resources = ResourceMenager::Get();
    auto& settings = Settings::Get();
     
    switch (m_SettingSection) {
        case SECTION_GAMEPLAY:
            section_name = std::string(TextFormat("%i. Gameplay", m_SettingSection + 1));

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
            GuiSlider(Rectangle { 272, 216, 120, 24 }, TextFormat("%0.02f", settings.GetSettingF(GAMEPLAY_DESELECT_TIME)), nullptr, &settings.GetSettingF(GAMEPLAY_DESELECT_TIME), 0.1f, 0.8f);


            break;

        case SECTION_IO:
            section_name = std::string(TextFormat("%i. File System", m_SettingSection + 1));

            // Setting: IO_SAVE_ON_GAME_EXIT
            GuiLabel(Rectangle { 24, 120, 288, 24 }, "Save the data on game exit:");
            GuiCheckBox(Rectangle { 368, 120, 24, 24 }, nullptr, &settings.GetSettingB(IO_SAVE_ON_GAME_EXIT));

            // Setting: IO_SAVE_ON_LEVEL_EXIT
            GuiLabel(Rectangle { 24, 152, 288, 24 }, "Save the data on level exit:");
            GuiCheckBox(Rectangle { 368, 152, 24, 24 }, nullptr, &settings.GetSettingB(IO_SAVE_ON_LEVEL_EXIT));

            break;

    }

    GuiSetStyle(LABEL, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);

    GuiSetStyle(DEFAULT, TEXT_SIZE, 64);
    GuiLabel(Rectangle { 0, 8, 400, 64 }, "Settings");
    GuiSetStyle(DEFAULT, TEXT_SIZE, ResourceMenager::Get().GetCurrentFont().baseSize);

    GuiLabel(Rectangle { 120, 80, 160, 24 }, section_name.c_str());

    if(m_CurrentSettingSection - 1 < 0) GuiDisable();

    if(GuiButton(Rectangle { 96, 80, 24, 24 }, GuiIconText(ICON_ARROW_LEFT_FILL, nullptr))) {
        resources.PlaySoundByName("click");
        m_CurrentSettingSection--;
    }

    GuiEnable();

    if(m_CurrentSettingSection + 1 >= LENGTH) GuiDisable();
    
    if(GuiButton(Rectangle { 280, 80, 24, 24 }, GuiIconText(ICON_ARROW_RIGHT_FILL, nullptr))) {
        resources.PlaySoundByName("click");
        m_CurrentSettingSection++;
    }

    GuiEnable();

    m_SettingSection = static_cast<SceneSettingSection>(m_CurrentSettingSection);

    GuiSetStyle(LABEL, TEXT_ALIGNMENT, DEFAULT);

    if(GuiButton(Rectangle { 136, 264, 128, 24 }, GuiIconText(ICON_RESTART, "Back"))) {
        settings.SerializeSettings();

        SceneMenager::Get().LoadScene(new SceneMainMenu());
        
        resources.PlaySoundByName("click");
    }
}