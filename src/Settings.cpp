#include "Settings.hpp"

#include <fstream>

#include "json.hpp"

#include "FileSystem.hpp"
#include "Debug.hpp"

Settings::Settings() : 
// Section: Gameplay
m_GameplayDisplayTime(true), m_GameplayCountdownAtTheBeginning(true), m_GameplayCountdownAfterPause(false),
m_GameplayDeselectTime(0.4f),
// Section: IO
m_IOSaveOnGameExit(false), m_IOSaveOnLevelExit(true) {
    DeserializeSettings();
}

Settings::~Settings() {
    SerializeSettings();
}


float& Settings::GetSettingF(SettingList setting) {
    switch(setting) {
        case GAMEPLAY_DESELECT_TIME: return m_GameplayDeselectTime;
    }
}

bool& Settings::GetSettingB(SettingList setting) {
    switch(setting) {
        case GAMEPLAY_DISPLAY_TIME: return m_GameplayDisplayTime;
        case GAMEPLAY_COUNTDOWN_AT_THE_BEGINNING: return m_GameplayCountdownAtTheBeginning;
        case GAMEPLAY_COUNTDOWN_AFTER_PAUSE: return m_GameplayCountdownAfterPause;
        case IO_SAVE_ON_GAME_EXIT: return m_IOSaveOnGameExit;
        case IO_SAVE_ON_LEVEL_EXIT: return m_IOSaveOnLevelExit;
    }
}

void Settings::SetSettingB(SettingList setting, bool value) {
    switch(setting) {
        case GAMEPLAY_DISPLAY_TIME: m_GameplayDisplayTime = value; break;
        case GAMEPLAY_COUNTDOWN_AT_THE_BEGINNING: m_GameplayCountdownAtTheBeginning = value; break;
        case GAMEPLAY_COUNTDOWN_AFTER_PAUSE: m_GameplayCountdownAfterPause = value; break;
        case IO_SAVE_ON_GAME_EXIT: m_IOSaveOnGameExit = value; break;
        case IO_SAVE_ON_LEVEL_EXIT: m_IOSaveOnLevelExit = value; break;
    }
}

void Settings::SetSettingF(SettingList setting, float value) {
    switch(setting) {
        case GAMEPLAY_DESELECT_TIME: m_GameplayDeselectTime = value; break;
    }
}

void Settings::SerializeSettings() {
    if(!FileSystem::Get().DataFileExists()) {
        return;
    }

    std::ifstream json_input("data.json");
    nlohmann::json json = nlohmann::json::parse(json_input);
    json_input.close();

    json["settings"]["gameplay_display_time"] = m_GameplayDisplayTime;
    json["settings"]["gameplay_countdown_after_pause"] = m_GameplayCountdownAfterPause;
    json["settings"]["gameplay_countdown_at_the_beginning"] = m_GameplayCountdownAtTheBeginning;
    json["settings"]["io_save_on_game_exit"] = m_IOSaveOnGameExit;
    json["settings"]["io_save_on_level_exit"] = m_IOSaveOnLevelExit;
    json["settings"]["gameplay_deselect_time"] = m_GameplayDeselectTime;

    std::ofstream json_output("data.json");
    json_output << json << std::endl;
    json_output.close();


    Debug::Log("Settings serialized successfully!");
}

void Settings::DeserializeSettings() {
    std::ifstream json_input = std::ifstream("data.json");
    nlohmann::json json = nlohmann::json::parse(json_input);

    m_GameplayDisplayTime = json["settings"]["gameplay_display_time"];
    m_GameplayCountdownAfterPause = json["settings"]["gameplay_countdown_after_pause"];
    m_GameplayCountdownAtTheBeginning = json["settings"]["gameplay_countdown_at_the_beginning"];
    m_IOSaveOnGameExit = json["settings"]["io_save_on_game_exit"];
    m_IOSaveOnLevelExit = json["settings"]["io_save_on_level_exit"];
    m_GameplayDeselectTime = json["settings"]["gameplay_deselect_time"];

    json_input.close();

    Debug::Log("Settings deserialized successfully!");
}

